// MathGraphSecPage.cpp : implementation file
//

#include "stdafx.h"
#include "mathgraph.h"
#include "MathGraphSecPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage dialog

IMPLEMENT_DYNCREATE(CMathGraphSecPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphSecPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMathGraphSecPage)
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_SELECTED, OnSelchangeSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {BDCC3AA5-BE5F-11D1-AFF7-0000C03E618C}
IMPLEMENT_OLECREATE_EX(CMathGraphSecPage, "MathGraph.CMathGraphSecPage",
	0xbdcc3aa5, 0xbe5f, 0x11d1, 0xaf, 0xf7, 0x0, 0x0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage::CMathGraphSecPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphSecPage

BOOL CMathGraphSecPage::CMathGraphSecPageFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MATHGRAPH_SEC_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage::CMathGraphSecPage - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

CMathGraphSecPage::CMathGraphSecPage() :
	COlePropertyPage(IDD, IDS_MATHGRAPH_SEC_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMathGraphSecPage)
	m_nGraphType = -1;
	m_nXAxisVar = 0;
	m_nYAxisVar = 0;
	m_nZAxisVar = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage::DoDataExchange - Moves data between page and properties

void CMathGraphSecPage::DoDataExchange(CDataExchange* pDX)
{
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_DATA_MAP(CMathGraphSecPage)
	DDP_CBIndex(pDX, IDC_SELECTED, m_nGraphType, _T("GraphType") );
	DDX_CBIndex(pDX, IDC_SELECTED, m_nGraphType);
	DDP_Text(pDX, IDC_X_AXIS, m_nXAxisVar, _T("XAxisVar") );
	DDX_Text(pDX, IDC_X_AXIS, m_nXAxisVar);
	DDV_MinMaxInt(pDX, m_nXAxisVar, 0, 4);
	DDP_Text(pDX, IDC_Y_AXIS, m_nYAxisVar, _T("YAxisVar") );
	DDX_Text(pDX, IDC_Y_AXIS, m_nYAxisVar);
	DDV_MinMaxInt(pDX, m_nYAxisVar, 0, 4);
	DDP_Text(pDX, IDC_Z_AXIS, m_nZAxisVar, _T("ZAxisVar") );
	DDX_Text(pDX, IDC_Z_AXIS, m_nZAxisVar);
	DDV_MinMaxInt(pDX, m_nZAxisVar, 0, 4);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage message handlers


void CMathGraphSecPage::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	char		str[100];
/*	sprintf(str, "Pozicija - %d, %d", point.x, point.y);
	AfxMessageBox(str);*/
	
	CComboBox *m_ctrlSelected = (CComboBox *) GetDlgItem(IDC_SELECTED);

	if( point.x > 25 && point.x < 78 && point.y > 30 && point.y < 82 )
	{
		m_ctrlSelected->SetCurSel(0);
		SetSelection(0);
	}
	else 	if( point.x > 100 && point.x < 154 && point.y > 30 && point.y < 82 )
	{
		m_ctrlSelected->SetCurSel(1);
		SetSelection(1);
	}
//	COlePropertyPage::OnLButtonDown(nFlags, point);
}

void CMathGraphSecPage::SetSelection(int nSel)
{
/*	if( nSel >= 0 && nSel < 6 )
	{
		CEdit	*pEdit = (CEdit *) GetDlgItem(IDC_DESCRIPTION);
		pEdit->SetSel( 0,-1 );
		pEdit->Clear();

		switch(nSel)
		{
			case 0 :	pEdit->ReplaceSel("Graph selected"); break;
			case 1 :	pEdit->ReplaceSel("Phase selected"); break;
			case 2 :	pEdit->ReplaceSel("Phase3D selected"); break;
			case 3 :	pEdit->ReplaceSel("Surface selected"); break;
			case 4 :	pEdit->ReplaceSel("Fitt linear selected"); break;
			case 5 :	pEdit->ReplaceSel("Fitt polynom selected"); break;
		}
	}*/
}

void CMathGraphSecPage::OnSelchangeSelected() 
{
	CComboBox *m_ctrlSelected = (CComboBox *) GetDlgItem(IDC_SELECTED);

	int	ind = m_ctrlSelected->GetCurSel();
	SetSelection(ind);
}

BOOL CMathGraphSecPage::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
