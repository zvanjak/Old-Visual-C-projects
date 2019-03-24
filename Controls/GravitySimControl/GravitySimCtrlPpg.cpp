// GravitySimCtrlPpg.cpp : Implementation of the CGravitySimCtrlPropPage property page class.

#include "stdafx.h"
#include "GravitySimControl.h"
#include "GravitySimCtrlPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGravitySimCtrlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGravitySimCtrlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGravitySimCtrlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGravitySimCtrlPropPage, "GRAVITYSIMCTRL.GravitySimCtrlPropPage.1",
	0x566a579, 0xc260, 0x11d2, 0x96, 0x49, 0, 0xc0, 0xdf, 0xe5, 0x27, 0x8a)


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrlPropPage::CGravitySimCtrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGravitySimCtrlPropPage

BOOL CGravitySimCtrlPropPage::CGravitySimCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GRAVITYSIMCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrlPropPage::CGravitySimCtrlPropPage - Constructor

CGravitySimCtrlPropPage::CGravitySimCtrlPropPage() :
	COlePropertyPage(IDD, IDS_GRAVITYSIMCTRL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGravitySimCtrlPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT

	SetHelpInfo(_T("Names to appear in the control"), _T("GRAVITYSIMCONTROL.HLP"), 0);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrlPropPage::DoDataExchange - Moves data between page and properties

void CGravitySimCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGravitySimCtrlPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrlPropPage message handlers
