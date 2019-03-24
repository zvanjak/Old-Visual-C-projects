//klasa koja implementira jednostruko povezanu listu 
//koja sadr�i podatke o fiksiranim ispitima nekog kolegija 
class Fiks_Ispit{
public:
	Fiks_Ispit();
	~Fiks_Ispit();
	void destrukt();
	//dodavanje novog fiks.kolegija
	void dodaj_cvor(int sif, int d_r_0, int d_r_1, int d_r_2);
	//promjena datuma odr�avanja nekog kolegija koji je ve� u listi
	void promjeni_cvor(int sif, int d_r_0, int d_r_1, int d_r_2);
	//izbacivanje iz liste datuma nekog kolegija
	void oduzmi_cvor(int sif);
	//postavljanje pokaziva�a na prvi �lan liste
	void reset();
	//dohva�anje datuma kolegija na kojeg trenuta�no gleda pokaziva� "trenutni"
	int& datum(int rok);
	int ispit_cvor();
	void set_param(int k_r_0, int k_r_1, int k_r_2);
	void set_param(int k_r_0, int k_r_1);
	void set_param(int k_r_0);
	int get_r_d(int rok);
	
	//pokaziva�i na jednostruko povezanu listu
	cvor* glava;
	cvor* trenutni;
	cvor* predhodni;
	cvor* sljedeci;
	cvor* predhodni_k;
	cvor* kraj;
	int br_cvor;//broj ispita u toj listi
};

