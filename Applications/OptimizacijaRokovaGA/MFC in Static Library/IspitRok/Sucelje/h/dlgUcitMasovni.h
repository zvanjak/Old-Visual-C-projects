//dialo�ki okvir s dva gumba �ijim pritiskanjem se pojavljuju 
//standardni dialo�ki okvir za u�itavannje datoteka

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
	// metode za hvatanje poruka gumbiju zadu�enih za otvaranje 
	//standardnih dialo�kih okvira za u�itavannje datoteka
	virtual void OnNastavniPlan();
	virtual void OnPresjek();
	

	DECLARE_MESSAGE_MAP()

	
};//CWndUcitMasovnoDlg

