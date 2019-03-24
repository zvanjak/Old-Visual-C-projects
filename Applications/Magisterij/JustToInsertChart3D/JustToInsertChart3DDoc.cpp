// JustToInsertChart3DDoc.cpp : implementation of the CJustToInsertChart3DDoc class
//

#include "stdafx.h"
#include "JustToInsertChart3D.h"

#include "JustToInsertChart3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DDoc

IMPLEMENT_DYNCREATE(CJustToInsertChart3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CJustToInsertChart3DDoc, CDocument)
	//{{AFX_MSG_MAP(CJustToInsertChart3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DDoc construction/destruction

CJustToInsertChart3DDoc::CJustToInsertChart3DDoc()
{
	// TODO: add one-time construction code here

}

CJustToInsertChart3DDoc::~CJustToInsertChart3DDoc()
{
}

BOOL CJustToInsertChart3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DDoc serialization

void CJustToInsertChart3DDoc::Serialize(CArchive& ar)
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
// CJustToInsertChart3DDoc diagnostics

#ifdef _DEBUG
void CJustToInsertChart3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJustToInsertChart3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJustToInsertChart3DDoc commands
