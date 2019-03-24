#include "..\h\Sucelje.h"




BEGIN_MESSAGE_MAP(CParametrDlg, CDialog)
	
END_MESSAGE_MAP()


//dialoški okvir za uèitavanje parametara
void CParametrDlg::OnOK() 
{

	ok = 1;
	vel_pop = spnCtrlVelPop().GetPos();

	ppmb = spnCtrlMutBitP().GetPos();
	zpmb = spnCtrlMutBitZ().GetPos();
	kpmb = spnCtrlMutBitK().GetPos();

	ppmg = spnCtrlMutGenP().GetPos();
	zpmg = spnCtrlMutGenZ().GetPos();
	kpmg = spnCtrlMutGenK().GetPos();

	ppspg = spnCtrlSmislPocGenerP().GetPos();
	zpspg = spnCtrlSmislPocGenerZ().GetPos();
	kpspg = spnCtrlSmislPocGenerK().GetPos();

	br_iter = spnCtrlBrIter().GetPos();
	br_ponavlj = spnCtrlBrPonavlj().GetPos();

	doljgran = spnCtrlDg().GetPos();
	gorgran = spnCtrlGg().GetPos();

	gpbs = spnCtrlGPBS().GetPos();

	CDialog::OnOK();
}

BOOL CParametrDlg::OnInitDialog() 
{
	ok = 0;
	
	spnCtrlVelPop().SetRange(vel_pop, 500);
	spnCtrlVelPop().SetPos(vel_pop);

	spnCtrlMutBitK().SetRange(1, 50);
	spnCtrlMutBitK().SetPos(kpmb);
	spnCtrlMutBitP().SetRange(1, 99);
	spnCtrlMutBitP().SetPos(ppmb);
	spnCtrlMutBitZ().SetRange(1, 99);
	spnCtrlMutBitZ().SetPos(zpmb);

	spnCtrlMutGenK().SetRange(1, 50);
	spnCtrlMutGenK().SetPos(kpmg);
	spnCtrlMutGenP().SetRange(1, 99);
	spnCtrlMutGenP().SetPos(ppmg);
	spnCtrlMutGenZ().SetRange(1, 99);
	spnCtrlMutGenZ().SetPos(zpmg);

	spnCtrlSmislPocGenerK().SetRange(1, 50);
	spnCtrlSmislPocGenerK().SetPos(kpspg);
	spnCtrlSmislPocGenerP().SetRange(1, 99);
	spnCtrlSmislPocGenerP().SetPos(ppspg);
	spnCtrlSmislPocGenerZ().SetRange(1, 99);
	spnCtrlSmislPocGenerZ().SetPos(zpspg);

	spnCtrlBrIter().SetRange(1, 100);
	spnCtrlBrIter().SetPos(br_iter);

	spnCtrlBrPonavlj().SetRange(1, 100);
	spnCtrlBrPonavlj().SetPos(br_ponavlj);
	spnCtrlGPBS().SetRange(1, 1000);
	spnCtrlGPBS().SetPos(gpbs);

	if(!maxbrdan)
	{
		spnCtrlDg().EnableWindow(FALSE);
		spnCtrlGg().EnableWindow(FALSE);
		wndEditGg().EnableWindow(FALSE);
		wndEditDg().EnableWindow(FALSE);
		wndEditIg().EnableWindow(FALSE);
	}
	else
	{
		spnCtrlDg().SetRange(7, idealgran);
		spnCtrlDg().SetPos(doljgran);
		spnCtrlGg().SetRange(idealgran, maxbrdan);
		spnCtrlGg().SetPos(gorgran);

		char str[4];
		_itoa(idealgran, str, 10);
		wndEditIg().SetWindowText(str);
	}
	

	return TRUE;
}
