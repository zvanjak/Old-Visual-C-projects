// FileDiff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	FILE		*fp1, *fp2;

	fp1 = fopen("C:\\06.jpg", "r");
	fp2 = fopen("C:\\my06.jpg", "r");

	int i=0, a, b;
	while( (a=fgetc(fp1)) != EOF ) {
		b = fgetc(fp2);

		if( a != b ) {
			printf("Razlika na %d", i);
			break;
		}
	}

	return 0;
}

