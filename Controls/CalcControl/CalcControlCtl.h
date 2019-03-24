#if !defined(AFX_CALCCONTROLCTL_H__6C265408_F934_11D1_913A_00C0DFE52874__INCLUDED_)
#define AFX_CALCCONTROLCTL_H__6C265408_F934_11D1_913A_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CalcControlCtl.h : Declaration of the CCalcControlCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CCalcControlCtrl : See CalcControlCtl.cpp for implementation.

class CCalcControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCalcControlCtrl)

// Constructor
public:
	CCalcControlCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcControlCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CCalcControlCtrl();

	DECLARE_OLECREATE_EX(CCalcControlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCalcControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCalcControlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCalcControlCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CCalcControlCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCalcControlCtrl)
	afx_msg double Calc(LPCTSTR szLine);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCalcControlCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCalcControlCtrl)
	dispidCalc = 1L,
	//}}AFX_DISP_ID
	};
private:
	MathSpace		Mth;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCCONTROLCTL_H__6C265408_F934_11D1_913A_00C0DFE52874__INCLUDED)
