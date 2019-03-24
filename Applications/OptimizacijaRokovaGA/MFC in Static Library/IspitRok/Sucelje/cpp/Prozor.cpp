
#include "..\h\Sucelje.h"


IMPLEMENT_DYNCREATE(CMainWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
   ON_WM_CREATE()
   ON_COMMAND(ID_BUTTON_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_BUTTON_SAVE, OnFileSaveAll)
	ON_COMMAND(ID_BUTTON_STOP, OnButtonStop)
	ON_COMMAND(ID_ALATI_ZAUSTAVLJANJEOPTIMIZACIJE, OnButtonStop)
	ON_COMMAND(ID_BUTTON_SAVE_TREN, OnFileSaveTrenut)
	ON_COMMAND(ID_BUTTON_OPEN, OnUcitavanjePodataka)
	ON_COMMAND(ID_BUTTON_FX, OnButtonFiksKolegij)
	ON_COMMAND(ID_BUTTON_OPCIJE, OnButtonParametriOptimizacije)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_DATOTEKA_UCITAVANJEPODATAKA, OnUcitavanjePodataka)
	ON_COMMAND(ID_ALATI_POKRENIOPTIMIZACIJU, OnButtonGa)
	ON_COMMAND(ID_OPCIJE_PREDODREENIDATUMI, OnButtonFiksKolegij)
	ON_COMMAND(ID_OPCIJE_PARAMETRIOPTIMIZACIJE, OnButtonParametriOptimizacije)
	ON_COMMAND(ID_DATOTEKA_SNIMANJEREZULTATA, OnFileSaveAll)
	ON_COMMAND(ID_DATOTEKA_SNIMANJEODABRANOGREZULTATA, OnFileSaveTrenut)
   ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_BUTTON_GA, OnButtonGa)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify) 
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnLeftDblClick)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CMainWnd::OnClose()
{
	if(!opt_u_tijeku)
		CWnd::OnClose();//uništavanje prozora
	else
	{
		CWndGreska3Dlg cwg3d;
		cwg3d.DoModal();//prijavljivanje greške
	}
}

void CMainWnd::SetClientBackColor(LONG lColor)
{
   ::SetClassLong(this->m_hWnd, GCL_HBRBACKGROUND, 
      (LONG)(HBRUSH)(lColor + 1));
}  
void CMainWnd::OnButtonStop()
{

	if(opt_u_tijeku)
	{
		CSingleLock  SingleLock(&mutex);

		SingleLock.Lock();// traženje resursa
		stop = 1;//signaliziranje prekida optimizacije
		opt_u_tijeku = 0;
		SingleLock.Unlock();//oslobaðanje resursa
	}
	
}

void CMainWnd :: string_kill()
{
	int i;

	for(i = 0; i < ukupno; i++)
		delete p_rezultati[i] ;

	if(p_rezultati) delete [] p_rezultati;
}

void CMainWnd::granice_rokova()
{
	double temp, temp1, temp2, temp3;
	int temp4;

			if(ip.br_rok == 3)
			{
							
				if(gran.dol_gran_rok % 7 == 5)
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 3;
					gran_dol_ost_u = 0;
				}
				else
				if(gran.dol_gran_rok % 7 == 6)
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 2;
					gran_dol_ost_u = 0;
				}
				else
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 1;
					gran_dol_ost_u = gran.dol_gran_rok - gran.dol_gran_rok / 7 * 7;
				}

				
			
				temp = ((double)ip.br_rad_dan / (double)ip.br_rok);
				temp2 = temp;

				temp1 = temp - floor(temp);
				if(!temp1)
				{
					if(!((int)temp % 5)) 
						temp1 = ((int) temp / 5 - 1) * 2;
					else 
						temp1 = ((int) temp / 5) * 2;
				}
				else temp1 = ((int) temp / 5) * 2;
 
				temp += temp1;
				temp = temp - gran.dol_gran_rok;
		
				temp3 = temp;
				temp3 += ((double)ip.br_rad_dan / (double)ip.br_rok); 
				temp1 = floor(temp3);
				temp1 = temp3 - temp1;
				if(temp1 > 0.5) temp3 = ceil(temp3);
				else temp3 = floor(temp3);
	
				if(!((int)temp3 % 5))
					temp2 = ((int) temp3 / 5 - 1) * 2;
				else
					temp2 = ((int) temp3 / 5) * 2;
				gran.gor_gran_rok_1 = (int)(temp3 + temp2);

				temp4 = (int)(ip.br_rad_dan - temp3);
				if(temp4 % 5) temp1 = (temp4 / 5);
				else temp1 = (temp4 / 5 - 1);
				temp4 = (int)(temp4 + 2 * temp1);
				if((temp4 % 7 == 5))
				{
					gran.dol_gran_rok_3 = temp4 + 3;
					gran_dol_ost_v = 0;
					poc_van = temp4 + 2;
				}
				else
				{
					gran.dol_gran_rok_3 = temp4 + 1;
					gran_dol_ost_v = temp4 - temp4 / 7 * 7;
					poc_van = temp4;
				}

				if(!((int)ip.br_rad_dan % 5))
					temp2 = ((int) ip.br_rad_dan / 5 - 1) * 2;
				else
					temp2 = ((int) ip.br_rad_dan / 5) * 2;
				gran.gor_gran_rok_3 = (int)(ip.br_rad_dan + temp2);

				if(!(gran.dol_gran_rok % 5))
					temp1 = (gran.dol_gran_rok / 5 - 1) * 2;
				else
					temp1 = (gran.dol_gran_rok / 5) * 2;
				temp2 = gran.dol_gran_rok - temp1;

				temp2 += (2 * temp + ((double)ip.br_rad_dan / 3));

				if(!((int)temp2 % 5))
					temp1 = ((int)temp2 / 5 - 1) * 2;
				else
					temp1 = ((int)temp2 / 5) * 2;

				gran.gor_gran_rok_2 = (int)(temp2 + temp1);
				
				
			
				if(!(gran.gor_gran_rok_2 % 7))
						temp1 = ((int)gran.gor_gran_rok_2 / 7 - 1) * 2;
				else
					temp1 = ((int)gran.gor_gran_rok_2 / 7) * 2;

				temp1 = gran.gor_gran_rok_2 - temp1;

				if(!(gran.dol_gran_rok_2 % 7))
						temp2 = ((int)gran.dol_gran_rok_2 / 7 - 1) * 2;
				else
					temp2 = ((int)gran.dol_gran_rok_2 / 7) * 2;

				temp2 = gran.dol_gran_rok_2 - temp2;

				sir_jed = (int)(log((double)( temp1 - temp2 + 1)) / log(2.0)) + 1;


			}
			else
			if(ip.br_rok == 2)
			{
				gran.dol_gran_rok_3 = 0;
				gran.gor_gran_rok_3 = 0;

				if(gran.dol_gran_rok % 7 == 5)
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 3;
					gran_dol_ost_v = 0;
				}
				else
				if(gran.dol_gran_rok % 7 == 6)
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 2;
					gran_dol_ost_v = 0;
				}
				else
				{
					gran.dol_gran_rok_2 = gran.dol_gran_rok + 1;
					gran_dol_ost_v = gran.dol_gran_rok - gran.dol_gran_rok / 7 * 7;
				}

			
				
			temp = (double)ip.br_rad_dan / (double)ip.br_rok;
			temp1 = temp - floor(temp);
			if(!temp1)
			{
				if(!((int)temp % 5)) 
					temp1 = ((int) temp / 5 - 1) * 2;
				else 
					temp1 = ((int) temp / 5) * 2;
			}
			else temp1 = ((int) temp / 5) * 2;

			temp += temp1; 
			temp = temp - gran.dol_gran_rok;
			
			temp3 = temp;
			temp3 += (double)ip.br_rad_dan / (double)ip.br_rok;
			if(!((int)temp3 % 5))
				temp2 = ((int)temp3 / 5 - 1) * 2;
			else
				temp2 = ((int)temp3 / 5) * 2;
			gran.gor_gran_rok_1 = (int)(temp3 + temp2);

			if(!(ip.br_rad_dan % 5))
				temp2 = (ip.br_rad_dan / 5 - 1) * 2;
			else
				temp2 = (ip.br_rad_dan / 5) * 2;
			gran.gor_gran_rok_2 = (int)(ip.br_rad_dan + temp2);
			
			
			if(gran.dol_gran_rok % 7 == 5)
				poc_van = gran.dol_gran_rok + 2;
			else
				poc_van = gran.dol_gran_rok;



			if(!(gran.gor_gran_rok_1 % 7))
						temp1 = ((int)gran.gor_gran_rok_1 / 7 - 1) * 2;
				else
					temp1 = ((int)gran.gor_gran_rok_1 / 7) * 2;

				temp1 = gran.gor_gran_rok_1 - temp1;

				if(!(gran.dol_gran_rok_1 % 7))
						temp2 = ((int)gran.dol_gran_rok_1 / 7 - 1) * 2;
				else
					temp2 = ((int)gran.dol_gran_rok_1 / 7) * 2;

				temp2 = gran.dol_gran_rok_1 - temp2;

				sir_jed = (int)(log((double)( temp1 - temp2 + 1)) / log(2.0)) + 1;

		
				
			}
			else
			{
				gran.dol_gran_rok_2 = 0;
				gran.gor_gran_rok_2 = 0;
				gran.dol_gran_rok_3 = 0;
				gran.gor_gran_rok_3 = 0;
				
				gran.dol_gran_rok_1 = 1;
				if(!(ip.br_rad_dan % 5))
					temp2 = (ip.br_rad_dan / 5 - 1) * 2;
				else
					temp2 = (ip.br_rad_dan / 5) * 2;
				gran.gor_gran_rok_1 = (int)(ip.br_rad_dan + temp2);

				if(!(gran.gor_gran_rok_1 % 7))
						temp1 = ((int)gran.gor_gran_rok_1 / 7 - 1) * 2;
				else
					temp1 = ((int)gran.gor_gran_rok_1 / 7) * 2;

				temp1 = gran.gor_gran_rok_1 - temp1;

				if(!(gran.dol_gran_rok_1 % 7))
						temp2 = ((int)gran.dol_gran_rok_1 / 7 - 1) * 2;
				else
					temp2 = ((int)gran.dol_gran_rok_1 / 7) * 2;

				temp2 = gran.dol_gran_rok_1 - temp2;

				sir_jed = (int)(log((double)( temp1 - temp2 + 1)) / log(2.0)) + 1;

			
			}
}

void CMainWnd::OnButtonParametriOptimizacije()//uèitavanje parametara optimizacije
{

	if(!opt_u_tijeku)
	{
	if(data_valid)
	{
		data_valid_param = 1;
		CParametrDlg cpd;

		ideal_gran = (int)(ip.br_dan * isz.max_br_isp / (ip.br_rok * isz.max_br_isp - 1));
		if(rokflag)
		{
			gran.gor_gran_rok = ideal_gran + 1;
			if(gran.gor_gran_rok > ip.br_dan / 3 * 2) gran.gor_gran_rok = ip.br_dan / 3 * 2;
			gran.dol_gran_rok = ideal_gran - 1;	
			if(gran.dol_gran_rok < 7) gran.dol_gran_rok = 7;
			rokflag = 0;
		}
		
			cpd.gorgran = gran.gor_gran_rok;	// |
			cpd.doljgran = gran.dol_gran_rok;// |
			cpd.br_iter = br_iter;//				|
			cpd.br_ponavlj = br_ponavlj;//		|

			cpd.kpmb = mkg.korak_b;//				|
			cpd.kpmg = mkg.korak_k;//				|
			cpd.ppmb = mkg.ppmb;//					|upisivanje vrijednosti u dialoški okvir
			cpd.ppmg = mkg.ppmk;//					|
			cpd.zpmb = mkg.zpmb;//					|
			cpd.zpmg = mkg.zpmk;//					|

			cpd.kpspg = psgkg.korak;//				|
			cpd.ppspg = psgkg.ppsg;//				|
			cpd.zpspg = psgkg.zpsg;	//				|	
			cpd.vel_pop = vel_pop;//				|

			cpd.gpbs = isz.max_stud_grup_pred;

		cpd.idealgran = ideal_gran;
		if(ip.br_rok == 1)
		cpd.maxbrdan = 0;
		else
		if(ip.br_rok == 2)
			cpd.maxbrdan = ip.br_dan;
		else
		cpd.maxbrdan = (ip.br_dan / 3) * 2;
		cpd.DoModal();

		if(cpd.ok)
		{
			br_iter = cpd.br_iter;				// |
			br_ponavlj = cpd.br_ponavlj;		// |
	
			mkg.korak_b = cpd.kpmb;				// |
			mkg.korak_k = cpd.kpmg;				// |
			mkg.ppmb = cpd.ppmb;					// |
			mkg.ppmk = cpd.ppmg;					// |uèitavanje unesenih vrijednosti iz 
			mkg.zpmb = cpd.zpmb;					// |dialoškog okbira
			mkg.zpmk = cpd.zpmg;					// |

			psgkg.korak = cpd.kpspg;			// |
			psgkg.ppsg = cpd.ppspg;				// |
			psgkg.zpsg = cpd.zpspg;				// |

			gran.dol_gran_rok = cpd.doljgran;// |
			
			gran.gor_gran_rok = cpd.gorgran;	// |
			vel_pop = cpd.vel_pop;				// |

			isz.max_stud_grup_pred = cpd.gpbs;//|

			gran.dol_gran_rok_1 = 1;			// |

			granice_rokova();//raèunanje vremenskih granica ispitnih rokova
		}
	}
	else
	{
		CWndGreskaDlg cwgd;

		cwgd.DoModal();// prijavljivanje greške
	}

	}

}

void CMainWnd::OnUcitavanjePodataka()
{
	CString *ime_1 = new CString;
	CString *ime_2 = new CString;

	CUcitDlg cud;

	if(!opt_u_tijeku)
	{
		cud.ime_1 = ime_1;
		cud.ime_2 = ime_2;
		cud.DoModal();

		data_valid_ucit = 0;			// |
		data_valid_param = 0;		// |
		ip.br_dan = cud.br_dan;		// |
		ip.br_rok = cud.br_rok;		// |uèitavanje podataka iz dijaloškog okvira
		ip.ljet_jesn = cud.lj_j;	// |
		ip.godina = cud.godina;		// |
		ip.inic();
		rokflag = cud.rokflag;

		data_valid = cud.data_valid;
	
		if(data_valid) 
		{
	

			if(EXIT_FAILURE == isz.Create(ip, ime_1, ime_2, ctlProgress1())) //kreacija Ispit_Stud_Zavod  objekta
			{
				data_valid = 0;
				::MessageBox(GetSafeHwnd(), "Problemi s èitavanjem ulaznih datoteka", "Greška", MB_OK | MB_ICONSTOP);
			
			}
		
		}
	}
}

void CMainWnd::OnLeftDblClick( NMHDR * pNotifyStruct, LRESULT * result )
{

	int i;
	int cursel;
	int gor_gran;


	if(data_valid_opt)
	{
	gor_gran = m_ctlList.GetItemCount();
	for(i = 0; i < gor_gran; i++)
	{
		cursel = m_ctlList.GetItemState(i, LVIS_SELECTED);
		if(cursel)
		{	
			cur_sel_rez = i;// koji je rezultat dvokliknut
			break;
		}
	}//for i
		
	//prikazivanje dotiènog rezultata u CEdit prozoru
	if(cursel) m_wndEdit.SetWindowText(*(p_rezultati[cur_sel_rez]));
	}

}

void CMainWnd::OnColumClick(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
}

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{ 
	//promjena velièine dijelova suèelja prilikom promjene dimenzija glavnog prozora

	CWnd :: OnSize(nType, cx, cy);
	m_wndToolBar.SetWindowPos(0, 0, 0, cx, 30, SWP_SHOWWINDOW);
	m_dlgBar.SetWindowPos(0, 0, cy - 20, cx, cy, SWP_SHOWWINDOW);
	m_ctlList.SetWindowPos(0, 0, 30, 300, cy - 50, SWP_SHOWWINDOW);
	m_wndEdit.MoveWindow(CRect(300, 30, cx, cy - 20));
	

}

BOOL CMainWnd::OnToolTipNotify(UINT id, NMHDR* pNMHDR, 
                               LRESULT* pResult)
{
   TOOLTIPTEXT *pTTT = (TOOLTIPTEXT*) pNMHDR;

   UINT nID = pNMHDR->idFrom;


   if (pTTT->uFlags & TTF_IDISHWND) // ID is hWnd
   {
      nID = ::GetDlgCtrlID((HWND)nID);

      if (nID == 0)
         return FALSE;
   }

   
   switch (nID)
   {
      case ID_BUTTON_GA:
         pTTT->lpszText = "Pokretanje optimizacije";
         break;

      case ID_BUTTON_FX:
         pTTT->lpszText = "Odreðivanje datuma ispitnih rokova kolegija";
         break;

		case ID_BUTTON_SAVE:
         pTTT->lpszText = "Snimanje svih rezultata";
         break;

		case ID_BUTTON_SAVE_TREN:
         pTTT->lpszText = "Snimanje odabranog rezultata";
         break;

		case ID_BUTTON_ABOUT:
         pTTT->lpszText = "O programu";
         break;

		case ID_BUTTON_OPEN:
         pTTT->lpszText = "Uèitavanje podataka  optimizacije";
         break;

		case ID_BUTTON_OPCIJE:
         pTTT->lpszText = "Parametri optimizacije";
         break;


   }

	return TRUE;
}


void CMainWnd :: OnButtonGa()
{
	int i;


	if(!opt_u_tijeku)
	{
	if(data_valid && data_valid_param)
	{

		if(data_valid_opt)
		{
			string_kill();//uništavanje polja CString objekata
			m_ctlList.DeleteAllItems();// brisanje svih "itema" iz CListCtrl - a
		}

		srand((unsigned)time(NULL));
		m_wndEdit.SetWindowText(" ");

		ukupno = (psgkg.zpsg - psgkg.ppsg) / psgkg.korak + 1;
		ukupno *= (mkg.zpmk - mkg.ppmk) / mkg.korak_k + 1;
		ukupno *= (mkg.zpmb - mkg.ppmb) / mkg.korak_b + 1;
		ukupno *= br_ponavlj;// raèunanje broja uzastopnih optimizacija

		p_rezultati = new (CString(*[ukupno]));

		for(i = 0; i < ukupno; i++)
			p_rezultati[i] = new CString;

		opt_u_tijeku = 1;

//kreiranje radne niti
		m_pOptThr = new COptimizacijaThread(br_iter, &fi, &isz,&ip, sir_jed, 
														vel_pop, 3, poc_van, gran_dol_ost_v, 
														gran_dol_ost_u, &gran, &mkg, br_ponavlj, 
														&psgkg, 
														&stop, m_ctlList/*.GetSafeHwnd()*/, p_rezultati, &mutex, 
														&opt_u_tijeku, ctlProgress1(), ctlProgress2());
//pokretanje radne niti
		m_pOptThr -> CreateThread();

		
		data_valid = 1;
		data_valid_opt = 1;
	}
	else
	{
		if(!data_valid)
		{
			CWndGreskaDlg cwgd;//prijava greške
			cwgd.DoModal();
		}
		else
		if(!data_valid_param)
		{
			CWndGreska2Dlg cwg2d;//prijava greške
			cwg2d.DoModal();
		}
	}
	}

	
}



CMainWnd::CMainWnd() // poèetne vrijednosti koje se pojavljuju kod dialoških okvira
{ 
		stop = 0;
		data_valid = 0;
		data_valid_param = 0;
		vel_pop = 100;
		br_iter = 10;
		br_ponavlj = 1;

		mkg.korak_b = 3;
		mkg.korak_k = 5;
		mkg.ppmb = 3;
		mkg.ppmk = 15;
		mkg.zpmb = 3;
		mkg.zpmk = 15;
		data_valid_ucit = 0; 

		psgkg.korak = 5;
		psgkg.ppsg = 23;
		psgkg.zpsg = 23;
		rokflag = 0;
		data_valid_opt = 0;
		p_rezultati = NULL;
		m_pOptThr = NULL;
		cur_sel_rez = -1;
		opt_u_tijeku = 0;
	

}


CMainWnd::~CMainWnd()
{  
	int i;

	if(data_valid_opt)
	{
		for(i = 0; i < ukupno; i++)
			delete p_rezultati[i] ;//uništavanje polja CString objekata

		if(p_rezultati) delete [] p_rezultati;
	}


}


int CMainWnd::OnCreate(LPCREATESTRUCT lpCS)
{

	data_valid = 0;
  
 
	if(!m_wndToolBar.Create(this, (WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS ), IDR_TOOLBAR1))
	{
		 TRACE0("Failed to set toolbar\n");
      return -1;
	}// kreiranje trake s alatima
	

	if(!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to set toolbar\n");
      return -1;
	}// uèitavanje gumbi iz Prozor.rc skripte


   if (!m_dlgBar.Create(this, IDD_DLGBAR, WS_CHILD | CBRS_TOP, 
      IDD_DLGBAR))
   {
      TRACE0("Failed to create dialog bar\n");
      return -1;    
   }// kreiranje dialoške trake

	
	

   m_dlgBar.ShowWindow(SW_SHOWNORMAL);

	//kreiranje CListCtrl prozora
	if (!m_ctlList.Create(
           LVS_REPORT | WS_VISCHILD | WS_BORDER | LVS_SINGLESEL, 
           CRect(0, 0, 0, 0), this, IDC_LIST1
        )
      )
      TRACE0(_T("Problem creating list control!"));      
	

	m_ctlList.InsertColumn(0, _T("Fija. Cilja"), LVCFMT_LEFT, 80, -1);
	m_ctlList.InsertColumn(1, _T("KGp"), LVCFMT_LEFT, 35, -1);
	m_ctlList.InsertColumn(2, _T("K1-2"), LVCFMT_LEFT, 35, -1);
	m_ctlList.InsertColumn(4, _T("x1000"), LVCFMT_LEFT, 45, -1);
	m_ctlList.InsertColumn(5, _T("%sg"), LVCFMT_LEFT, 35, -1); 
	m_ctlList.InsertColumn(6, _T("%mg"), LVCFMT_LEFT, 35, -1);
	m_ctlList.InsertColumn(7, _T("%mb"), LVCFMT_LEFT, 35, -1); 


//kreiranje CEdit prozora
	m_wndEdit.Create(ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | \
                  WS_CHILD | ES_LEFT | WS_BORDER | ES_READONLY | ES_AUTOHSCROLL,
						CRect(0, 0, 0, 0), this, IDC_EDIT4);

	
	
   return 0;
}


void CMainWnd::OnFileExit() 
{
	if(!opt_u_tijeku)
		DestroyWindow();//ako je optimizacija završila uništavanje programa
	else
	{
		CWndGreska3Dlg cwg3d; // ako nije prijava greške s uputstvima
		cwg3d.DoModal();
	}
}


void CMainWnd::OnFileSaveAll() 
{
	if(!opt_u_tijeku)
	{
		if(data_valid_opt)
		{
			CString sFilter = 
			   "Sve Datoteke (*.*)|*.*||";
 
   
			 CFileDialog dlgSave(FALSE, 0, 0, OFN_HIDEREADONLY | 
			  OFN_OVERWRITEPROMPT, (LPCTSTR)sFilter, this);

   
			 if (IDCANCEL == dlgSave.DoModal())
				return;

			CString sMsg;
			 sMsg.Format(dlgSave.GetPathName());

	
			CFile file((LPCTSTR) sMsg, 
			CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	
//snimanje svih rezultata uzastopnih optimizacija koji se nalaze u CString objektima
			for(int i = 0; i < ukupno; i++)
				file.Write((void*)(LPCTSTR) *(p_rezultati[i]), p_rezultati[i] -> GetLength());

	
		}
	}
}

void CMainWnd::OnFileSaveTrenut() 
{

	if(!opt_u_tijeku)
	{
		if(data_valid_opt)
		{
			CString sFilter = 
				"Sve Datoteke (*.*)|*.*||";
 
			CFileDialog dlgSave(FALSE, 0, 0, OFN_HIDEREADONLY | 
			OFN_OVERWRITEPROMPT, (LPCTSTR)sFilter, this);

			if (IDCANCEL == dlgSave.DoModal())
				return;

			CString sMsg;
			sMsg.Format(dlgSave.GetPathName());
			CFile file((LPCTSTR) sMsg, 
			CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
			//ako je datoteka kreirana snimi odabrani rezultat ( nalazi se u obliku CString objekta )
			if(cur_sel_rez != -1)
				file.Write((void*)(LPCTSTR) *(p_rezultati[cur_sel_rez]), p_rezultati[cur_sel_rez] -> GetLength());

		}
	}
}


void CMainWnd::OnHelpAbout() 
{
   CAboutDlg dlgAbout;
   dlgAbout.DoModal();
}

void CMainWnd::OnButtonFiksKolegij() 
{
	if(!opt_u_tijeku)
	{
		if(data_valid && data_valid_param)
		{
			
			CKolegijDlg dlgKolegij; // stvaranje dialoškog okvira
			dlgKolegij.fi = &fi;
			dlgKolegij.br_rok = ip.br_rok;
			dlgKolegij.zapor_p = isz.isp_ozn_p;
			dlgKolegij.br_ispit = isz.ukup_br_isp;
			dlgKolegij.data_valid_ucit = data_valid_ucit;
			(dlgKolegij.gran).dol_gran_rok_1 = gran.dol_gran_rok_1;// | 
			(dlgKolegij.gran).dol_gran_rok_2 = gran.dol_gran_rok_2;// | 
			(dlgKolegij.gran).dol_gran_rok_3 = gran.dol_gran_rok_3;// | uèitavanje poèetnih 
			(dlgKolegij.gran).gor_gran_rok_1 = gran.gor_gran_rok_1;// | podataka
			(dlgKolegij.gran).gor_gran_rok_2 = gran.gor_gran_rok_2;// | 
			(dlgKolegij.gran).gor_gran_rok_3 = gran.gor_gran_rok_3;// | 
			dlgKolegij.DoModal();//prikazivanje dialoškog okvira
			data_valid_ucit = dlgKolegij.data_valid_ucit;
		}
		else
		{
			if(!data_valid)
			{
				CWndGreskaDlg cwgd;
				cwgd.DoModal();// prijava greške
			}
			else
			if(!data_valid_param)
			{
				CWndGreska2Dlg cwg2d;
				cwg2d.DoModal();//prijava greške
			}
		}

	}
}


BOOL CMyApp::InitInstance()
{
   CMainWnd* pFrame = new CMainWnd();

   pFrame -> LoadFrame(IDR_MAINFRAME, 
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   this -> m_pMainWnd = pFrame;
   pFrame->SetClientBackColor(COLOR_APPWORKSPACE);

   pFrame -> CenterWindow();
   pFrame -> ShowWindow(SW_SHOWMAXIMIZED);
   pFrame -> UpdateWindow();

   return TRUE;
}


CMyApp MyApp;
