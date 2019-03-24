#include "stdafx.h"
#include "OptimizationData.h"


/***************************************************************************************/

Gen::Gen( int inBrIsp, int inBrPodrok )
{
	m_vecpnTerminiIspita.resize(inBrIsp);
	m_vecbFiksniTermini.resize(inBrIsp);
	
	for( int i=0; i<inBrIsp; i++ ) {
		m_vecpnTerminiIspita[i] = new int[inBrPodrok];
		m_vecbFiksniTermini[i] = false;
	}

	m_nBrIsp = inBrIsp;
	m_nBrPodrok = inBrPodrok;
}

Gen::~Gen()
{
	for( int i=0; i<m_nBrIsp; i++ )
		delete [](m_vecpnTerminiIspita[i]);
}

bool	Gen::fiksirajTermin( int brIspita )
{
	if( brIspita > 0 && brIspita < m_vecpnTerminiIspita.size() )
		m_vecbFiksniTermini[brIspita] = true;
	else
		return false;

	return true;
}

bool	Gen::calcStatistic( Gen & )
{
	return true;
}

int Gen::GetTermin( int inBrIsp, int inBrPodrok ){
	assert( (inBrIsp >= 0 && inBrIsp < m_nBrIsp) && (inBrPodrok >= 0 && inBrPodrok < m_nBrPodrok) );
	return m_vecpnTerminiIspita[inBrIsp][inBrPodrok];
}

bool	Gen::IsFiksiranTermin( int inBrIsp ){
	assert( inBrIsp >= 0 && inBrIsp < m_nBrIsp );
	return m_vecbFiksniTermini[inBrIsp];
}

bool	Gen::IsTermSet( int brIsp, int Term ){
	for( int i=0; i<m_nBrPodrok; i++ )
		if( Term == GetTermin(brIsp, i) )
			return true;

	return false;
}

void	Gen::GenerateGeneTerm( CalendarData &calData )
{
	int		i, j;
	vector<int>		a;

	a.resize(calData.BrojTermina());

	for( i=0; i<m_nBrIsp; i++ )
	{
		SelectRandomNumbers(a, m_nBrPodrok, 0, calData.BrojTermina()-1);

		for( j=0; j<m_nBrPodrok; j++ )
			m_vecpnTerminiIspita[i][j] = a[j];
	}
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

/***************************************************************************************/

void	GenAlgParam::SetVelPop( int inVelPop )
{
	assert(inVelPop > 0);
	m_nVelPop = inVelPop;
}

void	GenAlgParam::SetIterNum( int inIterNum )
{
	assert(inIterNum > 0);
	m_lIterNum = inIterNum;
}

void	GenAlgParam::SetMutModul( int inMutModul )
{
	assert(inMutModul > 0);
	m_lMutModul = inMutModul;
}

void	GenAlgParam::PostaviParametre( int inVelPop, long inIterNum, long inMutModul )
{
	SetVelPop(inVelPop);
	SetIterNum(inIterNum);
	SetMutModul(inMutModul);
}


/***************************************************************************************/
/*
OptimizationData::OptimizationData( int inBrIsp, int inBrTerm, int inBrPodrok, int inVelPop )
{
	int		i;

	assert( inVelPop > 0 );

	genParam.SetVelPop(inVelPop);
	Population.resize(inVelPop);
	for( i=0; i<inVelPop; i++ )
		Population[i] = new Gen(inBrIsp, inBrPodrok);

	brIsp = inBrIsp;
	brTerm = inBrTerm;
	brPodrok = inBrPodrok;

	matSumaPoGrupPred.resize(MAX_GRUPA);			// nema više od 40 grupa predmeta;
	for( i=0; i<MAX_GRUPA; i++ )
		matSumaPoGrupPred[i].resize(inBrTerm);
}
*/

Gen&	OptimizationData::GetGene( int i )
{
	assert( i>=0 && i<genParam.GetVelPop() );

	return *Population[i];
}


void	OptimizationData::GenerateInitialPopulation( void )
{
	CalendarData	calData;

	for( int i=0; i<genParam.GetVelPop(); i++ )
		Population[i]->GenerateGeneTerm(calData);
}




OptimizationData::OptimizationData( ProblemData &problem, 
																		SelectedProblemDescr &opis, 
																		CalendarData	&cal,
																		OptFuncParam	&func,
																		int inVelPop )
{
	int			i;

	assert( inVelPop > 0 );

	calData = cal;
	FuncPar = func;

	PostaviPodatkeModela(problem, opis);

	brIsp = modelData.BrojIspita();
	brTerm = cal.BrojTermina();
	brPodrok = cal.BrojPodrokova();

	genParam.SetVelPop(inVelPop);
	Population.resize(inVelPop);
	for( i=0; i<inVelPop; i++ )
		Population[i] = new Gen(brIsp, cal.BrojPodrokova());

	matSumaPoGrupPred.resize(MAX_GRUPA);			// nema više od 40 grupa predmeta;
	for( i=0; i<MAX_GRUPA; i++ )
		matSumaPoGrupPred[i].resize(brTerm);
}


bool	OptimizationData::PostaviPodatkeModela( ProblemData &probData, SelectedProblemDescr &modelDescr )
{
	int			i, j, nSif;
	string	szNaziv;

	// proæi æemo kroz sve ispite u problemu, i one koji su dio modela staviti u 'model'
	for( i=0; i<probData.vecPredmeti.size(); i++ )
		for( j=0; j<probData.vecPredmeti[i].getBrojDodPod(); j++ )
			if( modelDescr.IsPartOfModel(probData.vecPredmeti[i].getSifra(), probData.vecPredmeti[i].getDodPod(j)) == true ) 
			{
				nSif = probData.vecPredmeti[i].getSifra();
				szNaziv = probData.vecPredmeti[i].getNaziv();

				modelData.addPredmet(nSif, szNaziv, probData.vecPredmeti[i].getDodPod(j));
			}


	// postavljamo presjeke izmeðu ispita u modelu
	int		sif1;
	ParSifraPresjek		par;
	for( i=0; i<probData.Presjek.getBrojRedaka(); i++ )
		for( j=0; j<probData.Presjek.getBrojPresjeka(i); j++ ) 
		{
			sif1 = probData.Presjek.getSifraRetka(i);
			par  = probData.Presjek.getPresjekRedStup(i,j);
			
			// ne treba provjeravati da li su ispiti dio modela jer æe to provjeriti sama funkcija
			// prije dodavanja u popis
			modelData.addPresjek( sif1, par.m_nSifra, par.m_nPresjek );
		}
	

	// sada treba još postaviti i ispite za koje bi bilo dobro da budu isti dan, ali samo one ubaciti
	// koji su dio opt. problema
	int		rownum=0, row_size;
	int		first=-1;
	int		second=-1;

	for( i=0; i<probData.matIspitiIstiDan.size(); i++ )
	{
		first = -1;
		second = -1;
		for( j=0; j<probData.matIspitiIstiDan[i].size(); j++ )
			if( modelData.IsPartOfProblem(probData.matIspitiIstiDan[i][j]) )
			{
				if( first == -1 )		// to je prvi kojeg ubacujemo u redak ( neæemo ga ubacivati dok ne naðemo i drugoga )
					first = probData.matIspitiIstiDan[i][j];
				else if( second == -1 )
				{
					// onda ubaci oba
					modelData.matIspitiIstiDan.resize(rownum+1);
					modelData.matIspitiIstiDan[rownum].resize(2);
					
					modelData.matIspitiIstiDan[rownum][0] = first;
					second = probData.matIspitiIstiDan[i][j];
					modelData.matIspitiIstiDan[rownum][1] = second;

					row_size = 2;
					rownum++;
				}
				else	// ovo nam je znaèi veæ treæi ( ili n-ti ) kojeg ubacujemo u ovaj redak
				{
					modelData.matIspitiIstiDan[rownum-1].resize(row_size + 1);
					modelData.matIspitiIstiDan[rownum-1][row_size++] = probData.matIspitiIstiDan[i][j];
				}
			}
	}
	return true;
}

void	OptimizationData::Krizaj( Gen &a, Gen &b, Gen &res )
{
	int		i, j;

	for( i=0; i<modelData.BrojIspita(); i++ )
		for( j=0; j<calData.BrojPodrokova(); j++ )
		{
			// ako je u obe jedinke termin ispita isti, onda zadrži taj termin u rezultirajuæoj jedinki
			if( a.GetTermin(i,j) == b.GetTermin(i,j) )
				res.SetTermin(i, j, a.GetTermin(i,j) );
			else
			{
				// ukoliko se termin razlikuje, onda odaberi termin od jedne od jedinki
				if( rand() % 2 == 0 )
					res.SetTermin(i, j, a.GetTermin(i,j) );
				else
					res.SetTermin(i, j, b.GetTermin(i,j) );
			}
		}
}

void	OptimizationData::Mutiraj( void )
{
	int		i, j, sif, sem, ind;
	long	rnd;
	bool	found;
	int		NoviTerminIspita;

	for( i=0; i<GetVelPop(); i++ )
		for( j=0; j<modelData.BrojIspita(); j++ )
		{
			found = false;
			// TODO
			// provjeriti da li se radi o ispitu sa fiksiranim datumom održavanja
			found = Population[i]->IsFiksiranTermin(j);

			if( found == false )		// mutirati æemo samo ako se ne radi o ispitu sa fiksiranim datumom
			{
				rnd = rand() % GetMutModul();

				if( rnd < calData.BrojPodrokova() )
				{
					// sada treba paziti da nam novogeneriran termin ispita nije jedan od veæ postojeæih
					sif = modelData.vecPredmeti[j].getSifra();
					ind = modelData.vecSifraUIndex[sif];
					sem = modelData.vecPredmeti[ind].getSemestar(0);
				
					do
					{
							NoviTerminIspita = rand() % calData.BrojTermina();
							// TODO treba provjeriti za praznike ..
							// provjeravamo da li je taj novi termin veæ prisutan
					} while( Population[i]->IsTermSet(j,NoviTerminIspita) == true );

					Population[i]->SetTermin(j, rnd, NoviTerminIspita);
				}
			}
		}
}

double	OptimizationData::Func( Gen &a )
{
	int			i, j, k;
	int			dist;
	double	fd, h;

	fd = 0;
	
	a.m_funcData.BlizinaIspita = 0;
	a.m_funcData.KaznePrevelikeBlizine = 0;
	a.m_funcData.PresjekIspita = 0;
	a.m_funcData.KazneOdstupanjaOdPodrokova = 0;
	a.m_funcData.ZeljeProfesora = 0;
	a.m_funcData.KazneOpterecenjaNaGrupama = 0;
	a.m_funcData.KaznePrekoracenjaMaxIspitaNaIstomSmjeru = 0;
	
	a.m_statData.brPrevelikaBlizinaIspita									= 0;
	a.m_statData.brOdstupanjaOdPodrokova									= 0;
	a.m_statData.brPrekoracenjeOpterecenjaNaGrupiPredmeta	= 0;
	a.m_statData.brIspunjeneZeljeProfesora								= 0;


	// najprije raèunamo doprinose za ispite pojedinaèno ( da termini budu što udaljeniji, 
	// i to  ponderirano sa brojem studenata koji slušaju taj ispit
	for( i=0; i<modelData.BrojIspita(); i++ )
		for( j=0; j<calData.BrojPodrokova()-1; j++ )
		{
			dist = Dist(a.GetTermin(i,j), a.GetTermin(i,j+1));

			if( dist < FuncPar.GetMinDistance() ) 
			{
				h = FuncPar.GetKaznaMinDist() * ( FuncPar.GetMinDistance() - dist );

				fd -= h;
				a.m_funcData.KaznePrevelikeBlizine -= h;
				a.m_statData.brPrevelikaBlizinaIspita++;
			}
			else
			{
				h = FuncPar.GetAmpBlizineIspita() * sqrt( modelData.vecPredmeti[i].getBrojStud() * dist);

				fd += h;
				a.m_funcData.BlizinaIspita += h;
			}
		}

	int		NajkasnijiTermin, NajranijiTermin;

	for( k=0; k<calData.BrojPodrokova()-1; k++ )
	{
		// treba naæi ispit s najkasnijim terminom na ovom roku
		NajkasnijiTermin = a.GetTermin(0, k); 
		for( i=1; i<modelData.BrojIspita(); i++ )
			if( a.GetTermin(i, k) > NajkasnijiTermin )
				NajkasnijiTermin = a.GetTermin(i ,k);

		// zatim treba naæi ispit s najranijim terminom na slijedeæem roku
		NajranijiTermin = a.GetTermin(0, k+1);
		for( i=1; i<modelData.BrojIspita(); i++ )
			if( a.GetTermin(i, k+1) < NajranijiTermin )
				NajranijiTermin = a.GetTermin(i, k);

		// zatim treba proæi kroz sve ispite ovog roka koji su kasnije od najranijeg termina
		if( NajkasnijiTermin >= NajranijiTermin )
		{
			for( i=0; i<modelData.BrojIspita(); i++ )
				if( a.GetTermin(i, k) >= NajranijiTermin )
				{
					h = FuncPar.GetKaznaPodjeleNaPodrokove() * ( 1 + Dist(a.GetTermin(i, k), NajranijiTermin) );

					fd -= h;
					a.m_funcData.KazneOdstupanjaOdPodrokova -= h;
					a.m_statData.brOdstupanjaOdPodrokova++;
				}
		}
	}

	// sada æemo raèunati doprinos presjeka studenata
	int			ind1, ind2, sif1, sif2;
	double	coef;
	ParSifraPresjek		par;

	for( i=0; i<modelData.Presjek.getBrojRedaka(); i++ )
	{
		sif1 = modelData.Presjek.getSifraRetka(i);
		ind1 = modelData.vecSifraUIndex[sif1];

//		sem1 = ModPar.vecOptIsp[ModPar.vecSifraUIndex[sif1]].vecDodPod[0].Semestar;

		for( j=0; j<modelData.Presjek.getBrojPresjeka(i); j++ )
			for( k=0; k<calData.BrojPodrokova(); k++ )
			{
				par = modelData.Presjek.getPresjekRedStup(i,j);
				sif2 = par.m_nSifra;
				ind2 = modelData.vecSifraUIndex[sif2];
				
//				sem2 = ModPar.vecOptIsp[ModPar.vecSifraUIndex[sif2]].vecDodPod[0].Semestar;

				// ako optimiramo zimski rok, tada æemo zanemariti presjek izmedju ispita sa zimskog i ljetnog roka
				coef = 1.0;
/*
				if( ModPar.Tip == ZIMSKI && ( (sem1%2==0 && sem2%2==1) ||(sem1%2==1 && sem2%2==0) ) )
					coef = 0.3;
				else
					coef = 1.0;
*/
				h		= coef * FuncPar.GetAmpPresjekaStud() * sqrt( par.m_nPresjek * Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k)));
				fd += h;
				a.m_funcData.PresjekIspita += h;

				// a onda se treba pobrinuti da ne budu preblizu ispit na ovom roku i onaj drugi na slijedeæem ( ili prethodnom )
				if( k == 0 )			// ako se radi o prvom roku
				{
					if( a.GetTermin(ind1,k) > a.GetTermin(ind2,k) )
					{
						h		= coef * FuncPar.GetAmpPresjekaStud() * sqrt( par.m_nPresjek * Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k+1)));
						fd += h;
						a.m_funcData.PresjekIspita += h;
					}
				}
				else if( k == calData.BrojPodrokova()-1 )		// ako se radi o zadnjem roku
				{
					if( a.GetTermin(ind1,k) < a.GetTermin(ind2,k) )
					{
						h		= coef * FuncPar.GetAmpPresjekaStud() * sqrt( par.m_nPresjek * Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k-1)));
						fd += h;
						a.m_funcData.PresjekIspita += h;
					}
				}
				else
				{
					if( Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k-1)) < Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k+1)) )
					{
						h		= coef * FuncPar.GetAmpPresjekaStud() * sqrt( par.m_nPresjek * Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k-1)));
						fd += h;
						a.m_funcData.PresjekIspita += h;
					}
					else
					{
						h		= coef * FuncPar.GetAmpPresjekaStud() * sqrt( par.m_nPresjek * Dist(a.GetTermin(ind1,k), a.GetTermin(ind2,k+1)));
						fd += h;
						a.m_funcData.PresjekIspita += h;
					}
				}	
			}
	}

	// sada treba nagraditi raspored kog kojeg su poštovane želje profesora
	int		l, m;

	for( i=0; i<modelData.matIspitiIstiDan.size(); i++ )
	{
		for( k=0; k<calData.BrojPodrokova(); k++ )		// na svakom roku æemo vidjeti posebno da li su u istom temrinu
			for( l=0; l<modelData.matIspitiIstiDan[i].size(); l++ )
				for( m=l+1; m<modelData.matIspitiIstiDan[i].size(); m++ )
				{
					ind1 = modelData.vecSifraUIndex[ modelData.matIspitiIstiDan[i][l] ];
					ind2 = modelData.vecSifraUIndex[ modelData.matIspitiIstiDan[i][m] ];

					a.m_statData.brZeljaProfesora++;

					if( a.GetTermin(ind1,k) == a.GetTermin(ind2,k) )
					{
						a.m_statData.brIspunjeneZeljeProfesora++;

						h		= FuncPar.GetNagradaIstiDan();
						fd += h;
						a.m_funcData.ZeljeProfesora += h;
					}
				}
	}
/*
	// da vidimo što æemo sa optereæenjem na grupama predmeta
	int		grupa;
	valarray<bool>	*GrupaPostoji = new valarray<bool>(false, MAX_GRUPA);

	for( i=0; i<matSumaPoGrupPred.size(); i++ )
		for( j=0; j<matSumaPoGrupPred[i].size(); j++ )
		{
			matSumaPoGrupPred[i][j].m_nBrIsp = 0;
			matSumaPoGrupPred[i][j].m_nBrStud = 0;
		}

	for( i=0; i<modelData.BrojIspita(); i++ )
	{
		grupa = modelData.vecPredmeti[i].getGrupaPred();
		(*GrupaPostoji)[grupa] = true;

		for( k=0; k<calData.BrojPodrokova(); k++ )
		{
			matSumaPoGrupPred[grupa][a.GetTermin(i, k)].m_nBrStud += modelData.vecPredmeti[i].getBrojStud();
			matSumaPoGrupPred[grupa][a.GetTermin(i, k)].m_nBrIsp++;
		}
	}

	for( i=0; i<matSumaPoGrupPred.size(); i++ )
		if( (*GrupaPostoji)[i] )
		{
			for( j=0; j<calData.BrojDana(); j++ )
				if( matSumaPoGrupPred[i][j].m_nBrStud > FuncPar.GetMaxBrojStudZaGrupuPred() &&
						matSumaPoGrupPred[i][j].m_nBrIsp > 1 )				// ako ima više od jednog ispita u istom danu, naravno
				{
					h = FuncPar.GetKaznaZaMaxBrojStudZaGrupuPred();

					fd -= h;
					a.m_funcData.KazneOpterecenjaNaGrupama -= h;

					a.m_statData.brPrekoracenjeOpterecenjaNaGrupiPredmeta++;
				}
		}
	delete GrupaPostoji;
*/
	return fd;
}

