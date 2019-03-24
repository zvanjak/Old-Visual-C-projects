//dialoški okvir s dva gumba èijim pritiskanjem se pojavljuju 
//standardni dialoški okvir za uèitavannje datoteka

class CWndUcitMasovnoDlg : public CDialog{
public:
	CWndUcitMasovnoDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_UCIT_MASOVNI };	
	UINT ucit_1;
	UINT ucit_2;
	CString* ime_1;
	CString* ime_2;

protected:

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	// metode za hvatanje poruka gumbiju zaduženih za otvaranje 
	//standardnih dialoških okvira za uèitavannje datoteka
	virtual void OnNastavniPlan();
	virtual void OnPresjek();
	

	DECLARE_MESSAGE_MAP()

	
};//CWndUcitMasovnoDlg

