// DBOptimDoc.cpp : implementation of the CDBOptimDoc class
//

#include "stdafx.h"
#include "DBOptim.h"

#include "DBOptimSet.h"
#include "DBOptimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBOptimDoc

IMPLEMENT_DYNCREATE(CDBOptimDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBOptimDoc, CDocument)
	//{{AFX_MSG_MAP(CDBOptimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDBOptimDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CDBOptimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDBOptim to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E54B71E6-D607-4496-99D2-164B574D6BBD}
static const IID IID_IDBOptim =
{ 0xe54b71e6, 0xd607, 0x4496, { 0x99, 0xd2, 0x16, 0x4b, 0x57, 0x4d, 0x6b, 0xbd } };

BEGIN_INTERFACE_MAP(CDBOptimDoc, CDocument)
	INTERFACE_PART(CDBOptimDoc, IID_IDBOptim, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBOptimDoc construction/destruction

CDBOptimDoc::CDBOptimDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CDBOptimDoc::~CDBOptimDoc()
{
	AfxOleUnlockApp();
}

BOOL CDBOptimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDBOptimDoc serialization

void CDBOptimDoc::Serialize(CArchive& ar)
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
// CDBOptimDoc diagnostics

#ifdef _DEBUG
void CDBOptimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBOptimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBOptimDoc commands
