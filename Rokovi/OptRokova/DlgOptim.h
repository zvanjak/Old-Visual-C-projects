//{{AFX_INCLUDES()
#include "scrollbar.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGOPTIM_H__19A7B303_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_)
#define AFX_DLGOPTIM_H__19A7B303_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptim.h : header file
//

#define		X0				11
#define		Y0				11
#define		HEIGHT		560
#define		WIDTH			970

#define		MAX_ISP_NA_EKRANU		35

UINT	DoSomething( LPVOID lParam );


/////////////////////////////////////////////////////////////////////////////
// CDlgOptim dialog

class CDlgOptim : public CDialog
{
// Construction
public:
	CDlgOptim(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptim)
	enum { IDD = IDD_OPTIMIZACIJA };
	CStatic	m_ctrlRect;
	CButton	m_ctrlStop;
	CProgressCtrl	m_ctrlOptProgress;
	CScrollbar	m_ctrlVScroll;
	double	m_dProsjek;
	//}}AFX_DATA

	void			PrintConfig();
	bool			bCalcInProgress;
	bool			bCalcStopped;			// istina ukoliko je optimizacija privremeno zaustavljena ( radi pregleda rezutlata, pomicanja odreðenih temrina interaktivno ... )

	int				m_nWndHeight, m_nWndWidth;

	bool			bTermSelected;		// kada se klikne mišem na termin odreðenog ispita èiji se termin želi promijeniti
	int				nRow, nOldTerm, nRok;				// redak i stupac u kojem je selektiran

	int				m_VertPos;				// pozicija scrollbar-a
	int				m_StartWith;			// sa kojim rednimn brojem predmeta poèinje ispis na ekran
	int				m_SelIspit;				// koji ispit je odabran da s eprikazuju njeogvi presjeci sa ostalima
	
	time_t		timeStarted;
	time_t		timeEnded;
	int				IterNum;
	int				nCurrIterNum;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptim)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptim)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnChangeVscroll();
	afx_msg void OnScrollVscroll();
	afx_msg void OnStop();
	afx_msg void OnNastaviOptimizaciju();
	afx_msg void OnOptPromijeniPar();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIM_H__19A7B303_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_)
