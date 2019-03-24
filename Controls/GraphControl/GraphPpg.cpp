// GraphPpg.cpp : Implementation of the CGraphPropPage property page class.

#include "stdafx.h"
#include "GraphControl.h"
#include "GraphPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGraphPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGraphPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGraphPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGraphPropPage, "GRAPHCONTROL.GraphPropPage.1",
	0x106d39e9, 0xc7af, 0x11d1, 0xaf, 0xfe, 0, 0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// CGraphPropPage::CGraphPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGraphPropPage

BOOL CGraphPropPage::CGraphPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GRAPH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGraphPropPage::CGraphPropPage - Constructor

CGraphPropPage::CGraphPropPage() :
	COlePropertyPage(IDD, IDS_GRAPH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGraphPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGraphPropPage::DoDataExchange - Moves data between page and properties

void CGraphPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGraphPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGraphPropPage message handlers
