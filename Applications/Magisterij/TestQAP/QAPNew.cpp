#include "stdafx.h"

#include "GeneticAlgNew.h"
#include "QAPNew.h"

bool	CheckCrom( int p[], int n );

/*****************************************************************************************/

QAPSimple::QAPSimple(int inFacNum) : A(inFacNum,inFacNum), B(inFacNum,inFacNum), C(inFacNum,inFacNum)
{
	if( !A.IsValid() || !B.IsValid() || !C.IsValid() ) {
		// matrice se nisu ispravno alocirale
		FacilityNum=0;
	}
	else {
		FacilityNum=inFacNum;

		A.Clear();
		B.Clear();
		C.Clear();
	}
}

void	QAPSimple::SetMatrices( const Matrix<float> &a, const Matrix<float> &b, const Matrix<float> &c )
{
	SetA(a);
	SetB(b);
	SetC(c);
}

void	QAPSimple::SetA( const Matrix<float> &a )
{
	if( a.RowNum() != N() || a.ColNum() != N() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		A = a;
}

void	QAPSimple::SetB( const Matrix<float> &b )
{
	if( b.RowNum() != N() || b.ColNum() != N() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		B = b;
}

void	QAPSimple::SetC( const Matrix<float> &c )
{
	if( c.RowNum() != N() || c.ColNum() != N() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		C = c;
}

float	QAPSimple::OptFunc(std::vector<int> &Sol) 
{
	int		i, j, pi, pj;
	float	f=0.0, a, b;

	for( i=0; i<N(); i++ ) {
		for( j=0; j<N(); j++ ) {
			pi = Sol[i];
			pj = Sol[j];

			a = A[i][j];
			b = B[pi][pj];

			f += A[i][j] * B[pi][pj];
		}
		
		f += C[i][pi];
	}
	return -f;
}

/***************************************************************************************/
/***************************************************************************************/

QAPCrom::QAPCrom() 
{
	FacilityNum = 0;
}

QAPCrom::QAPCrom(int inFacNum) 
{
	if( inFacNum > 0 ) {
		Sol.resize(inFacNum);
		FacilityNum = inFacNum;
	}
	else
		FacilityNum = 0;
}

void	QAPCrom::SetFacilityNum( int inFacNum )
{
	if( inFacNum > 0 ) {
		Sol.resize(inFacNum);
		FacilityNum = inFacNum;
	}
	else
		FacilityNum = 0;
}

int	QAPCrom::GenerateCromosom() 
{
	int		i, n, x, y, tmp;

	n = N();
	// najprije æemo ih rasporediti po rednom broju
	for( i=0; i<n; i++ )
		Sol[i] = i;

	// a zatim æemo ih malo promiješati
	for( i=0; i<n*2; i++ ) {
		// najprije odredi indekse kuglica èije æemo pozicije zamijeniti
		x = rand() % n;
		y = rand() % n;

		// a zatim ih zamijeni
		tmp	= Sol[x];
		Sol[x] = Sol[y];
		Sol[y] = tmp;
	}

	return 1;
}

void QAPCrom::Print() 
{
	printf("\n");
	for( int i=0; i<N(); i++ )
		printf("Facility %3d  na lokaciji   %3d\n", i, Sol[i] );
}

void QAPCrom::PrintHorizontal() 
{
	printf("\n");
	for( int i=0; i<N(); i++ )
		printf(" %3d ", Sol[i] );
}

int&	QAPCrom::operator[]( int i ) 
{
	if( i>=0 && i<N() )
		return Sol[i];
	else
		throw(1);
}

bool	CheckCrom( int p[], int n ) {
	bool	*Exist = new bool[n];
	bool	ret = true;
	int		i;

	for( i=0; i<n; i++ )
		Exist[i] = false;

	for( i=0; i<n; i++ ) {
		if( Exist[p[i]] == true ) {
			ret=false;
		}
		else
			Exist[p[i]] = true;
	}
	delete []Exist;

	return ret;
}

/***************************************************************************************/
/***************************************************************************************/

QAPSimpleGenetic::QAPSimpleGenetic( int inFacNum, int inPopSize, int inIterNum, float inMutProb )
		: QAPSimple(inFacNum), GenAlgTournamentSelection<QAPCrom>(inPopSize,inIterNum,inMutProb)
{
	// pa treba postaviti njihove parametre
	for( int i=0; i<PopulationSize; i++ )
		CromList[i].SetFacilityNum(inFacNum);
}

void	QAPSimpleGenetic::PerformMutation()
{
	int		i, ind1, ind2, tmp;
	float	prob;

	for( i=0; i<PopulationSize; i++ ) {
		prob = rand() / ((float) RAND_MAX);		// najprije odredi vjerojatnost mutacije
		
		if( prob>=0 && prob<=MutationProb ) {
			// odredi indekse kuglica èije æe se pozicije (slotovi) zamijeniti
			ind1 = rand() % N();
			ind2 = rand() % N();

			tmp = (CromList[i])[ind1];		// (kromosom)operator[ind1] - da se malo pojasni što se zbiva
			CromList[i][ind1] = CromList[i][ind2];
			CromList[i][ind2] = tmp;
		}
	}
}

void QAPSimpleGenetic::Optimize()
{
	int		ToReplace, ToSurvive[2];
	int		i, j, BestInd;
	float	Max;
	
	GenerateInitialPopulation();

	for( i=CurrIterNum; CurrIterNum<IterNum; CurrIterNum++ )
	{
		PerformSelection(&ToReplace, ToSurvive, 2);
		PerformCrossover(ToSurvive[0],ToSurvive[1],ToReplace);
		PerformMutation();

		if( CurrIterNum% 1000 == 0 )
		{
			// naæi æemo najbolju jedinku i ispisati f-ju cilja
			Max = CromList[0].getFuncValue();
			BestInd = 0;
			for( j=1; j<PopulationSize; j++ )
				if( CromList[j].getFuncValue() > Max )
				{
					Max = CromList[j].getFuncValue();
					BestInd = j;
				}

			printf("\nIteracija %6d. Crom[%2d]= %f", CurrIterNum, BestInd, Max );
			addCurrentIteration();
		}
	}
	CromList[BestInd].PrintHorizontal();
}

/***************************************************************************************/
/***************************************************************************************/

int	CromosomCrossover( QAPCrom &a, QAPCrom &b, QAPCrom &res )
{
	// ovo polje nam govori koje brojeve smo veæ potrošili
	bool	*Exist = new bool[a.N()];
	bool	Set;
	int		i, j, N = a.N();

	for( i=0; i<N; i++ )
		Exist[i] = false;
	
	for( i=0; i<N; i++ ) {
		res[i]  = 0;
		
		if( a[i] == b[i] ) {			// ako su iste lokacije u obe jedinke, onda preuzmi
			res[i] = a[i];
			Exist[a[i]] = true;
		}
	}
	for( i=0; i<N; i++ ) {
		if( res[i] == 0 ) {			// samo ukoliko veæ nismo postavili 
			Set = true;					// govori da li smo uspjeli postaviti i-tu kuglicu na neko mjesto

			if( rand() % 2 == 0 ){						// biramo iz a
				if( Exist[a[i]] == false ) {		// ali samo ukoliko taj veæ nije izabran
					res[i] = a[i];
					Exist[a[i]] = true;
				}
				else if( Exist[b[i]] == false ) {		// provjeravamo da li je b[i] veæ zauzeto
					res[i] = b[i];
					Exist[b[i]] = true;
				}
				else
					Set = false;
			}
			else {
				if( Exist[b[i]] == false ) {				// ali samo ukoliko taj veæ nije izabran
					res[i] = b[i];
					Exist[b[i]] = true;
				}
				else if( Exist[a[i]] == false ) {		// provjeravamo da li je a[i] veæ zauzeto
					res[i] = a[i];
					Exist[a[i]] = true;
				}
				else
					Set = false;
			}

			if( Set == false ) {						// znaèi da su obje veæ bile zauzete
				for( j=0; j<N; j++ )					// pa æemo uzeti prvu slobodnu
					if( Exist[j] == false ) {
						res[i] = j;
						Exist[j] = true;
						break;
					}
			}
		}
	}
	delete []Exist;

/*
	if( CheckCrom(&res[0], N) == false ) {
		printf("\n");
		for( i=0; i<10; i++ )
			printf("  %d  ", a[i]);
		printf("\n");
		for( i=0; i<10; i++ )
			printf("  %d  ", b[i]);
		printf("\n");
		for( i=0; i<10; i++ )
			printf("  %d  ", res[i]);

		throw(3);
	}
*/

	return 1;
}
