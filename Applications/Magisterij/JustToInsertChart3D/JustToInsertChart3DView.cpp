// JustToInsertChart3DView.cpp : implementation of the CJustToInsertChart3DView class
//

#include "stdafx.h"
#include "JustToInsertChart3D.h"

#include "JustToInsertChart3DDoc.h"
#include "JustToInsertChart3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView

IMPLEMENT_DYNCREATE(CJustToInsertChart3DView, CView)

BEGIN_MESSAGE_MAP(CJustToInsertChart3DView, CView)
	//{{AFX_MSG_MAP(CJustToInsertChart3DView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView construction/destruction

CJustToInsertChart3DView::CJustToInsertChart3DView()
{
	// TODO: add construction code here

}

CJustToInsertChart3DView::~CJustToInsertChart3DView()
{
}

BOOL CJustToInsertChart3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView drawing

void CJustToInsertChart3DView::OnDraw(CDC* pDC)
{
	CJustToInsertChart3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView printing

BOOL CJustToInsertChart3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJustToInsertChart3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJustToInsertChart3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView diagnostics

#ifdef _DEBUG
void CJustToInsertChart3DView::AssertValid() const
{
	CView::AssertValid();
}

void CJustToInsertChart3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJustToInsertChart3DDoc* CJustToInsertChart3DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJustToInsertChart3DDoc)));
	return (CJustToInsertChart3DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DView message handlers
