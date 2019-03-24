// DlgVizualniPrikaz.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgVizualniPrikaz.h"

#include "OptRokDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVizualniPrikaz dialog


CDlgVizualniPrikaz::CDlgVizualniPrikaz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVizualniPrikaz::IDD, pParent)
{
	Create(IDD_VIZUALNI_PRIKAZ, pParent );

	//{{AFX_DATA_INIT(CDlgVizualniPrikaz)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_StartWith = 0;
	m_VertPos = 0;
	m_SelIspit = -1;

	m_ctrlVScroll.SetMin(0);
	m_ctrlVScroll.SetMax(100);
	m_ctrlVScroll.SetSmallChange(1);
	m_ctrlVScroll.SetLargeChange(35);

	bTermSelected = false;

	m_Rok = LJETNI;
	m_ctrlButtLjet.SetCheck(1);
}


void CDlgVizualniPrikaz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVizualniPrikaz)
	DDX_Control(pDX, IDC_CHECK_ZIM, m_ctrlButtZim);
	DDX_Control(pDX, IDC_CHECK_PROLJ, m_ctrlButtProlj);
	DDX_Control(pDX, IDC_CHECK_LJET, m_ctrlButtLjet);
	DDX_Control(pDX, IDC_CHECK_JESIZV, m_ctrlButtJesIzv);
	DDX_Control(pDX, IDC_CHECK_JES, m_ctrlButtJes);
	DDX_Control(pDX, IDC_VIZPRIKAZ_VSCROLL, m_ctrlVScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVizualniPrikaz, CDialog)
	//{{AFX_MSG_MAP(CDlgVizualniPrikaz)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_JESIZV, OnCheckJesizv)
	ON_BN_CLICKED(IDC_CHECK_ZIM, OnCheckZim)
	ON_BN_CLICKED(IDC_CHECK_PROLJ, OnCheckProlj)
	ON_BN_CLICKED(IDC_CHECK_LJET, OnCheckLjet)
	ON_BN_CLICKED(IDC_CHECK_JES, OnCheckJes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVizualniPrikaz message handlers

void CDlgVizualniPrikaz::OnOk() 
{
	// TODO: Add your control notification handler code here

	CDialog::OnOK();
}

BEGIN_EVENTSINK_MAP(CDlgVizualniPrikaz, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgVizualniPrikaz)
	ON_EVENT(CDlgVizualniPrikaz, IDC_VIZPRIKAZ_VSCROLL, 2 /* Change */, OnChangeVizualniPrikazVscroll, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgVizualniPrikaz::OnChangeVizualniPrikazVscroll() 
{
	int		NewPos;

	NewPos = m_ctrlVScroll.GetValue();
	
	m_StartWith += ( NewPos - m_VertPos );
	m_VertPos = NewPos;

	m_SelIspit = -1;

	PrintConfig();
}

void CDlgVizualniPrikaz::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int		i, Height, Width, nRowHeight;
	int		col, row, nLenNaziv, h;
				
	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);

//	ASSERT_VALID(pDoc);

	Height = HEIGHT - 15;//(int) (15 * (pDoc->m_Opt->ModPar.nBrIsp));
	Width  = WIDTH - 50;
	nLenNaziv = 200;		

	if( pDoc->m_Opt->ModPar.nBrIsp > MAX_ISP_NA_EKRANU )
		nRowHeight = Height / MAX_ISP_NA_EKRANU;
	else
		nRowHeight = Height/(pDoc->m_Opt->ModPar.nBrIsp+1);

	if ( nRowHeight > 20 )
		nRowHeight = 18;
	
	// ispit se selektira samo ukoliko se klikne na naziv
	if( point.x < nLenNaziv)
		m_SelIspit = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;
	else
	{
		{
			if( bTermSelected == false )		// ako je to prvi klik mišem ( odabiremo termin koji pomièemo )
			{
				row = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;	// redak na koji je kliknuto
				col = ( point.x - X0 - nLenNaziv ) * ( BrojDanaZaPrikaz(m_Rok) + 1) / ( Width - nLenNaziv ) + 1;

				// sada treba provjeriti da li je za odabrani ispit odabran ispravan termin ( u kojem se stvarno održava taj ispit )
				for( i=0; i<BrojRokova(m_Rok); i++ )

//					if( pDoc->m_Opt->Population[pDoc->m_nBestCromosomInd]->TerminiIspita[row][i] == DanUTermin(col)-1 )
				{
					switch(m_Rok)
					{
						case JESENSKI_IZV : h = pDoc->m_arrDatumiIspita[row].m_arrDanJesIzv; break;
						case ZIMSKI				: h = pDoc->m_arrDatumiIspita[row].m_arrDanZim[i]; break;
						case PROLJETNI		: h = pDoc->m_arrDatumiIspita[row].m_arrDanProlj; break;
						case LJETNI				: h = pDoc->m_arrDatumiIspita[row].m_arrDanLjet[i]; break;
						case JESENSKI			: h = pDoc->m_arrDatumiIspita[row].m_arrDanJes[i]; break;
					}

					if( h == col - 1 )
					{
						AfxMessageBox("Evo");
						nRow = row;
						nOldTerm = DanUTermin(col - 1) - 1;
						nRok = i;
						
						bTermSelected = true;
					}
				}
				char	str[50];
				sprintf(str, "Redak = %d, Termin = %d, Dan = %d, Rok = %d", row, nOldTerm, col, nRok );
				AfxMessageBox(str);
			}
			else
			{
				AfxMessageBox("Drugi klik");

				// znaèi da sada treba promijeniti termin odabranog ispita na odabranom roku u skladu sa pozicijom na koju je kliknuto mišem
				row = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;	// redak na koji je kliknuto
				col = ( point.x - X0 - nLenNaziv ) * ( BrojDanaZaPrikaz(m_Rok) + 1) / ( Width - nLenNaziv ) + 1;

				if( IsVikend(col) )
					AfxMessageBox("Ne može se staviti termin ispita u subotu ili nedjelju !!!");
				else
				{
					// da provjerimo da li je u novom terminu veæ stavljen ovaj ispit
					bool	AlreadyExistInTerm = false;
					
					for( i=0; i<pDoc->m_Opt->ModPar.nBrRok; i++ )
					{
						switch(m_Rok)
						{
							case JESENSKI_IZV : h = pDoc->m_arrDatumiIspita[nRow].m_arrDanJesIzv; break;
							case ZIMSKI				: h = pDoc->m_arrDatumiIspita[nRow].m_arrDanZim[i]; break;
							case PROLJETNI		: h = pDoc->m_arrDatumiIspita[nRow].m_arrDanProlj; break;
							case LJETNI				: h = pDoc->m_arrDatumiIspita[nRow].m_arrDanLjet[i]; break;
							case JESENSKI			: h = pDoc->m_arrDatumiIspita[nRow].m_arrDanJes[i]; break;
						}

						if( h == col-1 && i != nRok )
							AlreadyExistInTerm = true;
					}

					if( AlreadyExistInTerm == false )		// znaèi da ga možemo staviti u taj termin
					{
						switch(m_Rok)
						{
							case JESENSKI_IZV : pDoc->m_arrDatumiIspita[nRow].m_arrDanJesIzv = col-1; break;
							case ZIMSKI				: pDoc->m_arrDatumiIspita[nRow].m_arrDanZim[nRok] = col-1; break;
							case PROLJETNI		: pDoc->m_arrDatumiIspita[nRow].m_arrDanProlj = col-1; break;
							case LJETNI				: pDoc->m_arrDatumiIspita[nRow].m_arrDanLjet[nRok] = col-1; break;
							case JESENSKI			: pDoc->m_arrDatumiIspita[nRow].m_arrDanJes[nRok] = col-1; break;
						}
						
						bTermSelected = false;
					}
					else
					{
						AfxMessageBox("Ispit veæ postoji u tom terminu !!!" );
					}
				}
			}
		}
	}
	
	// ovo nam treba da izbrišemo stare presjeke
	CDC *pDC = GetDC();
	pDC->Rectangle(X0+Width,Y0-1, X0+WIDTH, Y0+HEIGHT+1);
	
	PrintConfig();
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgVizualniPrikaz::PrintConfig()
{
	int			i, k, dan, sif, Height, Width, nLenNaziv, nRowHeight;
	int			X, Y, BrIspUDanu[100];
	int			BrojIspNaEkranu, BrRok, sif1, sif2, presj;
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

//	int		*sort = new int[pDoc->m_Opt->ModPar.nBrIsp];

	BrRok = BrojRokova(m_Rok);
	Height = HEIGHT - 15;//(int) (15 * (pDoc->pDoc->m_Opt->ModPar.nBrIsp));
	Width  = WIDTH - 50;

	nLenNaziv = 150;
	if( pDoc->m_Opt->ModPar.nBrIsp > MAX_ISP_NA_EKRANU )
	{
		nRowHeight = Height / MAX_ISP_NA_EKRANU;
		BrojIspNaEkranu = MAX_ISP_NA_EKRANU;
	}
	else
	{
		nRowHeight = Height/(pDoc->m_Opt->ModPar.nBrIsp+1);
		BrojIspNaEkranu = pDoc->m_Opt->ModPar.nBrIsp;
	}
	if ( nRowHeight > 20 )
		nRowHeight = 18;

	pDC->Rectangle(X0-1,Y0-1, X0+Width+50, Y0+HEIGHT+1);

	CFont		tmpFont, *pPrevFont;

	tmpFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
										OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Times New Roman" );
	
	pPrevFont = pDC->SelectObject(&tmpFont);

	for( i=1; i<=BrojIspNaEkranu; i++ )
	{
		sif = pDoc->m_arrDatumiIspita[m_StartWith+i-1].m_nSifraIspita;
		strNaziv = pDoc->m_Opt->vecNaziviPred[sif];

		sprintf(pred, "%-25s", strNaziv.c_str());
//		sprintf(pred, "%3d.%10s", i+m_StartWith, strNaziv.c_str());
		pred[25] = 0;
		pDC->TextOut(X0+2,Y0+i*nRowHeight, pred);
	}
	pDC->SelectObject(pPrevFont);

	// sada æemo selektirani ispit iscrtati bijelim slovima na crnoj pozadini
	if( m_SelIspit >= 0 )
	{
		CRect		rect(X0, Y0+(m_SelIspit+1)*nRowHeight, X0+Width, Y0+nRowHeight*(m_SelIspit+2) );

		pDC->InvertRect(&rect);
	}

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


	for( i=0; i<100; i++ )
		BrIspUDanu[i] = 0;

	for( i=0; i<pDoc->m_Opt->ModPar.nBrIsp; i++ )
		for( k=0; k<BrRok; k++ )
		{
			dan = DanIspita(pDoc, i, k );
			BrIspUDanu[dan]++;
		}
	
	for( i=0; i<BrojIspNaEkranu; i++ )
	{
		{
			for( k=0; k<BrRok; k++ )
			{
				dan = DanIspita(pDoc, m_StartWith+i, k );

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

		if( (i + m_StartWith) != m_SelIspit && m_SelIspit != -1 )
		{
			sif1 = pDoc->m_Opt->ModPar.vecOptIsp[m_SelIspit].Sif;
			sif2 = pDoc->m_Opt->ModPar.vecOptIsp[i+m_StartWith].Sif;

			presj = pDoc->m_Opt->ModPar.GetPresjek(sif1, sif2);

			if( presj > 0 )
			{
				X = Width+35;
				Y = Y0 + (i+1)*nRowHeight + 1;

				sprintf(str, "%d", presj );
				pDC->TextOut(X,Y,str);
			}
		}

		// a sada æemo signalizirati koji ne zadovoljavaju minimalnu udaljenost i podjelu na podrokove
		int		dan1, dan2;
		bool	fleg_min_dist;
		
		fleg_min_dist = false;
		sif2 = pDoc->m_Opt->ModPar.vecOptIsp[i+m_StartWith].Sif;
		if( BrRok >= 2 )
			for( k=0; k<BrRok-1; k++ )
			{
				dan1 = DanIspita(pDoc, m_StartWith+i, k );
				dan2 = DanIspita(pDoc, m_StartWith+i, k+1 );

				if( abs(dan1-dan2) < pDoc->m_Opt->FuncPar.GetMinDistance() )
					fleg_min_dist = true;
			}
		if( fleg_min_dist == true )
		{
			X = Width+12;
			Y = Y0 + (i+1)*nRowHeight + 5;
			pDC->Ellipse(X,Y,X+8,Y+8);
		}

		bool	fleg_podrokovi;
		int		*GranicaRoka = new int[BrRok];	

		fleg_podrokovi = false;
		if( BrRok > 1 )				// jedino ako imamo više od jednog roka možemo imati podjelu na podrokove
			for( k=0; k<BrRok-1; k++ )
			{
//				GranicaRoka[k] = pDoc->m_Opt->ModPar.nBrDan / BrRok * ( k + 1 );
				GranicaRoka[k] = BrojDanaZaPrikaz(m_Rok) / BrRok * ( k + 1 );
				dan = DanIspita(pDoc, m_StartWith+i, k );

				{
					if( k == 0 )		// prvi rok 
					{
						if( dan >= GranicaRoka[0] )		// znaèi da odstupa od podjele na podrokove
							fleg_podrokovi = true;
					}
					else if( k == BrRok-1 )				// zadnji rok
					{
						if( dan <= GranicaRoka[k-1] )		
							fleg_podrokovi = true;
					}
					else
					{
						if( dan  < GranicaRoka[k-1] )		// znaèi da odstupa od podjele na podrokove
							fleg_podrokovi = true;
						else if( dan > GranicaRoka[k] )
							fleg_podrokovi = true;
					}
				}
			}

		delete []GranicaRoka;

		// ako krši rapsodjelu na podrokove, onda iscrtaj kvadratiæ pored njega
		if( fleg_podrokovi == true )		
		{
			X = Width+25;
			Y = Y0 + (i+1)*nRowHeight + 5;
			pDC->Rectangle(X,Y,X+8,Y+8);
		}
	
	}

	for( i=0; i<BrojDanaZaPrikaz(m_Rok); i++ )
	{
		sprintf(str, "%2d", BrIspUDanu[i] );
		X = X0 + nLenNaziv + (i+1) * (Width-nLenNaziv)/(BrojDanaZaPrikaz(m_Rok)+1) + 5;
		
		if( BrIspUDanu[i] != 0 )
			pDC->TextOut(X, HEIGHT-5, str);
	}

	
	for( i=0; i<pDoc->m_Opt->ModPar.nBrIsp; i++ )
	{
		// a sada æemo signalizirati koji ne zadovoljavaju minimalnu udaljenost i podjelu na podrokove
		int		dan1, dan2;
		bool	fleg_min_dist = false;

		if( BrRok >= 2 )
			for( k=0; k<BrRok-1; k++ )
			{
				dan1 = DanIspita(pDoc, i, k );
				dan2 = DanIspita(pDoc, i, k+1 );

				if( abs(dan1-dan2) < pDoc->m_Opt->FuncPar.GetMinDistance() )
					BrOdstupBlizina++;
			}

		bool	fleg_podrokovi;
		int		*GranicaRoka = new int[BrRok];	

		fleg_podrokovi = false;
		if( BrRok > 1 )				// jedino ako imamo više od jednog roka možemo imati podjelu na podrokove
			for( k=0; k<BrRok-1; k++ )
			{
				GranicaRoka[k] = BrojDanaZaPrikaz(m_Rok) / BrRok * ( k + 1 );
				dan = DanIspita(pDoc, i, k );

				{
					if( k == 0 )		// prvi rok 
					{
						if( dan >= GranicaRoka[0] )		// znaèi da odstupa od podjele na podrokove
							BrOdstupPodrokovi++;
					}
					else if( k == BrRok-1 )				// zadnji rok
					{
						if( dan <= GranicaRoka[k-1] )		
							BrOdstupPodrokovi++;
					}
					else
					{
						if( dan  < GranicaRoka[k-1] )		// znaèi da odstupa od podjele na podrokove
							BrOdstupPodrokovi++;
						else if( dan > GranicaRoka[k] )
							BrOdstupPodrokovi++;
					}
				}
			}

		delete []GranicaRoka;
	}
	
	
	sprintf(str, "Broj kazni zbog odstupanja podjele na podrokove = %3d ", BrOdstupPodrokovi);
	pDC->TextOut(200, HEIGHT+35+18*1, str);
	sprintf(str, "Broj kazni zbog prevelike blizine = %3d ", BrOdstupBlizina );
	pDC->TextOut(200, HEIGHT+35+18*2, str);
//	sprintf(str, "Broj kazni zbog opterecenja na grupi pred = %3d ", pDoc->m_Opt->Population[BestCromosomInd]->BrojKazniOpterecenjeGrupe );
//DC->TextOut(20, HEIGHT+35+18*5, str);

	// sada treba nagraditi raspored kog kojeg su poštovane želje profesora
	int		l, m, ind1, ind2, BrojZeljaProfesora=0, BrojIspunjenihZeljaProfesora=0;

	for( i=0; i<pDoc->m_Opt->ModPar.matIspitiIstiDan.size(); i++ )
	{
		for( k=0; k<BrRok; k++ )		// na svakom roku æemo vidjeti posebno da li su u istom temrinu
			for( l=0; l<pDoc->m_Opt->ModPar.matIspitiIstiDan[i].size(); l++ )
				for( m=l+1; m<pDoc->m_Opt->ModPar.matIspitiIstiDan[i].size(); m++ )
				{
					ind1 = pDoc->m_Opt->ModPar.vecSifraUIndex[ pDoc->m_Opt->ModPar.matIspitiIstiDan[i][l] ];
					ind2 = pDoc->m_Opt->ModPar.vecSifraUIndex[ pDoc->m_Opt->ModPar.matIspitiIstiDan[i][m] ];

					BrojZeljaProfesora++;
					if( DanIspita(pDoc,ind1,k) == DanIspita(pDoc,ind2,k) )
						BrojIspunjenihZeljaProfesora++;
				}
	}

	// da vidimo što æemo sa optereæenjem na grupama predmeta
	int		j, grupa, ind, BrojKazniOpterecenjaGrupe=0;
	bool	GrupaPostoji[MAX_GRUPA];

	for( i=0; i<MAX_GRUPA; i++ )
		GrupaPostoji[i] = false;

	for( i=0; i<pDoc->m_Opt->ModPar.matSumaPoGrupPred.size(); i++ )
		for( j=0; j<pDoc->m_Opt->ModPar.matSumaPoGrupPred[i].size(); j++ )
		{
			pDoc->m_Opt->ModPar.matSumaPoGrupPred[i][j].m_nBrIsp = 0;
			pDoc->m_Opt->ModPar.matSumaPoGrupPred[i][j].m_nBrStud = 0;
		}

	for( i=0; i<pDoc->m_Opt->ModPar.nBrIsp; i++ )
	{
		sif = pDoc->m_Opt->ModPar.vecOptIsp[i].Sif;
		ind = pDoc->m_Opt->IndexPredSaSifrom(sif);
		grupa = pDoc->m_Opt->vecPopisPred[ind].m_nGrupaPred;
		GrupaPostoji[grupa] = true;

		for( k=0; k<BrRok; k++ )
		{
			pDoc->m_Opt->ModPar.matSumaPoGrupPred[grupa][DanIspita(pDoc,i,k)].m_nBrStud += pDoc->m_Opt->vecPopisPred[ind].m_nBrojStud;
			pDoc->m_Opt->ModPar.matSumaPoGrupPred[grupa][DanIspita(pDoc,i,k)].m_nBrIsp++;
		}
	}

	for( i=0; i<pDoc->m_Opt->ModPar.matSumaPoGrupPred.size(); i++ )
		if( GrupaPostoji[i] )
		{
			for( j=0; j<BrojDanaZaPrikaz(m_Rok); j++ )
				if( pDoc->m_Opt->ModPar.matSumaPoGrupPred[i][j].m_nBrStud > pDoc->m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
						pDoc->m_Opt->ModPar.matSumaPoGrupPred[i][j].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
				{
					BrojKazniOpterecenjaGrupe++;
				}
		}
	sprintf(str, "Broj kazni zbog prevelikog opterecenja = %3d ", BrojKazniOpterecenjaGrupe);
	pDC->TextOut(200, HEIGHT+35+18*3, str);
	sprintf(str, "Broj ispunjenih zelje profesora ( ukupan broj ) = %3d (%3d) ",  BrojIspunjenihZeljaProfesora,BrojZeljaProfesora );
	pDC->TextOut(200, HEIGHT+35+18*4, str);

//	delete []sort;
}

int	 CDlgVizualniPrikaz::DanIspita( COptRokDoc	*pDoc, int BrIsp, int BrRok )
{
	switch( m_Rok )
	{
		case JESENSKI_IZV :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanJesIzv;
			break;
		case ZIMSKI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanZim[BrRok];
		case PROLJETNI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanProlj;
		case LJETNI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanLjet[BrRok];
		case JESENSKI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanJes[BrRok];
	}
	return -1;
}

void CDlgVizualniPrikaz::OnCheckJesizv() 
{
	m_ctrlButtJesIzv.SetCheck(1);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = JESENSKI_IZV;

	PrintConfig();
}

void CDlgVizualniPrikaz::OnCheckZim() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(1);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = ZIMSKI;

	PrintConfig();
}

void CDlgVizualniPrikaz::OnCheckProlj() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(1);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = PROLJETNI;

	PrintConfig();
}

void CDlgVizualniPrikaz::OnCheckLjet() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(1);
	m_ctrlButtJes.SetCheck(0);

	m_Rok = LJETNI;

	PrintConfig();
}

void CDlgVizualniPrikaz::OnCheckJes() 
{
	m_ctrlButtJesIzv.SetCheck(0);
	m_ctrlButtZim.SetCheck(0);
	m_ctrlButtProlj.SetCheck(0);
	m_ctrlButtLjet.SetCheck(0);
	m_ctrlButtJes.SetCheck(1);

	m_Rok = JESENSKI;

	PrintConfig();
}
