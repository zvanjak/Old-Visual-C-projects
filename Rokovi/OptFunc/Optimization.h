#include "ModelPar.h"

using namespace std;


class GenAlgParam {
public:
	GenAlgParam()	{ VEL_POP = 70;
									ITER_NUM = 500000;
									MUT_MODUL = 20000; }
	GenAlgParam( int VelPop, long IterNum, long MutMod ) { VEL_POP = VelPop; ITER_NUM = IterNum; MUT_MODUL = MutMod; }

	bool	PostaviParametre( int VelPop, long IterNum, long MutMod ); 
	int		GetVelPop() { return VEL_POP; }
	long	GetIterNum() { return ITER_NUM; }
	long	GetMutModul() { return MUT_MODUL; }

private:
	int		VEL_POP;
	long	ITER_NUM;
	long	MUT_MODUL;
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

class Gen {
public:
	Gen(int BrojIspita, int BrojRokova);
	
	vector<long>						Cromosom;
	vector< vector<int> >		TerminiIspita;

	int			BrojOdstupanjaPodrokova;
	int			BrojOdstupanjaBlizineIspita;
	int			BrojKazniOpterecenjeGrupe;
	int			BrojZeljaProfesora;
	int			BrojIspunjenihZeljaProfesora;
	int			BrojKazniZbogViseIspitaNaIstomSmjeru;
};

class OptProblem {
public:
		OptProblem();			// default konstruktor
		OptProblem( char *strFilePred, char *strFileProgram, char *strFilePresjek, char *strFileIspitiIstiDan );
		OptProblem( char *strFilePred, char *strFileProgram, char *strFilePresjek, char *strFileIspitiIstiDan, 
								Date start, Date end,
								vector<Ispit> vecSifreIspita, int nBroj,
								int BrRok, TerminRoka Vrsta );
		
		~OptProblem();

		ModelParam		ModPar;			// parametri modela
		GenAlgParam		GenPar;			// parametri genetskog algoritma
		OptFuncParam	FuncPar;		// parametri funkcije koja se optimizira
		
		int							nBrojPred;
		vector<Ispit>		vecPopisPred;			// detaljniji podaci o predmetu
		
		int							nUkupnoPredmeta;	// ukupan broj predmeta
		vector<string>	vecNaziviPred;		// vec[i] = naziv predmeta sa sifrom 'i'


		// vecPopisSifri[i] = u kojem retku (odn. stupcu) matrice matPresjekStud se 
		//										nalaze podaci o presjeku predmeta sa sifrom 'i'
		vector<int>						vecPopisSifraUIndex;
		// za koji predmet se nalaze podaci o presjeku u i-tom retku (odn. stupcu) matrice
		vector<int>						vecPopisIndexUSifru;
		
		vector< vector<int> >			matPresjekStud;		// matrica koja sadrži presjek studenata

		int												nUbacenoSifri;
		vector< int >							vecSifre;
		vector< vector<ParSifraPresjek> >		matPresjek;

		vector< vector<int> > matIstiPred;
		vector< vector<int> > matIspitiIstiDan;

		vector< Gen* >		Population;

		vector<int>				vecFiksIspiti;				// šifre fiksiranih ispita
		int								matFiksDani[4][10];		// dani na koje su fiksirani za sve rokove

	//*************************************** Funkcije	*************************************//

		int			Optimize();
		double	Func( Gen &a, FunkcijaCilja &ref  );

		int		UcitajPredmete( char *strFileName );
		int		UcitajNastavniProgram( char *strFileName );
		int		UcitajPresjek( char *strFileName );
		int		UbaciPresjek( int sif1, int sif2, int pres );
		void	UcitajPredmeteIstiDan( char *strFileName );
		
		void	PostaviDatume( Date start, Date end );
		int		PostaviIspite( vector<Ispit> vecSifreIspita, int nBroj );
		void	PostaviPresjek();
		void	PostaviParametre( int BrRok, TerminRoka Vrsta );

		void	IspisiPredmete();
		void	IspisiPopisPred();
		void	IspisiOptPredmete();
		void	IspisiPresjek();
		void	IspisiPresjek2();

		bool	PostaviRezultatOptimizacije( vector< Zapis > &vecRez );

		int		IndexPredSaSifrom( int sifra );
		bool	PartOfOptProblem( int sifra );		// da li je predmet sa sifrom 'sifra' ukljuèen u proces optimizacije

		void	GenerateInitialPopulation( vector<Gen *> &Pop );
		void	GenerateGene( Gen *gen, int SelectedBitsNum, int Range );

		Gen		Krizaj( Gen a, Gen b );
		void	Mutiraj( vector<Gen *> Pop );
};

/////////////////////////////////////////////////////////////////////////////
//	Potrebno nam je za rad genetskog algoritma

void	SelectRandomNumbers( vector<int> &a, int num, int start, int end );

long	SetBit( long a, int n );
long	ClearBit( long a, int n );
bool	IsBitSet( long a, int n );
int		NumberOfBits( long a );
bool	InSet( int a[], int num, int br );
bool	InSet( vector<int> a, int num, int br );

void	PrintPopulation( Gen	Pop[] );

int		Dist( int term1, int term2 );
int		TerminUDan( int term );
int		DanUTermin( int dan );
bool	IsVikend( int dan );

int		BrojRokova( TerminRoka	Rok );
int		BrojDana( TerminRoka	Rok );
int		BrojDanaZaPrikaz( TerminRoka Rok );

/*
#define VEL_POP		70

#define ITER_NUM		30000
#define	BR_ISPITA		20
#define BR_ROKOVA		3
#define BR_TERMINA	20
#define	BR_DANA			26
*/

void PrintConfig( OptProblem &o, vector<Gen*>	Pop );

