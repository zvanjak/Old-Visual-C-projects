
//dialoški okvir pomoæu kojega se uèitavaju parametri modela optimizacije
class CParametrDlg : public CDialog
{
public:
   CParametrDlg(CWnd* pParent = NULL);   // standard constructor
   enum { IDD = IDD_PARAMETRI };
	UINT vel_pop;
	UINT ppmg; // poèetni postotak mutacij gena
	UINT zpmg; // završni postotak mutacij gena
	UINT kpmg; // korak promjene postotka mutacij gena
	UINT ppmb; // |
	UINT zpmb; // |isto kao predhodno, ali se postotci odnose na mutaciju bitova u genu
	UINT kpmb; // |
	UINT br_iter; // broj iteracija
	UINT br_ponavlj; // broj ponavljanja uzastopnih optimizacija s istim parametrima
	UINT ppspg; // |
	UINT zpspg; // |isto kao predhodno mutacij gena, ali se postotci odnose na postotak poèetne smišljene populacije
	UINT kpspg; // |
	UINT doljgran; // min udaljenost meðu ispitima jednog kolegija
	UINT gorgran; // max udaljenost meðu ispitima jednog kolegija
	UINT idealgran;
	UINT maxbrdan; // max broj studenata koje jedna grupa predmeta može obraditi u isti dan
	UINT ok;
	UINT gpbs; 


protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	

	DECLARE_MESSAGE_MAP()

// metode za dohvaæanje pojedinih objekata "by reference" unutar dialoškog okvira
private:
		CSpinButtonCtrl& spnCtrlVelPop() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN6); }
		CSpinButtonCtrl& spnCtrlMutGenP() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1); }
		CSpinButtonCtrl& spnCtrlMutGenZ() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN2); }
		CSpinButtonCtrl& spnCtrlMutGenK() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN5); }
		CSpinButtonCtrl& spnCtrlMutBitP() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN7); }
		CSpinButtonCtrl& spnCtrlMutBitZ() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN8); }
		CSpinButtonCtrl& spnCtrlMutBitK() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN9); }
		CSpinButtonCtrl& spnCtrlSmislPocGenerP() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN10); }
		CSpinButtonCtrl& spnCtrlSmislPocGenerZ() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN11); }
		CSpinButtonCtrl& spnCtrlSmislPocGenerK() 
		{ return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN12); }
		CSpinButtonCtrl& spnCtrlBrPonavlj() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN16); }
		CSpinButtonCtrl& spnCtrlBrIter() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN18); }
		CSpinButtonCtrl& spnCtrlDg() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN13); }
		CSpinButtonCtrl& spnCtrlGg() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN14); }
		CSpinButtonCtrl& spnCtrlGPBS() 
      { return *(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN15); }
		CEdit& wndEditGg() 
      { return *(CEdit*) GetDlgItem(IDC_EDIT_GG); }
		CEdit& wndEditDg() 
      { return *(CEdit*) GetDlgItem(IDC_EDIT_DG); }
		CEdit& wndEditIg() 
      { return *(CEdit*) GetDlgItem(IDC_EDIT_IG); }
		
		

};

inline CParametrDlg::CParametrDlg(CWnd* pParent) : 
   CDialog(CParametrDlg::IDD, pParent) 
	{}

	
