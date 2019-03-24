// SchEqDoc.h : interface of the CSchEqDoc class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SCHEQDOC_H__AAAA81F1_B1B6_427F_B529_34510A9E3AA6__INCLUDED_)
#define AFX_SCHEQDOC_H__AAAA81F1_B1B6_427F_B529_34510A9E3AA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

#include <Mathlib\Mathlib.h>

#include <Mathlib\Matrix.h>
#include <Mathlib\Vector.h>
#include <Mathlib\RootFinding.h>

#include <Mathlib\Function.h>
#include <Mathlib\ODEIntegration.h>

#include <Mathlib\BoundaryProblem.h>

class FinitePotHole {
public:
	FinitePotHole( float in_a1, float in_a2, float in_b1, float in_b2,
								 float inV0, float inE ) {
		a1 = in_a1;
		a2 = in_a2;
		b1 = in_b1;
		b2 = in_b2;
		
		V0 = inV0;
		E = inE;
	}
	float Potential( float x ) {
		if( x < a1 || x > a2 )
			return 3 * V0;							// odnosno beskonaèno
		else if( x > b1 && x < b2 )
			return V0;
		else
			return 0;
	}
	
	void derivs( float x, float y[], float dydx[] ) 
	{
		dydx[0] = y[1];
		dydx[1] = ( Potential(x) - E ) * y[0];
	}

	float		a1, a2, b1, b2;
	float		V0, E;
};


/*************************************************************************************/
/*************************************************************************************/

void IntFunc( double x, Vector<double> &y, Vector<double>	&dydx );

#define		POTFUNC_POINTS_NUM		300

class CSchEqDoc : public CDocument
{
protected: // create from serialization only
	CSchEqDoc();
	DECLARE_DYNCREATE(CSchEqDoc)

// Attributes
public:
	// Rezultati
	std::vector<double>	vecEnergy;

	std::vector< Vector<double> >	vecYStart1;
	std::vector< Vector<double> >	vecYStart2;

	std::vector< float * >		vecpXPsi;		// vektor apscisa
	std::vector< float * >		vecpYPsi;		// vektor ordinata
	std::vector< int >				vecPntNum;	// vektor ordinata
	std::vector< bool	>				vecAdded;		// vektor ordinata

	float		xPot[POTFUNC_POINTS_NUM];
	float		yPot[POTFUNC_POINTS_NUM];
	int			PotGraphID;
	bool		bPotAdded, bPotChanged;

	bool		bClearAll;

	int			GraphNum;

	// podaci o potencijalu
	float		a1, a2;
	float		b1, b2;
	float		V0;

	bool		bViewNumInt;

	QMPotentialWell		prob;

// Operations
public:
	float	CalcPerturbation1( int n );
	float CalcPerturbation2( int n );
	float	CalcPerturbStateFunc( int n, float x );

	void	ClearResults();
	void	SetPotentialData();

	bool	AddResult( double Energy, Vector<double> &Y1, Vector<double> &Y2, int n, float *X, float *Y );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchEqDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSchEqDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchEqDoc)
	afx_msg void OnDefineParameters();
	afx_msg void OnPerformIntegration();
	afx_msg void OnViewResults();
	afx_msg void OnViewOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEQDOC_H__AAAA81F1_B1B6_427F_B529_34510A9E3AA6__INCLUDED_)
