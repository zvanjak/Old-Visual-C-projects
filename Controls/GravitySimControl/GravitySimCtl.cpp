// GravitySimCtl.cpp : Implementation of the CGravitySimCtrl ActiveX Control class.

#include "stdafx.h"
#include "GravitySimControl.h"
#include "GravitySimCtl.h"
#include "GravitySimCtrlPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGravitySimCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGravitySimCtrl, COleControl)
	//{{AFX_MSG_MAP(CGravitySimCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGravitySimCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGravitySimCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGravitySimCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGravitySimCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGravitySimCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGravitySimCtrl, 1)
	PROPPAGEID(CGravitySimCtrlPropPage::guid)
END_PROPPAGEIDS(CGravitySimCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGravitySimCtrl, "GRAVITYSIMCONTROL.GravitySimlCtrl.1",
	0x566a578, 0xc260, 0x11d2, 0x96, 0x49, 0, 0xc0, 0xdf, 0xe5, 0x27, 0x8a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGravitySimCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGravitySimCtrl =
		{ 0x566a576, 0xc260, 0x11d2, { 0x96, 0x49, 0, 0xc0, 0xdf, 0xe5, 0x27, 0x8a } };
const IID BASED_CODE IID_DGravitySimCtrlEvents =
		{ 0x566a577, 0xc260, 0x11d2, { 0x96, 0x49, 0, 0xc0, 0xdf, 0xe5, 0x27, 0x8a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGravitySimCtrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGravitySimCtrl, IDS_GRAVITYSIMCTRL, _dwGravitySimCtrlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::CGravitySimCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGravitySimCtrl

BOOL CGravitySimCtrl::CGravitySimCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GRAVITYSIMCTRL,
			IDB_GRAVITYSIMCTRL,
			afxRegApartmentThreading,
			_dwGravitySimCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("GravitySimControl.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1999 ZPM";


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::CGravitySimCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CGravitySimCtrl::CGravitySimCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::CGravitySimCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CGravitySimCtrl::CGravitySimCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::CGravitySimCtrl - Constructor

CGravitySimCtrl::CGravitySimCtrl()
{
	InitializeIIDs(&IID_DGravitySimCtrl, &IID_DGravitySimCtrlEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::~CGravitySimCtrl - Destructor

CGravitySimCtrl::~CGravitySimCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::OnDraw - Drawing function

void CGravitySimCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::DoPropExchange - Persistence support

void CGravitySimCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::OnResetState - Reset control to default state

void CGravitySimCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl::AboutBox - Display an "About" box to the user

void CGravitySimCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GRAVITYSIMCTRL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl message handlers
