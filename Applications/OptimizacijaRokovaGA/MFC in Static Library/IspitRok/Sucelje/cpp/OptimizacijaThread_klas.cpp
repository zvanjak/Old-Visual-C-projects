#include "..\h\Sucelje.h"

COptimizacijaThread :: COptimizacijaThread()
{
	
}
COptimizacijaThread :: COptimizacijaThread(int _br_i, Fiks_Ispit *_fi, Ispit_Stud_Zavod *_isz,
	Ispit_Period *_ip, int _sj, int _vp, double _od_f, UINT _poc_van, UINT _gran_dol_ost_v, 
	UINT _gran_dol_ost_u, granice *_gran, mut_korak_gran *_mkg, int _br_ponavlj, 
	psg_korak_gran *_psgkg, UINT *_stop, 
	HWND _clc, CString** _p_rezultati, CMutex *_mutex, UINT *_opt_u_tijeku, HWND _m_hwnd_1, HWND _m_hwnd_2)
{
	//preslikavanje dobivenih podataka u podatke svoje klase
	opt_u_tijeku = _opt_u_tijeku;
	mutex = _mutex;
	br_i = _br_i;
	fi = _fi;
	isz = _isz;
	ip = _ip;
	gran = _gran; 
	mkg = _mkg; 
	br_ponavlj = _br_ponavlj; 
	psgkg = _psgkg;
	sj = _sj; 
	vp = _vp; 
	od_f = _od_f; 
	poc_van = _poc_van; 
	gran_dol_ost_v = _gran_dol_ost_v; 
	gran_dol_ost_u = _gran_dol_ost_u;
	m_hwnd_1 = _m_hwnd_1;
	m_hwnd_2 = _m_hwnd_2;	

	stop = _stop; 
	clc = _clc;
	p_rezultati = _p_rezultati;
}
COptimizacijaThread :: ~COptimizacijaThread()
{

}

BOOL COptimizacijaThread :: InitInstance()
{
//kreiranje objekta Opt_God i pokretanje optimizacije
	og.Create(br_i, *fi, *isz, *ip, sj, vp, 1, poc_van, gran_dol_ost_v, gran_dol_ost_u, *gran, m_hwnd_1, m_hwnd_2, clc);
	og.start_opt_god(*isz, *ip, *fi, *mkg, br_ponavlj, *psgkg, *stop, p_rezultati, mutex, *opt_u_tijeku);

	return 0;
}