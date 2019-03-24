// DlgPregledSmjerGodinaVizualno.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgPregledSmjerGodinaVizualno.h"

#include "OptRokDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledSmjerGodinaVizualno dialog


CDlgPregledSmjerGodinaVizualno::CDlgPregledSmjerGodinaVizualno(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPregledSmjerGodinaVizualno::IDD, pParent)
{
	Create(IDD_PREGLED_SMJER_GOD_VIZ, pParent );

	//{{AFX_DATA_INIT(CDlgPregledSmjerGodinaVizualno)
	//}}AFX_DATA_INIT

	memset(&m_nBrojPredmeta[0][0], 0, sizeof(int) * 5 * 23 );

	m_StartWith = 0;
	m_ctrlButtLjet.SetCheck(1);
}


void CDlgPregledSmjerGodinaVizualno::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPregledSmjerGodinaVizualno)
	DDX_Control(pDX, IDC_CHECK_ZIM, m_ctrlButtZim);
	DDX_Control(pDX, IDC_CHECK_PROLJ, m_ctrlButtProlj);
	DDX_Control(pDX, IDC_CHECK_LJET, m_ctrlButtLjet);
	DDX_Control(pDX, IDC_CHECK_JESIZV, m_ctrlButtJesIzv);
	DDX_Control(pDX, IDC_CHECK_JES, m_ctrlButtJes);
	DDX_Control(pDX, IDC_ODABIR_SMJERA, m_ctrlSmjer);
	DDX_Control(pDX, IDC_GODINA5, m_ctrlGod5);
	DDX_Control(pDX, IDC_GODINA4, m_ctrlGod4);
	DDX_Control(pDX, IDC_GODINA3, m_ctrlGod3);
	DDX_Control(pDX, IDC_GODINA2, m_ctrlGod2);
	DDX_Control(pDX, IDC_GODINA1, m_ctrlGod1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPregledSmjerGodinaVizualno, CDialog)
	//{{AFX_MSG_MAP(CDlgPregledSmjerGodinaVizualno)
	ON_BN_CLICKED(IDC_GODINA1, OnGodina1)
	ON_BN_CLICKED(IDC_GODINA2, OnGodina2)
	ON_BN_CLICKED(IDC_GODINA3, OnGodina3)
	ON_BN_CLICKED(IDC_GODINA4, OnGodina4)
	ON_BN_CLICKED(IDC_GODINA5, OnGodina5)
	ON_CBN_SELCHANGE(IDC_ODABIR_SMJERA, OnSelchangeOdabirSmjera)
	ON_BN_CLICKED(IDC_PROMJENI_SMJER, OnPromjeniSmjer)
	ON_BN_CLICKED(IDC_CHECK_JES, OnCheckJes)
	ON_BN_CLICKED(IDC_CHECK_JESIZV, OnCheckJesizv)
	ON_BN_CLICKED(IDC_CHECK_LJET, OnCheckLjet)
	ON_BN_CLICKED(IDC_CHECK_PROLJ, OnCheckProlj)
	ON_BN_CLICKED(IDC_CHECK_ZIM, OnCheckZim)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledSmjerGodinaVizualno message handlers

void CDlgPregledSmjerGodinaVizualno::OnGodina1() 
{
	m_nGodina = 1;
	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnGodina2() 
{
	m_nGodina = 2;
	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnGodina3() 
{
	m_nGodina = 3;
	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnGodina4() 
{
	m_nGodina = 4;
	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnGodina5() 
{
	m_nGodina = 5;
	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnSelchangeOdabirSmjera() 
{
	int		IndexUSmjer[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, 20, 21, 21 }; 
	int		sel = m_ctrlSmjer.GetCurSel();
	
	if( sel != CB_ERR )
		m_nSifraSmjera = IndexUSmjer[sel];
}

void CDlgPregledSmjerGodinaVizualno::OnPromjeniSmjer() 
{
	ShowData();	
}

#define HEIGHT	400
#define WIDTH		960
#define MAX_ISP_NA_EKRANU	30

#define		X0				11
#define		Y0				120

void CDlgPregledSmjerGodinaVizualno::ShowData() 
{
	int			i, k, dan, Height, Width, nLenNaziv, nRowHeight;
	int			X, Y, BrIspUDanu[100];
	int			BrojIspNaEkranu, BrRok;
	char		pred[100], sdan[50], str[100];
	int			BrOdstupPodrokovi=0, BrOdstupBlizina=0;
	string	strNaziv;

	BrOdstupPodrokovi = 0;
	BrOdstupBlizina = 0;

	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);


	CDC *pDC = GetDC();

	BrRok = BrojRokova(m_Rok);
	Height = HEIGHT - 15;//(int) (15 * (pDoc->pDoc->m_Opt->ModPar.nBrIsp));
	Width  = WIDTH - 50;

	nLenNaziv = 150;
	if( m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera] > MAX_ISP_NA_EKRANU )
	{
		nRowHeight = Height / MAX_ISP_NA_EKRANU;
		BrojIspNaEkranu = MAX_ISP_NA_EKRANU;
	}
	else if (m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera] > 0 )
	{
		nRowHeight = Height/(m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera]+1);
		BrojIspNaEkranu = m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera];
	}
	else BrojIspNaEkranu = 0;

	if ( nRowHeight > 20 )
		nRowHeight = 16;

	pDC->Rectangle(X0-1,Y0-1, X0+Width+50, Y0+HEIGHT+1);

	CFont		tmpFont, *pPrevFont;

	tmpFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
										OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Times New Roman" );
	
	pPrevFont = pDC->SelectObject(&tmpFont);

	for( i=1; i<=BrojIspNaEkranu; i++ )
	{
		sprintf(pred, "%-25s", m_chPredmet[m_nGodina-1][m_nSifraSmjera][i-1]);
		pred[25] = 0;
		pDC->TextOut(X0+2,Y0+i*nRowHeight, pred);
	}
	pDC->SelectObject(pPrevFont);

	for( dan=1; dan<=BrojDanaZaPrikaz(m_Rok); dan++ )
	{
		sprintf(sdan, "%2d", dan);
		pDC->TextOut(X0+nLenNaziv+dan*(Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1)+4, Y0+0, sdan);
	}

	for( i=1; i<=BrojIspNaEkranu+1; i++ )
	{
		pDC->MoveTo(X0+0,Y0+i*nRowHeight);
		pDC->LineTo(X0+Width,Y0+i*nRowHeight);
	}

	for( dan=1; dan<=BrojDanaZaPrikaz(m_Rok)+1; dan++ )
	{
		pDC->MoveTo(X0+nLenNaziv+dan*(Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1), Y0+0);
		pDC->LineTo(X0+nLenNaziv+dan*(Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1), Y0+Height);
	}

	int		IndexPocetkaRoka;

	switch( m_Rok )
	{
		case JESENSKI_IZV : IndexPocetkaRoka = 0; break;
		case ZIMSKI : IndexPocetkaRoka = 1; break;
		case PROLJETNI : IndexPocetkaRoka = 3; break;
		case LJETNI : IndexPocetkaRoka = 4; break;
		case JESENSKI : IndexPocetkaRoka = 7; break;
	}

	BrRok = BrojRokova(m_Rok);

	for( i=0; i<100; i++ )
		BrIspUDanu[i] = 0;

	for( i=0; i<m_nBrojPredmeta[m_nGodina-1][m_nSifraSmjera]; i++ )
		for( k=0; k<BrRok; k++ )
		{
			dan = m_nDaniIspita[m_nGodina-1][m_nSifraSmjera][i][k + IndexPocetkaRoka];
			BrIspUDanu[dan]++;
		}
	
	for( i=0; i<BrojIspNaEkranu; i++ )
	{
			for( k=0; k<BrRok; k++ )
			{
				dan = m_nDaniIspita[m_nGodina-1][m_nSifraSmjera][i][k + IndexPocetkaRoka];

				X = X0 + nLenNaziv + (dan + 1) * (Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1) + 10;
				Y = Y0 + (i+1)*nRowHeight + 1;
				
//				pDC->Ellipse(X+2, Y+4, X+9, Y+11);

				if( k == 0 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(255,0,0)));
				else if( k == 1 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(0,0,255)));
				else if( k == 2 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(0,0,0)));
			}
	}

	for( i=0; i<BrojDanaZaPrikaz(m_Rok); i++ )
	{
		sprintf(str, "%2d", BrIspUDanu[i] );
		X = X0 + nLenNaziv + (i+1) * (Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1) + 5;
		
		if( BrIspUDanu[i] != 0 )
			pDC->TextOut(X, HEIGHT+Y0-17, str);
	}
/*
	sprintf(str, "Broj kazni zbog odstupanja podjele na podrokove = %3d ", BrOdstupPodrokovi);
	pDC->TextOut(200, HEIGHT+Y0+35+18*1, str);
	sprintf(str, "Broj kazni zbog prevelike blizine = %3d ", BrOdstupBlizina );
	pDC->TextOut(200, HEIGHT+Y0+35+18*2, str);
*/
}

void CDlgPregledSmjerGodinaVizualno::OnCheckJes() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(1);

	m_Rok = JESENSKI;

	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnCheckJesizv() 
{
	m_ctrlButtJesIzv.SetCheck(1);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = JESENSKI_IZV;

	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnCheckLjet() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(1);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = LJETNI;

	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnCheckProlj() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(1);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = PROLJETNI;

	ShowData();
}

void CDlgPregledSmjerGodinaVizualno::OnCheckZim() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(1);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = ZIMSKI;

	ShowData();
}
