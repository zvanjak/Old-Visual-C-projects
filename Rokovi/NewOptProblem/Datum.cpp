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

	// sada zbrajamo dane za sve godine koje su protekle izmeğu dva datuma
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

bool	Date::operator<( Date &b )
{
	if( god < b.god )
		return true;
	else if( god > b.god )
		return false;
	else {// ista godina
		if( mj < b.mj )
			return true;
		else if( mj > b.mj )
			return false;
		else {	// isti mjesec
			if( dan < b.dan )
				return true;
			else
				return false;
		}
	}
}
