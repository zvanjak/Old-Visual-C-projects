//prilikom fiksiranja ispita iz nekog kolegija poziva se objekt ove klase za 
//odreðivanje datuma ispita na pojedinim rokovima

class CWndFiksDlg : public CDialog{
public:
	CWndFiksDlg(CWnd* pParent = NULL);
	enum { IDD_F = IDD_DIALOG_FIKS };
	UINT rok_1;
	UINT rok_2;
	UINT rok_3;
	UINT naziv;
	UINT isp_sif;
	CString zaporka;//oznaka kolegija
	UINT br_rok;
	granice gran;
	UINT odabir;
	UINT ok;
		
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	

	DECLARE_MESSAGE_MAP()

	
};//CWndFiksDlg

