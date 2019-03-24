//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIEWDATA_H__55455A57_8A61_4BA7_AF49_BC1A5D7C86DE__INCLUDED_)
#define AFX_DLGVIEWDATA_H__55455A57_8A61_4BA7_AF49_BC1A5D7C86DE__INCLUDED_

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
	CMSFlexGrid	m_ctrlGridA;
	CMSFlexGrid	m_ctrlGridB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewData)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWDATA_H__55455A57_8A61_4BA7_AF49_BC1A5D7C86DE__INCLUDED_)
