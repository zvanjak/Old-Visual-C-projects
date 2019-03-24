// PrikazRasporedaIspitaPpg.cpp : Implementation of the CPrikazRasporedaIspitaPropPage property page class.

#include "stdafx.h"
#include "PrikazRasporedaIspita.h"
#include "PrikazRasporedaIspitaPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPrikazRasporedaIspitaPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPrikazRasporedaIspitaPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPrikazRasporedaIspitaPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPrikazRasporedaIspitaPropPage, "PRIKAZRASPOREDAISPITA.PrikazRasporedaIspitaPropPage.1",
	0x81678bb3, 0x9c70, 0x48c4, 0x89, 0xc3, 0x25, 0xc6, 0x22, 0xad, 0xca, 0xf9)


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaPropPage::CPrikazRasporedaIspitaPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPrikazRasporedaIspitaPropPage

BOOL CPrikazRasporedaIspitaPropPage::CPrikazRasporedaIspitaPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PRIKAZRASPOREDAISPITA_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaPropPage::CPrikazRasporedaIspitaPropPage - Constructor

CPrikazRasporedaIspitaPropPage::CPrikazRasporedaIspitaPropPage() :
	COlePropertyPage(IDD, IDS_PRIKAZRASPOREDAISPITA_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPrikazRasporedaIspitaPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaPropPage::DoDataExchange - Moves data between page and properties

void CPrikazRasporedaIspitaPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPrikazRasporedaIspitaPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaPropPage message handlers
