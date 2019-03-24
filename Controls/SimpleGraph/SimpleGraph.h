#if !defined(AFX_SIMPLEGRAPH_H__A2AF24D9_BA11_47E9_9637_71302D2BA34F__INCLUDED_)
#define AFX_SIMPLEGRAPH_H__A2AF24D9_BA11_47E9_9637_71302D2BA34F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SimpleGraph.h : main header file for SIMPLEGRAPH.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphApp : See SimpleGraph.cpp for implementation.

class CSimpleGraphApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEGRAPH_H__A2AF24D9_BA11_47E9_9637_71302D2BA34F__INCLUDED)
