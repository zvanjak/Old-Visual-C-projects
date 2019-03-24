#if !defined(AFX_DLGGENERIC_H__E05817E5_26A7_4221_8B89_8A905E1B7889__INCLUDED_)
#define AFX_DLGGENERIC_H__E05817E5_26A7_4221_8B89_8A905E1B7889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGeneric.h : header file
//

#include "QAPSolverDoc.h"

#define WM_REFRESH_MESSAGE (WM_USER + 100)


/////////////////////////////////////////////////////////////////////////////
// CDlgGeneric dialog

class CDlgGeneric : public CDialog
{
// Construction
public:
	CDlgGeneric(CQAPSolverDoc	*p, CWnd* pParent = NULL);   // standard constructor

	void	Refresh( IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol  );

	IOptTerminator											*GetTermObj();
	IOptSaver<float, QAPSolution>				*GetSaveObj();
	OptRefreshMultiThread<float, QAPSolution>		*GetRefreshObj();

	// ovdje se mora kreirati sam objekt koji æe provesti optimizaciju
	virtual	void	OnStart() = 0;
	virtual	void	OnStop() = 0;
	virtual	void	OnContinue() = 0;
	virtual	void	OnUseNewParameters() = 0;
	virtual	void	OnGenericOK() = 0;
	virtual	void	OnGenericCancel() = 0;

// Dialog Data
	//{{AFX_DATA(CDlgGeneric)
	enum { IDD = IDD_GENERIC_ITERATIVE_OPT };
	CButton	m_ctrlCmdPerformInitial;
	CButton	m_ctrlCheckSaveEveryImprovement;
	CButton	m_ctrlCheckCallbackEveryImprovement;
	CButton	m_ctrlCheckCallbackMillisec;
	CButton	m_ctrlCheckCallbackIterNum;
	CButton	m_ctrlCheckSaveMillisec;
	CButton	m_ctrlCheckSaveIterNum;
	CButton	m_ctrlCheckTermReachedValue;
	CButton	m_ctrlCheckTermOptimDuration;
	CButton	m_ctrlCheckTermIterNum;
	CButton	m_ctrlCmdUseNew;
	CButton	m_ctrlCmdStop;
	CButton	m_ctrlCmdStart;
	CButton	m_ctrlCmdContinue;
	CEdit	m_ctrlIterNum;
	CEdit	m_ctrlMaxValue;
	CEdit	m_ctrlMaxSol;
	CEdit	m_ctrlDuration;
	CEdit	m_ctrlCurrValue;
	CEdit	m_ctrlCurrSol;
	CPrikazRasporedaIspita	m_ctrlSol;
	long	m_nTermIterNum;
	long	m_nCallbackIterNum;
	long	m_nCallbackMillisec;
	long	m_nSaveIterNum;
	long	m_nSaveMillisec;
	long	m_nTermOptimDuration;
	float	m_fTermReachedValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGeneric)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:

protected:
	CQAPSolverDoc		*pDoc;

	bool	RefreshInProgress;

	// da li pokazivaè i dalje pokazuje na ispravan ExchangeData objekt
	bool				bExchValid;
	ExchangeDataObject<float, QAPSolution>		*pExch;

	// Generated message map functions
	//{{AFX_MSG(CDlgGeneric)
	afx_msg void OnStartOptimizationCmd();
	afx_msg void OnStopOptimizationCmd();
	afx_msg void OnUseNewParametersCmd();
	afx_msg void OnCmdContinue();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnCheckTermIterNum();
	afx_msg void OnCheckTermOptimDuration();
	afx_msg void OnCheckTermReachedValue();
  afx_msg LRESULT OnRefreshMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCheckCallbackIternum();
	afx_msg void OnCheckCallbackMilisec();
	afx_msg void OnCheckSaveIternum();
	afx_msg void OnCheckSaveMilisec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/**************************************************************************************/
/**************************************************************************************/


template<class _SolverType>
class CDlgGenericTemplate : public CDlgGeneric {
public:
	CDlgGenericTemplate<_SolverType>(CQAPSolverDoc	*p, CWnd* pParent = NULL) 
		: CDlgGeneric(p, pParent) 
	{
		pQAP = NULL;
	}

	virtual void DoDataExchange(CDataExchange* pDX) {    // DDX/DDV support
	}
	virtual void	OnStart() = 0;

	virtual	void	SaveDialogValues() {
		m_nOldIterNum = m_nTermIterNum;
		m_nOldOptimDuration = m_nTermOptimDuration;
		m_fOldReachedValue = m_fTermReachedValue;
	}
	
	virtual	bool	CheckChangedDialogValues(){
		if( pQAP != NULL ) {
			if( m_ctrlCheckTermIterNum.GetCheck() == TRUE && m_nTermIterNum != m_nOldIterNum ) {
					IterativeOptTerminator	*temp = new IterativeOptTerminator(m_nTermIterNum);
					pQAP->SetOptTerminatorObject(temp);

					return true;
			}
			if( m_ctrlCheckTermOptimDuration.GetCheck() == TRUE && m_nTermOptimDuration != m_nOldOptimDuration ) {
					TimeOptTerminator	*temp = new TimeOptTerminator(m_nTermOptimDuration);
					pQAP->SetOptTerminatorObject(temp);

					return true;
				}
			if( m_ctrlCheckTermReachedValue.GetCheck() == TRUE && m_fTermReachedValue != m_fOldReachedValue ) {
					ConvergedFromUpOptTerminator	*temp = new ConvergedFromUpOptTerminator(m_fTermReachedValue);
					pQAP->SetOptTerminatorObject(temp);

					return true;
			}
		}
		return false;
	}

	void	OnUseNewParameters() {
		SaveDialogValues();
		UpdateData(TRUE);	
		CheckChangedDialogValues();
	}

	void	OnStop() {
		if( pQAP != NULL ) {
			while( RefreshInProgress == true )
				Sleep(1000);

			pQAP->Stop();

			m_ctrlCmdContinue.EnableWindow(TRUE);
			m_ctrlCmdUseNew.EnableWindow(TRUE);

//			EnableEditCtrl(this, TABU_SEARCH_EDIT_TABULIST_SIZE, TRUE);

			if( m_ctrlCheckTermIterNum.GetCheck() == TRUE ) 
				EnableEditCtrl(this, IDC_EDIT_TERM_ITER_NUM, TRUE);
			if( m_ctrlCheckTermOptimDuration.GetCheck() == TRUE ) 
				EnableEditCtrl(this, IDC_EDIT_TERM_OPTIM_DURATION, TRUE);
			if( m_ctrlCheckTermReachedValue.GetCheck() == TRUE ) 
				EnableEditCtrl(this, IDC_EDIT_TERM_REACHED_VALUE, TRUE);
		}
	}
	
	void	OnContinue() {
		pQAP->Continue();
	}
	
	void	OnGenericCancel() {
		if( pQAP != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
			if( pQAP->IsCalcInProgress() == true )
				pQAP->Terminate();
		}

		if( pQAP != NULL )
			delete pQAP;
	}
	
	void	OnGenericOK() {
		// problem ukoliko je nit zaustavljena a mi kliknemo na OK(Cancel)
		if( pQAP != NULL ) {		// najprije vidi da li je optimizacija uopæe pokrenuta
			if( pQAP->IsCalcInProgress() == true )
				pQAP->Terminate();
		}

		if( pQAP != NULL )
			delete pQAP;
		}

protected:
	_SolverType		*pQAP;

private:
	long	m_nOldIterNum;
	long	m_nOldOptimDuration;
	float	m_fOldReachedValue;
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGENERIC_H__E05817E5_26A7_4221_8B89_8A905E1B7889__INCLUDED_)
