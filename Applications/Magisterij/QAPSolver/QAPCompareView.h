#if !defined(AFX_QAPCOMPAREVIEW_H__26B36D9F_67CD_41BC_AAE9_C270C90A949D__INCLUDED_)
#define AFX_QAPCOMPAREVIEW_H__26B36D9F_67CD_41BC_AAE9_C270C90A949D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QAPCompareView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareView view

class CQAPCompareView : public CView
{
protected:
	CQAPCompareView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQAPCompareView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAPCompareView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQAPCompareView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQAPCompareView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QAPCOMPAREVIEW_H__26B36D9F_67CD_41BC_AAE9_C270C90A949D__INCLUDED_)
