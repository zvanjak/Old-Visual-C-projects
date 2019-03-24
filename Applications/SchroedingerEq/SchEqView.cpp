// SchEqView.cpp : implementation of the CSchEqView class
//

#include "stdafx.h"
#include "SchroedingerEq.h"

#include "SchEqDoc.h"
#include "SchEqView.h"

//#include "Integration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchEqView

IMPLEMENT_DYNCREATE(CSchEqView, CView)

BEGIN_MESSAGE_MAP(CSchEqView, CView)
	//{{AFX_MSG_MAP(CSchEqView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_DRAW_METAFILE, OnDrawMetafile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchEqView construction/destruction

CSchEqView::CSchEqView()
{
	nGraphID = -1;
}

CSchEqView::~CSchEqView()
{
}

BOOL CSchEqView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSchEqView drawing

#define		XEXT		10000
#define		YEXT		10000

void DrawLine( CDC *pDC, long x1, long y1, long x2, long y2 )
{
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CSchEqView::OnDraw(CDC* pDC)
{
	CSchEqDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if( pDoc->bClearAll == true ) {
		m_ctrlGraph.RemoveAllGraphs();
		pDoc->bClearAll = false;
	}

	if( pDoc->bPotAdded == false ) {
		pDoc->PotGraphID = m_ctrlGraph.AddGraph(pDoc->xPot, pDoc->yPot, POTFUNC_POINTS_NUM, "Potencijal");
		pDoc->bPotAdded = true;
	}
	else if( pDoc->bPotChanged == true ) {
		m_ctrlGraph.ChangeGraphData(pDoc->PotGraphID, pDoc->xPot, pDoc->yPot, POTFUNC_POINTS_NUM, "Potencijal");
		pDoc->bPotChanged = false;
	}

	for( int i=0; i<pDoc->vecEnergy.size(); i++ ) {
		if( pDoc->vecAdded[i] == false ) {
			char		str[200];

			// za gustoæu vjerojatnost
			sprintf(str, "Valna funkcija E=%6.3f", pDoc->vecEnergy[i] );
/*
			if( pDoc->bViewNumInt == true ) 
				sprintf(str, "Num.int.val.fun. E=%6.3f", pDoc->vecEnergy[i] );
			else
				sprintf(str, "Perturbirana val.fun. E=%6.3f", pDoc->CalcPerturbation2(i+1) );
*/
			m_ctrlGraph.AddGraph(pDoc->vecpXPsi[i], pDoc->vecpYPsi[i], pDoc->vecPntNum[i], str);
			pDoc->vecAdded[i] = true;
		}
	}

	float	dx = pDoc->a2 - pDoc->a1;
	float	a1Exp = pDoc->a1 - fabs(dx * 0.1);
	float	a2Exp = pDoc->a2 + fabs(dx * 0.1);

	m_ctrlGraph.SetStartX(a1Exp);
	m_ctrlGraph.SetEndX(a2Exp);

	m_ctrlGraph.Invalidate();

	// energije za V0 = 0
//	E1 = 0.0222;
//	E2 = 0.09;
//	E3 = 0.22;
//	E4 = 0.4;

// Energije za V0 = 1.5
//	E1 = 0.2889;
//	E2 = 1.1039;
//	E3 = 2.15;

// Energije za V0 = 5
//	E1 = 0.3319994957;
//	E2 = 1.319586;
//	E3 = 2.9266;
}


/////////////////////////////////////////////////////////////////////////////
// CSchEqView printing

BOOL CSchEqView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSchEqView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSchEqView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSchEqView diagnostics

#ifdef _DEBUG
void CSchEqView::AssertValid() const
{
	CView::AssertValid();
}

void CSchEqView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSchEqDoc* CSchEqView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSchEqDoc)));
	return (CSchEqDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchEqView message handlers

int CSchEqView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ctrlGraph.Create("Caption jumbo", WS_VISIBLE, CRect(0,0,100,100), this, 0);
	
	return 0;
}

void CSchEqView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CSchEqDoc* pDoc = GetDocument();

	CRect		rect;
	GetClientRect(&rect);
	m_ctrlGraph.SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW );	
	m_ctrlGraph.SetUseLineStyles(TRUE);
	m_ctrlGraph.SetUseColors(TRUE);
//	m_ctrlGraph.RemoveAllGraphs();
/*
	float xc, x[5000], y1[5000];
	int		i;

	a = pDoc->a;
	b = pDoc->b;
	V0 = pDoc->V0;
	E = pDoc->E;

	for( i=0, xc = -11.; xc<11.; xc+=0.01, i++ )
	{
		x[i] = xc;
		y1[i] = f(xc, a, b, V0);
	}

	nPotGraphID = m_ctrlGraph.AddGraph(x, y1, i, "Graph 1 - potencijal");

	m_ctrlGraph.SetTitle("Potencijalna jama");
	m_ctrlGraph.SetEndX(15.0);
	m_ctrlGraph.SetStartX(-15.0);
	*/
}

void CSchEqView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( nType == SIZE_RESTORED )
	{
		CRect		rect;
		GetClientRect(&rect);
		m_ctrlGraph.SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW );	
	}
	
}


void CSchEqView::OnDrawMetafile() 
{
	CFileDialog	dlg(TRUE);

	if( dlg.DoModal() == IDOK )
	{
		m_ctrlGraph.DrawtToMetafile(dlg.GetPathName(), 1000, 650);
	}
}
