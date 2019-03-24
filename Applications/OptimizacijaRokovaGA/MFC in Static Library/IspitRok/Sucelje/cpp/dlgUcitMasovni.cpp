#include "..\h\Sucelje.h"


BEGIN_MESSAGE_MAP(CWndUcitMasovnoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NASTAV_PLAN, OnNastavniPlan)
	ON_BN_CLICKED(IDC_BUTTON_PRESJEK, OnPresjek)
END_MESSAGE_MAP()

CWndUcitMasovnoDlg::CWndUcitMasovnoDlg(CWnd* pParent) 
: CDialog(CWndUcitMasovnoDlg::IDD, pParent)
{}

void CWndUcitMasovnoDlg::OnOK() 
{
	
	CDialog::OnOK();
}

BOOL CWndUcitMasovnoDlg::OnInitDialog()
{
	ucit_1 = 0;
	ucit_2 = 0;
	return TRUE;
}

void CWndUcitMasovnoDlg::OnNastavniPlan() 
{
   CString sFilter = 
      "Sve Datoteke (*.*)|*.*||";
 
   CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | 
      OFN_FILEMUSTEXIST, (LPCTSTR)sFilter, this);

   
   if (IDCANCEL == dlgOpen.DoModal())
      return;

   
	ime_1 -> Format(dlgOpen.GetPathName());
   
	ucit_1 = 1;
}
void CWndUcitMasovnoDlg::OnPresjek() 
{
   CString sFilter = 
      "SveDatoteke (*.*)|*.*||";
 
  
   CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | 
      OFN_FILEMUSTEXIST, (LPCTSTR)sFilter, this);

   
   if (IDCANCEL == dlgOpen.DoModal())
      return;

  
	ime_2 -> Format(dlgOpen.GetPathName());
	ucit_2 = 1;
}