// SurfacePlotPpg.cpp : Implementation of the CSurfacePlotPropPage property page class.

#include "stdafx.h"
#include "SurfacePlot.h"
#include "SurfacePlotPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSurfacePlotPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSurfacePlotPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSurfacePlotPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSurfacePlotPropPage, "SURFACEPLOT.SurfacePlotPropPage.1",
	0x7e0d9edd, 0x75a, 0x11d2, 0x91, 0x4a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotPropPage::CSurfacePlotPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSurfacePlotPropPage

BOOL CSurfacePlotPropPage::CSurfacePlotPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SURFACEPLOT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotPropPage::CSurfacePlotPropPage - Constructor

CSurfacePlotPropPage::CSurfacePlotPropPage() :
	COlePropertyPage(IDD, IDS_SURFACEPLOT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSurfacePlotPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotPropPage::DoDataExchange - Moves data between page and properties

void CSurfacePlotPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSurfacePlotPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotPropPage message handlers
