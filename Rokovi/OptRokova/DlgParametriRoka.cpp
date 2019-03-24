// DlgParametriRoka.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgParametriRoka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParametriRoka dialog


CDlgParametriRoka::CDlgParametriRoka(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParametriRoka::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParametriRoka)
	m_nBrojRokova = 0;
	//}}AFX_DATA_INIT
}


void CDlgParametriRoka::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParametriRoka)
	DDX_Control(pDX, IDC_DATUM_ZAVRSETKA, m_ctrlZavrsetak);
	DDX_Control(pDX, IDC_DATUM_POCETKA, m_ctrlPocetak);
	DDX_Control(pDX, IDC_ROK_ZIMSKI, m_ctrlZim);
	DDX_Control(pDX, IDC_ROK_LJETNI, m_ctrlLJet);
	DDX_Control(pDX, IDC_ROK_PROLJETNI, m_ctrlProljet);
	DDX_Control(pDX, IDC_ROK_JESENSKI_IZV, m_ctrlJesIzv);
	DDX_Control(pDX, IDC_ROK_JESENSKI, m_ctrlJes);
	DDX_Text(pDX, IDC_BROJ_ROKOVA, m_nBrojRokova);
	DDV_MinMaxInt(pDX, m_nBrojRokova, 1, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParametriRoka, CDialog)
	//{{AFX_MSG_MAP(CDlgParametriRoka)
	ON_NOTIFY(MCN_SELECT, IDC_DATUM_POCETKA, OnSelectDatumPocetka)
	ON_NOTIFY(MCN_SELECT, IDC_DATUM_ZAVRSETKA, OnSelectDatumZavrsetka)
	ON_BN_CLICKED(IDC_ROK_JESENSKI, OnRokJesenski)
	ON_BN_CLICKED(IDC_ROK_JESENSKI_IZV, OnRokJesenskiIzv)
	ON_BN_CLICKED(IDC_ROK_LJETNI, OnRokLjetni)
	ON_BN_CLICKED(IDC_ROK_PROLJETNI, OnRokProljetni)
	ON_BN_CLICKED(IDC_ROK_ZIMSKI, OnRokZimski)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParametriRoka message handlers

void CDlgParametriRoka::OnSelectDatumPocetka(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME  date;
	
	*pResult = 0;
	m_ctrlPocetak.GetCurSel(&date);

	dateStart.dan = date.wDay;
	dateStart.mj = date.wMonth;
	dateStart.god = date.wYear;
}

void CDlgParametriRoka::OnOK() 
{
	// TODO: Add extra validation here
		
	CDialog::OnOK();
}

void CDlgParametriRoka::OnSelectDatumZavrsetka(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME  date;
	
	*pResult = 0;
	m_ctrlZavrsetak.GetCurSel(&date);

	dateEnd.dan = date.wDay;
	dateEnd.mj = date.wMonth;
	dateEnd.god = date.wYear;
}

void CDlgParametriRoka::OnRokJesenski() 
{
	m_ctrlJesIzv.SetCheck(0);
	m_ctrlJes.SetCheck(1);
	m_ctrlLJet.SetCheck(0);
	m_ctrlProljet.SetCheck(0);
	m_ctrlZim.SetCheck(0);

	Vrsta = JESENSKI;
}

void CDlgParametriRoka::OnRokJesenskiIzv() 
{
	m_ctrlJesIzv.SetCheck(1);
	m_ctrlJes.SetCheck(0);
	m_ctrlLJet.SetCheck(0);
	m_ctrlProljet.SetCheck(0);
	m_ctrlZim.SetCheck(0);

	Vrsta = JESENSKI_IZV;
}

void CDlgParametriRoka::OnRokLjetni() 
{
	m_ctrlJesIzv.SetCheck(0);
	m_ctrlJes.SetCheck(0);
	m_ctrlLJet.SetCheck(1);
	m_ctrlProljet.SetCheck(0);
	m_ctrlZim.SetCheck(0);

	Vrsta = LJETNI;
}

void CDlgParametriRoka::OnRokProljetni() 
{
	m_ctrlJesIzv.SetCheck(0);
	m_ctrlJes.SetCheck(0);
	m_ctrlLJet.SetCheck(0);
	m_ctrlProljet.SetCheck(1);
	m_ctrlZim.SetCheck(0);

	Vrsta = PROLJETNI;
}

void CDlgParametriRoka::OnRokZimski() 
{
	m_ctrlJesIzv.SetCheck(0);
	m_ctrlJes.SetCheck(0);
	m_ctrlLJet.SetCheck(0);
	m_ctrlProljet.SetCheck(0);
	m_ctrlZim.SetCheck(1);

	Vrsta = ZIMSKI;
}
