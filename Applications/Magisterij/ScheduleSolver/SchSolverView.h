// SchSolverView.h : interface of the CSchSolverView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHSOLVERVIEW_H__446588FC_DC13_40DD_A7AC_474457FC56B6__INCLUDED_)
#define AFX_SCHSOLVERVIEW_H__446588FC_DC13_40DD_A7AC_474457FC56B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//##ModelId=39571A98021E
class CSchSolverView : public CEditView
{
protected: // create from serialization only
	//##ModelId=39571A980264
	CSchSolverView();
	DECLARE_DYNCREATE(CSchSolverView)

// Attributes
public:
	//##ModelId=39571A98025E
	CSchSolverDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchSolverView)
	public:
	//##ModelId=39571A98025C
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//##ModelId=39571A98025A
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=39571A980254
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//##ModelId=39571A980251
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=39571A980247
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A980246
	virtual ~CSchSolverView();
#ifdef _DEBUG
	//##ModelId=39571A98023E
	virtual void AssertValid() const;
	//##ModelId=39571A98023C
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchSolverView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SchSolverView.cpp
inline CSchSolverDoc* CSchSolverView::GetDocument()
   { return (CSchSolverDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHSOLVERVIEW_H__446588FC_DC13_40DD_A7AC_474457FC56B6__INCLUDED_)
