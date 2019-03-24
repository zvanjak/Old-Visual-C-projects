

// Dialoški okvir u kojem se prikazuju predmeti na odreðenoj godini za fiksiranje
// datuma njihovih ispita

class CKolegijDlg : public CDialog
{
public:
   CKolegijDlg(CWnd* pParent = NULL);
   enum { IDD = IDD_KOLEGIJ };
	int* zapor_p;
	Fiks_Ispit* fi;
	int br_ispit;
	UINT r_1;
	UINT r_2;
	UINT r_3;
	granice gran;
	UINT br_rok;
	UINT ok;
	UINT data_valid_ucit;
	
	//metode koje "hvataju poruke upuæene od gumbiju ili miša"
protected:
	afx_msg void OnButtonPrijenosClick();
	afx_msg void OnButtonDatumClick();
	afx_msg void OnButtonBrisanjeClick();
   afx_msg void OnZaporListBoxDblClick();    
   afx_msg void OnFiksListBoxDblClick();    
   afx_msg void OnZaporListBoxClick();
	
    

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	UINT temp_zapor[50];
	UINT br_cvor;

   DECLARE_MESSAGE_MAP()

//funkcije kojima dohvaæamo "by reference" objekte CListBox unutar programa
private:
	CListBox& wndListBoxZapor() 
     { return *(CListBox*) GetDlgItem(IDC_LIST_KOLEGIJI); }
	CListBox& wndListBoxFiks() 
     { return *(CListBox*) GetDlgItem(IDC_LIST_KOLEGIJI_FIKS); }
};

inline CKolegijDlg::CKolegijDlg(CWnd* pParent) : 
   CDialog(CKolegijDlg::IDD, pParent) { }
