// DlgViewBestSolution.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgViewBestSolution.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewBestSolution dialog


CDlgViewBestSolution::CDlgViewBestSolution(CString s1, CString s2, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewBestSolution::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewBestSolution)
	m_strAssignment = _T("");
	m_strValue = _T("");
	//}}AFX_DATA_INIT

	m_strValue = s1;
	m_strAssignment = s2;

	Create(IDD_VIEW_BEST_SOLUTION, pParent);
}


void CDlgViewBestSolution::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewBestSolution)
	DDX_Text(pDX, IDC_EDIT_ASSIGNMENT, m_strAssignment);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewBestSolution, CDialog)
	//{{AFX_MSG_MAP(CDlgViewBestSolution)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewBestSolution message handlers
