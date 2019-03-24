#if !defined(AFX_DLGPREGLEDSMJERGODINAVIZUALNO_H__109DA0B7_7DA7_48AF_A773_0E9AD14D5ECC__INCLUDED_)
#define AFX_DLGPREGLEDSMJERGODINAVIZUALNO_H__109DA0B7_7DA7_48AF_A773_0E9AD14D5ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPregledSmjerGodinaVizualno.h : header file
//

#include "OptRokDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledSmjerGodinaVizualno dialog

class CDlgPregledSmjerGodinaVizualno : public CDialog
{
// Construction
public:
	CDlgPregledSmjerGodinaVizualno(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPregledSmjerGodinaVizualno)
	enum { IDD = IDD_PREGLED_SMJER_GOD_VIZ };
	CButton	m_ctrlButtZim;
	CButton	m_ctrlButtProlj;
	CButton	m_ctrlButtLjet;
	CButton	m_ctrlButtJesIzv;
	CButton	m_ctrlButtJes;
	CComboBox	m_ctrlSmjer;
	CButton	m_ctrlGod5;
	CButton	m_ctrlGod4;
	CButton	m_ctrlGod3;
	CButton	m_ctrlGod2;
	CButton	m_ctrlGod1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPregledSmjerGodinaVizualno)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPregledSmjerGodinaVizualno)
	afx_msg void OnGodina1();
	afx_msg void OnGodina2();
	afx_msg void OnGodina3();
	afx_msg void OnGodina4();
	afx_msg void OnGodina5();
	afx_msg void OnSelchangeOdabirSmjera();
	afx_msg void OnPromjeniSmjer();
	afx_msg void OnCheckJes();
	afx_msg void OnCheckJesizv();
	afx_msg void OnCheckLjet();
	afx_msg void OnCheckProlj();
	afx_msg void OnCheckZim();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int			m_nSifraSmjera;			// šifra smjera koji se trenutno prikazuje
	int			m_nGodina;					// godina za koju se prikazuju predmeti
	TerminRoka		m_Rok;

	int			m_StartWith;

	char		m_chPredmet[5][23][25][50];		// nazivi predmeta  [GOD][SMJER][PREDMET]
	int			m_nDaniIspita[5][23][20][10];		// kada su dani odrzavanja ispita
	int			m_nSemestar[5][23][20];			// kada su dani odrzavanja ispita
	int			m_nBrojStud[5][23][20];			// kada su dani odrzavanja ispita
	int			m_nGrupaPred[5][23][20];		// kada su dani odrzavanja ispita
	char		m_chOpis[5][23][20];				// kada su dani odrzavanja ispita
	int			m_nBrojPredmeta[5][23];

	void		ShowData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREGLEDSMJERGODINAVIZUALNO_H__109DA0B7_7DA7_48AF_A773_0E9AD14D5ECC__INCLUDED_)
