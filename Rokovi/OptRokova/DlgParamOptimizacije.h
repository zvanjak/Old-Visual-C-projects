#if !defined(AFX_DLGPARAMOPTIMIZACIJE_H__85982E37_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
#define AFX_DLGPARAMOPTIMIZACIJE_H__85982E37_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParamOptimizacije.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgParamOptimizacije dialog

class CDlgParamOptimizacije : public CDialog
{
// Construction
public:
	CDlgParamOptimizacije(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParamOptimizacije)
	enum { IDD = IDD_PARAMETRI_OPTIMIZACIJE };
	double	m_dExpUdalj;
	long	m_IterNum;
	double	m_dKaznaPodrokovi;
	int		m_nVelPop;
	int		m_nMinDist;
	int		m_nMinPresjek;
	int		m_nMutacija;
	double	m_dNagradaIstiDan;
	int		m_nMaxOpterecNaGrupiPred;
	double	m_dKaznaGrupaPred;
	double	m_dKaznaMinDist;
	double	m_dAmpBlizine;
	double	m_dAmpPresjeka;
	int		m_nMaxIspita;
	double	m_dKaznaMaxIspita;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParamOptimizacije)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParamOptimizacije)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARAMOPTIMIZACIJE_H__85982E37_6A98_11D3_A9AF_00C0DFE5278A__INCLUDED_)
