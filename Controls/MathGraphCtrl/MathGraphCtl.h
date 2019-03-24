#if !defined(AFX_MATHGRAPHCTL_H__945B8413_14C0_11D2_9154_00C0DFE52874__INCLUDED_)
#define AFX_MATHGRAPHCTL_H__945B8413_14C0_11D2_9154_00C0DFE52874__INCLUDED_

#include "graph.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraphCtl.h : Declaration of the CMathGraphCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl : See MathGraphCtl.cpp for implementation.

class CMathGraphCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMathGraphCtrl)

	CGraph		m_ctrlGraph;

// Constructor
public:
	CMathGraphCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathGraphCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMathGraphCtrl();

	DECLARE_OLECREATE_EX(CMathGraphCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMathGraphCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMathGraphCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMathGraphCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMathGraphCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMathGraphCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMathGraphCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMathGraphCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHCTL_H__945B8413_14C0_11D2_9154_00C0DFE52874__INCLUDED)
