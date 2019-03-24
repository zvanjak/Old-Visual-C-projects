#include "stdafx.h"
#include "OptProblem.h"

bool	SelectedProblemDescr::IsPartOfModel( int Sifra, IspitDodPodaci	dodPod )
{
//	return true;

	if( dodPod.getSemestar() >= 1  && dodPod.getSemestar() <= 4  )
		return true;
	else
		return false;
}

int OptProblem::UcitajPredmete( char *strFileName )
{
	FILE	*fp;
	char	buff[150], chSifra[10], chIme[100];
	char	*pDelimiter, *pNewBuff;
	int		nSifra, maxSifra=-1;

	if( (fp = fopen(strFileName, "r")) == NULL )
	{
		printf("Nisam otvorio datoteku %s ", strFileName);
		return 1;
	}

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

			if( vecNaziviPred.size() <= nSifra )
				vecNaziviPred.resize(nSifra+1);
			
			vecNaziviPred[nSifra] = chIme;
			if( nSifra > maxSifra )
				maxSifra = nSifra;
		}
		else
		{
			puts("Greska kod ucitavanja - nisam nasao drugi delimiter !!!");
			return 3;
		}
	}

	fclose(fp);
	return maxSifra+1;		// +1 jer pretpostavljamo da šifre predmeta idu od 0 ( a idu od 1 )
}

int OptProblem::UcitajNastavniProgram( char *strFileName )
{
	FILE	*fp;
	int		sif_pred, sif_smj, sem, gr_pred, br_stud, num;
	char	opis;

	if( (fp = fopen(strFileName, "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku %s ", strFileName);
		return 1;
	}

	num = 0;
	rewind(fp);

	while( fscanf(fp, "%d#%d#%c#%d#%d#%d#", &sif_pred, &sif_smj, &opis, &sem, &gr_pred, &br_stud) == 6 )
	{
		// najprije dodajemo u popis predmeta šifru i naziv
		probData.addPredmet(sif_pred, vecNaziviPred[sif_pred] );

		// a sada æemo dodati i podatke o instanci predmeta
		probData.addPredmet(sif_pred, sem, br_stud, sif_smj, opis, gr_pred );
	}

	fclose(fp);
	return num;
}


int	OptProblem::UcitajPresjek( char *strFileName )
{
	FILE	*fp;
	int		sif_pred1, sif_pred2, presjek;

	if( (fp = fopen(strFileName, "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku %s ", strFileName);
		return 1;
	}

	while( fscanf(fp, "%d#%d#%d#", &sif_pred1, &sif_pred2, &presjek) == 3 )
		probData.addPresjek(sif_pred1, sif_pred2, presjek);

	fclose(fp);
	return 0;
}

void OptProblem::UcitajPredmeteIstiDan( char *strFileName )
{
	FILE		*fp;
	int			size, row, n, sifra, len;
	char		buff[512];

	size = probData.matIspitiIstiDan.size();

	if( (fp = fopen(strFileName, "r") ) != NULL )
	{
		row = 0;
		while( fgets(buff, 512, fp) != NULL )
		{
			n = 0;
			len = 0;
			while( sscanf(buff+len, "%d", &sifra) == 1 )
			{
				len += (int) log10(sifra) + 2;
				if( n == 0 )			// ako je to prvi ispit iz retka koji sadrži ispite zaisti dan
				{
					probData.matIspitiIstiDan.resize(size+1);
					size++;
				}
				
				probData.matIspitiIstiDan[row].resize(n+1);
				probData.matIspitiIstiDan[row][n++] = sifra;
			}
			row++;
		}
	}
}


void OptProblem::IspisiPredmete()
{
	int		i, br=1;

	cout << "Ispisujem sve predmete" << endl;

	for( i=0; i<vecNaziviPred.size(); i++ )
	{
		cout.width(70);
//		cout << vecNaziviPred[i] << endl;
		
		if( br % 50 == 0 )			// ako je ispunjen ekran, zaustavi ispis
			getch();
		br++;
	}
}

/*

void OptProblem::IspisiOptPredmete()
{
	int		i, sif, ind, br=1;

	printf("\n Ispisujem predmete za optimizaciju \n");

	for( i=0; i<ModPar.nBrIsp; i++ )
	{
		sif = ModPar.vecOptIsp[i].Sif;
		ind = IndexPredSaSifrom(sif);

		cout.width(3);
		cout << i;
		cout.width(70);
		cout << vecNaziviPred[vecPopisPred[ind].m_nSifra] << "  ";
		cout.width(3);
		cout << sif << "  " << vecPopisPred[ind].m_nSemestar << "  " << vecPopisPred[ind].m_chOpis << "   ";
		cout.width(3);
		cout << vecPopisPred[ind].m_nSifraSmjera << "  ";
		cout.width(3);
		cout << vecPopisPred[ind].m_nBrojStud<< endl;

		if( br % 50 == 0 )
			getch();
		br++;
	}
}

void OptProblem::IspisiPresjek()
{
	int		i, j;

	printf("       ");
	for( i=0; i<nBrojPred; i++ )
		printf(" %3d ", vecPopisIndexUSifru[i] );
	printf("\n---------------------------------------------------------------------------------------------------------");

	for( i=0; i<nBrojPred; i++ )
	{
		printf("\n %3d | ", vecPopisIndexUSifru[i] );
		for( j=0; j<nBrojPred; j++ )
			printf(" %3d ", matPresjekStud[i][j] );
	}
}

void OptProblem::IspisiPresjek2()
{
	int		i, j;

	for( i=0; i<nUbacenoSifri; i++ )
	{
		printf("\n %3d ", vecSifre[i] );
		j = 0;
		while( matPresjek[i][j].m_nSifra != -1 )
		{
			printf(" ( %d, %d ) ", matPresjek[i][j].m_nSifra, matPresjek[i][j].m_nPresjek );
			j++;
		}
	}
}*/