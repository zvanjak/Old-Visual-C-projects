// OptScheduleView.h : interface of the COptScheduleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTSCHEDULEVIEW_H__27D5154E_C3C6_427E_9B9F_5B4843AA85D2__INCLUDED_)
#define AFX_OPTSCHEDULEVIEW_H__27D5154E_C3C6_427E_9B9F_5B4843AA85D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COptScheduleView : public CView
{
protected: // create from serialization only
	COptScheduleView();
	DECLARE_DYNCREATE(COptScheduleView)

// Attributes
public:
	COptScheduleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptScheduleView)
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
	virtual ~COptScheduleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptScheduleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OptScheduleView.cpp
inline COptScheduleDoc* COptScheduleView::GetDocument()
   { return (COptScheduleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTSCHEDULEVIEW_H__27D5154E_C3C6_427E_9B9F_5B4843AA85D2__INCLUDED_)
