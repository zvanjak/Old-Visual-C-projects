// CalcControlCtl.cpp : Implementation of the CCalcControlCtrl ActiveX Control class.

#include "stdafx.h"
#include "CalcControl.h"
#include "CalcControlCtl.h"
#include "CalcControlPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCalcControlCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCalcControlCtrl, COleControl)
	//{{AFX_MSG_MAP(CCalcControlCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CCalcControlCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CCalcControlCtrl)
	DISP_FUNCTION(CCalcControlCtrl, "Calc", Calc, VT_R8, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CCalcControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CCalcControlCtrl, COleControl)
	//{{AFX_EVENT_MAP(CCalcControlCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCalcControlCtrl, 1)
	PROPPAGEID(CCalcControlPropPage::guid)
END_PROPPAGEIDS(CCalcControlCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCalcControlCtrl, "CALCCONTROL.CalcControlCtrl.1",
	0x6c2653fa, 0xf934, 0x11d1, 0x91, 0x3a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CCalcControlCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DCalcControl =
		{ 0x6c2653f8, 0xf934, 0x11d1, { 0x91, 0x3a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };
const IID BASED_CODE IID_DCalcControlEvents =
		{ 0x6c2653f9, 0xf934, 0x11d1, { 0x91, 0x3a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwCalcControlOleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCalcControlCtrl, IDS_CALCCONTROL, _dwCalcControlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::CCalcControlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCalcControlCtrl

BOOL CCalcControlCtrl::CCalcControlCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_CALCCONTROL,
			IDB_CALCCONTROL,
			afxRegApartmentThreading,
			_dwCalcControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::CCalcControlCtrl - Constructor

CCalcControlCtrl::CCalcControlCtrl()
{
	InitializeIIDs(&IID_DCalcControl, &IID_DCalcControlEvents);

	EnableSimpleFrame();

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::~CCalcControlCtrl - Destructor

CCalcControlCtrl::~CCalcControlCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::OnDraw - Drawing function

void CCalcControlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::DoPropExchange - Persistence support

void CCalcControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::OnResetState - Reset control to default state

void CCalcControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl::AboutBox - Display an "About" box to the user

void CCalcControlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CALCCONTROL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl message handlers

double CCalcControlCtrl::Calc(LPCTSTR szLine) 
{
	double	ret;
	char		str[200];
	int			hFunc;

	strcpy(str, szLine);
	if( (hFunc = Mth.DefineFunction(str)) >= 0 )
	{ 
		ret = Mth.Evaluate(hFunc));
		Mth.UndefineFunction(hFunc);
	}
	else
		ret = 0.0;

	return ret;
}
