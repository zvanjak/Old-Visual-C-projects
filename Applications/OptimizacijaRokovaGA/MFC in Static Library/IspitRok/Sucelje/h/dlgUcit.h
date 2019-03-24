//dialo�ki okvir kod kojeg se u�ituje godina i ispitni period koji se treba optimizirat
// te se nalaze gumb koji pozivaju dialo�ki okvir za u�itavanje masovnih podataka

class CUcitDlg : public CDialog
{
public:
   CUcitDlg(CWnd* pParent = NULL);   
   enum { IDD = IDD_DIALOG_PODACI };
	UINT godina;
	UINT br_rok;
	UINT lj_j; // ljetni ili jesenski ispitni period
	UINT br_dan; // trajanje ispitnog perioda
	UINT rokflag;
	UINT data_valid; // sinkronizacijska varijabla
	UINT ucit_1;
	UINT ucit_2;
	CString* ime_1; // ime datoteke u kojoj se nalazi nastavni plan
	CString* ime_2; // ime datoteke u kojoj se nalazi presjek broja studenata izme�u ispita

protected:
	afx_msg void OnUcitPodat();//poruka za u�itavanje masovnih podataka
	afx_msg void OnRadioClick();//poruka za radio gumbe ( godina i ispitni period )
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
   DECLARE_MESSAGE_MAP()

private:

	UINT pG[4];
	UINT pR[4];
	UINT* p;

	UINT FindRadio();
	void SetRadio(UINT rg, UINT poz);

	//metode za dohva�anje "by reference" objekata unutar dialo�kog okvira
	CButton& radioGod1() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_GOD_1); }
	CButton& radioGod2() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_GOD_2); }
	CButton& radioGod3() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_GOD_3); }
	CButton& radioGod4() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_GOD_4); }
	CSpinButtonCtrl& spnCtrlBrDan() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1); }
	CButton& radioRokZ() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_ROK_Z); }
	CButton& radioRokP() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_ROK_P); }
	CButton& radioRokLJ() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_ROK_LJ); }
	CButton& radioRokJ() 
      { return *(CButton*) GetDlgItem(IDC_RADIO_ROK_J); }
};

inline CUcitDlg::CUcitDlg(CWnd* pParent) : 
   CDialog(CUcitDlg::IDD, pParent) { }
