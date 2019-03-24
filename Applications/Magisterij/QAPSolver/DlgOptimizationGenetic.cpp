// DlgOptimizationGenetic.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgOptimizationGenetic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationGenetic dialog


CDlgOptimizationGenetic::CDlgOptimizationGenetic(CQAPSolverDoc	*p, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptimizationGenetic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptimizationGenetic)
	m_fMutProb = 0.01f;
	m_nIterNum = 30000;
	m_nPopSize = 50;
	m_nCallBackPeriod = 500;
	m_nSaveResPeriod = 100;
	m_nOptimDuration = 0;
	m_fReachedValue = 0.0f;
	//}}AFX_DATA_INIT

	Create(IDD_OPTIMIZATION_GENETIC, pParent);

	pDoc = p;
	pQAPGeneticSolver = NULL;

	m_ctrlCheckIterNum.SetCheck(TRUE);
}


void CDlgOptimizationGenetic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptimizationGenetic)
	DDX_Control(pDX, IDC_INFO_CURR_SOL, m_ctrlCurrSol);
	DDX_Control(pDX, IDC_CHECK_REACHED_VALUE, m_ctrlCheckReachedValue);
	DDX_Control(pDX, IDC_CHECK_OPTIM_DURATION, m_ctrlCheckOptimDuration);
	DDX_Control(pDX, IDC_CHECK_ITER_NUM, m_ctrlCheckIterNum);
	DDX_Control(pDX, IDC_INFO_ITER_NUM, m_ctrlIterNum);
	DDX_Control(pDX, IDC_INFO_MAX_VALUE, m_ctrlMaxValue);
	DDX_Control(pDX, IDC_INFO_MAX_SOL, m_ctrlMaxSol);
	DDX_Control(pDX, IDC_INFO_DURATION, m_ctrlDuration);
	DDX_Control(pDX, IDC_INFO_CURR_VALUE, m_ctrlCurrValue);
	DDX_Control(pDX, IDC_CMD_USE_NEW_PARAM, m_ctrlCmdUseNew);
	DDX_Control(pDX, IDC_CMD_STOP, m_ctrlCmdStop);
	DDX_Control(pDX, IDC_CMD_START, m_ctrlCmdStart);
	DDX_Control(pDX, IDC_CMD_CONTINUE, m_ctrlCmdContinue);
	DDX_Control(pDX, IDC_SOLUTION, m_ctrlSol);
	DDX_Text(pDX, IDC_EDIT_MUT_PROB, m_fMutProb);
	DDX_Text(pDX, IDC_EDIT_ITER_NUM, m_nIterNum);
	DDX_Text(pDX, IDC_EDIT_POP_SIZE, m_nPopSize);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_PERIOD, m_nCallBackPeriod);
	DDX_Text(pDX, IDC_EDIT_SAVE_RESULTS_PERIOD, m_nSaveResPeriod);
	DDX_Text(pDX, IDC_EDIT_OPTIM_DURATION, m_nOptimDuration);
	DDX_Text(pDX, IDC_EDIT_REACHED_VALUE, m_fReachedValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptimizationGenetic, CDialog)
	//{{AFX_MSG_MAP(CDlgOptimizationGenetic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizationGenetic message handlers

void CDlgOptimizationGenetic::OnStartOptimizationCmd() 
{
	ASSERT(pDoc!=NULL);		// mora dijalogu biti pridružena Doc klasa

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_POP_SIZE, FALSE);
	EnableEditCtrl(this, IDC_EDIT_MUT_PROB, FALSE);
	
	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
	EnableEditCtrl(this, IDC_CHECK_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_CHECK_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_CHECK_REACHED_VALUE, FALSE);

	IOptTerminator	*pTermObj;

	UpdateData();
	// najprije kreiramo objekt
	if( pQAPGeneticSolver == NULL ) 
	{
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		pQAPGeneticSolver = new ThreadableGeneticQAPSolver(pDoc->getProblemSize(), m_nPopSize, pTermObj, m_fMutProb);

		pQAPGeneticSolver->setA(*pDoc->getA());
		pQAPGeneticSolver->setB(*pDoc->getB());
/*
		pQAPGeneticSolver->SetRefreshCallBack(this);
		pQAPGeneticSolver->SetRefreshCallBackPeriod(m_nCallBackPeriod);
		pQAPGeneticSolver->SetSaveResultsPeriod(m_nSaveResPeriod);
*/
	}
	else {
		// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju

	//	setPopSize je opasan zato što realocira polje kromosoma 
		// - zato se može mijenjati iskljuèivo prije nego što uopæe poène (Start) optimizacije
	//	pQAPGeneticSolver->setPopulationSize(m_nPopSize);
		pQAPGeneticSolver->setMutProb(m_fMutProb);
		
		// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			pTermObj = new IterativeOptTerminator(m_nIterNum);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			pTermObj = new TimeOptTerminator(m_nOptimDuration);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			pTermObj = new ConvergedFromUpOptTerminator(m_fReachedValue);

		pQAPGeneticSolver->SetOptTerminatorObject(pTermObj);
	}

	ThreadParam		*par = new ThreadParam(pDoc, pQAPGeneticSolver);
	pQAPGeneticSolver->Start(this->GeneticThreadFunc, par);
}

UINT	CDlgOptimizationGenetic::GeneticThreadFunc( LPVOID pParam )
{
	ThreadParam		*Par = static_cast<ThreadParam*>(pParam);
	IterOptContResWithSolutions<float,QAPSolution> *opt = new IterOptContResWithSolutions<float,QAPSolution>(); 

	ThreadableGeneticQAPSolver	*pQAP = static_cast<ThreadableGeneticQAPSolver *> (Par->pQAP);
	CQAPSolverDoc								*pDoc = static_cast<CQAPSolverDoc *> (Par->pDoc);

	ASSERT(pQAP!=NULL);
	ASSERT(pDoc!=NULL);

//	opt->setSaveResPeriod(pQAP->GetSaveResultsPeriod());
	
	// TODO - kako zapisati da su se parametri tijekom optimizacije mijenjali
	AlgDescription	alg("Genetic ", "Simple " );
	alg.setAutomaticOptID();
	alg.addParam("Pop.size", (long)pQAP->getPopulationSize(), "%ld", 'I' );
	alg.addParam("Mut.prob", pQAP->getMutProb(), "%f", 'F' );

	pQAP->Optimize(opt);

	// spremi rezultat u CDocument klasu
	pDoc->AddOptimizationResult(*opt, alg);

	// nakon završetka optimizacije, reci svima da je gotovo
	SetEvent(pQAP->getEventHandle());

	delete opt;
	delete Par;

	return 1;
}

void CDlgOptimizationGenetic::OnStopOptimizationCmd() 
{
	if( pQAPGeneticSolver != NULL ) {
		pQAPGeneticSolver->Stop();

		m_ctrlCmdContinue.EnableWindow(TRUE);
		m_ctrlCmdUseNew.EnableWindow(TRUE);

		EnableEditCtrl(this, IDC_EDIT_MUT_PROB, TRUE);

		// neæemo dopustiti da se mijenja broj iteracija nakon što je zaustavljena optimizacija
		// BOLJE - ne bi trebalo dopustiti da se mijenja vrsta Terminatora
		if( m_ctrlCheckIterNum.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_ITER_NUM, TRUE);
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, TRUE);
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE ) 
			EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, TRUE);
	}
}

void CDlgOptimizationGenetic::OnContinueOptimizationCmd() 
{
	pQAPGeneticSolver->Continue();

	m_ctrlCmdContinue.EnableWindow(FALSE);
	m_ctrlCmdUseNew.EnableWindow(FALSE);

	EnableEditCtrl(this, IDC_EDIT_MUT_PROB, FALSE);

	EnableEditCtrl(this, IDC_EDIT_ITER_NUM, FALSE);
	EnableEditCtrl(this, IDC_EDIT_OPTIM_DURATION, FALSE);
	EnableEditCtrl(this, IDC_EDIT_REACHED_VALUE, FALSE);
}

void CDlgOptimizationGenetic::OnUseNewParametersCmd() 
{
	float	OldMutProb = m_fMutProb;
	long	OldIterNum = m_nIterNum;
	float	OldOptimDuration = m_nOptimDuration;
	float	OldReachedValue = m_fReachedValue;
	
	// bitno je da se ova funkcija ne može pozvati za vrijeme izvršavanja niti
	UpdateData();

	if( pQAPGeneticSolver != NULL ) {
		if( m_fMutProb != OldMutProb )
			pQAPGeneticSolver->setMutProb(m_fMutProb);
		
		if( m_ctrlCheckIterNum.GetCheck() == TRUE && m_nIterNum != OldIterNum ) {
				IterativeOptTerminator	*temp = new IterativeOptTerminator(m_nIterNum);
				pQAPGeneticSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckOptimDuration.GetCheck() == TRUE && m_nOptimDuration != OldOptimDuration ) {
				TimeOptTerminator	*temp = new TimeOptTerminator(m_nOptimDuration);
				pQAPGeneticSolver->SetOptTerminatorObject(temp);
			}
		if( m_ctrlCheckReachedValue.GetCheck() == TRUE && m_fReachedValue != OldReachedValue ) {
				ConvergedFromUpOptTerminator	*temp = new ConvergedFromUpOptTerminator(m_fReachedValue);
				pQAPGeneticSolver->SetOptTerminatorObject(temp);
		}
	}
}

void CDlgOptimizationGenetic::OnCancel() 
{
	if( pQAPGeneticSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		if( pQAPGeneticSolver->IsInProgress() == true )
			pQAPGeneticSolver->Terminate();
	}
	
	if( pQAPGeneticSolver != NULL )
		delete pQAPGeneticSolver;

	DestroyWindow();
}

void CDlgOptimizationGenetic::OnOK() 
{
	// problem ukoliko je nit zaustavljena a mi kliknemo na OK(Cancel)
	if( pQAPGeneticSolver != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
		if( pQAPGeneticSolver->IsInProgress() == true ) {
			HANDLE		m_h = AfxGetApp()->m_hThread;
			pQAPGeneticSolver->Terminate();
		}
	}

	if( pQAPGeneticSolver != NULL )
		delete pQAPGeneticSolver;

	CDialog::OnOK();
}

void CDlgOptimizationGenetic::PostNcDestroy() 
{
	delete this;
	
	CDialog::PostNcDestroy();
}

void CDlgOptimizationGenetic::OnCheckIterNum() 
{
	m_ctrlCheckIterNum.SetCheck(TRUE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationGenetic::OnCheckOptimDuration() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(TRUE);
	m_ctrlCheckReachedValue.SetCheck(FALSE);
}

void CDlgOptimizationGenetic::OnCheckReachedValue() 
{
	m_ctrlCheckIterNum.SetCheck(FALSE);
	m_ctrlCheckOptimDuration.SetCheck(FALSE);
	m_ctrlCheckReachedValue.SetCheck(TRUE);
}
///////////////////////////////////////////////////////////////////////////////////////

void CDlgOptimizationGenetic::Refresh(IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol )
{
	// sada treba iz najnovijih rješenja koja smo primili u parametru res, 
	// osvježiti podatke u dijalogu
	int		i, term;
	char	str[100], strCurrSol[500], strMaxSol[500], hsol[10];
	int		Min, Sec, Msec;
	float	Duration;

//	TRACE("Start");

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

	sprintf(str, "%f",  BestSol->getValue());
	m_ctrlMaxValue.SetWindowText(str);
	
	Duration = res->getOptimDuration();
	Min  = Duration/60000;
	Sec  = (Duration - Min*60000) / 1000;
	Msec = ((long) Duration) % 1000;
	sprintf(str, "%02d:%02d:%03d", Min, Sec, Msec  );
	m_ctrlDuration.SetWindowText(str);
	
	sprintf(str, "%ld", res->getIterNum() );
	m_ctrlIterNum.SetWindowText(str);

//	TRACE("End");
}
