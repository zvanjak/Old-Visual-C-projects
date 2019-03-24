#include "QAPNew.h"

#include <time.h>
#include <conio.h>


void main() {
	QAPSimpleGenetic	QAP(19, 50,5000,0.01f);
	Matrix<float>		A(19,19), B(19,19), C(19,19);
	
	float	SolFunc = 17212548;
	int	Sol[19] = {9, 10, 7, 18, 14, 19, 13, 17, 6, 11, 4, 5, 12, 8, 15, 16, 1, 2, 3 };

	A.Clear();
	B.Clear();
	C.Clear();
	
	FILE *fp;
	int		i, j, n, a;

	fp = fopen("els19.dat", "r");
	fscanf(fp, "%d\n", &n );
	for( i=0; i<19; i++ ) {
		for( j=0; j<19; j++ ) {
			fscanf(fp, " %3d", &a);
			A[i][j] = a;
		}
	}
//	B.Print(5,0);
//	getch();

	for( i=0; i<19; i++ ) {
		for( j=0; j<19; j++ ) {
			fscanf(fp, " %5d", &a);
			B[i][j] = a;
		}
	}
//	A.Print(6,0);
//	getch();

/*
	for( i=0; i<10; i++ ) {
		for( j=0; j<10; j++ ) {
			A[i][j] = rand() % 100;
			B[i][j] = abs(i-j);
		}
	}
*/
	QAP.SetA(A);
	QAP.SetB(B);
	QAP.SetC(C);

	QAP.Optimize();

	printf("\n");
	for( i=0; i<19; i++ ) {
		printf(" %3d ", Sol[i]-1);
	}
	printf("\n Optimal value = %f \n", SolFunc);


	vector<float>	Res;
//	Res.resize(50);

	bool ret = QAP.getIterationResults(4000,Res);
	if( ret == true ) {
		for( i=0; i<50; i++ )
			printf(" \n %f", Res[i] );
	}

/*		Test CromosomCrossover
	QAPCrom		Crom1(10), Crom2(10), CromRes(10);
	int		i;

	srand(time(NULL));
	Crom1.GenerateCromosom();
	Crom2.GenerateCromosom();

	for( i=0; i<10; i++ )
		printf("  %d  ", Crom1[i]);
	printf("\n");
	for( i=0; i<10; i++ )
		printf("  %d  ", Crom2[i]);

	CromosomCrossover(Crom1, Crom2, CromRes);

	printf("\n");
	for( i=0; i<10; i++ )
		printf("  %d  ", CromRes[i]);
*/
}