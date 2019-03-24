// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__4D21E8D4_5B88_412E_B567_0452A18C52D3__INCLUDED_)
#define AFX_CHILDFRM_H__4D21E8D4_5B88_412E_B567_0452A18C52D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//##ModelId=39571A9900E9
class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	//##ModelId=39571A99011D
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	//##ModelId=39571A99011B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A990112
	virtual ~CChildFrame();
#ifdef _DEBUG
	//##ModelId=39571A990111
	virtual void AssertValid() const;
	//##ModelId=39571A990108
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__4D21E8D4_5B88_412E_B567_0452A18C52D3__INCLUDED_)
