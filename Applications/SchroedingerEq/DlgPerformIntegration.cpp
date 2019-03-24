// DlgPerformIntegration.cpp : implementation file
//

#include "stdafx.h"
#include "SchroedingerEq.h"
#include "DlgPerformIntegration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPerformIntegration dialog


CDlgPerformIntegration::CDlgPerformIntegration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPerformIntegration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPerformIntegration)
	m_fEnd = 0.0;
	m_fStart = 0.0;
	m_fStep = 0.0;
	m_fValues = _T("");
	m_fNorm = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgPerformIntegration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPerformIntegration)
	DDX_Text(pDX, IDC_EDIT_E_END, m_fEnd);
	DDX_Text(pDX, IDC_EDIT_E_START, m_fStart);
	DDX_Text(pDX, IDC_EDIT_E_STEP, m_fStep);
	DDX_Text(pDX, IDC_EDIT_E_VALUES, m_fValues);
	DDX_Text(pDX, IDC_EDIT_NORM, m_fNorm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPerformIntegration, CDialog)
	//{{AFX_MSG_MAP(CDlgPerformIntegration)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPerformIntegration message handlers
