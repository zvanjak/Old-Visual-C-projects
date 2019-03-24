#if !defined(AFX_GRAPHCONTROL_H__106D39EE_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_)
#define AFX_GRAPHCONTROL_H__106D39EE_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GraphControl.h : main header file for GRAPHCONTROL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphControlApp : See GraphControl.cpp for implementation.

class CGraphControlApp : public COleControlModule
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

#endif // !defined(AFX_GRAPHCONTROL_H__106D39EE_C7AF_11D1_AFFE_0000C03E618C__INCLUDED)
