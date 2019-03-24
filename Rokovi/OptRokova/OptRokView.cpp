// OptRokView.cpp : implementation of the COptRokView class
//

#include "stdafx.h"
#include "OptRokova.h"

#include "OptRokDoc.h"
#include "OptRokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptRokView

IMPLEMENT_DYNCREATE(COptRokView, CView)

BEGIN_MESSAGE_MAP(COptRokView, CView)
	//{{AFX_MSG_MAP(COptRokView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRokView construction/destruction

COptRokView::COptRokView()
{
	// TODO: add construction code here

}

COptRokView::~COptRokView()
{
}

BOOL COptRokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COptRokView drawing

void COptRokView::OnDraw(CDC* pDC)
{
	COptRokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COptRokView printing

BOOL COptRokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COptRokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COptRokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COptRokView diagnostics

#ifdef _DEBUG
void COptRokView::AssertValid() const
{
	CView::AssertValid();
}

void COptRokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COptRokDoc* COptRokView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COptRokDoc)));
	return (COptRokDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptRokView message handlers
