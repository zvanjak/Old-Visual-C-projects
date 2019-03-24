#if !defined(AFX_CALCCONTROLPPG_H__6C26540A_F934_11D1_913A_00C0DFE52874__INCLUDED_)
#define AFX_CALCCONTROLPPG_H__6C26540A_F934_11D1_913A_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CalcControlPpg.h : Declaration of the CCalcControlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CCalcControlPropPage : See CalcControlPpg.cpp.cpp for implementation.

class CCalcControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCalcControlPropPage)
	DECLARE_OLECREATE_EX(CCalcControlPropPage)

// Constructor
public:
	CCalcControlPropPage();

// Dialog Data
	//{{AFX_DATA(CCalcControlPropPage)
	enum { IDD = IDD_PROPPAGE_CALCCONTROL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CCalcControlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCCONTROLPPG_H__6C26540A_F934_11D1_913A_00C0DFE52874__INCLUDED)
