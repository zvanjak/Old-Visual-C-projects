// TestOptFuncView.h : interface of the CTestOptFuncView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTOPTFUNCVIEW_H__98AE12AC_786C_4740_BBEB_0AB9ACDFE55D__INCLUDED_)
#define AFX_TESTOPTFUNCVIEW_H__98AE12AC_786C_4740_BBEB_0AB9ACDFE55D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestOptFuncView : public CView
{
protected: // create from serialization only
	CTestOptFuncView();
	DECLARE_DYNCREATE(CTestOptFuncView)

// Attributes
public:
	CTestOptFuncDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestOptFuncView)
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
	virtual ~CTestOptFuncView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestOptFuncView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestOptFuncView.cpp
inline CTestOptFuncDoc* CTestOptFuncView::GetDocument()
   { return (CTestOptFuncDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOPTFUNCVIEW_H__98AE12AC_786C_4740_BBEB_0AB9ACDFE55D__INCLUDED_)
