#ifndef __MODEL_DESCRIPTION
#define	__MODEL_DESCRIPTION		1


class OptFuncParam {
public:
	OptFuncParam() {	dExponent = 0.5;
										dKaznaPodjeleNaPodrokove = 3000;
										dKaznaMinDist = 3000;
										dKaznaGrupaPred = 8000;
										dNagradaIstiDan = 10000;
										dAmpBlizineIspita = 5;
										dAmpPresjekaStud = 5;
										nMinDistance = 8;
										nMinPresjek = 20;
										nMaxBrojStudZaGrupuPred = 300;
										nMaxIspitaIstiDanNaIstomSmjeru = 2;
										dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru = 2000; }

	bool		PostaviParametre( double, double, double, double, double, double, double, int, int, int, int, double );

	double	GetExponent() { return dExponent; }
	double	GetKaznaPodjeleNaPodrokove() { return dKaznaPodjeleNaPodrokove; }
	double	GetNagradaIstiDan() { return dNagradaIstiDan; }
	double	GetKaznaZaMaxBrojStudZaGrupuPred() { return dKaznaGrupaPred; }
	double	GetKaznaMinDist() { return dKaznaMinDist; }
	double	GetAmpBlizineIspita() { return dAmpBlizineIspita; }
	double	GetAmpPresjekaStud() { return dAmpPresjekaStud; }
	
	int			GetMinDistance() { return nMinDistance; }
	int			GetMinPresjek() { return nMinPresjek; }
	int			GetMaxBrojStudZaGrupuPred() { return nMaxBrojStudZaGrupuPred; }
	int			GetMaxBrojIspitaIstiDanNaIstomSmjer() { return nMaxIspitaIstiDanNaIstomSmjeru; }
	double	GetKaznaPrekoracenjaMaxIspitaNaIstomSmjeru() { return 	dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru; }


private:
	double	dExponent;								// 0.5
	double	dKaznaPodjeleNaPodrokove;	// 100
	double	dNagradaIstiDan;					// 100
	double	dKaznaGrupaPred;					// 100
	double	dKaznaMinDist;						// 1000
	double	dAmpBlizineIspita;
	double	dAmpPresjekaStud;

	int			nMinDistance;							// 8
	int			nMinPresjek;
	int			nMaxBrojStudZaGrupuPred;	// 200
	int			nMaxIspitaIstiDanNaIstomSmjeru;
	double	dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru;
};

class	SelectedProblemDescr {
public:
	// vraæa TRUE ako je predmet sa tom šifrom dio modela, FALSE ako nije
	bool	IsPartOfModel( int Sifra, IspitDodPodaci	dodPod  );
};
// funkcija definirana u LoadData.cpp

#endif
