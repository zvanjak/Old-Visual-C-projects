// DlgViewResults.cpp : implementation file
//

#include "stdafx.h"
#include "SchroedingerEq.h"
#include "DlgViewResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults dialog


CDlgViewResults::CDlgViewResults(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgViewResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewResults)
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewResults, CDialog)
	//{{AFX_MSG_MAP(CDlgViewResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewResults message handlers

BOOL CDlgViewResults::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlList.InsertColumn(0, "Base energy", LVCFMT_LEFT, 150 );
	m_ctrlList.InsertColumn(1, "Num.integration", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(2, "Perturbation 1", LVCFMT_LEFT, 150 );
	m_ctrlList.InsertColumn(3, "Perturbation 2", LVCFMT_LEFT, 150 );
	
	m_ctrlList.SetColumnWidth(0, 130);
	m_ctrlList.SetColumnWidth(1, 130);
	m_ctrlList.SetColumnWidth(2, 130);
	m_ctrlList.SetColumnWidth(3, 130);

	CString		strText;
	float			diff;
	int				i;

	for( i=0; i<nLevelsNum; i++ ) {
		strText.Format("%f", pBase[i] );
		m_ctrlList.InsertItem(i, strText);
	}
	for( i=0; i<nLevelsNum; i++ ) {
		diff = (pNum[i] - pBase[i]) / pBase[i] * 100.f;
		strText.Format("%f (%5.2f)", pNum[i], diff );
		m_ctrlList.SetItemText(i,1,strText);

		diff = (pPerturb1[i] - pBase[i]) / pBase[i] * 100.f;
		strText.Format("%f (%5.2f)", pPerturb1[i], diff );
		m_ctrlList.SetItemText(i,2,strText);

		diff = (pPerturb2[i] - pBase[i]) / pBase[i] * 100.f;
		strText.Format("%f (%5.2f)", pPerturb2[i], diff );
		m_ctrlList.SetItemText(i,3,strText);
	}


	m_ctrlList2.InsertColumn(0, "Num.integration", LVCFMT_LEFT, 150);
	m_ctrlList2.InsertColumn(1, "Base energy", LVCFMT_LEFT, 150 );
	m_ctrlList2.InsertColumn(2, "Perturbation 1", LVCFMT_LEFT, 150 );
	m_ctrlList2.InsertColumn(3, "Perturbation 2", LVCFMT_LEFT, 150 );
	
	m_ctrlList2.SetColumnWidth(0, 130);
	m_ctrlList2.SetColumnWidth(1, 130);
	m_ctrlList2.SetColumnWidth(2, 130);
	m_ctrlList2.SetColumnWidth(3, 130);

	for( i=0; i<nLevelsNum; i++ ) {
		strText.Format("%f", pNum[i] );
		m_ctrlList2.InsertItem(i, strText);
	}
	for( i=0; i<nLevelsNum; i++ ) {
		diff = (pBase[i] - pNum[i]) / pNum[i] * 100.f;
		strText.Format("%f (%5.2f)", pBase[i], diff );
		m_ctrlList2.SetItemText(i,1,strText);

		diff = (pPerturb1[i] - pNum[i]) / pNum[i] * 100.f;
		strText.Format("%f (%5.2f)", pPerturb1[i], diff );
		m_ctrlList2.SetItemText(i,2,strText);

		diff = (pPerturb2[i] - pNum[i]) / pNum[i] * 100.f;
		strText.Format("%f (%5.2f)", pPerturb2[i], diff );
		m_ctrlList2.SetItemText(i,3,strText);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
