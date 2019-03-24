//{{AFX_INCLUDES()
#include "graph.h"
#include "simplegraph.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGVIEWGRAPHRESULTS_H__EE5029CC_58E6_4708_B9A4_92B7FBBB39C5__INCLUDED_)
#define AFX_DLGVIEWGRAPHRESULTS_H__EE5029CC_58E6_4708_B9A4_92B7FBBB39C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewGraphResults.h : header file
//

class CDlgViewResults;

/////////////////////////////////////////////////////////////////////////////
// CDlgViewGraphResults dialog

class CDlgViewGraphResults : public CDialog
{
// Construction
public:
	CDlgViewGraphResults(CDlgViewResults *inOwner, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewGraphResults)
	enum { IDD = IDD_VIEW_GRAPH_RESULTS };
	CButton	m_ctrlDrawMetaile;
	CSimpleGraph	m_ctrlGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewGraphResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgViewResults *pOwner;

public:
	// kada se zatvori dijalog rezultata, on svakom otvorenom dijalogu prikaza grafa
	// šalje ovu poruku kako bi oni znali da više ne postoji
	void OwnerClosed() { pOwner = NULL; }

	// Generated message map functions
	//{{AFX_MSG(CDlgViewGraphResults)
	virtual void OnCancel();
	afx_msg void OnDrawMetafile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWGRAPHRESULTS_H__EE5029CC_58E6_4708_B9A4_92B7FBBB39C5__INCLUDED_)
