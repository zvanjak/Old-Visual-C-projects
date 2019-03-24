// DlgOptimizationTabuSearch.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgOptimizationTabuSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationTabuSearch dialog


CDlgOptimizationTabuSearch::CDlgOptimizationTabuSearch(CQAPSolverDoc	*p,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptimizationTabuSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptimizationTabuSearch)
	m_nIterNum = 5000;
	m_nTabuListSize = 30;
	m_nCallBackPeriod = 100;
	m_nSaveResPeriod = 100;
	m_nOptimDuration = 0;
	m_fReachedValue = 0.0f;
	//}}AFX_DATA_INIT

	Create(IDD_OPTIMIZATION_TABU_SEARCH, pParent);

	pDoc = p;
	pQAPTabuSearchSolver= NULL;

	m_ctrlCheckIterNum.SetCheck(TRUE);
}


void CDlgOptimizationTabuSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptimizationTabuSearch)
	DDX_Control(pDX, IDC_CHECK_REACHED_VALUE, m_ctrlCheckReachedValue);
	DDX_Control(pDX, IDC_CHECK_OPTIM_DURATION, m_ctrlCheckOptimDuration);
	DDX_Control(pDX, IDC_CHECK_ITER_NUM, m_ctrlCheckIterNum);
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
	DDX_Text(pDX, IDC_EDIT_ITER_NUM, m_nIterNum);
	DDX_Text(pDX, IDC_EDIT_TABU_LIST_SIZE, m_nTabuListSize);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_PERIOD, m_nCallBackPeriod);
	DDX_Text(pDX, IDC_EDIT_SAVE_RESULTS_PERIOD, m_nSaveResPeriod);
	DDX_Text(pDX, IDC_EDIT_OPTIM_DURATION, m_nOptimDuration);
	DDX_Text(pDX, IDC_EDIT_REACHED_VALUE, m_fReachedValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptimizationTabuSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgOptimizationTabuSearch)
	ON_BN_CLICKED(IDC_CMD_START, OnStartOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_STOP, OnStopOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_USE_NEW_PARAMETERS, OnUseNewParametersCmd)
	ON_BN_CLICKED(IDC_CMD_CONTINUE, OnCmdContinue)
	ON_BN_CLICKED(IDC_CHECK_ITER_NUM, OnCheckIterNum)
	ON_BN_CLICKED(IDC_CHECK_OPTIM_DURATION, OnCheckOptimDuration)
	ON_BN_CLICKED(IDC_CHECK_REACHED_VALUE, OnCheckReachedValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationTabuSearch message handlers
void CDlgOptimizationTabuSearch::OnStartOptimizationCmd() 
{
	ASSERT(pDoc!=NULL);		// mora dijalogu biti pridružena Doc klasa

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_TABU_LIST_SIZE, FALSE);

	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
	EnableEditCtrl(this, IDC_CHECK_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_CHECK_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_CHECK_REACHED_VALUE, FALSE);

	IOptTerminator	*pTermObj;

	// najprije kreiramo objekt
	if( pQAPTabuSearchSolver == NULL ) 
	{
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		pQAPTabuSearchSolver = new ThreadableRobustTabuSearchQAPSolver(pDoc->getProblemSize(), pTermObj, m_nTabuListSize );

		pQAPTabuSearchSolver->setA(*pDoc->getA());
		pQAPTabuSearchSolver->setB(*pDoc->getB());
/*
		pQAPTabuSearchSolver->SetRefreshCallBack(this);
		pQAPTabuSearchSolver->SetRefreshCallBackPeriod(m_nCallBackPeriod);
		pQAPTabuSearchSolver->SetSaveResultsPeriod(m_nSaveResPeriod);
*/
	}
	else {
		// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
		pQAPTabuSearchSolver->setTabuListSize(m_nTabuListSize);
		
		// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		pQAPTabuSearchSolver->SetOptTerminatorObject(pTermObj);
	}

	ThreadParam		*par = new ThreadParam(pDoc, pQAPTabuSearchSolver );
	pQAPTabuSearchSolver->Start(this->TabuSearchThreadFunc, par);
}

UINT	CDlgOptimizationTabuSearch::TabuSearchThreadFunc( LPVOID pParam )
{
	ThreadParam		*Par = static_cast<ThreadParam*>(pParam);

	ThreadableRobustTabuSearchQAPSolver	*pQAP = static_cast<ThreadableRobustTabuSearchQAPSolver *> (Par->pQAP);
	CQAPSolverDoc									*pDoc = static_cast<CQAPSolverDoc *> (Par->pDoc);

	ASSERT(pQAP!=NULL);
	ASSERT(pDoc!=NULL);

	IterOptContResWithSolutions<float,QAPSolution> *opt = new IterOptContResWithSolutions<float,QAPSolution>(); 
//	opt->setSaveResPeriod(pQAP->GetSaveResultsPeriod());
	
	// TODO - kako zapisati da su se parametri tijekom optimizacije mijenjali
	AlgDescription	alg("Tabu search ", "Simple " );
	alg.setAutomaticOptID();
	alg.addParam("Tabu list size ", (long)pQAP->getTabuListSize(), "%ld", 'I' );

	pQAP->Optimize(opt);

	// spremi rezultat u CDocument klasu
	pDoc->AddOptimizationResult(*opt, alg);

	pQAP->OptimizationFinished();

	// nakon završetka optimizacije, reci svima da je gotovo
	SetEvent(pQAP->getEventHandle());

	delete opt;
	delete Par;

	return 1;
}

void CDlgOptimizationTabuSearch::OnStopOptimizationCmd() 
{
	if( pQAPTabuSearchSolver != NULL ) {
		pQAPTabuSearchSolver->Stop();

		m_ctrlCmdContinue.EnableWindow(TRUE);
		m_ctrlCmdUseNew.EnableWindow(TRUE);

		EnableEditCtrl(this, IDC_EDIT_TABU_LIST_SIZE, TRUE);

		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_ITER_NUM, TRUE);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, TRUE);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, TRUE);
	}
}

void CDlgOptimizationTabuSearch::OnCmdContinue() 
{
	pQAPTabuSearchSolver->Continue();

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_TABU_LIST_SIZE, FALSE);

	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
}

void CDlgOptimizationTabuSearch::OnUseNewParametersCmd() 
{
	int		OldTabuListSize = m_nTabuListSize;

	long	OldIterNum = m_nIterNum;
	float	OldOptimDuration = m_nOptimDuration;
	float	OldReachedValue = m_fReachedValue;

	UpdateData();	

	if( pQAPTabuSearchSolver != NULL ) {
		if( m_nTabuListSize != OldTabuListSize ) 
			pQAPTabuSearchSolver->setTabuListSize(m_nTabuListSize);

		if( m_ctrlCheckIterNum.GetCheck() == TRUE && m_nIterNum != OldIterNum ) 
		{
				IterativeOptTerminator	*temp = new IterativeOptTerminator(m_nIterNum);
				pQAPTabuSearchSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE && m_nOptimDuration != OldOptimDuration ) 
		{
				TimeOptTerminator	*temp = new TimeOptTerminator(m_nOptimDuration);
				pQAPTabuSearchSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE && m_fReachedValue != OldReachedValue ) 
		{
				ConvergedFromUpOptTerminator	*temp = new ConvergedFromUpOptTerminator(m_fReachedValue);
				pQAPTabuSearchSolver->SetOptTerminatorObject(temp);
		}
	}
}

void CDlgOptimizationTabuSearch::OnCancel() 
{
	if( pQAPTabuSearchSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		if( pQAPTabuSearchSolver->IsInProgress() == true )
			pQAPTabuSearchSolver->Terminate();
	}
	
	if( pQAPTabuSearchSolver != NULL )
		delete pQAPTabuSearchSolver;

	DestroyWindow();
}

void CDlgOptimizationTabuSearch::OnOK() 
{
	// problem ukoliko je nit zaustavljena a mi kliknemo na OK(Cancel)
	if( pQAPTabuSearchSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		if( pQAPTabuSearchSolver->IsInProgress() == true )
			pQAPTabuSearchSolver->Terminate();
	}

	if( pQAPTabuSearchSolver != NULL )
		delete pQAPTabuSearchSolver;

	CDialog::OnOK();
}

void CDlgOptimizationTabuSearch::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}

void CDlgOptimizationTabuSearch::Refresh(IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol )
{
	// sada treba iz najnovijih rješenja koja smo primili u parametru res, 
	// osvježiti podatke u dijalogu
	int		i, term;
	char	str[100], strCurrSol[500], strMaxSol[500], hsol[10];
	int		Min, Sec, Msec;
	float	Duration;

	memset(str, 0, 100);
	memset(strCurrSol, 0, 200);
	memset(strMaxSol, 0, 200);

	m_ctrlSol.ClearAllData();

	for( i=0; i<pDoc->getProblemSize(); i++ ) {
		term = (*BestSol)(i);
		sprintf(hsol, " %2d ", term+1);
		strcat(strMaxSol, hsol);

		term = res->getSolution()(i);
		sprintf(hsol, " %2d ", term+1);
		strcat(strCurrSol, hsol);

		m_ctrlSol.AddRowTerm(i, term);
		m_ctrlSol.DrawItself();
	}

	m_ctrlCurrSol.SetWindowText(strCurrSol);
	m_ctrlMaxSol.SetWindowText(strMaxSol);

	sprintf(str, "%f",  res->getFuncValue());
	m_ctrlCurrValue.SetWindowText(str);

	sprintf(str, "%f",  Best);
	m_ctrlMaxValue.SetWindowText(str);

	Duration = res->getOptimDuration();
	Min  = Duration/60000;
	Sec  = (Duration - Min*60000) / 1000;
	Msec = ((long) Duration) % 1000;
	sprintf(str, "%02d:%02d:%03d", Min, Sec, Msec  );
	m_ctrlDuration.SetWindowText(str);

	sprintf(str, "%ld", res->getIterNum() );
	m_ctrlIterNum.SetWindowText(str);
}

void CDlgOptimizationTabuSearch::OnCheckIterNum() 
{
	m_ctrlCheckIterNum.SetCheck(TRUE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationTabuSearch::OnCheckOptimDuration() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(TRUE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationTabuSearch::OnCheckReachedValue() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(TRUE);
}
