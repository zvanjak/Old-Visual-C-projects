// expresionDlg.h : header file
//

#if !defined(AFX_EXPRESIONDLG_H__DA6A6CE9_FD20_11D1_8960_00002145DF63__INCLUDED_)
#define AFX_EXPRESIONDLG_H__DA6A6CE9_FD20_11D1_8960_00002145DF63__INCLUDED_

#include "Express.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CExpresionDlg dialog

class CExpresionDlg : public CDialog
{
// Construction
public:
	CMapVariabile m_VarsMap;
	CExpression m_expression;
	CExpresionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExpresionDlg)
	enum { IDD = IDD_EXPRESION_DIALOG };
	CString	m_ExprStr;
	double	m_Result;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpresionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExpresionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCalculate();
	afx_msg void OnInsertVar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPRESIONDLG_H__DA6A6CE9_FD20_11D1_8960_00002145DF63__INCLUDED_)
