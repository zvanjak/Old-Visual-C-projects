// DlgViewData.cpp : implementation file
//

#include "stdafx.h"
#include "OptSchedule.h"
#include "DlgViewData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewData dialog


CDlgViewData::CDlgViewData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewData::IDD, pParent)
{
	Create(IDD_VIEW_DATA, pParent);
	ShowWindow(1);

	//{{AFX_DATA_INIT(CDlgViewData)
	//}}AFX_DATA_INIT
}


void CDlgViewData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewData)
	DDX_Control(pDX, IDC_TREE_PRESJECI, m_ctrlTreePresjeci);
	DDX_Control(pDX, IDC_DATA_TREE, m_ctrlDataTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewData, CDialog)
	//{{AFX_MSG_MAP(CDlgViewData)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewData message handlers
