#include "stdafx.h"

int Date::BrDana[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };

bool Prestupna( Date &d )
{
	if( d.god % 4 == 0 && d.god % 400 != 0 )
		return true;
	else
		return false;
}

// vraæa 1 ako je prvi datum veæi od drugoga, -1 ako je drugi veæi, ili 0 ako su jednaki
int	UsporediDatume( Date &d1, Date &d2 )
{
	if( d1.god > d2.god )
		return 1;
	else if( d1.god < d2.god )
		return -1;
	else if( d1.mj > d2.mj )
		return 1;
	else if( d1.mj < d2.mj )
		return -1;
	else if( d1.dan > d2.dan )
		return 1;
	else if( d1.dan < d2.dan )
		return -1;
	else
		return 0;
}

// vraæa broj dana koji je protekao od 1.1.1900 do dana 'd'
long	TransformDate( Date &d )
{
	int			i;
	long		ret = 0;

	// najprije zbroji dane iz tog mjeseca
	ret += d.dan;

	// zbroji dane iz mjesece prije toga ( od te godine )
	for( i=1; i<d.mj; i++ )
		ret += Date::BrDana[i];
	
	// ako se radi o prestupnoj godini, dodaj još jedan dan za 29.2.
	if( Prestupna(d) == true && d.mj > 2)
		ret += 1;

	// sada zbrajamo dane za sve godine koje su protekle izmeðu dva datuma
	ret += 365 * (d.god - 1900);

	// sada treba još izraèunati koliko je bilo prestupnih godina
	ret += (d.god - 1900) / 4;

	// ali, ukoliko nam je trenutna godina prestupna, onda zbog nje ne treba dodati 1, 
	// jer æe se to uraditi kod zbrajanja po mjesecima
	if( Prestupna(d) == true )
		ret -= 1;

	// i još samo jedan dan ukoliko smo u godinama 1901-... ( jer je i 1900. bila prestupna )
	// ( ali ne i ako smo u 1900, jer smo onda to veæ uraèunali kod zbrajanja mjeseci )
	if( d.god > 1900 )
		ret += 1;

	return ret;
}

int	RazlikaDana( Date &d1, Date &d2 )
{
	return abs( TransformDate(d1) - TransformDate(d2) );
}

Date::Dan	DanUTjednu( Date &d )
{
	switch( TransformDate(d) % 7 )
	{
		case 0 : return Date::SUB;
		case 1 : return Date::NED;
		case 2 : return Date::PON;
		case 3 : return Date::UTO;
		case 4 : return Date::SRI;
		case 5 : return Date::CET;
		case 6 : return Date::PET;
	}

	return Date::PON;
}

// za sada radi samo ukoliko se zbraja manje od 30 dana ( što je nama dosta )
Date	Date::operator+( int br_dana )
{
	Date		ret(dan,mj,god);

	if( dan + br_dana > BrDana[mj] )		// ukoliko æemo prijeæi u slijedeæi mjesec
	{
		ret.mj++;
		ret.dan = br_dana - ( BrDana[mj] - ret.dan );
	}
	else
		ret.dan += br_dana;

	return ret;
}

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

ModelParam::ModelParam()
{
	dateStartDate = Date(12,6,2000);
	dateEndDate = Date(12,7,2000);

	nBrIsp = 0;
	nBrRok = 3;
	nBrTerm = IzracunajBrojTermina();
	nBrDan = IzracunajBrojDana();

	Tip = LJETNI;

	vecOptIsp.resize(100);

	vecSifraUIndex.resize(700);
	matSumaPoGrupPred.resize(MAX_GRUPA);			// nema više od 40 grupa predmeta;

	PostaviGranicePodrokova();
}

bool ModelParam::PostaviDatume( Date start, Date end )
{
//	if( DanUTjednu(start) != Date::PON )
//		return false;
	dateStartDate = start;

//	if( DanUTjednu(end) != Date::PET )		// ova provjera je upitna, jer za neke rokove je srijeda zadnji termin za pismeni
//		assert(0);
	dateEndDate = end;

	nBrTerm = IzracunajBrojTermina();
	nBrDan = IzracunajBrojDana();

	for( int i=0; i<matSumaPoGrupPred.size(); i++ )
		matSumaPoGrupPred[i].resize(nBrDan+1);

	PostaviGranicePodrokova();

	return true;
}

bool	ModelParam::PostaviGranicePodrokova()
{
	int		nDanaPoPodroku;

	if( BrojRokova() != 0 )
		nDanaPoPodroku = BrojDana() / BrojRokova();
	else
	{
		assert(0);
		return false;
	}

	vecGraniceRokovaUDanima.resize(BrojRokova());
	vecGraniceRokovaUTerminima.resize(BrojRokova());

	vecGraniceRokovaUDanima[0].DonjaGranica = 0;
	vecGraniceRokovaUTerminima[0].DonjaGranica = 0;

	int a;
	for( int i=0; i<BrojRokova()-1; i++ )
	{
		a = vecGraniceRokovaUDanima[i].GornjaGranica = nDanaPoPodroku * (i + 1);
		a = vecGraniceRokovaUDanima[i+1].DonjaGranica = vecGraniceRokovaUDanima[i].GornjaGranica ;
	}
	vecGraniceRokovaUDanima[BrojRokova()-1].GornjaGranica = BrojDana();

	for( i=0; i<BrojRokova()-1; i++ )
	{
		a = vecGraniceRokovaUTerminima[i].GornjaGranica = DanUTermin(vecGraniceRokovaUDanima[i].GornjaGranica);
		a = vecGraniceRokovaUTerminima[i+1].DonjaGranica = vecGraniceRokovaUTerminima[i].GornjaGranica ;
	}
	vecGraniceRokovaUTerminima[BrojRokova()-1].GornjaGranica = BrojTermina();

/*
	for( i=0; i<BrojRokova(); i++ )
		printf("\n %d  -   %d", vecGraniceRokovaUDanima[i].DonjaGranica , vecGraniceRokovaUDanima[i].GornjaGranica );

	for( i=0; i<BrojRokova(); i++ )
		printf("\n %d  -   %d", vecGraniceRokovaUTerminima[i].DonjaGranica , vecGraniceRokovaUTerminima[i].GornjaGranica );
*/
	return true;
}

int	ModelParam::DanPocetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojRokova() )
		return vecGraniceRokovaUDanima[BrojRoka].DonjaGranica;
	else
		return -1;
}

int	ModelParam::DanZavrsetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojRokova() )
		return vecGraniceRokovaUDanima[BrojRoka].GornjaGranica;
	else
		return -1;
}

int	ModelParam::TerminPocetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojRokova() )
		return vecGraniceRokovaUTerminima[BrojRoka].DonjaGranica;
	else
		return -1;
}

int	ModelParam::TerminZavrsetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojRokova() )
		return vecGraniceRokovaUTerminima[BrojRoka].GornjaGranica;
	else
		return -1;
}


bool	ModelParam::PostaviIspite( vector<Ispit> vecSif, vector<Ispit> vecPopisPred, int nBroj, vector< vector<int> > matIstiDan )
{
	int		i,j, num=0, ind, broj;
	bool	bExist;
	
	if( vecOptIsp.size() < nBroj )
		vecOptIsp.resize(nBroj+1);

	// buduæi da u nastavnom programu ima istih ispita, sa istim šiframa a da se pojavljuju više puta
	// ( razlièiti semestri, razlièite grupe, razlièiti smjerovi )
	// Mi æemo u naš popis ispita za optimizaciju, svaku šifru staviti samo jednom, ali æemo u dodatne
	// varijable staviti i ostale podatke
	for( i=0; i<nBroj; i++ )
	{
		bExist = false;
		int	sf;
		
		sf = vecSif[i].m_nSifra;
		int	a = 1;

		for( j=0; j<num; j++ )
			if( vecOptIsp[j].Sif == vecSif[i].m_nSifra )
			{
				bExist = true;
				broj = j;
				break;
			}

		if( bExist == false )		// ako dosada taj predmet nismo stavljali u popis
		{
			vecOptIsp[num].Sif = vecSif[i].m_nSifra;
			vecOptIsp[num].vecDodPod.resize(1);

			vecOptIsp[num].vecDodPod[0].Smjer = vecSif[i].m_nSifraSmjera;
			vecOptIsp[num].vecDodPod[0].Grupa = vecSif[i].m_nGrupaPred;
			vecOptIsp[num].vecDodPod[0].Semestar = vecSif[i].m_nSemestar;
			vecOptIsp[num].vecDodPod[0].BrojStud = vecSif[i].m_nBrojStud;
			vecOptIsp[num].vecDodPod[0].Opis = vecSif[i].m_chOpis;

			vecSifraUIndex[vecSif[i].m_nSifra] = num;

			num++;
		}
		else			// ako smo predmet sa tom šifrom veæ dodali u model, onda æemo samo ubaciti dodatne podatke
		{
			int		sz = vecOptIsp[broj].vecDodPod.size();
			
			// rezerviramo mjesto za dodatne podatke
			vecOptIsp[broj].vecDodPod.resize(sz+1);

			vecOptIsp[broj].vecDodPod[sz].Smjer = vecSif[i].m_nSifraSmjera;
			vecOptIsp[broj].vecDodPod[sz].Grupa = vecSif[i].m_nGrupaPred;
			vecOptIsp[broj].vecDodPod[sz].Semestar = vecSif[i].m_nSemestar;
			vecOptIsp[broj].vecDodPod[sz].BrojStud = vecSif[i].m_nBrojStud;
			vecOptIsp[broj].vecDodPod[sz].Opis = vecSif[i].m_chOpis;
		}
	}

	nBrIsp = num;

	// sada treba još postaviti i ispite za koje bi bilo dobro da budu isti dan, ali samo one ubaciti
	// koji su dio opt. problema
	int		rownum=0, row_size;
	int		first=-1;
	int		second=-1;

	for( i=0; i<matIstiDan.size(); i++ )
	{
		first = -1;
		second = -1;
		for( j=0; j<matIstiDan[i].size(); j++ )
			if( IsPartOfOptProblem(matIstiDan[i][j]) )
			{
				if( first == -1 )		// to je prvi kojeg ubacujemo u redak ( neæemo ga ubacivati dok ne naðemo i drugoga )
					first = matIstiDan[i][j];
				else if( second == -1 )
				{
					// onda ubaci oba
					matIspitiIstiDan.resize(rownum+1);
					matIspitiIstiDan[rownum].resize(2);
					
					matIspitiIstiDan[rownum][0] = first;
					second = matIstiDan[i][j];
					matIspitiIstiDan[rownum][1] = second;

					row_size = 2;
					rownum++;
				}
				else	// ovo nam je znaèi veæ treæi ( ili n-ti ) kojeg ubacujemo u ovaj redak
				{
					matIspitiIstiDan[rownum-1].resize(row_size + 1);
					matIspitiIstiDan[rownum-1][row_size++] = matIstiDan[i][j];
				}
			}
	}

		//	printf("\n Broj opt ispita = %d", num );

	return true;
}

bool	ModelParam::PostaviPresjek( vector< vector< ParSifraPresjek > > &matP, int nRowNum, vector<int> &vecSifre, int MinPresjek )
{
	int			i, j, k, l, n;

	nBrPresj = 0;

	vecSifreUMatrici.resize(nBrIsp+1);
	matPresjek.resize(nBrIsp+1);

	for( i=0; i<nRowNum; i++ )
	{
		// najprije treba vidjeti da li je ispit èiji se presjeci nalaze u i-tom retku matrice dio problem
		for( j=0; j<nBrIsp; j++ )
			if( vecSifre[i] == vecOptIsp[j].Sif )
			{
				// jest
				vecSifreUMatrici[nBrPresj] = vecSifre[i];
				k = 0;
				n = 0;
				while( matP[i][k].m_nSifra != -1 )
				{
					// sada treba uzeti presjek samo sa onima koji su takoðer dio opt. problema
					for( l=0; l<nBrIsp; l++ )
					{
						if( matP[i][k].m_nSifra == vecOptIsp[l].Sif && matP[i][k].m_nPresjek > MinPresjek)
						{
							matPresjek[nBrPresj].resize(n+1);
							matPresjek[nBrPresj][n++] = matP[i][k];
						}
					}
					k++;
				}

				nBrPresj++;
				break;
			}
	}
	
	return true;
}

int	ModelParam::GetPresjek( int sif1, int sif2 )
{
	int			i, j;

	for( i=0; i<nBrPresj; i++ )
		if( vecSifreUMatrici[i] == sif1 )
		{
			for( j=0; j<matPresjek[i].size(); j++ )
				if( matPresjek[i][j].m_nSifra == sif2 )
					return matPresjek[i][j].m_nPresjek;

			return 0;
		}

	return 0;
}

bool ModelParam::PostaviParametre( int BrRok, TerminRoka Vrsta )
{
	nBrRok = BrRok;
	Tip = Vrsta;

	return true;
}

// pretpostaviti æemo da rokovi uvijek poèinju u ponedjeljak i završavaju u petak
int	ModelParam::IzracunajBrojTermina()
{
	int		br, br_tjedana;

	br = RazlikaDana(dateStartDate, dateEndDate) + 1;
	br_tjedana = br / 7;

	// br % 7 zato jer ako rok završava u petak, kod dijeljenja i množenja sa 7, tih pet dana se neæe uraèunati
	return (br_tjedana*5 + br % 7);
}

int	ModelParam::IzracunajBrojDana()
{
	return RazlikaDana(dateStartDate,dateEndDate) + 1;
}

void ModelParam::IspisiPresjek()
{
	int		i, j;

	for( i=0; i<nBrPresj; i++ )
	{
		printf("\n %3d ", vecSifreUMatrici[i] );
		j = 0;
		while( matPresjek[i][j].m_nSifra != -1 && j < matPresjek[i].size() )
		{
			printf(" (%d,%d) ", matPresjek[i][j].m_nSifra, matPresjek[i][j].m_nPresjek );
			j++;
		}
	}
}

bool	ModelParam::IsPartOfOptProblem( int sifra )
{
	for( int i=0; i<nBrIsp; i++ )
		if( vecOptIsp[i].Sif == sifra )
			return true;

	return false;
}


