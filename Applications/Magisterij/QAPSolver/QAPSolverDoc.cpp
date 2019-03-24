// QAPSolverDoc.cpp : implementation of the CQAPSolverDoc class
//

#include "stdafx.h"
#include "QAPSolver.h"

extern	CQAPSolverApp theApp;

#include "QAPSolverDoc.h"
#include "QAPSolverView.h"

#include "DlgViewData.h"
#include "DlgViewResults.h"
#include "DlgViewBestSolution.h"

#include "DlgTestChart.h"
#include "DlgGeneric.h"

#include "DlgOptimizationGRASP.h"
#include "DlgOptimizationLocal.h"
#include "DlgOptimizationGenetic.h"
#include "DlgOptimizationTabuSearch.h"
#include "DlgOptimizationSimAnnealing.h"

#include <Optimization\Win32Serialize.h>

template bool SerializeInArchive<AlgParam>( CArchive &ar, std::vector<AlgParam> &);
template bool SerializeInArchive<float> ( CArchive &ar, Math::Matrix<float> & );


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverDoc

IMPLEMENT_DYNCREATE(CQAPSolverDoc, CDocument)

BEGIN_MESSAGE_MAP(CQAPSolverDoc, CDocument)
	//{{AFX_MSG_MAP(CQAPSolverDoc)
	ON_COMMAND(ID_FILE_LOAD_PROBLEM_DATA, OnLoadProblemData)
	ON_COMMAND(ID_VIEW_DATA, OnViewData)
	ON_COMMAND(ID_VIEW_RESULTS, OnViewResults)
	ON_COMMAND(ID_FILE_LOAD_BEST_SOL, OnLoadBestKnownSolution)
	ON_COMMAND(ID_VIEW_BEST_SOLUTION, OnViewBestSolution)
	ON_COMMAND(ID_TEST_CHART, OnTestChart)
	ON_COMMAND(ID_TEST_GENERIC, OnTestGeneric)
	ON_COMMAND(ID_TABU_SEARCH_ROBUST_DIVERSIFY, OnTabuSearchRobustDiversify)
	ON_COMMAND(ID_TABU_SEARCH_SIMPLE, OnTabuSearchSimple)
	ON_COMMAND(ID_TABU_SEARCH_SIMPLE_DIVERSIFY, OnTabuSearchSimpleDiversify)
	ON_COMMAND(ID_TABU_SEARCH_ROBUST_SIMPLE, OnTabuSearchRobustSimple)
	ON_COMMAND(ID_START_OPTIMIZATION_BR_SIMANN, OnStartOptimizationBrSimann)
	ON_COMMAND(ID_START_OPTIMIZATION_AUT_SIMANN, OnStartOptimizationAutSimAnn)
	ON_COMMAND(ID_START_OPTIMIZATION_AUT_CONNOLY_SIMANN, OnStartOptimizationAutConnolySimAnn)
	ON_COMMAND(ID_START_OPTIMIZATION_CONNOLY_SIMANN, OnStartOptimizationConnolySimAnn)
	ON_COMMAND(ID_START_OPTIMIZATION_WW_SIMANN, OnStartOptimizationWWSimAnn)
	ON_COMMAND(ID_START_OPTIMIZATION_3TOUR_SELECTION, OnStartOptimization3TournamentSelection)
	ON_COMMAND(ID_START_OPTIMIZATION_FIRST_IMPROV, OnStartOptimizationFirstImprovement)
	ON_COMMAND(ID_START_OPTIMIZATION_BEST_IMPROV, OnStartOptimizationBestImprovement)
	ON_COMMAND(ID_START_OPTIMIZATION_HEIDER, OnStartOptimizationHeider)
	ON_COMMAND(ID_START_OPTIMIZATION_GRASP, OnStartOptimizationGrasp)
	ON_COMMAND(ID_START_OPTIMIZATION_FFGA, OnStartOptimizationFFGA)
	ON_COMMAND(ID_START_OPTIMIZATION_GREEDY_GA, OnStartOptimizationGreedyGA)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverDoc construction/destruction

CQAPSolverDoc::CQAPSolverDoc()
{
	// TODO: add one-time construction code here
	A = NULL;
	B = NULL;

	bDataLoaded = false;
	bBestSolutionLoaded = false;
}

CQAPSolverDoc::~CQAPSolverDoc()
{
	if( A != NULL )
		delete A;

	if( B != NULL )
		delete B;
}

BOOL CQAPSolverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CQAPSolverDoc serialization

void CQAPSolverDoc::Serialize(CArchive& ar)
{
//	int		i, j;
	int	Size;

	if (ar.IsStoring())
	{
		ar << bDataLoaded;

		if( bDataLoaded == true ) {
			// zapisujemo velièinu modela
			ar << getProblemSize();
	
			ar << *A;
			ar << *B;
		}

		ar << bBestSolutionLoaded;
		if( bBestSolutionLoaded == true ) {
			ar << BestKnownSolution;
		}
	}
	else
	{
		// najprije treba izbrisati stare podatke
		ClearAllData();

		int		bLoad;
		ar >> bLoad;
		bDataLoaded = (bLoad != 0);
		
		if( bDataLoaded == true ) {
			// uèitavamo velièinu
			ar >> Size;
			setProblemSize(Size);
			
			A = new Math::Matrix<float>(getProblemSize(),getProblemSize());
			B = new Math::Matrix<float>(getProblemSize(),getProblemSize());
			
			if( !A->IsValid() || !B->IsValid() ) {
				AfxMessageBox("Greška kod rezerviranja memorije !!!");

				// ovdje je pitanje što æe se desiti ukoliko se jedna konstruira a druga ne
				delete A;
				delete B;
				
				return;
			}

			ar >> *A;
			ar >> *B;
		}
		ar >> bLoad;
		bBestSolutionLoaded = (bLoad != 0);

		if( bBestSolutionLoaded == true ) {
			ar >> BestKnownSolution;
		}
	}

//	SerializeInArchive(ar, vecSol);
	int		i;

	if( ar.IsStoring() ) {
		Size = vecSol.size();
		ar << Size;

		for( i=0; i<Size; i++ )
			vecSol[i].Serialize(ar);
	}
	else {
		ar >> Size;

		vecSol.resize(Size);
		for( i=0; i<Size; i++ ) {
			ar >> vecSol[i];
		}
	}

//	SerializeInArchive(ar, vecAlgDesc );
	if( ar.IsStoring() ) {
		Size = vecAlgDesc.size();
		ar << Size;

		for( i=0; i<Size; i++ )
			ar << vecAlgDesc[i];
	}
	else {
		ar >> Size;

		vecAlgDesc.resize(Size);
		for( i=0; i<Size; i++ )
			ar >> vecAlgDesc[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverDoc diagnostics

#ifdef _DEBUG
void CQAPSolverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQAPSolverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CQAPSolverDoc::ClearAllData() 
{
	if( A != NULL )
		delete A;
	if( B != NULL )
		delete B;

	setProblemSize(-1);
	bDataLoaded = false;

	vecSol.clear();
	vecAlgDesc.clear();
}


/////////////////////////////////////////////////////////////////////////////
// CQAPSolverDoc commands

void CQAPSolverDoc::OnLoadProblemData() 
{
	CFileDialog		fileDlg(TRUE);

	if( fileDlg.DoModal() == IDOK ) {
		CString	path = fileDlg.GetFileName();

		FILE *fp;
		fp = fopen(path.GetBuffer(100), "r");

		if( fp == NULL ) {
			AfxMessageBox("Nisam uspio otvoriti datoteku ");
		}
		else {
			int		i, j, Size;

			fscanf(fp, "%d", &Size);
			setProblemSize(Size);

			if( getProblemSize() > 0 && getProblemSize() < 1000 ) {
				A = new Math::Matrix<float>(getProblemSize(),getProblemSize());
				B = new Math::Matrix<float>(getProblemSize(),getProblemSize());
			}
			else {
				AfxMessageBox("Greška kod uèitavanja velièine problema ");
			}

			for( i=1; i<=getProblemSize(); i++ )
				for( j=1; j<=getProblemSize(); j++ )
					if( fscanf(fp, "%f", &(*A)[i][j] ) <= 0 ) 
					{
						AfxMessageBox("Greška kod uèitavanja podataka o matrici A ");
						ClearAllData();

						return;
					}

			for( i=1; i<=getProblemSize(); i++ )
				for( j=1; j<=getProblemSize(); j++ )
					if( fscanf(fp, "%f", &(*B)[i][j] ) <= 0 ) {
						AfxMessageBox("Greška kod uèitavanja podataka o matrici B ");
						ClearAllData();						

						return;
					}

			if( !A->IsSymetric() )
				AfxMessageBox("Matrica A nije simetrièna");

			bDataLoaded = true;
		}
	}
}

void CQAPSolverDoc::OnLoadBestKnownSolution() 
{
	CFileDialog		fileDlg(TRUE);

	if( fileDlg.DoModal() == IDOK ) {
		CString	path = fileDlg.GetFileName();

		FILE *fp;
		fp = fopen(LPCTSTR(path), "r");

		if( fp == NULL ) {
			AfxMessageBox("Nisam uspio otvoriti datoteku ");
		}
		else {
			int			Size;
			float		Value;

			fscanf(fp, "%d", &Size );
			if( Size != getProblemSize() ) {
				AfxMessageBox("Velièina rješenja problema se ne podudara sa velièinom uèitanog problema ");
				return;
			}
			if( fscanf(fp, "%f", &Value) != 1 ) {
				AfxMessageBox("Nisam uspio uèitati iznos rješenja");
				return;
			}
			QAPSolution		Sol(getProblemSize());

			Sol.setValue(Value);
			for( int i=1; i<=getProblemSize(); i++ )
				if( fscanf(fp, "%d", &Sol[i] ) != 1 ) {
					AfxMessageBox("Greška kod uèitavanja lokacija ");
					return;
				}
			BestKnownSolution = Sol;
			bBestSolutionLoaded = true;
			fclose(fp);

			SetModifiedFlag();
		}
	}
}

bool	CQAPSolverDoc::AddOptResult(IterOptContResWithSolutions<float, QAPSolution> &res, AlgDescription	&alg )
{
	int	size = vecSol.size();

	vecSol.resize(size+1);
	vecAlgDesc.resize(size+1);
	
	vecSol[size] = res;
	vecAlgDesc[size] = alg;

	SetModifiedFlag();

	return true;
}

bool	CQAPSolverDoc::DeleteOptimizationResult( int Index )
{
	if( Index >= 0 && Index < vecSol.size() ) {
		vecSol.erase(vecSol.begin() + Index);
		vecAlgDesc.erase(vecAlgDesc.begin() + Index);

		SetModifiedFlag();
		return true;
	}
	return false;
}

void CQAPSolverDoc::OnViewData() 
{
	if( bDataLoaded == true ) {
		CDlgViewData	*pDlg = new CDlgViewData();

		if( !A->IsSymetric() )
			AfxMessageBox("Matrica A nije simetrièna");

		pDlg->m_ctrlGridA.SetRows(getProblemSize()+1);
		pDlg->m_ctrlGridA.SetCols(getProblemSize()+1);

		int		i, j;
		char	str[100];
		for( i=1; i<=getProblemSize(); i++ ) {
			pDlg->m_ctrlGridA.SetColWidth(i, 600);
		
			for( j=1; j<=getProblemSize(); j++ ) {
				sprintf(str, "%6.2f", (*A)[i][j]);
				pDlg->m_ctrlGridA.SetTextMatrix(i, j, str);
			}
		}

		pDlg->m_ctrlGridB.SetRows(getProblemSize()+1);
		pDlg->m_ctrlGridB.SetCols(getProblemSize()+1);

		for( i=1; i<=getProblemSize(); i++ ) {
			pDlg->m_ctrlGridB.SetColWidth(i, 600);

			for( j=1; j<=getProblemSize(); j++ ) {
				sprintf(str, "%6.2f", (*B)[i][j]);
				pDlg->m_ctrlGridB.SetTextMatrix(i, j, str);
			}
		}

		pDlg->ShowWindow(TRUE);
	}
}


void CQAPSolverDoc::OnViewResults() 
{
	CDlgViewResults	*pDlg = new CDlgViewResults(this); //,pView);

	FillDialogWithResults(pDlg);

	pDlg->ShowWindow(TRUE);
}

void	CQAPSolverDoc::FillDialogWithResults( CDlgViewResults *pDlg )
{
	int	Size = vecSol.size();
	pDlg->m_ctrlRes.SetRows(Size+1);

	pDlg->m_ctrlRes.SetCols(7);
	pDlg->m_ctrlRes.SetTextMatrix(0,0,"OptID");
	pDlg->m_ctrlRes.SetColWidth(0, 1500);

	pDlg->m_ctrlRes.SetTextMatrix(0,1,"Type");
	pDlg->m_ctrlRes.SetColWidth(1, 1200);
	pDlg->m_ctrlRes.SetTextMatrix(0,2,"Subtype");
	pDlg->m_ctrlRes.SetColWidth(2, 1800);

	pDlg->m_ctrlRes.SetTextMatrix(0,3,"Parameters");
	pDlg->m_ctrlRes.SetColWidth(3, 5000);
	
	pDlg->m_ctrlRes.SetTextMatrix(0,4,"Duration");
	pDlg->m_ctrlRes.SetColWidth(4, 1100);

	pDlg->m_ctrlRes.SetTextMatrix(0,5,"Iter.num.");
	pDlg->m_ctrlRes.SetColWidth(5, 800);

	pDlg->m_ctrlRes.SetTextMatrix(0,6,"Func.value");
	pDlg->m_ctrlRes.SetColWidth(6, 1200);

	int			i;
	char		str[100], str2[100], Type;
	long		IterNum;
	int			Min, Sec, Msec; 
	float		Duration, FuncValue;

	std::string		strIn;

	for( i=0; i<Size; i++ )
	{
		vecAlgDesc[i].getOptID(strIn);
		pDlg->m_ctrlRes.SetTextMatrix(i+1,0, strIn.c_str() );
		vecAlgDesc[i].getType(strIn);
		pDlg->m_ctrlRes.SetTextMatrix(i+1,1, strIn.c_str() );
		vecAlgDesc[i].getSubtype(strIn);
		pDlg->m_ctrlRes.SetTextMatrix(i+1,2, strIn.c_str() );

		str[0] = 0;
		for( int j=0; j<vecAlgDesc[i].getParamNum(); j++ )
		{
			string	Name, Value;
			vecAlgDesc[i].getParam(j, Name, Value, Type);
			sprintf(str2, "%s = %s; ", Name.c_str(), Value.c_str() );
			strcat(str, str2);
		}
		pDlg->m_ctrlRes.SetTextMatrix(i+1,3, str );

		Duration = vecSol[i].getOptimDuration();
		Min  = Duration/60000;
		Sec  = (Duration - Min*60000) / 1000;
		Msec = ((long) Duration) % 1000;
		sprintf(str, "%02d:%02d:%03d", Min, Sec, Msec  );
		pDlg->m_ctrlRes.SetTextMatrix(i+1,4, str );
		
		IterNum = vecSol[i].getIterNum();
		sprintf(str, "%ld", IterNum );
		pDlg->m_ctrlRes.SetTextMatrix(i+1,5, str );

		FuncValue = vecSol[i].getBestFuncValue();
		sprintf(str, "%.2f", FuncValue );
		pDlg->m_ctrlRes.SetTextMatrix(i+1,6, str );
	}
}

void CQAPSolverDoc::OnViewBestSolution() 
{
	if( bBestSolutionLoaded == false )
		AfxMessageBox("Best known solution not set !!!");
	else {
		CDlgViewBestSolution	*pDlg;

		char			hsol[10];
		CString		csValue;
		CString		csAssignment;

		sprintf(hsol, "%f", BestKnownSolution.getValue() );
		csValue = hsol;

		for( int i=1; i<=getProblemSize(); i++ ) {
			sprintf(hsol, " %2d ", BestKnownSolution[i]);
			csAssignment += hsol;
		}

		pDlg = new CDlgViewBestSolution(csValue, csAssignment);
		pDlg->ShowWindow(TRUE);
	}
}

void CQAPSolverDoc::OnTestChart() 
{
	CDlgTestChart		*pDlg;

	pDlg = new CDlgTestChart();

	pDlg->m_ctrlChart.SetChartType(2);
//	pDlg->m_ctrlChart.SetChartType(VtChChartType3dLine);

	pDlg->m_ctrlChart.SetColumnCount(8);
	pDlg->m_ctrlChart.SetRowCount(8);

	for( int i=1; i<=8; i++ ) {
		pDlg->m_ctrlChart.SetColumn(i);
		pDlg->m_ctrlChart.SetRow(i);
		pDlg->m_ctrlChart.SetColumnLabel("Keloza djoza");
		pDlg->m_ctrlChart.SetRowLabel("Keloza djoza");

		for( int j=1; j<=8; j++ )
		{
			pDlg->m_ctrlChart.SetRow(j);

			int		c = rand() % 200;
			char	str[20];
			sprintf(str, "%d", c);
			pDlg->m_ctrlChart.SetData(str);
		}
	}

	pDlg->ShowWindow(TRUE);
}

void CQAPSolverDoc::OnTestGeneric() 
{
}

void CQAPSolverDoc::OnTabuSearchRobustDiversify() 
{
	CDlgTabuSearchRobustDiversify	*pDlg;

	pDlg = new CDlgTabuSearchRobustDiversify(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=0; i<getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i+1);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnTabuSearchSimple() 
{
	CDlgTabuSearchSimple *pDlg;

	pDlg = new CDlgTabuSearchSimple(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnTabuSearchSimpleDiversify() 
{
	CDlgTabuSearchSimpleDiversify	*pDlg;

	pDlg = new CDlgTabuSearchSimpleDiversify(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnTabuSearchRobustSimple() 
{
	CDlgTabuSearchRobust *pDlg;

	pDlg = new CDlgTabuSearchRobust(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}


void CQAPSolverDoc::OnStartOptimizationBrSimann() 
{
	CDlgSimAnnSimple	*pDlg;

	pDlg = new CDlgSimAnnSimple(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationAutSimAnn() 
{
	CDlgSimAnnAutomated	*pDlg;

	pDlg = new CDlgSimAnnAutomated(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationAutConnolySimAnn() 
{
	CDlgSimAnnConnAutomated	*pDlg;

	pDlg = new CDlgSimAnnConnAutomated(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationConnolySimAnn() 
{
	CDlgSimAnnConn *pDlg;

	pDlg = new CDlgSimAnnConn(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationWWSimAnn() 
{
	CDlgSimAnnWW	*pDlg;

	pDlg = new CDlgSimAnnWW(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimization3TournamentSelection() 
{
	CDlgGenAlgTournamentSelection *pDlg;

	pDlg = new CDlgGenAlgTournamentSelection(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationFirstImprovement() 
{
	CDlgLSFirstImprovement	*pDlg;

	pDlg = new CDlgLSFirstImprovement(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationBestImprovement() 
{
	CDlgLSBestImprovement	*pDlg;

	pDlg = new CDlgLSBestImprovement(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationHeider() 
{
	CDlgLSHeider	*pDlg;

	pDlg = new CDlgLSHeider(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationGrasp() 
{
	CDlgGRASP	*pDlg;

	pDlg = new CDlgGRASP(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;
}

void CQAPSolverDoc::OnStartOptimizationFFGA() 
{
	CDlgGenAlgFFGA	*pDlg;

	pDlg = new CDlgGenAlgFFGA(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;	
}

void CQAPSolverDoc::OnStartOptimizationGreedyGA() 
{
	CDlgGenAlgGreedy	*pDlg;

	pDlg = new CDlgGenAlgGreedy(this);

	if( bDataLoaded == true ) {
		int		i;
		char	str[200];

		pDlg->m_ctrlSol.SetTermNum(getProblemSize());
		for( i=1; i<=getProblemSize(); i++ ) {
			sprintf(str, "Facility%2d", i);
			
			if(	pDlg->m_ctrlSol.AddRow(str) != TRUE )
				AfxMessageBox("Nisam uspio dodati redak ");
		}
		pDlg->ShowWindow(TRUE);
	}
	else
		delete pDlg;	
}
