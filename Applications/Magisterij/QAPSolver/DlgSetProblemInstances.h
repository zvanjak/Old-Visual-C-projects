#if !defined(AFX_DLGSETPROBLEMINSTANCES_H__CDFD436E_2FB9_4DB8_971A_839DF82E9A0C__INCLUDED_)
#define AFX_DLGSETPROBLEMINSTANCES_H__CDFD436E_2FB9_4DB8_971A_839DF82E9A0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetProblemInstances.h : header file
//

#include "QAPCompareDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSetProblemInstances dialog

class CDlgSetProblemInstances : public CDialog
{
// Construction
public:
	CDlgSetProblemInstances(CQAPCompareDoc	*pDoc, CWnd* pParent = NULL);   // standard constructor

	CQAPCompareDoc		*pDoc;

	void Load( int ind );
	void LoadBestSolution( int ind );

// Dialog Data
	//{{AFX_DATA(CDlgSetProblemInstances)
	enum { IDD = IDD_SET_INSTANCES };
	//}}AFX_DATA
	CString		m_strFile[10];
	CString		m_strLabel[10];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetProblemInstances)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetProblemInstances)
	afx_msg void OnBrowseCmd1();
	afx_msg void OnBrowseCmd2();
	afx_msg void OnBrowseCmd3();
	afx_msg void OnBrowseCmd4();
	afx_msg void OnBrowseCmd5();
	afx_msg void OnBrowseCmd6();
	afx_msg void OnBrowseCmd7();
	afx_msg void OnBrowseCmd8();
	afx_msg void OnBrowseCmd9();
	afx_msg void OnBrowseCmd10();
	afx_msg void OnLoadBestsolCmd1();
	afx_msg void OnLoadBestsolCmd10();
	afx_msg void OnLoadBestsolCmd2();
	afx_msg void OnLoadBestsolCmd3();
	afx_msg void OnLoadBestsolCmd4();
	afx_msg void OnLoadBestsolCmd5();
	afx_msg void OnLoadBestsolCmd6();
	afx_msg void OnLoadBestsolCmd7();
	afx_msg void OnLoadBestsolCmd8();
	afx_msg void OnLoadBestsolCmd9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETPROBLEMINSTANCES_H__CDFD436E_2FB9_4DB8_971A_839DF82E9A0C__INCLUDED_)
