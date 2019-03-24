// QAPSolverDoc.h : interface of the CQAPSolverDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QAPSOLVERDOC_H__1D859EB6_4671_401F_A6E3_4C8454D9AE8C__INCLUDED_)
#define AFX_QAPSOLVERDOC_H__1D859EB6_4671_401F_A6E3_4C8454D9AE8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

#include <Mathlib\Matrix.h>
#include <QAP\QAP.h>
#include <Optimization\Optimization.h>

class CDlgViewResults;

class CQAPSolverDoc : public CDocument, public ISaveResultObject<float, QAPSolution>
{
public:
	CQAPSolverDoc();		// prebaèeno iz protected
protected: // create from serialization only
	DECLARE_DYNCREATE(CQAPSolverDoc)

// Attributes
public:

private:
	int			nProblemSize;
	Math::Matrix<float>		*A;
	Math::Matrix<float>		*B;

	bool		bDataLoaded;

public:
	std::vector< IterOptContResWithSolutions<float, QAPSolution> >	vecSol;
	std::vector< AlgDescription >	vecAlgDesc;

	bool					bBestSolutionLoaded;
	QAPSolution		BestKnownSolution;

// Operations
public:
	int		getProblemSize() { return nProblemSize; }
	void	setProblemSize( int inProblemSize ) { nProblemSize = inProblemSize; }
	
	Math::Matrix<float>		*getA() { return A;}
	Math::Matrix<float>		*getB() { return B;}

	void	ClearAllData();

	bool	AddOptResult( IterOptContResWithSolutions<float, QAPSolution> &res,
											AlgDescription	&alg );
	bool	DeleteOptimizationResult( int Index );
	void	FillDialogWithResults( CDlgViewResults *pDlg );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAPSolverDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQAPSolverDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CQAPSolverDoc)
	afx_msg void OnLoadProblemData();
	afx_msg void OnViewData();
	afx_msg void OnViewResults();
	afx_msg void OnLoadBestKnownSolution();
	afx_msg void OnViewBestSolution();
	afx_msg void OnTestChart();
	afx_msg void OnTestGeneric();
	afx_msg void OnTabuSearchRobustDiversify();
	afx_msg void OnTabuSearchSimple();
	afx_msg void OnTabuSearchSimpleDiversify();
	afx_msg void OnTabuSearchRobustSimple();
	afx_msg void OnStartOptimizationBrSimann();
	afx_msg void OnStartOptimizationAutSimAnn();
	afx_msg void OnStartOptimizationAutConnolySimAnn();
	afx_msg void OnStartOptimizationConnolySimAnn();
	afx_msg void OnStartOptimizationWWSimAnn();
	afx_msg void OnStartOptimization3TournamentSelection();
	afx_msg void OnStartOptimizationFirstImprovement();
	afx_msg void OnStartOptimizationBestImprovement();
	afx_msg void OnStartOptimizationHeider();
	afx_msg void OnStartOptimizationGrasp();
	afx_msg void OnStartOptimizationFFGA();
	afx_msg void OnStartOptimizationGreedyGA();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CQAPSolverDoc*	OpenDoc( LPCTSTR lpszPathName);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QAPSOLVERDOC_H__1D859EB6_4671_401F_A6E3_4C8454D9AE8C__INCLUDED_)
