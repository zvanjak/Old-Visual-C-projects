//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGPREGLEDZELJA_H__704699D6_7D6E_11D3_A9C6_00C0DFE5278A__INCLUDED_)
#define AFX_DLGPREGLEDZELJA_H__704699D6_7D6E_11D3_A9C6_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPregledZelja.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPregledZelja dialog

class CDlgPregledZelja : public CDialog
{
// Construction
public:
	CDlgPregledZelja(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPregledZelja)
	enum { IDD = IDD_PREGLED_SA_ZELJAMA };
	CMSFlexGrid	m_ctrlGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPregledZelja)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPregledZelja)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREGLEDZELJA_H__704699D6_7D6E_11D3_A9C6_00C0DFE5278A__INCLUDED_)
