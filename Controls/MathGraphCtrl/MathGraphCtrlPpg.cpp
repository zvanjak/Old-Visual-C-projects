// MathGraphCtrlPpg.cpp : Implementation of the CMathGraphCtrlPropPage property page class.

#include "stdafx.h"
#include "MathGraphCtrl.h"
#include "MathGraphCtrlPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMathGraphCtrlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphCtrlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMathGraphCtrlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMathGraphCtrlPropPage, "MATHGRAPHCTRL.MathGraphCtrlPropPage.1",
	0x945b8406, 0x14c0, 0x11d2, 0x91, 0x54, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlPropPage::CMathGraphCtrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphCtrlPropPage

BOOL CMathGraphCtrlPropPage::CMathGraphCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MATHGRAPHCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlPropPage::CMathGraphCtrlPropPage - Constructor

CMathGraphCtrlPropPage::CMathGraphCtrlPropPage() :
	COlePropertyPage(IDD, IDS_MATHGRAPHCTRL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMathGraphCtrlPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlPropPage::DoDataExchange - Moves data between page and properties

void CMathGraphCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMathGraphCtrlPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlPropPage message handlers
