class COptimizacijaThread : public CWinThread
{
public:
	COptimizacijaThread();
	//pribavljanje svih podataka potrebnih objektu klase Opt_God
	COptimizacijaThread(int _br_i, Fiks_Ispit *_fi, Ispit_Stud_Zavod *_isz, Ispit_Period *_ip,
		int _sj, int _vp, double _od_f, UINT _poc_van, UINT _gran_dol_ost_v, UINT _gran_dol_ost_u,
		granice *_gran, mut_korak_gran *_mkg, int _br_ponavlj, psg_korak_gran *_psgkg,
		UINT *_stop, HWND _clc,
		CString** _p_rezultati, CMutex *_mutex, UINT *_opt_u_tijeku, HWND _m_hwnd_1, HWND _m_hwnd_2);
	~COptimizacijaThread();

protected:
	HWND m_hwnd_1;
	HWND m_hwnd_2;

	UINT *opt_u_tijeku;
	CMutex *mutex;
	Opt_God og;
	int br_i;
	Fiks_Ispit *fi;
	Ispit_Stud_Zavod *isz;
	Ispit_Period *ip;
	granice *gran; 
	mut_korak_gran *mkg; 
	int br_ponavlj; 
	psg_korak_gran *psgkg;
	int sj; 
	int vp; 
	double od_f; 
	UINT poc_van; 
	UINT gran_dol_ost_v; 
	UINT gran_dol_ost_u;
	
	UINT *stop; 
	HWND clc;
	CString** p_rezultati;

	virtual BOOL InitInstance(); // kreiranje radne niti i pokretanje optimizacije

};