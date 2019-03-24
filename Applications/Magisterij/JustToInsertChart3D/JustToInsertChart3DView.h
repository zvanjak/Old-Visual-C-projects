// JustToInsertChart3DView.h : interface of the CJustToInsertChart3DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUSTTOINSERTCHART3DVIEW_H__397AE6A1_79B1_4CE5_BB27_01B19380311C__INCLUDED_)
#define AFX_JUSTTOINSERTCHART3DVIEW_H__397AE6A1_79B1_4CE5_BB27_01B19380311C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJustToInsertChart3DView : public CView
{
protected: // create from serialization only
	CJustToInsertChart3DView();
	DECLARE_DYNCREATE(CJustToInsertChart3DView)

// Attributes
public:
	CJustToInsertChart3DDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJustToInsertChart3DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJustToInsertChart3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJustToInsertChart3DView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in JustToInsertChart3DView.cpp
inline CJustToInsertChart3DDoc* CJustToInsertChart3DView::GetDocument()
   { return (CJustToInsertChart3DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUSTTOINSERTCHART3DVIEW_H__397AE6A1_79B1_4CE5_BB27_01B19380311C__INCLUDED_)
