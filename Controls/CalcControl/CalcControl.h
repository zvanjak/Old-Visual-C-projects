#if !defined(AFX_CALCCONTROL_H__6C265400_F934_11D1_913A_00C0DFE52874__INCLUDED_)
#define AFX_CALCCONTROL_H__6C265400_F934_11D1_913A_00C0DFE52874__INCLUDED_

#include "mathlib.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CalcControl.h : main header file for CALCCONTROL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalcControlApp : See CalcControl.cpp for implementation.

class CCalcControlApp : public COleControlModule
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

#endif // !defined(AFX_CALCCONTROL_H__6C265400_F934_11D1_913A_00C0DFE52874__INCLUDED)
