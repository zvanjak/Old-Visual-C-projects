#ifndef	__IOPTROK_H
#define __IOPTROK_H

#pragma warning( disable : 4786 )

#include <map>
#include <string>
#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::multimap;
using std::map;
using	std::pair;
using std::make_pair;

/*****************************************************************************************/
/*****************************************************************************************/

typedef unsigned long RESULT;

#define		NO_ERROR								0

#define		ERR_STREAM_NOT_OPENED			1
#define		NO_FIRST_DELIMITER				2
#define		NO_SECOND_DELIMITER				3
#define		ERR_READING_EXAM_DATA			4
#define		ERR_READING_PRESJEK_DATA	5

// forward declaration
class		IspitDodPodaci;
class		Ispit;
class		SelectedProblemDescr;

struct ParSifraPresjek {
public:
	ParSifraPresjek( int inSifra = 1, int inPresjek = 0 ) { m_nSifra = inSifra; m_nPresjek = inPresjek; }

	int		m_nSifra;
	int		m_nPresjek;
};

typedef std::multimap<int,ParSifraPresjek>::iterator				MIter;
typedef std::multimap<int,ParSifraPresjek>::const_iterator	MConstIter;

//	Struktura koja sadrži dodatne podatke o odreðenom ispitu

class	IspitDodPodaci {
public:
	IspitDodPodaci();
	IspitDodPodaci( int	inSemestar, 
									int	inBrojStud,
									int	inSmjer,
									char inOpis,
									int	inGrupaPred );

	int		getSemestar()	const { return m_nSemestar; }
	int		getBrojStud()	const { return m_nBrojStud; }
	int		getSmjer()		const { return m_nSmjer; }
	char	getOpis()			const { return m_chOpis; }
	int		getGrupaPred()const { return m_nGrupaPred; }

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
	int			getSifra() const { return m_nSifra; }
	string	getNaziv() const { return m_strNaziv; }
	
	// kada tražimo semestar, broj studenata ..., moramo definirati na koji predmet 
	// ( na kojem smjeru i na kojoj godini ) se to odnosi
	int			getSemestar( int i=0 ) const ;
	int			getBrojStud( int i=0 ) const ;
	int			getSmjer( int i=0 ) const;
	char		getOpis( int i=0 ) const;
	int			getGrupaPred( int i=0 ) const;

	// za ovaj ispit, dodaje u vecDodPod podatke o novoj 'instanci' ispita 
	bool		addDodPodaci( IspitDodPodaci &dod );
	bool		addDodPodaci( int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );

	int		getBrojDodPod() const { return m_vecDodPod.size(); }
	const	IspitDodPodaci&	getDodPod( int j ) const;

	int			Print(FILE *fp);

private:
	int			m_nSifra;
	string	m_strNaziv;
	
	vector<IspitDodPodaci>	m_vecDodPod;
};


class	SelectedProblemDescr {
public:
	SelectedProblemDescr() {
		m_SemLow = 0;				m_SemUpp = 9;
		m_BrojStudLow = 0;	m_BrojStudUpp = 1000;
		strcpy(m_Opis, "OIHKD");
	}

	// vraæa TRUE ako je predmet sa tom šifrom dio modela, FALSE ako nije
	bool	IsPartOfModel( int Sifra, IspitDodPodaci	dodPod  );

	bool	setSemestarBounds( int Low, int Upp );
	bool	setBrojStudBounds( int Low, int Upp );
	bool	setOpis( char str[] );
	
	void	getSemestarBounds( int &Low, int &Upp );
	void	getBrojStudBounds( int &Low, int &Upp );
	void	getOpis( char str[] );

private:
	// granice za vrijednosti podataka o ispitu pomoæu kojih se odreðuje da li ulazi u model ili ne
	int		m_SemLow, m_SemUpp;
	int		m_BrojStudLow, m_BrojStudUpp;
	// string sadržava slova onih opisa koja sudjeluju u optimizaciji
	char	m_Opis[10];
};

class OptFuncParam {
public:
	OptFuncParam() {	dExponent = 0.5;
										dKaznaPodjeleNaPodrokove = 3000;
										dKaznaMinDist = 3000;
										dKaznaGrupaPred = 8000;
										dNagradaIstiDan = 10000;
										dAmpBlizineIspita = 5;
										dAmpPresjekaStud = 5;
										nMinDistance = 8;
										nMinPresjek = 20;
										nMaxBrojStudZaGrupuPred = 300;
										nMaxIspitaIstiDanNaIstomSmjeru = 2;
										dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru = 2000; }

	bool		PostaviParametre( double, double, double, double, double, double, double, int, int, int, int, double );

	double	GetExponent() { return dExponent; }
	double	GetKaznaPodjeleNaPodrokove() { return dKaznaPodjeleNaPodrokove; }
	double	GetNagradaIstiDan() { return dNagradaIstiDan; }
	double	GetKaznaZaMaxBrojStudZaGrupuPred() { return dKaznaGrupaPred; }
	double	GetKaznaMinDist() { return dKaznaMinDist; }
	double	GetAmpBlizineIspita() { return dAmpBlizineIspita; }
	double	GetAmpPresjekaStud() { return dAmpPresjekaStud; }
	
	int			GetMinDistance() { return nMinDistance; }
	int			GetMinPresjek() { return nMinPresjek; }
	int			GetMaxBrojStudZaGrupuPred() { return nMaxBrojStudZaGrupuPred; }
	int			GetMaxBrojIspitaIstiDanNaIstomSmjer() { return nMaxIspitaIstiDanNaIstomSmjeru; }
	double	GetKaznaPrekoracenjaMaxIspitaNaIstomSmjeru() { return 	dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru; }


private:
	double	dExponent;								// 0.5
	double	dKaznaPodjeleNaPodrokove;	// 100
	double	dNagradaIstiDan;					// 100
	double	dKaznaGrupaPred;					// 100
	double	dKaznaMinDist;						// 1000
	double	dAmpBlizineIspita;
	double	dAmpPresjekaStud;

	int			nMinDistance;							// 8
	int			nMinPresjek;
	int			nMaxBrojStudZaGrupuPred;	// 200
	int			nMaxIspitaIstiDanNaIstomSmjeru;
	double	dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru;
};

/*****************************************************************************************/
/*****************************************************************************************/

class IORDataSource {
public:
	virtual	~IORDataSource()=0;  // potreban nam je virtualni destruktor
	virtual	RESULT		ResetIterators() = 0;

	virtual	RESULT		GetNextExam(char *Name, char *Code) = 0;
	virtual	RESULT		GetNextExamData(char *Code, int *Sem, int*StudNum, int *Group, char *Desc, int *Smjer) = 0;
	virtual	RESULT		GetNextGroup(char *Name, int *Code) = 0;
	virtual	RESULT		GetNextPresjek(int *Code1, int *Code2, int *Num ) = 0;
	virtual	RESULT		GetNextSameDayExams(int *Code1, int *Code2) = 0;
};

/*****************************************************************************************/

class IIspitCollection {
public:
	virtual	bool	addIspit( int inSifra, char *inNaziv ) = 0;
	virtual	bool	addIspit( int inSifra, string inNaziv ) = 0;

	virtual	bool	addIspit( int inSifra, string inNaziv, IspitDodPodaci &inDodPodaci ) = 0;
	virtual	bool	addIspit( int inSifra, char *inNaziv, IspitDodPodaci &inDodPodaci ) = 0;

	virtual	bool	addIspit( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred ) = 0;
	virtual	bool	addIspit( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred ) = 0;

	// SAMO ZA DODAVANJE NOVIH INSTANCI   !!!!!
	virtual	bool	addIspit( int	inSifra, int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred ) = 0;

	virtual	const Ispit&	getIspitIndex( int index ) = 0;
	virtual	const	Ispit&	getIspitSifra( int sifra ) = 0;

	virtual	int		getBrojIspita() = 0;

	virtual	void	clearAllData() = 0;
};

/*****************************************************************************************/

class IPresjekCollection {
public:
	virtual	bool	setPresjek( int sifra1, int sifra2, int presjek ) = 0;
	virtual	bool	getPresjek( int sifra1, int sifra2, int *presjek ) const = 0;
	virtual	bool	getPresjekSifra( int sifra, std::pair<MConstIter,MConstIter>	&redak ) const = 0;

	virtual	void	clearAllData() = 0;
};

/*****************************************************************************************/

class IIstiDanCollection {
};

/*****************************************************************************************/

class IIstiIspitiCollection {
};

/*****************************************************************************************/
/*****************************************************************************************/

class	PresjekStudData : public IPresjekCollection {
public:
	PresjekStudData() {}

	///////////////////////////////////////////////////////////////////////////////////////*
	//	naslijeðeni interface
	bool	setPresjek( int sifra1, int sifra2, int presjek );
	bool	getPresjek( int sifra1, int sifra2, int *presjek ) const;
	
	//	vraæa iterator cijelog retka u kojem se nalaze podaci za danu šifru
	bool	getPresjekSifra( int sifra, std::pair<MConstIter,MConstIter>	&redak ) const;

	void	clearAllData();

	///////////////////////////////////////////////////////////////////////////////////////*
	//	dodatne funkcije

private:
	std::multimap<int, ParSifraPresjek> mmapPresjek;

};

class IspitData : public IIspitCollection {
public:
	IspitData() {}

	bool	addIspit( int inSifra, char *inNaziv );
	bool	addIspit( int inSifra, string inNaziv );

	bool	addIspit( int inSifra, string inNaziv, IspitDodPodaci &inDodPodaci );
	bool	addIspit( int inSifra, char *inNaziv, IspitDodPodaci &inDodPodaci );

	bool	addIspit( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );
	bool	addIspit( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred );

	bool	addIspit( int	inSifra, int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred );

	const Ispit&	getIspitIndex( int index );
	const	Ispit&	getIspitSifra( int sifra );

	int		getBrojIspita() { return vecIspit.size(); }
	void	clearAllData();

private:
	// dodaje predmet sa sifrom 'sifra' i indeksom 'index' u vektor 'vecSifraUIndex'
	bool	addSifraUIndex( int sifra, int index );

	int		findPredmet( int sifra );
	int		findPredmet( string naziv );
	int		findPredmet( char *naziv );

private:
	vector<Ispit>		vecIspit;

	// vecSifraUIndex[sif] nam daje index u vecIspiti ispita sa sifrom sif
	vector<int>			vecSifraUIndex;
};

class ProblemData {
public:
	ProblemData();

	//////////////////////////////////////////////////////////////////////////////////////////
	// dodaje predmet sa šifrom i danim nazivom
	bool	addPredmet( int inSifra, char *inNaziv ) { return pcollIspit->addIspit(inSifra, inNaziv); }
	bool	addPredmet( int inSifra, string inNaziv ) { return pcollIspit->addIspit(inSifra, inNaziv); }

	bool	addPredmet( int inSifra, char *inNaziv, IspitDodPodaci dodPod ) { return pcollIspit->addIspit(inSifra, inNaziv, dodPod); }
	bool	addPredmet( int inSifra, string inNaziv, IspitDodPodaci dodPod  ) { return pcollIspit->addIspit(inSifra, inNaziv, dodPod); }

	bool	addPredmet( int	inSifra, char	*inNaziv,	int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred ) {
						return pcollIspit->addIspit(inSifra, inNaziv, inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);	}
	bool	addPredmet( int	inSifra, string inNaziv, int	inSemestar, int	inBrojStud, int	inSmjer, char	inOpis,	int	inGrupaPred ) {
						return pcollIspit->addIspit(inSifra, inNaziv, inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);	}

	// SAMO ZA DODAVANJE NOVIH INSTANCI   !!!!!
	bool	addPredmet( int	inSifra, int	inSemestar, int	inBrojStud,	int	inSmjer, char	inOpis,	int	inGrupaPred ) {
						return pcollIspit->addIspit(inSifra, inSemestar, inBrojStud, inSmjer, inOpis, inGrupaPred);	}

	//////////////////////////////////////////////////////////////////////////////////////////
	bool	addPresjek( int sifra1, int sifra2, int presjek ) { return pcollPresjek->setPresjek(sifra1, sifra2, presjek); }

	//////////////////////////////////////////////////////////////////////////////////////////
	int		BrojIspita() { return pcollIspit->getBrojIspita(); }
//	void	Print(FILE *);
	bool	ClearAll();				// briše sve podatke

	//////////////////////////////////////////////////////////////////////////////////////////
	const Ispit&		getPredmetIndex( int i ) { return pcollIspit->getIspitIndex(i); }
	const Ispit&		getPredmetSifra( int sifra ) { return pcollIspit->getIspitSifra(sifra); }
	
	const IPresjekCollection&		getPresjek() { return *pcollPresjek; }

	bool	PostaviPodatkeModela( ProblemData	&model, SelectedProblemDescr	&modelDescr );

private:
	//	sadrži podatke o ispitima
	IIspitCollection			*pcollIspit;

	//	sadrži podatke o presjecima
	IPresjekCollection		*pcollPresjek;
	
	// podaci o ispitima koji moraju biti isti dan
	IIstiDanCollection		*pcollIstiDan;
	
	// podaci o istim ispitima, ali koji imaju razlièite šifre
	IIstiIspitiCollection	*pcollIstiIspiti;
};

#endif