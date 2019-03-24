// SchroedingerEq.h : main header file for the SCHROEDINGEREQ application
//

#if !defined(AFX_SCHROEDINGEREQ_H__EFEED4F1_CB87_4599_A3E2_A38AB0FE4E21__INCLUDED_)
#define AFX_SCHROEDINGEREQ_H__EFEED4F1_CB87_4599_A3E2_A38AB0FE4E21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSchEqApp:
// See SchroedingerEq.cpp for the implementation of this class
//

class CSchEqApp : public CWinApp
{
public:
	CSchEqApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchEqApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSchEqApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHROEDINGEREQ_H__EFEED4F1_CB87_4599_A3E2_A38AB0FE4E21__INCLUDED_)
