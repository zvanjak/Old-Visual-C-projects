// PregledSmjeroviGodinaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "PregledSmjeroviGodinaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPregledSmjeroviGodinaDlg dialog


CPregledSmjeroviGodinaDlg::CPregledSmjeroviGodinaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPregledSmjeroviGodinaDlg::IDD, pParent)
{
	Create(IDD_PREGLED_PO_SMJEROVIMA, pParent );

	//{{AFX_DATA_INIT(CPregledSmjeroviGodinaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPregledSmjeroviGodinaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPregledSmjeroviGodinaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPregledSmjeroviGodinaDlg, CDialog)
	//{{AFX_MSG_MAP(CPregledSmjeroviGodinaDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPregledSmjeroviGodinaDlg message handlers
