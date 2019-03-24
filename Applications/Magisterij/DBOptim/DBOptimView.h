// DBOptimView.h : interface of the CDBOptimView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBOPTIMVIEW_H__AC304A9A_12CD_48EE_873C_F4BDF8F70B69__INCLUDED_)
#define AFX_DBOPTIMVIEW_H__AC304A9A_12CD_48EE_873C_F4BDF8F70B69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDBOptimSet;

//##ModelId=39571A290142
class CDBOptimView : public COleDBRecordView
{
protected: // create from serialization only
	//##ModelId=39571A2901A6
	CDBOptimView();
	DECLARE_DYNCREATE(CDBOptimView)

public:
	//{{AFX_DATA(CDBOptimView)
	enum{ IDD = IDD_DBOPTIM_FORM };
	//##ModelId=39571A290159
	CDBOptimSet* m_pSet;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	//##ModelId=39571A29019E
	CDBOptimDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBOptimView)
	public:
	//##ModelId=39571A29019D
	virtual CRowset* OnGetRowset();
	//##ModelId=39571A290194
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=39571A290192
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//##ModelId=39571A29018A
	virtual void OnInitialUpdate(); // called first time after construct
	//##ModelId=39571A290188
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//##ModelId=39571A29017F
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=39571A290175
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A290174
	virtual ~CDBOptimView();
#ifdef _DEBUG
	//##ModelId=39571A29016B
	virtual void AssertValid() const;
	//##ModelId=39571A290160
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBOptimView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DBOptimView.cpp
inline CDBOptimDoc* CDBOptimView::GetDocument()
   { return (CDBOptimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBOPTIMVIEW_H__AC304A9A_12CD_48EE_873C_F4BDF8F70B69__INCLUDED_)
