// DlgGeneric.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgGeneric.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGeneric dialog

CDlgGeneric::CDlgGeneric( CQAPSolverDoc	*p, CWnd* pParent /*=NULL*/)
: CDialog(CDlgGeneric::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGeneric)
	m_nTermIterNum = 10000;
	m_nCallbackIterNum = 100;
	m_nCallbackMillisec = 1000;
	m_nSaveIterNum = 10;
	m_nSaveMillisec = 100;
	m_nTermOptimDuration = 10000;
	m_fTermReachedValue = 0.0f;
	//}}AFX_DATA_INIT

	Create(IDD_GENERIC_ITERATIVE_OPT, pParent);

	pDoc = p;
	pExch = NULL;
	RefreshInProgress = false;

	m_ctrlCheckTermIterNum.SetCheck(TRUE);
	m_ctrlCheckCallbackIterNum.SetCheck(TRUE);
	m_ctrlCheckSaveIterNum.SetCheck(TRUE);

	m_ctrlCheckCallbackEveryImprovement.SetCheck(FALSE);
	m_ctrlCheckSaveEveryImprovement.SetCheck(TRUE);
}


void CDlgGeneric::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGeneric)
	DDX_Control(pDX, IDC_CMD_PERFORM_INITAL, m_ctrlCmdPerformInitial);
	DDX_Control(pDX, IDC_CHECK_SAVE_EVERY_IMPROVEMENT, m_ctrlCheckSaveEveryImprovement);
	DDX_Control(pDX, IDC_CHECK_CALLBACK_EVERY_IMPROVEMENT, m_ctrlCheckCallbackEveryImprovement);
	DDX_Control(pDX, IDC_CHECK_CALLBACK_MILISEC, m_ctrlCheckCallbackMillisec);
	DDX_Control(pDX, IDC_CHECK_CALLBACK_ITERNUM, m_ctrlCheckCallbackIterNum);
	DDX_Control(pDX, IDC_CHECK_SAVE_MILISEC, m_ctrlCheckSaveMillisec);
	DDX_Control(pDX, IDC_CHECK_SAVE_ITERNUM, m_ctrlCheckSaveIterNum);
	DDX_Control(pDX, IDC_CHECK_TERM_REACHED_VALUE, m_ctrlCheckTermReachedValue);
	DDX_Control(pDX, IDC_CHECK_TERM_OPTIM_DURATION, m_ctrlCheckTermOptimDuration);
	DDX_Control(pDX, IDC_CHECK_TERM_ITER_NUM, m_ctrlCheckTermIterNum);
	DDX_Control(pDX, IDC_CMD_USE_NEW_PARAMETERS, m_ctrlCmdUseNew);
	DDX_Control(pDX, IDC_CMD_STOP, m_ctrlCmdStop);
	DDX_Control(pDX, IDC_CMD_START, m_ctrlCmdStart);
	DDX_Control(pDX, IDC_CMD_CONTINUE, m_ctrlCmdContinue);
	DDX_Control(pDX, IDC_INFO_ITER_NUM, m_ctrlIterNum);
	DDX_Control(pDX, IDC_INFO_MAX_VALUE, m_ctrlMaxValue);
	DDX_Control(pDX, IDC_INFO_MAX_SOL, m_ctrlMaxSol);
	DDX_Control(pDX, IDC_INFO_DURATION, m_ctrlDuration);
	DDX_Control(pDX, IDC_INFO_CURR_VALUE, m_ctrlCurrValue);
	DDX_Control(pDX, IDC_INFO_CURR_SOL, m_ctrlCurrSol);
	DDX_Control(pDX, IDC_SOLUTION, m_ctrlSol);
	DDX_Text(pDX, IDC_EDIT_TERM_ITER_NUM, m_nTermIterNum);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_ITERNUM, m_nCallbackIterNum);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_MILISEC, m_nCallbackMillisec);
	DDX_Text(pDX, IDC_EDIT_SAVE_ITERNUM, m_nSaveIterNum);
	DDX_Text(pDX, IDC_EDIT_SAVE_MILISEC, m_nSaveMillisec);
	DDX_Text(pDX, IDC_EDIT_TERM_OPTIM_DURATION, m_nTermOptimDuration);
	DDX_Text(pDX, IDC_EDIT_TERM_REACHED_VALUE, m_fTermReachedValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGeneric, CDialog)
	//{{AFX_MSG_MAP(CDlgGeneric)
	ON_BN_CLICKED(IDC_CMD_START, OnStartOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_STOP, OnStopOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_USE_NEW_PARAMETERS, OnUseNewParametersCmd)
	ON_BN_CLICKED(IDC_CMD_CONTINUE, OnCmdContinue)
	ON_BN_CLICKED(IDC_CHECK_TERM_ITER_NUM, OnCheckTermIterNum)
	ON_BN_CLICKED(IDC_CHECK_TERM_OPTIM_DURATION, OnCheckTermOptimDuration)
	ON_BN_CLICKED(IDC_CHECK_TERM_REACHED_VALUE, OnCheckTermReachedValue)
  ON_MESSAGE(WM_REFRESH_MESSAGE , OnRefreshMessage)
	ON_BN_CLICKED(IDC_CHECK_CALLBACK_ITERNUM, OnCheckCallbackIternum)
	ON_BN_CLICKED(IDC_CHECK_CALLBACK_MILISEC, OnCheckCallbackMilisec)
	ON_BN_CLICKED(IDC_CHECK_SAVE_ITERNUM, OnCheckSaveIternum)
	ON_BN_CLICKED(IDC_CHECK_SAVE_MILISEC, OnCheckSaveMilisec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGeneric message handlers

IOptTerminator	*CDlgGeneric::GetTermObj() 
{
	IOptTerminator	*pTermObj;

	if( m_ctrlCheckTermIterNum.GetCheck() == TRUE ) 
		pTermObj = new IterativeOptTerminator(m_nTermIterNum);
	if( m_ctrlCheckTermOptimDuration.GetCheck() == TRUE ) 
		pTermObj = new TimeOptTerminator(m_nTermOptimDuration);
	if( m_ctrlCheckTermReachedValue.GetCheck() == TRUE ) 
		pTermObj = new ConvergedFromUpOptTerminator(m_fTermReachedValue);

	return pTermObj;
}

OptRefreshMultiThread<float, QAPSolution>	*CDlgGeneric::GetRefreshObj()
{
	OptRefreshMultiThread<float, QAPSolution>	*pRefreshObj;

	if( m_ctrlCheckCallbackIterNum.GetCheck() == TRUE ) 
		pRefreshObj = new IterativeRefresherMT<float, QAPSolution>(m_nCallbackIterNum);
	
	if( m_ctrlCheckCallbackMillisec.GetCheck() == TRUE ) 
		pRefreshObj = new TimeRefresherMT<float, QAPSolution>(m_nCallbackMillisec);

	if( m_ctrlCheckCallbackEveryImprovement.GetCheck() == TRUE )
		pRefreshObj->SetRefreshOnEveryImprovement(true);
	else
		pRefreshObj->SetRefreshOnEveryImprovement(false);

	return pRefreshObj;
}

IOptSaver<float, QAPSolution>	*CDlgGeneric::GetSaveObj()
{
	IOptSaver<float, QAPSolution>	*pSaveObj;

	if( m_ctrlCheckSaveIterNum.GetCheck() == TRUE ) 
		pSaveObj = new IterativeOptSaver<float, QAPSolution>(m_nSaveIterNum);
	if( m_ctrlCheckSaveMillisec.GetCheck() == TRUE ) 
		pSaveObj = new TimeOptSaver<float, QAPSolution>(m_nSaveMillisec);

	if( m_ctrlCheckSaveEveryImprovement.GetCheck() == TRUE )
		pSaveObj->SetSaveOnEveryImprovement(true);
	else
		pSaveObj->SetSaveOnEveryImprovement(false);

	return pSaveObj;
}

void CDlgGeneric::OnStartOptimizationCmd() 
{
//	ASSERT(pDoc!=NULL);		// mora dijalogu biti pridružena Doc klasa

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_TERM_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_TERM_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_TERM_REACHED_VALUE, FALSE);
	EnableEditCtrl(this, IDC_CHECK_TERM_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_CHECK_TERM_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_CHECK_TERM_REACHED_VALUE, FALSE);

	OnStart();
}


void CDlgGeneric::OnStopOptimizationCmd() 
{
	OnStop();
}

void CDlgGeneric::OnCmdContinue() 
{
	OnContinue();

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

//	EnableEditCtrl(this, TABU_SEARCH_EDIT_TABULIST_SIZE, FALSE);

	EnableEditCtrl(this, IDC_EDIT_TERM_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_TERM_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_TERM_REACHED_VALUE, FALSE);
}

void CDlgGeneric::OnUseNewParametersCmd() 
{
	OnUseNewParameters();
}

void CDlgGeneric::OnCancel() 
{
	OnGenericCancel();

	DestroyWindow();
}

void CDlgGeneric::OnOK() 
{
	OnGenericOK();

	CDialog::OnOK();
}

void CDlgGeneric::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}

void CDlgGeneric::Refresh(IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol )
{
//ostMessage(WM_REFRESH_MESSAGE);
}

void CDlgGeneric::OnCheckTermIterNum() 
{
	m_ctrlCheckTermIterNum.SetCheck(TRUE);
	m_ctrlCheckTermOptimDuration.SetCheck(FALSE);
	m_ctrlCheckTermReachedValue.SetCheck(FALSE);
}

void CDlgGeneric::OnCheckTermOptimDuration() 
{
	m_ctrlCheckTermIterNum.SetCheck(FALSE);
	m_ctrlCheckTermOptimDuration.SetCheck(TRUE);
	m_ctrlCheckTermReachedValue.SetCheck(FALSE);
}

void CDlgGeneric::OnCheckTermReachedValue() 
{
	m_ctrlCheckTermIterNum.SetCheck(FALSE);
	m_ctrlCheckTermOptimDuration.SetCheck(FALSE);
	m_ctrlCheckTermReachedValue.SetCheck(TRUE);
}

void CDlgGeneric::OnCheckCallbackIternum() 
{
	m_ctrlCheckCallbackIterNum.SetCheck(TRUE);
	m_ctrlCheckCallbackMillisec.SetCheck(FALSE);
}

void CDlgGeneric::OnCheckCallbackMilisec() 
{
	m_ctrlCheckCallbackIterNum.SetCheck(FALSE);
	m_ctrlCheckCallbackMillisec.SetCheck(TRUE);
}

void CDlgGeneric::OnCheckSaveIternum() 
{
	m_ctrlCheckSaveMillisec.SetCheck(FALSE);
	m_ctrlCheckSaveIterNum.SetCheck(TRUE);
}

void CDlgGeneric::OnCheckSaveMilisec() 
{
	m_ctrlCheckSaveMillisec.SetCheck(TRUE);
	m_ctrlCheckSaveIterNum.SetCheck(FALSE);
}

LRESULT	CDlgGeneric::OnRefreshMessage(WPARAM wParam, LPARAM lParam)
{
	// sada treba iz najnovijih rješenja koja smo primili u parametru res, 
	// osvježiti podatke u dijalogu
	int		i, term;
	char	str[100], strCurrSol[500], strMaxSol[500], hsol[10];
	int		Min, Sec, Msec;
	float	Duration;

	IterativeOptRes<float, QAPSolution>		CurrSol;	
	float				BestValue;
	QAPSolution	BestSolution;
	
	RefreshInProgress = true;

	memset(str, 0, 100);
	memset(strCurrSol, 0, 200);
	memset(strMaxSol, 0, 200);

	m_ctrlSol.ClearAllData();

	for( i=0; i<pDoc->getProblemSize(); i++ ) {
/*	TO DO - Max solution
		sprintf(hsol, " %2d ", term+1);
		strcat(strMaxSol, hsol);
*/
		pExch->GetResult(&CurrSol, &BestValue, &BestSolution);
		term = CurrSol.getSolution()(i);
		sprintf(hsol, " %2d ", term+1);
		strcat(strCurrSol, hsol);

		m_ctrlSol.AddRowTerm(i, term);
	}
	m_ctrlSol.DrawItself();

	m_ctrlCurrSol.SetWindowText(strCurrSol);
	m_ctrlMaxSol.SetWindowText(strMaxSol);

	sprintf(str, "%f",  CurrSol.getFuncValue() );
	m_ctrlCurrValue.SetWindowText(str);

	sprintf(str, "%f",  BestValue);
	m_ctrlMaxValue.SetWindowText(str);

	Duration = CurrSol.getOptimDuration();
	Min  = Duration/60000;
	Sec  = (Duration - Min*60000) / 1000;
	Msec = ((long) Duration) % 1000;
	sprintf(str, "%02d:%02d:%03d", Min, Sec, Msec  );
	m_ctrlDuration.SetWindowText(str);

	sprintf(str, "%ld", CurrSol.getIterNum() );
	m_ctrlIterNum.SetWindowText(str);

	RefreshInProgress = false;

	return 1;
}
