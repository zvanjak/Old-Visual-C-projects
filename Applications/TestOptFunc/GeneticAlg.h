#if !defined(GENETIC_ALG)
#define GENETIC_ALG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <vector>
#include "ScheduleFramework.h"

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

class	Cromosom {
public:
	virtual	int			GenerateCromosom() = 0;

	float		GetFuncValue() { return Value; }
	void		GetMaxValue( float *Max, long *Iter ) { *Max = MaxValue; *Iter = MaxValInIterNum; }

	void		SetFuncValue( float Val ) { Value = Val; }
	void		SetFuncValue( float Val, long IterNum ) { 	
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

template<class _TCrom> class GeneticAlg {
public:
	// konstruktor
	GeneticAlg( int inPopulationSize, int inIterNum, float inMutationProb );

	// metode
	virtual	void		GenerateInitialPopulation() = 0;
	
	// ToReplace	- indeks jedinke koja je selekcijom odabrana za zamjenu
	// ToSurvive[]- popis indeksa jedinki koje æe preživjeti i iz kojih æe se križanjem dobiti nove
	virtual	void		PerformSelection(int *ToReplace, int ToSurvive[], int NumToSurvive) = 0;
	
	// Ind1, Ind2 - indeksi jedinki koje æe se križati
	// IndRes			- indeks jedinke u koju æe se staviti jedinka dobivena križanjem
	virtual	void		PerformCrossover(int Ind1, int Ind2, int IndRes) = 0;
	
	virtual	void		PerformMutation() = 0;

	virtual	float		OptFunc( _TCrom & ) = 0;

	// pristupne funkcije
	_TCrom&			GetIndividual( int i );		// ukoliko je 'i' izvan raspona, throw exception

	bool		SetPopulationSize( int inPopSize ) { 
						if( inPopSize>0 ) {
							PopulationSize = inPopSize;
							return true;
						} else return false;
					}
	bool		SetIterNum( long inIterNum ) { IterNum = inIterNum; return true;}
	bool		SetMutationProb( float inMutProb ) { MutationProb = inMutProb; return true; }

	int			GetPopulationSize() { return PopulationSize; }
	long		GetIterNum() { return IterNum; }
	float		GetMutProb() { return MutationProb; }

	OptResults	PrepareResults();

protected:
	// èlanske varijable
	int			PopulationSize;
	long		IterNum;
	float		MutationProb;

	long		CurrIterNum;

	_TCrom	*CromList;
};

/***************************************************************************************/
/***********************				    IMPLEMENTACIJA				      ************************/
/***************************************************************************************/

template<class _TCrom>
GeneticAlg<_TCrom>::GeneticAlg( int inPopulationSize, int inIterNum, float inMutationProb )
{
	PopulationSize = inPopulationSize;
	IterNum = inIterNum;
	MutationProb = inMutationProb;
	
	CurrIterNum = 0;
}

template<class _TCrom>
_TCrom& GeneticAlg<_TCrom>::GetIndividual( int i)
{
	if( i>=0 && i<GetPopulationSize() )
		return CromList[i];
	else {
		throw(1);
		return CromList[0];
	}
}

template<class _TCrom>
OptResults	GeneticAlg<_TCrom>::PrepareResults()
{
	OptResults		res;

	if( GetPopulationSize() > 0 ) {
		res.CRes.resize(GetPopulationSize());
		
		res.BestFuncVal = CromList[0].GetFuncValue();
		res.BestCromInd = 0;
		for( int i=0; i<GetPopulationSize(); i++ ) 
		{
			res.CRes[i].CurrFuncVal = CromList[i].GetFuncValue();
			CromList[i].GetMaxValue( &res.CRes[i].MaxFuncVal, &res.CRes[i].IterNumForMaxVal );

			if( CromList[i].GetFuncValue() > res.BestFuncVal ) {
				res.BestFuncVal = CromList[i].GetFuncValue();
				res.BestCromInd = i;
			}
		}
		res.IterNum = CurrIterNum;
	}
	
	return res;
}

/***************************************************************************************/
/******************				TOURNAMENT SELECTION ALGORITHM					**********************/
/***************************************************************************************/

template<class _TCrom> class GenAlgTournamentSelection : public GeneticAlg<_TCrom> {
public:
	GenAlgTournamentSelection(int PopSize, int IterNum, float MutProb) : GeneticAlg<_TCrom>(PopSize,IterNum,MutProb) {}
	~GenAlgTournamentSelection() {} 

	virtual	void		GenerateInitialPopulation();

	virtual	void		PerformSelection(int *ToReplace, int ToSurvive[], int NumToSurvive);
	virtual	void		PerformCrossover(int Ind1, int Ind2, int IndRes);
	virtual	void		PerformMutation() = 0;

	virtual	float		OptFunc( _TCrom & ) = 0;
};

template<class _TCrom> int	CromosomCrossover( _TCrom &a, _TCrom &b, _TCrom &res );

/***************************************************************************************/
/***********************				    IMPLEMENTACIJA				      ************************/
/***************************************************************************************/

template<class _TCrom> 
void	GenAlgTournamentSelection<_TCrom>::GenerateInitialPopulation()
{
	for( int i=0; i<PopulationSize; i++ ){
		CromList[i].GenerateCromosom();
		CromList[i].SetFuncValue(OptFunc(CromList[i]),0);
	}
}

template<class _TCrom> 
void	GenAlgTournamentSelection<_TCrom>::PerformSelection(int *ToReplace, int ToSurvive[], int NumToSurvive)
{
	int			i, j;
	int			*Random = new int[NumToSurvive + 1];
	bool		AlreadyExist;
	float		MinValue;

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
	MinValue = CromList[Random[0]].GetFuncValue();
	for( i=1; i<NumToSurvive+1; i++ )
		if( CromList[Random[i]].GetFuncValue() < MinValue )
		{
			MinValue = CromList[Random[i]].GetFuncValue();
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
	CromList[IndRes].SetFuncValue(OptFunc(CromList[IndRes]),CurrIterNum);
}

#endif