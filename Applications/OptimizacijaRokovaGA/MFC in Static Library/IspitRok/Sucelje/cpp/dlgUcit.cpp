#include "..\h\Sucelje.h"




BEGIN_MESSAGE_MAP(CUcitDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnUcitPodat)
	ON_BN_CLICKED(IDC_RADIO_GOD_1, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_GOD_2, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_GOD_3, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_GOD_4, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_ROK_Z, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_ROK_P, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_ROK_LJ, OnRadioClick)
	ON_BN_CLICKED(IDC_RADIO_ROK_J, OnRadioClick)
END_MESSAGE_MAP()

void CUcitDlg::OnOK() 
{
	if(ucit_1 && ucit_2) data_valid = 1;
	else data_valid = 0;

	br_dan = spnCtrlBrDan().GetPos();
	CDialog::OnOK();
	//preslikavanje u Ispit_Period bazne klase
}

BOOL CUcitDlg::OnInitDialog() 
{
	int i;

	rokflag = 1;
	data_valid = 0;
	ucit_1 = 0;
	ucit_2 = 0;
	

	for(i = 0; i < 4; i++)
	{
		pG[i] = 0;
		pR[i] = 0;
	}//for i

	//postavljanje inicijalne pozicije radio gumbi
	pG[2] = 1;
	godina = 3;
	radioGod3().SetCheck(1);
	
	pR[2] = 1;
	br_rok = 3;
	lj_j = 0;
	radioRokLJ().SetCheck(1);

	br_dan = 33;
	spnCtrlBrDan().SetRange(7, 50);
	spnCtrlBrDan().SetPos(33);

	return TRUE;
}

void CUcitDlg::OnUcitPodat() 
{

	CWndUcitMasovnoDlg cwumd;

	cwumd.ucit_1 = 0;
	cwumd.ucit_2 = 0;
	cwumd.ime_1 = ime_1;
	cwumd.ime_2 = ime_2;
	cwumd.DoModal();

	ucit_1 = cwumd.ucit_1;
	ucit_2 = cwumd.ucit_2;

	radioGod1().EnableWindow(FALSE);
	radioGod2().EnableWindow(FALSE);
	radioGod3().EnableWindow(FALSE);
	radioGod4().EnableWindow(FALSE);
	radioRokZ().EnableWindow(FALSE);
	radioRokP().EnableWindow(FALSE);
	radioRokLJ().EnableWindow(FALSE);
	radioRokJ().EnableWindow(FALSE);

}

UINT CUcitDlg::FindRadio()
{
	UINT i;

	for(i = 0; i < 4; i++)
		if(p[i]) return i;

	return 0;
}


void CUcitDlg::SetRadio(UINT rg, UINT poz)
{
	if(!rg)
	{
		if(poz == 0) radioGod1().SetCheck(1);
		else
		if(poz == 1) radioGod2().SetCheck(1); 
		else
		if(poz == 2) radioGod3().SetCheck(1);
		else
		if(poz == 3) radioGod4().SetCheck(1);
	}
	else
	{
		if(poz == 0) radioRokZ().SetCheck(1);
		else
		if(poz == 1) radioRokP().SetCheck(1);
		else
		if(poz == 2) radioRokLJ().SetCheck(1);
		else
		if(poz == 3) radioRokJ().SetCheck(1);

	}//else

}

//postavljanje radio gumbi s obzirom na korisnièki klik mišem
void CUcitDlg::OnRadioClick()
{
	if(radioGod1().GetCheck())	
	{
		godina = 1;
		p = pG;
		pG[FindRadio()] =0;
		pG[0] = 0;

		p = pR;
		SetRadio(1, FindRadio());		
	}
	else
	if(radioGod2().GetCheck())
	{
		godina = 2;
		p = pG;
		pG[FindRadio()] =0;
		pG[1] = 1;

		p = pR;
		SetRadio(1, FindRadio());
	}
	else
	if(radioGod3().GetCheck())
	{
		godina = 3;
		p = pG;
		pG[FindRadio()] =0;
		pG[2] = 1;

		p = pR;
		SetRadio(1, FindRadio());
	}
	else
	if(radioGod4().GetCheck())
	{
		godina = 4;
		p = pG;
		pG[FindRadio()] =0;
		pG[3] = 1;

		p = pR;
		SetRadio(1, FindRadio());
	}
	else
	if(radioRokZ().GetCheck())
	{
		br_rok = 2;
		p = pR;
		pR[FindRadio()] =0;
		pR[0] = 1;

		p = pG;
		SetRadio(0, FindRadio());
		spnCtrlBrDan().SetPos(25);
	}
	else
	if(radioRokP().GetCheck())
	{
		br_rok = 1;
		p = pR;
		pR[FindRadio()] =0;
		pR[1] = 1;

		p = pG;
		SetRadio(0, FindRadio());

		spnCtrlBrDan().SetPos(7);
	}
	else
	if(radioRokLJ().GetCheck())
	{
		br_rok = 3;
		lj_j = 0;
		p = pR;
		pR[FindRadio()] =0;
		pR[2] = 1;

		p = pG;
		SetRadio(0, FindRadio());

		spnCtrlBrDan().SetPos(33);
	}
	else
	if(radioRokJ().GetCheck())
	{
		br_rok = 3;
		lj_j = 1;
		p = pR;
		pR[FindRadio()] =0;
		pR[3] = 1;

		p = pG;
		SetRadio(0, FindRadio());
		spnCtrlBrDan().SetPos(25);
	}//else
}