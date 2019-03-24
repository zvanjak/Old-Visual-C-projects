// QAPSolverView.cpp : implementation of the CQAPSolverView class
//

#include "stdafx.h"
#include "QAPSolver.h"

#include "QAPSolverDoc.h"
#include "QAPSolverView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView

IMPLEMENT_DYNCREATE(CQAPSolverView, CView)

BEGIN_MESSAGE_MAP(CQAPSolverView, CView)
	//{{AFX_MSG_MAP(CQAPSolverView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView construction/destruction

CQAPSolverView::CQAPSolverView()
{
	// TODO: add construction code here

}

CQAPSolverView::~CQAPSolverView()
{
}

BOOL CQAPSolverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView drawing

void CQAPSolverView::OnDraw(CDC* pDC)
{
	CQAPSolverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView printing

BOOL CQAPSolverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CQAPSolverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CQAPSolverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView diagnostics

#ifdef _DEBUG
void CQAPSolverView::AssertValid() const
{
	CView::AssertValid();
}

void CQAPSolverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CQAPSolverDoc* CQAPSolverView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQAPSolverDoc)));
	return (CQAPSolverDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQAPSolverView message handlers
