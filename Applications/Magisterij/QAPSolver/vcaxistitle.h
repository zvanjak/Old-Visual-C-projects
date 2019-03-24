#if !defined(AFX_VCAXISTITLE_H__BC98B3E5_30C0_42D5_9C22_46E43BAD9EDA__INCLUDED_)
#define AFX_VCAXISTITLE_H__BC98B3E5_30C0_42D5_9C22_46E43BAD9EDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcBackdrop;
class CVcFont;
class CVcTextLayout;
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CVcAxisTitle wrapper class

class CVcAxisTitle : public COleDispatchDriver
{
public:
	CVcAxisTitle() {}		// Calls COleDispatchDriver default constructor
	CVcAxisTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcAxisTitle(const CVcAxisTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CVcBackdrop GetBackdrop();
	CVcFont GetVtFont();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CVcTextLayout GetTextLayout();
	short GetTextLength();
	void SetRefFont(LPDISPATCH newValue);
	COleFont GetFont();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCAXISTITLE_H__BC98B3E5_30C0_42D5_9C22_46E43BAD9EDA__INCLUDED_)
