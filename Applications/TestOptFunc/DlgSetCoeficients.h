#if !defined(AFX_DLGSETCOEFICIENTS_H__481588A4_129B_436F_A116_F70D4D2152F1__INCLUDED_)
#define AFX_DLGSETCOEFICIENTS_H__481588A4_129B_436F_A116_F70D4D2152F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetCoeficients.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetCoeficients dialog

class CDlgSetCoeficients : public CDialog
{
// Construction
public:
	CDlgSetCoeficients(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetCoeficients)
	enum { IDD = IDD_SET };
	int		m_ctrlExamNum;
	long	m_ctrlIterNum;
	double	m_ctrlMutProb;
	int		m_ctrlPopSize;
	int		m_ctrlSubperiodNum;
	int		m_ctrlTermNum;
	double	m_ctrlX0;
	double	m_ctrlExp;
	double	m_ctrlCutPoint;
	double	m_ctrlLinCoef;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetCoeficients)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetCoeficients)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETCOEFICIENTS_H__481588A4_129B_436F_A116_F70D4D2152F1__INCLUDED_)
