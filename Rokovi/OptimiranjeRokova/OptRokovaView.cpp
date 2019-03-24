// OptRokovaView.cpp : implementation of the COptRokovaView class
//

#include "stdafx.h"
#include "OptimiranjeRokova.h"

#include "OptRokovaDoc.h"
#include "OptRokovaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView

IMPLEMENT_DYNCREATE(COptRokovaView, CView)

BEGIN_MESSAGE_MAP(COptRokovaView, CView)
	//{{AFX_MSG_MAP(COptRokovaView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView construction/destruction

COptRokovaView::COptRokovaView()
{
	// TODO: add construction code here

}

COptRokovaView::~COptRokovaView()
{
}

BOOL COptRokovaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView drawing

void COptRokovaView::OnDraw(CDC* pDC)
{
	COptRokovaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView printing

BOOL COptRokovaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COptRokovaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COptRokovaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView diagnostics

#ifdef _DEBUG
void COptRokovaView::AssertValid() const
{
	CView::AssertValid();
}

void COptRokovaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COptRokovaDoc* COptRokovaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COptRokovaDoc)));
	return (COptRokovaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptRokovaView message handlers
