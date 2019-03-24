#if !defined(AFX_DLGTIMETOREACHSOL_H__04CA39FE_02D4_4EE7_ADC4_A7F8B0259749__INCLUDED_)
#define AFX_DLGTIMETOREACHSOL_H__04CA39FE_02D4_4EE7_ADC4_A7F8B0259749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimeToReachSol.h : header file
//

class CQAPCompareDoc;

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeToReachSol dialog

class CDlgTimeToReachSol : public CDialog
{
// Construction
public:
	CDlgTimeToReachSol(	CQAPCompareDoc	*inpDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTimeToReachSol)
	enum { IDD = IDD_ALG_DEPENDENCE_TIME };
	CComboBox	m_ctrlSelAlgType;
	int		m_nRepetitionNum;
	//}}AFX_DATA
	
	CQAPCompareDoc		*pDoc;

	CString		m_strPar[4];
	CString		m_strValues[4];
	float			m_fFrom[4];
	float			m_fStep[4];
	float			m_fTo[4];

	int				m_ParNum;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTimeToReachSol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTimeToReachSol)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAlgType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMETOREACHSOL_H__04CA39FE_02D4_4EE7_ADC4_A7F8B0259749__INCLUDED_)
