// TestNumFrameworkDlg.h : header file
//

#if !defined(AFX_TESTNUMFRAMEWORKDLG_H__13577C00_4BC7_4810_BBC5_0817241C3C6D__INCLUDED_)
#define AFX_TESTNUMFRAMEWORKDLG_H__13577C00_4BC7_4810_BBC5_0817241C3C6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Skeleton.h"

#define WM_REFRESH_MESSAGE (WM_USER + 100)

class CTestDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog, 
								 public IVisualizationObject<long>,
								 public ISaveResultObject<long>
{
	DECLARE_DYNAMIC(CTestDlg);
	friend class CTestDlgAutoProxy;

// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTestDlg();

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TESTNUMFRAMEWORK_DIALOG };
	CButton	m_cmdStop;
	CButton	m_cmdContinue;
	CEdit	m_ctrlLastFound;
	CButton	m_cmdStart;
	CString	m_strEdit;
	long	m_lStart;
	long	m_lEnd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTestDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

//	IExchangeDataObject<long>		*pExch;
	ThreadablePrimSolver				*pSolver;

	void AddCalcResult( long &res );

	std::vector<long>		vecResult;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCmdStart();
  afx_msg LRESULT OnRefreshMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCmdStop();
	afx_msg void OnCmdContinue();
	afx_msg void OnCmdTerminate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTNUMFRAMEWORKDLG_H__13577C00_4BC7_4810_BBC5_0817241C3C6D__INCLUDED_)
