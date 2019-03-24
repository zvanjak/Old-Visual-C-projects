#if !defined(AFX_DLGSETMODELDESCR_H__F26AE94C_55AB_4BED_9B78_9002764EC764__INCLUDED_)
#define AFX_DLGSETMODELDESCR_H__F26AE94C_55AB_4BED_9B78_9002764EC764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetModelDescr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetModelDescr dialog

class CDlgSetModelDescr : public CDialog
{
// Construction
public:
	CDlgSetModelDescr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetModelDescr)
	enum { IDD = IDD_SET_MODEL_DATA };
	int		m_nBrojStudLow;
	int		m_nBrojStudUpp;
	int		m_nSemLow;
	int		m_nSemUpp;
	BOOL	m_bDiplomski;
	BOOL	m_bHuman;
	BOOL	m_bIzborni;
	BOOL	m_bObavezni;
	BOOL	m_bSeminar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetModelDescr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetModelDescr)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETMODELDESCR_H__F26AE94C_55AB_4BED_9B78_9002764EC764__INCLUDED_)
