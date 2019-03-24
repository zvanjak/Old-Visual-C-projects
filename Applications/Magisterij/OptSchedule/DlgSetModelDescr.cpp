// DlgSetModelDescr.cpp : implementation file
//

#include "stdafx.h"
#include "OptSchedule.h"
#include "DlgSetModelDescr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetModelDescr dialog


CDlgSetModelDescr::CDlgSetModelDescr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetModelDescr::IDD, pParent)
{
//	Create(IDD_SET_MODEL_DATA, pParent);
//	ShowWindow(1);

	//{{AFX_DATA_INIT(CDlgSetModelDescr)
	m_nBrojStudLow = 0;
	m_nBrojStudUpp = 0;
	m_nSemLow = 0;
	m_nSemUpp = 0;
	m_bDiplomski = FALSE;
	m_bHuman = FALSE;
	m_bIzborni = FALSE;
	m_bObavezni = FALSE;
	m_bSeminar = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSetModelDescr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetModelDescr)
	DDX_Text(pDX, IDC_BROJ_LOW, m_nBrojStudLow);
	DDV_MinMaxInt(pDX, m_nBrojStudLow, 0, 10000);
	DDX_Text(pDX, IDC_BROJ_UPP, m_nBrojStudUpp);
	DDV_MinMaxInt(pDX, m_nBrojStudUpp, 0, 10000);
	DDX_Text(pDX, IDC_SEM_LOW, m_nSemLow);
	DDV_MinMaxInt(pDX, m_nSemLow, 0, 15);
	DDX_Text(pDX, IDC_SEM_UPP, m_nSemUpp);
	DDV_MinMaxInt(pDX, m_nSemUpp, 0, 15);
	DDX_Check(pDX, IDC_CHECK_DIPLOMSKI, m_bDiplomski);
	DDX_Check(pDX, IDC_CHECK_HUMAN, m_bHuman);
	DDX_Check(pDX, IDC_CHECK_IZBORNI, m_bIzborni);
	DDX_Check(pDX, IDC_CHECK_OBAVEZNI, m_bObavezni);
	DDX_Check(pDX, IDC_CHECK_SEMINAR, m_bSeminar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetModelDescr, CDialog)
	//{{AFX_MSG_MAP(CDlgSetModelDescr)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetModelDescr message handlers
