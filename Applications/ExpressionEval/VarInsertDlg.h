#if !defined(AFX_VARINSERTDLG_H__AC8E70D4_333D_11D2_89A8_00002145DF63__INCLUDED_)
#define AFX_VARINSERTDLG_H__AC8E70D4_333D_11D2_89A8_00002145DF63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VarInsertDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVarInsertDlg dialog

# include "express.h"

class CVarInsertDlg : public CDialog
{
// Construction
public:
	void UpdateVarMapList();
	CMapVariabile * m_pVarsMap;
	CVarInsertDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVarInsertDlg)
	enum { IDD = IDD_VARINSERT };
	CListCtrl	m_VariableListCtrl;
	CString	m_VarName;
	CString	m_VarStrValue;
	BOOL	m_bExpression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVarInsertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVarInsertDlg)
	afx_msg void OnInsertVar();
	virtual BOOL OnInitDialog();
	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARINSERTDLG_H__AC8E70D4_333D_11D2_89A8_00002145DF63__INCLUDED_)
