// OptSchedule.h : main header file for the OPTSCHEDULE application
//

#if !defined(AFX_OPTSCHEDULE_H__50F97942_F392_46AA_8C3F_30AC77B3AC35__INCLUDED_)
#define AFX_OPTSCHEDULE_H__50F97942_F392_46AA_8C3F_30AC77B3AC35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COptScheduleApp:
// See OptSchedule.cpp for the implementation of this class
//

class COptScheduleApp : public CWinApp
{
public:
	COptScheduleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptScheduleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(COptScheduleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTSCHEDULE_H__50F97942_F392_46AA_8C3F_30AC77B3AC35__INCLUDED_)
