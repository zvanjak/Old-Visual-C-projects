// OptScheduleDoc.cpp : implementation of the COptScheduleDoc class
//

#include "stdafx.h"
#include "OptSchedule.h"

#include "OptScheduleDoc.h"
#include "DlgViewData.h"
#include "DlgSetModelDescr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptScheduleDoc

IMPLEMENT_DYNCREATE(COptScheduleDoc, CDocument)

BEGIN_MESSAGE_MAP(COptScheduleDoc, CDocument)
	//{{AFX_MSG_MAP(COptScheduleDoc)
	ON_COMMAND(ID_DATA_VIEW, OnDataView)
	ON_COMMAND(ID_DATA_VIEW_MODEL, OnDataViewModel)
	ON_COMMAND(ID_OPTIMIZATION_SET_MODEL_DATA, OnSetModelDescription)
	ON_COMMAND(ID_FILE_LOAD_EXTERNAL, OnFileLoadExternalData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COptScheduleDoc, CDocument)
	//{{AFX_DISPATCH_MAP(COptScheduleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOptSchedule to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D9D562D3-661A-4FF4-8902-892878E93DA0}
static const IID IID_IOptSchedule =
{ 0xd9d562d3, 0x661a, 0x4ff4, { 0x89, 0x2, 0x89, 0x28, 0x78, 0xe9, 0x3d, 0xa0 } };

BEGIN_INTERFACE_MAP(COptScheduleDoc, CDocument)
	INTERFACE_PART(COptScheduleDoc, IID_IOptSchedule, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptScheduleDoc construction/destruction

COptScheduleDoc::COptScheduleDoc()
{
	// TODO: add one-time construction code here
	FileData	*pData = new FileData("predmet.txt", "nasprog1.txt", NULL, "presjek1.txt" );

	m_ProbData.SetDataObject(pData);
	m_ProbData.LoadAllData(NULL);

//	pQAPSolver = new GeneticQAPSolver(10, 70, 10000, 0.01);
	EnableAutomation();

	AfxOleLockApp();
}

COptScheduleDoc::~COptScheduleDoc()
{
	AfxOleUnlockApp();
}

BOOL COptScheduleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COptScheduleDoc serialization

void COptScheduleDoc::Serialize(CArchive& ar)
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
// COptScheduleDoc diagnostics

#ifdef _DEBUG
void COptScheduleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COptScheduleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// COptScheduleDoc pomoæne funkcije

void COptScheduleDoc::ViewData(ProblemData &ref)
{
	CDlgViewData	*pDlg;
	pDlg = new CDlgViewData();

	HTREEITEM	ret;

	int		i, j;
	char	str[200];
	
	for( i=0; i<ref.BrojIspita(); i++ ) {
		const Ispit&	ispit = ref.getPredmetIndex(i);
		
		if( ispit.getBrojDodPod() > 0 ) {
			sprintf(str, "%d   %s", ispit.getSifra() , ispit.getNaziv().c_str() );
			ret = pDlg->m_ctrlDataTree.InsertItem(str);
			
			for( j=0; j<ispit.getBrojDodPod(); j++ ) {
				sprintf(str, "semestar=%d   broj stud=%d  opis=%c   smjer=%d   grupa pred.=%d", ispit.getSemestar(j), ispit.getBrojStud(j), ispit.getOpis(j), ispit.getSmjer(j), ispit.getGrupaPred(j) );
				pDlg->m_ctrlDataTree.InsertItem(str, ret);
			}
		}
	}

	int									ispitBr;
	const IPresjekCollection&	presjek = ref.getPresjek();
/*	
	// proæi æemo kroz sve retke u matrici presjeka
	for( i=0; i<presjek.getBrojRedaka(); i++ ) {
		// najprijemoramo saznati sifru predmeta èiji presjeci se nalaze u tom retku
		ispitBr = presjek.getSifraRetka(i);
		
		// zatim uzimamo podatke o tom ispitu
		Ispit&	ispit=ref.getPredmetSifra(ispitBr);
		sprintf(str, "%d   %s    presjeka = %d", ispit.getSifra() , ispit.getNaziv().c_str(), presjek.getBrojPresjeka(i));
		ret = pDlg->m_ctrlTreePresjeci.InsertItem(str);

		// a zatim dodajemo sve presjeke koji se nalaze u tom retku
		for( j=0; j<presjek.getBrojPresjeka(i); j++ ) {
			// uzimamo podatke o paru sifra-presjek iz tog mjesta u matrici
			ParSifraPresjek&	par = presjek.getPresjekRedStup(i,j);
			
			Ispit&	ispit2 = ref.getPredmetSifra(par.m_nSifra);
			sprintf(str, "%3d  -  %s", par.m_nPresjek , ispit2.getNaziv().c_str() );
			pDlg->m_ctrlTreePresjeci.InsertItem(str, ret);
		}
	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// COptScheduleDoc commands

void COptScheduleDoc::OnDataView() 
{
	ViewData(m_ProbData.getProblemData());
}

void COptScheduleDoc::OnDataViewModel() 
{
	ViewData(m_ProbData.getModelData());
}


void COptScheduleDoc::OnSetModelDescription() 
{
	CDlgSetModelDescr	*pDlg;
	pDlg = new CDlgSetModelDescr();

	char	Opis[10];
	m_ProbData.GetModelDescription(pDlg->m_nSemLow, pDlg->m_nSemUpp, pDlg->m_nBrojStudLow, pDlg->m_nBrojStudUpp, Opis);

	if( strchr(Opis, 'O') != NULL )
		pDlg->m_bObavezni = true;
	else
		pDlg->m_bObavezni = false ;

	if( strchr(Opis, 'I') != NULL )
		pDlg->m_bIzborni = true;
	else
		pDlg->m_bIzborni = false;

	if( strchr(Opis, 'H') != NULL )
		pDlg->m_bHuman = true;
	else
		pDlg->m_bHuman = false;
	
	if( strchr(Opis, 'K') != NULL )
		pDlg->m_bSeminar = true;
	else
		pDlg->m_bSeminar = false;
	
	if( strchr(Opis, 'D') != NULL )
		pDlg->m_bDiplomski = true;
	else
		pDlg->m_bDiplomski = false;

	if( pDlg->DoModal() == IDOK ){
		int		j=0;

		if( pDlg->m_bObavezni )
			Opis[j++] = 'O';
		if( pDlg->m_bIzborni )
			Opis[j++] = 'I';
		if( pDlg->m_bHuman )
			Opis[j++] = 'H';
		if( pDlg->m_bSeminar )
			Opis[j++] = 'K';
		if( pDlg->m_bDiplomski )
			Opis[j++] = 'D';
		
		Opis[j] = 0;

		m_ProbData.SetModelDescription(pDlg->m_nSemLow, pDlg->m_nSemUpp, pDlg->m_nBrojStudLow, pDlg->m_nBrojStudUpp, Opis);
		m_ProbData.PostaviPodatkeModela();
	}
}

void COptScheduleDoc::OnFileLoadExternalData() 
{
	// TODO: Add your command handler code here
	
}
