// DlgDefineParameters.cpp : implementation file
//

#include "stdafx.h"
#include "SchroedingerEq.h"
#include "DlgDefineParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDefineParameters dialog


CDlgDefineParameters::CDlgDefineParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDefineParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDefineParameters)
	m_a1 = 0.0f;
	m_a2 = 5.0f;
	m_b1 = 2.0f;
	m_b2 = 3.0f;
	m_V0 = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgDefineParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDefineParameters)
	DDX_Text(pDX, IDC_EDIT_FINITE_A1, m_a1);
	DDX_Text(pDX, IDC_EDIT_FINITE_A2, m_a2);
	DDX_Text(pDX, IDC_EDIT_FINITE_B1, m_b1);
	DDX_Text(pDX, IDC_EDIT_FINITE_B2, m_b2);
	DDX_Text(pDX, IDC_EDIT_FINITE_V0, m_V0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDefineParameters, CDialog)
	//{{AFX_MSG_MAP(CDlgDefineParameters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDefineParameters message handlers
