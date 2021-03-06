#if !defined(AFX_TESTCONTROLEMPTY_H__B7C9A2CB_5E23_4F96_8F05_F110F2156803__INCLUDED_)
#define AFX_TESTCONTROLEMPTY_H__B7C9A2CB_5E23_4F96_8F05_F110F2156803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CTestControlEmpty wrapper class

class CTestControlEmpty : public CWnd
{
protected:
	DECLARE_DYNCREATE(CTestControlEmpty)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xac61cbde, 0x4407, 0x4f59, { 0x8b, 0x17, 0x9, 0xfd, 0x23, 0xdb, 0x1d, 0xbc } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCONTROLEMPTY_H__B7C9A2CB_5E23_4F96_8F05_F110F2156803__INCLUDED_)
