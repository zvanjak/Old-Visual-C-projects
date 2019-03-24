#include "stdafx.h"
#include "ProblemData.h"

/********************************************************************************************/
/*		IMPLEMENTACIJA razreda IspitDodPodaci																									*/
/********************************************************************************************/

IspitDodPodaci::IspitDodPodaci() {
	m_nSemestar = 0;
	m_nBrojStud = 0;
	m_nGrupaPred = 0;
	m_chOpis = ' ';
	m_nSmjer = 0;
}

IspitDodPodaci::IspitDodPodaci( int	inSemestar, 
																int	inBrojStud,
																int	inSmjer,
																char inOpis,
																int	inGrupaPred ) {
	m_nSemestar = inSemestar;
	m_nBrojStud = inBrojStud;
	m_nGrupaPred = inGrupaPred;
	m_chOpis = inOpis;
	m_nSmjer = inSmjer;
}

/********************************************************************************************/
/********************************************************************************************/

Ispit::Ispit() {
}

Ispit::Ispit( int inSifra, char *inNaziv )
{
	m_nSifra = inSifra;
	m_strNaziv = string(inNaziv);
}

Ispit::Ispit( int inSifra, string inNaziv )
{
	m_nSifra = inSifra;
	m_strNaziv = inNaziv;
}

Ispit::Ispit( int inSifra, string inNaziv, IspitDodPodaci &inDodPodaci )
{
	m_nSifra = inSifra;
	m_strNaziv = inNaziv;

	m_vecDodPod.resize(1);
	m_vecDodPod[0] = inDodPodaci;
}

Ispit::Ispit( int inSifra, char *inNaziv, IspitDodPodaci &inDodPodaci )
{
	m_nSifra = inSifra;
	m_strNaziv = string(inNaziv);

	m_vecDodPod.resize(1);
	m_vecDodPod[0] = inDodPodaci;
}

Ispit::Ispit( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	m_nSifra = inSifra;
	m_strNaziv = string(inNaziv);

	m_vecDodPod.resize(1);
	m_vecDodPod[0] = IspitDodPodaci(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
}

Ispit::Ispit( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	m_nSifra = inSifra;
	m_strNaziv = inNaziv;

	m_vecDodPod.resize(1);
	m_vecDodPod[0] = IspitDodPodaci(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
}

/********************************************************************************************/

int	Ispit::getSemestar( int i )
{
	if( i < m_vecDodPod.size() )
		return m_vecDodPod[i].getSemestar();
	else
		return -1;
}

int	Ispit::getBrojStud( int i )
{
	if( i < m_vecDodPod.size() )
		return m_vecDodPod[i].getBrojStud();
	else
		return -1;
}

int	Ispit::getSmjer( int i )
{
	if( i < m_vecDodPod.size() )
		return m_vecDodPod[i].getSmjer();
	else
		return -1;
}

char	Ispit::getOpis( int i )
{
	if( i < m_vecDodPod.size() )
		return m_vecDodPod[i].getOpis();
	else
		return ' ';
}

int	Ispit::getGrupaPred( int i )
{
	if( i < m_vecDodPod.size() )
		return m_vecDodPod[i].getGrupaPred();
	else
		return -1;
}

bool	Ispit::addDodPodaci( IspitDodPodaci &dod )
{
	bool		found = false;

	// najprije æemo provjeriti da li smo takve dodatne podatke veæ ubacili za ovaj ispit
	for( int i=0; i<m_vecDodPod.size(); i++ )
		if( m_vecDodPod[i] == dod )
			found = true;
	
	if( found == false ) {
		int		sz;

		sz = m_vecDodPod.size();
		m_vecDodPod.resize(sz+1);
		m_vecDodPod[sz] = dod;

		return true;
	}
	else 
		return false;

}

bool	Ispit::addDodPodaci( int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	bool		found;;
	IspitDodPodaci	temp(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
	
	// najprije æemo provjeriti da li smo takve dodatne podatke veæ ubacili za ovaj ispit
	found = false;
	for( int i=0; i<m_vecDodPod.size(); i++ )
		if( m_vecDodPod[i] == temp )
			found = true;
	
	if( found == false ) {
		int		sz;

		sz = m_vecDodPod.size();
		m_vecDodPod.resize(sz+1);
		m_vecDodPod[sz] = temp;

		return true;
	}
	else
		return false;
}

IspitDodPodaci	Ispit::getDodPod( int j )
{
	assert( j >= 0 && j < m_vecDodPod.size() );

	if( j >= 0 && j < m_vecDodPod.size() ) {
		return m_vecDodPod[j];
	}
	else
		return IspitDodPodaci();
}

int	Ispit::Print()
{
	int		brRed = 1;

	printf("\n%3d %-30.30s", m_nSifra, m_strNaziv.c_str() );
	
	if( m_vecDodPod.size() > 0 ) {
		printf("sem - %1d   broj.stud - %3d   smjer - %2d    opis - %c    grupa - %2d", getSemestar(0), getBrojStud(0), getSmjer(0),getOpis(0), getGrupaPred(0) );
		brRed++;
	}
	
	for( int i=1; i<m_vecDodPod.size(); i++ ) {
		printf("\n%34.34s", " ");
		printf("sem - %1d   broj.stud - %3d   smjer - %2d    opis - %c    grupa - %2d", getSemestar(i), getBrojStud(i), getSmjer(i), getOpis(i), getGrupaPred(i) );
		brRed++;
	}
	return brRed;
}

/********************************************************************************************/
/********************************************************************************************/

ProblemData::ProblemData()
{
}

int		ProblemData::findPredmet( int sifra )
{
	for( int i=0; i<vecPredmeti.size(); i++ )
		if( vecPredmeti[i].getSifra() == sifra )
			return i;

	return -1;
}

int		ProblemData::findPredmet( string naziv )
{
	for( int i=0; i<vecPredmeti.size(); i++ )
		if( naziv.compare(vecPredmeti[i].getNaziv()) == 0 )
			return i;

	return -1;
}

int		ProblemData::findPredmet( char *naziv )
{
	for( int i=0; i<vecPredmeti.size(); i++ )
		if( strcmp(vecPredmeti[i].getNaziv().c_str(), naziv) == 0 )
			return i;

	return -1;
}

bool	ProblemData::IsPartOfProblem( int sifra )
{
	if( findPredmet(sifra) < 0 )
		return false;
	else
		return true;
}

/********************************************************************************************/

bool	ProblemData::addPredmet( int inSifra, char *inNaziv )
{
	// najprije provjeravamo da li je predmet s tom sifrom veæ ubaèen
	if( findPredmet(inSifra) < 0 ) {
		int		sz;

		sz = vecPredmeti.size();
		vecPredmeti.resize(sz+1);

		vecPredmeti[sz] = Ispit(inSifra, inNaziv);
		addSifraUIndex(inSifra, sz);
		
		return true;
	}
	else						// ako jest, onda ga ne stavljamo ponovo, veæ vraæamo FALSE
		return false;
}

bool	ProblemData::addPredmet( int inSifra, string inNaziv )
{
	if( findPredmet(inSifra) < 0 ) {
		int		sz;

		sz = vecPredmeti.size();
		vecPredmeti.resize(sz+1);

		vecPredmeti[sz] = Ispit(inSifra, inNaziv);
		addSifraUIndex(inSifra, sz);

		return true;
	}
	else
		return false;
}

bool	ProblemData::addPredmet( int inSifra, char *inNaziv, IspitDodPodaci dodPod )
{
	int		pos;
	bool	ret;

	pos = findPredmet(inSifra);
	if( pos < 0 ) {
		int		sz = vecPredmeti.size();

		vecPredmeti.resize(sz+1);
		vecPredmeti[sz] = Ispit(inSifra, inNaziv, dodPod);
		addSifraUIndex(inSifra, sz);

		ret = true;
	}
	else {	// ako veæ postoji takav predmet, onda æemo ubaciti podatke o dodatnoj instanci
		ret = vecPredmeti[pos].addDodPodaci(dodPod);
	}
	
	return ret;
}

bool	ProblemData::addPredmet( int inSifra, string inNaziv, IspitDodPodaci dodPod  )
{
	int		pos;
	bool	ret;

	pos = findPredmet(inSifra);
	if( pos < 0 ) {
		int		sz = vecPredmeti.size();

		vecPredmeti.resize(sz+1);
		vecPredmeti[sz] = Ispit(inSifra, inNaziv, dodPod);
		addSifraUIndex(inSifra, sz);

		ret = true;
	}
	else {	// ako veæ postoji takav predmet, onda æemo ubaciti podatke o dodatnoj instanci
		ret = vecPredmeti[pos].addDodPodaci(dodPod);
	}
	
	return ret;
}

bool	ProblemData::addPredmet( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	int		pos;
	bool	ret;

	pos = findPredmet(inSifra);
	if( pos < 0 ) {
		int		sz = vecPredmeti.size();

		vecPredmeti.resize(sz+1);
		vecPredmeti[sz] = Ispit(inSifra, inNaziv, inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
		addSifraUIndex(inSifra, sz);

		ret = true;
	}
	else {	// ako veæ postoji takav predmet, onda æemo ubaciti podatke o dodatnoj instanci
		ret = vecPredmeti[pos].addDodPodaci(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
	}
	
	return ret;
}

bool	ProblemData::addPredmet( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	int		pos;
	bool	ret;

	pos = findPredmet(inSifra);
	if( pos < 0 ) {
		int		sz;

		sz = vecPredmeti.size();
		vecPredmeti.resize(sz+1);

		vecPredmeti[sz] = Ispit(inSifra, inNaziv, inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
		addSifraUIndex(inSifra, sz);

		return true;
	}
	else {
		ret = vecPredmeti[pos].addDodPodaci(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
	}
	
	return ret;
}

/*
		Ova funkcija se može koristiti samo za dodavanje novih instanci veæ ubaèenim ispitima
		buduæi da se ne predaje ime ispita
*/
bool	ProblemData::addPredmet( int inSifra, int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred )
{
	int		pos;
	bool	ret;

	pos = findPredmet(inSifra);
	if( pos < 0 ) {
		return false;
	}
	else {
		ret = vecPredmeti[pos].addDodPodaci(inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);
	}
	
	return ret;
}

bool	ProblemData::addSifraUIndex( int sifra, int index )
{
	if( vecSifraUIndex.size() <= sifra )
		vecSifraUIndex.resize(sifra+1);

	vecSifraUIndex[sifra] = index;

	return true;
}

bool	ProblemData::addPresjek( int sifra1, int sifra2, int presjek )
{
	// najprije treba provjeriti da li su ta dva predmeta dio našeg problema
	if( IsPartOfProblem(sifra1) && IsPartOfProblem(sifra2) ) 
	{
		Presjek.setPresjek(sifra1, sifra2, presjek);
		return true;
	}
	else
		return false;
}

void	ProblemData::Print()
{
	int		i, j;
	int		brStranica=0, brRedaka=0;

	printf("\nPREDMETI\n");
	for( i=0; i<vecPredmeti.size(); i++ )
	{
		brRedaka += vecPredmeti[i].Print();
		if( brRedaka / 55 > brStranica ) {
			brStranica++;
			puts("\n Pritisnite tipku za nastavak");
			getch();
		}
	}
	puts("\n Pritisnite tipku za nastavak");
	getch();

	printf("\nPRESJECI\n");
//	Presjek.Print();
	
	puts("\n Pritisnite tipku za nastavak");
	getch();

	printf("\nISPITI ISTI DAN\n");
	for( i=0; i<matIspitiIstiDan.size(); i++ )
		for( j=0; j<matIspitiIstiDan[i].size(); j++ )
		{
			if( j == 0 )
				printf("\n");
			printf(" %3d ", matIspitiIstiDan[i][j] );
		}

	puts("\n Pritisnite tipku za nastavak");
	getch();

//	printf("\n vecs ize = %d,   %d, %d", vecSifraUIndex.size(), vecSifraUIndex[353], vecSifraUIndex[266] );
}
