#if !defined(DLG_GENERIC_GENETIC_H)
#define DLG_GENERIC_GENETIC_H

#include "DlgGeneric.h"

#include <QAP\QAPGeneticAlg.h>

#define		GEN_ALG_EDIT_POP_SIZE						58000
#define		GEN_ALG_EDIT_MUT_PROB						58001

class CDlgGenAlgTournamentSelection: public CDlgGenericTemplate<QAPGenAlgTournamentSelection> {
public:
	CDlgGenAlgTournamentSelection(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPGenAlgTournamentSelection>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Pop.size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Mutation prob.", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_ctrlPopSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, GEN_ALG_EDIT_POP_SIZE );
		m_ctrlPopSize.ShowWindow(TRUE);

		m_ctrlMutProb.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, GEN_ALG_EDIT_MUT_PROB );
		m_ctrlMutProb.ShowWindow(TRUE);

		m_nPopSize = 50;
		m_ctrlPopSize.SetWindowText("50");
		
		m_dMutProb = 0.99;
		m_ctrlMutProb.SetWindowText("0.99");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, GEN_ALG_EDIT_POP_SIZE, m_nPopSize);
		DDX_Text(pDX, GEN_ALG_EDIT_MUT_PROB, m_dMutProb);

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

			pQAP = new QAPGenAlgTournamentSelection ( 
																		pDoc->getProblemSize(), 
																		pTermObj,
																		NULL,
																		m_nPopSize,
																		m_dMutProb
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
		return ret1 || CDlgGenericTemplate<QAPGenAlgTournamentSelection>::CheckChangedDialogValues();
	}

private:
	int			m_nPopSize;
	double	m_dMutProb;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlPopSize, m_ctrlMutProb;
};


/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

#define		GEN_ALG_FFGA_EDIT_POP_SIZE						58100
#define		GEN_ALG_FFGA_EDIT_PER_GEN							58101
#define		GEN_ALG_FFGA_EDIT_SEL_PAR_R						58102

class CDlgGenAlgFFGA : public CDlgGenericTemplate<QAPGenAlgFFGA> {
public:
	CDlgGenAlgFFGA(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPGenAlgFFGA>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Pop.size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Per generation", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("Sel.par. R", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);
		
		m_ctrlPopSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, GEN_ALG_FFGA_EDIT_POP_SIZE );
		m_ctrlPopSize.ShowWindow(TRUE);

		m_ctrlPerGen.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, GEN_ALG_FFGA_EDIT_PER_GEN );
		m_ctrlPerGen.ShowWindow(TRUE);

		m_ctrlSelParR.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, GEN_ALG_FFGA_EDIT_SEL_PAR_R );
		m_ctrlSelParR.ShowWindow(TRUE);

		m_nPopSize = 50;
		m_ctrlPopSize.SetWindowText("50");
		
		m_nPerGen = 20;
		m_ctrlPerGen.SetWindowText("20");

		m_fSelParR = 1.5;
		m_ctrlSelParR.SetWindowText("1.5");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, GEN_ALG_FFGA_EDIT_POP_SIZE, m_nPopSize);
		DDX_Text(pDX, GEN_ALG_FFGA_EDIT_PER_GEN, m_nPerGen);
		DDX_Text(pDX, GEN_ALG_FFGA_EDIT_SEL_PAR_R, m_fSelParR);

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

			pQAP = new QAPGenAlgFFGA( 
																pDoc->getProblemSize(), 
																pTermObj,
																NULL,
																m_nPopSize,
																m_nPerGen,
																m_fSelParR
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
		return ret1 || CDlgGenericTemplate<QAPGenAlgFFGA>::CheckChangedDialogValues();
	}

private:
	int			m_nPopSize;
	int			m_nPerGen;
	float		m_fSelParR;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlPopSize, m_ctrlPerGen, m_ctrlSelParR;
};


/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

#define		GEN_ALG_GREEDY_EDIT_POP_SIZE						58200
#define		GEN_ALG_GREEDY_EDIT_PER_GEN							58201
#define		GEN_ALG_GREEDY_EDIT_SEL_PAR_R						58202

class CDlgGenAlgGreedy : public CDlgGenericTemplate<QAPGenAlgGreedy> {
public:
	CDlgGenAlgGreedy(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPGenAlgGreedy>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Pop.size", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Immigration ", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_Label3.Create("L.Search rate ", WS_VISIBLE , CRect(x,y+60,x+dx,y+80), this );
		m_Label3.ShowWindow(TRUE);
		
		m_ctrlPopSize.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, GEN_ALG_GREEDY_EDIT_POP_SIZE );
		m_ctrlPopSize.ShowWindow(TRUE);

		m_ctrlImmigration.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, GEN_ALG_GREEDY_EDIT_PER_GEN );
		m_ctrlImmigration.ShowWindow(TRUE);

		m_ctrlLSRate.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+55,x+2*dx,y+75), this, GEN_ALG_GREEDY_EDIT_SEL_PAR_R );
		m_ctrlLSRate.ShowWindow(TRUE);

		m_nPopSize = 50;
		m_ctrlPopSize.SetWindowText("50");
		
		m_nImmigrationRate = 20;
		m_ctrlImmigration.SetWindowText("20");

		m_nLocalSearchRate = 100;
		m_ctrlLSRate.SetWindowText("100");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, GEN_ALG_GREEDY_EDIT_POP_SIZE, m_nPopSize);
		DDX_Text(pDX, GEN_ALG_GREEDY_EDIT_PER_GEN, m_nImmigrationRate);
		DDX_Text(pDX, GEN_ALG_GREEDY_EDIT_SEL_PAR_R, m_nLocalSearchRate);

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

			pQAP = new QAPGenAlgGreedy( 
																pDoc->getProblemSize(), 
																pTermObj,
																NULL,
																m_nPopSize,
																m_nImmigrationRate,
																m_nLocalSearchRate
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
		return ret1 || CDlgGenericTemplate<QAPGenAlgGreedy>::CheckChangedDialogValues();
	}

private:
	int			m_nPopSize;
	int			m_nImmigrationRate;
	float		m_nLocalSearchRate;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlPopSize, m_ctrlImmigration, m_ctrlLSRate;
};

#endif