//skup klasa koje reprezentiraju dialo�ke okvire koji se pojavljuju kod prijave gre�aka
//uzrokovanim pritiskanjem odre�enog gumba, a da neki, potrebni, 
//prije toga nije bio pritisnut


class CWndGreskaDlg : public CDialog
{
public:
	CWndGreskaDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_DIALOG_GRESKA };		
	//CWndFiksDlg
};
class CWndGreska2Dlg : public CDialog{
public:
	CWndGreska2Dlg(CWnd* pParent = NULL);
	enum { IDD = IDD_DIALOG_GRESKA_2 };		
	
};

class CWndGreska3Dlg : public CDialog{
public:
	CWndGreska3Dlg(CWnd* pParent = NULL);
	enum { IDD = IDD_DIALOG_GRESKA_3 };		
	
};
