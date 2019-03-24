// OptRokovaDoc.cpp : implementation of the COptRokovaDoc class
//

#include "stdafx.h"
#include "OptimiranjeRokova.h"

#include "OptRokovaDoc.h"
#include "DlgOptimizacija.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptRokovaDoc

IMPLEMENT_DYNCREATE(COptRokovaDoc, CDocument)

BEGIN_MESSAGE_MAP(COptRokovaDoc, CDocument)
	//{{AFX_MSG_MAP(COptRokovaDoc)
	ON_COMMAND(ID_OPTIMIZACIJA_POKRENI, OnOptimizacijaPokreni)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COptRokovaDoc, CDocument)
	//{{AFX_DISPATCH_MAP(COptRokovaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOptimiranjeRokova to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {EA3DC2B5-5F6F-42DE-A127-2A57FE3F34B5}
static const IID IID_IOptimiranjeRokova =
{ 0xea3dc2b5, 0x5f6f, 0x42de, { 0xa1, 0x27, 0x2a, 0x57, 0xfe, 0x3f, 0x34, 0xb5 } };

BEGIN_INTERFACE_MAP(COptRokovaDoc, CDocument)
	INTERFACE_PART(COptRokovaDoc, IID_IOptimiranjeRokova, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRokovaDoc construction/destruction

COptRokovaDoc::COptRokovaDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

COptRokovaDoc::~COptRokovaDoc()
{
	AfxOleUnlockApp();
}

BOOL COptRokovaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COptRokovaDoc serialization

void COptRokovaDoc::Serialize(CArchive& ar)
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
// COptRokovaDoc diagnostics

#ifdef _DEBUG
void COptRokovaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COptRokovaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptRokovaDoc commands

void COptRokovaDoc::OnOptimizacijaPokreni() 
{
	CDlgOptimizacija	*pDlg = new	CDlgOptimizacija();

	char		str[50];
	for( int i=0; i<40; i++ ) {
		sprintf(str, "Redak%2d", i);
		pDlg->m_ctrlPrikaz.AddRow(str);
	}	

	pDlg->m_ctrlPrikaz.AddRowTerm(0,5);
	pDlg->m_ctrlPrikaz.AddRowTerm(0,10);
	pDlg->m_ctrlPrikaz.AddRowTerm(0,17);

	int	RowNum = pDlg->m_ctrlPrikaz.GetRowNum();
//	int	RowsPerPage = 40 / RowNum;

	pDlg->m_ctrlVScroll.SetMax(40-RowNum);

	pDlg->m_ctrlVScroll.SetLargeChange(RowNum);
}
