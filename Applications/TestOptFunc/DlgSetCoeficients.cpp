// DlgSetCoeficients.cpp : implementation file
//

#include "stdafx.h"
#include "TestOptFunc.h"
#include "DlgSetCoeficients.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetCoeficients dialog


CDlgSetCoeficients::CDlgSetCoeficients(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetCoeficients::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetCoeficients)
	m_ctrlExamNum = 0;
	m_ctrlIterNum = 0;
	m_ctrlMutProb = 0.0;
	m_ctrlPopSize = 0;
	m_ctrlSubperiodNum = 0;
	m_ctrlTermNum = 0;
	m_ctrlX0 = 0.0;
	m_ctrlExp = 0.0;
	m_ctrlCutPoint = 0.0;
	m_ctrlLinCoef = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgSetCoeficients::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetCoeficients)
	DDX_Text(pDX, IDC_EDIT_EXAMNUM, m_ctrlExamNum);
	DDV_MinMaxInt(pDX, m_ctrlExamNum, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_ITERNUM, m_ctrlIterNum);
	DDV_MinMaxLong(pDX, m_ctrlIterNum, 1, 2000000);
	DDX_Text(pDX, IDC_EDIT_MUTPROB, m_ctrlMutProb);
	DDV_MinMaxDouble(pDX, m_ctrlMutProb, 1.e-006, 1.);
	DDX_Text(pDX, IDC_EDIT_POPSIZE, m_ctrlPopSize);
	DDV_MinMaxInt(pDX, m_ctrlPopSize, 1, 500);
	DDX_Text(pDX, IDC_EDIT_SUBPERIODNUM, m_ctrlSubperiodNum);
	DDV_MinMaxInt(pDX, m_ctrlSubperiodNum, 1, 100);
	DDX_Text(pDX, IDC_EDIT_TERMNUM, m_ctrlTermNum);
	DDV_MinMaxInt(pDX, m_ctrlTermNum, 1, 100);
	DDX_Text(pDX, IDC_EDIT_X0, m_ctrlX0);
	DDX_Text(pDX, IDC_EDIT_EXP, m_ctrlExp);
	DDV_MinMaxDouble(pDX, m_ctrlExp, 1.e-005, 10.);
	DDX_Text(pDX, IDC_EDIT_CUT_POINT, m_ctrlCutPoint);
	DDX_Text(pDX, IDC_EDIT_LIN_COEF, m_ctrlLinCoef);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetCoeficients, CDialog)
	//{{AFX_MSG_MAP(CDlgSetCoeficients)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetCoeficients message handlers
