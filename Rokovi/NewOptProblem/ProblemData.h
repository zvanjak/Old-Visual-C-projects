#ifndef _PROBLEM_DATA
#define	_PROBLEM_DATA		1

#include "Presjek.h"

#include <iostream>
using namespace std;

/********************************************************************************************/
/********************************************************************************************/

//	Struktura koja sadrži dodatne podatke o odreðenom ispitu

class	IspitDodPodaci {
public:
	IspitDodPodaci();
	IspitDodPodaci( int	inSemestar, 
									int	inBrojStud,
									int	inSmjer,
									char inOpis,
									int	inGrupaPred );

	int		getSemestar()	{ return m_nSemestar; }
	int		getBrojStud()	{ return m_nBrojStud; }
	int		getSmjer()		{ return m_nSmjer; }
	char	getOpis()			{ return m_chOpis; }
	int		getGrupaPred(){ return m_nGrupaPred; }

	bool	operator==( IspitDodPodaci &b ) { return (m_nSemestar == b.getSemestar() &&
																									m_nBrojStud == b.getBrojStud() &&
																									m_nSmjer		== b.getSmjer() &&
																									m_chOpis		== b.getOpis() &&
																									m_nGrupaPred == b.getGrupaPred() ); }
private:
	int		m_nSemestar;
	int		m_nBrojStud;
	int		m_nSmjer;
	char	m_chOpis;
	int		m_nGrupaPred;
};

/********************************************************************************************/
/*					DEKLARACIJA	razreda	Ispit																												*/
/*	Sadrži podatke o ispitu																																	*/
/********************************************************************************************/

class Ispit {
public:
	// konstruktori
	Ispit();				// potreban je default konstruktor kada obavljamo resize vektora koji u sebi sadrži Ispit

	Ispit( int inSifra, char *inNaziv );
	Ispit( int inSifra, string inNaziv );

	Ispit( int inSifra, string inNaziv, IspitDodPodaci &inDodPodaci );
	Ispit( int inSifra, char *inNaziv, IspitDodPodaci &inDodPodaci );

	Ispit( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );
	Ispit( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred );

	// funkcije za pristup èlanovima
	int			getSifra() { return m_nSifra; }
	string	getNaziv() { return m_strNaziv; }
	
	// kada tražimo semestar, broj studenata ..., moramo definirati na koji predmet 
	// ( na kojem smjeru i na kojoj godini ) se to odnosi
	int			getSemestar( int i=0 );
	int			getBrojStud( int i=0 );
	int			getSmjer( int i=0 );
	char		getOpis( int i=0 );
	int			getGrupaPred( int i=0 );

	// za ovaj ispit, dodaje u vecDodPod podatke o novoj 'instanci' ispita 
	bool		addDodPodaci( IspitDodPodaci &dod );
	bool		addDodPodaci( int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );

	int							getBrojDodPod() { return m_vecDodPod.size(); }
	IspitDodPodaci	getDodPod( int j );

	int			Print();

private:
	int			m_nSifra;
	string	m_strNaziv;
	
	vector<IspitDodPodaci>	m_vecDodPod;
};


class ProblemData {
public:
	ProblemData();

	bool	addPredmet( int inSifra, char *inNaziv );
	bool	addPredmet( int inSifra, string inNaziv );

	bool	addPredmet( int inSifra, char *inNaziv, IspitDodPodaci dodPod );
	bool	addPredmet( int inSifra, string inNaziv, IspitDodPodaci dodPod  );

	bool	addPredmet( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );
	bool	addPredmet( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred );

	// SAMO ZA DODAVANJE NOVIH INSTANCI   !!!!!
	bool	addPredmet( int	inSifra, int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );

	bool	addPresjek( int sifra1, int sifra2, int presjek );

	int		BrojIspita() { return vecPredmeti.size(); }
	void	Print();

private:
	vector<Ispit>			vecPredmeti;
	PresjekStudData		Presjek;

	// koji ispiti moraju biti ispit dan ( po željama profesora )
	vector< vector<int> > matIspitiIstiDan;

	// vecSifraUIndex[sif] nam daje index u vecPredmeti predmeta sa sifrom sif
	vector<int>		vecSifraUIndex;
	// dodaje predmet sa sifrom 'sifra' i indeksom 'index' u vektor 'vecSifraUIndex'
	bool	addSifraUIndex( int sifra, int index );

	int		findPredmet( int sifra );
	int		findPredmet( string naziv );
	int		findPredmet( char *naziv );

	bool	IsPartOfProblem( int sifra );

	friend	class		OptProblem;
	friend	class		OptimizationData;
};


#endif