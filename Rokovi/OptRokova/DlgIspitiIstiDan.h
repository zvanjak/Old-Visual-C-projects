#if !defined(AFX_DLGISPITIISTIDAN_H__A26A1403_7BC4_11D3_A9C5_00C0DFE5278A__INCLUDED_)
#define AFX_DLGISPITIISTIDAN_H__A26A1403_7BC4_11D3_A9C5_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIspitiIstiDan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIspitiIstiDan dialog

class CDlgIspitiIstiDan : public CDialog
{
// Construction
public:
	CDlgIspitiIstiDan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIspitiIstiDan)
	enum { IDD = IDD_PREGLED_ISPITI_ISTI_DAN };
	CListBox	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIspitiIstiDan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIspitiIstiDan)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGISPITIISTIDAN_H__A26A1403_7BC4_11D3_A9C5_00C0DFE5278A__INCLUDED_)
