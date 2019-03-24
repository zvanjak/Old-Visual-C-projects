#if !defined(AFX_PRIKAZRASPOREDAISPITA_H__21524174_60AC_4798_8D2D_22258CD28966__INCLUDED_)
#define AFX_PRIKAZRASPOREDAISPITA_H__21524174_60AC_4798_8D2D_22258CD28966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PrikazRasporedaIspita.h : main header file for PRIKAZRASPOREDAISPITA.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaApp : See PrikazRasporedaIspita.cpp for implementation.

class CPrikazRasporedaIspitaApp : public COleControlModule
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

#endif // !defined(AFX_PRIKAZRASPOREDAISPITA_H__21524174_60AC_4798_8D2D_22258CD28966__INCLUDED)
