// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "SchroedingerEq.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog


CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptions)
	m_NumInt = -1;
	m_PerFunc = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptions)
	DDX_Radio(pDX, IDC_OPT_NUM_INT, m_NumInt);
	DDX_Radio(pDX, IDC_OPT_PERT_FUNC, m_PerFunc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers
