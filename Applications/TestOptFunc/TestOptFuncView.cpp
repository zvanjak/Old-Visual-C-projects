// TestOptFuncView.cpp : implementation of the CTestOptFuncView class
//

#include "stdafx.h"
#include "TestOptFunc.h"

#include "TestOptFuncDoc.h"
#include "TestOptFuncView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView

IMPLEMENT_DYNCREATE(CTestOptFuncView, CView)

BEGIN_MESSAGE_MAP(CTestOptFuncView, CView)
	//{{AFX_MSG_MAP(CTestOptFuncView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView construction/destruction

CTestOptFuncView::CTestOptFuncView()
{
	// TODO: add construction code here

}

CTestOptFuncView::~CTestOptFuncView()
{
}

BOOL CTestOptFuncView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView drawing

void CTestOptFuncView::OnDraw(CDC* pDC)
{
	CTestOptFuncDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView printing

BOOL CTestOptFuncView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestOptFuncView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestOptFuncView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView diagnostics

#ifdef _DEBUG
void CTestOptFuncView::AssertValid() const
{
	CView::AssertValid();
}

void CTestOptFuncView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestOptFuncDoc* CTestOptFuncView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestOptFuncDoc)));
	return (CTestOptFuncDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncView message handlers
