#if !defined(AFX_SCROLLBAR_H__19A7B309_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_)
#define AFX_SCROLLBAR_H__19A7B309_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CScrollbar wrapper class

class CScrollbar : public CWnd
{
protected:
	DECLARE_DYNCREATE(CScrollbar)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xdfd181e0, 0x5e2f, 0x11ce, { 0xa4, 0x49, 0x0, 0xaa, 0x0, 0x4a, 0x80, 0x3d } };
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
	void SetBackColor(long nNewValue);
	long GetBackColor();
	void SetForeColor(long nNewValue);
	long GetForeColor();
	void SetEnabled(BOOL bNewValue);
	BOOL GetEnabled();
	void SetMousePointer(long nNewValue);
	long GetMousePointer();
	void SetValue(long nNewValue);
	long GetValue();
	void SetMin(long nNewValue);
	long GetMin();
	void SetMax(long nNewValue);
	long GetMax();
	void SetSmallChange(long nNewValue);
	long GetSmallChange();
	void SetLargeChange(long nNewValue);
	long GetLargeChange();
	void SetProportionalThumb(BOOL bNewValue);
	BOOL GetProportionalThumb();
	void SetOrientation(long nNewValue);
	long GetOrientation();
	void SetDelay(long nNewValue);
	long GetDelay();
	void SetMouseIcon(LPDISPATCH newValue);
	void SetRefMouseIcon(LPDISPATCH newValue);
	CPicture GetMouseIcon();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBAR_H__19A7B309_6B41_11D3_A9B0_00C0DFE5278A__INCLUDED_)