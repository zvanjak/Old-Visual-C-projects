// JustToInsertChart3D.h : main header file for the JUSTTOINSERTCHART3D application
//

#if !defined(AFX_JUSTTOINSERTCHART3D_H__360464F4_697D_4DE9_8C9B_B696DA508377__INCLUDED_)
#define AFX_JUSTTOINSERTCHART3D_H__360464F4_697D_4DE9_8C9B_B696DA508377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DApp:
// See JustToInsertChart3D.cpp for the implementation of this class
//

class CJustToInsertChart3DApp : public CWinApp
{
public:
	CJustToInsertChart3DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJustToInsertChart3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CJustToInsertChart3DApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUSTTOINSERTCHART3D_H__360464F4_697D_4DE9_8C9B_B696DA508377__INCLUDED_)
