#ifndef _CALENDARDATA_H
#define _CALENDARDATA_H  1

#include "Calendar.h"

#include <vector>

using namespace std;

class	Granice {
public:
	int		DonjaGranica;
	int		GornjaGranica;
};


class CalendarData {
public:
	CalendarData() {};
	CalendarData( Date start, Date end, int inBrPodrok );

	bool	setDate( Date start, Date end );
	bool	setBrojPodrokova( int brPodrokova );

	// raèuna broj termina izmeðu poèetnog i završnog datuma roka
	int		calcBrojTermina();

	int		BrojPodrokova() { return m_nBrPodrok; }
	int		BrojTermina() { return m_nBrTerm; }
	int		BrojDana() { return m_nBrDan; }

	int		DanPocetkaPodroka( int BrojRoka );
	int		DanZavrsetkaPodroka( int BrojRoka );
	int		TerminPocetkaPodroka( int BrojRoka );
	int		TerminZavrsetkaPodroka( int BrojRoka );

	int		Dist( int term1, int term2 );
	int		TerminUDan( int term );
	int		DanUTermin( int dan );
	bool	IsVikend( int dan );

private:
	bool	calcGranicePodrokova();

	// definira gornju granicu za i-ti rok, a vec[0] = 0
	//		- rokove brojimo od 1
	//		- gornja granica nije ukljuèena u rok : i-ti rok je u rasponu [ vec[i-1], vec[i] )
	vector< Granice >		vecGraniceRokovaUDanima;
	vector< Granice >		vecGraniceRokovaUTerminima;

	int		m_nBrTerm;
	int		m_nBrDan;
	int		m_nBrPodrok; 

	Date	dateStartDate;			// poèetni i završni datum roka
	Date	dateEndDate;
	
	//	na koji naèin æe se odrediti granice podrokova
	enum	{ EQUAL_DIST, USER_DEFINED } m_enGranice;
};


int		Dist( int term1, int term2 );
int		TerminUDan( int term );
int		DanUTermin( int dan );
bool	IsVikend( int dan );


#endif