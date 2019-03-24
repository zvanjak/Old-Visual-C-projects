// DlgOptimizationSimAnnealing.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgOptimizationSimAnnealing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationSimAnnealing dialog


CDlgOptimizationSimAnnealing::CDlgOptimizationSimAnnealing(CQAPSolverDoc	*p, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptimizationSimAnnealing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptimizationSimAnnealing)
	m_nCallBackPeriod = 250;
	m_fAcceptHigherProb = 0.99f;
	m_fTempChangeFactor = 0.99f;
	m_nSaveResPeriod = 50;
	m_nIterNum = 15000;
	m_nPermNum = 100;
	m_nOptimDuration = 0;
	m_fReachedValue = 0.0f;
	//}}AFX_DATA_INIT

	Create(IDD_OPTIMIZATION_SIM_ANNEALING, pParent);

	pDoc = p;
	pQAPSimAnnSolver = NULL;

	RefreshInProgress = false;

	m_ctrlCheckIterNum.SetCheck(TRUE);
}


void CDlgOptimizationSimAnnealing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptimizationSimAnnealing)
	DDX_Control(pDX, IDC_CHECK_REACHED_VALUE, m_ctrlCheckReachedValue);
	DDX_Control(pDX, IDC_CHECK_OPTIM_DURATION, m_ctrlCheckOptimDuration);
	DDX_Control(pDX, IDC_CHECK_ITER_NUM, m_ctrlCheckIterNum);
	DDX_Control(pDX, IDC_INFO_ITER_NUM, m_ctrlIterNum);
	DDX_Control(pDX, IDC_INFO_MAX_VALUE, m_ctrlMaxValue);
	DDX_Control(pDX, IDC_INFO_MAX_SOL, m_ctrlMaxSol);
	DDX_Control(pDX, IDC_INFO_DURATION, m_ctrlDuration);
	DDX_Control(pDX, IDC_INFO_CURR_VALUE, m_ctrlCurrValue);
	DDX_Control(pDX, IDC_INFO_CURR_SOL, m_ctrlCurrSol);
	DDX_Control(pDX, IDC_CMD_USE_NEW_PARAM, m_ctrlCmdUseNew);
	DDX_Control(pDX, IDC_CMD_STOP, m_ctrlCmdStop);
	DDX_Control(pDX, IDC_CMD_START, m_ctrlCmdStart);
	DDX_Control(pDX, IDC_CMD_CONTINUE, m_ctrlCmdContinue);
	DDX_Control(pDX, IDC_SOLUTION, m_ctrlSol);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_PERIOD, m_nCallBackPeriod);
	DDX_Text(pDX, IDC_EDIT_ACCEPT_HIGHER_PROB, m_fAcceptHigherProb);
	DDX_Text(pDX, IDC_EDIT_TEMP_CHANGE_FACTOR, m_fTempChangeFactor);
	DDX_Text(pDX, IDC_EDIT_SAVE_RESULTS_PERIOD, m_nSaveResPeriod);
	DDX_Text(pDX, IDC_EDIT_ITER_NUM, m_nIterNum);
	DDX_Text(pDX, IDC_EDIT_PERM_NUM, m_nPermNum);
	DDX_Text(pDX, IDC_EDIT_OPTIM_DURATION, m_nOptimDuration);
	DDX_Text(pDX, IDC_EDIT_REACHED_VALUE, m_fReachedValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptimizationSimAnnealing, CDialog)
	//{{AFX_MSG_MAP(CDlgOptimizationSimAnnealing)
	ON_BN_CLICKED(IDC_CMD_CONTINUE, OnContinueOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_START, OnStartOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_STOP, OnStopOptimizationCmd)
	ON_BN_CLICKED(IDC_CMD_USE_NEW_PARAM, OnUseNewParametersCmd)
	ON_BN_CLICKED(IDC_CHECK_ITER_NUM, OnCheckIterNum)
	ON_BN_CLICKED(IDC_CHECK_OPTIM_DURATION, OnCheckOptimDuration)
	ON_BN_CLICKED(IDC_CHECK_REACHED_VALUE, OnCheckReachedValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationSimAnnealing message handlers


void CDlgOptimizationSimAnnealing::OnStartOptimizationCmd() 
{
	ASSERT(pDoc!=NULL);		// mora dijalogu biti pridružena Doc klasa

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
	EnableEditCtrl(this, IDC_CHECK_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_CHECK_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_CHECK_REACHED_VALUE, FALSE);

	IOptTerminator	*pTermObj = NULL;

//	AfxMessageBox("Ulazak u Start");

	// najprije kreiramo objekt
	if( pQAPSimAnnSolver  == NULL ) 
	{
/*
		char		str[200];
		sprintf(str, "%ld, %ld, %f", m_nIterNum, m_nOptimDuration, m_fReachedValue );
		AfxMessageBox(str);
*/

		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		if( pTermObj == NULL )
			AfxMessageBox("NULL");

		pQAPSimAnnSolver = new ThreadableSimAnnealingQAPSolver(pDoc->getProblemSize(), pTermObj, m_fAcceptHigherProb, m_fTempChangeFactor, m_nPermNum);

		pQAPSimAnnSolver->setA(*pDoc->getA());
		pQAPSimAnnSolver->setB(*pDoc->getB());
/*
		pQAPSimAnnSolver->SetRefreshCallBack(this);
		pQAPSimAnnSolver->SetRefreshCallBackPeriod(m_nCallBackPeriod);
		pQAPSimAnnSolver->SetSaveResultsPeriod(m_nSaveResPeriod);
*/
	}
	else {
		// znaèi da je dijalog veæ bi otvoren, pa je možda samo došlo do promjene parametara
		pQAPSimAnnSolver->SetAcceptHigherProb(m_fAcceptHigherProb);
		pQAPSimAnnSolver->SetTempChangeFactor(m_fTempChangeFactor);
		pQAPSimAnnSolver->SetPermNum(m_nPermNum);
/*
		pQAPSimAnnSolver->SetRefreshCallBackPeriod(m_nCallBackPeriod);
		pQAPSimAnnSolver->SetSaveResultsPeriod(m_nSaveResPeriod);
*/

		// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		pQAPSimAnnSolver->SetOptTerminatorObject(pTermObj);
	}

	ThreadParam		*par = new ThreadParam(pDoc, pQAPSimAnnSolver);
	pQAPSimAnnSolver->Start(this->SimAnnealingThreadFunc, par);
}

UINT	CDlgOptimizationSimAnnealing::SimAnnealingThreadFunc( LPVOID pParam )
{
	ThreadParam		*Par = static_cast<ThreadParam*>(pParam);

	ThreadableSimAnnealingQAPSolver	*pQAP = static_cast<ThreadableSimAnnealingQAPSolver *> (Par->pQAP);
	CQAPSolverDoc										*pDoc = static_cast<CQAPSolverDoc *> (Par->pDoc);

	ASSERT(pQAP!=NULL);
	ASSERT(pDoc!=NULL);

	IterOptContResWithSolutions<float,QAPSolution> *opt = new IterOptContResWithSolutions<float,QAPSolution>(); 

	//	opt->setSaveResPeriod(pQAP->GetSaveResultsPeriod());
	
	// TODO - kako zapisati da su se parametri tijekom optimizacije mijenjali
	AlgDescription	alg("Sim.annealing ", "Simple " );
	alg.setAutomaticOptID();
	alg.addParam("Accept.prob. ", (float) pQAP->GetAcceptHigherProb(), "%.3f", 'F' );
	alg.addParam("Temp.change factor ", (float) pQAP->GetTempChangeFactor(), "%.3f", 'F' );
	alg.addParam("Perm.num. ", (long) pQAP->GetPermNum(), "%ld", 'I' );

	pQAP->Optimize(opt);

	// spremi rezultat u CDocument klasu
	pDoc->AddOptimizationResult(*opt, alg);

	// nakon završetka optimizacije, reci svima da je gotovo
	SetEvent(pQAP->getEventHandle());

	delete opt;
	delete Par;

	return 1;
}

void CDlgOptimizationSimAnnealing::OnStopOptimizationCmd() 
{
	if( pQAPSimAnnSolver != NULL ) {
		while( RefreshInProgress == true )
			Sleep(1000);

		pQAPSimAnnSolver->Stop();

		m_ctrlCmdContinue.EnableWindow(TRUE);
		m_ctrlCmdUseNew.EnableWindow(TRUE);

		EnableEditCtrl(this, IDC_EDIT_PERM_NUM, TRUE);
		EnableEditCtrl(this, IDC_EDIT_ACCEPT_HIGHER_PROB, TRUE);
		EnableEditCtrl(this, IDC_EDIT_TEMP_CHANGE_FACTOR, TRUE);

		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_ITER_NUM, TRUE);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, TRUE);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, TRUE);
	}
}

void CDlgOptimizationSimAnnealing::OnContinueOptimizationCmd() 
{
	pQAPSimAnnSolver->Continue();

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_PERM_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_ACCEPT_HIGHER_PROB, FALSE);
	EnableEditCtrl(this, IDC_EDIT_TEMP_CHANGE_FACTOR, FALSE);

	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
}

void CDlgOptimizationSimAnnealing::OnUseNewParametersCmd() 
{
	float	OldAcceptHigherProb = m_fAcceptHigherProb;
	float	OldTempChangeFactor = m_fTempChangeFactor;
	long	OldPermNum = m_nPermNum;

	long	OldIterNum = m_nIterNum;
	float	OldOptimDuration = m_nOptimDuration;
	float	OldReachedValue = m_fReachedValue;

	UpdateData();

	if( pQAPSimAnnSolver != NULL ) {
		if( m_fAcceptHigherProb != OldAcceptHigherProb )
			pQAPSimAnnSolver->SetAcceptHigherProb(m_fAcceptHigherProb);
		if( m_fTempChangeFactor != OldTempChangeFactor )
			pQAPSimAnnSolver->SetTempChangeFactor(m_fTempChangeFactor);
		if( m_nPermNum != OldPermNum ) 
			pQAPSimAnnSolver->SetPermNum(m_nPermNum);

		if( m_ctrlCheckIterNum.GetCheck() == TRUE && m_nIterNum != OldIterNum ) {
				IterativeOptTerminator	*temp = new IterativeOptTerminator(m_nIterNum);
				pQAPSimAnnSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE && m_nOptimDuration != OldOptimDuration ) {
				TimeOptTerminator	*temp = new TimeOptTerminator(m_nOptimDuration);
				pQAPSimAnnSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE && m_fReachedValue != OldReachedValue ) {
				ConvergedFromUpOptTerminator	*temp = new ConvergedFromUpOptTerminator(m_fReachedValue);
				pQAPSimAnnSolver->SetOptTerminatorObject(temp);
		}
	}
}


void CDlgOptimizationSimAnnealing::OnCancel() 
{
	if( pQAPSimAnnSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		while( RefreshInProgress == true )
			Sleep(1000);

		if( pQAPSimAnnSolver->IsInProgress() == true )
			pQAPSimAnnSolver->Terminate();
	}
	
	if( pQAPSimAnnSolver != NULL )
		delete pQAPSimAnnSolver;

	DestroyWindow();
}

void CDlgOptimizationSimAnnealing::OnOK() 
{
	if( pQAPSimAnnSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		while( RefreshInProgress == true )
			Sleep(1000);

		if( pQAPSimAnnSolver->IsInProgress() == true ) {
			pQAPSimAnnSolver->Terminate();
		}
	}
	
	if( pQAPSimAnnSolver != NULL )
		delete pQAPSimAnnSolver;
	
	CDialog::OnOK();
}

void CDlgOptimizationSimAnnealing::PostNcDestroy() 
{
	delete this;	

	CDialog::PostNcDestroy();
}

///////////////////////////////////////////////////////////////////////////////////////

void CDlgOptimizationSimAnnealing::Refresh(IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol )
{
	// sada treba iz najnovijih rješenja koja smo primili u parametru res, 
	// osvježiti podatke u dijalogu
	int		i, term;
	char	str[100], strCurrSol[500], strMaxSol[500], hsol[10];
	int		Min, Sec, Msec;
	float	Duration;

	RefreshInProgress = true;

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
	}
	m_ctrlSol.DrawItself();

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

	RefreshInProgress = false;
}

void CDlgOptimizationSimAnnealing::OnCheckIterNum() 
{
	m_ctrlCheckIterNum.SetCheck(TRUE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationSimAnnealing::OnCheckOptimDuration() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(TRUE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationSimAnnealing::OnCheckReachedValue() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(TRUE);
}
