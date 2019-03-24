// DlgSelectGraphNumber.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "DlgSelectGraphNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGraphNumber dialog


CDlgSelectGraphNumber::CDlgSelectGraphNumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectGraphNumber::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectGraphNumber)
	m_nGraphNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgSelectGraphNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectGraphNumber)
	DDX_Text(pDX, IDC_EDIT_GRAPH_NUM, m_nGraphNum);
	DDV_MinMaxInt(pDX, m_nGraphNum, 0, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectGraphNumber, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectGraphNumber)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGraphNumber message handlers
