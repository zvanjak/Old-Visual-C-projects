#if !defined(AFX_SURFACEPLOTPPG_H__7E0D9EEC_075A_11D2_914A_00C0DFE52874__INCLUDED_)
#define AFX_SURFACEPLOTPPG_H__7E0D9EEC_075A_11D2_914A_00C0DFE52874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SurfacePlotPpg.h : Declaration of the CSurfacePlotPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSurfacePlotPropPage : See SurfacePlotPpg.cpp.cpp for implementation.

class CSurfacePlotPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSurfacePlotPropPage)
	DECLARE_OLECREATE_EX(CSurfacePlotPropPage)

// Constructor
public:
	CSurfacePlotPropPage();

// Dialog Data
	//{{AFX_DATA(CSurfacePlotPropPage)
	enum { IDD = IDD_PROPPAGE_SURFACEPLOT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSurfacePlotPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACEPLOTPPG_H__7E0D9EEC_075A_11D2_914A_00C0DFE52874__INCLUDED)
