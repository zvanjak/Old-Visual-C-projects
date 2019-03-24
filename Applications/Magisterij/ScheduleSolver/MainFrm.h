// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3DA31327_0603_4E95_BE1F_435B6F8C38F7__INCLUDED_)
#define AFX_MAINFRM_H__3DA31327_0603_4E95_BE1F_435B6F8C38F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=39571A98005B
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	//##ModelId=39571A9800BF
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//##ModelId=39571A9800B6
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A9800B5
	virtual ~CMainFrame();
#ifdef _DEBUG
	//##ModelId=39571A9800AC
	virtual void AssertValid() const;
	//##ModelId=39571A9800A3
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//##ModelId=39571A98008F
	CStatusBar  m_wndStatusBar;
	//##ModelId=39571A98007C
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	//##ModelId=39571A9800A1
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3DA31327_0603_4E95_BE1F_435B6F8C38F7__INCLUDED_)
