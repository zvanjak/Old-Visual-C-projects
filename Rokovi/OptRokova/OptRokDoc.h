// OptRokDoc.h : interface of the COptRokDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTROKDOC_H__85982E2D_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
#define AFX_OPTROKDOC_H__85982E2D_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


void Zapisi( CArchive &ar, Date dat );
void Ucitaj( CArchive &ar, Date &dat );


class COptRokDoc : public CDocument
{
protected: // create from serialization only
	COptRokDoc();
	DECLARE_DYNCREATE(COptRokDoc)

// Attributes
public:
	OptProblem		*m_Opt; //("predmet.txt", "nasprogram.txt", "presjek.txt");
	int						m_nBestCromosomInd;
	bool					m_bOptimizationStarted;

	int								m_nOptIspita;
	vector< Zapis >		m_arrDatumiIspita;

	bool	SifraSmjeraPostoji[23];
	char 	NazivSmjera[23][100];

// Operations
public:
	int	 DanIspita( COptRokDoc	*pDoc, int BrIsp, int BrRoka, TerminRoka	Vrsta );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptRokDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptRokDoc)
	afx_msg void OnPostaviParametreOptimizacije();
	afx_msg void OnPostaviParametreRoka();
	afx_msg void OnOptimizacijaPokreni();
	afx_msg void OnRezultatiPregledPoIspitima();
	afx_msg void OnRezultatiPregledPoGrupamaPredmeta();
	afx_msg void OnRezultatiPregledPoDanima();
	afx_msg void OnRezultatiVizualniPrikaz();
	afx_msg void OnWriteAscii();
	afx_msg void OnRezultatiPregledPoSemestrima();
	afx_msg void OnPregledIspitiIstiDan();
	afx_msg void OnPregledIspunjavanjeZeljaProf();
	afx_msg void OnFileExport();
	afx_msg void OnPregledPoSmjerovima();
	afx_msg void OnPregledSmjeroviGodine();
	afx_msg void OnAsciiDatSmjerGod();
	afx_msg void OnPregledSmjerGodVizualno();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKDOC_H__85982E2D_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)

