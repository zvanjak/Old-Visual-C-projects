// DlgViewResults.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"

#include "DlgViewResults.h"
#include "DlgSelectGraphNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults dialog


CDlgViewResults::CDlgViewResults(CQAPSolverDoc *inpDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewResults)
	//}}AFX_DATA_INIT

	Create(IDD_VIEW_RESULTS, pParent);

	pDoc = inpDoc;

	bShowGraphsInSameWnd = TRUE;
	bUseColors = TRUE;
	bUseLineStyle = TRUE;

	m_ctrlShowSame.SetCheck(TRUE);
	m_ctrlUseColors.SetCheck(TRUE);
	m_ctrlUseLineStyle.SetCheck(TRUE);
}


void CDlgViewResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewResults)
	DDX_Control(pDX, IDC_CHECK_USE_COLORS, m_ctrlUseColors);
	DDX_Control(pDX, IDC_CHECK_USE_LINESTYLES, m_ctrlUseLineStyle);
	DDX_Control(pDX, IDC_DELETE_OPT_RES_CMD, m_ctrlDeleteCmd);
	DDX_Control(pDX, IDC_SHOW_IN_SAME, m_ctrlShowSame);
	DDX_Control(pDX, IDC_RESULTS, m_ctrlRes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewResults, CDialog)
	//{{AFX_MSG_MAP(CDlgViewResults)
	ON_BN_CLICKED(IDC_SHOW_IN_SAME, OnShowInSame)
	ON_BN_CLICKED(IDC_DELETE_OPT_RES_CMD, OnDeleteOptResCmd)
	ON_BN_CLICKED(IDC_CHECK_USE_COLORS, OnCheckUseColors)
	ON_BN_CLICKED(IDC_CHECK_USE_LINESTYLES, OnCheckUseLinestyles)
	ON_BN_CLICKED(IDC_MENU_SHOW_GRAPH, OnPopupShowGraph)
	ON_BN_CLICKED(IDC_MENU_VIEW_SOLUTION, OnPopupViewSolution)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults message handlers

BEGIN_EVENTSINK_MAP(CDlgViewResults, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgViewResults)
	ON_EVENT(CDlgViewResults, IDC_RESULTS, -601 /* DblClick */, OnDblClickResults, VTS_NONE)
	ON_EVENT(CDlgViewResults, IDC_RESULTS, -605 /* MouseDown */, OnMouseDownResults, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgViewResults::OnDblClickResults() 
{
	long	SelRow = m_ctrlRes.GetRowSel();
	CDlgViewGraphResults *pDlg = NULL;

	if( SelRow >= 1 && SelRow < m_ctrlRes.GetRows() )
	{
		if( bShowGraphsInSameWnd == TRUE ) {	// zna�i da ne�emo otvarati novi prozor
			int		SelDlg = 0;

			if( vecGraphPtr.size() == 0 ) 
			{
				// morati �emo ipak najprije otvoriti bar jednoga budu�i da dosada nije nijedan otvoren
				pDlg = new CDlgViewGraphResults(this);

				vecGraphPtr.resize(1);
				vecNum.resize(1);
				vecGraphPtr[0] = pDlg;
				vecNum[0] = 0;

				// zatim prilago�avamo naziv prozora
				CString		csWndName;
				pDlg->GetWindowText(csWndName);
				char	strAdd[30];
				sprintf(strAdd, " : Graph - 0");
				csWndName += strAdd;
				pDlg->SetWindowText(LPCTSTR(csWndName));
			}
			else if( vecGraphPtr.size() > 1 )
			{
				// ukoliko smo otvorili vi�e prozora, a �elimo ovoga kojeg sada otvaramo staviti
				// u jedan od njih, ovdje �emo ga izabrati
				CDlgSelectGraphNumber		Dlg;

				SelDlg = -1;
				do {
					if( Dlg.DoModal() == IDOK ) {
						// moramo provjeriti da li je unesen ispravan broj grafa
						for( int i=0; i<vecNum.size(); i++ )
							if( vecNum[i] == Dlg.m_nGraphNum ) {
								SelDlg = i;
								break;
							}
					}
					else
						return;
				} while( SelDlg == -1 );
			}

			// uzimamo pokaziva� na odabrani dijalog
			pDlg = vecGraphPtr[SelDlg];

			char	strLegend[300];
			long	*X, ResSize, IterNum;
			float	*pdX, *Y, EndX;

			ResSize = pDoc->vecSol[SelRow-1].getResultsNum();
			X				= new long[ResSize];
			Y				= new float[ResSize];
			pdX			= new float[ResSize];	// treba nam float jer samo takvo pole prima Graph kontrola

			// uzmi sve vrijednosti potrebne za crtanje grafa
			IterNum = pDoc->vecSol[SelRow-1].getIterNum();
			pDoc->vecSol[SelRow-1].getAllFuncValues(X,Y);
			pDoc->vecAlgDesc[SelRow-1].getParamInString(strLegend);

			// iskopiraj ih u float polje
			for( int i=0; i<ResSize; i++ )
				pdX[i] = X[i];

			BOOL	ret = pDlg->m_ctrlGraph.DoesGraphAlreadyExist(pdX, Y, ResSize);
			if( ret == FALSE )
			{
				pDlg->m_ctrlGraph.SetUseLineStyles(TRUE);
				// za zavr�nu iteraciju postavi onog najve�eg
				EndX = pDlg->m_ctrlGraph.GetEndX();
				if( IterNum > EndX )
					pDlg->m_ctrlGraph.SetEndX(IterNum);

				// postavi po�etni x ( koji je uvijek isti jer broj iteracija kre�e od 0, ali �emo se mi
				// dati malo desno, kako bi se vidio po�etak grafa )
				pDlg->m_ctrlGraph.SetStartX(-pDlg->m_ctrlGraph.GetEndX()/15);
				
				pDlg->m_ctrlGraph.AddGraph(pdX, Y, ResSize, strLegend);
				pDlg->m_ctrlGraph.SetLegendPos(40,85);
				pDlg->m_ctrlGraph.RedrawWindow();
				pDlg->ShowWindow(TRUE);
			}
		}
		else {			// e ipak ho�emo 
			pDlg = new CDlgViewGraphResults(this);

			// najprije dodajemo pokaziva� na dijalog u listu otvorenih dijaloga
			int		sz = vecGraphPtr.size();
			vecGraphPtr.resize(sz+1);
			vecNum.resize(sz+1);
			vecGraphPtr[sz] = pDlg;
			if( sz == 0 )
				vecNum[sz] = 0;
			else
				vecNum[sz] = vecNum[sz-1] + 1;		// sljede�i graf ima za jedan broj ve�i od prethodnika

			// zatim prilago�avamo naziv prozora
			CString		csWndName;
			pDlg->GetWindowText(csWndName);
			char	strAdd[30];
			sprintf(strAdd, " : Graph - %d", vecNum[sz]);
			csWndName += strAdd;
			pDlg->SetWindowText(LPCTSTR(csWndName));

			// i onda dodajemo podatke za grafove
			long	ResSize = pDoc->vecSol[SelRow-1].getResultsNum();
			char	strLegend[300];
			long	*X = new long[ResSize];
			float	*Y = new float[ResSize];
			float	*pdX = new float[ResSize];	// treba nam float jer samo takvo polje prima Graph kontrola

			pDoc->vecSol[SelRow-1].getAllFuncValues(X,Y);
			for( int i=0; i<ResSize; i++ )
				pdX[i] = X[i];
			pDoc->vecAlgDesc[SelRow-1].getParamInString(strLegend);

			long	IterNum = pDoc->vecSol[SelRow-1].getIterNum();

			pDlg->m_ctrlGraph.SetUseLineStyles(TRUE);
			pDlg->m_ctrlGraph.SetStartX(-IterNum/15);
			pDlg->m_ctrlGraph.SetEndX(IterNum);
			short ID = pDlg->m_ctrlGraph.AddGraph(pdX, Y, ResSize, strLegend);

			pDlg->m_ctrlGraph.RedrawWindow();
			pDlg->ShowWindow(TRUE);
		}
	}
}

void CDlgViewResults::PostNcDestroy() 
{
	// treba obavijestiti sve otvorene dijaloge za prikaz grafova da smo zatvorili dijalog
	// prikaza rezultata
	for( int i=0; i<vecGraphPtr.size(); i++ )
		vecGraphPtr[i]->OwnerClosed();

	delete this;

//	CDialog::PostNcDestroy();
}

void CDlgViewResults::OnCancel() 
{
	DestroyWindow();
}

void CDlgViewResults::OnShowInSame() 
{
	if( bShowGraphsInSameWnd == TRUE ) {
		bShowGraphsInSameWnd = FALSE;
		m_ctrlShowSame.SetCheck(FALSE);
	}
	else {
		bShowGraphsInSameWnd = TRUE;
		m_ctrlShowSame.SetCheck(TRUE);
	}
}

void CDlgViewResults::OnDeleteOptResCmd() 
{
	long	SelRow = m_ctrlRes.GetRowSel();

	if( SelRow >= 1 && SelRow < m_ctrlRes.GetRows() )
	{
		pDoc->DeleteOptimizationResult(SelRow-1);
		m_ctrlRes.Clear();
		pDoc->FillDialogWithResults(this);
	}
}

void CDlgViewResults::ChildClosed(CDlgViewGraphResults *pDlg)
{
	// treba u popisu otvorenih prozora na�i onoga na kojeg pokazuje pDlg i izbaciti ga
	for( int i=0; i<vecGraphPtr.size(); i++ )
		if( vecGraphPtr[i] == pDlg ) {
			vecGraphPtr.erase(vecGraphPtr.begin() + i);
			vecNum.erase(vecNum.begin() + i );

			return;
		}
	// to zna�i da je ova funkcija pozvana sa pokaziva�em na dijalog kojeg nema u listi
	// otvorenih dijaloga
	ASSERT(1);
}

void CDlgViewResults::OnCheckUseColors() 
{
	if(	bUseColors == TRUE ) {
		bUseColors = FALSE;
		m_ctrlUseColors.SetCheck(FALSE);
	}
	else {
		bUseColors = TRUE;
		m_ctrlUseColors.SetCheck(TRUE);
	}
	RedrawAllGraphs();
}

void CDlgViewResults::OnCheckUseLinestyles() 
{
	if( bUseLineStyle == TRUE ) {
		bUseLineStyle = FALSE;
		m_ctrlUseLineStyle.SetCheck(FALSE);
	}
	else {
		bUseLineStyle = TRUE;
		m_ctrlUseLineStyle.SetCheck(TRUE);
	}
	RedrawAllGraphs();
}

void	CDlgViewResults::RedrawAllGraphs()
{
	int		sz = vecGraphPtr.size();
	CDlgViewGraphResults *pDlg;

	for( int i=0; i<sz; i++ ) {
		pDlg = vecGraphPtr[i];
		pDlg->m_ctrlGraph.SetUseColors(bUseColors);
		pDlg->m_ctrlGraph.SetUseLineStyles(bUseLineStyle);

		pDlg->m_ctrlGraph.RedrawWindow();
	}
}

void CDlgViewResults::OnMouseDownResults(short Button, short Shift, long x, long y) 
{
	if( Button == 2 )			// pritisnuto desno dugme
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		CRect	pos;
		m_ctrlRes.GetWindowRect(&pos);

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.left+x, pos.top+y, this); //AfxGetMainWnd());
	}
}

void CDlgViewResults::OnPopupViewSolution()
{
	AfxMessageBox("Keloza 1");
}

void CDlgViewResults::OnPopupShowGraph()
{
	AfxMessageBox("Keloza 2");
}

