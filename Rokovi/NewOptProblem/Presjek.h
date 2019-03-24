#ifndef _PRESJEK_STUD_DATA
#define _PRESJEK_STUD_DATA	1

#include <vector>

using namespace std;

struct ParSifraPresjek {
public:
	ParSifraPresjek( int inSifra = 1, int inPresjek = 0 ) { m_nSifra = inSifra; m_nPresjek = inPresjek; }

	int		m_nSifra;
	int		m_nPresjek;
};

class	PresjekStudData {
public:
	PresjekStudData();
	~PresjekStudData();

	bool		setPresjek( int sifra1, int sifra2, int presjek );
	int			getPresjek( int sifra1, int sifra2 );

	int			getSifraRetka( int red );
	int			getBrojRedaka() { return matPresjek.size(); }
	int			getBrojPresjeka( int red );

	ParSifraPresjek		getPresjekRedStup( int red, int stup );

	void		Print();
private:
	vector<int>			vecSifreRedaka;
	vector< vector<ParSifraPresjek> >		matPresjek;

	int		findSifra( int sifra );
	bool	addPresjek( int redak, int sifra2, int presjek );
};

#endif