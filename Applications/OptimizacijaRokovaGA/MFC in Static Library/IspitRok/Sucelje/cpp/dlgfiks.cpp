#include "..\h\Sucelje.h"


//dialoški okvir u kojemu se prikazuju kolegiji èiji ispiti fiksirani te oznake onih kolegija
//èiji se ispiti mogu fiksirati
BEGIN_MESSAGE_MAP(CKolegijDlg, CDialog)
	ON_COMMAND(IDC_BUTTON_PRIJENOS, OnButtonPrijenosClick)
	ON_COMMAND(IDC_BUTTON_DATUM, OnButtonDatumClick)
	ON_COMMAND(IDC_BUTTON_POBRISI, OnButtonBrisanjeClick)
	ON_LBN_DBLCLK(IDC_LIST_KOLEGIJI_FIKS, OnFiksListBoxDblClick)      
   ON_LBN_DBLCLK(IDC_LIST_KOLEGIJI, OnZaporListBoxDblClick)      
END_MESSAGE_MAP()

void CKolegijDlg::OnOK() 
{
	 CDialog::OnOK();
}



BOOL CKolegijDlg::OnInitDialog() 
{
	
	int i;

	char string[20];
	for(i = 0; i < br_ispit; i++)
	{
		_itoa(zapor_p[i], string, 10);
		if(LB_ERR == wndListBoxZapor().FindString(-1, string))
			wndListBoxZapor().AddString(string);	
	}//for i


	if(!data_valid_ucit)
	{
		if (wndListBoxFiks().GetCount())  
			wndListBoxFiks().ResetContent();
		int* sif_polj = NULL;
		sif_polj = new int [fi -> br_cvor];
		fi -> reset();
		for(i = 0; i < fi -> br_cvor; i++)
			sif_polj[i] = fi -> ispit_cvor();

		for(i = 0; i < fi -> br_cvor; i++)
			fi -> oduzmi_cvor(sif_polj[i]);
		
		if(sif_polj) delete sif_polj;

	}
	else
	if(fi -> br_cvor)
	{
		fi -> reset();
		for(i = 0; i < fi -> br_cvor; i++)
		{
			itoa(fi -> ispit_cvor(), string, 10);
			wndListBoxFiks().AddString(string);
		}
	}

		data_valid_ucit = 1;

	return TRUE;
}

void CKolegijDlg::OnButtonPrijenosClick()
{
	int sel;
	CString str;
	UINT rok_1;
	UINT rok_2;
	UINT rok_3;	

	sel = wndListBoxZapor().GetCurSel();
	if(sel != -1)
	{
		wndListBoxZapor().GetText(sel, str);
		if(LB_ERR == wndListBoxFiks().FindString(-1, str))
		{
			
			CWndFiksDlg dlgFiks;
			dlgFiks.zaporka = str;
			dlgFiks.br_rok = br_rok;
			(dlgFiks.gran).dol_gran_rok_1 = gran.dol_gran_rok_1;
			(dlgFiks.gran).dol_gran_rok_2 = gran.dol_gran_rok_2;
			(dlgFiks.gran).dol_gran_rok_3 = gran.dol_gran_rok_3;
			(dlgFiks.gran).gor_gran_rok_1 = gran.gor_gran_rok_1;
			(dlgFiks.gran).gor_gran_rok_2 = gran.gor_gran_rok_2;
			(dlgFiks.gran).gor_gran_rok_3 = gran.gor_gran_rok_3;
			dlgFiks.DoModal();

			rok_1 = dlgFiks.rok_1;
			rok_2 = dlgFiks.rok_2;
			rok_3 = dlgFiks.rok_3;

			ok = dlgFiks.ok;
			if(ok)
			if(br_rok == 3)
			{
				
				if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6) || ((rok_2 % 7) == 0)||((rok_2 % 7) == 6) || ((rok_3 % 7) == 0)||((rok_3 % 7) == 6)))
				{
					wndListBoxFiks().AddString(str);

					fi -> dodaj_cvor(atoi(str), rok_1, rok_2, rok_3);
				
				}
			
				else
					::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
						MB_OK | MB_ICONSTOP);
			}
			else
			if(br_rok == 2)
			{
				rok_1 = dlgFiks.rok_1;
				rok_2 = dlgFiks.rok_2;
				if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6) || ((rok_2 % 7) == 0)||((rok_2 % 7) == 6)))
				{
					wndListBoxFiks().AddString(str);
					
					fi -> dodaj_cvor(atoi(str), rok_1, rok_2, rok_3);
				
				}
			
				else
					::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
						MB_OK | MB_ICONSTOP);
				
			}
			else
			{
				rok_1 = dlgFiks.rok_1;
				if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6)))
				{
					wndListBoxFiks().AddString(str);

					fi -> dodaj_cvor(atoi(str), rok_1, rok_2, rok_3);
			
				}
			
				else
					::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
						MB_OK | MB_ICONSTOP);
			}

		}
	}
}

void CKolegijDlg::OnButtonDatumClick()
{
	CWndFiksDlg dlgFiks;
	CString str;
	int i;
	int zapor;
	UINT rok_1;
	UINT rok_2;
	UINT rok_3;	
	


	
	int cursel = wndListBoxFiks().GetCurSel();

	if(cursel != -1)
	{
		wndListBoxFiks().GetText(cursel, str);	
		dlgFiks.zaporka = str;
		zapor = atoi(str);

		fi -> reset();

		for(i = 0; fi -> br_cvor; i++)
		{
			if((fi -> ispit_cvor()) == zapor)
			{
				dlgFiks.br_rok = br_rok;
				(dlgFiks.gran).dol_gran_rok_1 = gran.dol_gran_rok_1;
				(dlgFiks.gran).dol_gran_rok_2 = gran.dol_gran_rok_2;
				(dlgFiks.gran).dol_gran_rok_3 = gran.dol_gran_rok_3;
				(dlgFiks.gran).gor_gran_rok_1 = gran.gor_gran_rok_1;
				(dlgFiks.gran).gor_gran_rok_2 = gran.gor_gran_rok_2;
				(dlgFiks.gran).gor_gran_rok_3 = gran.gor_gran_rok_3;
				dlgFiks.rok_1 = fi -> datum(0);
				dlgFiks.rok_2 = fi -> datum(1);
				dlgFiks.rok_3 = fi -> datum(2);
				dlgFiks.zaporka = str;
				dlgFiks.odabir = 0;
				

				break;
			}
		}//for i

		

		dlgFiks.DoModal();

			
		fi -> reset();
			for(i = 0; fi -> br_cvor; i++)
			if((fi -> ispit_cvor()) == zapor)
			{
		
				rok_1 = dlgFiks.rok_1;
				rok_2 = dlgFiks.rok_2;
				rok_3 = dlgFiks.rok_3;

				if(ok)
				if(br_rok == 3)
				{
				
					if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6) || ((rok_2 % 7) == 0)||((rok_2 % 7) == 6) || ((rok_3 % 7) == 0)||((rok_3 % 7) == 6)))
					{
						(fi -> datum(0)) = rok_1;
						(fi -> datum(1)) = rok_2;
						(fi -> datum(2)) = rok_3;
					}
			
					else
						::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
							MB_OK | MB_ICONSTOP);
				}
				else
				if(br_rok == 2)
				{
					rok_1 = dlgFiks.rok_1;
					rok_2 = dlgFiks.rok_2;
					if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6) || ((rok_2 % 7) == 0)||((rok_2 % 7) == 6)))
					{
						(fi -> datum(0)) = rok_1;
						(fi -> datum(1)) = rok_2;
						(fi -> datum(2)) = rok_3;
					}
			
					else
						::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
							MB_OK | MB_ICONSTOP);
				
				}
				else
				{
					rok_1 = dlgFiks.rok_1;
					if(!(((rok_1 % 7) == 0)||((rok_1 % 7) == 6)))
					{
						(fi -> datum(0)) = rok_1;
						(fi -> datum(1)) = rok_2;
						(fi -> datum(2)) = rok_3;
					}
			
					else
						::MessageBox(GetSafeHwnd(), "subota ili nedjelja nisu dozvoljeni dani", "Greška", 
							MB_OK | MB_ICONSTOP);
				}
		
				break;
			}//for i
		
	}//if cursel
}

void CKolegijDlg::OnButtonBrisanjeClick()
{
	CString str;
	

	int cursel = wndListBoxFiks().GetCurSel();
	if(cursel != -1)
	{
		wndListBoxFiks().GetText(cursel, str);
		wndListBoxFiks().DeleteString(cursel);
		fi -> oduzmi_cvor(atoi(str));

		
	}
}

void CKolegijDlg::OnZaporListBoxDblClick()
{
	OnButtonPrijenosClick();
}

void CKolegijDlg::OnZaporListBoxClick()
{
	
}

void CKolegijDlg::OnFiksListBoxDblClick()
{
	OnButtonDatumClick();
}

