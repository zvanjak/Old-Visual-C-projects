// DlgViewGraphResults.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"

#include "DlgViewGraphResults.h"
#include "DlgViewResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewGraphResults dialog


CDlgViewGraphResults::CDlgViewGraphResults(CDlgViewResults *inOwner, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewGraphResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewGraphResults)
	//}}AFX_DATA_INIT

	Create(IDD_VIEW_GRAPH_RESULTS, pParent );
	pOwner = inOwner;
}


void CDlgViewGraphResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewGraphResults)
	DDX_Control(pDX, IDC_DRAW_METAFILE, m_ctrlDrawMetaile);
	DDX_Control(pDX, IDC_CTRL_GRAPH, m_ctrlGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewGraphResults, CDialog)
	//{{AFX_MSG_MAP(CDlgViewGraphResults)
	ON_BN_CLICKED(IDC_DRAW_METAFILE, OnDrawMetafile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewGraphResults message handlers

void CDlgViewGraphResults::OnCancel() 
{
	if( pOwner != NULL )
		pOwner->ChildClosed(this);

	DestroyWindow();
}

void CDlgViewGraphResults::PostNcDestroy() 
{
	delete this;	
//	CDialog::PostNcDestroy();
}

void CDlgViewGraphResults::OnDrawMetafile() 
{
	CFileDialog	dlg(TRUE);

	if( dlg.DoModal() == IDOK )
	{
		m_ctrlGraph.DrawtToMetafile(dlg.GetPathName(), 1000, 650);
	}
}

void CDlgViewGraphResults::OnOK() 
{
	if( pOwner != NULL )
		pOwner->ChildClosed(this);

	CDialog::OnOK();
}
