#include "stdafx.h"
#include "GenAlg.h"

extern HANDLE hConsOut;
extern int		PresjekStud[BR_ISPITA][BR_ISPITA];
extern int		BrojStud[BR_ISPITA];

#define MIN_DISTANCE		8

/*************************************************************************************/

double Func( Gen a )
{
	int			i, j, k;
	double	fd = 0.0, dist;
	
	// najprije raèunamo doprinose za ispite pojedinaèno ( da termini budu što udaljeniji, 
	// i to  ponderirano sa brojem studenata koji slušaju taj ispit
	for( i=0; i<BR_ISPITA; i++ )
		for( j=0; j<BR_ROKOVA-1; j++ )
			fd += pow( BrojStud[i] * fabs(a.TerminiIspita[i][j] - a.TerminiIspita[i][j+1]), 0.5);

	// zatim æemo izraèunati kažnjavanje zbog prevelike blizine dva termina istog ispita
	for( i=0; i<BR_ISPITA; i++ )
		for( j=0; j<BR_ROKOVA-1; j++ )
		{
			dist = fabs(a.TerminiIspita[i][j] - a.TerminiIspita[i][j+1]);
			if( dist < MIN_DISTANCE )
				fd -= 150 * pow((MIN_DISTANCE - dist), 3);
		}

	// zatim æemo kazniti odstupanje od podjele na podrokove
	int		NajkasnijiTermin, NajranijiTermin;

	for( k=0; k<BR_ROKOVA-1; k++ )
	{
		// treba naæi ispit s najkasnijim terminom na ovom roku
		NajkasnijiTermin = a.TerminiIspita[0][k]; 
		for( i=1; i<BR_ISPITA; i++ )
			if( a.TerminiIspita[i][k] > NajkasnijiTermin )
				NajkasnijiTermin = a.TerminiIspita[i][k];

		// zatim treba naæi ispit s najranijim terminom na slijedeæem roku
		NajranijiTermin = a.TerminiIspita[0][k+1]; 
		for( i=1; i<BR_ISPITA; i++ )
			if( a.TerminiIspita[i][k+1] < NajranijiTermin )
				NajranijiTermin = a.TerminiIspita[i][k];

		// zatim treba proæi kroz sve ispite ovog roka koji su kasnije od najranijeg termina
		if( NajkasnijiTermin >= NajranijiTermin )
		{
			for( i=0; i<BR_ISPITA; i++ )
				if( a.TerminiIspita[i][k] >= NajranijiTermin )
					fd -= 100 * ( 1 + a.TerminiIspita[i][k] - NajranijiTermin );
		}
	}

	
	// sada æemo raèunati doprinos presjeka studenata
	for( i=0; i<BR_ISPITA; i++ )
		for( j=0; j<BR_ISPITA; j++ )
			for( k=0; k<BR_ROKOVA; k++ )
				if( i != j )
					fd += pow( PresjekStud[i][j] / 2 * fabs(a.TerminiIspita[i][k] - a.TerminiIspita[j][k]), 0.5 );

	return fd;
}

/*************************************************************************************/

void GenerateInitialPopulation( Gen Pop[] )
{
	for( int i=0; i<VEL_POP; i++ )
		Pop[i] = GenerateGene(BR_ROKOVA, BR_TERMINA);
}

Gen GenerateGene( int SelectedBitsNum, int Range )
{
	int		*a;
	Gen		gen;
	long	x;

	a = new int[SelectedBitsNum];
	for( int i=0; i<BR_ISPITA; i++ )
	{
		SelectRandomNumbers(a,SelectedBitsNum,0,Range-1);

		x = 0;
		for( int j=0; j<SelectedBitsNum; j++ )
		{
			x = SetBit(x, a[j]);
			gen.TerminiIspita[i][j] = a[j];
		}

		gen.Cromosom[i] = x;
	}

	delete []a;
	return gen;
}

Gen Krizaj( Gen a, Gen b )
{
	Gen		res;
	int		bitnum, j, num;

	for( int i=0; i<BR_ISPITA; i++ )
	{
		res.Cromosom[i] = a.Cromosom[i] & b.Cromosom[i];
	
		// odredi broj bitova u rezultirajuæem kromosomu
		// ( zato da znamo koliko je bitova u oba kromosoma bilo na istom mjestu )
		bitnum = NumberOfBits(res.Cromosom[i]);
		
		if( bitnum < BR_ROKOVA )
		{
			int		arr[BR_ROKOVA];
			long	tmp;

			tmp = 1;
			num = 0;
			SelectRandomNumbers(arr, BR_ROKOVA-bitnum, 0, (BR_ROKOVA-bitnum) * 2 - 1);

			for( j=0; j<32; j++ )
			{
				// da li je taj bit postavljen u rezultirajuæem kromosomu tako da su ga imala oba roditelja
				if( (res.Cromosom[i] & tmp) && (a.Cromosom[i] & tmp) )
					;						// ako jest, ne radi ništa
				else
				{
					// ako nije, treba provjeriti da li je taj bit postavljen u jednom od roditelja
					if ( ( a.Cromosom[i] & tmp ) || ( b.Cromosom[i] & tmp ) )			// da li je postavljen u jednom od roditelj
					{
						// i ako jest, da li je to onaj po redu koji je odabran da ide u dijete
						if( InSet(arr, BR_ROKOVA-bitnum, num) )
							res.Cromosom[i] |= tmp;
						
						num++;
					}
				}
				tmp <<= 1;
			}
		}
		
		num=0;
		for( j=0; j<BR_TERMINA; j++ )
			if( IsBitSet(res.Cromosom[i],j) )
				res.TerminiIspita[i][num++] = j;
	}

	return res;
}

void Mutiraj( Gen Pop[] )
{
	int		i, j, RemoveBit;
	unsigned int	NoviTerminIspita;
	long	rnd;

	for( i=0; i<VEL_POP; i++ )
		for( j=0; j<BR_ISPITA; j++ )
		{
			rnd = rand() % 3000;
			if( rnd < BR_ROKOVA )
			{
				RemoveBit = Pop[i].TerminiIspita[j][rnd];
				Pop[i].Cromosom[j] = ClearBit(Pop[i].Cromosom[j], RemoveBit);

				// sada treba paziti da nam novogeneriran termin ispita nije jedan od veæ postojeæih
				do
				{
					NoviTerminIspita = rand() % BR_TERMINA;
				} while( IsBitSet(Pop[i].Cromosom[j], NoviTerminIspita) == true );

				Pop[i].TerminiIspita[j][rnd] = NoviTerminIspita;
				Pop[i].Cromosom[j] = SetBit(Pop[i].Cromosom[j], NoviTerminIspita);
			}
		}
}

/*************************************************************************************/

void PrintPopulation( Gen	Pop[] )
{
	int		i, j;

	for( i=0; i<BR_ISPITA; i++ )
	{
		printf("\n");
		for( j=0; j<BR_TERMINA; j++ )
			if( IsBitSet(Pop[0].Cromosom[i], j) )
				printf(" x ");
			else
				printf("   ");

		for( j=0; j<BR_ROKOVA; j++ )
			printf("  %d ", Pop[0].TerminiIspita[i][j] );
	}
}

void PrintConfig( Gen	Pop[] )
{
	int			i, j, k, ind_max, SelIspit=0;
	double	f, min, max, avg;
//	bool	bFlag;

	COORD	coord;
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition(hConsOut, coord);

	max = Func(Pop[0]);
	ind_max = 0;
	min = Func(Pop[0]);
	avg = Func(Pop[0]);
	for( i=1; i<VEL_POP; i++ )
	{
		f = Func(Pop[i]);
		avg += f;
		if( f > max )
		{
			max = f;
			ind_max = i;
		}
		if( f < min )
			min = f;
	}
	avg /= VEL_POP;

	printf("         |");
	for( j=0; j<BR_TERMINA; j++ )
		printf(" %2d", j+1 );
	printf("\n----------------------------------------------------------------------------------------------------");
	
	for( i=0; i<BR_ISPITA; i++ )
	{
		printf("\n PRED%02d  | ", i+1);
		printf("                                                                                                  ");
		for( j=0; j<BR_TERMINA; j++ )
		{

//			bFlag = false;
			
			for( k=0; k<BR_ROKOVA; k++ )
			{
				coord.X = 12 + Pop[ind_max].TerminiIspita[i][k] * 3;
				coord.Y = 2*i + 2;

				SetConsoleCursorPosition(hConsOut, coord);
				printf("*");
			}
		}
		if( i != SelIspit && PresjekStud[SelIspit][i] > 0 )
		{
			coord.X = 100;
			coord.Y = 2*i + 2;

			SetConsoleCursorPosition(hConsOut, coord);
			printf("  %d", PresjekStud[SelIspit][i] );
		}

		printf("\n----------------------------------------------------------------------------------------------------");
	}
	printf("\n                                                                                                            ");
	printf("\n                                                                                                            ");

	for( i=0; i<BR_ISPITA; i++ )
	{
		printf("\n");
		for( j=0; j<BR_ROKOVA; j++ )
			printf(" %5d ", Pop[ind_max].TerminiIspita[i][j]+1 );
	}
	
	printf("\n Max. funkcije dobrote = %lf", max);
	printf("\n Min. funkcije dobrote = %lf", min);
	printf("\n Prosj. funkcije dobrote = %lf", avg);
}


/*************************************************************************************/
//						Pomoæne funkcije
/*************************************************************************************/

long SetBit( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;
	
	return (a | x);
}

long ClearBit( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;
	x = ~x;
	
	return (a & x);
}

bool IsBitSet( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;

	if( a & x )
		return true;
	else
		return false;
}

int NumberOfBits( long a )
{
	int		res=0;
	long	tmp;

	tmp = 1;
	for( int i=0; i<32; i++ )
	{
		if ( a & tmp )
			res++;

		tmp <<= 1;
	}

	return res;
}

void SelectRandomNumbers( int a[], int num, int start, int end )
{
	int		i, j;
	bool	bAlreadyGenerated;
	
	for( i=0; i<num; i++ )
	{
		do
		{
			bAlreadyGenerated=false;
		
			a[i] = rand() % ( end-start + 1) + start;

			for( j=0; j<i; j++ )
				if( a[j] == a[i] )
					bAlreadyGenerated = true;
		}
		while( bAlreadyGenerated == true );
	}
}

bool InSet( int a[], int num, int br )
{
	for( int i=0; i<num; i++ )
		if( a[i] == br )
			return true;

	return false;
}
