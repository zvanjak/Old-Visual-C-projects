// SimpleGraphPpg.cpp : Implementation of the CSimpleGraphPropPage property page class.

#include "stdafx.h"
#include "SimpleGraph.h"
#include "SimpleGraphPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSimpleGraphPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSimpleGraphPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSimpleGraphPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSimpleGraphPropPage, "SIMPLEGRAPH.SimpleGraphPropPage.1",
	0xe621a910, 0xf74, 0x4453, 0xa0, 0x8e, 0x92, 0x33, 0x1, 0x93, 0x9f, 0xec)


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphPropPage::CSimpleGraphPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSimpleGraphPropPage

BOOL CSimpleGraphPropPage::CSimpleGraphPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SIMPLEGRAPH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphPropPage::CSimpleGraphPropPage - Constructor

CSimpleGraphPropPage::CSimpleGraphPropPage() :
	COlePropertyPage(IDD, IDS_SIMPLEGRAPH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSimpleGraphPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphPropPage::DoDataExchange - Moves data between page and properties

void CSimpleGraphPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSimpleGraphPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphPropPage message handlers
