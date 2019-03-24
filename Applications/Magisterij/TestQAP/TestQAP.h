// TestQAP.h : main header file for the TESTQAP application
//

#if !defined(AFX_TESTQAP_H__6D47D7F1_8B1F_4911_93E9_863E25C90E6D__INCLUDED_)
#define AFX_TESTQAP_H__6D47D7F1_8B1F_4911_93E9_863E25C90E6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestQAPApp:
// See TestQAP.cpp for the implementation of this class
//

//##ModelId=39571AB0015A
class CTestQAPApp : public CWinApp
{
public:
	//##ModelId=39571AB00170
	CTestQAPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestQAPApp)
	public:
	//##ModelId=39571AB0016F
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestQAPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTQAP_H__6D47D7F1_8B1F_4911_93E9_863E25C90E6D__INCLUDED_)
