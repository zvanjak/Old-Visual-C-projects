#include "..\h\Sucelje.h"


BEGIN_MESSAGE_MAP(CWndFiksDlg, CDialog)

END_MESSAGE_MAP()

CWndFiksDlg::CWndFiksDlg(CWnd* pParent) 
: CDialog(CWndFiksDlg::IDD_F, pParent)
{
	
}

//dialoški okvir za uèitavanje datuma fiksiranih ispita
BOOL CWndFiksDlg::OnInitDialog() 
{
	
	ok = 0;

	CEdit* pEdit_1 = (CEdit*) this -> GetDlgItem(IDC_EDIT_ROK_1);
   if (!pEdit_1) 
      return -1;
	char temp[3];
	if(odabir)
	{
		_itoa(gran.dol_gran_rok_1, temp, 10);
		pEdit_1 -> SetWindowText(temp);
	}
	else
	{
		_itoa(rok_1, temp, 10);
		pEdit_1 -> SetWindowText(temp);
	}

	CEdit* pEdit_2 = (CEdit*) this -> GetDlgItem(IDC_EDIT_ROK_2);
	if (!pEdit_2) 
      return -1;
	if(odabir)
	{
		_itoa(gran.dol_gran_rok_2, temp, 10);
		pEdit_2 -> SetWindowText(temp);
	}
	else
	{
		_itoa(rok_2, temp, 10);
		pEdit_2 -> SetWindowText(temp);
	}

	CEdit* pEdit_3 = (CEdit*) this -> GetDlgItem(IDC_EDIT_ROK_3);
	if (!pEdit_3) 
      return -1;
	if(odabir)
	{
		_itoa(gran.dol_gran_rok_3, temp, 10);
		pEdit_3 -> SetWindowText(temp);
	}
	else
	{
		_itoa(rok_3, temp, 10);
		pEdit_3 -> SetWindowText(temp);
	}

	CEdit* pEdit_n = (CEdit*) this -> GetDlgItem(IDC_EDIT_NAZIV);
	if (!pEdit_n) 
      return -1;
	pEdit_n -> SetWindowText(zaporka);

	CEdit* pEdit_s = (CEdit*) this -> GetDlgItem(IDC_EDIT_SIFRA);
	if (!pEdit_s) 
      return -1;
	pEdit_s -> SetWindowText(zaporka);

	if(br_rok == 2)
		pEdit_3 -> EnableWindow(FALSE);
	else
	if(br_rok == 1)
	{
		pEdit_2 -> EnableWindow(FALSE);
		pEdit_3 -> EnableWindow(FALSE);
	}

	odabir = 1;

	return TRUE;
}




void CWndFiksDlg::OnOK() 
{
	ok = 1;
	CDialog::OnOK();
}

void CWndFiksDlg::DoDataExchange(CDataExchange* pDX)
{
	if(br_rok > 0)
	{
		DDX_Text(pDX, IDC_EDIT_ROK_1, rok_1);
		DDV_MinMaxUInt(pDX, rok_1, gran.dol_gran_rok_1, gran.gor_gran_rok_1);

		if(br_rok > 1)
		{
			DDX_Text(pDX, IDC_EDIT_ROK_2, rok_2);
			DDV_MinMaxUInt(pDX, rok_2, gran.dol_gran_rok_2, gran.gor_gran_rok_2);
		
			if(br_rok > 2)
			{
				DDX_Text(pDX, IDC_EDIT_ROK_3, rok_3);
				DDV_MinMaxUInt(pDX, rok_3, gran.dol_gran_rok_3, gran.gor_gran_rok_3);
			}
		}
	}

}

CWndGreskaDlg::CWndGreskaDlg(CWnd* pParent) 
: CDialog(CWndGreskaDlg::IDD, pParent)
{}

CWndGreska2Dlg::CWndGreska2Dlg(CWnd* pParent) 
: CDialog(CWndGreska2Dlg::IDD, pParent)
{}

CWndGreska3Dlg::CWndGreska3Dlg(CWnd* pParent) 
: CDialog(CWndGreska3Dlg::IDD, pParent)
{}

