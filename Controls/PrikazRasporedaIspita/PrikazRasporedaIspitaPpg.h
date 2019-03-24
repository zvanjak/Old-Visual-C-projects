#if !defined(AFX_PRIKAZRASPOREDAISPITAPPG_H__242D2D2D_4E87_4117_B394_899B8445CD56__INCLUDED_)
#define AFX_PRIKAZRASPOREDAISPITAPPG_H__242D2D2D_4E87_4117_B394_899B8445CD56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PrikazRasporedaIspitaPpg.h : Declaration of the CPrikazRasporedaIspitaPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaPropPage : See PrikazRasporedaIspitaPpg.cpp.cpp for implementation.

class CPrikazRasporedaIspitaPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPrikazRasporedaIspitaPropPage)
	DECLARE_OLECREATE_EX(CPrikazRasporedaIspitaPropPage)

// Constructor
public:
	CPrikazRasporedaIspitaPropPage();

// Dialog Data
	//{{AFX_DATA(CPrikazRasporedaIspitaPropPage)
	enum { IDD = IDD_PROPPAGE_PRIKAZRASPOREDAISPITA };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPrikazRasporedaIspitaPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIKAZRASPOREDAISPITAPPG_H__242D2D2D_4E87_4117_B394_899B8445CD56__INCLUDED)
