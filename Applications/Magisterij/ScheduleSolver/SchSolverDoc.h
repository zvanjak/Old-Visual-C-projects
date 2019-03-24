// SchSolverDoc.h : interface of the CSchSolverDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHSOLVERDOC_H__02BDC81E_C03D_465F_8AC2_170A3BDC097E__INCLUDED_)
#define AFX_SCHSOLVERDOC_H__02BDC81E_C03D_465F_8AC2_170A3BDC097E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//##ModelId=39571A970335
class CSchSolverDoc : public CDocument
{
protected: // create from serialization only
	//##ModelId=39571A970369
	CSchSolverDoc();
	DECLARE_DYNCREATE(CSchSolverDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchSolverDoc)
	public:
	//##ModelId=39571A970368
	virtual BOOL OnNewDocument();
	//##ModelId=39571A97035E
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=39571A97035D
	virtual ~CSchSolverDoc();
#ifdef _DEBUG
	//##ModelId=39571A970355
	virtual void AssertValid() const;
	//##ModelId=39571A970353
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchSolverDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSchSolverDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHSOLVERDOC_H__02BDC81E_C03D_465F_8AC2_170A3BDC097E__INCLUDED_)
