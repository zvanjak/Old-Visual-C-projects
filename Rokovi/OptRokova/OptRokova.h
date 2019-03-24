// OptRokova.h : main header file for the OPTROKOVA application
//

#if !defined(AFX_OPTROKOVA_H__85982E27_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
#define AFX_OPTROKOVA_H__85982E27_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COptRokApp:
// See OptRokova.cpp for the implementation of this class
//

class COptRokApp : public CWinApp
{
public:
	COptRokApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COptRokApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKOVA_H__85982E27_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
