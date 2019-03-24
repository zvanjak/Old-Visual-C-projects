// TestOptFuncDoc.h : interface of the CTestOptFuncDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTOPTFUNCDOC_H__A26A15CC_396B_43A9_AA63_33422F476B4B__INCLUDED_)
#define AFX_TESTOPTFUNCDOC_H__A26A15CC_396B_43A9_AA63_33422F476B4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestOptFuncDoc : public CDocument
{
protected: // create from serialization only
	CTestOptFuncDoc();
	DECLARE_DYNCREATE(CTestOptFuncDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestOptFuncDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestOptFuncDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestOptFuncDoc)
	afx_msg void OnTestStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOPTFUNCDOC_H__A26A15CC_396B_43A9_AA63_33422F476B4B__INCLUDED_)
