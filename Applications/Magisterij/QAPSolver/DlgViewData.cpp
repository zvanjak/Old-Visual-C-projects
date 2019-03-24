// DlgViewData.cpp : implementation file
//

#include "stdafx.h"
#include "QAPSolver.h"
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
	//{{AFX_DATA_INIT(CDlgViewData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Create(IDD_VIEW_DATA, pParent);
}


void CDlgViewData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewData)
	DDX_Control(pDX, IDC_MATRIX_A, m_ctrlGridA);
	DDX_Control(pDX, IDC_MATRIX_B, m_ctrlGridB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewData, CDialog)
	//{{AFX_MSG_MAP(CDlgViewData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewData message handlers

void CDlgViewData::PostNcDestroy() 
{
	delete this;
//	CDialog::PostNcDestroy();
}

void CDlgViewData::OnCancel() 
{
	DestroyWindow();
}
