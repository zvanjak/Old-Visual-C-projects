//{{AFX_INCLUDES()
#include "graph.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGGRAPH_H__11D86FE6_EEF6_4FA0_B93B_A56ED8EA1ABC__INCLUDED_)
#define AFX_DLGGRAPH_H__11D86FE6_EEF6_4FA0_B93B_A56ED8EA1ABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGraph dialog

class CDlgGraph : public CDialog
{
// Construction
public:
	CDlgGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGraph)
	enum { IDD = IDD_SHOW_GRAPH };
	CGraph	m_ctrlGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGraph)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRAPH_H__11D86FE6_EEF6_4FA0_B93B_A56ED8EA1ABC__INCLUDED_)
