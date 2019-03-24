// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "TestNumFramework.h"
#include "DlgProxy.h"
#include "TestNumFrameworkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlgAutoProxy

IMPLEMENT_DYNCREATE(CTestDlgAutoProxy, CCmdTarget)

CTestDlgAutoProxy::CTestDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CTestDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CTestDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CTestDlgAutoProxy::~CTestDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CTestDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CTestDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTestDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTestDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ITestNumFramework to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {CEB2F5A3-3E14-45B5-A8C0-C151039F0769}
static const IID IID_ITestNumFramework =
{ 0xceb2f5a3, 0x3e14, 0x45b5, { 0xa8, 0xc0, 0xc1, 0x51, 0x3, 0x9f, 0x7, 0x69 } };

BEGIN_INTERFACE_MAP(CTestDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CTestDlgAutoProxy, IID_ITestNumFramework, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {EE33A12D-74A0-42C3-B771-A62BF6CC785A}
IMPLEMENT_OLECREATE2(CTestDlgAutoProxy, "TestNumFramework.Application", 0xee33a12d, 0x74a0, 0x42c3, 0xb7, 0x71, 0xa6, 0x2b, 0xf6, 0xcc, 0x78, 0x5a)

/////////////////////////////////////////////////////////////////////////////
// CTestDlgAutoProxy message handlers
