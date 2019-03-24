//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIEWRESULTS_H__2F67CCED_56B5_4488_B200_40D23803D393__INCLUDED_)
#define AFX_DLGVIEWRESULTS_H__2F67CCED_56B5_4488_B200_40D23803D393__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewResults.h : header file
//

#include "QAPSolverDoc.h"
#include "DlgViewGraphResults.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults dialog

class CDlgViewResults : public CDialog
{
// Construction
public:
	CDlgViewResults(CQAPSolverDoc *inpDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewResults)
	enum { IDD = IDD_VIEW_RESULTS };
	CButton	m_ctrlUseColors;
	CButton	m_ctrlUseLineStyle;
	CButton	m_ctrlDeleteCmd;
	CButton	m_ctrlShowSame;
	CMSFlexGrid	m_ctrlRes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CQAPSolverDoc		*pDoc;

	// da li da za svaki graf koji želimo vidjeti otvori novi prozor (TRUE) ili ne(FALSE)
	bool		bShowGraphsInSameWnd;
	bool		bUseColors;
	bool		bUseLineStyle;

	// lista otvorenih dijaloga koji prikazuju grafove
	vector<CDlgViewGraphResults *>	vecGraphPtr;
	vector<int>											vecNum;

public:	
	// kada se DlgViewGraph zatvori, poslati æe ovu poruku dijalogu prikaza rezultata
	void ChildClosed(CDlgViewGraphResults *pDlg);

	void	RedrawAllGraphs();
	
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgViewResults)
	afx_msg void OnDblClickResults();
	virtual void OnCancel();
	afx_msg void OnShowInSame();
	afx_msg void OnDeleteOptResCmd();
	afx_msg void OnCheckUseColors();
	afx_msg void OnCheckUseLinestyles();
	afx_msg void OnPopupShowGraph();
	afx_msg void OnPopupViewSolution();
	afx_msg void OnMouseDownResults(short Button, short Shift, long x, long y);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWRESULTS_H__2F67CCED_56B5_4488_B200_40D23803D393__INCLUDED_)
