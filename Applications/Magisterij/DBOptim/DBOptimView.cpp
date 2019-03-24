// DBOptimView.cpp : implementation of the CDBOptimView class
//

#include "stdafx.h"
#include "DBOptim.h"

#include "DBOptimSet.h"
#include "DBOptimDoc.h"
#include "DBOptimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBOptimView

IMPLEMENT_DYNCREATE(CDBOptimView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CDBOptimView, COleDBRecordView)
	//{{AFX_MSG_MAP(CDBOptimView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, COleDBRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBOptimView construction/destruction

CDBOptimView::CDBOptimView()
	: COleDBRecordView(CDBOptimView::IDD)
{
	//{{AFX_DATA_INIT(CDBOptimView)
		// NOTE: the ClassWizard will add member initialization here
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDBOptimView::~CDBOptimView()
{
}

void CDBOptimView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBOptimView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDBOptimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CDBOptimView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_dBOptimSet;
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->Open();
		if (hr != S_OK)
		{
			AfxMessageBox(_T("Record set failed to open."), MB_OK);
			// Disable the Next and Previous record commands,
			// since attempting to change the current record without an
			// open RecordSet will cause a crash.
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}				
	}
	COleDBRecordView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// CDBOptimView printing

BOOL CDBOptimView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBOptimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBOptimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDBOptimView diagnostics

#ifdef _DEBUG
void CDBOptimView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CDBOptimView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CDBOptimDoc* CDBOptimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBOptimDoc)));
	return (CDBOptimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBOptimView database support
CRowset* CDBOptimView::OnGetRowset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CDBOptimView message handlers
