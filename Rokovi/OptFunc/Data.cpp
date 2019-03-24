#include "stdafx.h"

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

			if( vecNaziviPred.size() < nSifra )
				vecNaziviPred.resize(nSifra*2);
			
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
	if( vecNaziviPred.size() > maxSifra+1 )
		vecNaziviPred.resize(maxSifra+1);

	fclose(fp);
	return maxSifra+1;		// +1 jer pretpostavljamo da šifre predmeta idu od 0 ( a idu od 1 )
}

int OptProblem::UcitajNastavniProgram( char *strFileName )
{
	FILE	*fp;
	int		sif_pred, sif_smj, sem, gr_pred, br_stud, num;
	char	opis;
//	vector<int>		vecSif(100);

	if( (fp = fopen(strFileName, "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku %s ", strFileName);
		return 1;
	}

	num = 0;
	for( int i=1; i<50; i++ )
	{
		rewind(fp);

		while( fscanf(fp, "%d#%d#%c#%d#%d#%d#", &sif_pred, &sif_smj, &opis, &sem, &gr_pred, &br_stud) == 6 )
		{
			if( gr_pred == i)
			{
				if( vecPopisPred.size() <= num )
					vecPopisPred.resize(num+1);
	//			if( vecSif.size() <= num )
	//				vecSif.resize(num+1);

				vecPopisPred[num].m_nSifra = sif_pred;
				vecPopisPred[num].m_nSifraSmjera = sif_smj;
				vecPopisPred[num].m_chOpis = opis;
				vecPopisPred[num].m_nSemestar = sem;
				vecPopisPred[num].m_nGrupaPred = gr_pred;
				vecPopisPred[num].m_nBrojStud = br_stud;

	//			vecSif[num] = sif_pred;

				num++;
			}
		}
	}

//	ModPar.PostaviIspite(vecSif, num);

//	printf("\n %d", num );
//	getch();

	int sz = vecPopisPred.size();
	
	fclose(fp);
	return num;
}

int	OptProblem::UcitajPresjek( char *strFileName )
{
	FILE	*fp;
	int		sif_pred1, sif_pred2, presjek;
	int		i, a, x, y;
	int		nIspitPresjekNum=0, size;
	int		In=0, Tot=0;

	if( (fp = fopen(strFileName, "r")) == NULL )
	{
		printf("Nisam uspio otvoriti datoteku %s ", strFileName);
		return 1;
	}

	vecPopisIndexUSifru.resize(nBrojPred+1);
	for( i=0; i<nBrojPred; i++ )
		vecPopisIndexUSifru[i] = -1;
	
	vecPopisSifraUIndex.resize(nUkupnoPredmeta+1);
	for( i=0; i<nUkupnoPredmeta; i++ )
		vecPopisSifraUIndex[i] = -1;

	while( fscanf(fp, "%d#%d#%d#", &sif_pred1, &sif_pred2, &presjek) == 3 )
	{
		// samo ako su oba predmeta iz presjeka ukljuèena u optimizaciju, stavi presjek studenata u matricu
		if( PartOfOptProblem(sif_pred1) && PartOfOptProblem(sif_pred2) )
		{
			// najprije treba utvrditi da li se za predmete sa uèitanim šiframa veæ unosio nekakav presjek
			if( (a = vecPopisSifraUIndex[sif_pred1]) > -1 )
				x = a;
			else	
			{
				x = vecPopisSifraUIndex[sif_pred1] = nIspitPresjekNum++;
				vecPopisIndexUSifru[x] = sif_pred1;

				if( matPresjekStud.size() <= nIspitPresjekNum )
				{
					// ukoliko je matrica postala premala, treba je poveæati
					size = matPresjekStud.size();

					matPresjekStud.resize(size*3/2);		// poveæaj velièinu za 50%
					for( int i=0; i<matPresjekStud.size(); i++ )
						matPresjekStud[i].resize(size*3/2);
				}
			}
			// isto to napraviti i za sifru drugog predmeta
			if( (a = vecPopisSifraUIndex[sif_pred2]) > -1 )
				y = a;
			else	
			{
				y = vecPopisSifraUIndex[sif_pred2] = nIspitPresjekNum++;
				vecPopisIndexUSifru[y] = sif_pred2;

				if( matPresjekStud.size() <= nIspitPresjekNum )
				{
					// ukoliko je matrica postala premala, treba je poveæati
					size = matPresjekStud.size();

					matPresjekStud.resize(size*3/2);		// poveæaj velièinu za 50%
					for( int i=0; i<matPresjekStud.size(); i++ )
						matPresjekStud[i].resize(size*3/2);
				}
			}
			// treba se pobrinuti da to bude simetrièna matrica
			matPresjekStud[x][y] = presjek;
			matPresjekStud[y][x] = presjek;

			Tot++;
			In += UbaciPresjek(sif_pred1, sif_pred2, presjek);
		}
	}

	fclose(fp);
	return 0;
}

int	OptProblem::UbaciPresjek( int sif1, int sif2, int pres )
{
	int		i, pos1=-1, pos2=-1;
	int		ind1, ind2, g1, g2;

	ind1 = IndexPredSaSifrom(sif1);
	ind2 = IndexPredSaSifrom(sif2);

	g1 = (vecPopisPred[ind1].m_nSemestar-1) / 2 + 1;
	g2 = (vecPopisPred[ind2].m_nSemestar-1) / 2 + 1;

	if( g1 == g2 )		// ubaciti æemo presjeke samo na istoj godini 
	{
		for( i=0; i<vecSifre.size(); i++ )
		{
			if( vecSifre[i] == sif1 )
				pos1 = i;
			if( vecSifre[i] == sif2 )
				pos2 = i;
		}

		if( pos1 == -1 )			// znaèi da nismo našli traženu šifru
			vecSifre[pos1=nUbacenoSifri++] = sif1;
		if( pos2 == -1 )			// znaèi da nismo našli traženu šifru
			vecSifre[pos2=nUbacenoSifri++] = sif2;

		for( i=0; i<matPresjek[pos1].size(); i++ )
			if( matPresjek[pos1][i].m_nSifra == -1 )			// našli smo prazno mjesto
			{
				matPresjek[pos1][i].m_nSifra = sif2;
				matPresjek[pos1][i].m_nPresjek = pres;
				break;
			}
		for( i=0; i<matPresjek[pos2].size(); i++ )
			if( matPresjek[pos2][i].m_nSifra == -1 )			// našli smo prazno mjesto
			{
				matPresjek[pos2][i].m_nSifra = sif1;
				matPresjek[pos2][i].m_nPresjek = pres;
				break;
			}
	
		return 1;
	}
	else
		return 0;
}

void OptProblem::UcitajPredmeteIstiDan( char *strFileName )
{
	FILE		*fp;
	int			size, row, n, sifra, len;
	char		buff[512];

	size = matIspitiIstiDan.size();

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
					matIspitiIstiDan.resize(size+1);
					size++;
				}
				
				matIspitiIstiDan[row].resize(n+1);
				matIspitiIstiDan[row][n++] = sifra;
			}
			row++;
		}
	}
}


void OptProblem::IspisiPredmete()
{
	int		i, br=1;

	printf("\n Ispisujem sve predmete \n");

	for( i=0; i<nUkupnoPredmeta; i++ )
	{
		cout.width(70);
		cout << vecNaziviPred[i] << endl;
//		cout << "  " << i << "  " << vecPopisPred[i].m_nSemestar << "  " << vecPopisPred[i].m_chOpis << "   " << vecPopisPred[i].m_nBrojStud<< endl;
		if( br % 50 == 0 )
			getch();
		br++;
	}
}

void OptProblem::IspisiPopisPred()
{
	int		i, br=1;

	printf("\n Ispisujem popis predmeta \n");

	for( i=0; i<nBrojPred; i++ )
	{
		cout.width(3);
		cout << i;
		cout.width(70);
		cout << vecNaziviPred[vecPopisPred[i].m_nSifra] << "  ";
		cout.width(3);
		cout << vecPopisPred[i].m_nSifra << "  " << vecPopisPred[i].m_nSemestar << "  " << vecPopisPred[i].m_chOpis << "   ";
		cout.width(3);
		cout << vecPopisPred[i].m_nSifraSmjera << "  ";
		cout.width(3);
		cout << vecPopisPred[i].m_nBrojStud<< endl;
		
		if( br % 50 == 0 )
			getch();
		br++;
	}
}

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
}