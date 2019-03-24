// OptScheduleDoc.h : interface of the COptScheduleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTSCHEDULEDOC_H__6ED90403_6132_412C_973C_9D014DEC970D__INCLUDED_)
#define AFX_OPTSCHEDULEDOC_H__6ED90403_6132_412C_973C_9D014DEC970D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "QAPNew.h"

class COptScheduleDoc : public CDocument
{
protected: // create from serialization only
	COptScheduleDoc();
	DECLARE_DYNCREATE(COptScheduleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptScheduleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ViewData( ProblemData& );
	virtual ~COptScheduleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptScheduleDoc)
	afx_msg void OnDataView();
	afx_msg void OnDataViewModel();
	afx_msg void OnSetModelDescription();
	afx_msg void OnFileLoadExternalData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COptScheduleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	OptProblem	m_ProbData;

	IQAPSolver	*pQAPSolver;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTSCHEDULEDOC_H__6ED90403_6132_412C_973C_9D014DEC970D__INCLUDED_)
