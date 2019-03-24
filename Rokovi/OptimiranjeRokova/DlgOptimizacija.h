//{{AFX_INCLUDES()
#include "prikazrasporedaispita.h"
#include "scrollbar.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGOPTIMIZACIJA_H__A2BDBC01_A940_415E_A674_A17181461921__INCLUDED_)
#define AFX_DLGOPTIMIZACIJA_H__A2BDBC01_A940_415E_A674_A17181461921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptimizacija.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizacija dialog

class CDlgOptimizacija : public CDialog
{
// Construction
public:
	CDlgOptimizacija(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptimizacija)
	enum { IDD = IDD_OPTIMIZACIJA };
	CPrikazRasporedaIspita	m_ctrlPrikaz;
	CScrollbar	m_ctrlVScroll;
	//}}AFX_DATA

public:
	int		m_nScrollBarOldPos;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptimizacija)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptimizacija)
	afx_msg void OnChangeScrollbar();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIMIZACIJA_H__A2BDBC01_A940_415E_A674_A17181461921__INCLUDED_)
