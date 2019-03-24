// OptRokDoc.cpp : implementation of the COptRokDoc class
//

#include "stdafx.h"
#include "OptRok.h"

#include "OptRokDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptRokDoc

IMPLEMENT_DYNCREATE(COptRokDoc, CDocument)

BEGIN_MESSAGE_MAP(COptRokDoc, CDocument)
	//{{AFX_MSG_MAP(COptRokDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COptRokDoc, CDocument)
	//{{AFX_DISPATCH_MAP(COptRokDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOptRok to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3E869BAA-9507-46BA-BEAC-F433D217818E}
static const IID IID_IOptRok =
{ 0x3e869baa, 0x9507, 0x46ba, { 0xbe, 0xac, 0xf4, 0x33, 0xd2, 0x17, 0x81, 0x8e } };

BEGIN_INTERFACE_MAP(COptRokDoc, CDocument)
	INTERFACE_PART(COptRokDoc, IID_IOptRok, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRokDoc construction/destruction

COptRokDoc::COptRokDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

COptRokDoc::~COptRokDoc()
{
	AfxOleUnlockApp();
}

BOOL COptRokDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COptRokDoc serialization

void COptRokDoc::Serialize(CArchive& ar)
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
// COptRokDoc diagnostics

#ifdef _DEBUG
void COptRokDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COptRokDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptRokDoc commands
