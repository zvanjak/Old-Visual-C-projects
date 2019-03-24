#if !defined(DLG_GENERIC_LOCAL_SEARCH_H)
#define DLG_GENERIC_LOCAL_SEARCH_H

#include "DlgGeneric.h"

#include <QAP\QAPLocalSearch.h>

class CDlgLSFirstImprovement: public CDlgGenericTemplate<QAPSolverLSFirstImprovement> {
public:
	CDlgLSFirstImprovement(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverLSFirstImprovement>(p, pParent)
	{
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
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

			pQAP = new QAPSolverLSFirstImprovement( 
																		pDoc->getProblemSize(), 
																		pTermObj
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

		return ret1 || CDlgGenericTemplate<QAPSolverLSFirstImprovement>::CheckChangedDialogValues();
	}
};


class CDlgLSBestImprovement: public CDlgGenericTemplate<QAPSolverLSBestImprovement> {
public:
	CDlgLSBestImprovement(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverLSBestImprovement>(p, pParent)
	{
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
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

			pQAP = new QAPSolverLSBestImprovement( 
																		pDoc->getProblemSize(), 
																		pTermObj
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

		return ret1 || CDlgGenericTemplate<QAPSolverLSBestImprovement>::CheckChangedDialogValues();
	}
};


class CDlgLSHeider: public CDlgGenericTemplate<QAPSolverLSHeider> {
public:
	CDlgLSHeider(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverLSHeider>(p, pParent)
	{
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
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

			pQAP = new QAPSolverLSHeider( 
																		pDoc->getProblemSize(), 
																		pTermObj
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

		return ret1 || CDlgGenericTemplate<QAPSolverLSHeider>::CheckChangedDialogValues();
	}
};


#endif