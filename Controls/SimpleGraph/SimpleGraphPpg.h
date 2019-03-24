#if !defined(AFX_SIMPLEGRAPHPPG_H__FC11F7A8_C88F_482A_A93E_FB90A62B432E__INCLUDED_)
#define AFX_SIMPLEGRAPHPPG_H__FC11F7A8_C88F_482A_A93E_FB90A62B432E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SimpleGraphPpg.h : Declaration of the CSimpleGraphPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSimpleGraphPropPage : See SimpleGraphPpg.cpp.cpp for implementation.

class CSimpleGraphPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSimpleGraphPropPage)
	DECLARE_OLECREATE_EX(CSimpleGraphPropPage)

// Constructor
public:
	CSimpleGraphPropPage();

// Dialog Data
	//{{AFX_DATA(CSimpleGraphPropPage)
	enum { IDD = IDD_PROPPAGE_SIMPLEGRAPH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSimpleGraphPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEGRAPHPPG_H__FC11F7A8_C88F_482A_A93E_FB90A62B432E__INCLUDED)
