#if !defined(AFX_GRAPHPPG_H__106D39F8_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_)
#define AFX_GRAPHPPG_H__106D39F8_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GraphPpg.h : Declaration of the CGraphPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGraphPropPage : See GraphPpg.cpp.cpp for implementation.

class CGraphPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGraphPropPage)
	DECLARE_OLECREATE_EX(CGraphPropPage)

// Constructor
public:
	CGraphPropPage();

// Dialog Data
	//{{AFX_DATA(CGraphPropPage)
	enum { IDD = IDD_PROPPAGE_GRAPH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGraphPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPPG_H__106D39F8_C7AF_11D1_AFFE_0000C03E618C__INCLUDED)
