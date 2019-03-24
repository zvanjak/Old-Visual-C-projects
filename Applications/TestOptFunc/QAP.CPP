#include "QAP.H"
#include <time.h>

/*****************************************************************************************/
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
	float	f=0.0;

	for( i=0; i<N(); i++ ) {
		for( j=0; j<N(); j++ ) {
			pi = Sol[i];
			pj = Sol[j];

			f += A[i][j] * B[pi][pj];
		}
		
		f += C[i][pi];
	}
	return f;
}

/*****************************************************************************************/
/*****************************************************************************************/

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
	srand(time(NULL));
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
	for( int i=0; i<N(); i++ )
		printf("Facility %3d  na lokaciji   %3d\n", i, Sol[i] );
}

int&	QAPCrom::operator[]( int i ) 
{
	if( i>=0 && i<N() )
		return Sol[i];
	else
		throw(1);
}

/*****************************************************************************************/
/*****************************************************************************************/

QAPSimpleGenetic::QAPSimpleGenetic( int inFacNum, int inPopSize, int inIterNum, float inMutProb )
		: QAPSimple(inFacNum), GenAlgTournamentSelection<QAPCrom>(inPopSize,inIterNum,inMutProb)
{
	// ovdje æe se kreirati polje praznih kromosoma
	CromList = new QAPCrom[PopulationSize];

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

	for( i=0; i<IterNum; i++ )
	{
		PerformSelection(&ToReplace, ToSurvive, 2);
		PerformCrossover(ToSurvive[0],ToSurvive[1],ToReplace);
		PerformMutation();

		if( i % 1000 == 0 )
		{
			// naæi æemo najbolju jedinku i ispisati f-ju cilja
			Max = CromList[0].GetFuncValue();
			BestInd = 0;
			for( j=1; j<PopulationSize; j++ )
				if( CromList[j].GetFuncValue() > Max )
				{
					Max = CromList[j].GetFuncValue();
					BestInd = j;
				}

			printf("\nIteracija %6d. Crom[%2d]= %f", i, BestInd, Max );
		}
	}
	CromList[BestInd].Print();
}

/*****************************************************************************************/
/*****************************************************************************************/

QAPSchedule::QAPSchedule(int inItemNum, int inItemMulNum, int inSlotNum) 
								: A(inItemNum,inItemNum), B(inSlotNum,inSlotNum), C(inItemNum,inItemNum)
{
	if( !A.IsValid() || !B.IsValid() || !C.IsValid() ) {
		// matrice se nisu ispravno alocirale
		ItemNum=0;
		ItemMultiplicity = 0;
		SlotNum = 0;
	}
	else {
		ItemNum=inItemNum;
		ItemMultiplicity = inItemMulNum;
		SlotNum = inSlotNum;

		A.Clear();
		B.Clear();
		C.Clear();
	}
}

void	QAPSchedule::SetMatrices( const Matrix<float> &a, const Matrix<float> &b, const Matrix<float> &c )
{
	SetA(a);
	SetB(b);
	SetC(c);
}

void	QAPSchedule::SetA( const Matrix<float> &a )
{
	if( a.RowNum() != N() || a.ColNum() != N() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		A = a;
}

void	QAPSchedule::SetB( const Matrix<float> &b )
{
	if( b.RowNum() != M() || b.ColNum() != M() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		B = b;
}

void	QAPSchedule::SetC( const Matrix<float> &c )
{
	if( c.RowNum() != N() || c.ColNum() != N() )
		// kriva dimenzija pridružene matrice
		throw(2);
	else
		C = c;
}

float	QAPSchedule::OptFunc(Matrix<int> &Sol) 
{
	int		i, j, k, l, pi, pj, pj2, start=1;;
	float	f=0.0;

	for( i=0; i<N(); i++ ) {
		for( j=i; j<N(); j++ ) {
			for( k=0; k<L(); k++ ) {		// ovdje treba definirati koji podrokovi se meðusobno raèunaju
					pi = Sol[i][k];

					if( k==0 ) {
						pj = Sol[j][0];
						f += A[i][j] * B[pi][pj];

						pj2 = Sol[j][1];
						if( pj2 > pi && pj < pi )
							f += A[i][j] * B[pi][pj2];
					}
					else if( k==2 ) {
						pj2 = Sol[j][2];
						f += A[i][j] * B[pi][pj2];

						pj = Sol[j][1];
						if( pj < pi && pj2 > pi )
							f += A[i][j] * B[pi][pj];
					}
					else {
						pj = Sol[j][k];
						f += A[i][j] * B[pi][pj];
						if( pj > pi ) {		// onda uzmi onog prije
							pj2 = Sol[j][k-1];
							f += A[i][j] * B[pi][pj2];
						}
						else {
							pj2 = Sol[j][k+1];
							f += A[i][j] * B[pi][pj2];
						}

					}
/*
						pi = Sol[i][k];
						pj = Sol[j][l];

						f += A[i][j] * B[pi][pj];
*/
//					}
//				}
			}
		}
/*
		if( k == 0 ) {
			if(  pi > pj )
				f += A[i][j] * B[pi][pj];
		}
		else if( k == L()-1 ) {
			if( pi < pj )
				f += A[i][j] * B[pi][pj];
		}
		else {
		}
*/
//  ?		f += C[i][pi];
	}
	return f;
}

/*****************************************************************************************/

QAPScheduleCrom::QAPScheduleCrom()
{
	ItemNum=0;
	ItemMultiplicity = 0;
	SlotNum = 0;
	MaxValue = 0;
}

QAPScheduleCrom::QAPScheduleCrom(int inItemNum, int inItemMulNum, int inSlotNum)
{
	Sol = Matrix<int>(inItemNum,inItemMulNum);
	
	if( !Sol.IsValid() ) {
		ItemNum=0;
		ItemMultiplicity = 0;
		SlotNum = 0;
	}
	else {
		ItemNum=inItemNum;
		ItemMultiplicity = inItemMulNum;
		SlotNum = inSlotNum;

		Sol.Clear();
	}
	MaxValue = 0;
}

QAPScheduleCrom::~QAPScheduleCrom()
{
//	delete Sol;
}

bool	QAPScheduleCrom::SetParameters(int inItemNum, int inItemMulNum, int inSlotNum)
{
	return SetItemNum(inItemNum) && SetItemMulNum(inItemMulNum) && SetSlotNum(inSlotNum);
}

bool	QAPScheduleCrom::SetItemNum( int inItemNum )
{
	if( inItemNum > 0 ) {
		if( inItemNum != ItemNum)			// ukoliko nam se mijenja dimenzija matrice
		{
//			if( !Sol == NULL )	
//				Sol = new Matrix<int>(inItemNum, L());
//			else
				Sol.Resize(inItemNum, L());
		}
		
		ItemNum = inItemNum;
		if( Sol.IsValid() )
			return true;
		else
			return false;
	}
	else
		return false;
}

bool	QAPScheduleCrom::SetItemMulNum( int inItemMulNum )
{
	if( inItemMulNum > 0 ) {
		if( inItemMulNum != L() )
		{
//			if( Sol == NULL )	
//				Sol = new Matrix<int>(N(), inItemMulNum);
//			else
				Sol.Resize(N(), inItemMulNum);
		}

		ItemMultiplicity = inItemMulNum;
		if( Sol.IsValid() )
			return true;
		else
			return false;
	}
	else
		return false;
}

bool	QAPScheduleCrom::SetSlotNum( int inSlotNum )
{
	if( inSlotNum > 0 ) {
		SlotNum = inSlotNum;
		return true;
	}
	else
		return false;
}

int		QAPScheduleCrom::GenerateCromosom()
{
	int		i, j, k, pos;
	bool	AlreadyTaken;

	for( i=0; i<N(); i++ )
		for( j=0; j<L(); j++ ) 
			Sol[i][j] = -1;	
	
	for( i=0; i<N(); i++ ) {
		for( j=0; j<L(); j++ ) 
		{
			do {
				pos = rand() % M();
				
				AlreadyTaken = false;
				for( k=0; k<j; k++ )				// treba provjeriti da li smo taj slot veæ zauzeli
					if( Sol[i][k] == pos )
						AlreadyTaken = true;
			} while( AlreadyTaken == true );
			
			Sol[i][j] = pos;		// i zatim postavi kuglicu u taj slot
		}
	}

	return 1;
}

void	QAPScheduleCrom::Print()
{
	for( int i=0; i<N(); i++ ) {
		printf("\n");
		for( int j=0; j<L(); j++ )
			printf(" %3d ", Sol[i][j] );
	}
}

int*	QAPScheduleCrom::operator[]( int i )		// vraæa se po referenci -> može biti l-value
{
	if( i>=0 && i<Sol.RowNum() )
		return Sol[i];
	else {
		throw(1);
		return NULL;
	}
}

/*****************************************************************************************/
/*****************************************************************************************/

QAPScheduleGenetic::QAPScheduleGenetic(int inItemNum, int inItemMulNum, int inSlotNum, int inPopSize, int inIterNum, float inMutProb )
		: QAPSchedule(inItemNum, inItemMulNum, inSlotNum)
		, GenAlgTournamentSelection<QAPScheduleCrom>(inPopSize,inIterNum,inMutProb)
{
	// ovdje æe se kreirati polje praznih kromosoma
	CromList = new QAPScheduleCrom[PopulationSize];

	// pa treba postaviti njihove parametre
	for( int i=0; i<PopulationSize; i++ )
		CromList[i].SetParameters(inItemNum,inItemMulNum,inSlotNum);

	pfCallBackRetrieve = NULL;
	pObj = NULL;

	bTerminateItself = false;
	bTerminationPerformed = false;
}

QAPScheduleGenetic::~QAPScheduleGenetic()
{
	delete []CromList;
}

void	QAPScheduleGenetic::PerformMutation()
{
	int		i, j, k, Ind, NewPos;
	bool	AlreadyExist;
	float	Prob;

	for( i=0; i<PopulationSize; i++ ) {
		for( j=0; j<N(); j++ ) {								// mutiramo kuglice za j-ti Item
			Prob = rand() / ((float) RAND_MAX);		// najprije odredi vjerojatnost mutacije
		
			if( Prob>=0 && Prob<=MutationProb/N() ) {
				// za j-tu vrstu kuglica odredi kuglicu èija æe se pozicija promijeniti
				Ind = rand() % L();

				do {
					NewPos = rand() % M();
					AlreadyExist = false;
					for( k=0; k<L(); k++ )
						if( CromList[i].Sol[j][k]==NewPos && k!=Ind )		// ukoliko nam je u tom slotu veæ neka kuglica
							AlreadyExist = true;
				} while( AlreadyExist == true );

				CromList[i].Sol[j][Ind] = NewPos;
				CromList[i].SetFuncValue(OptFunc(CromList[i]),CurrIterNum);
			}
		}
	}
}

QAPResults QAPScheduleGenetic::Optimize()
{
	int		ToReplace, ToSurvive[2];
	int		j, BestInd=0;
	float	Max=0;

	QAPResults		res;
	
	GenerateInitialPopulation();

	for( CurrIterNum=0; CurrIterNum<=IterNum; CurrIterNum++ )
	{
		PerformSelection(&ToReplace, ToSurvive, 2);
		PerformCrossover(ToSurvive[0],ToSurvive[1],ToReplace);
		PerformMutation();

		if( bTerminateItself == true )
			break;

		if( CurrIterNum % 1000 == 0 )
		{
			// naæi æemo najbolju jedinku i ispisati f-ju cilja
			Max = CromList[0].GetFuncValue();
			BestInd = 0;
			for( j=1; j<PopulationSize; j++ )
				if( CromList[j].GetFuncValue() > Max )
				{
					Max = CromList[j].GetFuncValue();
					BestInd = j;
				}
			
			if( pfCallBackRetrieve != NULL ) {
				OptResults		optres;

				optres = PrepareResults();
				pfCallBackRetrieve(&optres);
			}
			if( pObj != NULL ) {
				OptResults		optres;

				optres = PrepareResults();
				pObj->RefreshData(&optres);
			}
		}
	}
	CromList[BestInd].GetMaxValue(&res.FuncVal,&res.IterNum);
	GetIndividual(BestInd).Print();
//	CromList[BestInd].Print();

	bTerminationPerformed = true;
	return res;
}

/*****************************************************************************************/
/*****************************************************************************************/

int	CromosomCrossover( QAPCrom &a, QAPCrom &b, QAPCrom &res )
{
	for( int i=0; i<a.N(); i++ )
		if( rand() % 2 == 0 )
			res[i] = a[i];
		else
			res[i] = b[i];

	return 1;
}

// funkcija je definirana u ScheduleGenetic.cpp
int CmpQAP( const void *a, const void *b )
{
	if( *(int*)a < *(int*)b )
		return -1;
	else if( *(int*)a > *(int*)b )
		return 1;
	else
		return 0;
}
int	CromosomCrossover( QAPScheduleCrom &a, QAPScheduleCrom &b, QAPScheduleCrom &res )
{
	int			i, j, k, m, n;
	bool		AlreadyExist;

	for( i=0; i<a.N(); i++ )
	{
		for( j=0; j<a.L(); j++ )
		{
			do {
				m = rand() % 2;			// definira od koje jedinke æe uzeti termin
				n = rand() % a.L();	// koji termin æe uzeti
				AlreadyExist = false;

				for( k=0; k<j; k++ )
					if( m == 0 ) {
						if( res[i][k] == a[i][n] )
							AlreadyExist = true;
					}
					else {
						if( res[i][k] == b[i][n] )
							AlreadyExist = true;
					}
			} while( AlreadyExist == true);
			
			if( m == 0 )
				res[i][j] = a[i][n];
			else
				res[i][j] = b[i][n];
		}
		
		qsort(res[i], res.L(), sizeof(int), CmpQAP);
	}

	return 1;
}
