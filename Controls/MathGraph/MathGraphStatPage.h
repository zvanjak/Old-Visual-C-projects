#if !defined(AFX_MATHGRAPHSTATPAGE_H__BDCC3AA9_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_)
#define AFX_MATHGRAPHSTATPAGE_H__BDCC3AA9_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MathGraphStatPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMathGraphStatPage : Property page dialog

class CMathGraphStatPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMathGraphStatPage)
	DECLARE_OLECREATE_EX(CMathGraphStatPage)

// Constructors
public:
	CMathGraphStatPage();

// Dialog Data
	//{{AFX_DATA(CMathGraphStatPage)
	enum { IDD = IDD_STAT_PROPPAGE_MATHGRAPH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMathGraphStatPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHSTATPAGE_H__BDCC3AA9_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_)
