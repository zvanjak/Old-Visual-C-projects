// CalcControlPpg.cpp : Implementation of the CCalcControlPropPage property page class.

#include "stdafx.h"
#include "CalcControl.h"
#include "CalcControlPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCalcControlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCalcControlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CCalcControlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCalcControlPropPage, "CALCCONTROL.CalcControlPropPage.1",
	0x6c2653fb, 0xf934, 0x11d1, 0x91, 0x3a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// CCalcControlPropPage::CCalcControlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCalcControlPropPage

BOOL CCalcControlPropPage::CCalcControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CALCCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlPropPage::CCalcControlPropPage - Constructor

CCalcControlPropPage::CCalcControlPropPage() :
	COlePropertyPage(IDD, IDS_CALCCONTROL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CCalcControlPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlPropPage::DoDataExchange - Moves data between page and properties

void CCalcControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCalcControlPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CCalcControlPropPage message handlers
