// DlgIspitiIstiDan.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgIspitiIstiDan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIspitiIstiDan dialog


CDlgIspitiIstiDan::CDlgIspitiIstiDan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIspitiIstiDan::IDD, pParent)
{
	Create(IDD_PREGLED_ISPITI_ISTI_DAN, pParent );

	//{{AFX_DATA_INIT(CDlgIspitiIstiDan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgIspitiIstiDan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIspitiIstiDan)
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIspitiIstiDan, CDialog)
	//{{AFX_MSG_MAP(CDlgIspitiIstiDan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIspitiIstiDan message handlers

void CDlgIspitiIstiDan::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgIspitiIstiDan::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
