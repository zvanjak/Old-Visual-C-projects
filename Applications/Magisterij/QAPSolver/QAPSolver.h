// QAPSolver.h : main header file for the QAPSOLVER application
//

#if !defined(AFX_QAPSOLVER_H__8953D230_DBFD_4793_AE14_C5EE0D1D03DA__INCLUDED_)
#define AFX_QAPSOLVER_H__8953D230_DBFD_4793_AE14_C5EE0D1D03DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

void	EnableEditCtrl(CDialog *pDlg, int nID, BOOL flag);

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverApp:
// See QAPSolver.cpp for the implementation of this class
//

class CQAPSolverApp : public CWinApp
{
public:
	CQAPSolverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAPSolverApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CQAPSolverApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QAPSOLVER_H__8953D230_DBFD_4793_AE14_C5EE0D1D03DA__INCLUDED_)
