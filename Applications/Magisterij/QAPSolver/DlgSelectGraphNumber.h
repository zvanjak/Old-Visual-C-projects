#if !defined(AFX_DLGSELECTGRAPHNUMBER_H__EAC4B15C_D644_469B_B2E9_04EE5CA9866E__INCLUDED_)
#define AFX_DLGSELECTGRAPHNUMBER_H__EAC4B15C_D644_469B_B2E9_04EE5CA9866E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectGraphNumber.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGraphNumber dialog

class CDlgSelectGraphNumber : public CDialog
{
// Construction
public:
	CDlgSelectGraphNumber(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelectGraphNumber)
	enum { IDD = IDD_SELECT_GRAPH_DLG };
	int		m_nGraphNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectGraphNumber)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectGraphNumber)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTGRAPHNUMBER_H__EAC4B15C_D644_469B_B2E9_04EE5CA9866E__INCLUDED_)
