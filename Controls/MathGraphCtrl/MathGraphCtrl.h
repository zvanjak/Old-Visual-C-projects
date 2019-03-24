#if !defined(AFX_MATHGRAPHCTRL_H__945B840B_14C0_11D2_9154_00C0DFE52874__INCLUDED_)
#define AFX_MATHGRAPHCTRL_H__945B840B_14C0_11D2_9154_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraphCtrl.h : main header file for MATHGRAPHCTRL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlApp : See MathGraphCtrl.cpp for implementation.

class CMathGraphCtrlApp : public COleControlModule
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

#endif // !defined(AFX_MATHGRAPHCTRL_H__945B840B_14C0_11D2_9154_00C0DFE52874__INCLUDED)
