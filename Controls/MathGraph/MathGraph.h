#if !defined(AFX_MATHGRAPH_H__81936D2F_BE53_11D1_AFF7_0000C03E618C__INCLUDED_)
#define AFX_MATHGRAPH_H__81936D2F_BE53_11D1_AFF7_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraph.h : main header file for MATHGRAPH.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathGraphApp : See MathGraph.cpp for implementation.

class CMathGraphApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPH_H__81936D2F_BE53_11D1_AFF7_0000C03E618C__INCLUDED)
