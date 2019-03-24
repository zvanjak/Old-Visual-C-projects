//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PREGLEDSMJEROVIGODINADLG_H__9EF4C56F_CEA1_4194_A53F_41CB900848DE__INCLUDED_)
#define AFX_PREGLEDSMJEROVIGODINADLG_H__9EF4C56F_CEA1_4194_A53F_41CB900848DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PregledSmjeroviGodinaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPregledSmjeroviGodinaDlg dialog

class CPregledSmjeroviGodinaDlg : public CDialog
{
// Construction
public:
	CPregledSmjeroviGodinaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPregledSmjeroviGodinaDlg)
	enum { IDD = IDD_PREGLED_PO_SMJEROVIMA };
	CComboBox	m_ctrlSmjer;
	CButton	m_ctrlGod5;
	CButton	m_ctrlGod4;
	CButton	m_ctrlGod3;
	CButton	m_ctrlGod2;
	CButton	m_ctrlGod1;
	CMSFlexGrid	m_ctrlGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPregledSmjeroviGodinaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPregledSmjeroviGodinaDlg)
	afx_msg void OnGodina1();
	afx_msg void OnGodina2();
	afx_msg void OnGodina3();
	afx_msg void OnGodina4();
	afx_msg void OnGodina5();
	afx_msg void OnSelchangeOdabirSmjera();
	afx_msg void OnPromjeniSmjer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int			m_nSifraSmjera;			// šifra smjera koji se trenutno prikazuje
	int			m_nGodina;					// godina za koju se prikazuju predmeti
	char		m_chPredmet[5][23][20][100];		// nazivi predmeta  [GOD][SMJER][PREDMET]
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

#endif // !defined(AFX_PREGLEDSMJEROVIGODINADLG_H__9EF4C56F_CEA1_4194_A53F_41CB900848DE__INCLUDED_)
