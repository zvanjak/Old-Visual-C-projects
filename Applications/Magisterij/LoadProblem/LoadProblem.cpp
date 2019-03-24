// LoadProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	char	Name[100];
	FILE	*fp;

	printf("\n Unesi ime datoteke : ");
	gets(Name);

	if( (fp=fopen(Name, "r")) == NULL ) {
		puts("Greška kod otvaranja !!!");
		return (1);
	}

	int		i, j, Size;
	Matrix<float>		*A, *B;

	fscanf(fp, "%d", &Size);
	if( Size > 0 && Size < 1000 ) {
		A = new Matrix<float>(Size,Size);
		B = new Matrix<float>(Size,Size);
	}
	else {
		puts("Greška kod uèitavanja velièine problema ");
		return 1;
	}

	for( i=0; i<Size; i++ )
		for( j=0; j<Size; j++ )
			fscanf(fp, "%f", &(*A)[i][j] );

	for( i=0; i<Size; i++ )
		for( j=0; j<Size; j++ )
			fscanf(fp, "%f", &(*B)[i][j] );

	A->Print(stdout, "%5.0f");
	puts(" ");
	B->Print(stdout, "%5.0f");

	return 0;
}
