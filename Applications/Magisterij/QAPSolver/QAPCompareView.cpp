// QAPCompareView.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "QAPCompareView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareView

IMPLEMENT_DYNCREATE(CQAPCompareView, CView)

CQAPCompareView::CQAPCompareView()
{
}

CQAPCompareView::~CQAPCompareView()
{
}


BEGIN_MESSAGE_MAP(CQAPCompareView, CView)
	//{{AFX_MSG_MAP(CQAPCompareView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareView drawing

void CQAPCompareView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareView diagnostics

#ifdef _DEBUG
void CQAPCompareView::AssertValid() const
{
	CView::AssertValid();
}

void CQAPCompareView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareView message handlers
