//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGPOPISISPITA_H__7FB08E93_7A34_11D3_A9C2_00C0DFE5278A__INCLUDED_)
#define AFX_DLGPOPISISPITA_H__7FB08E93_7A34_11D3_A9C2_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPopisIspita.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPopisIspita dialog

class CDlgPopisIspita : public CDialog
{
// Construction
public:
	CDlgPopisIspita(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPopisIspita)
	enum { IDD = IDD_POPIS_ISPITA };
	CButton	m_ctrlButtDatumi;
	CButton	m_ctrlButtDani;
	CMSFlexGrid	m_ctrlGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPopisIspita)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	bool		m_bPrikazDani;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPopisIspita)
	afx_msg void OnCheckDani();
	afx_msg void OnCheckDatumi();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOPISISPITA_H__7FB08E93_7A34_11D3_A9C2_00C0DFE5278A__INCLUDED_)
