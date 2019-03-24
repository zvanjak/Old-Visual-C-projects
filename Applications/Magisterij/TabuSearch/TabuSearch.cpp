// TabuSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define		N		10
#define		LIST_SIZE		30

using std::vector;
using	std::pair;
using std::cout;

class ValuePair {
public:
	ValuePair() {}
	ValuePair( float inVal, int i, int j ) {
		Value = inVal;
		Ind = std::make_pair(i,j);
	}

	float		Value;
	std::pair<int,int>	Ind;
};

bool	ValuePairLess( const ValuePair &x, const ValuePair &y ){
	return x.Value < y.Value;
}

bool	ValuePairGreater( const ValuePair &x, const ValuePair &y ){
	return x.Value > y.Value;
}

class SecondValuePair {
public:
	SecondValuePair() {}
	SecondValuePair( float inVal, int i, int j, int k, int l ) {
		Value = inVal;
		IndA = std::make_pair(i,j);
		IndB = std::make_pair(k,l);
	}

	float Value;
	std::pair<int,int>	IndA;
	std::pair<int,int>	IndB;
};

bool	SecondValuePairLess( const SecondValuePair &x, const SecondValuePair &y ){
	return x.Value < y.Value;
}

// A je matrica toka
// B je matrica udaljenosti

void	Switch( int *x, int *y );
float	OptFunc( float A[N][N], float B[N][N], int Sol[N] );
bool	GetNonDiagSmallestElemIndexes( Matrix<float>	&Mat, int Num, std::vector<ValuePair>	&Res );
bool	GetNonDiagLargestElemIndexes( Matrix<float>	&Mat, int Num, std::vector<ValuePair>	&Res );


int main(int argc, char* argv[])
{
	int		i, j;
	Matrix<float>	A(N,N), B(N,N);

	srand(100);
	// generiramo sluèajno matricu toka i udaljenosti
	for( i=0; i<N; i++ )
		for( j=i+1; j<N; j++ ) {
			A[i][j] = (float) (rand() % 100);
			A[j][i] = A[i][j];
			B[j][i] = (float) (rand() % 10);
			B[i][j] = B[j][i];
		}
	// matrica je simetrièna i na dijagonalama su 0
	for( i=0; i<N; i++ )
		A[i][i] = B[i][i] = 0;

	printf("Matrica A");
	for( i=0; i<N; i++ ) {
		printf("\n");
		for( j=0; j<N; j++ ) {
			printf("  %3.0f  ", A[i][j] );
		}
	}
	printf("\nMatrica B");
	for( i=0; i<N; i++ ) {
		printf("\n");
		for( j=0; j<N; j++ ) {
			printf("  %3.0f  ", B[i][j] );
		}
	}

	long		r, r_dot;
	float		alpha, beta;

	alpha = 0.5f;
	beta = 0.1f;

	std::vector<ValuePair>	ResA;
	std::vector<ValuePair>	ResB;

	r = beta*(N*N - N);
	r_dot = alpha*beta*(N*N-N);

	GetNonDiagSmallestElemIndexes( A, r, ResA );
	GetNonDiagLargestElemIndexes( B, r, ResB );

	std::vector<SecondValuePair>	ResSec;
	
	ResSec.resize(r);
	for( i=0; i<r; i++ )
		ResSec[i] = SecondValuePair(ResA[i].Value*ResB[i].Value, ResA[i].Ind.first, ResA[i].Ind.second, ResB[i].Ind.first, ResB[i].Ind.second);

	std::sort(ResSec.begin(), ResSec.end(), SecondValuePairLess);
	for( i=0; i<r_dot; i++ ) {
		printf("\n %f (%d,%d) (%d,%d) ", ResSec[i].Value, ResSec[i].IndA.first, ResSec[i].IndA.second, ResSec[i].IndB.first, ResSec[i].IndB.second );
	}

	getch();
	
/***************************************************************************************/
/***************************************************************************************/
/*												TABU SEARCH

	int		NextVisit[N][N];

	// matrica NextVisit nam govori u sljedeæoj kojoj iteraciji je dopušteno ponovo obaviti taj potez
	for( i=0; i<N; i++ )
		for( j=0; j<N; j++ )
			NextVisit[i][j] = 0;
	int		x, y, Sol[N];

	srand(time(NULL));

	// generiramo poèetno rješenje
	// najprije æemo ih rasporediti po redu
	for( i=0; i<N; i++ )
		Sol[i] = i;
	
	// a zatim æemo ih malo ispremiješati
	for( i=0; i<100; i++ ) {
		x = rand() % N;
		y = rand() % N;
		
		if( x != y ) 
			Switch(&Sol[x], &Sol[y]);
	}

	long		IterNum;
	int			r, s, k, ps, pk, pr, best_r, best_s;
	float		move_value, best_move_value, func_value, func_value2, BestSoFar=1e20f;

	// poèetna vrijednost funkcije cilja
	func_value = OptFunc(A,B,Sol);
	printf("\n\nPoèetna vrijednost funkcije cilja = %f", func_value );
	printf("\nPoèetno rješenje : ");
	for( i=0; i<N; i++ )
		printf("  %d  ", Sol[i]);

	printf("\n");

	for( IterNum=0; IterNum<50; IterNum++ ) {
		// treba izraèunati promjenu funkcije cilja za sve moguæe poteze
		best_move_value = 1e20f;

		for( r=0; r<N-1; r++ ) {
			for( s=r+1; s<N; s++ ) {

				move_value = 0;

				// raèunamo vrijednost poteza
				for( k=0; k<N; k++ ) {
					if( k!=s && k!=r ) {
						ps = Sol[s];
						pr = Sol[r];
						pk = Sol[k];
						
						move_value -= 2*(A[s][k] - A[r][k]) * ( B[ps][pk] - B[pr][pk]);
					}
				}

				if( move_value < best_move_value && NextVisit[r][s] <= IterNum && NextVisit[s][r] <= IterNum ) {
					best_move_value = move_value;
					best_r = r;
					best_s = s;
				}
			}
		}
		if( func_value < BestSoFar )
			BestSoFar = func_value;

		// napravi potez
		Switch(&Sol[best_s], &Sol[best_r]);
		NextVisit[best_r][best_s] = IterNum + LIST_SIZE;

		// ažuriraj funkciju cilja
		func_value += best_move_value;

		if( IterNum % 1 == 0 ) {
			printf("\nIter%4d, move=(%d,%d), val=%7.1f, func=%f", IterNum, best_r, best_s, best_move_value, func_value );
			
			printf("Sol : ");
			for( i=0; i<N; i++ )
				printf(" %d ", Sol[i]);
		}

//		func_value2 = OptFunc(A,B,Sol);
//		printf("\nIzracunata funkcija cilja = %f\n", func_value2 );
	}

	// konaèna vrijednost funkcije cilja
	func_value2 = OptFunc(A,B,Sol);
	printf("\nKonaèna vrijednost funkcije cilja = %f\n", func_value2 );

	printf("\nNajbolja vrijednost funkcije cilja = %f", BestSoFar );
*/
	return 0;
}

void Switch( int *x, int *y )
{
	int	temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

float	OptFunc( float A[N][N], float B[N][N], int Sol[N] )
{
	int		i, j, pi, pj;
	float	f = 0;

	for( i=0; i<N; i++ )
		for( j=0; j<N; j++ ) {
			pi = Sol[i];
			pj = Sol[j];
			
			f += A[i][j] * B[pi][pj];
		}

	return f;
}

bool	GetNonDiagSmallestElemIndexes( Matrix<float>	&Mat, int Num, std::vector<ValuePair>	&Res )
{
  typedef vector<ValuePair> ValuePairVector ;
  typedef ValuePairVector::iterator ValuePairVectorIt ;

	int			i, j, k;
	long		Rows, Cols;

	std::vector<ValuePair>	ResTemp;

	Rows = Mat.RowNum();
	Cols = Mat.ColNum();

	k = 0;
	ResTemp.resize(Rows*(Cols-1));

	for( i=0; i<Rows; i++ )
		for( j=0; j<Cols; j++ )
			if( i != j )									// samo za nedijagonalne elemente
				ResTemp[k++] = ValuePair(Mat[i][j],i,j);

  ValuePairVectorIt start, end;

  start = ResTemp.begin() ;   // location of first
  end		= ResTemp.end() ;       // one past the location

	std::sort(start, end, ValuePairLess) ;

	Res.resize(Num);
	for( i=0; i<Num; i++ )	Res[i] = ResTemp[i];

	return true;
}

bool	GetNonDiagLargestElemIndexes( Matrix<float>	&Mat, int Num, std::vector<ValuePair>	&Res )
{
  typedef vector<ValuePair> ValuePairVector ;
  typedef ValuePairVector::iterator ValuePairVectorIt ;

	int			i, j, k;
	long		Rows, Cols;

	std::vector<ValuePair>	ResTemp;

	Rows = Mat.RowNum();
	Cols = Mat.ColNum();

	k = 0;
	ResTemp.resize(Rows*(Cols-1));

	for( i=0; i<Rows; i++ )
		for( j=0; j<Cols; j++ )
			if( i != j )									// samo za nedijagonalne elemente
				ResTemp[k++] = ValuePair(Mat[i][j],i,j);

  ValuePairVectorIt start, end;

  start = ResTemp.begin() ;   // location of first
  end		= ResTemp.end() ;       // one past the location

	std::sort(start, end, ValuePairGreater) ;

	Res.resize(Num);
	for( i=0; i<Num; i++ )	Res[i] = ResTemp[i];

	return true;
	return true;
}
