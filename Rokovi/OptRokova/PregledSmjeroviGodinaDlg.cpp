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

//	CRect		rect;
//	m_ctrlSmjer.Create( CBS_DROPDOWN,rect,this,IDC_ODABIR_SMJERA);

	//{{AFX_DATA_INIT(CPregledSmjeroviGodinaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	for( int god=1; god<=5; god++ )
		for( int smjer=1; smjer<=22; smjer++ )
			m_nBrojPredmeta[god-1][smjer] = 0;
}


void CPregledSmjeroviGodinaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPregledSmjeroviGodinaDlg)
	DDX_Control(pDX, IDC_ODABIR_SMJERA, m_ctrlSmjer);
	DDX_Control(pDX, IDC_GODINA5, m_ctrlGod5);
	DDX_Control(pDX, IDC_GODINA4, m_ctrlGod4);
	DDX_Control(pDX, IDC_GODINA3, m_ctrlGod3);
	DDX_Control(pDX, IDC_GODINA2, m_ctrlGod2);
	DDX_Control(pDX, IDC_GODINA1, m_ctrlGod1);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_ctrlGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPregledSmjeroviGodinaDlg, CDialog)
	//{{AFX_MSG_MAP(CPregledSmjeroviGodinaDlg)
	ON_BN_CLICKED(IDC_GODINA1, OnGodina1)
	ON_BN_CLICKED(IDC_GODINA2, OnGodina2)
	ON_BN_CLICKED(IDC_GODINA3, OnGodina3)
	ON_BN_CLICKED(IDC_GODINA4, OnGodina4)
	ON_BN_CLICKED(IDC_GODINA5, OnGodina5)
	ON_CBN_SELCHANGE(IDC_ODABIR_SMJERA, OnSelchangeOdabirSmjera)
	ON_BN_CLICKED(IDC_PROMJENI_SMJER, OnPromjeniSmjer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPregledSmjeroviGodinaDlg message handlers

void CPregledSmjeroviGodinaDlg::OnGodina1() 
{
	m_nGodina = 1;
	ShowData();
}

void CPregledSmjeroviGodinaDlg::OnGodina2() 
{
	m_nGodina = 2;
	ShowData();
}

void CPregledSmjeroviGodinaDlg::OnGodina3() 
{
	m_nGodina = 3;
	ShowData();
}

void CPregledSmjeroviGodinaDlg::OnGodina4() 
{
	m_nGodina = 4;
	ShowData();
}

void CPregledSmjeroviGodinaDlg::OnGodina5() 
{
	m_nGodina = 5;
	ShowData();
}

void CPregledSmjeroviGodinaDlg::ShowData() 
{
	int		k, RowNum = 1;
	char	str[20];
	
	m_ctrlGrid.Clear();

	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski", "3.jesenski",
		"sem.", "br.st.", "grupa",  "opis"};

	m_ctrlGrid.SetRows(m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera] + 1);
	m_ctrlGrid.SetCols(16);
	m_ctrlGrid.SetColWidth(0,500);
	m_ctrlGrid.SetColWidth(1,3800);
	m_ctrlGrid.SetColAlignment(0,1);
	m_ctrlGrid.SetColAlignment(1,1);

	m_ctrlGrid.SetRow(0);

	m_ctrlGrid.SetCol(0);
	m_ctrlGrid.SetText(naslovi[0]);
	
	m_ctrlGrid.SetCol(1);
	m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<12; k++ )
	{
		m_ctrlGrid.SetCol(k);
		m_ctrlGrid.SetColAlignment(k,4);
		m_ctrlGrid.SetColWidth(k,800);
		m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=12; k<16; k++ )
	{
		m_ctrlGrid.SetCol(k);
		m_ctrlGrid.SetColAlignment(k,4);
		m_ctrlGrid.SetText(naslovi[k]);
		m_ctrlGrid.SetColWidth(k,500);
	}

	for( int i=0; i<m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera]; i++ )
	{
		m_ctrlGrid.SetRow(i+1);

		m_ctrlGrid.SetCol(0);
		sprintf(str, "%d", i+1 );
		m_ctrlGrid.SetText(str);

		m_ctrlGrid.SetCol(1);
		m_ctrlGrid.SetText(m_chPredmet[m_nGodina-1][m_nSifraSmjera][i]);

		for( int j=0; j<10; j++ )
		{
			m_ctrlGrid.SetCol(j+2);
			sprintf(str, "%d", m_nDaniIspita[m_nGodina-1][m_nSifraSmjera][i][j] );
			m_ctrlGrid.SetText(str);
		}

		m_ctrlGrid.SetCol(12);
		sprintf(str, "%d", m_nSemestar[m_nGodina-1][m_nSifraSmjera][i] );
		m_ctrlGrid.SetText(str);

		m_ctrlGrid.SetCol(13);
		sprintf(str, "%d", m_nBrojStud[m_nGodina-1][m_nSifraSmjera][i] );
		m_ctrlGrid.SetText(str);

		m_ctrlGrid.SetCol(14);
		sprintf(str, "%d", m_nGrupaPred[m_nGodina-1][m_nSifraSmjera][i] );
		m_ctrlGrid.SetText(str);

		m_ctrlGrid.SetCol(15);
		sprintf(str, "%c", m_chOpis[m_nGodina-1][m_nSifraSmjera][i] );
		m_ctrlGrid.SetText(str);
	}
}

void CPregledSmjeroviGodinaDlg::OnSelchangeOdabirSmjera() 
{
	int		IndexUSmjer[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, 20, 21, 21 }; 
	int		sel = m_ctrlSmjer.GetCurSel();
	
	if( sel != CB_ERR )
		m_nSifraSmjera = IndexUSmjer[sel];
}

void CPregledSmjeroviGodinaDlg::OnPromjeniSmjer() 
{
	ShowData();	
}
