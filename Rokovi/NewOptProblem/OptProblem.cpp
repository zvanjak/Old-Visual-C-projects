#include "stdafx.h"
#include "OptProblem.h"


OptProblem::OptProblem()
{
}

OptProblem::OptProblem( char *szFilePred, char *szFileProgram, char *szFilePresjek, char *szFileIspitiIstiDan )
{
	UcitajPredmete(szFilePred);
	UcitajNastavniProgram(szFileProgram);
	UcitajPresjek(szFilePresjek);
	UcitajPredmeteIstiDan(szFileIspitiIstiDan);
}

OptProblem::OptProblem( char *szFilePred, char *szFileProgram, char *szFilePresjek, char *szFileIspitiIstiDan, 
												Date start, Date end,
												int BrPodrok, TerminRoka Vrsta )
{
	UcitajPredmete(szFilePred);
	UcitajNastavniProgram(szFileProgram);
	UcitajPresjek(szFilePresjek);
	UcitajPredmeteIstiDan(szFileIspitiIstiDan);
}

void	OptProblem::Print()
{
	ProblemData		tmpData;

	PostaviPodatkeModela(tmpData);
	tmpData.Print();
}

bool	OptProblem::PostaviPodatkeModela( ProblemData	&model )
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

				model.addPredmet(nSif, szNaziv, probData.vecPredmeti[i].getDodPod(j));
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
			model.addPresjek( sif1, par.m_nSifra, par.m_nPresjek );
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
			if( model.IsPartOfProblem(probData.matIspitiIstiDan[i][j]) )
			{
				if( first == -1 )		// to je prvi kojeg ubacujemo u redak ( neæemo ga ubacivati dok ne naðemo i drugoga )
					first = probData.matIspitiIstiDan[i][j];
				else if( second == -1 )
				{
					// onda ubaci oba
					model.matIspitiIstiDan.resize(rownum+1);
					model.matIspitiIstiDan[rownum].resize(2);
					
					model.matIspitiIstiDan[rownum][0] = first;
					second = probData.matIspitiIstiDan[i][j];
					model.matIspitiIstiDan[rownum][1] = second;

					row_size = 2;
					rownum++;
				}
				else	// ovo nam je znaèi veæ treæi ( ili n-ti ) kojeg ubacujemo u ovaj redak
				{
					model.matIspitiIstiDan[rownum-1].resize(row_size + 1);
					model.matIspitiIstiDan[rownum-1][row_size++] = probData.matIspitiIstiDan[i][j];
				}
			}
	}
	return true;
}


/***************************************************************************************/
/*																GENETSKI ALGORITAM																	 */
/***************************************************************************************/

int OptProblem::Optimize( PFCALLBACK	pfCallBackFunc )
{
	int					i, j, nMinInd, nMaxInd;
	double			dMinFunc, dMaxFunc;
	vector<int>	a(calData.BrojPodrokova());

	// TEST
	
	OptimizationData		opt(probData, modelDescr, calData, FuncPar);

	opt.GenerateInitialPopulation();

	for( i=0; i<opt.GetIterNum(); i++ )
	{
		// SELEKCIJA
		// iz skupa od VEL_POP jedinki, odaberi njih 3 i indekse odabranih stavi u polje 'a'
		SelectRandomNumbers(a,3,0,opt.GetVelPop()-1);
		
		// treba naæi najlošiju jedinku
		nMinInd  = 0 ;
		dMinFunc = opt.Func(opt.GetGene(a[0]));
		for( j=1; j<3; j++ )
			if( dMinFunc > opt.Func(opt.GetGene(a[j])) )
			{
				dMinFunc = opt.Func(opt.GetGene(a[j]));
				nMinInd  = j;
			}

		// KRIŽANJE
		// križaj dvije jedinke koje su bolje od one treæe selektirane
		if( nMinInd == 0 )
			opt.Krizaj( opt.GetGene(a[1]), opt.GetGene(a[2]), opt.GetGene(a[nMinInd]) );
		else if( nMinInd == 1 )
			opt.Krizaj( opt.GetGene(a[0]), opt.GetGene(a[2]), opt.GetGene(a[nMinInd]) );
		else
			opt.Krizaj( opt.GetGene(a[0]), opt.GetGene(a[1]), opt.GetGene(a[nMinInd]) );

		// MUTACIJA
		opt.Mutiraj();

		if( i % 100 == 0 )
		{
			nMaxInd  = 0;
			dMaxFunc = opt.Func(opt.GetGene(0));
			
			for( int k=1; k<opt.GetVelPop(); k++ )
				if( dMaxFunc < opt.Func(*opt.Population[k]) ) {
					dMaxFunc = opt.Func(*opt.Population[k]);
					nMaxInd  = k;
				}
			
			printf("\n max.jed. = %3d   func = %15.7f    odstup = %3d", nMaxInd , dMaxFunc, opt.GetGene(nMaxInd).m_statData.brOdstupanjaOdPodrokova );

			// ukoliko nam je predana adresa callback funkcije kao parametar, onda ju pozovi
			if( pfCallBackFunc != NULL )
				(*pfCallBackFunc)(NULL);
		}
	}

	// END TEST

	/*
	if( optData != NULL )
		delete optData;

	optData = new OptimizationData(modelData.BrojIspita(), calData.BrojTermina(), calData.BrojPodrokova() );

	optData->GenerateInitialPopulation();

	for( i=0; i<optData->GetIterNum(); i++ )
	{
		// SELEKCIJA
		// iz skupa od VEL_POP jedinki, odaberi njih 3 i indekse odabranih stavi u polje 'a'
		SelectRandomNumbers(a,3,0,optData->GetVelPop()-1);
		
		// treba naæi najlošiju jedinku
		nMinInd  = 0 ;
		dMinFunc = Func(optData->GetGene(a[0]));
		for( j=1; j<3; j++ )
			if( dMinFunc > Func(optData->GetGene(a[j])) )
			{
				dMinFunc = Func(optData->GetGene(a[j]));
				nMinInd  = j;
			}

		// KRIŽANJE
		// križaj dvije jedinke koje su bolje od one treæe selektirane
		if( nMinInd == 0 )
			Krizaj( optData->GetGene(a[1]), optData->GetGene(a[2]), optData->GetGene(a[nMinInd]) );
		else if( nMinInd == 1 )
			Krizaj( optData->GetGene(a[0]), optData->GetGene(a[2]), optData->GetGene(a[nMinInd]) );
		else
			Krizaj( optData->GetGene(a[0]), optData->GetGene(a[1]), optData->GetGene(a[nMinInd]) );

		// MUTACIJA
		Mutiraj();

		if( i % 1000 == 0 )
		{
			nMaxInd  = 0;
			dMaxFunc = Func(optData->GetGene(0));
			
			for( int k=1; k<optData->GetVelPop(); k++ )
				if( dMaxFunc < Func(*optData->Population[k]) ) {
					dMaxFunc = Func(*optData->Population[k]);
					nMaxInd  = k;
				}
			
			printf("\n max.jed. = %3d   func = %f    odstup = %3d", nMaxInd , dMaxFunc, optData->GetGene(nMaxInd).m_statData.brOdstupanjaOdPodrokova );

			// ukoliko nam je predana adresa callback funkcije kao parametar, onda ju pozovi
			if( pfCallBackFunc != NULL )
				(*pfCallBackFunc)(NULL);
		}
	}
	*/

	return 1;
}

