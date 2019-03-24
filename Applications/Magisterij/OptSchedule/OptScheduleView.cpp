// OptScheduleView.cpp : implementation of the COptScheduleView class
//

#include "stdafx.h"
#include "OptSchedule.h"

#include "OptScheduleDoc.h"
#include "OptScheduleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView

IMPLEMENT_DYNCREATE(COptScheduleView, CView)

BEGIN_MESSAGE_MAP(COptScheduleView, CView)
	//{{AFX_MSG_MAP(COptScheduleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView construction/destruction

COptScheduleView::COptScheduleView()
{
	// TODO: add construction code here

}

COptScheduleView::~COptScheduleView()
{
}

BOOL COptScheduleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView drawing

void COptScheduleView::OnDraw(CDC* pDC)
{
	COptScheduleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView printing

BOOL COptScheduleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COptScheduleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COptScheduleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView diagnostics

#ifdef _DEBUG
void COptScheduleView::AssertValid() const
{
	CView::AssertValid();
}

void COptScheduleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COptScheduleDoc* COptScheduleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COptScheduleDoc)));
	return (COptScheduleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptScheduleView message handlers
