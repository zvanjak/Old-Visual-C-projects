// SchEqView.h : interface of the CSchEqView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEQVIEW_H__29316553_A188_4931_818C_FBBC75687408__INCLUDED_)
#define AFX_SCHEQVIEW_H__29316553_A188_4931_818C_FBBC75687408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "simplegraph.h"

class CSchEqView : public CView
{
protected: // create from serialization only
	CSchEqView();
	DECLARE_DYNCREATE(CSchEqView)

	CSimpleGraph		m_ctrlGraph;

	int		nGraphID;
	int		nPotGraphID;

// Attributes
public:
	CSchEqDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchEqView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSchEqView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchEqView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawMetafile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SchEqView.cpp
inline CSchEqDoc* CSchEqView::GetDocument()
   { return (CSchEqDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEQVIEW_H__29316553_A188_4931_818C_FBBC75687408__INCLUDED_)
