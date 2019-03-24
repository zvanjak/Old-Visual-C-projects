#include <vector>

using namespace std;

//	Struktura koja sadrži dodatne podatke o odreðenom ispitu
class	cIspitDodPodaci {
private:
	int		m_nSemestar;
	int		m_nBrojStud;
	int		m_nSmjer;
	char	m_chOpis;
	int		m_nGrupaPred;

public:
	cIspitDodPodaci();
	cIspitDodPodaci( int	inSemestar, 
									 int	inBrojStud,
									 int	inSmjer,
									 char inOpis,
									 int	inGrupaPred );

	int		getSemestar()	{ return m_nSemestar; }
	int		getBrojStud()	{ return m_nBrojStud; }
	int		getSmjer()		{ return m_nSmjer; }
	char	getOpis()			{ return m_chOpis; }
	int		getGrupaPred(){ return m_nGrupaPred; }
};

class cIspit {
private:
	int					m_nSifra;
	string			m_strNaziv;
	
	vector<cIspitDodPodaci>	m_vecDodPod;

public:
	int		GetSemestar( int i=0 ) { return m_vecDodPod[i].getSemestar(); }
};


class cProblemData {
	vector<cIspit>		vecPredmeti;
};
