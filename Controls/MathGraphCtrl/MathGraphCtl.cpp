// MathGraphCtl.cpp : Implementation of the CMathGraphCtrl ActiveX Control class.

#include "stdafx.h"
#include "MathGraphCtrl.h"
#include "MathGraphCtl.h"
#include "MathGraphCtrlPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMathGraphCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_MSG_MAP(CMathGraphCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMathGraphCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMathGraphCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMathGraphCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMathGraphCtrl, 1)
	PROPPAGEID(CMathGraphCtrlPropPage::guid)
END_PROPPAGEIDS(CMathGraphCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMathGraphCtrl, "MATHGRAPHCTRL.MathGraphCtrl.1",
	0x945b8405, 0x14c0, 0x11d2, 0x91, 0x54, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMathGraphCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMathGraphCtrl =
		{ 0x945b8403, 0x14c0, 0x11d2, { 0x91, 0x54, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };
const IID BASED_CODE IID_DMathGraphCtrlEvents =
		{ 0x945b8404, 0x14c0, 0x11d2, { 0x91, 0x54, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMathGraphCtrlOleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMathGraphCtrl, IDS_MATHGRAPHCTRL, _dwMathGraphCtrlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphCtrl

BOOL CMathGraphCtrl::CMathGraphCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_MATHGRAPHCTRL,
			IDB_MATHGRAPHCTRL,
			afxRegApartmentThreading,
			_dwMathGraphCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrl - Constructor

CMathGraphCtrl::CMathGraphCtrl()
{
	InitializeIIDs(&IID_DMathGraphCtrl, &IID_DMathGraphCtrlEvents);

	EnableSimpleFrame();

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::~CMathGraphCtrl - Destructor

CMathGraphCtrl::~CMathGraphCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::OnDraw - Drawing function

void CMathGraphCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::DoPropExchange - Persistence support

void CMathGraphCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::OnResetState - Reset control to default state

void CMathGraphCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::AboutBox - Display an "About" box to the user

void CMathGraphCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MATHGRAPHCTRL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl message handlers

int CMathGraphCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//	m_ctrlGraph.Create("Caption jumbo", WS_VISIBLE, CRect(0,0,500,500), this, 0);
	
	return 0;
}
/*
void CMathGraphCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( nType == SIZE_RESTORED )
	{
		CRect		rect;
		GetClientRect(&rect);
		m_ctrlGraph.SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW );	
	}
	
}
*/
