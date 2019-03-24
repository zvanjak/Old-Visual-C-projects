// OptimiranjeRokova.h : main header file for the OPTIMIRANJEROKOVA application
//

#if !defined(AFX_OPTIMIRANJEROKOVA_H__E27CF819_2E13_4E3B_97EF_082DC92C15D4__INCLUDED_)
#define AFX_OPTIMIRANJEROKOVA_H__E27CF819_2E13_4E3B_97EF_082DC92C15D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COptRokovaApp:
// See OptimiranjeRokova.cpp for the implementation of this class
//

class COptRokovaApp : public CWinApp
{
public:
	COptRokovaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokovaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(COptRokovaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIMIRANJEROKOVA_H__E27CF819_2E13_4E3B_97EF_082DC92C15D4__INCLUDED_)
