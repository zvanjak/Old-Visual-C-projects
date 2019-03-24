// OptRokDoc.h : interface of the COptRokDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTROKDOC_H__FEE671C7_9B8E_41F0_901B_714FF297CB8A__INCLUDED_)
#define AFX_OPTROKDOC_H__FEE671C7_9B8E_41F0_901B_714FF297CB8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QAP.h"

class COptRokDoc : public CDocument
{
protected: // create from serialization only
	COptRokDoc();
	DECLARE_DYNCREATE(COptRokDoc)

// Attributes
private:
	QAPScheduleGenetic		*m_Opt;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptRokDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptRokDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COptRokDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COptRokDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTROKDOC_H__FEE671C7_9B8E_41F0_901B_714FF297CB8A__INCLUDED_)
