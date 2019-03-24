//{{AFX_INCLUDES()
#include "scrollbar.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIZUALNIPRIKAZ_H__F6EAA85A_7AF9_11D3_A9C3_00C0DFE5278A__INCLUDED_)
#define AFX_DLGVIZUALNIPRIKAZ_H__F6EAA85A_7AF9_11D3_A9C3_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVizualniPrikaz.h : header file
//

#include "OptRokDoc.h"

#define		X0				11
#define		Y0				11
#define		HEIGHT		560
#define		WIDTH			970

#define		MAX_ISP_NA_EKRANU		35


/////////////////////////////////////////////////////////////////////////////
// CDlgVizualniPrikaz dialog

class CDlgVizualniPrikaz : public CDialog
{
// Construction
public:
	CDlgVizualniPrikaz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVizualniPrikaz)
	enum { IDD = IDD_VIZUALNI_PRIKAZ };
	CButton	m_ctrlButtZim;
	CButton	m_ctrlButtProlj;
	CButton	m_ctrlButtLjet;
	CButton	m_ctrlButtJesIzv;
	CButton	m_ctrlButtJes;
	CScrollbar	m_ctrlVScroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVizualniPrikaz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void			PrintConfig();

	bool			bTermSelected;		// kada se klikne mišem na termin odreðenog ispita èiji se termin želi promijeniti
	int				nRow, nOldTerm, nRok;				// redak i stupac u kojem je selektiran

	int				m_VertPos;				// pozicija scrollbar-a
	int				m_StartWith;			// sa kojim rednimn brojem predmeta poèinje ispis na ekran
	int				m_SelIspit;				// koji ispit je odabran da s eprikazuju njeogvi presjeci sa ostalima

	TerminRoka		m_Rok;

	int				DanIspita( COptRokDoc	*pDoc, int BrIsp, int BrRok );
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVizualniPrikaz)
	afx_msg void OnOk();
	afx_msg void OnChangeVizualniPrikazVscroll();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCheckJesizv();
	afx_msg void OnCheckZim();
	afx_msg void OnCheckProlj();
	afx_msg void OnCheckLjet();
	afx_msg void OnCheckJes();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIZUALNIPRIKAZ_H__F6EAA85A_7AF9_11D3_A9C3_00C0DFE5278A__INCLUDED_)
