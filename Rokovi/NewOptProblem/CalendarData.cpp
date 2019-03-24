#include "stdafx.h"
#include <assert.h>

#include "CalendarData.h"

CalendarData::CalendarData() 
{	
	dateStartDate = Date(12,6,2000);
	dateEndDate = Date(12,7,2000);
	m_nBrPodrok = 3;
	m_nBrTerm = 23;
}

CalendarData::CalendarData( Date inStartDate, Date inEndDate, int inBrPodrok )
{
	setDate(inStartDate, inEndDate);
	setBrojPodrokova(inBrPodrok);

	m_nBrTerm = calcBrojTermina();
}

bool	CalendarData::setDate( Date start, Date end )
{
	if( start < end ) {
		dateStartDate = start;
		dateEndDate = end;
		
		return true;
	} 
	else
		return false;
}

bool	CalendarData::setBrojPodrokova( int brPodrokova )
{
	assert( brPodrokova > 0 );

	m_nBrPodrok = brPodrokova;
	return true;
}

int	CalendarData::calcBrojTermina()
{
	// kasnije æe trebati uzeti u obzir i praznike, odnosno one datume koji su iskljuèeni
	int		d1, d2;

	d1 = TransformDate(dateStartDate);
	d2 = TransformDate(dateEndDate);

	return abs(d2-d1);
}

/****************************************************************************************/

bool	CalendarData::calcGranicePodrokova()
{
	int		nDanaPoPodroku;

	if( BrojPodrokova() != 0 )
		nDanaPoPodroku = BrojDana() / BrojPodrokova();
	else
	{
		assert(0);
		return false;
	}

	vecGraniceRokovaUDanima.resize(BrojPodrokova());
	vecGraniceRokovaUTerminima.resize(BrojPodrokova());

	vecGraniceRokovaUDanima[0].DonjaGranica = 0;
	vecGraniceRokovaUTerminima[0].DonjaGranica = 0;

	int a;
	for( int i=0; i<BrojPodrokova()-1; i++ )
	{
		a = vecGraniceRokovaUDanima[i].GornjaGranica = nDanaPoPodroku * (i + 1);
		a = vecGraniceRokovaUDanima[i+1].DonjaGranica = vecGraniceRokovaUDanima[i].GornjaGranica ;
	}
	vecGraniceRokovaUDanima[BrojPodrokova()-1].GornjaGranica = BrojDana();

	for( i=0; i<BrojPodrokova()-1; i++ )
	{
		a = vecGraniceRokovaUTerminima[i].GornjaGranica = DanUTermin(vecGraniceRokovaUDanima[i].GornjaGranica);
		a = vecGraniceRokovaUTerminima[i+1].DonjaGranica = vecGraniceRokovaUTerminima[i].GornjaGranica ;
	}
	vecGraniceRokovaUTerminima[BrojPodrokova()-1].GornjaGranica = BrojTermina();

/*
	for( i=0; i<BrojPodrokova(); i++ )
		printf("\n %d  -   %d", vecGraniceRokovaUDanima[i].DonjaGranica , vecGraniceRokovaUDanima[i].GornjaGranica );

	for( i=0; i<BrojPodrokova(); i++ )
		printf("\n %d  -   %d", vecGraniceRokovaUTerminima[i].DonjaGranica , vecGraniceRokovaUTerminima[i].GornjaGranica );
*/
	return true;
}

int	CalendarData::DanPocetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojPodrokova() )
		return vecGraniceRokovaUDanima[BrojRoka].DonjaGranica;
	else
		return -1;
}

int	CalendarData::DanZavrsetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojPodrokova() )
		return vecGraniceRokovaUDanima[BrojRoka].GornjaGranica;
	else
		return -1;
}

int	CalendarData::TerminPocetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojPodrokova() )
		return vecGraniceRokovaUTerminima[BrojRoka].DonjaGranica;
	else
		return -1;
}

int	CalendarData::TerminZavrsetkaPodroka( int BrojRoka )
{
	if( BrojRoka >= 0 && BrojRoka < BrojPodrokova() )
		return vecGraniceRokovaUTerminima[BrojRoka].GornjaGranica;
	else
		return -1;
}


/****************************************************************************************/

int		CalendarData::Dist( int term1, int term2 )
{
	int		d1, d2;

	d1 = TerminUDan(term1);
	d2 = TerminUDan(term2);

	return abs(d2-d1);
}

int		CalendarData::TerminUDan( int term )
{
	int	dan = ((term) / 5) * 7 + (term % 5) ;
	
	return dan;
}

int		CalendarData::DanUTermin( int dan )
{
	if( (dan+1) % 7 == 0 )
			return ((dan + 1) / 7) * 5;
	else if( (dan+1) % 7 == 6 )
			return ((dan + 2) / 7) * 5;
	else
		return (dan / 7) * 5 + ((dan) % 7);
}

bool	CalendarData::IsVikend( int dan )
{
	if( dan % 7 == 0 || (dan+1) % 7 == 0)
		return true;
	else
		return false;
}


int		Dist( int term1, int term2 )
{
	int		d1, d2;

	d1 = TerminUDan(term1);
	d2 = TerminUDan(term2);

	return abs(d2-d1);
}

/*
		Termini kreæu od 0, u slijedeæem obliku
				0 - PON
				1 - UTO
				2 - SRI
				3 - ÆET
				4 - PET
				5 - PON
*/
int		TerminUDan( int term )
{
	int	dan;

	dan = ((term) / 5) * 7 + (term % 5) ;
	
	return dan;
}

// NAPOMENA : funkcija daje krive rezultate ukoliko se traži termin koji odgovara suboti ili nedjelji
//   modifikacija : ukoliko se traži termin koji odgovara suboti ili nedjelju, funkcija vraæa termin od ponedjeljka
/*
		Dani poèinju s brojenjem od 0 :
				0 - PON
				1 - UTO
				...
				5 - SUB
				6 - NED
				7 - PON
				...
*/
int		DanUTermin( int dan )
{
	if( (dan+1) % 7 == 0 )
			return ((dan + 1) / 7) * 5;
	else if( (dan+1) % 7 == 6 )
			return ((dan + 2) / 7) * 5;
	else
		return (dan / 7) * 5 + ((dan) % 7);
}

bool IsVikend( int dan )
{
	if( dan % 7 == 0 || (dan+1) % 7 == 0)
		return true;
	else
		return false;
}
