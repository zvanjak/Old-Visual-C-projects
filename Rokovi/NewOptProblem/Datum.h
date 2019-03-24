class Date {
public:
	Date( int dd=0, int mm=0, int gg=0 ) { dan=dd; mj=mm; god=gg; }

	friend	int		UsporediDatume( Date &d1, Date &d2 );
	friend	int		RazlikaDana( Date &d1, Date &d2 );
	friend	long	TransformDate( Date &d );

	friend	bool	Prestupna( Date &d );

	Date		operator+( int br_dana );
	bool		operator<( Date &b );

	typedef enum { SUB=0, NED=1, PON=2, UTO=3, SRI=4, CET=5, PET=6 } Dan;
	friend	Dan		DanUTjednu( Date &d );

	static int BrDana[13]; // = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	int	dan,mj,god;
};


