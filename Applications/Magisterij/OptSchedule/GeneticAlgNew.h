#ifndef __GENETIC_ALG_NEW
#define __GENETIC_ALG_NEW

#pragma warning ( disable : 4786 )

#include <vector>
#include <map>

#include "Optimization.h"

using std::vector;
using std::map;

// forward declaration
class ResultsPool;

class GAErrException {
public:
	GAErrException( int inErrorID ) { ErrorID = inErrorID; }

private:
	int ErrorID;
};

/***************************************************************************************/
/***************************************************************************************/

class	CromResults {
public:
	float		CurrFuncVal;
	float		MaxFuncVal;
	long		IterNumForMaxVal;
};

class	OptResults {
public:
	float		BestFuncVal;
	int			BestCromInd;
	long		IterNum;

	vector<CromResults>		CRes; // rezultati pojedinog kromosoma
};

/***************************************************************************************/
/*******************				ABSTRACT INTERFACE CLASSES           ***********************/
/***************************************************************************************/

class	ICromosom {
public:
	virtual	int			GenerateCromosom() = 0;

	// vraæa trenutnu vrijednost funkcije cilja
	float		getFuncValue() { return Value; }
	
	// vraæa maksimalnu postignutu vrijednost funkcije cilja, i u kojoj je iteraciji postignuta
	void		getMaxValue( float *Max, long *Iter ) { 
						*Max = MaxValue; 
						*Iter = MaxValInIterNum; 
					}

	void		setFuncValue( float Val ) { Value = Val; }
	void		setFuncValue( float Val, long IterNum ) { 	
						Value = Val; 
						if( Val > MaxValue ) {
							MaxValue = Val;
							MaxValInIterNum = IterNum;
						} 
					}

protected:
	float		Value;						// vrijednost funkcije cilja za ovaj kromosom
	float		MaxValue;					// max. postignuta vrijednost funkcije cilja za ovu jedinku
	long		MaxValInIterNum;	// u kojoj iteraciji je postignuta ta max. vrijednost
};

template<class _TCrom> 
class IGeneticAlg /*: public virtual IIterativeOptimizationObject<float, _TCrom>*/
{
public:
	///////////////////////////////////////////////////////////////////////////////////////
	//		konstruktor
	IGeneticAlg( int inPopulationSize, long inIterNum, float inMutationProb );
	IGeneticAlg( int inPopulationSize, IOptTerminator *pTerm, float inMutationProb );
	~IGeneticAlg() {
		if( CromList != NULL )
			delete []CromList;
	}

 
	///////////////////////////////////////////////////////////////////////////////////////
	//		metode
	virtual	void		GenerateInitialPopulation() = 0;
	virtual	float		OptFunc( _TCrom & ) = 0;

	OptResults			PrepareResults();

	int		findMinCromIndex( float *outMinValue ) {
		int			BestInd = 0;
		float		Min;

		Min = CromList[0].getFuncValue();
		for( int j=1; j<getPopulationSize(); j++ )
			if( CromList[j].getFuncValue() < Min )
			{
				Min = CromList[j].getFuncValue();
				BestInd = j;
			}
		if( outMinValue != NULL )
			*outMinValue = Min;

		return BestInd;
	}
	
	int		findMaxCromIndex( float *outMaxValue) {
		int			BestInd = 0;
		float		Max;

		Max = CromList[0].getFuncValue();
		for( int j=1; j<getPopulationSize(); j++ )
			if( CromList[j].getFuncValue() > Max )
			{
				Max = CromList[j].getFuncValue();
				BestInd = j;
			}
		if( outMaxValue != NULL )
			*outMaxValue = Max;

		return BestInd;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//		pristupne funkcije
	_TCrom&		getIndividual( int i );		// ukoliko je 'i' izvan raspona, throw exception

	///////////////////////////////////////////////////////////////////////////////////////
	//		get i set metode
	int			getPopulationSize() { return PopulationSize; }
	bool		setPopulationSize( int inPopSize ) 
					{ 
						if( inPopSize>0 ) {						// provjera da li je ispravan broj
							PopulationSize = inPopSize;
							
							if( CromList != NULL ) {		// ukoliko smo veæ alocirali nekakvu listu jedinki
								delete []CromList;
								CromList = new _TCrom[getPopulationSize()];
							}
							return true;
						} 
						else 
							return false;
					}

	float		getMutProb() { return MutationProb; }
	bool		setMutProb( float inMutProb ) { MutationProb = inMutProb; return true; }

	///////////////////////////////////////////////////////////////////////////////////////
	//		Pool metode
	bool		addCurrentIteration();
	bool		getIterationResults( int IterNum, vector<float> &Res ) 
					{ 
						return CromPool.getIterationResults(IterNum,Res); 
					}

protected:
	///////////////////////////////////////////////////////////////////////////////////////
	//		èlanske varijable
	int			PopulationSize;
	float		MutationProb;
	long		CurrIterNum;

	_TCrom					*CromList;
	ResultsPool			CromPool;
};


/***************************************************************************************/
/******************				TOURNAMENT SELECTION ALGORITHM					**********************/
/***************************************************************************************/

template<class _TCrom> class GenAlgTournamentSelection : public IGeneticAlg<_TCrom> {
public:
	GenAlgTournamentSelection(int PopSize, long inIterNum, float MutProb) : IGeneticAlg<_TCrom>(PopSize,inIterNum,MutProb) {}
	GenAlgTournamentSelection(int PopSize, IOptTerminator *pTerm, float MutProb) : IGeneticAlg<_TCrom>(PopSize,pTerm,MutProb) {}
	~GenAlgTournamentSelection() {} 

	virtual	void		GenerateInitialPopulation();

	virtual	void		PerformSelection(int *ToReplace, int ToSurvive[], int NumToSurvive);
	virtual	void		PerformCrossover(int Ind1, int Ind2, int IndRes);
	virtual	void		PerformMutation() = 0;

	virtual	float		OptFunc( _TCrom & ) = 0;
};

template<class _TCrom> int	CromosomCrossover( _TCrom &a, _TCrom &b, _TCrom &res );

/***************************************************************************************/
/*******************								POOL	CLASSES								 ***********************/
/***************************************************************************************/

class ResultsPool {
public:
	ResultsPool( int inPopSize ) { PopSize = inPopSize; }

	bool	addData( int IterNum, vector<float>& Res );

	// vraæa cjelokupni rezultat iteracije
	bool	getIterationResults( int IterNum, vector<float>& Res );

	// vraæaju i postavljaju rezultate za pojedinu jedinku u iteraciji
	bool	getIndividualResult( int IterNum, int CromNum, float *Res );
	bool	setIndividualResult( int IterNum, int CromNum, float Res );

	void	Print();

private:
	int		PopSize;
	map<int, vector<float> > mapCromProgress;
};

/***************************************************************************************/
/***********************				    IMPLEMENTACIJA				      ************************/
/***************************************************************************************/

template<class _TCrom>
IGeneticAlg<_TCrom>::IGeneticAlg( int inPopulationSize, IOptTerminator *inpTerm, float inMutProb ) 
		: CromPool(inPopulationSize) /*, IIterativeOptimizationObject(inpTerm)*/
{
	CromList = NULL;

	if( setPopulationSize(inPopulationSize) && setMutProb(inMutProb) )
	{
		CurrIterNum = 0;
		CromList = new _TCrom[inPopulationSize];
	}
	else {
		throw(GAErrException(1));			// znaèi da nismo uspješno konstruirali objekt
	}
}

template<class _TCrom>
IGeneticAlg<_TCrom>::IGeneticAlg( int inPopulationSize, long inIterNum, float inMutProb ) : CromPool(inPopulationSize)
{
	CromList = NULL;
/*	
	IterativeOptTerminator		*pNewIter;

	pNewIter = new IterativeOptTerminator<(inIterNum);
	SetOptTerminatorObject(pNewIter);
*/
	if( setPopulationSize(inPopulationSize) && setMutProb(inMutProb) )
	{
		CurrIterNum = 0;
		CromList = new _TCrom[inPopulationSize];
	}
	else {
		throw(GAErrException(1));			// znaèi da nismo uspješno konstruirali objekt
	}
}

template<class _TCrom>
_TCrom& IGeneticAlg<_TCrom>::getIndividual( int i)
{
	if( i>=0 && i<getPopulationSize() )
		return CromList[i];
	else {
		throw(GAErrException(2));
		return CromList[0];
	}
}

template<class _TCrom>
bool	IGeneticAlg<_TCrom>::addCurrentIteration()
{
	vector<float>	Res;

	Res.resize(getPopulationSize());
	for( int i=0; i<getPopulationSize(); i++ )
		Res[i] = getIndividual(i).getFuncValue();

	CromPool.addData(CurrIterNum, Res);

	return true;
}

/***************************************************************************************/

template<class _TCrom> 
void	GenAlgTournamentSelection<_TCrom>::GenerateInitialPopulation()
{
	for( int i=0; i<PopulationSize; i++ ){
		CromList[i].GenerateCromosom();
		CromList[i].setFuncValue(OptFunc(CromList[i]),0);
	}
}

template<class _TCrom> 
void	GenAlgTournamentSelection<_TCrom>::PerformSelection(int *ToReplace, int ToSurvive[], int NumToSurvive)
{
	int			i, j;
	int			*Random = new int[NumToSurvive + 1];
	bool		AlreadyExist;
	float		MaxValue;

	// izaberi tri jedinke
	for( i=0; i<NumToSurvive+1; i++ ) {
		do 
		{
			Random[i] = rand() % PopulationSize;
			
			// treba provjeriti da li smo tu jedinku veæ odabrali
			AlreadyExist = false;
			for( j=0; j<i; j++ )
				if( Random[i] == Random[j] )
				{
					AlreadyExist = true;
					break;
				}
		} while( AlreadyExist == true );
	}
	
	// odredi iznos funkcije cilja za svaku
	*ToReplace = Random[0];
	MaxValue = CromList[Random[0]].getFuncValue();
	for( i=1; i<NumToSurvive+1; i++ )
		if( CromList[Random[i]].getFuncValue() > MaxValue )
		{
			MaxValue = CromList[Random[i]].getFuncValue();
			*ToReplace = Random[i];
		}

		// nakon što smo odabrali jedinku za zamjenu, treba preostale dvije pohraniti u polje ToSurvive
	j = 0;
	for( i=0; i<NumToSurvive+1; i++ )
		if( *ToReplace != Random[i] )		// ako to nije ona koja æe biti zamijenjena
			ToSurvive[j++] = Random[i];

	delete []Random;
}

template<class _TCrom> 
void	GenAlgTournamentSelection<_TCrom>::PerformCrossover(int Ind1, int Ind2, int IndRes)
{
	CromosomCrossover(CromList[Ind1], CromList[Ind2], CromList[IndRes]);
	CromList[IndRes].setFuncValue(OptFunc(CromList[IndRes]),CurrIterNum);
}

#endif
