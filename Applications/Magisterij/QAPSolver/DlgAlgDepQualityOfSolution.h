#if !defined(AFX_DLGALGDEPQUALITYOFSOLUTION_H__2BC7C4FA_5DCD_4243_A2E8_F544E3788286__INCLUDED_)
#define AFX_DLGALGDEPQUALITYOFSOLUTION_H__2BC7C4FA_5DCD_4243_A2E8_F544E3788286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlgDepQualityOfSolution.h : header file
//

class CQAPCompareDoc;

/////////////////////////////////////////////////////////////////////////////
// CDlgAlgDepQualityOfSolution dialog

class CDlgAlgDepQualityOfSolution : public CDialog
{
// Construction
public:
	CDlgAlgDepQualityOfSolution(CQAPCompareDoc *inpDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlgDepQualityOfSolution)
	enum { IDD = IDD_ALG_DEPENDENCE_QUALITY };
	CComboBox	m_ctrlSelAlgType;
	int		m_nRepetitionNum;
	//}}AFX_DATA

	CQAPCompareDoc		*pDoc;

	CString		m_strPar[4];
	CString		m_strValues[4];
	float			m_fFrom[4];
	float			m_fStep[4];
	float			m_fTo[4];
	float			m_fTime[10];

	int				m_ParNum;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlgDepQualityOfSolution)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlgDepQualityOfSolution)
	afx_msg void OnSelchangeAlgType();
	virtual BOOL OnInitDialog();
	afx_msg void OnStartAlgDepQualityCmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALGDEPQUALITYOFSOLUTION_H__2BC7C4FA_5DCD_4243_A2E8_F544E3788286__INCLUDED_)
