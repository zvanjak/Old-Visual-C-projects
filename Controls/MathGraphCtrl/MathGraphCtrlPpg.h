#if !defined(AFX_MATHGRAPHCTRLPPG_H__945B8415_14C0_11D2_9154_00C0DFE52874__INCLUDED_)
#define AFX_MATHGRAPHCTRLPPG_H__945B8415_14C0_11D2_9154_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraphCtrlPpg.h : Declaration of the CMathGraphCtrlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrlPropPage : See MathGraphCtrlPpg.cpp.cpp for implementation.

class CMathGraphCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMathGraphCtrlPropPage)
	DECLARE_OLECREATE_EX(CMathGraphCtrlPropPage)

// Constructor
public:
	CMathGraphCtrlPropPage();

// Dialog Data
	//{{AFX_DATA(CMathGraphCtrlPropPage)
	enum { IDD = IDD_PROPPAGE_MATHGRAPHCTRL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMathGraphCtrlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHCTRLPPG_H__945B8415_14C0_11D2_9154_00C0DFE52874__INCLUDED)
