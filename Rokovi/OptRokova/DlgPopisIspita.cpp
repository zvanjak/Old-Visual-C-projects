// DlgPopisIspita.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgPopisIspita.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPopisIspita dialog


CDlgPopisIspita::CDlgPopisIspita(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPopisIspita::IDD, pParent)
{
	Create(IDD_POPIS_ISPITA, pParent);

	//{{AFX_DATA_INIT(CDlgPopisIspita)
	//}}AFX_DATA_INIT

	m_bPrikazDani = true;
	m_ctrlButtDani.SetCheck(1);
}


void CDlgPopisIspita::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPopisIspita)
	DDX_Control(pDX, IDC_CHECK_DATUMI, m_ctrlButtDatumi);
	DDX_Control(pDX, IDC_CHECK_DANI, m_ctrlButtDani);
	DDX_Control(pDX, IDC_GRID, m_ctrlGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPopisIspita, CDialog)
	//{{AFX_MSG_MAP(CDlgPopisIspita)
	ON_BN_CLICKED(IDC_CHECK_DANI, OnCheckDani)
	ON_BN_CLICKED(IDC_CHECK_DATUMI, OnCheckDatumi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPopisIspita message handlers

void CDlgPopisIspita::OnCheckDani() 
{
	m_ctrlButtDani.SetCheck(1);
	m_ctrlButtDatumi.SetCheck(0);

	m_bPrikazDani = true;
	Invalidate();
}

void CDlgPopisIspita::OnCheckDatumi() 
{
	m_ctrlButtDani.SetCheck(0);
	m_ctrlButtDatumi.SetCheck(1);

	m_bPrikazDani = false;
	Invalidate();
}

void CDlgPopisIspita::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgPopisIspita::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
