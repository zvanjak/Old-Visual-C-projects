#if !defined(AFX_DLGPERFORMINTEGRATION_H__0933FC6C_6048_47F1_85C4_83C5C3345C82__INCLUDED_)
#define AFX_DLGPERFORMINTEGRATION_H__0933FC6C_6048_47F1_85C4_83C5C3345C82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPerformIntegration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPerformIntegration dialog

class CDlgPerformIntegration : public CDialog
{
// Construction
public:
	CDlgPerformIntegration(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPerformIntegration)
	enum { IDD = IDD_PERFORM_INTEGRATION };
	double	m_fEnd;
	double	m_fStart;
	double	m_fStep;
	CString	m_fValues;
	double	m_fNorm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPerformIntegration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPerformIntegration)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPERFORMINTEGRATION_H__0933FC6C_6048_47F1_85C4_83C5C3345C82__INCLUDED_)
