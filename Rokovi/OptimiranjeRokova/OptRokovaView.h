// OptRokovaView.h : interface of the COptRokovaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTROKOVAVIEW_H__28E9EDC6_33A6_4F67_B82F_B6ABFFC264A9__INCLUDED_)
#define AFX_OPTROKOVAVIEW_H__28E9EDC6_33A6_4F67_B82F_B6ABFFC264A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COptRokovaView : public CView
{
protected: // create from serialization only
	COptRokovaView();
	DECLARE_DYNCREATE(COptRokovaView)

// Attributes
public:
	COptRokovaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokovaView)
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
	virtual ~COptRokovaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptRokovaView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OptRokovaView.cpp
inline COptRokovaDoc* COptRokovaView::GetDocument()
   { return (COptRokovaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKOVAVIEW_H__28E9EDC6_33A6_4F67_B82F_B6ABFFC264A9__INCLUDED_)
