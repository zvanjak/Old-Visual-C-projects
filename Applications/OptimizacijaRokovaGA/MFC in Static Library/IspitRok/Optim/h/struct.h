// podatkovne strukture - komentirane u diplomskom radu

struct cvor
{
	int sifra;
	cvor* sljedeci;
	int datum_rok[3];

};

struct mut_korak_gran
{
	int ppmb;
	int ppmk;
	int zpmb;
	int zpmk;
	int korak_k;
	int korak_b;
};

struct psg_korak_gran
{
	int ppsg;
	int zpsg;
	int korak;
};

struct granice
{
	int gor_gran_rok;
	int dol_gran_rok;
	int dol_gran_rok_1;
	int gor_gran_rok_1;
	int dol_gran_rok_2;
	int gor_gran_rok_2;
	int dol_gran_rok_3;
	int gor_gran_rok_3;
};