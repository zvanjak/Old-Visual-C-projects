// MathGraphStatPage.cpp : implementation file
//

#include "stdafx.h"
#include "mathgraph.h"
#include "MathGraphStatPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage dialog

IMPLEMENT_DYNCREATE(CMathGraphStatPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphStatPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMathGraphStatPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {BDCC3AA8-BE5F-11D1-AFF7-0000C03E618C}
IMPLEMENT_OLECREATE_EX(CMathGraphStatPage, "MathGraph.CMathGraphStatPage",
	0xbdcc3aa8, 0xbe5f, 0x11d1, 0xaf, 0xf7, 0x0, 0x0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage::CMathGraphStatPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphStatPage

BOOL CMathGraphStatPage::CMathGraphStatPageFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MATHGRAPH_STAT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage::CMathGraphStatPage - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

CMathGraphStatPage::CMathGraphStatPage() :
	COlePropertyPage(IDD, IDS_MATHGRAPH_STAT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMathGraphStatPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage::DoDataExchange - Moves data between page and properties

void CMathGraphStatPage::DoDataExchange(CDataExchange* pDX)
{
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_DATA_MAP(CMathGraphStatPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage message handlers
