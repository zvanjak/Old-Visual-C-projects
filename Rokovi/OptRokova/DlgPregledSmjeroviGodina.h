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
		// NOTE: the ClassWizard will add data members here
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
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREGLEDSMJEROVIGODINADLG_H__9EF4C56F_CEA1_4194_A53F_41CB900848DE__INCLUDED_)
