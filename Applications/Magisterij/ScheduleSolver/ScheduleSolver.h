// ScheduleSolver.h : main header file for the SCHEDULESOLVER application
//

#if !defined(AFX_SCHEDULESOLVER_H__E56FAEF0_AEFF_4803_93A2_61BC19FFD09C__INCLUDED_)
#define AFX_SCHEDULESOLVER_H__E56FAEF0_AEFF_4803_93A2_61BC19FFD09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSchSolverApp:
// See ScheduleSolver.cpp for the implementation of this class
//

//##ModelId=39571A9902BF
class CSchSolverApp : public CWinApp
{
public:
	//##ModelId=39571A9902F3
	CSchSolverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchSolverApp)
	public:
	//##ModelId=39571A9902F2
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//##ModelId=39571A9902DF
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CSchSolverApp)
	//##ModelId=39571A9902F1
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULESOLVER_H__E56FAEF0_AEFF_4803_93A2_61BC19FFD09C__INCLUDED_)
