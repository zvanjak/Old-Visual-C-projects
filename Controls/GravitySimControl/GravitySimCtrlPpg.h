#if !defined(AFX_GRAVITYSIMCTRLPPG_H__0566A588_C260_11D2_9649_00C0DFE5278A__INCLUDED_)
#define AFX_GRAVITYSIMCTRLPPG_H__0566A588_C260_11D2_9649_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GravitySimCtrlPpg.h : Declaration of the CGravitySimCtrlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrlPropPage : See GravitySimCtrlPpg.cpp.cpp for implementation.

class CGravitySimCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGravitySimCtrlPropPage)
	DECLARE_OLECREATE_EX(CGravitySimCtrlPropPage)

// Constructor
public:
	CGravitySimCtrlPropPage();

// Dialog Data
	//{{AFX_DATA(CGravitySimCtrlPropPage)
	enum { IDD = IDD_PROPPAGE_GRAVITYSIMCTRL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGravitySimCtrlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVITYSIMCTRLPPG_H__0566A588_C260_11D2_9649_00C0DFE5278A__INCLUDED)
