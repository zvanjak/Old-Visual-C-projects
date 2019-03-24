#if !defined(DLG_GENERIC_SIM_ANNELING_H)
#define DLG_GENERIC_SIM_ANNELING_H

#include "DlgGeneric.h"

#include <QAP\QAPSimAnnealing.h>

#define		SIM_ANN_EDIT_ACCEPT_PROB								56000
#define		SIM_ANN_EDIT_TEMP_CHG_FACTOR						56001
#define		SIM_ANN_EDIT_PERM_NUM										56002

class CDlgSimAnnAutomated : public CDlgGenericTemplate<QAPSolverAutomatedSimAnnealing > {
public:
	CDlgSimAnnAutomated(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverAutomatedSimAnnealing >(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Accept.prob.", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Temp.change factor ", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("Perm-num", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);

		m_ctrlAcceptProb.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, SIM_ANN_EDIT_ACCEPT_PROB );
		m_ctrlAcceptProb.ShowWindow(TRUE);

		m_ctrlTempChgFactor.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, SIM_ANN_EDIT_TEMP_CHG_FACTOR );
		m_ctrlTempChgFactor.ShowWindow(TRUE);

		m_ctrlPermNum.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, SIM_ANN_EDIT_PERM_NUM );
		m_ctrlPermNum.ShowWindow(TRUE);

		m_dAcceptHigherProb = 0.99;
		m_ctrlAcceptProb.SetWindowText("0.99");
		
		m_dTempChangeFactor = 0.99;
		m_ctrlTempChgFactor.SetWindowText("0.99");

		m_nPermNum = 100;
		m_ctrlPermNum.SetWindowText("100");
	
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, SIM_ANN_EDIT_ACCEPT_PROB, m_dAcceptHigherProb);
		DDX_Text(pDX, SIM_ANN_EDIT_TEMP_CHG_FACTOR, m_dTempChangeFactor);
		DDX_Text(pDX, SIM_ANN_EDIT_PERM_NUM, m_nPermNum);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator														*pTermObj;
		IOptSaver<float, QAPSolution>							*pSaveObj;
		OptRefreshMultiThread<float, QAPSolution>	*pRefObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new QAPSolverAutomatedSimAnnealing ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		m_dAcceptHigherProb,
																		m_dTempChangeFactor,
																		m_nPermNum
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP->SetOptTerminatorObject(pTermObj);
			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);
		}

		if( pExch != NULL )
			delete pExch;
		pExch = new ExchangeDataObject<float, QAPSolution>(this->m_hWnd);

		pRefObj->AssignPointerToExchangeData(pExch);

		pQAP->Start();
	}

	void	SaveDialogValue() {
		SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
/*
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
*/
		}
		return ret1 || CDlgGenericTemplate<QAPSolverAutomatedSimAnnealing>::CheckChangedDialogValues();
	}

private:
	double	m_dAcceptHigherProb;
	double	m_dTempChangeFactor;
	int			m_nPermNum;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlAcceptProb, m_ctrlTempChgFactor, m_ctrlPermNum;
};


/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

#define		SIM_ANN_EDIT_BR_INIT_TEMP								56100
#define		SIM_ANN_EDIT_BR_TEMP_CHG_FACTOR					56101
#define		SIM_ANN_EDIT_BR_ITER_NUM								56102

class CDlgSimAnnSimple : public CDlgGenericTemplate<QAPSolverSimpleSimAnnealing> {
public:
	CDlgSimAnnSimple(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverSimpleSimAnnealing>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Inital temp.", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Temp.change factor ", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("Iter.num", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);

		m_ctrlInitTemp.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, SIM_ANN_EDIT_BR_INIT_TEMP );
		m_ctrlInitTemp.ShowWindow(TRUE);

		m_ctrlTempChgFactor.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, SIM_ANN_EDIT_BR_TEMP_CHG_FACTOR );
		m_ctrlTempChgFactor.ShowWindow(TRUE);

		m_ctrlIterNum.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, SIM_ANN_EDIT_BR_ITER_NUM );
		m_ctrlIterNum.ShowWindow(TRUE);

		m_dInitTemp = 1000;
		m_ctrlInitTemp.SetWindowText("1000");
		
		m_dTempChangeFactor = 0.99;
		m_ctrlTempChgFactor.SetWindowText("0.99");

		m_nIterNum = 100;
		m_ctrlIterNum.SetWindowText("100");
	
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, SIM_ANN_EDIT_BR_INIT_TEMP, m_dInitTemp);
		DDX_Text(pDX, SIM_ANN_EDIT_BR_TEMP_CHG_FACTOR, m_dTempChangeFactor);
		DDX_Text(pDX, SIM_ANN_EDIT_BR_ITER_NUM, m_nIterNum);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator														*pTermObj;
		IOptSaver<float, QAPSolution>							*pSaveObj;
		OptRefreshMultiThread<float, QAPSolution>	*pRefObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new QAPSolverSimpleSimAnnealing ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		m_dInitTemp,
																		m_dTempChangeFactor,
																		m_nIterNum
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
/*			pQAP->setTabuListSize(m_nTabuListSize);
	*/		
			// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP->SetOptTerminatorObject(pTermObj);
			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);
		}

		if( pExch != NULL )
			delete pExch;
		pExch = new ExchangeDataObject<float, QAPSolution>(this->m_hWnd);

		pRefObj->AssignPointerToExchangeData(pExch);

		pQAP->Start();
	}

	void	SaveDialogValue() {
		// najprije pamtimo varijable karakteristiène za ovaj razred
//		m_nOldTabuListSize = m_nTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
//		CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::SaveDialogValues();
		SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
/*
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
*/
		}
//		return ret1 || CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::CheckChangedDialogValues();
		return ret1 || CDlgGenericTemplate<QAPSolverSimpleSimAnnealing>::CheckChangedDialogValues();
	}

private:
	double	m_dInitTemp;
	double	m_dTempChangeFactor;
	int			m_nIterNum;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlInitTemp, m_ctrlTempChgFactor, m_ctrlIterNum;
};


/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

#define		SIM_ANN_EDIT_CONN_MAX_FAILED		56200
#define		SIM_ANN_EDIT_CONN_M							56201
#define		SIM_ANN_EDIT_CONN_T0						56202
#define		SIM_ANN_EDIT_CONN_TF						56203

class CDlgSimAnnConn : public CDlgGenericTemplate<QAPSolverConnSimAnnealing> {
public:
	CDlgSimAnnConn(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverConnSimAnnealing>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Inital temp.", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Final temp.", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("Max.failed", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);

		m_Label4.Create("M ", WS_VISIBLE , CRect(x,y+90,x+dx,y+110), this );
		m_Label4.ShowWindow(TRUE);

		m_ctrlT0.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, SIM_ANN_EDIT_CONN_T0 );
		m_ctrlT0.ShowWindow(TRUE);

		m_ctrlTf.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, SIM_ANN_EDIT_CONN_TF );
		m_ctrlTf.ShowWindow(TRUE);

		m_ctrlMaxFailed.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, SIM_ANN_EDIT_CONN_MAX_FAILED );
		m_ctrlMaxFailed.ShowWindow(TRUE);

		m_ctrlM.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+85,x+2*dx,y+105), this, SIM_ANN_EDIT_CONN_M );
		m_ctrlM.ShowWindow(TRUE);

		m_dT0 = 100;
		m_ctrlT0.SetWindowText("100");
		
		m_dTf = 0.0;
		m_ctrlTf.SetWindowText("0");

		int		n = pDoc->getProblemSize();
		char	str[20];

		m_lMaxFailed = n * (n-1) / 2;
		sprintf(str, "%ld", m_lMaxFailed);
		m_ctrlMaxFailed.SetWindowText(str);
	
		m_lM = 50 * n * (n-1) / 2;
		sprintf(str, "%ld", m_lM);
		m_ctrlM.SetWindowText(str);
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_T0, m_dT0);
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_TF, m_dTf);
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_MAX_FAILED, m_lMaxFailed);
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_M, m_lM);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator														*pTermObj;
		IOptSaver<float, QAPSolution>							*pSaveObj;
		OptRefreshMultiThread<float, QAPSolution>	*pRefObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new QAPSolverConnSimAnnealing ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		(int) m_lMaxFailed,
																		(int) m_lM,
																		(float) m_dT0,
																		(float) m_dTf
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
/*			pQAP->setTabuListSize(m_nTabuListSize);
	*/		
			// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP->SetOptTerminatorObject(pTermObj);
			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);
		}

		if( pExch != NULL )
			delete pExch;
		pExch = new ExchangeDataObject<float, QAPSolution>(this->m_hWnd);

		pRefObj->AssignPointerToExchangeData(pExch);

		pQAP->Start();
	}

	void	SaveDialogValue() {
		// najprije pamtimo varijable karakteristiène za ovaj razred
//		m_nOldTabuListSize = m_nTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
//		CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::SaveDialogValues();
		SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
/*
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
*/
		}
//		return ret1 || CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::CheckChangedDialogValues();
		return ret1 || CDlgGenericTemplate<QAPSolverConnSimAnnealing>::CheckChangedDialogValues();
	}

private:
	double	m_dT0, m_dTf;
	long		m_lMaxFailed;
	long		m_lM;
	
	CStatic		m_Label1, m_Label2, m_Label3, m_Label4;
	CEdit			m_ctrlT0, m_ctrlTf, m_ctrlMaxFailed, m_ctrlM;
};


/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

#define		SIM_ANN_EDIT_CONNAUT_MAX_FAILED		56200
#define		SIM_ANN_EDIT_CONNAUT_M							56201

class CDlgSimAnnConnAutomated : public CDlgGenericTemplate<QAPSolverConnAutomatedSimAnnealing> {
public:
	CDlgSimAnnConnAutomated(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverConnAutomatedSimAnnealing>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Max.failed", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("M ", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_ctrlMaxFailed.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, SIM_ANN_EDIT_CONNAUT_MAX_FAILED );
		m_ctrlMaxFailed.ShowWindow(TRUE);

		m_ctrlM.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, SIM_ANN_EDIT_CONNAUT_M );
		m_ctrlM.ShowWindow(TRUE);

		int		n = pDoc->getProblemSize();
		char	str[20];

		m_lMaxFailed = n * (n-1) / 2;
		sprintf(str, "%ld", m_lMaxFailed);
		m_ctrlMaxFailed.SetWindowText(str);
	
		m_lM = 50 * n * (n-1) / 2;
		sprintf(str, "%ld", m_lM);
		m_ctrlM.SetWindowText(str);
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_MAX_FAILED, m_lMaxFailed);
		DDX_Text(pDX, SIM_ANN_EDIT_CONN_M, m_lM);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator														*pTermObj;
		IOptSaver<float, QAPSolution>							*pSaveObj;
		OptRefreshMultiThread<float, QAPSolution>	*pRefObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new QAPSolverConnAutomatedSimAnnealing ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		m_lMaxFailed,
																		m_lM
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
/*			pQAP->setTabuListSize(m_nTabuListSize);
	*/		
			// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP->SetOptTerminatorObject(pTermObj);
			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);
		}

		if( pExch != NULL )
			delete pExch;
		pExch = new ExchangeDataObject<float, QAPSolution>(this->m_hWnd);

		pRefObj->AssignPointerToExchangeData(pExch);

		pQAP->Start();
	}

	void	SaveDialogValue() {
		// najprije pamtimo varijable karakteristiène za ovaj razred
//		m_nOldTabuListSize = m_nTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
//		CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::SaveDialogValues();
		SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
/*
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
*/
		}
//		return ret1 || CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::CheckChangedDialogValues();
		return ret1 || CDlgGenericTemplate<QAPSolverConnAutomatedSimAnnealing>::CheckChangedDialogValues();
	}

private:
	long		m_lMaxFailed;
	long		m_lM;
	
	CStatic		m_Label1, m_Label2;
	CEdit			m_ctrlMaxFailed, m_ctrlM;
};

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

#define		SIM_ANN_EDIT_WW_EPOCH_ITER_NUM			56900
#define		SIM_ANN_EDIT_WW_EPS									56901
#define		SIM_ANN_EDIT_WW_N										56902

class CDlgSimAnnWW : public CDlgGenericTemplate<QAPSolverWWSimAnnealing> {
public:
	CDlgSimAnnWW(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverWWSimAnnealing>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Epoch iter.num.", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Eps", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("N", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);

		m_ctrlEpochIterNum.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, SIM_ANN_EDIT_WW_EPOCH_ITER_NUM );
		m_ctrlEpochIterNum.ShowWindow(TRUE);

		m_ctrlEps.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, SIM_ANN_EDIT_WW_EPS );
		m_ctrlEps.ShowWindow(TRUE);

		m_ctrlN.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, SIM_ANN_EDIT_WW_N );
		m_ctrlN.ShowWindow(TRUE);

		m_nEpochIterNum = 10;
		m_ctrlEpochIterNum.SetWindowText("10");
		
		m_fEps = 0.05f;
		m_ctrlEps.SetWindowText("0.05");

		m_nN	= 100;
		m_ctrlN.SetWindowText("100");
	
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, SIM_ANN_EDIT_WW_EPOCH_ITER_NUM, m_nEpochIterNum);
		DDX_Text(pDX, SIM_ANN_EDIT_WW_EPS, m_fEps);
		DDX_Text(pDX, SIM_ANN_EDIT_WW_N, m_nN);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator														*pTermObj;
		IOptSaver<float, QAPSolution>							*pSaveObj;
		OptRefreshMultiThread<float, QAPSolution>	*pRefObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new QAPSolverWWSimAnnealing ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		m_nEpochIterNum,
																		m_fEps,
																		m_nN
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
/*			pQAP->setTabuListSize(m_nTabuListSize);
	*/		
			// odgovornost za brisanje OptTerminatora je na klijentu ( znaèi algoritmu koji ga koristi )
			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP->SetOptTerminatorObject(pTermObj);
			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);
		}

		if( pExch != NULL )
			delete pExch;
		pExch = new ExchangeDataObject<float, QAPSolution>(this->m_hWnd);

		pRefObj->AssignPointerToExchangeData(pExch);

		pQAP->Start();
	}

	void	SaveDialogValue() {
		// najprije pamtimo varijable karakteristiène za ovaj razred
//		m_nOldTabuListSize = m_nTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
//		CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::SaveDialogValues();
		SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
		}
		return ret1 || CDlgGenericTemplate<QAPSolverWWSimAnnealing>::CheckChangedDialogValues();
	}

private:
	int			m_nEpochIterNum;
	float		m_fEps;
	int			m_nN;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlEpochIterNum, m_ctrlEps, m_ctrlN;
};

#endif