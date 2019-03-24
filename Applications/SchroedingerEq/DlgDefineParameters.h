#if !defined(AFX_DLGDEFINEPARAMETERS_H__6EC3393C_C9AF_47CB_BAF2_22779B6B007C__INCLUDED_)
#define AFX_DLGDEFINEPARAMETERS_H__6EC3393C_C9AF_47CB_BAF2_22779B6B007C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDefineParameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDefineParameters dialog

class CDlgDefineParameters : public CDialog
{
// Construction
public:
	CDlgDefineParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDefineParameters)
	enum { IDD = IDD_DEFINE_PAR };
	float	m_a1;
	float	m_a2;
	float	m_b1;
	float	m_b2;
	float	m_V0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDefineParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDefineParameters)
	afx_msg void OnFiniteHole();
	afx_msg void OnGaussPot();
	afx_msg void OnInfHole();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEFINEPARAMETERS_H__6EC3393C_C9AF_47CB_BAF2_22779B6B007C__INCLUDED_)
