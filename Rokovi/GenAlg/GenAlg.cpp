#include "stdafx.h"
#include "GenAlg.h"

HANDLE	hConsOut;
int			PresjekStud[BR_ISPITA][BR_ISPITA];
int			BrojStud[BR_ISPITA];

void main( void )
{
	int		i, j, min_ind;
	double	min;
	int		a[BR_ROKOVA];
	Gen		Population[VEL_POP];
	Gen		CrossGen;
	Gen		temp;

//	Testiranje funkcija SetBit i IsBitSet
	/*
	long b=0;
	printf("\n %ld", SetBit(b,20) );
	b = SetBit(0,20);
	printf("\n %d", IsBitSet(b,21) );
	b = ClearBit(b,20);
	printf("\n %d", b);

	exit(1);
*/
	BrojStud[0] = 500;
	BrojStud[1] = 500;
	BrojStud[2] = 400;
	BrojStud[3] = 500;
	BrojStud[4] = 600;
	BrojStud[5] = 600;
	BrojStud[6] = 500;
	BrojStud[7] = 400;
	BrojStud[8] = 300;
	BrojStud[9] = 300;

	for( i=0; i<BR_ISPITA; i++ )
		for( j=0; j<BR_ISPITA; j++ )
			if( i == j )
				PresjekStud[i][j] = BrojStud[i];
			else
				PresjekStud[i][j] = 0;

	PresjekStud[0][1] = 100;
	PresjekStud[1][0] = 100;
	PresjekStud[0][2] = 200;
	PresjekStud[2][0] = 200;
	PresjekStud[0][3] = 400;
	PresjekStud[3][0] = 400;

	for( i=0; i<BR_ISPITA; i++ )
	{
		temp.TerminiIspita[i][0] = 0;
		temp.TerminiIspita[i][1] = 10;
		temp.TerminiIspita[i][2] = 19;
	}
	temp.TerminiIspita[0][0] = 3;
	temp.TerminiIspita[0][1] = 11;
	temp.TerminiIspita[0][2] = 19;

	temp.TerminiIspita[1][0] = 0;
	temp.TerminiIspita[1][1] = 8;
	temp.TerminiIspita[1][2] = 17;
	temp.TerminiIspita[2][0] = 2;
	temp.TerminiIspita[2][1] = 10;
	temp.TerminiIspita[2][2] = 17;
	temp.TerminiIspita[3][0] = 5;
	temp.TerminiIspita[3][1] = 13;
	temp.TerminiIspita[3][2] = 19;

//	printf("\n Funkcija dobrote = %lf", Func(temp) );
//	getch();

	srand( (unsigned)time( NULL ) );
	hConsOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GenerateInitialPopulation(Population);

//	PrintPopulation(Population);

	for( i=0; i<ITER_NUM; i++ )
	{
		// selekcija
		SelectRandomNumbers(a,3,0,VEL_POP-1);
		
		// treba naæi najlošiju jedinku
		min = Func(Population[a[0]]);
		min_ind =0 ;
		for( j=1; j<3; j++ )
			if( min > Func(Population[a[j]]) )
			{
				min = Func(Population[a[j]]);
				min_ind = j;
			}

		// križaj dvije jedinke koje su bolje od one treæe selektirane
		if( min_ind == 0 )
			CrossGen = Krizaj(Population[a[1]], Population[a[2]]);
		else if( min_ind == 1 )
			CrossGen = Krizaj(Population[a[0]], Population[a[2]]);
		else
			CrossGen = Krizaj(Population[a[0]], Population[a[1]]);

		Population[a[min_ind]] = CrossGen;

		Mutiraj(Population);

		if( i % 1000 == 0 )
			PrintConfig(Population);
	}
	PrintConfig(Population);
//	PrintPopulation(Population);
}

