#ifndef __OPT_PROBLEM
#define __OPT_PROBLEM		1

#pragma warning( disable : 4786 )

#include "CalendarData.h"
#include "IRokData.h"
#include "Matrix.h"
#include "IOptRok.h"

#include <map>

typedef	int	 (*PFCALLBACK) ( void * );
typedef enum { ZIMSKI=0, PROLJETNI=1, LJETNI=2, JESENSKI=3, JESENSKI_IZV=4 } TerminRoka;

// forward declaration
struct	ParSifraPresjek;
class		PresjekStudData;
class		IspitDodPodaci;
class		Ispit;
class		ProblemData;
class		OptFuncParam;
class		SelectedProblemDescr;
class		OptProblem;
class		ProblemSolvingParam;



#ifndef _PROBLEM_DATA
#define	_PROBLEM_DATA		1

/********************************************************************************************/
/********************************************************************************************/

/*
#ifndef _PRESJEK_STUD_DATA
#define _PRESJEK_STUD_DATA	1


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

	void		Print(FILE *);
	bool		Sort();
	bool		Erase();

private:
	vector<int>			vecSifreRedaka;
	vector< vector<ParSifraPresjek> >		matPresjek;

	int		findSifra( int sifra );
	bool	addPresjek( int redak, int sifra2, int presjek );
	bool	sortRedak( int redak );
};

#endif  // _PRESJEK_STUD_DATA
*/

/********************************************************************************************/
/********************************************************************************************/

#ifndef _ISPIT_DATA
#define _ISPIT_DATA	1


#endif _ISPIT_DATA

/********************************************************************************************/
/********************************************************************************************/


/********************************************************************************************/
/********************************************************************************************/

#ifndef __MODEL_DESCRIPTION
#define	__MODEL_DESCRIPTION		1


#endif  // _MODEL_DESCRIPTION

#endif	// _PROBLEM_DATA


class	ProblemSolvingParam {
	bool		bSortPoPodrokovima;
	enum		{ FIKSNI, VAR } enPodjelaNaPodrokove;
};


class	OptProblem {
public:
	OptProblem();
	OptProblem( Date start, Date end,
						  int BrPodrok, TerminRoka Vrsta );

	// postavlja IData pokazivaè na objekt iz kojeg æemo uzimati podatke
	void	SetDataObject( IORDataSource *p ) { pData = p; }
	// koristeæi dobiveni IData interface, uèitava iz njega sve podatke u klasu ProblemData
	bool	LoadAllData( ProblemData *dat );
	
	int		BrojIspita() { return probData.BrojIspita(); }
	int		BrojIspitaModela() { return modelData.BrojIspita(); }
	int		BrojTermina() { return calData.BrojTermina(); }
	int		BrojPodrokova() { return calData.BrojPodrokova(); }

	void	Print( FILE * );
	void	PrintModel( FILE * );

	int		ProduceA( ProblemData *dat, Matrix<float> &A );
	int		ProduceB( ProblemData *dat, Matrix<float> &B );
	int		ProduceC( ProblemData *dat, Matrix<float> &C );

	void	SetDates(Date start, Date end) { calData.setDate(start,end); }
	void	SetBrPodrokova( int BrPodrok ) { calData.setBrojPodrokova(BrPodrok); }

	bool	SetModelDescription( int SemLow, int SemUpp, int StudLow, int StudUpp, char *Opis );
	void	GetModelDescription( int &SemLow, int &SemUpp, int &StudLow, int &StudUpp, char *Opis );
	bool	PostaviPodatkeModela();

	int		Optimize( PFCALLBACK	pfCallBackFunc = NULL );

	ProblemData&	getProblemData() { return probData; }
	ProblemData&	getModelData() { return modelData; }

private:
	// pokazivaè na objekt koji æe nas opskrbiti podacima za model
	IORDataSource	*pData;

	// sadrži podatke o svim ispitima i presjecima, iz kojih se onda selektiraju oni ispiti 
	// koji æe sudjelovati u optimizaciji
	ProblemData		probData;

	ProblemData		modelData;

	// parametri optimizacijske funkcije ( koeficijenti kazni, ...
	OptFuncParam	FuncPar;

	// definira koji su ispiti dio modela
	SelectedProblemDescr	modelDescr;
	
	// podati o datumima ( vremenski interval, broj termina, ... 
	CalendarData					calData;
};

#endif