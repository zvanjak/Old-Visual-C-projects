// DlgOptim.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgOptim.h"
#include "DlgParamOptimizacije.h"

#include "OptRokDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptim dialog


CDlgOptim::CDlgOptim(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptim::IDD, pParent)
{
	Create(IDD_OPTIMIZACIJA, pParent );

	CRect		rect;

	ShowWindow(SW_SHOWMAXIMIZED);

	GetClientRect(&rect);
	m_nWndHeight = rect.Height();
	m_nWndWidth = rect.Width();

//	MoveWindow(&rect);

//	m_ctrlRect.GetClientRect(&rect);
	m_ctrlRect.MoveWindow(X0,Y0,rect.Width()*5/10,rect.Height()*8/10);
	m_ctrlRect.RedrawWindow();

//	m_ctrlRect.ShowWindow(SW_SHOWNORMAL);

	//{{AFX_DATA_INIT(CDlgOptim)
	//}}AFX_DATA_INIT

	m_StartWith = 0;
	m_VertPos = 0;
	m_SelIspit = -1;

	m_ctrlVScroll.GetWindowRect(&rect);
	m_ctrlVScroll.MoveWindow(m_nWndWidth-rect.Width()-10, Y0, rect.Width(), rect.Height() );

	m_ctrlVScroll.SetMin(0);
	m_ctrlVScroll.SetMax(100);
	m_ctrlVScroll.SetSmallChange(1);
	m_ctrlVScroll.SetLargeChange(35);

	bCalcStopped = false;
	bTermSelected = false;
	nCurrIterNum = 0;
}

void CDlgOptim::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptim)
	DDX_Control(pDX, IDC_RECT, m_ctrlRect);
	DDX_Control(pDX, IDC_STOP, m_ctrlStop);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlOptProgress);
	DDX_Control(pDX, IDC_VSCROLL, m_ctrlVScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptim, CDialog)
	//{{AFX_MSG_MAP(CDlgOptim)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_NASTAVI, OnNastaviOptimizaciju)
	ON_BN_CLICKED(IDC_OPT_PROMIJENI_PAR, OnOptPromijeniPar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptim message handlers

void CDlgOptim::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int		i, Height, Width, nRowHeight;
	int		col, row, nLenNaziv;
				
	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);

//	ASSERT_VALID(pDoc);

	Height = m_nWndHeight * 746 / 1000;//(int) (15 * (pDoc->m_Opt->ModPar.nBrIsp));
	Width  = m_nWndWidth * 9 / 10;
//	Height = HEIGHT - 15;//(int) (15 * (pDoc->m_Opt->ModPar.nBrIsp));
//	Width  = WIDTH - 50;
	nLenNaziv = 150;		

	if( pDoc->m_Opt->ModPar.nBrIsp > MAX_ISP_NA_EKRANU )
		nRowHeight = Height / MAX_ISP_NA_EKRANU;
	else
		nRowHeight = Height/(pDoc->m_Opt->ModPar.nBrIsp+1);

	if ( nRowHeight > 20 )
		nRowHeight = 18;
	
	// ispit se selektira samo ukoliko se klikne na naziv
	if( point.x < 150 )
		m_SelIspit = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;
	else
	{
		if( (pDoc->m_bOptimizationStarted == true && bCalcStopped == true) || bCalcInProgress == false )
		{
			if( bTermSelected == false )		// ako je to prvi klik mišem ( odabiremo termin koji pomièemo )
			{
				row = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;	// redak na koji je kliknuto
				col = ( point.x - X0 - nLenNaziv ) * ( pDoc->m_Opt->ModPar.nBrDan + 1) / ( Width - nLenNaziv ) + 1;

				// sada treba provjeriti da li je za odabrani ispit odabran ispravan termin ( u kojem se stvarno održava taj ispit )
				for( i=0; i<pDoc->m_Opt->ModPar.nBrRok; i++ )
					if( pDoc->m_Opt->Population[pDoc->m_nBestCromosomInd]->TerminiIspita[row][i] == DanUTermin(col)-1 )
					{
//						AfxMessageBox("Evo");
						nRow = row;
						nOldTerm = DanUTermin(col-1) - 1;
						nRok = i;
						
						bTermSelected = true;
					}
				char	str[50];
				sprintf(str, "Redak = %d, Termin = %d, Dan = %d, Rok = %d", nRow, nOldTerm, col, nRok );
				AfxMessageBox(str);
			}
			else
			{
//				AfxMessageBox("Drugi klik");

				// znaèi da sada treba promijeniti termin odabranog ispita na odabranom roku u skladu sa pozicijom na koju je kliknuto mišem
				row = ( point.y - Y0 ) / nRowHeight + m_StartWith - 1;	// redak na koji je kliknuto
				col = ( point.x - X0 - nLenNaziv ) * ( pDoc->m_Opt->ModPar.nBrDan + 1) / ( Width - nLenNaziv ) + 1;

				if( IsVikend(col) )
					AfxMessageBox("Ne može se staviti termin ispita u subotu ili nedjelju !!!");
				else
				{
					// da provjerimo da li je u novom terminu veæ stavljen ovaj ispit
					bool	AlreadyExistInTerm = false;
					
					for( i=0; i<pDoc->m_Opt->ModPar.nBrRok; i++ )
						if( pDoc->m_Opt->Population[pDoc->m_nBestCromosomInd]->TerminiIspita[nRow][i] == DanUTermin(col-1) && i != nRok )
							AlreadyExistInTerm = true;

					if( AlreadyExistInTerm == false )		// znaèi da ga možemo staviti u taj termin
					{
						pDoc->m_Opt->Population[pDoc->m_nBestCromosomInd]->TerminiIspita[nRow][nRok] = DanUTermin(col-1);
						
						// i sada još treba bitove u genu promijeniti
						long		crom;
						crom = pDoc->m_Opt->Population[pDoc->m_nBestCromosomInd]->Cromosom[nRow];
						ClearBit(crom, nOldTerm);
						SetBit(crom, DanUTermin(col-1) );

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

void CDlgOptim::PrintConfig(  )
{
	int			i, k, ind_max, dan, sif, Height, Width, nLenNaziv, nRowHeight;
	int			X, Y, BestCromosomInd, BrIspUDanu[100];
	int			BrojIspNaEkranu, sif1, sif2, presj;
	char		pred[100], sdan[50], str[100];
	int			hh, mm, sec;
	long		br_sec;
	double	f, min, max, avg;
	string	strNaziv;

	// najprije moramo doæi do pokazivaèa na dokument
	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);

//	ASSERT_VALID(pDoc);

	// a zatim idemo crtati
	CDC *pDC = GetDC();

	Height = m_nWndHeight * 746 / 1000;//(int) (15 * (pDoc->m_Opt->ModPar.nBrIsp));
	Width  = m_nWndWidth * 9 / 10;
/*
	CSize		siz = pDC->GetViewportExt();
	char		str2[100];

	sprintf(str2, "x=%d   y=%d", siz.cx, siz.cy );
	AfxMessageBox(str2);
*/
	nLenNaziv = 200;
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

	pDC->Rectangle(X0-1,Y0-1, X0+Width+50, Y0+Height+1);

	CFont		tmpFont, *pPrevFont;

	tmpFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
										OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Times New Roman" );
	
	pPrevFont = pDC->SelectObject(&tmpFont);

	for( i=1; i<=BrojIspNaEkranu; i++ )
	{
		sif = pDoc->m_Opt->ModPar.vecOptIsp[m_StartWith+i-1].Sif;
		strNaziv = pDoc->m_Opt->vecNaziviPred[sif];

		sprintf(pred, "%-30s", strNaziv.c_str());
//		sprintf(pred, "%3d.%10s", i+m_StartWith, strNaziv.c_str());
		pred[30] = 0;
		pDC->TextOut(X0+5,Y0+i*nRowHeight, pred);
	}
	pDC->SelectObject(pPrevFont);

	// sada æemo selektirani ispit iscrtati bijelim slovima na crnoj pozadini
	if( m_SelIspit >= 0 )
	{
		CRect		rect(X0, Y0+(m_SelIspit+1)*nRowHeight, X0+Width, Y0+nRowHeight*(m_SelIspit+2) );

		pDC->InvertRect(&rect);
	}

	for( dan=1; dan<=pDoc->m_Opt->ModPar.nBrDan; dan++ )
	{
		sprintf(sdan, "%2d", dan);
		pDC->TextOut(X0+nLenNaziv+dan*(Width-nLenNaziv)/(pDoc->m_Opt->ModPar.nBrDan+1)+5, Y0+0, sdan);
	}

	for( i=1; i<=BrojIspNaEkranu+1; i++ )
	{
		pDC->MoveTo(X0+0,Y0+i*nRowHeight);
		pDC->LineTo(X0+Width,Y0+i*nRowHeight);
	}

	for( dan=1; dan<=pDoc->m_Opt->ModPar.nBrDan+1; dan++ )
	{
		pDC->MoveTo(X0+nLenNaziv+dan*(Width-nLenNaziv)/(pDoc->m_Opt->ModPar.nBrDan+1), Y0+0);
		pDC->LineTo(X0+nLenNaziv+dan*(Width-nLenNaziv)/(pDoc->m_Opt->ModPar.nBrDan+1), Y0+Height);
	}

	for( i=0; i<100; i++ )
		BrIspUDanu[i] = 0;

	FunkcijaCilja	 refF, maxF;

	max = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[0], maxF);
	ind_max = 0;
	min = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[0], refF);
	avg = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[0], refF);
	
	for( i=1; i<pDoc->m_Opt->GenPar.GetVelPop(); i++ )
	{
		f = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[i], refF);
		avg += f;
		if( f > max )
		{
			max = f;
			maxF = refF;
			ind_max = i;
		}
		if( f < min )
			min = f;
	}
	avg /= pDoc->m_Opt->GenPar.GetVelPop();

	// mijenjaj najbolju jedinku jedino ako je još u tijeku izraèunavanje
	// ako je raèunanje gotovo, onda prepusti korisniku da je mijenja
//	if( bCalcInProgress == true )
	BestCromosomInd = ind_max;
	pDoc->m_nBestCromosomInd = ind_max;
//	else
//	{
//		//max = Func(Population[BestCromosomInd]);
//	}

	for( i=0; i<pDoc->m_Opt->ModPar.nBrIsp; i++ )
		for( k=0; k<pDoc->m_Opt->ModPar.nBrRok; k++ )
		{
			dan = TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[i][k]);
			BrIspUDanu[dan]++;
		}
	
	for( i=0; i<BrojIspNaEkranu; i++ )
	{
		{
			for( k=0; k<pDoc->m_Opt->ModPar.nBrRok; k++ )
			{
				dan = TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[m_StartWith+i][k]);

				X = X0 + nLenNaziv + (TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[m_StartWith+i][k])+1) * (Width-nLenNaziv)/(pDoc->m_Opt->ModPar.nBrDan+1) + 10;
				Y = Y0 + (i+1)*nRowHeight + 1;

//				CBrush	*pB = new CBrush(RGB(0,255,0));

				if( k == 0 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(255,0,0)));
//					pDC->SelectObject(CBrush(RGB(0,0,0)));
//					pDC->SelectStockObject(BLACK_BRUSH);
				else if( k == 1 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(0,0,255)));
//					pDC->SelectStockObject(LTGRAY_BRUSH);
				else if( k == 2 )
					pDC->FillRect(CRect(X+2, Y+4, X+9, Y+11), &CBrush(RGB(0,0,0)));
//					pDC->SelectObject(CBrush(RGB(255,0,0)));

//				pDC->Ellipse(X+2, Y+4, X+9, Y+11);
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
		bool	fleg_min_dist = false;

		sif2 = pDoc->m_Opt->ModPar.vecOptIsp[i+m_StartWith].Sif;
		if( pDoc->m_Opt->ModPar.nBrRok >= 2 )
			for( k=0; k<pDoc->m_Opt->ModPar.nBrRok-1; k++ )
			{
				dan1 = TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[m_StartWith+i][k]);
				dan2 = TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[m_StartWith+i][k+1]);

				if( abs(dan1-dan2) < pDoc->m_Opt->FuncPar.GetMinDistance() )
					fleg_min_dist = true;
			}
		if( fleg_min_dist == true )
		{
			X = Width+12;
			Y = Y0 + (i+1)*nRowHeight + 5;
			pDC->Ellipse(X,Y,X+8,Y+8);
		}

		bool	fleg_podrokovi = false;
		int		*GranicaRoka = new int[pDoc->m_Opt->ModPar.nBrRok];	

		if( pDoc->m_Opt->ModPar.nBrRok > 1 )				// jedino ako imamo više od jednog roka možemo imati podjelu na podrokove
			for( k=0; k<pDoc->m_Opt->ModPar.nBrRok; k++ )
			{
				GranicaRoka[k] = pDoc->m_Opt->ModPar.nBrDan / pDoc->m_Opt->ModPar.nBrRok * ( k + 1 );
				dan = TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[m_StartWith+i][k]);

//				for( j=0; j<pDoc->m_Opt->ModPar.nBrIsp; j++ )
				{
					if( k == 0 )		// prvi rok 
					{
						if( dan >= GranicaRoka[0] )		// znaèi da odstupa od podjele na podrokove
//						if( TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[i][0]) > GranicaRoka[0] )		// znaèi da odstupa od podjele na podrokove
							fleg_podrokovi = true;
					}
					else if( k == pDoc->m_Opt->ModPar.nBrRok-1 )				// zadnji rok
					{
						if( dan <= GranicaRoka[k-1] )		
//						if( TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[i][k]) < GranicaRoka[k-1] )		
							fleg_podrokovi = true;
					}
					else
					{
						if( dan < GranicaRoka[k-1] )		// znaèi da odstupa od podjele na podrokove
//						if( TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[i][k]) < GranicaRoka[k-1] )		// znaèi da odstupa od podjele na podrokove
							fleg_podrokovi = true;
						else if( dan > GranicaRoka[k] )
//				else if( TerminUDan(pDoc->m_Opt->Population[BestCromosomInd]->TerminiIspita[i][k]) > GranicaRoka[k] )
							fleg_podrokovi = true;
					}
				}
			}

		delete []GranicaRoka;

		if( fleg_podrokovi == true )
		{
			X = Width+25;
			Y = Y0 + (i+1)*nRowHeight + 5;
			pDC->Rectangle(X,Y,X+8,Y+8);
		}
	
	}

	for( i=0; i<pDoc->m_Opt->ModPar.nBrDan; i++ )
	{
		sprintf(str, "%2d", BrIspUDanu[i] );
		X = X0 + nLenNaziv + (i+1) * (Width-nLenNaziv)/(pDoc->m_Opt->ModPar.nBrDan+1) + 5;
		
		if( BrIspUDanu[i] != 0 )
			pDC->TextOut(X, Height-5, str);
	}

	sprintf(str, "Max. funkcije dobrote = %lf   ", max);
	pDC->TextOut(20, HEIGHT+30, str);
	sprintf(str, "Min. funkcije dobrote = %lf   ", min);
	pDC->TextOut(20, HEIGHT+30+18*1, str);
	sprintf(str, "Prosj. funkcije dobrote = %lf   ", avg);
	pDC->TextOut(20, HEIGHT+30+18*2, str);

	sprintf(str, "Broj kazni zbog odstupanja podjele na podrokove = %3d ", pDoc->m_Opt->Population[BestCromosomInd]->BrojOdstupanjaPodrokova );
	pDC->TextOut(20, HEIGHT+30+18*3, str);
	sprintf(str, "Broj kazni zbog prevelike blizine = %3d ", pDoc->m_Opt->Population[BestCromosomInd]->BrojOdstupanjaBlizineIspita );
	pDC->TextOut(20, HEIGHT+30+18*4, str);
	sprintf(str, "Broj kazni zbog opterecenja na grupi pred = %3d ", pDoc->m_Opt->Population[BestCromosomInd]->BrojKazniOpterecenjeGrupe );
	pDC->TextOut(20, HEIGHT+30+18*5, str);

	br_sec = time(NULL) - timeStarted;
	hh = br_sec / 3600;
	mm = (br_sec % 3600) / 60;
	sec = br_sec % 60;
	sprintf(str, "Vrijeme optimizacije = %02d:%02d:%02d,   broj iteracija = %ld   ", hh, mm, sec, IterNum);
	pDC->TextOut(20, HEIGHT+30+18*8, str);

	sprintf(str, "Ispunjene želje profesora (ukupan broj) =  %ld ( %ld ) ", pDoc->m_Opt->Population[BestCromosomInd]->BrojIspunjenihZeljaProfesora, pDoc->m_Opt->Population[BestCromosomInd]->BrojZeljaProfesora);
	pDC->TextOut(20, HEIGHT+30+18*6, str);

	sprintf(str, "Max ispita =  %d ", pDoc->m_Opt->Population[BestCromosomInd]->BrojKazniZbogViseIspitaNaIstomSmjeru );
	pDC->TextOut(20, HEIGHT+30+18*7, str);

	//////////////////////////////////////////////////

	double Tot = fabs(maxF.BlizinaIspita) + fabs(maxF.KazneOdstupanjaOdPodrokova) + fabs(maxF.KazneOpterecenjaNaGrupama) + fabs(maxF.KaznePrevelikeBlizine) + fabs(maxF.PresjekIspita ) + fabs(maxF.ZeljeProfesora ) + fabs(maxF.KaznePrekoracenjaMaxIspitaNaIstomSmjeru);

	sprintf(str, "Podrokovi kazne  = %lf   (%2d %%)      ", maxF.KazneOdstupanjaOdPodrokova,  (int) (maxF.KazneOdstupanjaOdPodrokova/Tot*100) );
	pDC->TextOut(400, HEIGHT+30, str);

	sprintf(str, "Prevelika blizina kazne = %lf   (%2d %%)    ", maxF.KaznePrevelikeBlizine, (int) (maxF.KaznePrevelikeBlizine/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18, str);

	sprintf(str, "Kazne opterecenja na grupama = %lf   (%2d %%)   ", maxF.KazneOpterecenjaNaGrupama, (int) (maxF.KazneOpterecenjaNaGrupama/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18*2, str);

	sprintf(str, "Blizina ispita = %lf   (%2d %%)    ", maxF.BlizinaIspita, (int) (maxF.BlizinaIspita/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18*3, str);

	sprintf(str, "Presjek studenata = %lf   (%2d %%)    ", maxF.PresjekIspita, (int) (maxF.PresjekIspita/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18*4, str);

	sprintf(str, "Ispunjene zelje profesora = %lf   (%2d %%)     ", maxF.ZeljeProfesora, (int) (maxF.ZeljeProfesora/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18*5, str);

	sprintf(str, "Kazne max ispita =  %lf   (%2d %%)  ", maxF.KaznePrekoracenjaMaxIspitaNaIstomSmjeru, (int) (maxF.KaznePrekoracenjaMaxIspitaNaIstomSmjeru/Tot*100) );
	pDC->TextOut(400, HEIGHT+30+18*7, str);
}

UINT	DoSomething( LPVOID lParam )
{
	int					prog=0, IterPerIncrease;
	double			ret=0;
	CDlgOptim		*pDlg;

	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);

//	ASSERT_VALID(pDoc);

	pDlg = (CDlgOptim *) lParam;

	IterPerIncrease = pDoc->m_Opt->GenPar.GetIterNum() / 100;

	////////////////////////////////////////////////////////////////////////////////
	//								sad slijedi rutina za optimizaciju
	////////////////////////////////////////////////////////////////////////////////

	int			i, j, min_ind;
	double	min;
	Gen			CrossGen(pDoc->m_Opt->ModPar.nBrIsp, pDoc->m_Opt->ModPar.nBrRok);

	vector<int>		a(pDoc->m_Opt->ModPar.nBrRok);
	
	// ukoliko je optimizacija bila samo privremeno prekinuta, nastavi je
	if( pDlg->bCalcStopped == true )
	{
		pDlg->bCalcStopped = false;
		prog = pDlg->nCurrIterNum / IterPerIncrease;
	}
	else
	{
		pDlg->m_ctrlOptProgress.SetRange(0,100); //pDoc->m_Opt->GenPar.GetIterNum() / 1000);
	
		// inaèe, generiraj poèetnu populaciju i kreni dalje
		pDoc->m_Opt->Population.resize(pDoc->m_Opt->GenPar.GetVelPop());

		for( i=0; i<pDoc->m_Opt->GenPar.GetVelPop(); i++ )
			pDoc->m_Opt->Population[i] = new Gen(pDoc->m_Opt->ModPar.nBrIsp, pDoc->m_Opt->ModPar.nBrRok);

		pDoc->m_Opt->GenerateInitialPopulation(pDoc->m_Opt->Population);
		pDlg->nCurrIterNum = 0;
	}

	pDlg->PrintConfig();

	FILE *fp;

	fp = fopen("C:\\Godina12.txt", "w");

	for( i=pDlg->nCurrIterNum; i<=pDoc->m_Opt->GenPar.GetIterNum(); i++ )
	{
//		if( pDlg->bCalcStopped == false )
		{
			// SELEKCIJA
			// iz skupa od VEL_POP jedinki, odaberi njih 3 i indekse odabranih stavi u polje 'a'
			SelectRandomNumbers(a,3,0,pDoc->m_Opt->GenPar.GetVelPop()-1);
			
			// treba naæi najlošiju jedinku
			FunkcijaCilja	ref;

			min = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[a[0]], ref);
			min_ind =0 ;
			for( j=1; j<3; j++ )
				if( min > pDoc->m_Opt->Func(*pDoc->m_Opt->Population[a[j]], ref) )
				{
					min = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[a[j]],ref);
					min_ind = j;
				}


			float		f, minvalue, avgvalue;

			if( i %  10 == 0 ) {
				minvalue = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[0], ref);
				avgvalue = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[0], ref);
			
				for( int k=1; k<pDoc->m_Opt->GenPar.GetVelPop(); k++ )
				{
					f = pDoc->m_Opt->Func(*pDoc->m_Opt->Population[k], ref);
					avgvalue += f;
					if( f < min )
						min = f;
				}
				avgvalue /= pDoc->m_Opt->GenPar.GetVelPop();

				fprintf(fp, "\n %d %f %f", i, minvalue, avgvalue);
			}


			// KRIŽANJE
			// križaj dvije jedinke koje su bolje od one treæe selektirane
			if( min_ind == 0 )
				CrossGen = pDoc->m_Opt->Krizaj( *pDoc->m_Opt->Population[a[1]], *pDoc->m_Opt->Population[a[2]] );
			else if( min_ind == 1 )
				CrossGen = pDoc->m_Opt->Krizaj( *pDoc->m_Opt->Population[a[0]], *pDoc->m_Opt->Population[a[2]] );
			else
				CrossGen = pDoc->m_Opt->Krizaj( *pDoc->m_Opt->Population[a[0]], *pDoc->m_Opt->Population[a[1]] );

			*pDoc->m_Opt->Population[a[min_ind]] = CrossGen;

			// MUTACIJA
			// Mutacija jedinki iz populacije
			pDoc->m_Opt->Mutiraj(pDoc->m_Opt->Population);

//	AfxMessageBox("Kelejka");

			// sada se treba pobrinuti za fiksirane ispite

			if( i % 100 == 0 )
			{
				pDlg->IterNum = i;
				pDlg->PrintConfig();
			}
			if( i % IterPerIncrease == 0 )
				pDlg->m_ctrlOptProgress.SetPos(prog++);

			if( pDlg->bCalcInProgress == false )
			{
				pDlg->timeEnded = time(NULL);
				return (UINT) ret;
			}

			if( pDlg->bCalcStopped == true )
			{
				pDlg->nCurrIterNum = i;
				return (UINT) ret;
			}
		}
	}
	
	fclose(fp);

	pDlg->PrintConfig();

	pDlg->bCalcInProgress = false;
	pDlg->timeEnded = time(NULL);
	return (UINT) ret;
}

BEGIN_EVENTSINK_MAP(CDlgOptim, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgOptim)
	ON_EVENT(CDlgOptim, IDC_VSCROLL, 2 /* Change */, OnChangeVscroll, VTS_NONE)
	ON_EVENT(CDlgOptim, IDC_VSCROLL, 7 /* Scroll */, OnScrollVscroll, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CDlgOptim::OnCancel() 
{
	int		ret;
	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);


	ret = AfxMessageBox("Želiš li saèuvati rezultat optimizacije ", MB_YESNOCANCEL );
	if( ret == IDYES )
		pDoc->m_Opt->PostaviRezultatOptimizacije(pDoc->m_arrDatumiIspita);

	if( ret != IDCANCEL )
	{
		bCalcInProgress = false;
	
		pDoc->m_bOptimizationStarted = false;
		CDialog::OnCancel();
	}
}

void CDlgOptim::OnChangeVscroll() 
{
	int		NewPos;

	NewPos = m_ctrlVScroll.GetValue();
	
	m_StartWith += ( NewPos - m_VertPos );
	m_VertPos = NewPos;

	m_SelIspit = -1;
	PrintConfig();
}

void CDlgOptim::OnScrollVscroll() 
{
}

void CDlgOptim::OnStop() 
{
	bCalcStopped = true;
	PrintConfig();
}

void CDlgOptim::OnNastaviOptimizaciju() 
{
	AfxBeginThread(DoSomething, this);	
}

void CDlgOptim::OnOptPromijeniPar() 
{
	CDlgParamOptimizacije		dlg;
	COptRokApp		*pApp;

	pApp = (COptRokApp *) AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();

	CDocTemplate *pTempl = pApp->GetNextDocTemplate(pos);
	pos = pTempl->GetFirstDocPosition();
	COptRokDoc *pDoc = (COptRokDoc *) pTempl->GetNextDoc(pos);

	// najprije æemo zaustaviti daljnje izraèunavanje
	bCalcStopped = true;
	PrintConfig();

	dlg.m_nVelPop = pDoc->m_Opt->GenPar.GetVelPop();
	dlg.m_IterNum = pDoc->m_Opt->GenPar.GetIterNum();
	dlg.m_nMutacija = pDoc->m_Opt->GenPar.GetMutModul();
	
	dlg.m_dExpUdalj				= pDoc->m_Opt->FuncPar.GetExponent();
	dlg.m_dKaznaPodrokovi	= pDoc->m_Opt->FuncPar.GetKaznaPodjeleNaPodrokove();
	dlg.m_dNagradaIstiDan = pDoc->m_Opt->FuncPar.GetNagradaIstiDan();
	dlg.m_nMinDist				= pDoc->m_Opt->FuncPar.GetMinDistance();
	dlg.m_nMinPresjek			= pDoc->m_Opt->FuncPar.GetMinPresjek();
	dlg.m_dKaznaMinDist		= pDoc->m_Opt->FuncPar.GetKaznaMinDist();
	dlg.m_dAmpBlizine			= pDoc->m_Opt->FuncPar.GetAmpBlizineIspita();
	dlg.m_dAmpPresjeka		= pDoc->m_Opt->FuncPar.GetAmpPresjekaStud();

	dlg.m_nMaxOpterecNaGrupiPred	= pDoc->m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred();
	dlg.m_dKaznaGrupaPred					= pDoc->m_Opt->FuncPar.GetKaznaZaMaxBrojStudZaGrupuPred();
	dlg.m_nMaxIspita							= pDoc->m_Opt->FuncPar.GetMaxBrojIspitaIstiDanNaIstomSmjer();
	dlg.m_dKaznaMaxIspita					= pDoc->m_Opt->FuncPar.GetKaznaPrekoracenjaMaxIspitaNaIstomSmjeru();

	int	ret = dlg.DoModal();
	if( ret == IDOK )
	{

		pDoc->m_Opt->GenPar.PostaviParametre(dlg.m_nVelPop, dlg.m_IterNum, dlg.m_nMutacija);
		
		int stari_presj = pDoc->m_Opt->FuncPar.GetMinPresjek();
		pDoc->m_Opt->FuncPar.PostaviParametre(dlg.m_dExpUdalj,dlg.m_dKaznaPodrokovi,
																		dlg.m_dNagradaIstiDan,dlg.m_dKaznaGrupaPred, dlg.m_dKaznaMinDist,
																		dlg.m_dAmpBlizine, dlg.m_dAmpPresjeka,
																		dlg.m_nMinDist, dlg.m_nMinPresjek, dlg.m_nMaxOpterecNaGrupiPred, dlg.m_nMaxIspita, dlg.m_dKaznaMaxIspita);

		if( stari_presj != pDoc->m_Opt->FuncPar.GetMinPresjek() )
			pDoc->m_Opt->PostaviPresjek();
	}

	// nakon promjene parametara æemo ponovo pokrenuti nit
	AfxBeginThread(DoSomething, this);	
}
