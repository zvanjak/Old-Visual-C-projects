// DlgTimeToReachSol.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"

#include "DlgTimeToReachSol.h"
#include "QAPCompareDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeToReachSol dialog


CDlgTimeToReachSol::CDlgTimeToReachSol(CQAPCompareDoc *inpDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTimeToReachSol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTimeToReachSol)
	m_nRepetitionNum = 0;
	//}}AFX_DATA_INIT

	pDoc = inpDoc; 

	m_strPar[0] = _T("");
	m_strPar[1] = _T("");
	m_strPar[2] = _T("");
	m_strPar[3] = _T("");

	m_strValues[0] = _T("");
	m_strValues[1] = _T("");
	m_strValues[2] = _T("");
	m_strValues[3] = _T("");
	
	m_fFrom[0] = 0.0f;
	m_fFrom[1] = 0.0f;
	m_fFrom[2] = 0.0f;
	m_fFrom[3] = 0.0f;

	m_fStep[0] = 0.0f;
	m_fStep[1] = 0.0f;
	m_fStep[2] = 0.0f;
	m_fStep[3] = 0.0f;

	m_fTo[0] = 0.0f;
	m_fTo[1] = 0.0f;
	m_fTo[2] = 0.0f;
	m_fTo[3] = 0.0f;

	m_ParNum = 0;
}


void CDlgTimeToReachSol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTimeToReachSol)
	DDX_Control(pDX, IDC_ALG_TYPE, m_ctrlSelAlgType);
	DDX_Text(pDX, IDC_REPETITION_NUM, m_nRepetitionNum);
	//}}AFX_DATA_MAP
	
	DDX_Text(pDX, IDC_PARNAME1, m_strPar[0]);
	DDX_Text(pDX, IDC_PARNAME2, m_strPar[1]);
	DDX_Text(pDX, IDC_PARNAME3, m_strPar[2]);
	DDX_Text(pDX, IDC_PARNAME4, m_strPar[3]);
	DDX_Text(pDX, IDC_PAR_VALUES1, m_strValues[0]);
	DDX_Text(pDX, IDC_PAR_VALUES2, m_strValues[1]);
	DDX_Text(pDX, IDC_PAR_VALUES3, m_strValues[2]);
	DDX_Text(pDX, IDC_PAR_VALUES4, m_strValues[3]);
	DDX_Text(pDX, IDC_RANGE_FROM1, m_fFrom[0]);
	DDX_Text(pDX, IDC_RANGE_FROM2, m_fFrom[1]);
	DDX_Text(pDX, IDC_RANGE_FROM3, m_fFrom[2]);
	DDX_Text(pDX, IDC_RANGE_FROM4, m_fFrom[3]);
	DDX_Text(pDX, IDC_RANGE_STEP1, m_fStep[0]);
	DDX_Text(pDX, IDC_RANGE_STEP2, m_fStep[1]);
	DDX_Text(pDX, IDC_RANGE_STEP3, m_fStep[2]);
	DDX_Text(pDX, IDC_RANGE_STEP4, m_fStep[3]);
	DDX_Text(pDX, IDC_RANGE_TO1, m_fTo[0]);
	DDX_Text(pDX, IDC_RANGE_TO2, m_fTo[1]);
	DDX_Text(pDX, IDC_RANGE_TO3, m_fTo[2]);
	DDX_Text(pDX, IDC_RANGE_TO4, m_fTo[3]);
}


BEGIN_MESSAGE_MAP(CDlgTimeToReachSol, CDialog)
	//{{AFX_MSG_MAP(CDlgTimeToReachSol)
	ON_CBN_SELCHANGE(IDC_ALG_TYPE, OnSelchangeAlgType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeToReachSol message handlers

BOOL CDlgTimeToReachSol::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlSelAlgType.AddString("Tabu search - simple");
	m_ctrlSelAlgType.AddString("Tabu search - simple diversifying");
	m_ctrlSelAlgType.AddString("Tabu search - robust");
	m_ctrlSelAlgType.AddString("Tabu search - robust diversifying");

//	m_ctrlSelAlgType.AddString("Simulated annealing");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTimeToReachSol::OnSelchangeAlgType() 
{
	switch( this->m_ctrlSelAlgType.GetCurSel() ) 
	{
		case 0 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "";
							m_strPar[2] = "";
							m_strPar[3] = "";
							
							m_ParNum = 1;

							break;
		case 1 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Aspiration T:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							
							break;
		case 2 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Delta t.l.size:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;

							break;
		case 3 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Delta t.l.size:";
							m_strPar[2] = "Aspiration T:";
							m_strPar[3] = "";

							m_ParNum = 3;
							break;
	}
	UpdateData(FALSE);
}
