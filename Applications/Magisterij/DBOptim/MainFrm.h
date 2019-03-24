// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EA17AC3B_128F_4EDC_861B_A59504F57A7D__INCLUDED_)
#define AFX_MAINFRM_H__EA17AC3B_128F_4EDC_861B_A59504F57A7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=39571A2801CF
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	//##ModelId=39571A280263
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//##ModelId=39571A28025A
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A280259
	virtual ~CMainFrame();
#ifdef _DEBUG
	//##ModelId=39571A280250
	virtual void AssertValid() const;
	//##ModelId=39571A280247
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//##ModelId=39571A280233
	CStatusBar  m_wndStatusBar;
	//##ModelId=39571A28021F
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	//##ModelId=39571A280245
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EA17AC3B_128F_4EDC_861B_A59504F57A7D__INCLUDED_)
