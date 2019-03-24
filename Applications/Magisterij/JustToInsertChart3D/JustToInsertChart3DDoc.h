// JustToInsertChart3DDoc.h : interface of the CJustToInsertChart3DDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUSTTOINSERTCHART3DDOC_H__772B027C_F461_48E3_B71B_2143D657928C__INCLUDED_)
#define AFX_JUSTTOINSERTCHART3DDOC_H__772B027C_F461_48E3_B71B_2143D657928C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJustToInsertChart3DDoc : public CDocument
{
protected: // create from serialization only
	CJustToInsertChart3DDoc();
	DECLARE_DYNCREATE(CJustToInsertChart3DDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJustToInsertChart3DDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJustToInsertChart3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJustToInsertChart3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUSTTOINSERTCHART3DDOC_H__772B027C_F461_48E3_B71B_2143D657928C__INCLUDED_)
