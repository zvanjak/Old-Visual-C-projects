//klasa koja implementira jednostruko povezanu listu 
//koja sadrži podatke o fiksiranim ispitima nekog kolegija 
class Fiks_Ispit{
public:
	Fiks_Ispit();
	~Fiks_Ispit();
	void destrukt();
	//dodavanje novog fiks.kolegija
	void dodaj_cvor(int sif, int d_r_0, int d_r_1, int d_r_2);
	//promjena datuma održavanja nekog kolegija koji je veæ u listi
	void promjeni_cvor(int sif, int d_r_0, int d_r_1, int d_r_2);
	//izbacivanje iz liste datuma nekog kolegija
	void oduzmi_cvor(int sif);
	//postavljanje pokazivaèa na prvi èlan liste
	void reset();
	//dohvaæanje datuma kolegija na kojeg trenutaèno gleda pokazivaè "trenutni"
	int& datum(int rok);
	int ispit_cvor();
	void set_param(int k_r_0, int k_r_1, int k_r_2);
	void set_param(int k_r_0, int k_r_1);
	void set_param(int k_r_0);
	int get_r_d(int rok);
	
	//pokazivaèi na jednostruko povezanu listu
	cvor* glava;
	cvor* trenutni;
	cvor* predhodni;
	cvor* sljedeci;
	cvor* predhodni_k;
	cvor* kraj;
	int br_cvor;//broj ispita u toj listi
};

