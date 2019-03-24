//klasa koja od polja double-ova odabire jedinke za eliminaciju
class Selekcija{
public:
	Selekcija();
	Selekcija(int n);
	~Selekcija();
	void kumulacija(Polje_D& pd);
	void odabir_elim(Polje_D& pd, Polje_I& pi, int vel_elim);
	void windowing(Polje_D& pd);
	double* kumul;
};

//od preživjelih jedinki nadopunjava populaciju
class Natalitet{
public:
	Natalitet(int v_e, int v_p, int m, int br_rok);
	Natalitet();
	~Natalitet();
	void roditelji_dijete(Polje_I& ip);
	void krizanje(Polje_I& pi, Gen& gen, Ispit_Period& ip, Ispit_Stud_Zavod& isz, int smjer);	
	int provjera(Polje_I& pi);
	void popravak(Polje_I& pi);
	int vel_polja;
	int* dijet_rod_p;
	int vel_elim;
	int mode;
	int vel_pop;
	unsigned long maska;
	int br_k;
};

//mutira genetski kod gena
class Mutacija{
public:
	Mutacija();
	Mutacija(int vel_pop, Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	void inic_mut(int pmb, int pmk, int vel_pop, int sir_jed, Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	~Mutacija();
	void inic_poz_gen();
	void mut_gena(Gen& g, int smjer);
	void mut_gena_god(Gen** g, int br_smjer, int pmb, int pmk, int vel_pop, int sir_jed, Ispit_Period& ip, Ispit_Stud_Zavod& isz);

	int pos_mut_bit;
	int pos_mut_krom;
	int br_mut_krom;
	int* ozraceni;
	int djel_gen;
	int br_k;
	int* br_mut_bit_krom;
	int* djel_krom;
	int* djel_pozic;
};