#if !defined(AFX_DLGVIEWBESTSOLUTION_H__A7819072_625C_4BC2_BB6E_5CEFFA997CAF__INCLUDED_)
#define AFX_DLGVIEWBESTSOLUTION_H__A7819072_625C_4BC2_BB6E_5CEFFA997CAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewBestSolution.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewBestSolution dialog

class CDlgViewBestSolution : public CDialog
{
// Construction
public:
	CDlgViewBestSolution(CString s1, CString s2, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewBestSolution)
	enum { IDD = IDD_VIEW_BEST_SOLUTION };
	CString	m_strAssignment;
	CString	m_strValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewBestSolution)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewBestSolution)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWBESTSOLUTION_H__A7819072_625C_4BC2_BB6E_5CEFFA997CAF__INCLUDED_)
