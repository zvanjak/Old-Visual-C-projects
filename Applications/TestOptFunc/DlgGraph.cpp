// DlgGraph.cpp : implementation file
//

#include "stdafx.h"
#include "TestOptFunc.h"
#include "DlgGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGraph dialog


CDlgGraph::CDlgGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGraph::IDD, pParent)
{
	Create(IDD_SHOW_GRAPH, pParent );
	ShowWindow(1);

	//{{AFX_DATA_INIT(CDlgGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGraph)
	DDX_Control(pDX, IDC_GRAPHCTRL1, m_ctrlGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGraph, CDialog)
	//{{AFX_MSG_MAP(CDlgGraph)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGraph message handlers
