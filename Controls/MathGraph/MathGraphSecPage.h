#if !defined(AFX_MATHGRAPHSECPAGE_H__BDCC3AA6_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_)
#define AFX_MATHGRAPHSECPAGE_H__BDCC3AA6_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MathGraphSecPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMathGraphSecPage : Property page dialog

class CMathGraphSecPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMathGraphSecPage)
	DECLARE_OLECREATE_EX(CMathGraphSecPage)

// Constructors
public:
	CMathGraphSecPage();

// Dialog Data
	//{{AFX_DATA(CMathGraphSecPage)
	enum { IDD = IDD_SEC_PROPPAGE_MATHGRAPH };
	int		m_nGraphType;
	short	m_nXAxisVar;
	short	m_nYAxisVar;
	short	m_nZAxisVar;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMathGraphSecPage)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeSelected();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetSelection( int nSel );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHSECPAGE_H__BDCC3AA6_BE5F_11D1_AFF7_0000C03E618C__INCLUDED_)
