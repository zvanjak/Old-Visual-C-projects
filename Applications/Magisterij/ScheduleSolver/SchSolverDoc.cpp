// SchSolverDoc.cpp : implementation of the CSchSolverDoc class
//

#include "stdafx.h"
#include "ScheduleSolver.h"

#include "SchSolverDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchSolverDoc

IMPLEMENT_DYNCREATE(CSchSolverDoc, CDocument)

BEGIN_MESSAGE_MAP(CSchSolverDoc, CDocument)
	//{{AFX_MSG_MAP(CSchSolverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSchSolverDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CSchSolverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IScheduleSolver to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {712970CA-F29F-4DEA-B9F5-A13814AF7B22}
static const IID IID_IScheduleSolver =
{ 0x712970ca, 0xf29f, 0x4dea, { 0xb9, 0xf5, 0xa1, 0x38, 0x14, 0xaf, 0x7b, 0x22 } };

BEGIN_INTERFACE_MAP(CSchSolverDoc, CDocument)
	INTERFACE_PART(CSchSolverDoc, IID_IScheduleSolver, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchSolverDoc construction/destruction

CSchSolverDoc::CSchSolverDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CSchSolverDoc::~CSchSolverDoc()
{
	AfxOleUnlockApp();
}

BOOL CSchSolverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSchSolverDoc serialization

void CSchSolverDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSchSolverDoc diagnostics

#ifdef _DEBUG
void CSchSolverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSchSolverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchSolverDoc commands
