// TestOptFuncDoc.cpp : implementation of the CTestOptFuncDoc class
//

#include "stdafx.h"
#include "TestOptFunc.h"

#include "TestOptFuncDoc.h"

#include "TestFuncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncDoc

IMPLEMENT_DYNCREATE(CTestOptFuncDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestOptFuncDoc, CDocument)
	//{{AFX_MSG_MAP(CTestOptFuncDoc)
	ON_COMMAND(ID_TEST_START, OnTestStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncDoc construction/destruction

CTestOptFuncDoc::CTestOptFuncDoc()
{
	// TODO: add one-time construction code here

}

CTestOptFuncDoc::~CTestOptFuncDoc()
{
}

BOOL CTestOptFuncDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncDoc serialization

void CTestOptFuncDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncDoc diagnostics

#ifdef _DEBUG
void CTestOptFuncDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestOptFuncDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestOptFuncDoc commands

void CTestOptFuncDoc::OnTestStart() 
{
	// TODO: Add your command handler code here
	CTestFuncDlg	*pDlg;
	
	pDlg = new CTestFuncDlg();
}
