#ifndef __OPT_PROBLEM
#define __OPT_PROBLEM		1

#include "OptimizationData.h"

#include <iostream>
using namespace std;

typedef	int (*PFCALLBACK) ( void * );

typedef enum { ZIMSKI=0, PROLJETNI=1, LJETNI=2, JESENSKI=3, JESENSKI_IZV=4 } TerminRoka;

class	ProblemSolvingParam {
	bool		bSortPoPodrokovima;
	enum		{ FIKSNI, VAR } enPodjelaNaPodrokove;
};


class	OptProblem {
public:
	OptProblem();
	OptProblem( char *szFilePred, char *szFileProgram, char *szFilePresjek, char *szFileIspitiIstiDan );
	OptProblem( char *szFilePred, char *szFileProgram, char *szFilePresjek, char *szFileIspitiIstiDan,
							Date start, Date end,
							int BrPodrok, TerminRoka Vrsta);

	int		UcitajPredmete( char *szFileName );
	int		UcitajNastavniProgram( char *szFileName );
	int		UcitajPresjek( char *szFileName );
	int		UbaciPresjek( int sif1, int sif2, int pres );
	void	UcitajPredmeteIstiDan( char *szFileName );

	bool	PostaviPodatkeModela( ProblemData &tmp );

	void	Print();
	void	IspisiPredmete();

	int		Optimize( PFCALLBACK	pfCallBackFunc = NULL );

private:
	// sadrži podatke o svim ispitima i presjecima, iz kojih se onda selektiraju oni ispiti 
	// koji æe sudjelovati u optimizaciji
	ProblemData		probData;
	
	// sadrži podatke o ispitima koji sudjeluju u optimizaciji
//	ProblemData		modelData;

	// parametri optimizacijske funkcije ( koeficijenti kazni, ...
	OptFuncParam	FuncPar;

	SelectedProblemDescr	modelDescr;
	
//	OptimizationData			*optData;
	CalendarData					calData;

	vector<string>				vecNaziviPred;			// nazivi predmeta ( vec[i] = naziv predmeta sa šifrom 'i'
};

#endif