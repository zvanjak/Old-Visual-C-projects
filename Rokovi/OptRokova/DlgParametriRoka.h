#if !defined(AFX_DLGPARAMETRIROKA_H__85982E38_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
#define AFX_DLGPARAMETRIROKA_H__85982E38_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParametriRoka.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgParametriRoka dialog

class CDlgParametriRoka : public CDialog
{
// Construction
public:
	CDlgParametriRoka(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParametriRoka)
	enum { IDD = IDD_PARAMETRI_ROKA };
	CMonthCalCtrl	m_ctrlZavrsetak;
	CMonthCalCtrl	m_ctrlPocetak;
	CButton	m_ctrlZim;
	CButton	m_ctrlLJet;
	CButton	m_ctrlProljet;
	CButton	m_ctrlJesIzv;
	CButton	m_ctrlJes;
	int		m_nBrojRokova;
	//}}AFX_DATA

	Date				dateStart;
	Date				dateEnd;
	TerminRoka	Vrsta;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParametriRoka)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParametriRoka)
	afx_msg void OnSelectDatumPocetka(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSelectDatumZavrsetka(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRokJesenski();
	afx_msg void OnRokJesenskiIzv();
	afx_msg void OnRokLjetni();
	afx_msg void OnRokProljetni();
	afx_msg void OnRokZimski();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARAMETRIROKA_H__85982E38_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
