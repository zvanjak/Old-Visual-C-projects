// DlgTestChart.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgTestChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestChart dialog


CDlgTestChart::CDlgTestChart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestChart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTestChart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Create(IDD_TEST_3DCHART, pParent);
}


void CDlgTestChart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTestChart)
	DDX_Control(pDX, IDC_CHART, m_ctrlChart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTestChart, CDialog)
	//{{AFX_MSG_MAP(CDlgTestChart)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestChart message handlers
