#if !defined(AFX_GRAVITYSIMCONTROL_H__0566A57E_C260_11D2_9649_00C0DFE5278A__INCLUDED_)
#define AFX_GRAVITYSIMCONTROL_H__0566A57E_C260_11D2_9649_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GravitySimControl.h : main header file for GRAVITYSIMCONTROL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGravitySimControlApp : See GravitySimControl.cpp for implementation.

class CGravitySimControlApp : public COleControlModule
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

#endif // !defined(AFX_GRAVITYSIMCONTROL_H__0566A57E_C260_11D2_9649_00C0DFE5278A__INCLUDED)
