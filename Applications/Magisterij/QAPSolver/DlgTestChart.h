//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGTESTCHART_H__F140F290_B990_475C_ABF3_1D1A7DF2792B__INCLUDED_)
#define AFX_DLGTESTCHART_H__F140F290_B990_475C_ABF3_1D1A7DF2792B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTestChart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTestChart dialog

class CDlgTestChart : public CDialog
{
// Construction
public:
	CDlgTestChart(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTestChart)
	enum { IDD = IDD_TEST_3DCHART };
	CMSChart	m_ctrlChart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestChart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTestChart)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTCHART_H__F140F290_B990_475C_ABF3_1D1A7DF2792B__INCLUDED_)
