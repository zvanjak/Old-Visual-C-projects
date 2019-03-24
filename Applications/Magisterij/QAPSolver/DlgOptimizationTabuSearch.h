#if !defined(DLG_GENERIC_TABU_SEARCH_H)
#define DLG_GENERIC_TABU_SEARCH_H

#include "DlgGeneric.h"

#include <QAP\QAPTabuSearch.h>

/**************************************************************************************/
/**************************************************************************************/

#define		TABU_SEARCH_EDIT_TABULIST_SIZE					55000
#define		TABU_SEARCH_EDIT_DELTA_TABULIST_SIZE		55001
#define		TABU_SEARCH_EDIT_ASP_TABULIST_SIZE			55002


class CDlgTabuSearchSimple : public CDlgGenericTemplate<SimpleTabuSearchQAPSolver> {
public:
	CDlgTabuSearchSimple(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<SimpleTabuSearchQAPSolver>(p, pParent)
	{
		int			x, y, dx;
		RECT		rect;

		GetClientRect(&rect);
		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Tabu list size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_ctrlTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, TABU_SEARCH_EDIT_TABULIST_SIZE);
		m_ctrlTabuSize.ShowWindow(TRUE);

		m_nTabuListSize = 30;
		m_ctrlTabuSize.SetWindowText("30");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, TABU_SEARCH_EDIT_TABULIST_SIZE, m_nTabuListSize);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator	*pTermObj;
		OptRefreshMultiThread<float, QAPSolution>		*pRefObj;
		IOptSaver<float, QAPSolution>		*pSaveObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new SimpleTabuSearchQAPSolver( 
																		pDoc->getProblemSize(), 
																		pTermObj, 
																		m_nTabuListSize
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
			pQAP->setTabuListSize(m_nTabuListSize);
			
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
		m_nOldTabuListSize = m_nTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
		CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
		}
		return ret1 || CDlgGenericTemplate<SimpleTabuSearchQAPSolver>::CheckChangedDialogValues();
	}

private:
	int				m_nTabuListSize, m_nOldTabuListSize;

	CStatic		m_Label1;
	CEdit			m_ctrlTabuSize;
};


class CDlgTabuSearchSimpleDiversify : public CDlgGenericTemplate<SimpleDiversifyTabuSearchQAPSolver> {
public:
	CDlgTabuSearchSimpleDiversify(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<SimpleDiversifyTabuSearchQAPSolver>(p, pParent)
	{
		int			x, y, dx;
		RECT		rect;

		GetClientRect(&rect);
		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Tabu list size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);
		m_Label3.Create("Aspiration", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this);
		m_Label3.ShowWindow(TRUE);

		m_ctrlTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y-15), this, TABU_SEARCH_EDIT_TABULIST_SIZE );
		m_ctrlTabuSize.ShowWindow(TRUE);

		m_ctrlAspiration.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, TABU_SEARCH_EDIT_ASP_TABULIST_SIZE);
		m_ctrlAspiration.ShowWindow(TRUE);

		m_nTabuListSize = 30;
		m_ctrlTabuSize.SetWindowText("30");
		
		m_nAspirationParamT = 1000;
		m_ctrlAspiration.SetWindowText("1000");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, TABU_SEARCH_EDIT_TABULIST_SIZE, m_nTabuListSize);
		DDX_Text(pDX, TABU_SEARCH_EDIT_ASP_TABULIST_SIZE, m_nAspirationParamT);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator	*pTermObj;
		OptRefreshMultiThread<float, QAPSolution>		*pRefObj;
		IOptSaver<float, QAPSolution>		*pSaveObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new SimpleDiversifyTabuSearchQAPSolver( 
																		pDoc->getProblemSize(), 
																		pTermObj, 
																		m_nTabuListSize, 
																		m_nAspirationParamT 
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
			pQAP->setTabuListSize(m_nTabuListSize);
			
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
		m_nOldTabuListSize = m_nTabuListSize;
		m_nOldAspirationParamT = m_nAspirationParamT;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
		CDlgGenericTemplate<SimpleDiversifyTabuSearchQAPSolver>::SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
			if( m_nOldAspirationParamT != m_nAspirationParamT ) {
				pQAP->setAspirationParamT(m_nAspirationParamT);
				ret1 = true;
			}
		}
		return ret1 || CDlgGenericTemplate<SimpleDiversifyTabuSearchQAPSolver>::CheckChangedDialogValues();
	}

private:
	int			m_nTabuListSize, m_nOldTabuListSize;
	long		m_nAspirationParamT, m_nOldAspirationParamT;

	CStatic		m_Label1, m_Label3;
	CEdit			m_ctrlTabuSize, m_ctrlAspiration;
};


class CDlgTabuSearchRobust : public CDlgGenericTemplate<RobustTabuSearchQAPSolver> {
public:
	CDlgTabuSearchRobust(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<RobustTabuSearchQAPSolver>(p, pParent)
	{
		int			x, y, dx;
		RECT		rect;

		GetClientRect(&rect);
		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Tabu list size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);
		m_Label2.Create("Delta tabu list", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this);
		m_Label2.ShowWindow(TRUE);

		m_ctrlTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, TABU_SEARCH_EDIT_TABULIST_SIZE );
		m_ctrlTabuSize.ShowWindow(TRUE);

		m_ctrlDeltaTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, TABU_SEARCH_EDIT_DELTA_TABULIST_SIZE);
		m_ctrlDeltaTabuSize.ShowWindow(TRUE);

		m_nTabuListSize = 30;
		m_ctrlTabuSize.SetWindowText("30");
		
		m_nDeltaTabuListSize = 5;
		m_ctrlDeltaTabuSize.SetWindowText("5");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, TABU_SEARCH_EDIT_TABULIST_SIZE, m_nTabuListSize);
		DDX_Text(pDX, TABU_SEARCH_EDIT_DELTA_TABULIST_SIZE, m_nDeltaTabuListSize);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator	*pTermObj;
		OptRefreshMultiThread<float, QAPSolution>		*pRefObj;
		IOptSaver<float, QAPSolution>		*pSaveObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new RobustTabuSearchQAPSolver( 
																		pDoc->getProblemSize(), 
																		pTermObj, 
																		m_nTabuListSize, 
																		m_nDeltaTabuListSize
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
			pQAP->setTabuListSize(m_nTabuListSize);
			
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
		m_nOldTabuListSize = m_nTabuListSize;
		m_nOldDeltaTabuListSize = m_nDeltaTabuListSize;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
		CDlgGenericTemplate<RobustTabuSearchQAPSolver>::SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
			if( m_nOldDeltaTabuListSize != m_nDeltaTabuListSize ) {
				pQAP->setDeltaTabuListSize(m_nDeltaTabuListSize);
				ret1 = true;
			}
		}
		return ret1 || CDlgGenericTemplate<RobustTabuSearchQAPSolver>::CheckChangedDialogValues();
	}

private:
	int			m_nTabuListSize, m_nOldTabuListSize;
	int			m_nDeltaTabuListSize, m_nOldDeltaTabuListSize;

	CStatic		m_Label1, m_Label2;
	CEdit			m_ctrlTabuSize, m_ctrlDeltaTabuSize;
};


class CDlgTabuSearchRobustDiversify : public CDlgGenericTemplate<RobustDiversifyTabuSearchQAPSolver> {
public:
	CDlgTabuSearchRobustDiversify(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<RobustDiversifyTabuSearchQAPSolver>(p, pParent)
	{
		int			x, y, dx;
		RECT		rect;

		GetClientRect(&rect);
		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Tabu list size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);
		m_Label2.Create("Delta tabu list", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this);
		m_Label2.ShowWindow(TRUE);
		m_Label3.Create("Aspiration", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this);
		m_Label3.ShowWindow(TRUE);

		m_ctrlTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, TABU_SEARCH_EDIT_TABULIST_SIZE );
		m_ctrlTabuSize.ShowWindow(TRUE);

		m_ctrlDeltaTabuSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx, y+25, x+2*dx, y+45), this, TABU_SEARCH_EDIT_DELTA_TABULIST_SIZE );
		m_ctrlDeltaTabuSize.ShowWindow(TRUE);

		m_ctrlAspiration.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx, y+55, x+2*dx, y+75), this, TABU_SEARCH_EDIT_ASP_TABULIST_SIZE);
		m_ctrlAspiration.ShowWindow(TRUE);

		m_nTabuListSize = 30;
		m_ctrlTabuSize.SetWindowText("30");
		
		m_nDeltaTabuListSize = 5;
		m_ctrlDeltaTabuSize.SetWindowText("5");

		m_nAspirationParamT = 1000;
		m_ctrlAspiration.SetWindowText("1000");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, TABU_SEARCH_EDIT_TABULIST_SIZE, m_nTabuListSize);
		DDX_Text(pDX, TABU_SEARCH_EDIT_DELTA_TABULIST_SIZE, m_nDeltaTabuListSize);
		DDX_Text(pDX, TABU_SEARCH_EDIT_ASP_TABULIST_SIZE, m_nAspirationParamT);

		CDlgGeneric::DoDataExchange(pDX);
	}

	void	OnStart() {
	// najprije kreiramo objekt
		IOptTerminator	*pTermObj;
		OptRefreshMultiThread<float, QAPSolution>		*pRefObj;
		IOptSaver<float, QAPSolution>		*pSaveObj;

		if( pQAP == NULL ){
			UpdateData();

			pTermObj = GetTermObj();
			pRefObj	 = GetRefreshObj();
			pSaveObj = GetSaveObj();

			pQAP = new RobustDiversifyTabuSearchQAPSolver( 
																		pDoc->getProblemSize(), 
																		pTermObj, 
																		m_nTabuListSize, 
																		m_nDeltaTabuListSize, 
																		m_nAspirationParamT 
																	);

			pQAP->SetOptRefresherObject(pRefObj);
			pQAP->SetOptSaverObject(pSaveObj);

			pQAP->setSaveObject(pDoc);

			pQAP->setA(*pDoc->getA());
			pQAP->setB(*pDoc->getB());
		}
		else {
			// znaèi da smo možda promijenili parametre i da nastavljamo optimizaciju
			pQAP->setTabuListSize(m_nTabuListSize);
			
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
		m_nOldTabuListSize = m_nTabuListSize;
		m_nOldDeltaTabuListSize = m_nDeltaTabuListSize;
		m_nOldAspirationParamT = m_nAspirationParamT;
		
		// a zatim moramo pozvati da se zapamte i one koje su zajednièke svima
		CDlgGenericTemplate<RobustDiversifyTabuSearchQAPSolver>::SaveDialogValues();
	}

	bool	CheckChangedDialogValues() {
		bool	ret1 = false;

		if( pQAP != NULL ) {
			if( m_nTabuListSize != m_nOldTabuListSize ) {
				pQAP->setTabuListSize(m_nTabuListSize);
				ret1 = true;
			}
			if( m_nOldDeltaTabuListSize != m_nDeltaTabuListSize ) {
				pQAP->setDeltaTabuListSize(m_nDeltaTabuListSize);
				ret1 = true;
			}
			if( m_nOldAspirationParamT != m_nAspirationParamT ) {
				pQAP->setAspirationParamT(m_nAspirationParamT);
				ret1 = true;
			}
		}
		return ret1 || CDlgGenericTemplate<RobustDiversifyTabuSearchQAPSolver>::CheckChangedDialogValues();
	}

private:
	int			m_nTabuListSize, m_nOldTabuListSize;
	int			m_nDeltaTabuListSize, m_nOldDeltaTabuListSize;
	long		m_nAspirationParamT, m_nOldAspirationParamT;

	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlTabuSize, m_ctrlDeltaTabuSize, m_ctrlAspiration;
};

#endif