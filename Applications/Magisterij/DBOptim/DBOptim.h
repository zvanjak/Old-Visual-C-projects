// DBOptim.h : main header file for the DBOPTIM application
//

#if !defined(AFX_DBOPTIM_H__0F49AAC3_7957_476B_AC0F_3132F1858431__INCLUDED_)
#define AFX_DBOPTIM_H__0F49AAC3_7957_476B_AC0F_3132F1858431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDBOptimApp:
// See DBOptim.cpp for the implementation of this class
//

//##ModelId=39571A280335
class CDBOptimApp : public CWinApp
{
public:
	//##ModelId=39571A28035E
	CDBOptimApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBOptimApp)
	public:
	//##ModelId=39571A28035D
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//##ModelId=39571A28034C
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CDBOptimApp)
	//##ModelId=39571A280353
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBOPTIM_H__0F49AAC3_7957_476B_AC0F_3132F1858431__INCLUDED_)
