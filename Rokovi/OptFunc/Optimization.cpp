#include "stdafx.h"

#define _DIST		1

Date::Date()
{
	dan = 0;
	mj = 0;
	god = 0;
}

bool GenAlgParam::PostaviParametre( int VelPop, long IterNum, long MutMod )
{
	if( VelPop > 10 && VelPop<200 )
		VEL_POP = VelPop;
	else
		return false;

	if( IterNum > 0 && IterNum < 2500000 )
		ITER_NUM = IterNum;
	else
		return false;

	if( MutMod >= 2000 && MutMod <= 50000 )
		MUT_MODUL = MutMod;
	else
		return false;

	return true;
}

bool	OptFuncParam::PostaviParametre( double dExp, double dKazna2, double dNagrada, double dKaznaGrupa, double KaznaMinDist, double AmpBliz, double AmpPresjek, int MinDist, int MinPresj, int MaxGrupa, int MaxIspita, double KaznaMaxIspita)
{
	if( (dKazna2<0) || (dExp<0) || (dExp>=1.0) || (MinDist<5) || (MinDist>15) )
		return false;

	dExponent = dExp;
	dKaznaPodjeleNaPodrokove = dKazna2;
	dNagradaIstiDan = dNagrada;
	dKaznaGrupaPred = dKaznaGrupa;
	dKaznaMinDist = KaznaMinDist;
	dAmpBlizineIspita = AmpBliz;
	dAmpPresjekaStud = AmpPresjek;

	nMinDistance = MinDist;
	nMinPresjek = MinPresj;
	nMaxBrojStudZaGrupuPred = MaxGrupa;
	nMaxIspitaIstiDanNaIstomSmjeru = MaxIspita;
	dKaznaPrekoracenjaMaxIspitaNaIstomSmjeru = KaznaMaxIspita;

	return true;
}

OptProblem::OptProblem()			// default konstruktor
{
}

OptProblem::OptProblem( char *strFilePred, char *strFileProgram, char *strFilePresjek,char *strFileIspitiIstiDan  )
{
	int		i;

	vecNaziviPred.resize(700);
	nUkupnoPredmeta = UcitajPredmete(strFilePred);

	vecPopisPred.resize(1);
//	vecPopisPred.resize(nUkupnoPredmeta+1);
	nBrojPred = UcitajNastavniProgram(strFileProgram);

	matPresjekStud.resize(100);
	for( i=0; i<matPresjekStud.size(); i++ )
		matPresjekStud[i].resize(100);

	nUbacenoSifri = 0;
	vecSifre.resize(700);
	
	matPresjek.resize(700);
	for( i=0; i<700; i++ )
		matPresjek[i].resize(100);

	UcitajPresjek(strFilePresjek);

	ModPar.nBrIsp = 0;

	UcitajPredmeteIstiDan(strFileIspitiIstiDan);
}

OptProblem::OptProblem( char *strFilePred, char *strFileProgram, char *strFilePresjek, char *strFileIspitiIstiDan,
												Date start, Date end,
												vector<Ispit> vecSifreIspita, int nBroj,
												int BrRok, TerminRoka Vrsta )
{
	int		i;

	vecNaziviPred.resize(700);
	nUkupnoPredmeta = UcitajPredmete(strFilePred);

	vecPopisPred.resize(1);
//	vecPopisPred.resize(nUkupnoPredmeta+1);
	nBrojPred = UcitajNastavniProgram(strFileProgram);

	matPresjekStud.resize(100);
	for( i=0; i<matPresjekStud.size(); i++ )
		matPresjekStud[i].resize(100);

	nUbacenoSifri = 0;
	vecSifre.resize(700);

	matPresjek.resize(700);
	for( i=0; i<700; i++ )
		matPresjek[i].resize(100);

	UcitajPresjek(strFilePresjek);

	ModPar.PostaviDatume(start,end);
	ModPar.PostaviIspite(vecSifreIspita, vecPopisPred, nBrojPred,matIspitiIstiDan);
	ModPar.PostaviParametre(BrRok, Vrsta);

	UcitajPredmeteIstiDan(strFileIspitiIstiDan);
}

OptProblem::~OptProblem()
{
	int		i;

	for( i=0; i<matPresjekStud.size(); i++ )
		matPresjekStud[i].~vector();
	matPresjekStud.~vector();

	vecPopisSifraUIndex.~vector();
	vecPopisIndexUSifru.~vector();

	vecNaziviPred.~vector();
	vecPopisPred.~vector();
}

void	OptProblem::PostaviDatume( Date start, Date end )
{
	ModPar.PostaviDatume(start,end);
}

int	OptProblem::PostaviIspite( vector<Ispit> vecSifreIspita, int nBroj )
{
	ModPar.PostaviIspite(vecSifreIspita, vecPopisPred,nBroj, matIspitiIstiDan);

	return ModPar.nBrIsp;
}

void  OptProblem::PostaviPresjek()
{
	ModPar.PostaviPresjek(matPresjek, nUbacenoSifri, vecSifre, FuncPar.GetMinPresjek());
}

void	OptProblem::PostaviParametre( int BrRok, TerminRoka Vrsta )
{
	ModPar.PostaviParametre(BrRok, Vrsta);
}

/*************************************************************************************/
/*								Funkcije za optimiranje ( genetski algoritam )										 */
/*************************************************************************************/

int OptProblem::Optimize()
{
	int			i, j, min_ind;
	double	min;
	Gen			CrossGen(ModPar.nBrIsp, ModPar.nBrRok);

	vector<int>		a(ModPar.nBrRok);
	
	Population.resize(GenPar.GetVelPop());

	for( i=0; i<GenPar.GetVelPop(); i++ )
		Population[i] = new Gen(ModPar.nBrIsp, ModPar.nBrRok);

	GenerateInitialPopulation(Population);

	for( i=0; i<GenPar.GetIterNum(); i++ )
	{
		// Selekcija
		// iz skupa od VEL_POP jedinki, odaberi njih 3 i indekse odabranih stavi u polje 'a'
		SelectRandomNumbers(a,3,0,GenPar.GetVelPop()-1);
		
		// treba naæi najlošiju jedinku
		FunkcijaCilja		ref;

		min = Func(*Population[a[0]],ref);
		min_ind =0 ;
		for( j=1; j<3; j++ )
			if( min > Func(*Population[a[j]],ref) )
			{
				min = Func(*Population[a[j]],ref);
				min_ind = j;
			}

		// križaj dvije jedinke koje su bolje od one treæe selektirane
		if( min_ind == 0 )
			CrossGen = Krizaj( *Population[a[1]], *Population[a[2]] );
		else if( min_ind == 1 )
			CrossGen = Krizaj( *Population[a[0]], *Population[a[2]] );
		else
			CrossGen = Krizaj( *Population[a[0]], *Population[a[1]] );

		*Population[a[min_ind]] = CrossGen;

		// Mutacija jedinki iz populacije
		Mutiraj(Population);

		AfxMessageBox("Keloza");
//		if( i % 100 == 0 )
//	PrintConfig(*this, Population);
	}

	return 1;
}

Gen::Gen( int BrojIspita, int BrojRokova )
{
	Cromosom.resize(BrojIspita);
	
	TerminiIspita.resize(BrojIspita);
	for( int i=0; i<BrojIspita; i++ )
		TerminiIspita[i].resize(BrojRokova+1);

	BrojOdstupanjaPodrokova = 0;
	BrojOdstupanjaBlizineIspita = 0;
	BrojKazniOpterecenjeGrupe = 0;
}

void OptProblem::GenerateInitialPopulation( vector<Gen *> &Pop )
{
	for( int i=0; i<GenPar.GetVelPop(); i++ )
		GenerateGene(Pop[i], ModPar.nBrRok, ModPar.nBrDan);
}

void OptProblem::GenerateGene( Gen *gen, int BrRok, int BrDan )
{
	int		i, j, Range;
	long	x;
/*
	int		a, Gr1, Gr2, TerminGraniceRoka, dan, dan0, dan1, ostatak, rnd;
	int		SlijedeciDopusteniDan, term, term_gran;
	int		sif, sem, ind;

	for( i=0; i<ModPar.nBrIsp; i++ )
	{
		x = 0;

		if( BrRok == 1 )
		{
			a = rand() % ModPar.BrojTermina();
			gen->TerminiIspita[i][0] = a;

			x = SetBit(x, a);
		}
		else if( BrRok == 2 )
		{
			sif = ModPar.vecOptIsp[i];
			ind = IndexPredSaSifrom(sif);
			sem = vecPopisPred[ind].m_nSemestar;

			TerminGraniceRoka = ModPar.TerminZavrsetkaPodroka(0);
			
			a = rand() % TerminGraniceRoka;
			gen->TerminiIspita[i][0] = a;
			x = SetBit(x, a);

			dan = TerminUDan(a);
			SlijedeciDopusteniDan = dan + FuncPar.GetMinDistance();
			term = DanUTermin(SlijedeciDopusteniDan);
	
			if( sem < 5 )		// ako se radi o jesenskom ili zimskom roku i ispit je iz prva èetiri semestra
				ostatak = ModPar.TerminZavrsetkaPodroka(1) - term - 1;		// ond aima jedan dan manje
			else
				ostatak = ModPar.TerminZavrsetkaPodroka(1) - term ;

			rnd = rand() % ostatak;
			a = term + rnd;
			
			gen->TerminiIspita[i][1] = a;
			x = SetBit(x, a);
		}
		else
		{
			sif = ModPar.vecOptIsp[i];
			ind = IndexPredSaSifrom(sif);
			sem = vecPopisPred[ind].m_nSemestar;

			Range = BrDan / 3;
			Gr1 = Range;
			Gr2 = 2 * Range;

//			TerminGraniceRoka = DanUTermin(Gr1);
			TerminGraniceRoka = ModPar.TerminZavrsetkaPodroka(0);;
		
			// prvi rok
			a = rand() % TerminGraniceRoka;

//			if( a == 8 )	// ovo je nepotrebno
//				a = 7;
			
			gen->TerminiIspita[i][0] = a;
			x = SetBit(x, a);

			//	drugi rok
			dan0 = TerminUDan(a);
			if( dan0 + FuncPar.GetMinDistance() < ModPar.DanPocetkaPodroka(1) )
			{
				ostatak = ModPar.TerminZavrsetkaPodroka(1) - ModPar.TerminPocetkaPodroka(1);
				rnd = rand() % ostatak;
				term = ModPar.TerminPocetkaPodroka(1) + rnd;

				if( term == 8 && ModPar.Tip == LJETNI )
					term += rand() % 6 + 1;
			}
			else
			{
				// granièni termin za drugi rok ( prije kojega ispit ne smije biti )
				term_gran = DanUTermin(dan0 + FuncPar.GetMinDistance() );

				ostatak = ModPar.TerminZavrsetkaPodroka(1) - term_gran;
				rnd = rand() % ostatak;

				term = term_gran + rnd;
				if( term == 8 && ModPar.Tip == LJETNI )
				{
					term += rand() % 6 + 1;
				}
			}

			gen->TerminiIspita[i][1] = term;
			x = SetBit(x, term);

			// ovaj +1 u (BrTerm +1) i gore u (Gr2 + 1) je potreban zato što radimo modul ( ostatak pri dijeljenju )
			// te nam je dobiveni raspon uvijek [0,..., br-1]
			dan1 = TerminUDan(term);
			if( dan1 + FuncPar.GetMinDistance() < ModPar.DanPocetkaPodroka(2) )
			{
				if(  sem < 5 )		// ako se radi o jesenskom ili zimskom roku i ispit je iz prva èetiri semestra
					ostatak = ModPar.TerminZavrsetkaPodroka(2) - ModPar.TerminPocetkaPodroka(2) - 1;
				else
					ostatak = ModPar.TerminZavrsetkaPodroka(2) - ModPar.TerminPocetkaPodroka(2);

				rnd = rand() % ostatak;
				term = ModPar.TerminPocetkaPodroka(2) + rnd;
			}
			else
			{
				// granièni termin za drugi rok ( prije kojega ispit ne smije biti )
				term_gran = DanUTermin(dan1 + FuncPar.GetMinDistance() );

				if(  sem < 5 )		// ako se radi o jesenskom ili zimskom roku i ispit je iz prva èetiri semestra
					ostatak = ModPar.TerminZavrsetkaPodroka(2) - term_gran - 1;
				else
					ostatak = ModPar.TerminZavrsetkaPodroka(2) - term_gran;

				if( ostatak == 0 )
					rnd = -1;
				else
					rnd = rand() % ostatak;


				term = term_gran + rnd;
			}

			gen->TerminiIspita[i][2] = term;
			x = SetBit(x, term);

			int	t0 = (gen->TerminiIspita[i][0]);
			int	t1 = (gen->TerminiIspita[i][1]);
			int	t2 = (gen->TerminiIspita[i][2]);
			
			int	d0 = TerminUDan(gen->TerminiIspita[i][0]);
			int	d1 = TerminUDan(gen->TerminiIspita[i][1]);
			int	d2 = TerminUDan(gen->TerminiIspita[i][2]);

//			if( gen->TerminiIspita[i][0] == 8 || gen->TerminiIspita[i][1] == 8  || gen->TerminiIspita[i][2] == 8 )
//				AfxMessageBox("Termin na 22.6 - Generate");

			if( d1-d0 < FuncPar.GetMinDistance() )
				a = 0;
			if( d2-d1 < FuncPar.GetMinDistance() )
				a = 1;
		}
		gen->Cromosom[i] = x;
	}

*/
	vector<int> a(BrRok);

/*
//		Po ovoj shemi se selektira pocetni datum ispita, i onda se ostala dva odreðuju da budu 7, odn. 14 dana kasnije
		int min = a[2];
		if( a[0] < a[1] && a[0] < a[2] )
			min = a[0];
		else if( a[1] < a[0] && a[1] < a[2] )
			min = a[1];

		a[0] = min;
		a[1] = min + 7;
		a[2] = min + 14;
*/


//	Po ovoj shemi se za svaki podrok posebno selektira termin ispita ( znaèi, inicijalno neæe biti kršenja raspodjele po podrokovima )
	Range = ModPar.nBrTerm;
	int		dulj_roka = Range / BrRok;

	for( i=0; i<ModPar.nBrIsp; i++ )
	{
		x = 0;
		
		SelectRandomNumbers(a,BrRok,0,Range-1);

/*
		//	ovo æe ih lijepo složiti unutar podrokova		
		for( j=0; j<BrRok; j++ )
			a[j] = ( rand() % dulj_roka ) + dulj_roka * j;
*/
		x = 0;
		for( j=0; j<BrRok; j++ )
		{
			x = SetBit(x, a[j]);
			gen->TerminiIspita[i][j] = a[j];
		}

		gen->Cromosom[i] = x;

		int ind = -1;
		
		for( int k=0; k<vecFiksIspiti.size(); k++ )
			if( vecFiksIspiti[k] == ModPar.vecOptIsp[i].Sif )
				ind = k;

		if( ind >= 0 )		// ako je to ispit koji ima fiksiran dan održavanja
		{
			if( ModPar.Tip == ZIMSKI )
			{
				gen->TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][0]);
				gen->TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][1]);
			}
			else if( ModPar.Tip == PROLJETNI )
			{
				gen->TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][2]);
			}
			else if( ModPar.Tip == LJETNI )
			{
				gen->TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][3]);
				gen->TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][4]);
				gen->TerminiIspita[i][2] = DanUTermin(matFiksDani[ind][5]);
			}
			else if( ModPar.Tip == JESENSKI )
			{
				gen->TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][6]);
				gen->TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][7]);
				gen->TerminiIspita[i][2] = DanUTermin(matFiksDani[ind][8]);
			}
			else if( ModPar.Tip == JESENSKI_IZV )
			{
				gen->TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][9]);
			}
		}
	}
}

Gen OptProblem::Krizaj( Gen a, Gen b )
{
	Gen		res(ModPar.nBrIsp, ModPar.nBrRok);
	int		j, h;
//	int		bitnum, num;
	long	lAllOne, x;
//	long	c, d;


	lAllOne = 1 << 32 - 1;

	for( int i=0; i<ModPar.nBrIsp; i++ )
	{
/*
		res.Cromosom[i] = a.Cromosom[i] & b.Cromosom[i];
	
		// odredi broj bitova u rezultirajuæem kromosomu
		// ( zato da znamo koliko je bitova u oba kromosoma bilo na istom mjestu )
		bitnum = NumberOfBits(res.Cromosom[i]);
		
		if( bitnum < ModPar.nBrRok )
		{
			long				tmp;
			vector<int> arr(ModPar.nBrRok);

			tmp = 1;
			num = 0;
			SelectRandomNumbers(arr, ModPar.nBrRok-bitnum, 0, (ModPar.nBrRok-bitnum) * 2 - 1);

			for( j=0; j<32; j++ )
			{
				// da li je taj bit postavljen u rezultirajuæem kromosomu tako da su ga imala oba roditelja
				if( (res.Cromosom[i] & tmp) && (a.Cromosom[i] & tmp) )
					;						// ako jest, ne radi ništa
				else
				{
					// ako nije, treba provjeriti da li je taj bit postavljen u jednom od roditelja
					if ( ( a.Cromosom[i] & tmp ) || ( b.Cromosom[i] & tmp ) )			// da li je postavljen u jednom od roditelj
					{
						// i ako jest, da li je to onaj po redu koji je odabran da ide u dijete
						if( InSet(arr, ModPar.nBrRok-bitnum, num) )
							res.Cromosom[i] |= tmp;
						
						num++;
					}
				}
				tmp <<= 1;
			}
		}
*/	
/*		long		la, lb;

		la = a.Cromosom[i];
		lb = b.Cromosom[i];
		c = la & lb;
		
		c = a.Cromosom[i] & b.Cromosom[i];
		d = c ^ lAllOne;

		res.Cromosom[i] = ( a.Cromosom[i] & d ) | c;
*/

		x = 0;
		for( j=0; j<ModPar.nBrRok; j++ )
		{
			if( ModPar.nBrRok == 3 && ModPar.Tip == LJETNI )
			{
				// treba iskljuèiti 22.6 - praznik
				if( a.TerminiIspita[i][j] == 8 )
					a.TerminiIspita[i][j] = 9;
				if( b.TerminiIspita[i][j] == 8 )
					b.TerminiIspita[i][j] = 7;
	//				AfxMessageBox("Termin na 22.6");
			}

			if( a.TerminiIspita[i][j] == b.TerminiIspita[i][j] )
			{
				res.TerminiIspita[i][j] = a.TerminiIspita[i][j];

				x = SetBit(x, res.TerminiIspita[i][j] );
			}
			else
			{
				if( rand() % 2 == 0 )
				{
					res.TerminiIspita[i][j] = a.TerminiIspita[i][j];
					x = SetBit(x, res.TerminiIspita[i][j] );
				}
				else
				{
					res.TerminiIspita[i][j] = b.TerminiIspita[i][j];
					x = SetBit(x, res.TerminiIspita[i][j] );
				}
			}

		}

		res.Cromosom[i] = x;
/*
		num=0;
		for( j=0; j<ModPar.nBrTerm; j++ )
			if( IsBitSet(res.Cromosom[i],j) )
				res.TerminiIspita[i][num++] = j;
*/

		// ovdje sortiramo po podrokovima
		if( ModPar.nBrRok == 3 )
		{
			if( res.TerminiIspita[i][0] > res.TerminiIspita[i][1] )
			{
				h = res.TerminiIspita[i][0];
				res.TerminiIspita[i][0] = res.TerminiIspita[i][1];
				res.TerminiIspita[i][1] = h;
			}
			if( res.TerminiIspita[i][0] > res.TerminiIspita[i][2] )
			{
				h = res.TerminiIspita[i][0];
				res.TerminiIspita[i][0] = res.TerminiIspita[i][2];
				res.TerminiIspita[i][2] = h;
			}
			if( res.TerminiIspita[i][1] > res.TerminiIspita[i][2] )
			{
				h = res.TerminiIspita[i][1];
				res.TerminiIspita[i][1] = res.TerminiIspita[i][2];
				res.TerminiIspita[i][2] = h;
			}
		}
		else if( ModPar.nBrRok == 2 )
		{
			if( res.TerminiIspita[i][0] > res.TerminiIspita[i][1] )
			{
				h = res.TerminiIspita[i][0];
				res.TerminiIspita[i][0] = res.TerminiIspita[i][1];
				res.TerminiIspita[i][1] = h;
			}
		}

		int ind = -1;
		
		for( int k=0; k<vecFiksIspiti.size(); k++ )
			if( vecFiksIspiti[k] == ModPar.vecOptIsp[i].Sif )
				ind = k;

		if( ind >= 0 )		// ako je to ispit koji ima fiksiran dan održavanja
		{
			if( ModPar.Tip == ZIMSKI )
			{
				res.TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][0]);
				res.TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][1]);
			}
			else if( ModPar.Tip == PROLJETNI )
			{
				res.TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][2]);
			}
			else if( ModPar.Tip == LJETNI )
			{
				res.TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][3]);
				res.TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][4]);
				res.TerminiIspita[i][2] = DanUTermin(matFiksDani[ind][5]);
			}
			else if( ModPar.Tip == JESENSKI )
			{
				res.TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][6]);
				res.TerminiIspita[i][1] = DanUTermin(matFiksDani[ind][7]);
				res.TerminiIspita[i][2] = DanUTermin(matFiksDani[ind][8]);
			}
			else if( ModPar.Tip == JESENSKI_IZV )
			{
				res.TerminiIspita[i][0] = DanUTermin(matFiksDani[ind][9]);
			}
		}
	}
	return res;
}

void OptProblem::Mutiraj( vector<Gen *> Pop )
{
	int		i, j, RemoveBit, sif, sem, ind;
	unsigned int	NoviTerminIspita;
	long	rnd;

//	int gr, nextTerm, Range, newTerm;

	for( i=0; i<GenPar.GetVelPop(); i++ )
		for( j=0; j<ModPar.nBrIsp; j++ )
		{
			bool	found = false;
			
			for( int k=0; k<vecFiksIspiti.size(); k++ )
				if( vecFiksIspiti[k] == ModPar.vecOptIsp[j].Sif )
					found = true;

			if( found == false )		// mutirati æemo samo ako se ne radi o ispitu sa fiksiranim datumom
			{
				rnd = rand() % GenPar.GetMutModul();

				if( rnd < ModPar.nBrRok )
				{

					// najprije æemo maknuti bit iz kromosoma
					RemoveBit = Pop[i]->TerminiIspita[j][rnd];
					Pop[i]->Cromosom[j] = ClearBit(Pop[i]->Cromosom[j], RemoveBit);
	/*
					// ako se radi o prvom roku
					if( rnd == 0 )
					{
						if( ModPar.nBrRok > 1 )
						{
							nextTerm = TerminUDan(Pop[i]->TerminiIspita[j][1] );		// termin slijedeæeg ispita
							gr = ModPar.nBrDan / ModPar.nBrRok; 

							if( gr < nextTerm - FuncPar.GetMinDistance() )
								Range = gr;
							else
								Range = nextTerm - FuncPar.GetMinDistance();

							NoviTerminIspita = rand() % Range;
						}
						else
						{
							NoviTerminIspita = rand() % ModPar.nBrTerm;
						}
					}
					else if( rnd == 1 )
					{
					}
					else if( rnd == 2 )
					{
					}
	*/
	//				Pop[i]->TerminiIspita[j][rnd] = NoviTerminIspita;
	//				Pop[i]->Cromosom[j] = SetBit(Pop[i]->Cromosom[j], NoviTerminIspita);

					// sada treba paziti da nam novogeneriran termin ispita nije jedan od veæ postojeæih
					sif = ModPar.vecOptIsp[j].Sif;
					ind = IndexPredSaSifrom(sif);
					sem = vecPopisPred[ind].m_nSemestar;
				
					do
					{
						if( ModPar.nBrRok >= 2 && sem < 5 )		// ako se radi o jesenskom ili zimskom roku i ispit je iz prva èetiri semestra
							NoviTerminIspita = rand() % (ModPar.nBrTerm - 1);
						else
							NoviTerminIspita = rand() % ModPar.nBrTerm;

						if( ModPar.Tip == LJETNI && NoviTerminIspita == 8 )
							NoviTerminIspita = 9;			// opet pazimo na 22.6 - praznik
					} while( IsBitSet(Pop[i]->Cromosom[j], NoviTerminIspita) == true );

					if( NoviTerminIspita == 8 && ModPar.Tip == LJETNI )
					{
						NoviTerminIspita = 9;
	//					AfxMessageBox("Mutacija ");
					}
					Pop[i]->TerminiIspita[j][rnd] = NoviTerminIspita;
					Pop[i]->Cromosom[j] = SetBit(Pop[i]->Cromosom[j], NoviTerminIspita);

				}
			}
		}
}


/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/


double OptProblem::Func( Gen &a, FunkcijaCilja &ref )
{
	int			i, j, k, sif, ind;
	double	fd = 0.0, dist, h;
	
	a.BrojOdstupanjaBlizineIspita = 0;
	a.BrojOdstupanjaPodrokova			= 0;
	a.BrojKazniOpterecenjeGrupe		= 0;
	a.BrojIspunjenihZeljaProfesora= 0;
	a.BrojZeljaProfesora					= 0;
	a.BrojKazniZbogViseIspitaNaIstomSmjeru = 0;

	ref.BlizinaIspita = 0;
	ref.KaznePrevelikeBlizine = 0;
	ref.PresjekIspita = 0;
	ref.KazneOdstupanjaOdPodrokova = 0;
	ref.ZeljeProfesora = 0;
	ref.KazneOpterecenjaNaGrupama = 0;
	ref.KaznePrekoracenjaMaxIspitaNaIstomSmjeru = 0;

	// najprije raèunamo doprinose za ispite pojedinaèno ( da termini budu što udaljeniji, 
	// i to  ponderirano sa brojem studenata koji slušaju taj ispit
	for( i=0; i<ModPar.nBrIsp; i++ )
		for( j=0; j<ModPar.nBrRok-1; j++ )
		{
			sif = ModPar.vecOptIsp[i].Sif;
			ind = IndexPredSaSifrom(sif);
#ifdef _DIST
			dist = Dist(a.TerminiIspita[i][j],a.TerminiIspita[i][j+1]);
#else
			dist = abs(a.TerminiIspita[i][j+1] - a.TerminiIspita[i][j]);
#endif

//			fd += pow( vecPopisPred[ind].m_nBrojStud * Dist(a.TerminiIspita[i][j],a.TerminiIspita[i][j+1]), 0.5);
			if( dist < FuncPar.GetMinDistance() ) 
			{
				h = FuncPar.GetKaznaMinDist() * ( FuncPar.GetMinDistance() - dist );

				fd -= h;
				ref.KaznePrevelikeBlizine -= h;
				
				a.BrojOdstupanjaBlizineIspita++;
			}
			else
			{
				h = FuncPar.GetAmpBlizineIspita() * sqrt( vecPopisPred[ind].m_nBrojStud * dist);

				fd += h;
				ref.BlizinaIspita += h;
			}
		}

	// ako ima samo jedan rok, onda æemo ih probati ravnomjerno rasporediti
/*
	if( ModPar.nBrRok == 1 )
	{
		int		sif1, sif2, ind1, ind2;

		for( i=0; i<ModPar.nBrIsp; i++ )
			for( j=i+1; j<ModPar.nBrIsp; j++ )
			{
				sif1 = ModPar.vecOptIsp[i];
				ind1 = IndexPredSaSifrom(sif1);
				sif2 = ModPar.vecOptIsp[j];
				ind2 = IndexPredSaSifrom(sif2);
				
				dist = Dist(a.TerminiIspita[i][0],a.TerminiIspita[j][0]);

				fd += sqrt( ( vecPopisPred[ind1].m_nBrojStud + vecPopisPred[ind2].m_nBrojStud ) * dist );

				if( dist == 0 )
					fd -= 1000;
			}

	}
*/	
	// zatim æemo izraèunati kažnjavanje zbog prevelike blizine dva termina istog ispita
/*
	for( i=0; i<ModPar.nBrIsp; i++ )
		for( j=0; j<ModPar.nBrRok-1; j++ )
		{
			dist = Dist(a.TerminiIspita[i][j], a.TerminiIspita[i][j+1]);
			if( dist < FuncPar.GetMinDistance() )
//				fd -= 150 * pow((MIN_DISTANCE - dist), 3);
				fd -= 150 * (FuncPar.GetMinDistance() - dist)*(FuncPar.GetMinDistance() - dist)*(FuncPar.GetMinDistance() - dist);
		}
*/
	// zatim æemo kazniti odstupanje od podjele na podrokove

	int		NajkasnijiTermin, NajranijiTermin;

	for( k=0; k<ModPar.nBrRok-1; k++ )
	{
		// treba naæi ispit s najkasnijim terminom na ovom roku
		NajkasnijiTermin = a.TerminiIspita[0][k]; 
		for( i=1; i<ModPar.nBrIsp; i++ )
			if( a.TerminiIspita[i][k] > NajkasnijiTermin )
				NajkasnijiTermin = a.TerminiIspita[i][k];

		// zatim treba naæi ispit s najranijim terminom na slijedeæem roku
		NajranijiTermin = a.TerminiIspita[0][k+1]; 
		for( i=1; i<ModPar.nBrIsp; i++ )
			if( a.TerminiIspita[i][k+1] < NajranijiTermin )
				NajranijiTermin = a.TerminiIspita[i][k];

		// zatim treba proæi kroz sve ispite ovog roka koji su kasnije od najranijeg termina
		if( NajkasnijiTermin >= NajranijiTermin )
		{
			for( i=0; i<ModPar.nBrIsp; i++ )
				if( a.TerminiIspita[i][k] >= NajranijiTermin )
				{
					h = 100 * ( 1 + Dist(a.TerminiIspita[i][k], NajranijiTermin) );

					fd -= h;
					ref.KazneOdstupanjaOdPodrokova -= h;

					a.BrojOdstupanjaPodrokova++;
				}
		}
	}


/*
	if( ModPar.nBrRok > 1 )				// jedino ako imamo više od jednog roka možemo imati podjelu na podrokove
	{
		int	*GranicaRoka = new int[ModPar.nBrRok];	
	
		for( k=0; k<ModPar.nBrRok; k++ )
		{
			GranicaRoka[k] = ModPar.nBrDan / ModPar.nBrRok * ( k + 1 );

			for( i=0; i<ModPar.nBrIsp; i++ )
			{
				if( k == 0 )		// prvi rok 
				{
					if( TerminUDan(a.TerminiIspita[i][0]) >= GranicaRoka[0] )		// znaèi da odstupa od podjele na podrokove
					{
#ifdef _DIST
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * (TerminUDan(a.TerminiIspita[i][0]) - GranicaRoka[0]);
#else
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * abs(a.TerminiIspita[i][0] - DanUTermin(GranicaRoka[0]));
#endif

						fd -= h;
						ref.KazneOdstupanjaOdPodrokova -= h;

						a.BrojOdstupanjaPodrokova++;
					}
				}
				else if( k == ModPar.nBrRok-1 )				// zadnji rok
				{
					if( TerminUDan(a.TerminiIspita[i][k]) <= GranicaRoka[k-1] )		
					{
#ifdef _DIST
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * (GranicaRoka[k-1] - TerminUDan(a.TerminiIspita[i][k]) );
#else
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * abs(DanUTermin(GranicaRoka[k-1]) - a.TerminiIspita[i][k]);
#endif

						fd -= h;
						ref.KazneOdstupanjaOdPodrokova -= h;

						a.BrojOdstupanjaPodrokova++;
					}
				}
				else
				{
					if( TerminUDan(a.TerminiIspita[i][k]) < GranicaRoka[k-1] )		// znaèi da odstupa od podjele na podrokove
					{
#ifdef _DIST
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * (GranicaRoka[k-1] - TerminUDan(a.TerminiIspita[i][k]));
#else
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * abs(DanUTermin(GranicaRoka[k-1]) - a.TerminiIspita[i][k]);
#endif

						fd -= h;
						ref.KazneOdstupanjaOdPodrokova -= h;

						a.BrojOdstupanjaPodrokova++;
					}
					else if( TerminUDan(a.TerminiIspita[i][k]) > GranicaRoka[k] )
					{
#ifdef _DIST
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * (TerminUDan(a.TerminiIspita[i][k]) - GranicaRoka[k]);
#else
						h = FuncPar.GetKaznaPodjeleNaPodrokove() * abs((a.TerminiIspita[i][k]) - DanUTermin(GranicaRoka[k]));
#endif

						fd -= h;
						ref.KazneOdstupanjaOdPodrokova -= h;

						a.BrojOdstupanjaPodrokova++;
					}
				}
			}
		}
		delete []GranicaRoka;
	}

*/
	// sada æemo raèunati doprinos presjeka studenata
	int		ind1, ind2, sif1, sif2, sem1, sem2;
	double	coef;

	for( i=0; i<ModPar.nBrPresj; i++ )
	{
//		int		kl;
//		kl = ModPar.matPresjek[i].size();

		sif1 = ModPar.vecSifreUMatrici[i];
		ind1 = ModPar.vecSifraUIndex[ModPar.vecSifreUMatrici[i]];
		sem1 = ModPar.vecOptIsp[ModPar.vecSifraUIndex[sif1]].vecDodPod[0].Semestar;

		for( j=0; j<ModPar.matPresjek[i].size(); j++ )
			for( k=0; k<ModPar.nBrRok; k++ )
			{
				sif2 = ModPar.matPresjek[i][j].m_nSifra;
				ind2 = ModPar.vecSifraUIndex[ModPar.matPresjek[i][j].m_nSifra];
				sem2 = ModPar.vecOptIsp[ModPar.vecSifraUIndex[sif2]].vecDodPod[0].Semestar;

				// ako optimiramo zimski rok, tada æemo zanemariti presjek izmedju ispita sa zimskog i ljetnog roka
				if( ModPar.Tip == ZIMSKI && ( (sem1%2==0 && sem2%2==1) ||(sem1%2==1 && sem2%2==0) ) )
					coef = 0.3;
				else
					coef = 1.0;

//				fd += pow( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k]), 0.5 );
//				fd += sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k]));
//				int h =ModPar.matPresjek[i][j].m_nPresjek ;
#ifdef _DIST
				h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k]));
#else
				h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * abs(a.TerminiIspita[ind1][k] - a.TerminiIspita[ind2][k]));
#endif

				fd += h;
				ref.PresjekIspita += h;

				// a onda se treba pobrinuti da ne budu preblizu ispit na ovom roku i onaj drugi na slijedeæem ( ili prethodnom )
				if( k == 0 )			// ako se radi o prvom roku
				{
					if( a.TerminiIspita[ind1][k] > a.TerminiIspita[ind2][k] )
					{
#ifdef _DIST
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k+1]));
#else
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * abs(a.TerminiIspita[ind1][k] - a.TerminiIspita[ind2][k+1]));
#endif

						fd += h;
						ref.PresjekIspita += h;
					}
				}
				else if( k == ModPar.nBrRok-1 )		// ako se radi o zadnjem roku
				{
					if( a.TerminiIspita[ind1][k] < a.TerminiIspita[ind2][k] )
					{
#ifdef _DIST
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k-1]));
#else
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * abs(a.TerminiIspita[ind1][k] - a.TerminiIspita[ind2][k-1]));
#endif
				
						fd += h;
						ref.PresjekIspita += h;
					}
				}
				else
				{
					if( Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k-1]) < Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k+1]) )
					{
#ifdef _DIST
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k-1]));
#else
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * abs(a.TerminiIspita[ind1][k] - a.TerminiIspita[ind2][k-1]));
#endif

						fd += h;
						ref.PresjekIspita += h;
					}
					else
					{
#ifdef _DIST
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * Dist(a.TerminiIspita[ind1][k], a.TerminiIspita[ind2][k+1]));
#else
						h = coef * FuncPar.GetAmpPresjekaStud() * sqrt( ModPar.matPresjek[i][j].m_nPresjek * abs(a.TerminiIspita[ind1][k] - a.TerminiIspita[ind2][k+1]));
#endif
						fd += h;
						ref.PresjekIspita += h;
					}
				}	
			}
	}
	
/*	
	int			sif1, sif2, x, y;

	for( i=0; i<ModPar.nBrIsp; i++ )
		for( j=0; j<ModPar.nBrIsp; j++ )
			for( k=0; k<ModPar.nBrRok; k++ )
				if( i != j )
				{
					sif1 = ModPar.vecOptIsp[i];
					sif2 = ModPar.vecOptIsp[j];

					x = vecPopisSifraUIndex[sif1];
					y = vecPopisSifraUIndex[sif2];
					
					// najprije raèunamo doprinos od blizine na istom roku
					fd += pow( matPresjekStud[x][y] * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k]), 0.5 );
					
					// a onda se treba pobrinuti da ne budu preblizu ispit na ovom roku i onaj drugi na slijedeæem ( ili prethodnom )
					if( k == 0 )			// ako se radi o prvom roku
					{
						if( a.TerminiIspita[i][k] > a.TerminiIspita[j][k] )
							fd += pow( matPresjekStud[x][y] * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k+1]), 0.5 );
					}
					else if( k == ModPar.nBrRok-1 )		// ako se radi o zadnjem roku
					{
						if( a.TerminiIspita[i][k] < a.TerminiIspita[j][k] )
							fd += pow( matPresjekStud[x][y] * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k-1]), 0.5 );
					}
					else
					{
						if( Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k-1]) < Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k+1]) )
							fd += pow( matPresjekStud[x][y] * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k-1]), 0.5 );
						else
							fd += pow( matPresjekStud[x][y] * Dist(a.TerminiIspita[i][k], a.TerminiIspita[j][k+1]), 0.5 );
					}
				
				}

*/
	// sada treba nagraditi raspored kog kojeg su poštovane želje profesora
	int		l, m;

	for( i=0; i<ModPar.matIspitiIstiDan.size(); i++ )
	{
		for( k=0; k<ModPar.nBrRok; k++ )		// na svakom roku æemo vidjeti posebno da li su u istom temrinu
			for( l=0; l<ModPar.matIspitiIstiDan[i].size(); l++ )
				for( m=l+1; m<ModPar.matIspitiIstiDan[i].size(); m++ )
				{
					ind1 = ModPar.vecSifraUIndex[ ModPar.matIspitiIstiDan[i][l] ];
					ind2 = ModPar.vecSifraUIndex[ ModPar.matIspitiIstiDan[i][m] ];

					a.BrojZeljaProfesora++;
					if( a.TerminiIspita[ind1][k] == a.TerminiIspita[ind2][k] )
					{
						a.BrojIspunjenihZeljaProfesora++;
						h = FuncPar.GetNagradaIstiDan();

						fd += h;
						ref.ZeljeProfesora += h;
					}
				}
	}

	// da vidimo što æemo sa optereæenjem na grupama predmeta
	int		grupa;
	bool	GrupaPostoji[MAX_GRUPA];

	for( i=0; i<MAX_GRUPA; i++ )
		GrupaPostoji[i] = false;

	for( i=0; i<ModPar.matSumaPoGrupPred.size(); i++ )
		for( j=0; j<ModPar.matSumaPoGrupPred[i].size(); j++ )
		{
			ModPar.matSumaPoGrupPred[i][j].m_nBrIsp = 0;
			ModPar.matSumaPoGrupPred[i][j].m_nBrStud = 0;
		}

	for( i=0; i<ModPar.nBrIsp; i++ )
	{
		sif = ModPar.vecOptIsp[i].Sif;
		ind = IndexPredSaSifrom(sif);
		grupa = vecPopisPred[ind].m_nGrupaPred;
		GrupaPostoji[grupa] = true;

		for( k=0; k<ModPar.nBrRok; k++ )
		{
			ModPar.matSumaPoGrupPred[grupa][a.TerminiIspita[i][k]].m_nBrStud += vecPopisPred[ind].m_nBrojStud;
			ModPar.matSumaPoGrupPred[grupa][a.TerminiIspita[i][k]].m_nBrIsp++;
		}
	}

	for( i=0; i<ModPar.matSumaPoGrupPred.size(); i++ )
		if( GrupaPostoji[i] )
		{
			for( j=0; j<ModPar.nBrDan; j++ )
				if( ModPar.matSumaPoGrupPred[i][j].m_nBrStud > FuncPar.GetMaxBrojStudZaGrupuPred() &&
						ModPar.matSumaPoGrupPred[i][j].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
				{
					h = FuncPar.GetKaznaZaMaxBrojStudZaGrupuPred();

					fd -= h;
					ref.KazneOpterecenjaNaGrupama -= h;

					a.BrojKazniOpterecenjeGrupe++;
				}
		}

	// sada æemo vidjeti koliko puta je prekoraèen max. dozvoljeni broj ispita na istom smjeru u isti dan na istoj godini

	if( ModPar.Tip != ZIMSKI )
	{
		int		BrojIspitaNaGodiniNaSmjeruUDanu[5][23][25];
		int		dan, godina, smjer, max;

		memset( &BrojIspitaNaGodiniNaSmjeruUDanu[0][0][0], 0, sizeof(int) * 5 * 23 * 25 );

	//	- proði kroz sve smjerove, kroz sve godine
		for( i=0; i<ModPar.nBrIsp; i++ )
			for( k=0; k<ModPar.nBrRok; k++ )
			{
				dan = a.TerminiIspita[i][k];		// dan održavanja ispita

				for( j=0; j<ModPar.vecOptIsp[i].vecDodPod.size(); j++ )
				{
					smjer = ModPar.vecOptIsp[i].vecDodPod[j].Smjer;
					godina = (ModPar.vecOptIsp[i].vecDodPod[j].Semestar-1) / 2;
					
					if( godina <= 1 )
						max = 1;
					else
						max = FuncPar.GetMaxBrojIspitaIstiDanNaIstomSmjer();

					if( ++BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan] > max )
					{
						a.BrojKazniZbogViseIspitaNaIstomSmjeru++;

						h = FuncPar.GetKaznaPrekoracenjaMaxIspitaNaIstomSmjeru() * ( BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan] - max );

						fd -= h;
						ref.KaznePrekoracenjaMaxIspitaNaIstomSmjeru -= h;
					}
				}
			}
	}
	else
	{
		// ovaj broj æe sada biti float zato što æemo ispite iz ljetnog semestra uzimati sa manjim koeficijentom
		float	BrojIspitaNaGodiniNaSmjeruUDanu[5][23][25];
		int		dan, godina, smjer, max;

		memset( &BrojIspitaNaGodiniNaSmjeruUDanu[0][0][0], 0, sizeof(int) * 5 * 23 * 25 );

	//	- proði kroz sve smjerove, kroz sve godine
		for( i=0; i<ModPar.nBrIsp; i++ )
			for( k=0; k<ModPar.nBrRok; k++ )
			{
				dan = a.TerminiIspita[i][k];		// dan održavanja ispita

				for( j=0; j<ModPar.vecOptIsp[i].vecDodPod.size(); j++ )
				{
					smjer = ModPar.vecOptIsp[i].vecDodPod[j].Smjer;
					godina = (ModPar.vecOptIsp[i].vecDodPod[j].Semestar-1) / 2;
					
					if( godina <= 1 )
						max = 1;
					else
						max = FuncPar.GetMaxBrojIspitaIstiDanNaIstomSmjer();

					if( ModPar.vecOptIsp[i].vecDodPod[j].Semestar % 2 == 1 )
					{
						// znaèi da se radi o predmetu iz zimskog semsetra
						++BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan];					
					}
					else
					{
						BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan] += 0.5;
					}

					if( BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan] >= max )
					{
						a.BrojKazniZbogViseIspitaNaIstomSmjeru++;

						h = FuncPar.GetKaznaPrekoracenjaMaxIspitaNaIstomSmjeru() * ( BrojIspitaNaGodiniNaSmjeruUDanu[godina][smjer][dan] - max );

						fd -= h;
						ref.KaznePrekoracenjaMaxIspitaNaIstomSmjeru -= h;
					}
				}
			}
	}

	return fd;
}

int		Dist( int term1, int term2 )
{
	int		d1, d2;

	d1 = TerminUDan(term1);
	d2 = TerminUDan(term2);

	return abs(d2-d1);
}

/*
		Termini kreæu od 0, u slijedeæem obliku
				0 - PON
				1 - UTO
				2 - SRI
				3 - ÆET
				4 - PET
				5 - PON
*/
int		TerminUDan( int term )
{
	int	dan;

//	dan = ((term-1) / 5) * 7 + (term % 5);
	dan = ((term) / 5) * 7 + (term % 5) ;
	
	return dan;
}

// NAPOMENA : funkcija daje krive rezultate ukoliko se traži termin koji odgovara suboti ili nedjelji
//   modifikacija : ukoliko se traži termin koji odgovara suboti ili nedjelju, funkcija vraæa termin od ponedjeljka
/*
		Dani poèinju s brojenjem od 0 :
				0 - PON
				1 - UTO
				...
				5 - SUB
				6 - NED
				7 - PON
				...
*/
int		DanUTermin( int dan )
{
	if( (dan+1) % 7 == 0 )
	{
//		if( dan < 10 )
			return ((dan + 1) / 7) * 5;
//		else
//			return ((dan - 2) / 7) * 5;
	}
	else if( (dan+1) % 7 == 6 )
	{
//		if( dan < 10 )
			return ((dan + 2) / 7) * 5;
//		else
//			return ((dan - 1) / 7) * 5;
	}
	else
		return (dan / 7) * 5 + ((dan) % 7);
}

bool IsVikend( int dan )
{
	if( dan % 7 == 0 || (dan+1) % 7 == 0)
		return true;
	else
		return false;
}

int		OptProblem::IndexPredSaSifrom( int sifra )
{
	int		i;

	for( i=0; i<nBrojPred; i++ )
		if( vecPopisPred[i].m_nSifra == sifra )
			return i;

	return -1;
}

bool	OptProblem::PartOfOptProblem( int sifra )
{
	if( IndexPredSaSifrom(sifra) < 0 )
		return false;
	else
		return true;
}

/*************************************************************************************/


/*************************************************************************************/
/*
void PrintPopulation( Gen	Pop[] )
{
	int		i, j;

	for( i=0; i<BR_ISPITA; i++ )
	{
		printf("\n");
		for( j=0; j<BR_TERMINA; j++ )
			if( IsBitSet(Pop[0].Cromosom[i], j) )
				printf(" x ");
			else
				printf("   ");

		for( j=0; j<BR_ROKOVA; j++ )
			printf("  %d ", Pop[0].TerminiIspita[i][j] );
	}
}

*/
/*************************************************************************************/
//						Pomoæne funkcije
/*************************************************************************************/

long SetBit( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;
	
	return (a | x);
}

long ClearBit( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;
	x = ~x;
	
	return (a & x);
}

bool IsBitSet( long a, int n )
{
	long		x;

	x = 1;
	x = x << n;

	if( a & x )
		return true;
	else
		return false;
}

int NumberOfBits( long a )
{
	int		res=0;
	long	tmp;

	tmp = 1;
	for( int i=0; i<32; i++ )
	{
		if ( a & tmp )
			res++;

		tmp <<= 1;
	}

	return res;
}

void SelectRandomNumbers( vector<int> &a, int num, int start, int end )
{
	int		i, j;
	bool	bAlreadyGenerated;
	
	for( i=0; i<num; i++ )
	{
		do
		{
			bAlreadyGenerated=false;
		
			a[i] = rand() % ( end-start + 1) + start;

			for( j=0; j<i; j++ )
				if( a[j] == a[i] )
					bAlreadyGenerated = true;
		}
		while( bAlreadyGenerated == true );
	}
}

bool InSet( int a[], int num, int br )
{
	for( int i=0; i<num; i++ )
		if( a[i] == br )
			return true;

	return false;
}

bool InSet( vector<int> a, int num, int br )
{
	for( int i=0; i<num; i++ )
		if( a[i] == br )
			return true;

	return false;
}

bool	OptProblem::PostaviRezultatOptimizacije( vector< Zapis > &vecRez )
{
	int			i, max_ind;
	double	max, f;

	vecRez.resize(ModPar.nBrIsp+1);

	// najprije treba naæi najbolju jedinku
	FunkcijaCilja		ref;

	max = Func(*Population[0], ref);
	max_ind = 0;
	for( i=1; i<GenPar.GetVelPop(); i++ )
	{
		f = Func(*Population[i], ref);
		if( f > max )
		{
			max = f;
			max_ind = i;
		}
	}

	for( i=0; i<ModPar.nBrIsp; i++ )
	{
		vecRez[i].m_nSifraIspita = ModPar.vecOptIsp[i].Sif;

		switch( ModPar.Tip )
		{
			case ZIMSKI : vecRez[i].m_arrDatZim[0] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][0]) - 1);
										vecRez[i].m_arrDatZim[1] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][1]) - 1);
										vecRez[i].m_arrDanZim[0] = TerminUDan(Population[max_ind]->TerminiIspita[i][0]);
										vecRez[i].m_arrDanZim[1] = TerminUDan(Population[max_ind]->TerminiIspita[i][1]);

				break;
			case PROLJETNI :	vecRez[i].m_arrDatProlj = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][0]) - 1);
												vecRez[i].m_arrDanProlj = (TerminUDan(Population[max_ind]->TerminiIspita[i][0]));
				break;
			case LJETNI :	vecRez[i].m_arrDatLjet[0] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][0]) - 1);
										vecRez[i].m_arrDatLjet[1] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][1]) - 1);
										vecRez[i].m_arrDatLjet[2] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][2]) - 1);
										vecRez[i].m_arrDanLjet[0] = (TerminUDan(Population[max_ind]->TerminiIspita[i][0]));
										vecRez[i].m_arrDanLjet[1] = (TerminUDan(Population[max_ind]->TerminiIspita[i][1]));
										vecRez[i].m_arrDanLjet[2] = (TerminUDan(Population[max_ind]->TerminiIspita[i][2]));
				break;
			case JESENSKI : vecRez[i].m_arrDatJes[0] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][0]) - 1);
											vecRez[i].m_arrDatJes[1] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][1]) - 1);
											vecRez[i].m_arrDatJes[2] = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][2]) - 1);
											vecRez[i].m_arrDanJes[0] = (TerminUDan(Population[max_ind]->TerminiIspita[i][0]));
											vecRez[i].m_arrDanJes[1] = (TerminUDan(Population[max_ind]->TerminiIspita[i][1]));
											vecRez[i].m_arrDanJes[2] = (TerminUDan(Population[max_ind]->TerminiIspita[i][2]));
				break;
			case JESENSKI_IZV : vecRez[i].m_arrDatJesIzv = ModPar.dateStartDate + (TerminUDan(Population[max_ind]->TerminiIspita[i][0]) - 1);
													vecRez[i].m_arrDanJesIzv = (TerminUDan(Population[max_ind]->TerminiIspita[i][0]));
				break;
		}
	}

	return true;
}

int		BrojRokova( TerminRoka	Rok )
{
	switch( Rok )
	{
		case JESENSKI_IZV : return 1;
		case ZIMSKI : return 2;
		case PROLJETNI : return 1;
		case LJETNI : return 3;
		case JESENSKI : return 3;
	}
	return 0;
}

int		BrojDana( TerminRoka	Rok )
{
	switch( Rok )
	{
		case JESENSKI_IZV : return 7;
		case ZIMSKI : return 4*7;
		case PROLJETNI : return 7;
		case LJETNI : return 5*7;
		case JESENSKI : return 4*7;
	}
	return 0;
}

int		BrojDanaZaPrikaz( TerminRoka Rok )
{
	switch( Rok )
	{
		case JESENSKI_IZV : return 5;
		case ZIMSKI : return 3*7+3 + 1;
		case PROLJETNI : return 4 ;
		case LJETNI : return 5*7-4 + 1;
		case JESENSKI : return 4*7-4 + 1;
	}
	return 0;
}


int		BrojTermina( TerminRoka	Rok )
{
	switch( Rok )
	{
		case JESENSKI_IZV : return 5;
		case ZIMSKI : return 4*5;
		case PROLJETNI : return 5;
		case LJETNI : return 5*5;
		case JESENSKI : return 4*5;
	}
	return 0;
}

