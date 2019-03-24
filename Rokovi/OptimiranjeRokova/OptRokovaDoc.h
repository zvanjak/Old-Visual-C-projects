// OptRokovaDoc.h : interface of the COptRokovaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTROKOVADOC_H__74C12DC0_9870_4C71_B98A_BC1F280897B7__INCLUDED_)
#define AFX_OPTROKOVADOC_H__74C12DC0_9870_4C71_B98A_BC1F280897B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptProblem.h"

class COptRokovaDoc : public CDocument
{
protected: // create from serialization only
	COptRokovaDoc();
	DECLARE_DYNCREATE(COptRokovaDoc)

// Attributes
public:

	OptProblem		opt();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokovaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptRokovaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptRokovaDoc)
	afx_msg void OnOptimizacijaPokreni();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COptRokovaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKOVADOC_H__74C12DC0_9870_4C71_B98A_BC1F280897B7__INCLUDED_)
