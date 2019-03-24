#if !defined(AFX_DLGVIEWRESULTS_H__CACAE3CD_059F_42EE_817F_BE9EBC381BF4__INCLUDED_)
#define AFX_DLGVIEWRESULTS_H__CACAE3CD_059F_42EE_817F_BE9EBC381BF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults dialog

class CDlgViewResults : public CDialog
{
// Construction
public:
	CDlgViewResults(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewResults)
	enum { IDD = IDD_VIEW_RESULTS };
	CListCtrl	m_ctrlList2;
	CListCtrl	m_ctrlList;
	//}}AFX_DATA

	int			nLevelsNum;
	float		*pNum;
	float		*pBase;
	float		*pPerturb1;
	float		*pPerturb2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewResults)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWRESULTS_H__CACAE3CD_059F_42EE_817F_BE9EBC381BF4__INCLUDED_)
