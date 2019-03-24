#include <afxcmn.h> 
#include <afxmt.h>


//klasa u �ijoj se metodi pokre�e, odr�ava i sinkronizira optimizacija
class Opt_God{
public:
	Opt_God();
	void Create(int br_i, Fiks_Ispit& fi, Ispit_Stud_Zavod& isz, Ispit_Period& ip, int sj, int vp, double od_f, UINT poc_van, UINT gran_dol_ost_v, UINT gran_dol_ost_u, granice gran, HWND m_hvnd_1, HWND m_hwnd_2, HWND _clc);
	~Opt_God();
	void ispis(Ispit_Stud_Zavod & isz, Ispit_Period& ip, int tk, int p, int o, int m, int l, CString** p_rezultati);
	//pokretanje optimizacije ispitnog perioda
	void start_opt_god(Ispit_Stud_Zavod & isz, Ispit_Period& ip, Fiks_Ispit& fi, mut_korak_gran& mkg, int br_ponavlj, psg_korak_gran& psgkg, UINT& stop, CString** p_rezultati, CMutex *mutex, UINT& opt_u_tijeku);
	void destrukt();

	Polje_I* poc_gen_plan;// polje koj ozna�ava jedinke u koje �e biti smje�tena smi�ljeni geni
	Polje_I* odab_elim;
	Selekcija* selekcija;
	Natalitet* natalitet;
	Mutacija* mutacija;
	CProgressCtrl pr1;
	CProgressCtrl pr2;
	CProgressCtrl *pct;
	CProgressCtrl *pcu;
	CListCtrl lc;
	CListCtrl * clc;
	int* ukupan_translat;
	int* ukupan_isp_ozn;
	int* ukupan_zav_ozn;
	int* ukupan_smjer_ozn;
	int* ukupan_isp_redni_br;
	int* ukupan_sem_ozn;
	int* djel_zav;
	int* djel_min_udalj;
	int* djel_ost;
	double* djel_ost_korjen;


	Polje_D** fija; // pokaziva� na polje pokaziva�a u kojima se nalaze parcijalne vrijednosti fije dobrote ( parcijalne vrijednosti -> smjerovi )
	Gen** p_gena; // pokaziva� na polje pokaziva�a objekta Gen ( Gen - jedan smjer )

	int max_stud_grup_pred;
	int d_o;
	int vel_elim;
	int maska;
	int br_smjer;
	int vel_pop;
	int sir_jed;
	int br_iter;
	int br_k;
	int max_index;
	double max_fij;
	int max_iter;
	int max_iter_1;
	int z_v;
	int m_u;
	
private:
	// osigurava odr�avanja ispita iz istog kolegija na razli�itim smjerovima na isti datum
	void isti_isp(Ispit_Stud_Zavod & isz, Ispit_Period& ip); 
	// sumiranje parcijalnih vrijednosti fije dobrote ( po smjerovima )
	void god_sum_max(Ispit_Period& ip, Ispit_Stud_Zavod& isz, int iter, int iter_1);
	// osigurava odr�avanja ispita iz fiksiranih kolegija na razli�itim smjerovima na isti datum
	void isti_isp_fiks(Ispit_Period& ip, Ispit_Stud_Zavod& isz, Fiks_Ispit& fi);
	// stvara po�etnu generaciju na smjerovima pomo�u metode Gen::pocetna_generacija()
	void set_poc_generacija(Ispit_Stud_Zavod& isz, Ispit_Period& ip, int pspg);
	void translat_popun(Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	//ka�njava odr�avanje prevelikog broja ispita iz nadle�nosti jedne grupe predmeta
	void zavod_fij(Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	
};
