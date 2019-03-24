//{{AFX_INCLUDES()
#include "treeview.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIEWDATA_H__B92067EC_202C_4996_ACF0_A16C1E57FD1F__INCLUDED_)
#define AFX_DLGVIEWDATA_H__B92067EC_202C_4996_ACF0_A16C1E57FD1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewData dialog

class CDlgViewData : public CDialog
{
// Construction
public:
	CDlgViewData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewData)
	enum { IDD = IDD_VIEW_DATA };
	CTreeCtrl	m_ctrlTreePresjeci;
	CTreeCtrl	m_ctrlDataTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewData)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWDATA_H__B92067EC_202C_4996_ACF0_A16C1E57FD1F__INCLUDED_)
