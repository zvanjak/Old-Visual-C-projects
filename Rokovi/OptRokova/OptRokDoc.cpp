// OptRokDoc.cpp : implementation of the COptRokDoc class
//

#include "stdafx.h"
#include "OptRokova.h"

#include "OptRokDoc.h"

#include "DlgParametriRoka.h"
#include "DlgParamOptimizacije.h"
#include "DlgOptim.h"
#include "DlgPopisIspita.h"
#include "DlgVizualniPrikaz.h"
#include "DlgIspitiIstiDan.h"
#include "DlgPregledZelja.h"
#include "PregledSmjeroviGodinaDlg.h"
#include "DlgPregledSmjerGodinaVizualno.h"

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
	ON_COMMAND(ID_PARAM_OPTIMIZACIJE, OnPostaviParametreOptimizacije)
	ON_COMMAND(ID_PARAM_ROKA, OnPostaviParametreRoka)
	ON_COMMAND(ID_OPTIMIZACIJA_POKRENI, OnOptimizacijaPokreni)
	ON_COMMAND(ID_REZULTATI_PREGLED_PO_ISPITIMA, OnRezultatiPregledPoIspitima)
	ON_COMMAND(ID_REZULTATI_PREGLED_PO_GRUPAMA_PREDMETA, OnRezultatiPregledPoGrupamaPredmeta)
	ON_COMMAND(ID_VIZUALNI_PRIKAZ, OnRezultatiVizualniPrikaz)
	ON_COMMAND(ID_WRITE_ASCII, OnWriteAscii)
	ON_COMMAND(ID_REZULTATI_PREGLED_PO_SEMESTRIMA, OnRezultatiPregledPoSemestrima)
	ON_COMMAND(ID_PREGLED_ISPITI_ISTI_DAN, OnPregledIspitiIstiDan)
	ON_COMMAND(ID_PREGLED_ISPUNJ_ZELJA_PROF, OnPregledIspunjavanjeZeljaProf)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_PREGLED_PO_SMJEROVIMA, OnPregledPoSmjerovima)
	ON_COMMAND(ID_PREGLED_SMJEROVI_GODINE, OnPregledSmjeroviGodine)
	ON_COMMAND(ID_ASCII_DAT_SMJER_GOD, OnAsciiDatSmjerGod)
	ON_COMMAND(ID_PREGLED_SMJER_GOD_VIZUALNO, OnPregledSmjerGodVizualno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRokDoc construction/destruction

COptRokDoc::COptRokDoc()
{
	// TODO: add one-time construction code here
	int						i, num=0;
	Ispit					tmp;
	vector<Ispit>		vecSif(700);

	m_Opt = new OptProblem("predmet.txt", "nasprog1.txt", "presjek1.txt", "IspitiIstiDan.txt");

	m_Opt->vecFiksIspiti.resize(4);
	m_Opt->vecFiksIspiti[0] = 441;		// DISKRETNA MAT.
	m_Opt->matFiksDani[0][0] = 0;
	m_Opt->matFiksDani[0][1] = 18;
	m_Opt->matFiksDani[0][2] = 1;
	m_Opt->matFiksDani[0][3] = 4;
	m_Opt->matFiksDani[0][4] = 18;
	m_Opt->matFiksDani[0][5] = 29;
	m_Opt->matFiksDani[0][6] = 3;
	m_Opt->matFiksDani[0][7] = 11;
	m_Opt->matFiksDani[0][8] = 23;
	m_Opt->matFiksDani[0][9] = 0;


	m_Opt->vecFiksIspiti[1] = 429;		// NUMERIÈKA
	m_Opt->matFiksDani[1][0] = 0;
	m_Opt->matFiksDani[1][1] = 18;
	m_Opt->matFiksDani[1][2] = 1;
	m_Opt->matFiksDani[1][3] = 4;
	m_Opt->matFiksDani[1][4] = 18;
	m_Opt->matFiksDani[1][5] = 29;
	m_Opt->matFiksDani[1][6] = 3;
	m_Opt->matFiksDani[1][7] = 11;
	m_Opt->matFiksDani[1][8] = 23;
	m_Opt->matFiksDani[1][9] = 0;

	m_Opt->vecFiksIspiti[2] = 439;		// STOHASTIÈKA
	m_Opt->matFiksDani[2][0] = 11;
	m_Opt->matFiksDani[2][1] = 22;
	m_Opt->matFiksDani[2][2] = 1;
	m_Opt->matFiksDani[2][3] = 4;
	m_Opt->matFiksDani[2][4] = 14;
	m_Opt->matFiksDani[2][5] = 25;
	m_Opt->matFiksDani[2][6] = 2;
	m_Opt->matFiksDani[2][7] = 10;
	m_Opt->matFiksDani[2][8] = 21;
	m_Opt->matFiksDani[2][9] = 0;

	m_Opt->vecFiksIspiti[3] = 293;		// TMIL
	m_Opt->matFiksDani[3][0] = 4;
	m_Opt->matFiksDani[3][1] = 21;
	m_Opt->matFiksDani[3][2] = 0;
	m_Opt->matFiksDani[3][3] = 3;
	m_Opt->matFiksDani[3][4] = 22;
	m_Opt->matFiksDani[3][5] = 30;
	m_Opt->matFiksDani[3][6] = 4;
	m_Opt->matFiksDani[3][7] = 15;
	m_Opt->matFiksDani[3][8] = 23;
	m_Opt->matFiksDani[3][9] = 0;

	m_Opt->PostaviDatume(Date(12,6,2000), Date(13,7,2000));
	m_Opt->PostaviParametre(3, LJETNI);

	for( i=0; i<m_Opt->nBrojPred; i++ )
	{
		tmp = m_Opt->vecPopisPred[i];
/*
		if( tmp.m_chOpis != 'H' && tmp.m_chOpis != 'K' && tmp.m_nSifra > 15 
				&& tmp.m_nSifra != 346 && tmp.m_nSifra != 25 && tmp.m_nSifra != 306 && tmp.m_nSifra != 358
				&& ( ( tmp.m_nSemestar >=5 && tmp.m_nSemestar <= 6 ) || ( tmp.m_nSemestar>6 && (tmp.m_chOpis=='O' || tmp.m_nBrojStud>20) ) ) )
*/
		if( tmp.m_nSemestar == 1 || tmp.m_nSemestar == 2 || tmp.m_nSemestar == 3 || tmp.m_nSemestar == 4  )

//		if( ( tmp.m_nSemestar >=1 && tmp.m_nSemestar <= 4 ) )//  || 
//			( tmp.m_nSemestar >= 7 && tmp.m_nSemestar <=8 && ( tmp.m_chOpis == 'O' || ( tmp.m_chOpis == 'I' && tmp.m_nBrojStud > 20 ) ) ) )
//		if( /*tmp.m_nBrojStud > 20 &&*/ (tmp.m_chOpis == 'O' || tmp.m_chOpis == 'I' ) )
		{
			vecSif[num] = m_Opt->vecPopisPred[i];
			num++;
		}
	}

	m_nOptIspita = m_Opt->PostaviIspite(vecSif, num);
	m_Opt->PostaviPresjek();

	srand(time(NULL));

	m_Opt->Population.resize(m_Opt->GenPar.GetVelPop());

	for( i=0; i<m_Opt->GenPar.GetVelPop(); i++ )
		m_Opt->Population[i] = new Gen(m_Opt->ModPar.nBrIsp, m_Opt->ModPar.nBrRok);

	m_bOptimizationStarted = false;

	m_arrDatumiIspita.resize(m_Opt->ModPar.nBrIsp+1);

	m_nOptIspita = m_Opt->ModPar.nBrIsp;
	for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
	{
		m_arrDatumiIspita[i].m_arrDanJesIzv = 0;
		m_arrDatumiIspita[i].m_arrDanZim[0] = 0;
		m_arrDatumiIspita[i].m_arrDanZim[1] = 0;
		m_arrDatumiIspita[i].m_arrDanProlj = 0;
		m_arrDatumiIspita[i].m_arrDanLjet[0] = 0;
		m_arrDatumiIspita[i].m_arrDanLjet[1] = 0;
		m_arrDatumiIspita[i].m_arrDanLjet[2] = 0;
		m_arrDatumiIspita[i].m_arrDanJes[0] = 0;
		m_arrDatumiIspita[i].m_arrDanJes[1] = 0;
		m_arrDatumiIspita[i].m_arrDanJes[2] = 0;

		m_arrDatumiIspita[i].m_arrDatJesIzv = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatZim[0] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatZim[1] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatProlj = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatLjet[0] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatLjet[1] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatLjet[2] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatJes[0] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatJes[1] = Date(0,0,0);
		m_arrDatumiIspita[i].m_arrDatJes[2] = Date(0,0,0);
	}

	strcpy(NazivSmjera[1], "Temeljni dio studija");
	strcpy(NazivSmjera[2], "Elektroenergetika");
	strcpy(NazivSmjera[3], "Elektrostrojarstvo i automatizacija");
	strcpy(NazivSmjera[4], "Industrijska elektronika");
	strcpy(NazivSmjera[5], "Telekomunikacije i informatika");
	strcpy(NazivSmjera[6], "Automatika");
	strcpy(NazivSmjera[7], "Raèunarska tehnika");
	strcpy(NazivSmjera[8], "Radiokomunikacije i profesionalna elektronika");
	strcpy(NazivSmjera[9], "Energetske tehnologije");
	strcpy(NazivSmjera[10], "Nuklearna energetika");
	strcpy(NazivSmjera[14], "Izgradnja i pogon elektroenergetskih sustava");
	strcpy(NazivSmjera[15], "Upravljanje elektroenergetskim sistemom");
	strcpy(NazivSmjera[16], "Opæa energetika");
	strcpy(NazivSmjera[20], "Studij raèunarstva");
	strcpy(NazivSmjera[21], "Energetski sustavi");
	strcpy(NazivSmjera[22], "Energetske tehnologije");

	for( i=1; i<23; i++ )
		SifraSmjeraPostoji[i] = false;

	SifraSmjeraPostoji[1] = true;
	SifraSmjeraPostoji[2] = true;
	SifraSmjeraPostoji[3] = true;
	SifraSmjeraPostoji[4] = true;
	SifraSmjeraPostoji[5] = true;
	SifraSmjeraPostoji[6] = true;
	SifraSmjeraPostoji[7] = true;
	SifraSmjeraPostoji[8] = true;
	SifraSmjeraPostoji[9] = true;
	SifraSmjeraPostoji[10] = true;
	SifraSmjeraPostoji[14] = true;
	SifraSmjeraPostoji[15] = true;
	SifraSmjeraPostoji[16] = true;
	SifraSmjeraPostoji[20] = true;
	SifraSmjeraPostoji[21] = true;
	SifraSmjeraPostoji[22] = true;
}

COptRokDoc::~COptRokDoc()
{
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
	int			i, j, k, BrRok, BrIsp;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nOptIspita;
		
		for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
		{
			ar << m_arrDatumiIspita[i].m_nSifraIspita;

			for( j=0; j<2; j++ )
				Zapisi(ar , m_arrDatumiIspita[i].m_arrDatZim[j] );

			Zapisi(ar , m_arrDatumiIspita[i].m_arrDatProlj );
			
			for( j=0; j<3; j++ )
				Zapisi(ar , m_arrDatumiIspita[i].m_arrDatLjet[j] );
			
			for( j=0; j<3; j++ )
				Zapisi(ar , m_arrDatumiIspita[i].m_arrDatJes[j] );
			
			Zapisi(ar , m_arrDatumiIspita[i].m_arrDatJesIzv );

			if( m_arrDatumiIspita[i].m_arrDanZim[0] < 50 )
				ar << m_arrDatumiIspita[i].m_arrDanZim[0];
			else 
				ar << (int) 0;
			if( m_arrDatumiIspita[i].m_arrDanZim[1] < 50 )
				ar << m_arrDatumiIspita[i].m_arrDanZim[1];
			else
				ar << (int) 0;
			
			ar << m_arrDatumiIspita[i].m_arrDanProlj;

			ar << m_arrDatumiIspita[i].m_arrDanLjet[0];
			ar << m_arrDatumiIspita[i].m_arrDanLjet[1];
			ar << m_arrDatumiIspita[i].m_arrDanLjet[2];

			ar << m_arrDatumiIspita[i].m_arrDanJes[0];
			ar << m_arrDatumiIspita[i].m_arrDanJes[1];
			ar << m_arrDatumiIspita[i].m_arrDanJes[2];

			if( m_arrDatumiIspita[i].m_arrDanJesIzv < 50 )
				ar << m_arrDatumiIspita[i].m_arrDanJesIzv;
			else
				ar << (int) 0;
		}

		// najprije æemo zapisati duljinu kromosoma ( efektivno, broj ispita )
		ar << m_Opt->ModPar.nBrIsp;
		
		// zatim æemo zapisati broj rokova
		ar << m_Opt->ModPar.nBrRok;
		
		// a zatim æemo zapisati i sve kromosome
		for( i=0; i<m_Opt->GenPar.GetVelPop(); i++ )
		{
			for( j=0; j<m_Opt->Population[i]->Cromosom.size(); j++ )
			{
				ar << m_Opt->Population[i]->Cromosom[j];		// zapisujemo sam kromosom

				// zapisujemo temrine ispita koji su zapisani unutra
				for( k=0; k<m_Opt->ModPar.nBrRok; k++ )
					ar << m_Opt->Population[i]->TerminiIspita[j][k];
			}
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nOptIspita;

		m_arrDatumiIspita.resize(m_nOptIspita+1);

		for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
		{
			ar >> m_arrDatumiIspita[i].m_nSifraIspita;

			for( j=0; j<2; j++ )
				Ucitaj(ar , m_arrDatumiIspita[i].m_arrDatZim[j] );

			Ucitaj(ar , m_arrDatumiIspita[i].m_arrDatProlj );
			
			for( j=0; j<3; j++ )
				Ucitaj(ar , m_arrDatumiIspita[i].m_arrDatLjet[j] );
			
			for( j=0; j<3; j++ )
				Ucitaj(ar , m_arrDatumiIspita[i].m_arrDatJes[j] );
			
			Ucitaj(ar , m_arrDatumiIspita[i].m_arrDatJesIzv );

			ar >> m_arrDatumiIspita[i].m_arrDanZim[0];
			ar >> m_arrDatumiIspita[i].m_arrDanZim[1];

			ar >> m_arrDatumiIspita[i].m_arrDanProlj;

			ar >> m_arrDatumiIspita[i].m_arrDanLjet[0];
			ar >> m_arrDatumiIspita[i].m_arrDanLjet[1];
			ar >> m_arrDatumiIspita[i].m_arrDanLjet[2];

			ar >> m_arrDatumiIspita[i].m_arrDanJes[0];
			ar >> m_arrDatumiIspita[i].m_arrDanJes[1];
			ar >> m_arrDatumiIspita[i].m_arrDanJes[2];

			ar >> m_arrDatumiIspita[i].m_arrDanJesIzv;

/*
			if( m_arrDatumiIspita[i].m_nSifraIspita == 441 )	// DISKRETNA
			{
				m_arrDatumiIspita[i].m_arrDanZim[0] = 0;
				m_arrDatumiIspita[i].m_arrDanZim[1] = 18;

				m_arrDatumiIspita[i].m_arrDanProlj = 1;

				m_arrDatumiIspita[i].m_arrDanLjet[0] = 4;
				m_arrDatumiIspita[i].m_arrDanLjet[1] = 18;
				m_arrDatumiIspita[i].m_arrDanLjet[2] = 29;

				m_arrDatumiIspita[i].m_arrDanJes[0] = 3;
				m_arrDatumiIspita[i].m_arrDanJes[1] = 11;
				m_arrDatumiIspita[i].m_arrDanJes[2] = 23;

				m_arrDatumiIspita[i].m_arrDanJesIzv = 0;
			}
			else if( m_arrDatumiIspita[i].m_nSifraIspita == 429 ) // NUMAT
			{
				m_arrDatumiIspita[i].m_arrDanZim[0] = 0;
				m_arrDatumiIspita[i].m_arrDanZim[1] = 18;

				m_arrDatumiIspita[i].m_arrDanProlj = 1;

				m_arrDatumiIspita[i].m_arrDanLjet[0] = 4;
				m_arrDatumiIspita[i].m_arrDanLjet[1] = 18;
				m_arrDatumiIspita[i].m_arrDanLjet[2] = 29;

				m_arrDatumiIspita[i].m_arrDanJes[0] = 3;
				m_arrDatumiIspita[i].m_arrDanJes[1] = 11;
				m_arrDatumiIspita[i].m_arrDanJes[2] = 23;

				m_arrDatumiIspita[i].m_arrDanJesIzv = 0;
			}
			else if( m_arrDatumiIspita[i].m_nSifraIspita == 439 )		// STOMAT
			{
				m_arrDatumiIspita[i].m_arrDanZim[0] = 11;
				m_arrDatumiIspita[i].m_arrDanZim[1] = 22;

				m_arrDatumiIspita[i].m_arrDanProlj = 2;

				m_arrDatumiIspita[i].m_arrDanLjet[0] = 4;
				m_arrDatumiIspita[i].m_arrDanLjet[1] = 14;
				m_arrDatumiIspita[i].m_arrDanLjet[2] = 25;

				m_arrDatumiIspita[i].m_arrDanJes[0] = 2;
				m_arrDatumiIspita[i].m_arrDanJes[1] = 10;
				m_arrDatumiIspita[i].m_arrDanJes[2] = 21;

				m_arrDatumiIspita[i].m_arrDanJesIzv = 0;
			}
			else if( m_arrDatumiIspita[i].m_nSifraIspita == 293 )		// TMIL
			{
				m_arrDatumiIspita[i].m_arrDanZim[0] = 4;
				m_arrDatumiIspita[i].m_arrDanZim[1] = 21;

				m_arrDatumiIspita[i].m_arrDanProlj = 0;

				m_arrDatumiIspita[i].m_arrDanLjet[0] = 3;
				m_arrDatumiIspita[i].m_arrDanLjet[1] = 22;
				m_arrDatumiIspita[i].m_arrDanLjet[2] = 30;

				m_arrDatumiIspita[i].m_arrDanJes[0] = 4;
				m_arrDatumiIspita[i].m_arrDanJes[1] = 15;
				m_arrDatumiIspita[i].m_arrDanJes[2] = 23;

				m_arrDatumiIspita[i].m_arrDanJesIzv = 0;
			}
*/
		}
		ar >> BrIsp;
		ar >> BrRok;
		
		for( i=0; i<m_Opt->GenPar.GetVelPop(); i++ )
		{
			for( j=0; j<BrIsp; j++ )
			{
				ar >> m_Opt->Population[i]->Cromosom[j];

				for( k=0; k<BrRok; k++ )
					ar >> m_Opt->Population[i]->TerminiIspita[j][k];
			}
		}
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

void COptRokDoc::OnPostaviParametreOptimizacije() 
{
	CDlgParamOptimizacije		dlg;
	
	dlg.m_nVelPop = m_Opt->GenPar.GetVelPop();
	dlg.m_IterNum = m_Opt->GenPar.GetIterNum();
	dlg.m_nMutacija = m_Opt->GenPar.GetMutModul();
	
	dlg.m_dExpUdalj				= m_Opt->FuncPar.GetExponent();
	dlg.m_dKaznaPodrokovi	= m_Opt->FuncPar.GetKaznaPodjeleNaPodrokove();
	dlg.m_dNagradaIstiDan = m_Opt->FuncPar.GetNagradaIstiDan();
	dlg.m_nMinDist				= m_Opt->FuncPar.GetMinDistance();
	dlg.m_nMinPresjek			= m_Opt->FuncPar.GetMinPresjek();
	dlg.m_dKaznaMinDist		= m_Opt->FuncPar.GetKaznaMinDist();
	dlg.m_dAmpBlizine			= m_Opt->FuncPar.GetAmpBlizineIspita();
	dlg.m_dAmpPresjeka		= m_Opt->FuncPar.GetAmpPresjekaStud();

	dlg.m_nMaxOpterecNaGrupiPred	= m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred();
	dlg.m_dKaznaGrupaPred					= m_Opt->FuncPar.GetKaznaZaMaxBrojStudZaGrupuPred();

	int	ret = dlg.DoModal();
	if( ret == IDOK )
	{

		m_Opt->GenPar.PostaviParametre(dlg.m_nVelPop, dlg.m_IterNum, dlg.m_nMutacija);
		
		int stari_presj = m_Opt->FuncPar.GetMinPresjek();
		m_Opt->FuncPar.PostaviParametre(dlg.m_dExpUdalj,dlg.m_dKaznaPodrokovi,
																		dlg.m_dNagradaIstiDan,dlg.m_dKaznaGrupaPred, dlg.m_dKaznaMinDist,
																		dlg.m_dAmpBlizine, dlg.m_dAmpPresjeka,
																		dlg.m_nMinDist, dlg.m_nMinPresjek, dlg.m_nMaxOpterecNaGrupiPred, dlg.m_nMaxIspita, dlg.m_dKaznaMaxIspita  );

		if( stari_presj != m_Opt->FuncPar.GetMinPresjek() )
			m_Opt->PostaviPresjek();
	}
}

void COptRokDoc::OnPostaviParametreRoka() 
{
	int			ret;
	CDlgParametriRoka		dlg;

	ret = dlg.DoModal();

	if( ret == IDOK )
	{
		m_Opt->PostaviParametre(dlg.m_nBrojRokova,dlg.Vrsta);
		m_Opt->PostaviDatume(dlg.dateStart, dlg.dateEnd);
	}
}

void COptRokDoc::OnOptimizacijaPokreni() 
{
	int			max;
	CDlgOptim			*pDlg;

	if( m_bOptimizationStarted == false )
	{
		pDlg = new CDlgOptim();

		pDlg->bCalcInProgress = true;
		pDlg->timeStarted = time(NULL);

		max = m_Opt->ModPar.nBrIsp - MAX_ISP_NA_EKRANU;
		if( max < 0 )
		{
			max = 0;
		}
		pDlg->m_ctrlVScroll.SetMax(max);

		char		str[100];
		sprintf(str, "Optimizira se raspored za %d ispita", m_Opt->ModPar.nBrIsp );
		AfxMessageBox(str);

		m_bOptimizationStarted = true;
		AfxBeginThread(DoSomething, pDlg);
	}
}

void COptRokDoc::OnRezultatiPregledPoIspitima() 
{
	CDlgPopisIspita		*pDlg;
	int				sif, k, i;
	string		str;
	char			isp[200];
	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski", "3.jesenski", 
		"sem.", "br.st.", "grupa", "smjer", "opis"};

	pDlg = new CDlgPopisIspita();

	pDlg->m_ctrlGrid.SetRows(m_Opt->ModPar.nBrIsp+1);
	pDlg->m_ctrlGrid.SetCols(16);
	pDlg->m_ctrlGrid.SetColWidth(0,500);
	pDlg->m_ctrlGrid.SetColWidth(1,3800);
	pDlg->m_ctrlGrid.SetColAlignment(0,1);
	pDlg->m_ctrlGrid.SetColAlignment(1,1);

	pDlg->m_ctrlGrid.SetRow(0);

	pDlg->m_ctrlGrid.SetCol(0);
	pDlg->m_ctrlGrid.SetText(naslovi[0]);
	
	pDlg->m_ctrlGrid.SetCol(1);
	pDlg->m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<12; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetColWidth(k,800);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=12; k<17; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
		pDlg->m_ctrlGrid.SetColWidth(k,500);
	}
	
	for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
	{
		pDlg->m_ctrlGrid.SetRow(i+1);

		sif = m_arrDatumiIspita[i].m_nSifraIspita;
		sprintf(isp, "%d", sif);
		pDlg->m_ctrlGrid.SetCol(0);
		pDlg->m_ctrlGrid.SetText(isp);
		
		str = m_Opt->vecNaziviPred[sif];
		sprintf(isp, "%s", str.c_str() );
		pDlg->m_ctrlGrid.SetCol(1);
		pDlg->m_ctrlGrid.SetText(isp);
/*
		for( k=0; k<m_Opt->ModPar.nBrRok; k++ )
		{
			pDlg->m_ctrlGrid.SetCol(k+2);

			sprintf(isp, "%2d", m_Opt->Population[m_nBestCromosomInd]->TerminiIspita[i][k]);
			pDlg->m_ctrlGrid.SetText(isp);
		}
*/
		if( pDlg->m_bPrikazDani == true )
		{
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJesIzv );
			pDlg->m_ctrlGrid.SetCol(2);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[0] );
			pDlg->m_ctrlGrid.SetCol(3);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[1] );
			pDlg->m_ctrlGrid.SetCol(4);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanProlj );
			pDlg->m_ctrlGrid.SetCol(5);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[0] );
			pDlg->m_ctrlGrid.SetCol(6);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[1] );
			pDlg->m_ctrlGrid.SetCol(7);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[2] );
			pDlg->m_ctrlGrid.SetCol(8);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[0] );
			pDlg->m_ctrlGrid.SetCol(9);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[1] );
			pDlg->m_ctrlGrid.SetCol(10);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[2] );
			pDlg->m_ctrlGrid.SetCol(11);
			pDlg->m_ctrlGrid.SetText(isp);
		}
		else
		{
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatJesIzv.dan, m_arrDatumiIspita[i].m_arrDatJesIzv.mj );
			pDlg->m_ctrlGrid.SetCol(2);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatZim[0].dan, m_arrDatumiIspita[i].m_arrDatZim[0].mj );
			pDlg->m_ctrlGrid.SetCol(3);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatZim[1].dan, m_arrDatumiIspita[i].m_arrDatZim[1].mj );
			pDlg->m_ctrlGrid.SetCol(4);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatProlj.dan, m_arrDatumiIspita[i].m_arrDatProlj.mj );
			pDlg->m_ctrlGrid.SetCol(5);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatLjet[0].dan, m_arrDatumiIspita[i].m_arrDatLjet[0].mj );
			pDlg->m_ctrlGrid.SetCol(6);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatLjet[1].dan, m_arrDatumiIspita[i].m_arrDatLjet[1].mj );
			pDlg->m_ctrlGrid.SetCol(7);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatLjet[2].dan, m_arrDatumiIspita[i].m_arrDatLjet[2].mj );
			pDlg->m_ctrlGrid.SetCol(8);
			pDlg->m_ctrlGrid.SetText(isp);

			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatJes[0].dan, m_arrDatumiIspita[i].m_arrDatJes[0].mj );
			pDlg->m_ctrlGrid.SetCol(9);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatJes[1].dan, m_arrDatumiIspita[i].m_arrDatJes[1].mj );
			pDlg->m_ctrlGrid.SetCol(10);
			pDlg->m_ctrlGrid.SetText(isp);
			sprintf(isp, "%d.%d", m_arrDatumiIspita[i].m_arrDatJes[2].dan, m_arrDatumiIspita[i].m_arrDatJes[2].mj );
			pDlg->m_ctrlGrid.SetCol(11);
			pDlg->m_ctrlGrid.SetText(isp);
		}

		sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar );
		pDlg->m_ctrlGrid.SetCol(12);
		pDlg->m_ctrlGrid.SetText(isp);
		sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nBrojStud );
		pDlg->m_ctrlGrid.SetCol(13);
		pDlg->m_ctrlGrid.SetText(isp);
		sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred );
		pDlg->m_ctrlGrid.SetCol(14);
		pDlg->m_ctrlGrid.SetText(isp);
		sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSifraSmjera );
		pDlg->m_ctrlGrid.SetCol(15);
		pDlg->m_ctrlGrid.SetText(isp);
		sprintf(isp, "%c", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_chOpis );
		pDlg->m_ctrlGrid.SetCol(16);
		pDlg->m_ctrlGrid.SetText(isp);

	}
}

void COptRokDoc::OnRezultatiPregledPoGrupamaPredmeta() 
{
	CDlgPopisIspita		*pDlg;
	int				sif, k, i, RowNum, dan;
	string		str;
	char			isp[200];
	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski",
		"sem.", "br.st.", "grupa", "smjer", "opis", "isti"};

	pDlg = new CDlgPopisIspita();

	pDlg->m_ctrlGrid.SetRows(m_Opt->ModPar.nBrIsp+1);
	pDlg->m_ctrlGrid.SetCols(17);
	pDlg->m_ctrlGrid.SetColWidth(0,500);
	pDlg->m_ctrlGrid.SetColWidth(1,3800);
	pDlg->m_ctrlGrid.SetColAlignment(0,1);
	pDlg->m_ctrlGrid.SetColAlignment(1,1);

	pDlg->m_ctrlGrid.SetRow(0);

	pDlg->m_ctrlGrid.SetCol(0);
	pDlg->m_ctrlGrid.SetText(naslovi[0]);
	
	pDlg->m_ctrlGrid.SetCol(1);
	pDlg->m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<11; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetColWidth(k,800);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=11; k<17; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
		pDlg->m_ctrlGrid.SetColWidth(k,500);
	}
	
	RowNum = 1;

	vector< vector< ParBrStudBrIsp > >		matSumaPoGrupPred[5];		// za svaki rok æemo imati posebnu matricu

	int		j, grupa, ind, BrojKazniOpterecenjaGrupe=0;
	bool	GrupaPostoji[MAX_GRUPA];

	for( i=0; i<MAX_GRUPA; i++ )
		GrupaPostoji[i] = false;

	for( int rok=0; rok<5; rok++ )
	{
		matSumaPoGrupPred[rok].resize( m_Opt->ModPar.matSumaPoGrupPred.size() );
		for( i=0; i<m_Opt->ModPar.matSumaPoGrupPred.size(); i++ )
		{
			matSumaPoGrupPred[rok][i].resize( m_Opt->ModPar.matSumaPoGrupPred[i].size() );
			for( j=0; j<m_Opt->ModPar.matSumaPoGrupPred[i].size(); j++ )
			{
				matSumaPoGrupPred[rok][i][j].m_nBrIsp = 0;
				matSumaPoGrupPred[rok][i][j].m_nBrStud = 0;
			}
		}
	}

	for( rok=0; rok<5; rok++ )
		for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;
			ind = m_Opt->IndexPredSaSifrom(sif);
			grupa = m_Opt->vecPopisPred[ind].m_nGrupaPred;
			GrupaPostoji[grupa] = true;

			for( k=0; k<BrojRokova((TerminRoka) rok); k++ )
			{
				matSumaPoGrupPred[(TerminRoka) rok][grupa][DanIspita(this,i,k,(TerminRoka) rok)].m_nBrStud += m_Opt->vecPopisPred[ind].m_nBrojStud;
				matSumaPoGrupPred[(TerminRoka) rok][grupa][DanIspita(this,i,k,(TerminRoka) rok)].m_nBrIsp++;
			}
		}

	for( j=1; j<MAX_GRUPA;j++ )
	{
//		if( GrupaPostoji[i] )
			for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
			{
				sif = m_arrDatumiIspita[i].m_nSifraIspita;
				if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred == j )
				{
					pDlg->m_ctrlGrid.SetRow(RowNum++);
		
					sprintf(isp, "%d", sif);
					pDlg->m_ctrlGrid.SetCol(0);
					pDlg->m_ctrlGrid.SetText(isp);
					
					str = m_Opt->vecNaziviPred[sif];
					sprintf(isp, "%s", str.c_str() );
					pDlg->m_ctrlGrid.SetCol(1);
					pDlg->m_ctrlGrid.SetText(isp);

					//*****************************************************************************
					// JESENSKI IZVANREDNI
					dan = m_arrDatumiIspita[i].m_arrDanJesIzv;
					if( matSumaPoGrupPred[JESENSKI_IZV][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[JESENSKI_IZV][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(2);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJesIzv );
						pDlg->m_ctrlGrid.SetCol(2);
						pDlg->m_ctrlGrid.SetText(isp);
					}

					//*****************************************************************************
					// ZIMSKI rok
					dan = m_arrDatumiIspita[i].m_arrDanZim[0];
					if( matSumaPoGrupPred[ZIMSKI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[ZIMSKI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(3);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[0] );
						pDlg->m_ctrlGrid.SetCol(3);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					
					dan = m_arrDatumiIspita[i].m_arrDanZim[1];
					if( matSumaPoGrupPred[ZIMSKI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[ZIMSKI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(4);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[1] );
						pDlg->m_ctrlGrid.SetCol(4);
						pDlg->m_ctrlGrid.SetText(isp);
					}


					//*****************************************************************************
					// PROLJETNI rok
					dan = m_arrDatumiIspita[i].m_arrDanProlj;
					if( matSumaPoGrupPred[PROLJETNI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[PROLJETNI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(5);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanProlj );
						pDlg->m_ctrlGrid.SetCol(5);
						pDlg->m_ctrlGrid.SetText(isp);
					}


					//*****************************************************************************
					// LJETNI rok
					dan = m_arrDatumiIspita[i].m_arrDanLjet[0];
					if( matSumaPoGrupPred[LJETNI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[LJETNI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(6);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[0] );
						pDlg->m_ctrlGrid.SetCol(6);
						pDlg->m_ctrlGrid.SetText(isp);
					}

					dan = m_arrDatumiIspita[i].m_arrDanLjet[1];
					if( matSumaPoGrupPred[LJETNI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[LJETNI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(7);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[1] );
						pDlg->m_ctrlGrid.SetCol(7);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					
					dan = m_arrDatumiIspita[i].m_arrDanLjet[2];
					if( matSumaPoGrupPred[LJETNI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[LJETNI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(8);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[2] );
						pDlg->m_ctrlGrid.SetCol(8);
						pDlg->m_ctrlGrid.SetText(isp);
					}

					//*****************************************************************************
					// JESENSKI rok
					dan = m_arrDatumiIspita[i].m_arrDanJes[0];
					if( matSumaPoGrupPred[JESENSKI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[JESENSKI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(9);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[0] );
						pDlg->m_ctrlGrid.SetCol(9);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					
					dan = m_arrDatumiIspita[i].m_arrDanJes[1];
					if( matSumaPoGrupPred[JESENSKI][j][dan].m_nBrStud > m_Opt->FuncPar.GetMaxBrojStudZaGrupuPred() &&
							matSumaPoGrupPred[JESENSKI][j][dan].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
					{
						sprintf(isp, "%d", dan );
						pDlg->m_ctrlGrid.SetCol(10);
						pDlg->m_ctrlGrid.SetCellFontBold(true);
						pDlg->m_ctrlGrid.SetText(isp);
					}
					else
					{
						sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[1] );
						pDlg->m_ctrlGrid.SetCol(10);
						pDlg->m_ctrlGrid.SetText(isp);
					}

					sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar );
					pDlg->m_ctrlGrid.SetCol(11);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nBrojStud );
					pDlg->m_ctrlGrid.SetCol(12);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred );
					pDlg->m_ctrlGrid.SetCol(13);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSifraSmjera );
					pDlg->m_ctrlGrid.SetCol(14);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%c", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_chOpis );
					pDlg->m_ctrlGrid.SetCol(15);
					pDlg->m_ctrlGrid.SetText(isp);


					for( k=0; k<m_Opt->matIspitiIstiDan.size(); k++ )
					{
						for( int l=0; l<m_Opt->matIspitiIstiDan[k].size(); l++ )
						{
							if( sif == m_Opt->matIspitiIstiDan[k][l] ) 
							{
								sprintf(isp, "X" );
								pDlg->m_ctrlGrid.SetCol(16);
								pDlg->m_ctrlGrid.SetText(isp);
								}
						}
					}
				}
			}
		}
}

void COptRokDoc::OnRezultatiPregledPoSemestrima() 
{
	CDlgPopisIspita		*pDlg;
	int				sif, k, i, RowNum, ind;
	string		str;
	char			isp[200];
	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski", "3.jesenski",
		"sem.", "br.st.", "grupa", "smjer", "opis"};

	pDlg = new CDlgPopisIspita();

	pDlg->m_ctrlGrid.SetRows(m_Opt->ModPar.nBrIsp+1);
	pDlg->m_ctrlGrid.SetCols(17);
	pDlg->m_ctrlGrid.SetColWidth(0,500);
	pDlg->m_ctrlGrid.SetColWidth(1,3800);
	pDlg->m_ctrlGrid.SetColAlignment(0,1);
	pDlg->m_ctrlGrid.SetColAlignment(1,1);

	pDlg->m_ctrlGrid.SetRow(0);

	pDlg->m_ctrlGrid.SetCol(0);
	pDlg->m_ctrlGrid.SetText(naslovi[0]);
	
	pDlg->m_ctrlGrid.SetCol(1);
	pDlg->m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<12; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetColWidth(k,800);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=12; k<16; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
		pDlg->m_ctrlGrid.SetColWidth(k,500);
	}
	
	RowNum = 1;
	for( int j=1; j<=9;j++ )
	{
		for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;
			ind = m_Opt->ModPar.vecSifraUIndex[sif];

			bool	exist = false;
			for( int k=0; k<m_Opt->ModPar.vecOptIsp[ind].vecDodPod.size(); k++ )
				if( m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar == j )
				{
					exist = true;
					break;
				}
			
			if( exist == true )
//			if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar == j )
			{
				pDlg->m_ctrlGrid.SetRow(RowNum++);
	
				sprintf(isp, "%d", sif);
				pDlg->m_ctrlGrid.SetCol(0);
				pDlg->m_ctrlGrid.SetText(isp);
				
				str = m_Opt->vecNaziviPred[sif];
				sprintf(isp, "%s", str.c_str() );
				pDlg->m_ctrlGrid.SetCol(1);
				pDlg->m_ctrlGrid.SetText(isp);
		/*
				for( k=0; k<m_Opt->ModPar.nBrRok; k++ )
				{
					pDlg->m_ctrlGrid.SetCol(k+2);

					sprintf(isp, "%2d", m_Opt->Population[m_nBestCromosomInd]->TerminiIspita[i][k]);
					pDlg->m_ctrlGrid.SetText(isp);
				}
		*/
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJesIzv );
				pDlg->m_ctrlGrid.SetCol(2);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[0] );
				pDlg->m_ctrlGrid.SetCol(3);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[1] );
				pDlg->m_ctrlGrid.SetCol(4);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanProlj );
				pDlg->m_ctrlGrid.SetCol(5);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[0] );
				pDlg->m_ctrlGrid.SetCol(6);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[1] );
				pDlg->m_ctrlGrid.SetCol(7);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[2] );
				pDlg->m_ctrlGrid.SetCol(8);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[0] );
				pDlg->m_ctrlGrid.SetCol(9);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[1] );
				pDlg->m_ctrlGrid.SetCol(10);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[2] );
				pDlg->m_ctrlGrid.SetCol(11);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar  );
				pDlg->m_ctrlGrid.SetCol(12);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].BrojStud );
				pDlg->m_ctrlGrid.SetCol(13);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Grupa );
				pDlg->m_ctrlGrid.SetCol(14);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer );
				pDlg->m_ctrlGrid.SetCol(15);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%c", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Opis );
				pDlg->m_ctrlGrid.SetCol(16);
				pDlg->m_ctrlGrid.SetText(isp);

/*				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar );
				pDlg->m_ctrlGrid.SetCol(12);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nBrojStud );
				pDlg->m_ctrlGrid.SetCol(13);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred );
				pDlg->m_ctrlGrid.SetCol(14);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSifraSmjera );
				pDlg->m_ctrlGrid.SetCol(15);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%c", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_chOpis );
				pDlg->m_ctrlGrid.SetCol(16);
				pDlg->m_ctrlGrid.SetText(isp);
*/
			}
		}
	}
}

void COptRokDoc::OnRezultatiVizualniPrikaz() 
{
	int									max;
	CDlgVizualniPrikaz	*pDlg;

	pDlg = new CDlgVizualniPrikaz();

	max = m_Opt->ModPar.nBrIsp - MAX_ISP_NA_EKRANU;
	if( max < 0 )
	{
		max = 0;
	}
	pDlg->m_ctrlVScroll.SetMax(max);
	pDlg->PrintConfig();
}

void Zapisi( CArchive &ar, Date dat )
{
	ar << dat.dan << dat.mj << dat.god;
}

void Ucitaj( CArchive &ar, Date &dat )
{
	ar >> dat.dan >> dat.mj >> dat.god;
}

void COptRokDoc::OnWriteAscii() 
{
	int			i, j, sif, dan;
	char		naziv[100];
	Date		dat;
	FILE		*fp;
	
	if( (fp = fopen("ASCII.txt", "w") ) == NULL )
		AfxMessageBox("Nisam uspio otvoriti datoteku ASCII.txt");


	// najprije æemo ih zapisati po semestrima
	for( j=1; j<=9; j++ )
	{
		fprintf(fp, "\n\nPredmeti iz %d. semestra \n", j );
		for( i=0; i<m_nOptIspita; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;
			if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar == j )
			{
				sprintf(naziv, "%-35s", m_Opt->vecNaziviPred[sif].c_str() );
				naziv[35] = 0;
				fprintf(fp, "\n%3d, %25s \t", sif, naziv );

//				dan = m_arrDatumiIspita[i].m_arrDanJesIzv;
//				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanZim[0];
				fprintf(fp, "%2d.  ", dan);
				dan = m_arrDatumiIspita[i].m_arrDanZim[1];
				fprintf(fp, "%2d.     ", dan);

				dan = m_arrDatumiIspita[i].m_arrDanProlj;
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanLjet[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[2];
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanJes[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[2];
				fprintf(fp, "%2d.  ", dan );
			}
		}
	}
	for( j=1; j<MAX_GRUPA;j++ )
	{
		fprintf(fp, "\n\n Grupa predmeta broj   %d\n", j);
		for( i=0; i<m_nOptIspita; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;
			if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred == j )
			{
				sprintf(naziv, "%-35s", m_Opt->vecNaziviPred[sif].c_str() );
				naziv[35] = 0;
				fprintf(fp, "\n%3d, %25s \t", sif, naziv );

//				dan = m_arrDatumiIspita[i].m_arrDanJesIzv;
//				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanZim[0];
				fprintf(fp, "%2d.  ", dan);
				dan = m_arrDatumiIspita[i].m_arrDanZim[1];
				fprintf(fp, "%2d.     ", dan);

				dan = m_arrDatumiIspita[i].m_arrDanProlj;
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanLjet[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[2];
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanJes[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[2];
				fprintf(fp, "%2d.  ", dan );
			}
		}
	}
	for( j=1; j<30;j++ )
	{
		fprintf(fp, "\n\n Smjer  %d\n", j);
		for( i=0; i<m_nOptIspita; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;
			if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSifraSmjera == j )
			{
				sprintf(naziv, "%-35s", m_Opt->vecNaziviPred[sif].c_str() );
				naziv[35] = 0;
				fprintf(fp, "\n%3d, %25s \t", sif, naziv );

//				dan = m_arrDatumiIspita[i].m_arrDanJesIzv;
//				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanZim[0];
				fprintf(fp, "%2d.  ", dan);
				dan = m_arrDatumiIspita[i].m_arrDanZim[1];
				fprintf(fp, "%2d.     ", dan);

				dan = m_arrDatumiIspita[i].m_arrDanProlj;
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanLjet[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[2];
				fprintf(fp, "%2d.     ", dan );

				dan = m_arrDatumiIspita[i].m_arrDanJes[0];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[1];
				fprintf(fp, "%2d.  ", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[2];
				fprintf(fp, "%2d.  ", dan );
			}
		}
	}
/*
	for( i=0; i<m_nOptIspita; i++ )
	{
		sif = m_arrDatumiIspita[i].m_nSifraIspita;
		fprintf(fp, "\n%3d, %s \n", sif, m_Opt->vecNaziviPred[sif].c_str() );

		dat = m_arrDatumiIspita[i].m_arrDatJesIzv;
		fprintf(fp, "%2d.%d.     ", dat.dan, dat.mj );

		dat = m_arrDatumiIspita[i].m_arrDatZim[0];
		fprintf(fp, "%2d.%d.  ", dat.dan, dat.mj );
		dat = m_arrDatumiIspita[i].m_arrDatZim[1];
		fprintf(fp, "%2d.%d.     ", dat.dan, dat.mj );

		dat = m_arrDatumiIspita[i].m_arrDatProlj;
		fprintf(fp, "%2d.%d.     ", dat.dan, dat.mj );

		dat = m_arrDatumiIspita[i].m_arrDatLjet[0];
		fprintf(fp, "%2d.%d.  ", dat.dan, dat.mj );
		dat = m_arrDatumiIspita[i].m_arrDatLjet[1];
		fprintf(fp, "%2d.%d.  ", dat.dan, dat.mj );
		dat = m_arrDatumiIspita[i].m_arrDatLjet[2];
		fprintf(fp, "%2d.%d.     ", dat.dan, dat.mj );

		dat = m_arrDatumiIspita[i].m_arrDatJes[0];
		fprintf(fp, "%2d.%d.  ", dat.dan, dat.mj );
		dat = m_arrDatumiIspita[i].m_arrDatJes[1];
		fprintf(fp, "%2d.%d.  ", dat.dan, dat.mj );
		dat = m_arrDatumiIspita[i].m_arrDatJes[2];
		fprintf(fp, "%2d.%d.\n", dat.dan, dat.mj  );
	}
*/
}


void COptRokDoc::OnPregledIspitiIstiDan() 
{
	// TODO: Add your command handler code here
	int			i, j, sif, ind;
	char		str[200];
	bool		fleg;
	CDlgIspitiIstiDan		*pDlg;
	
	pDlg = new CDlgIspitiIstiDan();

	for( i=0; i<m_Opt->ModPar.matIspitiIstiDan.size(); i++ )
	{
		fleg = false;
		for( j=0; j<m_Opt->ModPar.matIspitiIstiDan[i].size(); j++ )
		{
			sif = m_Opt->ModPar.matIspitiIstiDan[i][j];
			ind = m_Opt->IndexPredSaSifrom(sif);
			sprintf(str, " %3d - %s   \t %d  \t %d   ;    ", sif, m_Opt->vecNaziviPred[sif].c_str(), m_Opt->vecPopisPred[ind].m_nSemestar, m_Opt->vecPopisPred[ind].m_nGrupaPred );
			
			pDlg->m_ctrlList.AddString(str);
			fleg = true;
		}
		if( fleg == true )
			pDlg->m_ctrlList.AddString("-----------------------------------------------------------------------");
	}
}

void COptRokDoc::OnPregledIspunjavanjeZeljaProf() 
{
	// TODO: Add your command handler code here
	CDlgPregledZelja		*pDlg;
	int				sif, k, i, RowNum;
	string		str;
	char			isp[200];
	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski", "3.jesenski",
		"sem.", "br.st.", "grupa", "smjer", "opis"};

	pDlg = new CDlgPregledZelja();

	pDlg->m_ctrlGrid.SetRows(m_Opt->ModPar.nBrIsp+1);
	pDlg->m_ctrlGrid.SetCols(16);
	pDlg->m_ctrlGrid.SetColWidth(0,500);
	pDlg->m_ctrlGrid.SetColWidth(1,3800);
	pDlg->m_ctrlGrid.SetColAlignment(0,1);
	pDlg->m_ctrlGrid.SetColAlignment(1,1);

	pDlg->m_ctrlGrid.SetRow(0);

	pDlg->m_ctrlGrid.SetCol(0);
	pDlg->m_ctrlGrid.SetText(naslovi[0]);
	
	pDlg->m_ctrlGrid.SetCol(1);
	pDlg->m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<12; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetColWidth(k,800);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=12; k<17; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
		pDlg->m_ctrlGrid.SetColWidth(k,500);
	}
	
	RowNum = 1;
	for( i=0; i<=m_Opt->ModPar.matIspitiIstiDan.size(); i++ )
	{
		for( int j=0; j<m_Opt->ModPar.matIspitiIstiDan[i].size(); j++ )
		{
			int			ind = -1;

			sif = m_Opt->ModPar.matIspitiIstiDan[i][j];
			
			for( int l=0; l<m_nOptIspita; l++ )
				if( m_arrDatumiIspita[l].m_nSifraIspita == sif )
				{
					ind = l;
					break;
				}

			if( ind != -1 )
			{
				pDlg->m_ctrlGrid.SetRow(RowNum++);
	
				sprintf(isp, "%d", sif);
				pDlg->m_ctrlGrid.SetCol(0);
				pDlg->m_ctrlGrid.SetText(isp);
				
				str = m_Opt->vecNaziviPred[sif];
				sprintf(isp, "%d. %s", i, str.c_str() );
				pDlg->m_ctrlGrid.SetCol(1);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanJesIzv );
				pDlg->m_ctrlGrid.SetCol(2);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanZim[0] );
				pDlg->m_ctrlGrid.SetCol(3);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanZim[1] );
				pDlg->m_ctrlGrid.SetCol(4);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanProlj );
				pDlg->m_ctrlGrid.SetCol(5);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanLjet[0] );
				pDlg->m_ctrlGrid.SetCol(6);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanLjet[1] );
				pDlg->m_ctrlGrid.SetCol(7);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanLjet[2] );
				pDlg->m_ctrlGrid.SetCol(8);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanJes[0] );
				pDlg->m_ctrlGrid.SetCol(9);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanJes[1] );
				pDlg->m_ctrlGrid.SetCol(10);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_arrDatumiIspita[ind].m_arrDanJes[2] );
				pDlg->m_ctrlGrid.SetCol(11);
				pDlg->m_ctrlGrid.SetText(isp);

				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar );
				pDlg->m_ctrlGrid.SetCol(12);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nBrojStud );
				pDlg->m_ctrlGrid.SetCol(13);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nGrupaPred );
				pDlg->m_ctrlGrid.SetCol(14);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%d", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSifraSmjera );
				pDlg->m_ctrlGrid.SetCol(15);
				pDlg->m_ctrlGrid.SetText(isp);
				sprintf(isp, "%c", m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_chOpis );
				pDlg->m_ctrlGrid.SetCol(16);
				pDlg->m_ctrlGrid.SetText(isp);
			}
		}
	}	
}

int	 COptRokDoc::DanIspita( COptRokDoc	*pDoc, int BrIsp, int BrRoka, TerminRoka	Vrsta )
{
	switch( Vrsta )
	{
		case JESENSKI_IZV :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanJesIzv;
			break;
		case ZIMSKI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanZim[BrRoka];
		case PROLJETNI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanProlj;
		case LJETNI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanLjet[BrRoka];
		case JESENSKI :
			return pDoc->m_arrDatumiIspita[BrIsp].m_arrDanJes[BrRoka];
	}
	return -1;
}

void COptRokDoc::OnFileExport() 
{
	// TODO: Add your command handler code here
	int			i, j, sif, dan;
	Date		dat;
	FILE		*fp;
	
	if( (fp = fopen("Export.txt", "w") ) == NULL )
		AfxMessageBox("Nisam uspio otvoriti datoteku Export.txt");


	// najprije æemo ih zapisati po semestrima
	for( j=1; j<=9; j++ )
	{
		for( i=0; i<m_nOptIspita; i++ )
		{
			sif = m_arrDatumiIspita[i].m_nSifraIspita;

			if( m_Opt->vecPopisPred[m_Opt->IndexPredSaSifrom(sif)].m_nSemestar == j )
			{
				fprintf(fp, "%d;", sif );

				dan = m_arrDatumiIspita[i].m_arrDanZim[0] + 1;
				fprintf(fp, "%2d;", dan);
				dan = m_arrDatumiIspita[i].m_arrDanZim[1] + 1;
				fprintf(fp, "%2d;", dan);

				dan = m_arrDatumiIspita[i].m_arrDanProlj + 1;
				fprintf(fp, "%2d;", dan );

				dan = m_arrDatumiIspita[i].m_arrDanLjet[0] + 1;
				fprintf(fp, "%2d;", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[1] + 1;
				fprintf(fp, "%2d;", dan );
				dan = m_arrDatumiIspita[i].m_arrDanLjet[2] + 1;
				fprintf(fp, "%2d;", dan );

				dan = m_arrDatumiIspita[i].m_arrDanJes[0] + 1;
				fprintf(fp, "%2d;", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[1] + 1;
				fprintf(fp, "%2d;", dan );
				dan = m_arrDatumiIspita[i].m_arrDanJes[2] + 1;
				fprintf(fp, "%2d;\n", dan );
			}
		}
	}

}

void COptRokDoc::OnPregledPoSmjerovima() 
{
	CDlgPopisIspita		*pDlg;
	int				sif, k, i, RowNum, ind;
	string		str;
	char			isp[200];
	char			naslovi[17][20] = {  "Sifra", "Naziv predmeta", "Jes.izv.", "1. zimski", "2. zimski", "Proljetni", "1. ljetni",
		"2. ljetni", "3.ljetni", "1. jesenski", "2.jesenski", "3.jesenski",
		"sem.", "br.st.", "grupa", "smjer", "opis"};

	pDlg = new CDlgPopisIspita();

	pDlg->m_ctrlGrid.SetRows(250);
	pDlg->m_ctrlGrid.SetCols(17);
	pDlg->m_ctrlGrid.SetColWidth(0,500);
	pDlg->m_ctrlGrid.SetColWidth(1,3800);
	pDlg->m_ctrlGrid.SetColAlignment(0,1);
	pDlg->m_ctrlGrid.SetColAlignment(1,1);

	pDlg->m_ctrlGrid.SetRow(0);

	pDlg->m_ctrlGrid.SetCol(0);
	pDlg->m_ctrlGrid.SetText(naslovi[0]);
	
	pDlg->m_ctrlGrid.SetCol(1);
	pDlg->m_ctrlGrid.SetText(naslovi[1]);

	for( k=2; k<12; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetColWidth(k,800);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
	}
	for( k=12; k<16; k++ )
	{
		pDlg->m_ctrlGrid.SetCol(k);
		pDlg->m_ctrlGrid.SetColAlignment(k,4);
		pDlg->m_ctrlGrid.SetText(naslovi[k]);
		pDlg->m_ctrlGrid.SetColWidth(k,500);
	}
	
	RowNum = 1;
	for( int smj=1; smj<=22; smj++ )
		for( int j=1; j<=9;j++ )
		{
			for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
			{
				sif = m_arrDatumiIspita[i].m_nSifraIspita;
				ind = m_Opt->ModPar.vecSifraUIndex[sif];

				bool	exist = false;
				for( int k=0; k<m_Opt->ModPar.vecOptIsp[ind].vecDodPod.size(); k++ )
					if( m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar == j && 
							m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer == smj )
					{
						exist = true;
						break;
					}
				
				if( exist == true )
				{
					pDlg->m_ctrlGrid.SetRow(RowNum++);
		
					sprintf(isp, "%d", sif);
					pDlg->m_ctrlGrid.SetCol(0);
					pDlg->m_ctrlGrid.SetText(isp);
					
					str = m_Opt->vecNaziviPred[sif];
					sprintf(isp, "%s", str.c_str() );
					pDlg->m_ctrlGrid.SetCol(1);
					pDlg->m_ctrlGrid.SetText(isp);
			/*
					for( k=0; k<m_Opt->ModPar.nBrRok; k++ )
					{
						pDlg->m_ctrlGrid.SetCol(k+2);

						sprintf(isp, "%2d", m_Opt->Population[m_nBestCromosomInd]->TerminiIspita[i][k]);
						pDlg->m_ctrlGrid.SetText(isp);
					}
			*/
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJesIzv );
					pDlg->m_ctrlGrid.SetCol(2);
					pDlg->m_ctrlGrid.SetText(isp);

					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[0] );
					pDlg->m_ctrlGrid.SetCol(3);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanZim[1] );
					pDlg->m_ctrlGrid.SetCol(4);
					pDlg->m_ctrlGrid.SetText(isp);

					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanProlj );
					pDlg->m_ctrlGrid.SetCol(5);
					pDlg->m_ctrlGrid.SetText(isp);

					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[0] );
					pDlg->m_ctrlGrid.SetCol(6);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[1] );
					pDlg->m_ctrlGrid.SetCol(7);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanLjet[2] );
					pDlg->m_ctrlGrid.SetCol(8);
					pDlg->m_ctrlGrid.SetText(isp);

					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[0] );
					pDlg->m_ctrlGrid.SetCol(9);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[1] );
					pDlg->m_ctrlGrid.SetCol(10);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_arrDatumiIspita[i].m_arrDanJes[2] );
					pDlg->m_ctrlGrid.SetCol(11);
					pDlg->m_ctrlGrid.SetText(isp);

					sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar  );
					pDlg->m_ctrlGrid.SetCol(12);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].BrojStud );
					pDlg->m_ctrlGrid.SetCol(13);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Grupa );
					pDlg->m_ctrlGrid.SetCol(14);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%d", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer );
					pDlg->m_ctrlGrid.SetCol(15);
					pDlg->m_ctrlGrid.SetText(isp);
					sprintf(isp, "%c", m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Opis );
					pDlg->m_ctrlGrid.SetCol(16);
					pDlg->m_ctrlGrid.SetText(isp);
				}
			}
		}
}

void COptRokDoc::OnPregledSmjeroviGodine() 
{
	int			k, i, sif, ind, god, br_pred;
	int			tot=0;
	string	str;

	CPregledSmjeroviGodinaDlg		*pDlg;	

	pDlg = new CPregledSmjeroviGodinaDlg();

	char		isp[200];

	for( int smj=1; smj<=22; smj++ )
		for( int j=1; j<=5;j++ )
		{
			for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
			{
				sif = m_arrDatumiIspita[i].m_nSifraIspita;
				ind = m_Opt->ModPar.vecSifraUIndex[sif];

				bool	exist = false;
				for( int k=0; k<m_Opt->ModPar.vecOptIsp[ind].vecDodPod.size(); k++ )
					if( (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2 == j-1 && 
							m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer == smj )
					{
						exist = true;
						break;
					}
				
				if( exist == true )
				{
					god = (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2;
					br_pred = pDlg->m_nBrojPredmeta[god][smj];

					str = m_Opt->vecNaziviPred[sif];
					sprintf(isp, "%s", str.c_str() );

					strcpy(pDlg->m_chPredmet[god][smj][br_pred], isp);
					
					pDlg->m_nDaniIspita[god][smj][br_pred][0] = m_arrDatumiIspita[i].m_arrDanJesIzv ;

					pDlg->m_nDaniIspita[god][smj][br_pred][1] = m_arrDatumiIspita[i].m_arrDanZim[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][2] = m_arrDatumiIspita[i].m_arrDanZim[1];

					pDlg->m_nDaniIspita[god][smj][br_pred][3] = m_arrDatumiIspita[i].m_arrDanProlj;

					pDlg->m_nDaniIspita[god][smj][br_pred][4] = m_arrDatumiIspita[i].m_arrDanLjet[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][5] = m_arrDatumiIspita[i].m_arrDanLjet[1];
					pDlg->m_nDaniIspita[god][smj][br_pred][6] = m_arrDatumiIspita[i].m_arrDanLjet[2];

					pDlg->m_nDaniIspita[god][smj][br_pred][7] = m_arrDatumiIspita[i].m_arrDanJes[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][8] = m_arrDatumiIspita[i].m_arrDanJes[1];
					pDlg->m_nDaniIspita[god][smj][br_pred][9] = m_arrDatumiIspita[i].m_arrDanJes[2];

					pDlg->m_chOpis[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Opis;
					pDlg->m_nSemestar[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar;
					pDlg->m_nGrupaPred[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Grupa;
					pDlg->m_nBrojStud[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].BrojStud;


					pDlg->m_nBrojPredmeta[god][smj]++;
					
					tot++;
				}
			}
		}

	pDlg->m_nGodina = 1;
	pDlg->m_nSifraSmjera = 20;

	pDlg->ShowData();
}


void COptRokDoc::OnAsciiDatSmjerGod() 
{
	int			k, i, sif, ind, god, br_pred;
	int			tot=0;
	string	str;

	char		m_chPredmet[5][23][20][100];		// nazivi predmeta  [GOD][SMJER][PREDMET]
	int			m_nDaniIspita[5][23][20][10];		// kada su dani odrzavanja ispita
	int			m_nSemestar[5][23][20];			// kada su dani odrzavanja ispita
	int			m_nBrojStud[5][23][20];			// kada su dani odrzavanja ispita
	int			m_nGrupaPred[5][23][20];		// kada su dani odrzavanja ispita
	char		m_chOpis[5][23][20];				// kada su dani odrzavanja ispita
	int			m_nBrojPredmeta[5][23];

	char		isp[200];

	for( int smj=1; smj<=22; smj++ )
		for( int j=1; j<=5;j++ )
		{
			for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
			{
				sif = m_arrDatumiIspita[i].m_nSifraIspita;
				ind = m_Opt->ModPar.vecSifraUIndex[sif];

				bool	exist = false;
				for( int k=0; k<m_Opt->ModPar.vecOptIsp[ind].vecDodPod.size(); k++ )
					if( (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2 == j-1 && 
							m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer == smj )
					{
						exist = true;
						break;
					}
				
				if( exist == true )
				{
					god = (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2;
					br_pred = m_nBrojPredmeta[god][smj];

					str = m_Opt->vecNaziviPred[sif];
					sprintf(isp, "%s", str.c_str() );

					strcpy(m_chPredmet[god][smj][br_pred], isp);
					
					m_nDaniIspita[god][smj][br_pred][0] = m_arrDatumiIspita[i].m_arrDanJesIzv ;

					m_nDaniIspita[god][smj][br_pred][1] = m_arrDatumiIspita[i].m_arrDanZim[0];
					m_nDaniIspita[god][smj][br_pred][2] = m_arrDatumiIspita[i].m_arrDanZim[1];

					m_nDaniIspita[god][smj][br_pred][3] = m_arrDatumiIspita[i].m_arrDanProlj;

					m_nDaniIspita[god][smj][br_pred][4] = m_arrDatumiIspita[i].m_arrDanLjet[0];
					m_nDaniIspita[god][smj][br_pred][5] = m_arrDatumiIspita[i].m_arrDanLjet[1];
					m_nDaniIspita[god][smj][br_pred][6] = m_arrDatumiIspita[i].m_arrDanLjet[2];

					m_nDaniIspita[god][smj][br_pred][7] = m_arrDatumiIspita[i].m_arrDanJes[0];
					m_nDaniIspita[god][smj][br_pred][8] = m_arrDatumiIspita[i].m_arrDanJes[1];
					m_nDaniIspita[god][smj][br_pred][9] = m_arrDatumiIspita[i].m_arrDanJes[2];

					m_chOpis[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Opis;
					m_nSemestar[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar;
					m_nGrupaPred[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Grupa;
					m_nBrojStud[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].BrojStud;


					m_nBrojPredmeta[god][smj]++;
					
					tot++;
				}
			}
		}

	int			dan;
	FILE		*fp;

	if( (fp = fopen("ASCII_Smjer_Godina.txt", "w") ) == NULL )
		AfxMessageBox("Nisam uspio otvoriti datoteku ASCII_Smjer_Godina.txt");

	for( smj=1; smj<23; smj++ )
	{
		fprintf(fp, "\n\n%s", NazivSmjera[smj] );
		for( int god=0; god<5; god++ )
		{
			if( m_nBrojPredmeta[god][smj] > 0 )
				fprintf(fp, "\n\n %d. godina\n", god+1);

			for( k=0; k<m_nBrojPredmeta[god][smj]; k++ )
			{
				sprintf(isp, "%-40s", m_chPredmet[god][smj][k] );
				isp[40] = 0;
				fprintf(fp, "\n  %-s   ", isp );
				for( dan=1; dan<10; dan++ )
				{
					fprintf(fp, " %2d ", m_nDaniIspita[god][smj][k][dan] );
					if( dan == 2 )				// odvoji zimski rok od ostalih
						fprintf(fp, "   ");
					if( dan == 3 )
						fprintf(fp, "   ");
					if( dan == 6 )
						fprintf(fp, "   ");
				}
			}
		}
	}
}

void COptRokDoc::OnPregledSmjerGodVizualno() 
{
	int			k, i, sif, ind, god, br_pred;
	int			tot=0;
	string	str;

	CDlgPregledSmjerGodinaVizualno		*pDlg;	

	pDlg = new CDlgPregledSmjerGodinaVizualno();

	char		isp[200];

	for( int smj=1; smj<=22; smj++ )
		for( int j=1; j<=5;j++ )
		{
			for( i=0; i<m_Opt->ModPar.nBrIsp; i++ )
			{
				sif = m_arrDatumiIspita[i].m_nSifraIspita;
				ind = m_Opt->ModPar.vecSifraUIndex[sif];

				bool	exist = false;
				for( int k=0; k<m_Opt->ModPar.vecOptIsp[ind].vecDodPod.size(); k++ )
					if( (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2 == j-1 && 
							m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Smjer == smj )
					{
						exist = true;
						break;
					}
				
				if( exist == true )
				{
					god = (m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar-1) / 2;
					br_pred = pDlg->m_nBrojPredmeta[god][smj];

					str = m_Opt->vecNaziviPred[sif];
					sprintf(isp, "%s", str.c_str() );
					isp[49] = 0;

					strcpy(pDlg->m_chPredmet[god][smj][br_pred], isp);
					
					pDlg->m_nDaniIspita[god][smj][br_pred][0] = m_arrDatumiIspita[i].m_arrDanJesIzv ;

					pDlg->m_nDaniIspita[god][smj][br_pred][1] = m_arrDatumiIspita[i].m_arrDanZim[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][2] = m_arrDatumiIspita[i].m_arrDanZim[1];

					pDlg->m_nDaniIspita[god][smj][br_pred][3] = m_arrDatumiIspita[i].m_arrDanProlj;

					pDlg->m_nDaniIspita[god][smj][br_pred][4] = m_arrDatumiIspita[i].m_arrDanLjet[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][5] = m_arrDatumiIspita[i].m_arrDanLjet[1];
					pDlg->m_nDaniIspita[god][smj][br_pred][6] = m_arrDatumiIspita[i].m_arrDanLjet[2];

					pDlg->m_nDaniIspita[god][smj][br_pred][7] = m_arrDatumiIspita[i].m_arrDanJes[0];
					pDlg->m_nDaniIspita[god][smj][br_pred][8] = m_arrDatumiIspita[i].m_arrDanJes[1];
					pDlg->m_nDaniIspita[god][smj][br_pred][9] = m_arrDatumiIspita[i].m_arrDanJes[2];

					pDlg->m_chOpis[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Opis;
					pDlg->m_nSemestar[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Semestar;
					pDlg->m_nGrupaPred[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].Grupa;
					pDlg->m_nBrojStud[god][smj][br_pred] = m_Opt->ModPar.vecOptIsp[ind].vecDodPod[k].BrojStud;


					pDlg->m_nBrojPredmeta[god][smj]++;
					
					tot++;
				}
			}
		}

	pDlg->m_nGodina = 3;
	pDlg->m_nSifraSmjera = 20;
	pDlg->m_Rok = LJETNI;

	pDlg->ShowData();
}
