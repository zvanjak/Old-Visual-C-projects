// DBOptimDoc.h : interface of the CDBOptimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBOPTIMDOC_H__AD479044_A917_449A_BB1C_84F80FE37D5F__INCLUDED_)
#define AFX_DBOPTIMDOC_H__AD479044_A917_449A_BB1C_84F80FE37D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DBOptimSet.h"


//##ModelId=39571A29034A
class CDBOptimDoc : public CDocument
{
protected: // create from serialization only
	//##ModelId=39571A290389
	CDBOptimDoc();
	DECLARE_DYNCREATE(CDBOptimDoc)

// Attributes
public:
	//##ModelId=39571A290368
	CDBOptimSet m_dBOptimSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBOptimDoc)
	public:
	//##ModelId=39571A290388
	virtual BOOL OnNewDocument();
	//##ModelId=39571A29037D
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A29037C
	virtual ~CDBOptimDoc();
#ifdef _DEBUG
	//##ModelId=39571A290374
	virtual void AssertValid() const;
	//##ModelId=39571A290372
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBOptimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDBOptimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBOPTIMDOC_H__AD479044_A917_449A_BB1C_84F80FE37D5F__INCLUDED_)
