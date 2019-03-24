// OptRok.h : main header file for the OPTROK application
//

#if !defined(AFX_OPTROK_H__D3FC8A41_7F9C_44B8_A99A_3F5B4A9267DB__INCLUDED_)
#define AFX_OPTROK_H__D3FC8A41_7F9C_44B8_A99A_3F5B4A9267DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COptRokApp:
// See OptRok.cpp for the implementation of this class
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
	COleTemplateServer m_server;
		// Server object for document creation
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

#endif // !defined(AFX_OPTROK_H__D3FC8A41_7F9C_44B8_A99A_3F5B4A9267DB__INCLUDED_)
