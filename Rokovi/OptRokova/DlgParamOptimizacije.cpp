// DlgParamOptimizacije.cpp : implementation file
//

#include "stdafx.h"
#include "OptRokova.h"
#include "DlgParamOptimizacije.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParamOptimizacije dialog


CDlgParamOptimizacije::CDlgParamOptimizacije(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamOptimizacije::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParamOptimizacije)
	m_dExpUdalj = 0.0;
	m_IterNum = 0;
	m_dKaznaPodrokovi = 0.0;
	m_nVelPop = 0;
	m_nMinDist = 0;
	m_nMinPresjek = 0;
	m_nMutacija = 0;
	m_dNagradaIstiDan = 0.0;
	m_nMaxOpterecNaGrupiPred = 0;
	m_dKaznaGrupaPred = 0.0;
	m_dKaznaMinDist = 0.0;
	m_dAmpBlizine = 0.0;
	m_dAmpPresjeka = 0.0;
	m_nMaxIspita = 0;
	m_dKaznaMaxIspita = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgParamOptimizacije::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParamOptimizacije)
	DDX_Text(pDX, IDC_EXP_UDALJ, m_dExpUdalj);
	DDV_MinMaxDouble(pDX, m_dExpUdalj, 0., 1.);
	DDX_Text(pDX, IDC_ITER_NUM, m_IterNum);
	DDV_MinMaxLong(pDX, m_IterNum, 1, 1500000);
	DDX_Text(pDX, IDC_KAZNA_PODROKOVI, m_dKaznaPodrokovi);
	DDV_MinMaxDouble(pDX, m_dKaznaPodrokovi, 0., 500000.);
	DDX_Text(pDX, IDC_VEL_POP, m_nVelPop);
	DDV_MinMaxInt(pDX, m_nVelPop, 10, 200);
	DDX_Text(pDX, IDC_MIN_DIST, m_nMinDist);
	DDV_MinMaxInt(pDX, m_nMinDist, 5, 15);
	DDX_Text(pDX, IDC_MIN_PRESJEK, m_nMinPresjek);
	DDV_MinMaxInt(pDX, m_nMinPresjek, 1, 10000);
	DDX_Text(pDX, IDC_MUTACIJA, m_nMutacija);
	DDV_MinMaxInt(pDX, m_nMutacija, 2000, 100000);
	DDX_Text(pDX, IDC_NAGRADA_ISTI_DAN, m_dNagradaIstiDan);
	DDV_MinMaxDouble(pDX, m_dNagradaIstiDan, 0., 500000.);
	DDX_Text(pDX, IDC_MAX_OPTEREC_GRUPA_PRED, m_nMaxOpterecNaGrupiPred);
	DDV_MinMaxInt(pDX, m_nMaxOpterecNaGrupiPred, 1, 10000);
	DDX_Text(pDX, IDC_KAZNA_MAX_OPTEREC_GRUPA_PRED, m_dKaznaGrupaPred);
	DDX_Text(pDX, IDC_KAZNA_MIN_DIST, m_dKaznaMinDist);
	DDX_Text(pDX, IDC_AMP_BLIZINE, m_dAmpBlizine);
	DDX_Text(pDX, IDC_AMP_PRESJEK, m_dAmpPresjeka);
	DDX_Text(pDX, IDC_MAX_ISP, m_nMaxIspita);
	DDV_MinMaxInt(pDX, m_nMaxIspita, 1, 50);
	DDX_Text(pDX, IDC_KAZNA_MAX_ISP, m_dKaznaMaxIspita);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParamOptimizacije, CDialog)
	//{{AFX_MSG_MAP(CDlgParamOptimizacije)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParamOptimizacije message handlers
