//{{AFX_INCLUDES()
#include "prikazrasporedaispita.h"
//}}AFX_INCLUDES
#if !defined(AFX_TESTFUNCDLG_H__16A21C7C_B68B_4F91_9EE3_DF189A748CBA__INCLUDED_)
#define AFX_TESTFUNCDLG_H__16A21C7C_B68B_4F91_9EE3_DF189A748CBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestFuncDlg.h : header file
//

class	QAPSchedCromWrapper {
public:
	QAPSchedCromWrapper() { p = NULL; }
	~QAPSchedCromWrapper() { if( p!=NULL ) delete p; }

	void operator=( QAPScheduleCrom *a ) { p = a; }
	void operator=( QAPScheduleCrom &a ) 
		{
			if( p!= NULL )
				delete p;

			p	 = new QAPScheduleCrom(a.N(), a.L(), a.M());
			*p = a;
		}

	QAPScheduleCrom	*p;
};

/////////////////////////////////////////////////////////////////////////////
// CTestFuncDlg dialog

class CTestFuncDlg : public CDialog, public HasRefreshData
{
// Construction
public:
	CTestFuncDlg(CWnd* pParent = NULL);   // standard constructor
	~CTestFuncDlg();

	void	RefreshData( OptResults *res );
	void	Optim();

// Dialog Data
	//{{AFX_DATA(CTestFuncDlg)
	enum { IDD = IDD_TEST };
	CButton	m_ctrlCheckLin;
	CButton	m_ctrlCheckPow;
	CButton	m_ctrlCheckExp;
	CButton	m_ctrlCheckEqual;
	CPrikazRasporedaIspita	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestFuncDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestFuncDlg)
	afx_msg void OnStart();
	afx_msg void OnSetCoeficients();
	afx_msg void OnCheckEqual();
	afx_msg void OnCheckPow();
	afx_msg void OnCheckExp();
	afx_msg void OnRowSelectedList(short RowNum);
	afx_msg void OnColSelectedList(short ColNum);
	afx_msg void OnTermSelectedList(short RowNum, short ColNum);
	afx_msg void OnCheckLincut();
	afx_msg void OnShowBestCrom();
	afx_msg void OnShowGraph();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	QAPScheduleGenetic		*pQAP;

	// kromosomi za analizu
	QAPScheduleCrom		*pBestTotal;			// ukupno najbolja jedinka koja se pojavila tijekom optimizacije
	int								BestInd;					// indeks najbolje jedinke

	QAPScheduleCrom		*pCurrSolution;		// jedinka koja je trenutno prikazana na ekranu

	vector< vector<QAPSchedCromWrapper> >	matSolEvol;
	bool	bIsAllocated;

	int SubPeriodNum;
	int TermNum;
	int ExamNum;

	long		IterNum;
	double	MutProb;
	int			PopSize;

	enum { EQUAL_DIST, LINEAR_CUT, POW_DIST, EXP_DIST } DistType;
	double		CutPoint;
	double		LinCoef;
	double		Pow;
	double		X0;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTFUNCDLG_H__16A21C7C_B68B_4F91_9EE3_DF189A748CBA__INCLUDED_)
