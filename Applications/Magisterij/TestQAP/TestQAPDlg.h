// TestQAPDlg.h : header file
//

#if !defined(AFX_TESTQAPDLG_H__2D4890B5_68F9_4868_B24D_16EE556DD3D8__INCLUDED_)
#define AFX_TESTQAPDLG_H__2D4890B5_68F9_4868_B24D_16EE556DD3D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CTestQAPDlg dialog

//##ModelId=39571AAF032F
class CTestQAPDlg : public CDialog
{
// Construction
public:
	//##ModelId=39571AAF03A8
	CTestQAPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestQAPDlg)
	enum { IDD = IDD_TESTQAP_DIALOG };
	//##ModelId=39571AAF0377
	CRichEditCtrl	m_ctrlRichEdit;
	//##ModelId=39571AAF0363
	CEdit	m_ctrlEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestQAPDlg)
	protected:
	//##ModelId=39571AAF039E
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=39571AAF0357
	HICON m_hIcon;
	
	//##ModelId=39571AAF0346
	QAPSimpleGenetic	QAP;//(19, 50,5000,0.01f);
	Matrix<float>		A, B, C; //(19,19), B(19,19), C(19,19);
	
	//##ModelId=39571AAF0343
	float	SolFunc; // = 17212548;
	//##ModelId=39571AAF033A
	int	Sol[19];// = {9, 10, 7, 18, 14, 19, 13, 17, 6, 11, 4, 5, 12, 8, 15, 16, 1, 2, 3 };

	// Generated message map functions
	//{{AFX_MSG(CTestQAPDlg)
	//##ModelId=39571AAF039D
	virtual BOOL OnInitDialog();
	//##ModelId=39571AAF038B
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//##ModelId=39571AAF038A
	afx_msg void OnPaint();
	//##ModelId=39571AAF0389
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTQAPDLG_H__2D4890B5_68F9_4868_B24D_16EE556DD3D8__INCLUDED_)
