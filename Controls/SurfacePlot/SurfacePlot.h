#if !defined(AFX_SURFACEPLOT_H__7E0D9EE2_075A_11D2_914A_00C0DFE52874__INCLUDED_)
#define AFX_SURFACEPLOT_H__7E0D9EE2_075A_11D2_914A_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SurfacePlot.h : main header file for SURFACEPLOT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotApp : See SurfacePlot.cpp for implementation.

class CSurfacePlotApp : public COleControlModule
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

#endif // !defined(AFX_SURFACEPLOT_H__7E0D9EE2_075A_11D2_914A_00C0DFE52874__INCLUDED)
