// VarInsertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "expresion.h"
#include "VarInsertDlg.h"
#include "ExpValue.h"
#include "VarValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarInsertDlg dialog


CVarInsertDlg::CVarInsertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVarInsertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVarInsertDlg)
	m_VarName = _T("");
	m_VarStrValue = _T("");
	m_bExpression = FALSE;
	//}}AFX_DATA_INIT
}


void CVarInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVarInsertDlg)
	DDX_Control(pDX, IDC_LIST1, m_VariableListCtrl);
	DDX_Text(pDX, IDC_VARNAME_EDIT, m_VarName);
	DDX_Text(pDX, IDC_VARVLUE_EDIT, m_VarStrValue);
	DDX_Check(pDX, IDC_CHECK1, m_bExpression);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVarInsertDlg, CDialog)
	//{{AFX_MSG_MAP(CVarInsertDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnInsertVar)
	ON_BN_CLICKED(IDC_BUTTON3, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVarInsertDlg message handlers

void CVarInsertDlg::OnInsertVar() 
{
	// TODO: Add your control notification handler code here
	// Insert a variable in the var map
	UpdateData();	
	if (m_bExpression)
		{
			// This is a expression
			CExpression *expresie = new CExpression(m_pVarsMap);
			expresie->ChangeExpression(m_VarStrValue);
			CExpValue *value = new CExpValue;
			value->SetValue(expresie);
			(*m_pVarsMap)[m_VarName] = value;
		}
		else
		{
			// It's a numeric value
			CNumericValue *value = new CNumericValue;
			value->SetValue(atof(m_VarStrValue));
			(*m_pVarsMap)[m_VarName] = value;
		}
		UpdateVarMapList();
}

void CVarInsertDlg::UpdateVarMapList()
{
	// Delete all Items
	m_VariableListCtrl.DeleteAllItems();
	
	// Parsing the car list and inserting to the control
	
	POSITION pos = m_pVarsMap->GetStartPosition();
	while (pos != NULL)
	{
		CString sName;
		CValue *pVal;
		m_pVarsMap->GetNextAssoc (pos, sName, pVal);
	

		LV_ITEM lvitem;
		lvitem.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM;
		lvitem.pszText = (LPSTR)(LPCSTR)sName;
		lvitem.state = LVIS_FOCUSED | LVIS_SELECTED;
		lvitem.iSubItem = 0;
		lvitem.iItem = 0;
		long index = m_VariableListCtrl.InsertItem(&lvitem);
		CString sVal;
		sVal.Format("%.3f",pVal->GetValue());
		m_VariableListCtrl.SetItemText(index, 1, (LPSTR)(LPCTSTR)sVal);
	}
	m_VariableListCtrl.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
}

BOOL CVarInsertDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString buf;
	buf.Format(IDS_VARLIST_COL1);
	m_VariableListCtrl.InsertColumn(0, (LPCTSTR)buf, LVCFMT_LEFT, 150, 0);
	buf.Format(IDS_VARLIST_COL2);
	m_VariableListCtrl.InsertColumn(1, (LPCTSTR)buf, LVCFMT_LEFT, 150, 1);	
	UpdateVarMapList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVarInsertDlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	long index = m_VariableListCtrl.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED);
	// Hey there is no car selected
	if (index < 0)
		return ;
	CString sName = m_VariableListCtrl.GetItemText (index, 0);
	m_pVarsMap->RemoveKey (sName);
	UpdateVarMapList();
}
