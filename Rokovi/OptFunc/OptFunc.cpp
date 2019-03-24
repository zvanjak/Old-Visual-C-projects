// OptFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;

HANDLE hConsOut;

int main(int argc, char* argv[])
{
	int						i, num=0;
	Ispit					tmp;
	vector<int>		vecSif(300);
	OptProblem		o("predmet.txt", "nasprogram.txt", "presjek.txt", "IspitiIstiDan.txt");

	hConsOut = GetStdHandle(STD_OUTPUT_HANDLE);

	o.PostaviDatume(Date(12,6,2000), Date(12,7,2000));
	o.PostaviParametre(3, JESENSKI);

	for( i=0; i<o.vecPopisPred.size(); i++ )
	{
		tmp = o.vecPopisPred[i];
		if( tmp.m_chOpis == 'O' && ( tmp.m_nSemestar == 1 || tmp.m_nSemestar == 2 ) )
		{
			vecSif[num] = o.vecPopisPred[i].m_nSifra;
			num++;
		}
	}

	o.PostaviIspite(vecSif, num);
	o.PostaviPresjek();
	o.IspisiOptPredmete();

	srand(time(NULL));

//	o.IspisiPresjek2();
//	getch();
	
	o.ModPar.IspisiPresjek();
	getch();

//	o.Optimize();
	return 0;
}

void PrintConfig( OptProblem &o, vector<Gen *> Pop )
{
	int			i, j, k, ind_max, SelIspit=0;
	double	f, min, max, avg;
	FunkcijaCilja	ref;

//	bool	bFlag;

	COORD	coord;
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition(hConsOut, coord);

	max = o.Func(*Pop[0], ref);
	ind_max = 0;
	min = o.Func(*Pop[0], ref);
	avg = o.Func(*Pop[0], ref);
	for( i=1; i<o.GenPar.GetVelPop(); i++ )
	{
		f = o.Func(*Pop[i], ref);
		avg += f;
		if( f > max )
		{
			max = f;
			ind_max = i;
		}
		if( f < min )
			min = f;
	}
	avg /= o.GenPar.GetVelPop();

	printf("         |");
	for( j=0; j<o.ModPar.nBrDan; j++ )
		printf(" %2d", j+1 );
	printf("\n----------------------------------------------------------------------------------------------------");
	
	for( i=0; i<o.ModPar.nBrIsp; i++ )
	{
		printf("\n PRED%02d  | ", i+1);
		printf("                                                                                                  ");
		for( j=0; j<o.ModPar.nBrTerm; j++ )
		{

//			bFlag = false;
			
			for( k=0; k<o.ModPar.nBrRok; k++ )
			{
				coord.X = 12 + TerminUDan(Pop[ind_max]->TerminiIspita[i][k]) * 3;
				coord.Y = 2*i + 2;

				SetConsoleCursorPosition(hConsOut, coord);
				printf("*");
			}
		}
/*		if( i != SelIspit && PresjekStud[SelIspit][i] > 0 )
		{
			coord.X = 100;
			coord.Y = 2*i + 2;

			SetConsoleCursorPosition(hConsOut, coord);
			printf("  %d", PresjekStud[SelIspit][i] );
		}
*/
		printf("\n----------------------------------------------------------------------------------------------------");
	}
	printf("\n                                                                                                            ");
	printf("\n                                                                                                            ");

	for( i=0; i<o.ModPar.nBrIsp; i++ )
	{
		printf("\n");
		for( j=0; j<o.ModPar.nBrRok; j++ )
			printf(" %5d ", Pop[ind_max]->TerminiIspita[i][j]+1 );
	}
	
	printf("\n Max. funkcije dobrote = %lf", max);
	printf("\n Min. funkcije dobrote = %lf", min);
	printf("\n Prosj. funkcije dobrote = %lf", avg);
}
