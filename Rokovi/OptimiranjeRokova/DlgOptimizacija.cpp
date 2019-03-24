// DlgOptimizacija.cpp : implementation file
//

#include "stdafx.h"
#include "OptimiranjeRokova.h"
#include "DlgOptimizacija.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizacija dialog


CDlgOptimizacija::CDlgOptimizacija(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptimizacija::IDD, pParent)
{
	Create(IDD_OPTIMIZACIJA, pParent );

//	m_ctrlVScroll.GetWindowRect(&rect);
//	m_ctrlVScroll.MoveWindow(m_nWndWidth-rect.Width()-10, Y0, rect.Width(), rect.Height() );

	m_nScrollBarOldPos = 0;

	m_ctrlVScroll.SetMin(0);
	m_ctrlVScroll.SetMax(100);
	m_ctrlVScroll.SetSmallChange(1);
	m_ctrlVScroll.SetLargeChange(35);

	//{{AFX_DATA_INIT(CDlgOptimizacija)
	//}}AFX_DATA_INIT
}


void CDlgOptimizacija::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptimizacija)
	DDX_Control(pDX, IDC_PRIKAZRASPOREDAISPITACTRL1, m_ctrlPrikaz);
	DDX_Control(pDX, IDC_SCROLLBAR, m_ctrlVScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptimizacija, CDialog)
	//{{AFX_MSG_MAP(CDlgOptimizacija)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptimizacija message handlers

BEGIN_EVENTSINK_MAP(CDlgOptimizacija, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgOptimizacija)
	ON_EVENT(CDlgOptimizacija, IDC_SCROLLBAR, 2 /* Change */, OnChangeScrollbar, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgOptimizacija::OnChangeScrollbar() 
{
	int		i, NewPos, Diff;

	NewPos = m_ctrlVScroll.GetValue();
	Diff = NewPos - m_nScrollBarOldPos;

	if( Diff > 0 ) {
		for( i=0; i<Diff; i++ )
			m_ctrlPrikaz.MoveDown();
	}
	else if( Diff < 0 )
		for( i=0; i>Diff; i-- )
			m_ctrlPrikaz.MoveUp();
	
	m_nScrollBarOldPos = NewPos;
}
