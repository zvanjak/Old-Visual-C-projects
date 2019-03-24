#pragma warning ( disable : 4786 )

/*
	Zahtjev na _SAConfig je da ima u sebi funkciju 
							float	CalcRandomConfigChange(_SAConfig *New)
*/
template<class _SAConfig> 
class ISimAnnealing : public IIterativeOptimizationObject
{
public:
	// poèetna temperatura
	virtual	float		InitialTemperature() = 0;
	// izraèunava sljedeæu temperaturu u annealing schedele
	virtual	float		NextTemperature( float CurrTemp, long IterNum ) = 0;
	// da li je za danu temperaturu dostignuta termalna ravnoteža
	virtual	bool		IsEquilibriumReached() = 0;

	// mijenja trenutnu konfiguraciju Old i vraæa novu konfiguraciju New(ako je razlièito od NULL)
	// te promjenu energije
	virtual	float		ChangeConfig( _SAConfig &Old, _SAConfig *New ) = 0;

	// funkcija cilja
	virtual	float		OptFunc( _SAConfig	&Conf ) = 0;
	// glavna funkcija za optimizaciju
	virtual	float		Optimize( IterOptContResWithSolutions<float,_SAConfig> *Res ) = 0;
};

template<class _SAConfig>	class SimpleSimAnnealing : public ISimAnnealing<_SAConfig> 
{
protected:
	long						CurrIterNum;

	double					AcceptHigherProb;
	double					TempChangeFactor;
	int							PermNum;

public:
	SimpleSimAnnealing(	IOptTerminator	*inpTerm,
											double					inAcceptHigherProb=0.99,
											double					inTempChangeFactor = 0.99,
											int							inPermNum = 100) 
			: IIterativeOptimizationObject(inpTerm)
	{
		AcceptHigherProb = inAcceptHigherProb;
		TempChangeFactor = inTempChangeFactor;
		PermNum	 = inPermNum;
	}
	
	~SimpleSimAnnealing() {
		if( pTermObj != NULL )
			delete pTermObj;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// funkcije koje treba overloadati da bi algoritam mogao raditi
	//		moraju se postaviti parametri strukture koja æe sadržavati rješenja
	virtual	void		SetConfigurationParameters( _SAConfig &Sol ) = 0;
	//		mora se definirati funkcija cilja u ovisnosti o strukturi rješenja
	virtual float		OptFunc( _SAConfig	&Conf ) = 0;

	//////////////////////////////////////////////////////////////////////////////////////
	//	funkcije iz suèelja ISimAnnealing
	float		InitialTemperature() {
		return ( AverageEnergyInc(Sol) / log ( 1 / AcceptHigherProb ) );
	}
	float		NextTemperature( float CurrTemp, long IterNum ) {
		return CurrTemp * TempChangeFactor;
	}
	bool		IsEquilibriumReached() { 
		if( CurrIterNum != 0 && CurrIterNum % PermNum == 0 )
			return true;
		else
			return false;
	}
	float		ChangeConfig( _SAConfig &Old, _SAConfig *New ) {
		return Old.CalcRandomConfigChange(New);
	}

	virtual float		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res ) 
	{
		_SAConfig		Sol, NewSol, BestSolution;

		SetConfigurationParameters( Sol );
		SetConfigurationParameters( NewSol );
		SetConfigurationParameters( BestSolution );

		int				j, Ind1, Ind2, temp;
		float			TimeElapsed, BestSoFar;
		double		dE, T, E;
		clock_t		TimeStart = clock();

		StartOptimization();

		// najprije generiramo poèetno rješenje
		Sol.GenerateRandom();
		BestSoFar = E = OptFunc(Sol);
		BestSolution = Sol;

		T = InitialTemperature();
		
		CurrIterNum = 0;
		while( IsOptimizationFinished() == false )
		{
			while( IsEquilibriumReached() != true )	{
				// promjeni konfiguraciju
				dE = ChangeConfig(Sol, &NewSol);
				
				// ukoliko se radi o smanjenju energije, uzmi uvijek
				// a ukoliko ne, onda provjeri Boltzmannov zakon
				if( dE < 0 || (exp(-dE / T)) > (rand() / RAND_MAX) ) 
				{
					// nova konfiguracija prihvaæena
					Sol = NewSol;
					E += dE;
					
					if( E < BestSoFar ) {
						BestSoFar = E;
						BestSolution = Sol;
					}
				}
			}
			// smanji temperaturu
			T = TempChangeFactor * T;

			NextStep(&E);
			CurrIterNum++;
		}
		TimeElapsed = (clock() - TimeStart) * 1000.f / CLOCKS_PER_SEC;

		Res->setBestFuncValue(BestSoFar);
		Res->setSolution(BestSolution);
		Res->setIterNum(CurrIterNum);
		Res->setOptimDuration(TimeElapsed);

		return 1; 
	}

	//////////////////////////////////////////////////////////////////////////////////////
	//	dodatne funkcije
	double	AverageEnergyInc( QAPSolution &Sol ) {
		int			i, nNum=0;
		double	dTotEnergy=0, dE;

		for( i=0; i<100; i++ ) {
			// promjeni malo konfiguraciju i izraèunaj kolika je promjena energije
			dE = CalcRandomChangeConfig(Sol);
			if( dE > 0 ) {
				dTotEnergy += dE;
				nNum++;
			}
		}
		return (dTotEnergy/nNum);		// vrati prosjeènu promjenu energije
	}
};
