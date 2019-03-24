// DlgPregledZelja.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgPregledZelja.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledZelja dialog


CDlgPregledZelja::CDlgPregledZelja(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPregledZelja::IDD, pParent)
{
	Create(IDD_PREGLED_SA_ZELJAMA, pParent);

	//{{AFX_DATA_INIT(CDlgPregledZelja)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPregledZelja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPregledZelja)
	DDX_Control(pDX, IDC_GRID, m_ctrlGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPregledZelja, CDialog)
	//{{AFX_MSG_MAP(CDlgPregledZelja)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledZelja message handlers
