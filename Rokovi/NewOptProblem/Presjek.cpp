#include "stdafx.h"
#include "Presjek.h"

PresjekStudData::PresjekStudData()
{
}

PresjekStudData::~PresjekStudData()
{
}

// Traži zadanu šifru u matrici presjeka 
// odnosno, provjerava da li postoji redak u kojem se nalaze presjeci predmeta sa tom šifrom
int	PresjekStudData::findSifra( int sifra )
{
	for( int i=0; i<vecSifreRedaka.size(); i++ )
		if( vecSifreRedaka[i] == sifra )
			return i;

	return -1;
}

bool PresjekStudData::addPresjek( int redak, int sifra2, int presjek )
{
	int			j, sz;
	bool		found;

	assert( redak >= 0 && redak < getBrojRedaka() );

	// sada æemo provjeriti da li u retku veæ postoji podatak o presjeku sa danim predmetom ( sifra2 )
	found = false;
	for( j=0; j<matPresjek[redak].size(); j++ )
		if( matPresjek[redak][j].m_nSifra == sifra2 ) {
			matPresjek[redak][j].m_nPresjek = presjek;			// jednostavno postavljamo novu vrijednost presjeka
			found = true;
		}
	
	// ako presjek ne postoji, onda æemo dodati novi element u taj redak
	if( found == false ) {
		sz = matPresjek[redak].size();
		matPresjek[redak].resize(sz+1);
		
		matPresjek[redak][sz].m_nSifra = sifra2;
		matPresjek[redak][sz].m_nPresjek = presjek;
	}

	return true;
}

bool	PresjekStudData::setPresjek( int sifra1, int sifra2, int presjek )
{
	int		sz;
	int		red1, red2;

	if( (red1 = findSifra(sifra1)) < 0 ) {		// ukoliko sifre1 nema vec u matrici presjek
		sz = matPresjek.size();
		matPresjek.resize(sz+1);			// onda treba poveæati broj redaka matrice

		vecSifreRedaka.resize(sz+1);
		vecSifreRedaka[sz] = sifra1;
		
		red1 = sz;								// i sada æemo presjeke sa tom šifrom stavljati u dodani redak
	}

	// sada isto to i za šifru drugog predmeta
	if( (red2 = findSifra(sifra2)) < 0 ) {
		sz = matPresjek.size();
		matPresjek.resize(sz+1);
		
		vecSifreRedaka.resize(sz+1);
		vecSifreRedaka[sz] = sifra2;

		red2 = sz;
	}

	addPresjek(red1, sifra2, presjek);
	addPresjek(red2, sifra1, presjek);
		
	return true;
}

int	PresjekStudData::getBrojPresjeka( int red )
{
	assert( red >= 0 && red < getBrojRedaka() );

	return matPresjek[red].size();
}

int	PresjekStudData::getPresjek( int sifra1, int sifra2 )
{
	int		redak;

	if( (redak = findSifra(sifra1)) < 0 )
		return 0;
	else {
		for( int j=0; j<matPresjek[redak].size(); j++ )
			if( matPresjek[redak][j].m_nSifra == sifra2 )
				return matPresjek[redak][j].m_nPresjek;

		return 0;
	}
}

int	 PresjekStudData::getSifraRetka( int red )
{
	assert( red >= 0 && red < getBrojRedaka() );

	return vecSifreRedaka[red];
}

ParSifraPresjek		PresjekStudData::getPresjekRedStup( int red, int stup )
{
	assert( red >= 0 && red < getBrojRedaka() && stup >= 0 && stup < getBrojPresjeka(red) );

	int		sif, presj;

	sif	  = matPresjek[red][stup].m_nSifra;
	presj = matPresjek[red][stup].m_nPresjek;

	return ParSifraPresjek( sif, presj );
}

void PresjekStudData::Print()
{
	int		i, j;

	for( i=0; i<matPresjek.size(); i++ ) {
		printf("\n  sifra=%3d   -  ", vecSifreRedaka[i] );
		for( j=0; j<matPresjek[i].size(); j++ ) {
			printf("  (%3d, %3d)  ", matPresjek[i][j].m_nSifra, matPresjek[i][j].m_nPresjek );
		}
	}
}