#ifndef __MODEL_PAR_H
#define __MODEL_PAR_H		

#define	MAX_GRUPA		50

using namespace std;

typedef enum { ZIMSKI=0, PROLJETNI=1, LJETNI=2, JESENSKI=3, JESENSKI_IZV=4 } TerminRoka;


struct FunkcijaCilja{
	double	BlizinaIspita;
	double	KaznePrevelikeBlizine;
	double	PresjekIspita;
	double	KazneOdstupanjaOdPodrokova;
	double	ZeljeProfesora;
	double	KazneOpterecenjaNaGrupama;
	double	KaznePrekoracenjaMaxIspitaNaIstomSmjeru;
};

class Ispit {
public:
	Ispit() { m_nSifra=0; 
						m_nSifraSmjera=0; 
						m_chOpis=' '; 
						m_nSemestar=0; 
						m_nGrupaPred=0; 
						m_nBrojStud=0;}

	int		m_nSifra;
	int		m_nSifraSmjera;
	char	m_chOpis;
	int		m_nSemestar;
	int		m_nGrupaPred;
	int		m_nBrojStud;
};

class Date {
public:
	Date();
	Date( int dd, int mm, int gg ) { dan=dd; mj=mm; god=gg; }

	friend	int		UsporediDatume( Date &d1, Date &d2 );
	friend	int		RazlikaDana( Date &d1, Date &d2 );
	friend	long	TransformDate( Date &d );

	friend	bool	Prestupna( Date &d );

	Date		operator+( int br_dana );

	typedef enum { SUB=0, NED=1, PON=2, UTO=3, SRI=4, CET=5, PET=6 } Dan;
	friend	Dan		DanUTjednu( Date &d );

	static int BrDana[13]; // = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	int	dan,mj,god;
};


class		Zapis {
public:
	int			m_nSifraIspita;
	
	// datumi kada je ispit
	Date		m_arrDatZim[2];
	Date		m_arrDatProlj;
	Date		m_arrDatLjet[3];
	Date		m_arrDatJes[3];
	Date		m_arrDatJesIzv;

	// a ovdje æe biti redni broj dana u roku kada se održava ispit
	int			m_arrDanZim[2];
	int			m_arrDanProlj;
	int			m_arrDanLjet[3];
	int			m_arrDanJes[3];
	int			m_arrDanJesIzv;
};


class ParSifraPresjek {
public:
	ParSifraPresjek() { m_nSifra = -1; m_nPresjek = 0; }

	int		m_nSifra;
	int		m_nPresjek;
};

class ParBrStudBrIsp {
public:
	ParBrStudBrIsp() { m_nBrStud = 0; m_nBrIsp = 0; }

	int		m_nBrStud;
	int		m_nBrIsp;
};

class	Granice {
public:
	int		DonjaGranica;
	int		GornjaGranica;
};

class cDodPodaci {
public:
	int		Smjer;
	int		Semestar;
	int		BrojStud;
	int		Grupa;
	char	Opis;
};

class	IspPodaci {
public:
	int	Sif;
	vector<cDodPodaci>	vecDodPod;
};

class ModelParam {
public:
	ModelParam();			// default konstruktor

	bool	PostaviDatume( Date start, Date end );
	bool	PostaviIspite( vector<Ispit> vecSifreIspita, vector<Ispit> vecPopisPred, int nBroj, vector< vector<int> > matIstiDan );
	bool	PostaviPresjek( vector< vector< ParSifraPresjek > > &matP, int nRowNum, vector<int> &vecSifre, int MinPresjek );
	bool	PostaviParametre( int BrRok, TerminRoka Vrsta );

	void	IspisiPresjek();
	int		GetPresjek( int sif1, int sif2 );

	int		IzracunajBrojTermina();
	int		IzracunajBrojDana();

	bool	IsPartOfOptProblem( int sifra );

	int		BrojRokova() { return nBrRok; }
	int		BrojTermina() { return nBrTerm; }
	int		BrojIspita() { return nBrIsp; }
	int		BrojDana() { return nBrDan; }

	int		DanPocetkaPodroka( int BrojRoka );
	int		DanZavrsetkaPodroka( int BrojRoka );
	int		TerminPocetkaPodroka( int BrojRoka );
	int		TerminZavrsetkaPodroka( int BrojRoka );

private:
	bool	PostaviGranicePodrokova();

	// definira gornju granicu za i-ti rok, a vec[0] = 0
	//		- rokove borjimo od 1
	//		- gornja granica nije ukljuèena u rok : i-ti rok je u rasponu [ vec[i-1], vec[i] )
	vector< Granice >		vecGraniceRokovaUDanima;
	vector< Granice >		vecGraniceRokovaUTerminima;

public:
	Date	dateStartDate;			// poèetni i završni datum roka
	Date	dateEndDate;

	int					nBrIsp;
	vector<IspPodaci> vecOptIsp;		// šifre ispita èiji raspored optimiramo

	int					nBrPresj;
	vector< int >		vecSifreUMatrici;
	vector< vector< ParSifraPresjek > >	matPresjek;

	vector< vector<int> >		matIspitiIstiDan;

	int		nBrRok;
	int		nBrTerm;	// ova dva parametra se mogu izraèunati iz datuma poèetka i završetka
	int		nBrDan;

	TerminRoka		Tip;

	// pomoæni niz pomoæu kojega æemo brzo saznati indeks predmeta u nizu 'vecOptIsp' sa zadanom šifrom
	vector<int>		vecSifraUIndex;

	// u ovoj matrici æemo raèunati koliko u kojem danu koja grupa predmeta ima studenata na ispitu
	vector< vector<ParBrStudBrIsp> >   matSumaPoGrupPred;

	friend class OptProblem;
};


#endif