#if !defined(AFX_DLGOPTIONS_H__BE7834F0_FE76_460A_98B8_454B99C6A121__INCLUDED_)
#define AFX_DLGOPTIONS_H__BE7834F0_FE76_460A_98B8_454B99C6A121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog

class CDlgOptions : public CDialog
{
// Construction
public:
	CDlgOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptions)
	enum { IDD = IDD_OPTIONS };
	int		m_NumInt;
	int		m_PerFunc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONS_H__BE7834F0_FE76_460A_98B8_454B99C6A121__INCLUDED_)
