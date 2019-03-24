#if !defined(AFX_MATHGRAPHPPG_H__81936D39_BE53_11D1_AFF7_0000C03E618C__INCLUDED_)
#define AFX_MATHGRAPHPPG_H__81936D39_BE53_11D1_AFF7_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraphPpg.h : Declaration of the CMathGraphPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMathGraphPropPage : See MathGraphPpg.cpp.cpp for implementation.

class CMathGraphPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMathGraphPropPage)
	DECLARE_OLECREATE_EX(CMathGraphPropPage)

// Constructor
public:
	CMathGraphPropPage();

// Dialog Data
	//{{AFX_DATA(CMathGraphPropPage)
	enum { IDD = IDD_PROPPAGE_MATHGRAPH };
	CButton	m_ctrlNormLog;
	CButton	m_ctrlNormNorm;
	CButton	m_ctrlLogNorm;
	CButton	m_ctrlLogLog;
	CButton	m_ctrlSpher;
	CButton	m_ctrlCylind;
	CButton	m_ctrlCart;
	CString	m_strTitle;
	CString	m_strXAxis;
	CString	m_strYAxis;
	CString	m_strZAxis;
	BOOL	m_bUseColors;
	BOOL	m_bUseLineStyles;
	BOOL	m_bShowLegend;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMathGraphPropPage)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCartesian();
	afx_msg void OnCylindrical();
	afx_msg void OnSpherical();
	afx_msg void OnLogLog();
	afx_msg void OnLogNorm();
	afx_msg void OnNormLog();
	afx_msg void OnNormNorm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHPPG_H__81936D39_BE53_11D1_AFF7_0000C03E618C__INCLUDED)
