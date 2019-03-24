// TestFuncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestOptFunc.h"

#include "TestFuncDlg.h"
#include "DlgSetCoeficients.h"
#include "DlgGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestFuncDlg dialog


CTestFuncDlg::CTestFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestFuncDlg::IDD, pParent)
{
	Create(IDD_TEST, pParent );
	ShowWindow(1);

	ExamNum = 2;
	TermNum = 20;
	SubPeriodNum = 3;

	PopSize = 70;
	IterNum = 10000;
	MutProb = 0.01;

	DistType = EQUAL_DIST;
	CutPoint = 8;
	LinCoef = 1;
	Pow = 0.5;
	X0 = 8;

	pBestTotal = NULL;
	BestInd = 0;
	pCurrSolution = NULL;

	bIsAllocated = false;
	//{{AFX_DATA_INIT(CTestFuncDlg)
	//}}AFX_DATA_INIT
}

CTestFuncDlg::~CTestFuncDlg()
{
	if( bIsAllocated == true ) {
		for( int i=0; i<matSolEvol.size(); i++ )
			matSolEvol[i].~vector();
		matSolEvol.~vector();
	}
}


void CTestFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestFuncDlg)
	DDX_Control(pDX, IDC_CHECK_LINCUT, m_ctrlCheckLin);
	DDX_Control(pDX, IDC_CHECK_POW, m_ctrlCheckPow);
	DDX_Control(pDX, IDC_CHECK_EXP, m_ctrlCheckExp);
	DDX_Control(pDX, IDC_CHECK_EQUAL, m_ctrlCheckEqual);
	DDX_Control(pDX, IDC_PRIKAZRASPOREDAISPITACTRL1, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestFuncDlg, CDialog)
	//{{AFX_MSG_MAP(CTestFuncDlg)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_SET, OnSetCoeficients)
	ON_BN_CLICKED(IDC_CHECK_EQUAL, OnCheckEqual)
	ON_BN_CLICKED(IDC_CHECK_POW, OnCheckPow)
	ON_BN_CLICKED(IDC_CHECK_EXP, OnCheckExp)
	ON_BN_CLICKED(IDC_CHECK_LINCUT, OnCheckLincut)
	ON_BN_CLICKED(IDC_SHOW_BEST_CROM, OnShowBestCrom)
	ON_BN_CLICKED(IDC_SHOW_GRAPH, OnShowGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestFuncDlg message handlers

void CTestFuncDlg::OnStart() 
{
	_CrtMemState s1, s2, s3;

	_CrtMemCheckpoint( &s1 );
	Optim();
	_CrtMemCheckpoint( &s2 );

	if ( _CrtMemDifference( &s3, &s1, &s2) ) 
		 _CrtMemDumpStatistics( &s3 );
}

void CTestFuncDlg::Optim()
{
	int		i, j;
	char	strName[100];

	if( m_ctrlList.GetRowNum() < ExamNum )
		for( i=m_ctrlList.GetRowNum(); i<ExamNum; i++ ) {
			sprintf(strName, "Ispit%d", i);
			m_ctrlList.AddRow(strName);
		}
	// TODO: Add your control notification handler code here
	pQAP = new QAPScheduleGenetic(ExamNum,SubPeriodNum,TermNum, PopSize, IterNum, MutProb);

	// ako smo matricu alocirali u prethodnom optimiranju, sada æemo je osloboditi
	if( bIsAllocated == true ) {
		for( i=0; i<matSolEvol.size(); i++ )
			matSolEvol[i].~vector();
		matSolEvol.~vector();
	}

	// da bi je mogli ponovno alocirati
	matSolEvol.resize(PopSize);
	for( i=0; i<PopSize; i++ )
		matSolEvol[i].resize(IterNum/100+1);
	bIsAllocated = true;

	Matrix<float>			A(ExamNum,ExamNum);
	Matrix<float>			B(TermNum,TermNum);		// matrica udaljenosti meðu terminima

	for( i=0; i<ExamNum; i++ )
		for( j=i; j<ExamNum; j++ ) {
			A[i][j] = 1;
			A[j][i] = 1;
			if( i == j )
				A[i][i] = 2;
		}

	float	dist;
	B.Clear();
	for( i=0; i<TermNum; i++ )
		for( j=i+1; j<TermNum; j++ ) {
			dist = fabs(i-j);
			
			if( DistType == EQUAL_DIST )
				B[i][j] = dist;
			else if( DistType = LINEAR_CUT ) {
				if( dist < CutPoint )
					B[i][j] = LinCoef * dist;
				else
					B[i][j] = LinCoef * CutPoint;
			}
			else if( DistType == POW_DIST )
				B[i][j] = pow(dist, Pow);		
			else if( DistType == EXP_DIST )
				B[i][j] = exp(-(dist-X0)*(dist-X0)/20);

			B[j][i] = B[i][j];
		}

	pQAP->SetA(A);
	pQAP->SetB(B);

	srand(time(NULL));
	
	QAPResults	res;

	pQAP->SetCallBackObj(this);
	pQAP->SetCallBackPeriod(100);

	res = pQAP->Optimize();

	pQAP->~QAPScheduleGenetic();
}

void CTestFuncDlg::RefreshData( OptResults *res )
{
	int			i, j, term;

	CDC	*pDC = GetDC();
	CString	str;
	char	s[100];
	sprintf(s, "BestCrom[%2d] = %15.7f,   Iter=%6d               ", res->BestCromInd, res->BestFuncVal, res->IterNum );
	str = s;
	pDC->TextOut(20,550,str);

	j = res->IterNum / 100;
	for( i=0; i<PopSize; i++ ) {
		matSolEvol[i][j] = pQAP->GetIndividual(i);
	}

	// najbolja jedinka trenutno
	QAPScheduleCrom		&best = pQAP->GetIndividual(res->BestCromInd);

	if( pBestTotal == NULL ) 	// ukoliko još nismo definirali najbolju, onda je to ova
		pBestTotal = matSolEvol[res->BestCromInd][j].p;
	else if(pBestTotal->GetFuncValue() < best.GetFuncValue())
		pBestTotal = matSolEvol[res->BestCromInd][j].p;

	// zapamtiti æemo i indeks najbolje jedinke kako bi mogli nacrtati graf
	BestInd = res->BestCromInd;		

	for( i=0; i<ExamNum; i++ ) 
	{
		m_ctrlList.ClearRowData(i);
		for( j=0; j<SubPeriodNum; j++ ) {
			term = best[i][j];
			m_ctrlList.AddRowTerm(i,term);
		}
	}
	m_ctrlList.RedrawWindow();
}

void CTestFuncDlg::OnSetCoeficients() 
{
	// TODO: Add your control notification handler code here
	CDlgSetCoeficients	Dlg;
	
	Dlg.m_ctrlExamNum = ExamNum;
	Dlg.m_ctrlTermNum = TermNum;
	Dlg.m_ctrlSubperiodNum = SubPeriodNum;

	Dlg.m_ctrlIterNum = IterNum;
	Dlg.m_ctrlPopSize = PopSize;
	Dlg.m_ctrlMutProb = MutProb;

	Dlg.m_ctrlExp = Pow;
	Dlg.m_ctrlX0	= X0;
	Dlg.m_ctrlCutPoint = CutPoint;
	Dlg.m_ctrlLinCoef = LinCoef;

	int ret = Dlg.DoModal();
	if( ret == IDOK ) {
		ExamNum = Dlg.m_ctrlExamNum;
		TermNum = Dlg.m_ctrlTermNum;
		SubPeriodNum = Dlg.m_ctrlSubperiodNum;

		IterNum = Dlg.m_ctrlIterNum;
		PopSize = Dlg.m_ctrlPopSize;
		MutProb = Dlg.m_ctrlMutProb;

		Pow = Dlg.m_ctrlExp;
		X0	= Dlg.m_ctrlX0;
		CutPoint = Dlg.m_ctrlCutPoint;
		LinCoef = Dlg.m_ctrlLinCoef;
	}
}

void CTestFuncDlg::OnCheckEqual() 
{
	// TODO: Add your control notification handler code here
	DistType = EQUAL_DIST;
	m_ctrlCheckPow.SetCheck(FALSE);
	m_ctrlCheckExp.SetCheck(FALSE);
	m_ctrlCheckLin.SetCheck(FALSE);
}

void CTestFuncDlg::OnCheckPow() 
{
	// TODO: Add your control notification handler code here
	DistType = POW_DIST;
	m_ctrlCheckExp.SetCheck(FALSE);
	m_ctrlCheckEqual.SetCheck(FALSE);
	m_ctrlCheckLin.SetCheck(FALSE);
}

void CTestFuncDlg::OnCheckExp() 
{
	// TODO: Add your control notification handler code here
	DistType = EXP_DIST;	
	m_ctrlCheckEqual.SetCheck(FALSE);
	m_ctrlCheckPow.SetCheck(FALSE);
	m_ctrlCheckLin.SetCheck(FALSE);
}

void CTestFuncDlg::OnCheckLincut() 
{
	// TODO: Add your control notification handler code here
	DistType = LINEAR_CUT;	
	m_ctrlCheckExp.SetCheck(FALSE);
	m_ctrlCheckEqual.SetCheck(FALSE);
	m_ctrlCheckPow.SetCheck(FALSE);
}

BEGIN_EVENTSINK_MAP(CTestFuncDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestFuncDlg)
	ON_EVENT(CTestFuncDlg, IDC_PRIKAZRASPOREDAISPITACTRL1, 1 /* RowSelected */, OnRowSelectedList, VTS_I2)
	ON_EVENT(CTestFuncDlg, IDC_PRIKAZRASPOREDAISPITACTRL1, 2 /* ColSelected */, OnColSelectedList, VTS_I2)
	ON_EVENT(CTestFuncDlg, IDC_PRIKAZRASPOREDAISPITACTRL1, 3 /* TermSelected */, OnTermSelectedList, VTS_I2 VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CTestFuncDlg::OnRowSelectedList(short RowNum) 
{
	// TODO: Add your control notification handler code here
	
}

void CTestFuncDlg::OnColSelectedList(short ColNum) 
{
	// TODO: Add your control notification handler code here
	
}

void CTestFuncDlg::OnTermSelectedList(short RowNum, short ColNum) 
{
	// TODO: Add your control notification handler code here
	
}


void CTestFuncDlg::OnShowBestCrom() 
{
	int		i, j, term;

	if( pBestTotal != NULL ) {
		CDC	*pDC = GetDC();
		CString	str;
		char	s[100];
		sprintf(s, "BestCrom = %15.7f,                 ", pBestTotal->GetFuncValue() );
		str = s;
		pDC->TextOut(20,550,str);

		for( i=0; i<ExamNum; i++ ) 
		{
			m_ctrlList.ClearRowData(i);
			for( j=0; j<SubPeriodNum; j++ ) {
				term = (*pBestTotal)[i][j];
				m_ctrlList.AddRowTerm(i,term);
			}
		}
		m_ctrlList.RedrawWindow();

	}
}

void CTestFuncDlg::OnShowGraph() 
{
	int		i, j;
	CDlgGraph		*pDlg;

	pDlg = new CDlgGraph();
	
	if( bIsAllocated == true ) {
		int			PntNum = IterNum/100 + 1;
		
		double	*x = new double[PntNum];
		double	*y[10];
		double	*yBest = new double[PntNum];

		for( i=0; i<10; i++ )
			y[i] = new double[PntNum];

		// ovdje æemo popuniti y-koordinate i y-koordinate najbolje jedinke
		for( i=0; i<PntNum; i++ ) {
			x[i] = IterNum/1000 * i;
			yBest[i] = matSolEvol[BestInd][i].p->GetFuncValue();
		}
		
		// a ovdje æemo popuniti podatke za još neke jedinke
		for( j=0; j<10; j++ )
			for( i=0; i<PntNum; i++ ) {
				y[j][i] = matSolEvol[j][i].p->GetFuncValue();
			}

		pDlg->m_ctrlGraph.SetStartX(0);
		pDlg->m_ctrlGraph.SetEndX(IterNum);

		pDlg->m_ctrlGraph.AddNewGraphWithX(x, yBest, PntNum, "Najbolja jedinka");
		for( i=0; i<10; i++ )
			pDlg->m_ctrlGraph.AddNewGraph(y[i], PntNum, "Jedinka");

		pDlg->m_ctrlGraph.RedrawWindow();

		delete []x;
		delete []yBest;
		for( i=0; i<10; i++ )
			delete []y[i];
	}
}
