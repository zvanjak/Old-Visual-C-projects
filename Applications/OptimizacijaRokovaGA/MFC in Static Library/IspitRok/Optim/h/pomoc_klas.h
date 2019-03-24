
//klase koje sadrže polja koja se alociraju u konstruktorima, a velièina se sprema 
// u varijablu "duljina"

class Polje_I{
public:
	Polje_I();
	Polje_I(int n);
	~Polje_I();
	int& operator [](int i);
	void set0();
	int *m_polje;
	int duljina;
};


class Polje_D{
public:
	Polje_D();
	Polje_D(int n);
	~Polje_D();
	void destrukt();
	double& operator [](int i);
	double *m_polje;
	int duljina;
};