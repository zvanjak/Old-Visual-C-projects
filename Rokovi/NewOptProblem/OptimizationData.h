#ifndef __OPTIMIZATION_DATA	
#define	__OPTIMIZATION_DATA		1

#include <iostream>

using namespace std;

#define	MAX_VEL_POP			200
#define	MAX_PODROKOVA		3
#define MAX_GRUPA				50

#include "CalendarData.h"
#include "ProblemData.h"
#include "ModelDescription.h"

const	int		cnstDefaultVelPop = 70;
const	int		cnstDefaultIterNum = 500000;
const	int		cnstDefaultMutModul = 20000;


class ParBrStudBrIsp {
public:
	ParBrStudBrIsp() { m_nBrStud = 0; m_nBrIsp = 0; }

	int		m_nBrStud;
	int		m_nBrIsp;
};


/***************************************************************************************/

class StatisticalData {
public:
	int		brOdstupanjaOdPodrokova;
	int		brPrevelikaBlizinaIspita;
	int		brPrekoracenjeOpterecenjaNaGrupiPredmeta;
	int		brZeljaProfesora;
	int		brIspunjeneZeljeProfesora;

	vector<long>	brStudentDana_Ispita;
	long					totalStudentDana_Ispita;
};


/***************************************************************************************/

// koliko pojedini dijelovi sudjeluju s iznosom u funkciji cilja
class	FuncData {
public:
	double	BlizinaIspita;
	double	KaznePrevelikeBlizine;
	double	PresjekIspita;
	double	KazneOdstupanjaOdPodrokova;
	double	ZeljeProfesora;
	double	KazneOpterecenjaNaGrupama;
	double	KaznePrekoracenjaMaxIspitaNaIstomSmjeru;
};


/***************************************************************************************/

class	Gen {
public:
	Gen( int brIspita, int brPodokova );
	~Gen();

	bool	fiksirajTermin( int brIspita );
	bool	calcStatistic( Gen & );

	void	GenerateGeneTerm( CalendarData &calData );

	inline int	GetTermin( int brIsp, int brPodrok );
	inline void	SetTermin( int brIsp, int brPodrok, int Term ) { m_vecpnTerminiIspita[brIsp][brPodrok] = Term; }
	inline bool	IsTermSet( int brIsp, int Term );
	inline bool	IsFiksiranTermin( int brIsp );

private:
	vector<int *>		m_vecpnTerminiIspita;

	// da li je termin ispita fiksiran 
	//( ukoliko se fiksira termin , onda se mora fiksirati termin na svim podrokovima )
	vector<bool>		m_vecbFiksniTermini;

	// treba nam da bi znali da li je adresiranje pomoæu operatora [] ispravno
	// u release verziji se može i izbaciti
	int		m_nBrIsp;
	int		m_nBrPodrok;

	StatisticalData		m_statData;
	FuncData					m_funcData;

	friend class	OptimizationData;
	friend class	OptProblem;
};


/***************************************************************************************/

class GenAlgParam {
public:
	GenAlgParam()	{ m_nVelPop = cnstDefaultVelPop;
									m_lIterNum = cnstDefaultIterNum;
									m_lMutModul = cnstDefaultMutModul; }
	
	GenAlgParam( int inVelPop, long inIterNum, long inMutMod ) {
						m_nVelPop		= inVelPop; 
						m_lIterNum	= inIterNum;
						m_lMutModul = inMutMod; }

	int		GetVelPop() { return m_nVelPop; }
	long	GetIterNum() { return m_lIterNum; }
	long	GetMutModul() { return m_lMutModul; }

	void	SetVelPop( int inVelPop );
	void	SetIterNum( int inIterNum );
	void	SetMutModul( int inMutModul );

	void	PostaviParametre( int inVelPop, long inIterNum, long inMutMod ); 
private:
	int		m_nVelPop;
	long	m_lIterNum;
	long	m_lMutModul;
};


/***************************************************************************************/

class OptimizationData {
public:
//	OptimizationData( int inBrIsp, int inBrTerm, int inBrPodrok, int inVelPop = cnstDefaultVelPop  );
	
	OptimizationData( ProblemData &problem, 
										SelectedProblemDescr &opis, 
										CalendarData	&cal,
										OptFuncParam	&funcPar,
										int inVelPop = cnstDefaultVelPop  );
	
	bool	PostaviPodatkeModela( ProblemData &probData, SelectedProblemDescr &modelDescr );

	// TODO
	// mijenja velicinu populacije
	//	- ukoliko je novi broj veæi od staroga, nove jedinke se generiraju
	//	- ukoliko je novi broj jedinki manji, onda treba neke jedinke izbaciti
	//		( po defaultu se izbacuju one najgore, ali æe se to moæi i promijeniti )
	bool	SetVelPop( int inVelPop );
	bool	SetIterNum( int IterNum );
	bool	SetMutModul( int inMutModul );

	int		GetVelPop() { return genParam.GetVelPop(); }
	long	GetIterNum() { return genParam.GetIterNum(); }
	long	GetMutModul() { return genParam.GetMutModul(); }

	Gen&	GetGene( int i );

	// funkcije genetskog algoritma
	void		GenerateInitialPopulation( void );

	void		Krizaj( Gen &a, Gen &b, Gen &res );
	void		Mutiraj( void );
	double	Func( Gen &a );

private:
	int		brTerm;
	int		brIsp;
	int		brPodrok;
	
	GenAlgParam			genParam;
	vector<Gen *>		Population;

	// podaci koje æemo koristiti prilikom izraèunavanja, pa da ih ne kreiramo u svakoj iteraciji
	// izraèunavanja, staviti æemo ih u ovu klasu
	vector< vector<ParBrStudBrIsp> >   matSumaPoGrupPred;

	friend class	OptProblem;

	ProblemData		modelData;
	CalendarData	calData;
	OptFuncParam	FuncPar;
};

/***************************************************************************************/

void SelectRandomNumbers( vector<int> &a, int num, int start, int end );

#endif