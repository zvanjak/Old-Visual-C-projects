#if !defined(DLG_GENERIC_GRASP_H)
#define DLG_GENERIC_GRASP_H

#include "DlgGeneric.h"

#include <QAP\QAPGRASP.h>

#define		GRASP_EDIT_ALPHA								57000
#define		GRASP_EDIT_BETA									57001

class CDlgGRASP: public CDlgGenericTemplate<QAPSolverGRASP> {
public:
	CDlgGRASP(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGenericTemplate<QAPSolverGRASP>(p, pParent)
	{
		RECT		rect;
		GetClientRect(&rect);

		int		x, y, dx;

		x = rect.right * 0.77;
		dx = rect.right * 0.1;
		y = rect.bottom * 0.2;

		m_Label1.Create("Alpha ", WS_VISIBLE , CRect(x,y,x+dx,y+20), this );
		m_Label1.ShowWindow(TRUE);

		m_Label2.Create("Beta ", WS_VISIBLE , CRect(x,y+30,x+dx,y+50), this );
		m_Label2.ShowWindow(TRUE);

		m_ctrlAlpha.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y-5,x+2*dx,y+15), this, GRASP_EDIT_ALPHA );
		m_ctrlAlpha.ShowWindow(TRUE);

		m_ctrlBeta.Create(BS_PUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, CRect(x+dx,y+25,x+2*dx,y+45), this, GRASP_EDIT_BETA );
		m_ctrlBeta.ShowWindow(TRUE);

		m_dAlpha= 0.99;
		m_ctrlAlpha.SetWindowText("0.99");
		
		m_dBeta = 0.99;
		m_ctrlBeta.SetWindowText("0.99");
	}

	void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
		DDX_Text(pDX, GRASP_EDIT_ALPHA, m_dAlpha);
		DDX_Text(pDX, GRASP_EDIT_BETA, m_dBeta);

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

			pQAP = new QAPSolverGRASP( pDoc->getProblemSize(), 
																 pTermObj,
																 m_dAlpha,
																 m_dBeta
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
		return ret1 || CDlgGenericTemplate<QAPSolverGRASP>::CheckChangedDialogValues();
	}

private:
	double	m_dAlpha;
	double	m_dBeta;
	
	CStatic		m_Label1, m_Label2, m_Label3;
	CEdit			m_ctrlAlpha, m_ctrlBeta;
};

#endif