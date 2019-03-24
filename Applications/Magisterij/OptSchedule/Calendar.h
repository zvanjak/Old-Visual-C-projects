#if  !defined( __DATE_H )
#define	__DATE_H  1

class Date {
public:
	Date( int dd=0, int mm=0, int gg=0 ) { m_Day=dd; m_Month=mm; m_Year=gg; }

	Date		operator+( int DaysNum );
	bool		operator<( Date &b );
	bool		operator>=( Date &b ) { return !(*this<b); }
	bool		operator==( Date &b );

	int			Day() { return m_Day; }
	int			Month() { return m_Month; }
	int			Year() { return m_Year; }

	friend	int		CmpDate( Date &d1, Date &d2 );
	friend	int		DateDiff( Date &d1, Date &d2 );
	friend	long	TransformDate( Date &d );

	friend	bool	IsOverlapYear( Date &d );

	typedef enum { SAT=0, SUN=1, MON=2, TUE=3, WED=4, THU=5, FRI=6 } DayName;
	friend	DayName	DayInWeek( Date &d );

	static int DaysInMonth[13];
	
private:
	int	m_Day, m_Month, m_Year;
};

#endif

#if !defined(_CALENDAR_INTERVAL)
#define _CALENDAR_INTERVAL	1

#include "Interval.h"

static int	HolidayDay[9] =   { 1, 6, 1, 30, 22, 5, 15, 25, 26, };
static int	HolidayMonth[9] = { 1, 1, 5,  5,  6, 8,  8, 12, 12, };

class CalendarInterval : public Interval<Date> {
public:
	CalendarInterval() : Interval<Date>(Date(1,1,1970),Date(1,1,1971)) {}
	CalendarInterval(Date &a, Date &b) : Interval<Date>(a,b) {}

	int		TotalDaysInInterval();
	int		DaysInInterval( Date::DayName name );
	int		GetWorkDayNum();

	Date	GetStartDate() { return GetLB(); }
	Date	GetEndDate() { return GetUB(); }

	int		IntervalLenght();
};


#endif