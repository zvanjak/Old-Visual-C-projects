#include <afxcmn.h>  

// sadržo podatke o godini i ispitnom periodu za optimizaciju
class Ispit_Period{
public:
	Ispit_Period();
	Ispit_Period(int br, int bd, int lj_j, int g);
	void inic();
	int br_rok;
	int br_rad_dan;
	int br_dan;
	int ljet_jesn;
	int godina;
};



class Ispit_Stud_Zavod{
public:
	Ispit_Stud_Zavod();
	//popuna podatkovnih polja
	int Create(Ispit_Period& ip, CString* ime_1,CString* ime_2, CProgressCtrl& pct);
	~Ispit_Stud_Zavod();
	//èitanje i obrada podataka iz datoteke koja sadrži nastavni plan
	int podatak_6(ifstream& ifile, char* string, int* podaci);
	//èitanje i obrada podataka iz datoteke koja sadrži presjek broja studenata
	int podatak_3(ifstream& ifile, char* string, int* podaci);
	void destrukt();
	int& operator [] (int i);
	int& operator () (int smj, int i);
	int& operator () (int smj, int sem, int i);
	int& operator () (int smj, int sem_1, int i1, int sem_2, int i2);
	int smjer(int poz, Ispit_Period& ip);
	int prvi_drugi(int poz, int smj, Ispit_Period& ip);
	int krom_poz(int poz, int smj, Ispit_Period& ip);
	int& sif_isp(int smj, int sem, int i);

	int br_smjer;
	int smjerovi[50];
	int grup_isp[512];
	int br_razl_isp;
	int ukup_br_isp;
	int max_br_isp;
	int ukup_br_isp_1;
	int mnoz;
	int br_grup_pred;
	int max_stud_grup_pred;
	
	int** presjek_p;
	int* count;
	int* isp_zav_ozn_p;
	int* br_ispit_p;
	int* poc_smjer_stud;
	int* poc_smjer_stud_1;
	int* isp_ozn_p;
	int* br_stud_p;
	char* razl_isp_p;
	char* zaj_isp_smj_sem;
	int* razl_isp_ozn_p;
	char* zaj_isp_smj_poz;
};

