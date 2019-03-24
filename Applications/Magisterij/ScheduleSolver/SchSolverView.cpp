// SchSolverView.cpp : implementation of the CSchSolverView class
//

#include "stdafx.h"
#include "ScheduleSolver.h"

#include "SchSolverDoc.h"
#include "SchSolverView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView

IMPLEMENT_DYNCREATE(CSchSolverView, CEditView)

BEGIN_MESSAGE_MAP(CSchSolverView, CEditView)
	//{{AFX_MSG_MAP(CSchSolverView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView construction/destruction

CSchSolverView::CSchSolverView()
{
	// TODO: add construction code here

}

CSchSolverView::~CSchSolverView()
{
}

BOOL CSchSolverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView drawing

void CSchSolverView::OnDraw(CDC* pDC)
{
	CSchSolverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView printing

BOOL CSchSolverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CSchSolverView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSchSolverView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView diagnostics

#ifdef _DEBUG
void CSchSolverView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSchSolverView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSchSolverDoc* CSchSolverView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSchSolverDoc)));
	return (CSchSolverDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchSolverView message handlers
