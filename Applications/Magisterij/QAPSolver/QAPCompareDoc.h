#if !defined(AFX_QAPCOMPAREDOC_H__E9FC3263_44DA_4E6E_A40F_C8CC55A4BD58__INCLUDED_)
#define AFX_QAPCOMPAREDOC_H__E9FC3263_44DA_4E6E_A40F_C8CC55A4BD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QAPCompareDoc.h : header file
//

#include <vector>
#include <Mathlib\Matrix.h>

#include <QAP\QAP.h>
#include <Optimization\Optimization.h>

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareDoc document
class CQAPCompareDoc : public CDocument
{
protected:
	CQAPCompareDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQAPCompareDoc)

// Attributes
public:

private:
	CString		strSize[10];
	CString		strFileName[10];

	// da li je uopæe problem definiran
	std::vector< BOOL >		vecProblemDefined;

	std::vector< Math::Matrix<float> >  vecA;
	std::vector< Math::Matrix<float> >  vecB;

	std::vector< QAPSolution >	vecBestKnownSol;
	std::vector< BOOL	>					vecBestKnownSolLoaded;


	std::vector< IterOptContResWithSolutions<float, QAPSolution> >	vecSol;
	std::vector< AlgDescription >	vecAlgDesc;

	char	fileProblem[10][50];
	char	fileSol[10][50];
	int		size[10];
	float	time[10];

	friend class	CDlgSetProblemInstances;
	friend class	CDlgAlgDepQualityOfSolution;
	friend class	CDlgTimeToReachSol;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAPCompareDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQAPCompareDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQAPCompareDoc)
	afx_msg void OnSetProblemInstances();
	afx_msg void OnAlgDepTimeToReachSolution();
	afx_msg void OnAlgDepQualityOfSolution();
	afx_msg void OnCompareTabuSearch();
	afx_msg void OnCompareSimAnn();
	afx_msg void OnCompareGenetic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QAPCOMPAREDOC_H__E9FC3263_44DA_4E6E_A40F_C8CC55A4BD58__INCLUDED_)
