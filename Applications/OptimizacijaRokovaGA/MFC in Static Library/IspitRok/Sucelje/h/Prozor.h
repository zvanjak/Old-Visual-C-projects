
#include "..\..\Resource\resource.h"


//srž win aplikacije
class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};


//klasa koja sadrži suèelje aplikacije - komentirana u diplomskom radu
class CMainWnd : public CFrameWnd
{ 
   DECLARE_DYNCREATE(CMainWnd) 

public:
   CMainWnd(); 
   virtual ~CMainWnd(); 
	int temp_m;
	UINT stop;
	CMutex mutex;
	
	Ispit_Period ip;
	Ispit_Stud_Zavod isz;
	UINT ideal_gran;
	UINT vel_pop;
	UINT br_iter;
	UINT br_ponavlj;
	mut_korak_gran mkg;
	psg_korak_gran psgkg;
	UINT rokflag;
	granice gran;
	UINT	gran_dol_ost_v;
	UINT	gran_dol_ost_u;
	UINT poc_van;
	CString** p_rezultati;
	int ukupno;
	CListCtrl	m_ctlList;
	UINT sir_jed;
	void SetClientBackColor(LONG lColor);
	COptimizacijaThread *m_pOptThr;
	
	
protected:
   CDialogBar  m_dlgBar;
	
	CToolBar		m_wndToolBar;
	
	CEdit			m_wndEdit;
	Fiks_Ispit fi;
	UINT data_valid;
	UINT data_valid_param;
	UINT data_valid_ucit;
	UINT data_valid_opt;
	UINT opt_u_tijeku;
	int cur_sel_rez;
	


	void granice_rokova();
	void string_kill();

   // Message map methods
   afx_msg int OnCreate(LPCREATESTRUCT lpCS);
	void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
   afx_msg void OnFileExit();
	afx_msg void OnFileSaveAll();
	afx_msg void OnUcitavanjePodataka();
	afx_msg void OnFileSaveTrenut();
   afx_msg void OnHelpAbout();
	afx_msg void OnButtonGa();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonFiksKolegij();
	afx_msg void OnButtonParametriOptimizacije();
	afx_msg void OnLeftDblClick(NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnColumClick(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	BOOL CMainWnd::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

private:
	CProgressCtrl& ctlProgress1() 
      { return *(CProgressCtrl*) m_dlgBar.GetDlgItem(IDC_PROGRESS1); }
	CProgressCtrl& ctlProgress2() 
      { return *(CProgressCtrl*) m_dlgBar.GetDlgItem(IDC_PROGRESS2); }

};

class CAboutDlg : public CDialog
{
public:
   CAboutDlg(CWnd* pParent = NULL);   // standard constructor
   enum { IDD = IDD_ABOUTBOX };
};

inline CAboutDlg::CAboutDlg(CWnd* pParent) : 
   CDialog(CAboutDlg::IDD, pParent) { }




