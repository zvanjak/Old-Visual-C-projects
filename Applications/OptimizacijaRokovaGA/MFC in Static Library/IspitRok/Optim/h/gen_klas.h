//srž programa koja sadrži genetski kod, funkciju dobrote 
//i metode za stvaranje poèetne populacije
class Gen{
public : 

	Gen();
	Gen(int sj, int vp, Ispit_Stud_Zavod& is, UINT poc_van, UINT gran_dol_ost_v, UINT gran_dol_ost_u, granice gran, Ispit_Period& ip, double od_f, int smj); // (sirina jedinke(bitovi), velicina populacije, postotak mutacije)
	~Gen();

	//funkcije dobrote
	void fija_cilja_p(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);//proljetni ispit period
	void fija_cilja_z(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);//zimski ispit period
	void fija_cilja_lj(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);//ljetni ispit period
	void fija_cilja_j(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);//jesenski ispit period
	 

	//metode koje izraèunavaju parcijalne djelove funkcije dobrote i koje koriste 
	//funkcije dobrote pojedinih ispitnih perioda
	void fija_cilja_1(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);
	void fija_cilja_1_2(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);
	void fija_cilja_3(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip);
	void fija_cilja_4(Ispit_Stud_Zavod& isz, const Ispit_Period& ip);
	void fija_cilja_5(Ispit_Stud_Zavod& isz, const Ispit_Period& ip);
	void fija_cilja_6(Ispit_Stud_Zavod& isz, const Ispit_Period& ip);

	//metode koje na osnovu dobivene informacije estrahiraju podatke o najboljoj jedinci
	void ukupno_najbolj_lj(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	void ukupno_najbolj_j(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	void ukupno_najbolj_z(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	void ukupno_najbolj_p(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz);

	//dekodiranje genetskog koda u vremensku dimenziju
	int translat_p(unsigned long k, const Ispit_Period& ip);
	int translat_u(unsigned long k, const Ispit_Period& ip);
	int translat_z(unsigned long k, const Ispit_Period& ip);

	// metoda koja stvara poèetnu generaciju
	void pocetna_generacija(Polje_I& poc_gen_plan, Ispit_Stud_Zavod& is, Ispit_Period& ip);
	//metoda za sortiranje polja
	void shellsort(int* polje_s, int* index_sort_1, int* index_sort_2, int n);
	void shellsort(int* polje_s, int* index_sort_1, int* index_sort_2, int* index_sort_3, int* index_sort_4, int n);
	void provjeri(int* p, int index, int poz, int n);
	void ispis(Ispit_Period& ip, Ispit_Stud_Zavod& is, int smjer, CString** p_rezultati, int br_ponavlj);
	void destrukt();
	int trans_inverz(int dan, int rok);

	typedef int (Gen :: *F_T)(unsigned long, const Ispit_Period&);
	F_T* t_f;

	typedef void (Gen :: *F) (Polje_D& pd, Ispit_Stud_Zavod& is, const Ispit_Period& ip);
	F f;

	typedef void (Gen :: *NAJB) (Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz);
	NAJB najb;

	unsigned long* krom_1; //genetski kod ispita iz zimskog semestra
	unsigned long* krom_2; //genetski kod ispita iz ljetnog semestra
	unsigned long* kromosom[2];
	unsigned long maska;
	int* trans_krom; // polje s dekodiranim vrijednostima krom_1 i krom_2
	int* trans_dan[3];
	int* index_c;
	int* index_s;
	int* index_sort;
	int* index;
	int* index_cont;
	int* rez;
	int* rez_sort; // sortirani rezultat najbolje jedinke
	int* translacija;
	int* translat;
	int* translat_6;
	int* translat_sort_1;
	int* translat_sort_2;
	int* translat_2_2;
	int* djel_r_1;	// |
	int* djel_r_2;	// |
	int* djel_1;	// | polja parcijalne vrijednosti kazni jedinki
	int* djel_3;	// |
	int* djel_4;	// |
	int* djel_min_udalj;
	int* djel_ost;
	double* djel_ost_korjen;
	double* fc;
	double* fc_r_1;
	double* fc_r_2;
	double* fc_1; // polje s parcijalnim vrijednostima fije dobrote
	double* fc_3; // polje s parcijalnim vrijednostima fije dobrote
	int sir_gen[2];
	int sir_gen_u;
	
	int max_i;
	int max_j;	
	int djel_max;
	int djel_max_1;
	int djel_max_4;
	int vel_pop;
	int sir_jed;
	int vel_elim;
	int gran_gor_dan;
	int gran_dol_dan;
	int gran_dol_ost_u;
	int gran_dol_ost_v;
	int min_disp_dan;
	int min_disp_dan_2;
	int br_grup_krom;
	int poc_van;
	int smjer;
	int br_smisl_poc_gen;
	double odn_fij;
	double max;
	double f1_max;
	double f2_max;
	double del_x;
	double del_x_u;// razmak izmeðu susjednih vrijednosti genetskog koda kod unutrašnjeg ispitnog roka
	double del_x_v;// razmak izmeðu susjednih vrijednosti genetskog koda kod vanjskih ispitnog roka
	double preklapanje_v;
	double preklapanje_u;
};