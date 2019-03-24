// OptRokView.h : interface of the COptRokView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTROKVIEW_H__3B23E2D1_4811_4462_A37C_091A7AEC1AFF__INCLUDED_)
#define AFX_OPTROKVIEW_H__3B23E2D1_4811_4462_A37C_091A7AEC1AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COptRokView : public CView
{
protected: // create from serialization only
	COptRokView();
	DECLARE_DYNCREATE(COptRokView)

// Attributes
public:
	COptRokDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokView)
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
	virtual ~COptRokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptRokView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OptRokView.cpp
inline COptRokDoc* COptRokView::GetDocument()
   { return (COptRokDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKVIEW_H__3B23E2D1_4811_4462_A37C_091A7AEC1AFF__INCLUDED_)
