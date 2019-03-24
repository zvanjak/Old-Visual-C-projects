// Data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#define MAX_PRED		648

class Predmet
{
public:
	Predmet(string ime, int sif_smjera, char opis, int sem, int grupa, int broj_stud )
	{
		m_strNaziv=ime;
		m_nSifSmjera=sif_smjera;
		m_nGrupa=grupa;
		m_nSem=sem;
		m_nBrojStud=broj_stud;
		m_chOpis=opis;
	};
	Predmet( const Predmet& copy )
	{
		m_strNaziv=copy.m_strNaziv;
		m_nSifSmjera=copy.m_nSifSmjera;
		m_nGrupa=copy.m_nGrupa;
		m_nSem=copy.m_nSem;
		m_nBrojStud=copy.m_nBrojStud;
		m_chOpis=copy.m_chOpis;
	};

public:
	string	m_strNaziv;
	int			m_nSifSmjera;
	int			m_nGrupa;
	int			m_nSem;
	int			m_nBrojStud;
	char		m_chOpis;

	int			operator<( const Predmet& b) const;
};

int UcitajPredmete();
int UcitajNastavniProgram();
int	UcitajPresjek();
int	NadjiPredmeteSaViseStudenata( int nMinStud, int *pSifPred );

bool		arrPredPostoji[MAX_PRED];
int			arrSifraSmjera[MAX_PRED];
char		arrOpis[MAX_PRED];
int			arrSemestar[MAX_PRED];
int			arrGrupaPred[MAX_PRED];
int			arrBrojStud[MAX_PRED];

string	arrNaziviPred[MAX_PRED];

list<string>	listPredmeti;
list<Predmet> listPred;

int			matPresjek[MAX_PRED][MAX_PRED];


int	Predmet::operator<( const Predmet& b) const
{
	return m_strNaziv.compare(b.m_strNaziv);
}

ostream& operator<<( ostream& s, Predmet& b)
{
	s.width(70);
	s << b.m_strNaziv;
	return s << "  " << b.m_nSifSmjera << "  " << b.m_nSem << "  " << b.m_chOpis << "   " << b.m_nBrojStud << endl;
}

int main(int argc, char* argv[])
{
	int		i, j, num, dod_uvj_num=0;
	int		arrSif[300];

	UcitajPredmete();
	UcitajNastavniProgram();
	UcitajPresjek();

	listPred.clear();
	for( i=1; i<MAX_PRED; i++ )
		listPred.push_back(Predmet(arrNaziviPred[i], arrSifraSmjera[i], arrOpis[i], arrSemestar[i], arrGrupaPred[i], arrBrojStud[i]) );

	listPred.sort();

	num = 0;
	list<Predmet>::iterator start=listPred.begin();
	while( start != listPred.end() )
	{
		cout << *start;
		start++;
		num++;
		if( num == 50 )
		{
			getch();
			num=0;
		}
	}

	getch();

	num = NadjiPredmeteSaViseStudenata( 50, arrSif );
	for( i=0; i<num; i++ )
	{
		if( arrSemestar[arrSif[i]] == 5 || arrSemestar[arrSif[i]] == 6 )
		{
			cout.width(70);
			cout << arrNaziviPred[arrSif[i]];
			cout << "  " << arrSif[i] << "  " << arrSemestar[arrSif[i]] << "  " << arrOpis[arrSif[i]] << "   " << arrBrojStud[arrSif[i]] << endl;

			dod_uvj_num++;
		}
	}
	printf("\n Broj predmeta = %d, Uz dodatni uvjet = %d", num, dod_uvj_num ); 
	getch();
	
	for( i=0; i<num; i++ )
	{
		if( arrSemestar[arrSif[i]] == 5 || arrSemestar[arrSif[i]] == 6 )
		{
			printf("\n");
			for( j=0; j<num; j++ )
			{
				if( arrSemestar[arrSif[j]] == 5 || arrSemestar[arrSif[j]] == 6 )
				{
					printf(" %3d ", matPresjek[arrSif[i]][arrSif[j]] );
				}
			}
		}
	}

	return 0;
}

int UcitajPredmete()
{
	FILE	*fp;
	char	buff[150], chSifra[10], chIme[100];
	char	*pDelimiter, *pNewBuff;
	int		nSifra;

	if( (fp = fopen("predmet.txt", "r")) == NULL )
	{
		puts("Nisam otvorio datoteku predmet.txt");
		return 1;
	}

	for( int i=0; i<MAX_PRED; i++ )
		arrPredPostoji[i] = false;

	while( fgets(buff, 150, fp) )
	{
		pDelimiter = strchr(buff, '#');

		if( pDelimiter != NULL )
		{
			memcpy( chSifra, buff, pDelimiter-buff );
			
			chSifra[pDelimiter-buff] = '\0';
			nSifra = atoi(chSifra);
		}
		else
		{
			puts("Greska kod ucitavanja - nisam nasao prvi delimiter !!!");
			return 2;
		}
		
		pNewBuff = pDelimiter + 1;
		pDelimiter = strchr(pNewBuff, '#');
		if( pDelimiter != NULL )
		{
			strcpy( chIme, pNewBuff);
			chIme[pDelimiter - pNewBuff] = '\0';

			arrNaziviPred[nSifra] = chIme;
/*		
			string	addList;

			addList += "            ";
			addList += string(chSifra);
			listPredmeti.push_front(addList);
*/
		}
		else
		{
			puts("Greska kod ucitavanja - nisam nasao drugi delimiter !!!");
			return 3;
		}
	}
/*
	listPredmeti.sort();
	int		num=0;

	list<string>::iterator start=listPredmeti.begin();
	while( start != listPredmeti.end() )
	{
		cout << *start << endl;
		start++;
		num++;
		if( num == 50 )
		{
			getch();
			num=0;
		}
	}
*/

	fclose(fp);
	return 0;
}

int UcitajNastavniProgram()
{
	FILE	*fp;
	int		sif_pred, sif_smj, sem, gr_pred, br_stud;
	char	opis;

	if( (fp = fopen("nasprogram.txt", "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku nasprogram.txt");
		return 1;
	}

	while( fscanf(fp, "%d#%d#%c#%d#%d#%d#", &sif_pred, &sif_smj, &opis, &sem, &gr_pred, &br_stud) == 6 )
	{
		arrSifraSmjera[sif_pred] = sif_smj;
		arrOpis[sif_pred] = opis;
		arrSemestar[sif_pred] = sem;
		arrGrupaPred[sif_pred] = gr_pred;
		arrBrojStud[sif_pred] = br_stud;

		arrPredPostoji[sif_pred] = true;
	}

	fclose(fp);
	return 0;
}

int	UcitajPresjek()
{
	FILE	*fp;
	int		sif_pred1, sif_pred2, presjek;

	if( (fp = fopen("presjek.txt", "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku presjek.txt");
		return 1;
	}

	for( int i=0; i<MAX_PRED; i++ )
		for( int j=0; j<MAX_PRED; j++ )
			matPresjek[i][j] = 0;

	while( fscanf(fp, "%d#%d#%d#", &sif_pred1, &sif_pred2, &presjek) == 3 )
	{
		// treba se pobrinuti da to bude simetrièna matrica
		matPresjek[sif_pred1][sif_pred2] = presjek;
		matPresjek[sif_pred2][sif_pred1] = presjek;
	}


	fclose(fp);
	return 0;
}

int	NadjiPredmeteSaViseStudenata( int nMinStud, int *pSifPred )
{
	int		num = 0;

	for( int i=0; i<MAX_PRED; i++ )
		if( arrBrojStud[i] > nMinStud && arrPredPostoji[i] == true )
		{
			pSifPred[num++] = i;
		}

	return num;
}