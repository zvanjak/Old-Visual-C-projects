 // MathGraphPpg.cpp : Implementation of the CMathGraphPropPage property page class.

#include "stdafx.h"
#include "MathGraph.h"
#include "MathGraphPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMathGraphPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMathGraphPropPage)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CARTESIAN, OnCartesian)
	ON_BN_CLICKED(IDC_CYLINDRICAL, OnCylindrical)
	ON_BN_CLICKED(IDC_SPHERICAL, OnSpherical)
	ON_BN_CLICKED(IDC_LOG_LOG, OnLogLog)
	ON_BN_CLICKED(IDC_LOG_NORM, OnLogNorm)
	ON_BN_CLICKED(IDC_NORM_LOG, OnNormLog)
	ON_BN_CLICKED(IDC_NORM_NORM, OnNormNorm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMathGraphPropPage, "MATHGRAPH.MathGraphPropPage.1",
	0x81936d2a, 0xbe53, 0x11d1, 0xaf, 0xf7, 0, 0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphPropPage::CMathGraphPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphPropPage

BOOL CMathGraphPropPage::CMathGraphPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MATHGRAPH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphPropPage::CMathGraphPropPage - Constructor

CMathGraphPropPage::CMathGraphPropPage() :
	COlePropertyPage(IDD, IDS_MATHGRAPH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMathGraphPropPage)
	m_strTitle = _T("");
	m_strXAxis = _T("");
	m_strYAxis = _T("");
	m_strZAxis = _T("");
	m_bUseColors = FALSE;
	m_bUseLineStyles = FALSE;
	m_bShowLegend = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphPropPage::DoDataExchange - Moves data between page and properties

void CMathGraphPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMathGraphPropPage)
	DDX_Control(pDX, IDC_NORM_LOG, m_ctrlNormLog);
	DDX_Control(pDX, IDC_NORM_NORM, m_ctrlNormNorm);
	DDX_Control(pDX, IDC_LOG_NORM, m_ctrlLogNorm);
	DDX_Control(pDX, IDC_LOG_LOG, m_ctrlLogLog);
	DDX_Control(pDX, IDC_SPHERICAL, m_ctrlSpher);
	DDX_Control(pDX, IDC_CYLINDRICAL, m_ctrlCylind);
	DDX_Control(pDX, IDC_CARTESIAN, m_ctrlCart);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_X_AXIS, m_strXAxis);
	DDX_Text(pDX, IDC_Y_AXIS, m_strYAxis);
	DDX_Text(pDX, IDC_Z_AXIS, m_strZAxis);
	DDP_Check(pDX, IDC_COLORS, m_bUseColors, _T("m_bUseColors") );
	DDX_Check(pDX, IDC_COLORS, m_bUseColors);
	DDP_Check(pDX, IDC_DIFF_LINE_STYLES, m_bUseLineStyles, _T("m_bUseLineStyles") );
	DDX_Check(pDX, IDC_DIFF_LINE_STYLES, m_bUseLineStyles);
	DDP_Check(pDX, IDC_SHOW_LEGEND, m_bShowLegend, _T("m_bShowLegend") );
	DDX_Check(pDX, IDC_SHOW_LEGEND, m_bShowLegend);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphPropPage message handlers

void CMathGraphPropPage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	AfxMessageBox("joko");	
	COlePropertyPage::OnLButtonDown(nFlags, point);
}

void CMathGraphPropPage::OnCartesian() 
{
	m_ctrlCart.SetCheck(1);
	m_ctrlCylind.SetCheck(0);
	m_ctrlSpher.SetCheck(0);
}

void CMathGraphPropPage::OnCylindrical() 
{
	m_ctrlCart.SetCheck(0);
	m_ctrlCylind.SetCheck(1);
	m_ctrlSpher.SetCheck(0);
}

void CMathGraphPropPage::OnSpherical() 
{
	m_ctrlCart.SetCheck(0);
	m_ctrlCylind.SetCheck(0);
	m_ctrlSpher.SetCheck(1);
}

void CMathGraphPropPage::OnLogLog() 
{
	m_ctrlLogLog.SetCheck(1);
	m_ctrlLogNorm.SetCheck(0);
	m_ctrlNormLog.SetCheck(0);
	m_ctrlNormNorm.SetCheck(0);
}

void CMathGraphPropPage::OnLogNorm() 
{
	m_ctrlLogLog.SetCheck(0);
	m_ctrlLogNorm.SetCheck(1);
	m_ctrlNormLog.SetCheck(0);
	m_ctrlNormNorm.SetCheck(0);
}

void CMathGraphPropPage::OnNormLog() 
{
	m_ctrlLogLog.SetCheck(0);
	m_ctrlLogNorm.SetCheck(0);
	m_ctrlNormLog.SetCheck(1);
	m_ctrlNormNorm.SetCheck(0);
}

void CMathGraphPropPage::OnNormNorm() 
{
	m_ctrlLogLog.SetCheck(0);
	m_ctrlLogNorm.SetCheck(0);
	m_ctrlNormLog.SetCheck(0);
	m_ctrlNormNorm.SetCheck(1);
}
