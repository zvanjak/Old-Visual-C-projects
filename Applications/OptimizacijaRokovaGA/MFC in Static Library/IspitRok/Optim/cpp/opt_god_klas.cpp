#include "..\h\ispit_rok.h"

Opt_God :: Opt_God()
{
	pct = pcu = NULL;
	odab_elim = NULL;
	selekcija = NULL;
	natalitet = NULL;
	mutacija = NULL;
	ukupan_translat = NULL;
	ukupan_isp_ozn = NULL;
	ukupan_zav_ozn = NULL;
	ukupan_smjer_ozn = NULL;
	poc_gen_plan = NULL;
	djel_zav = NULL;
	djel_min_udalj = NULL;
	djel_ost = NULL;
	djel_ost_korjen = NULL;
	p_gena = NULL;
	fija = NULL;
	ukupan_isp_redni_br = NULL;
	ukupan_sem_ozn = NULL;

	br_smjer = -1;
	
}//Opt_God

void Opt_God :: Create(int br_i, Fiks_Ispit& fi, Ispit_Stud_Zavod& isz, Ispit_Period& ip, int sj, int vp, double od_f, UINT poc_van, UINT gran_dol_ost_v, UINT gran_dol_ost_u, granice gran, HWND m_hwnd_1, HWND m_hwnd_2, HWND _clc)
{
	int i;

	destrukt();

	pct = pcu = NULL;
	max_stud_grup_pred = isz.max_stud_grup_pred;
	
	pct = (CProgressCtrl*) pr1.FromHandle(m_hwnd_1);//stvaranje privremenog objekta koji kontrolira napredak na suèelju
	pcu = (CProgressCtrl*) pr2.FromHandle(m_hwnd_2);//stvaranje privremenog objekta koji kontrolira napredak na suèelju 

	clc = (CListCtrl*) lc.FromHandle(_clc); 

	br_smjer = isz.br_smjer;
	vel_pop = vp;
	sir_jed = sj;
	if(vel_pop % 2) vel_pop ++;
	br_iter = br_i;

	vel_elim = vel_pop / 2;

	if(sir_jed > 30) _ASSERT(0);
	maska = (int)(pow(2, sir_jed) - 1);

	
	if(ip.br_rok == 3) br_k = 2;
	else br_k = 1;
		
	djel_zav = new int [vel_pop];
	djel_ost = new int [vel_pop];
	djel_ost_korjen = new double [vel_pop];
	if(ip.br_rok == 3)
	{
		ukupan_translat = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
		ukupan_isp_ozn = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
		ukupan_zav_ozn = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
		ukupan_smjer_ozn = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
		ukupan_isp_redni_br = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
		ukupan_sem_ozn = new int [vel_pop * isz.ukup_br_isp * ip.br_rok];
	}
	else
	{
		ukupan_translat = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
		ukupan_isp_ozn = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
		ukupan_zav_ozn = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
		ukupan_smjer_ozn = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
		ukupan_isp_redni_br = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
		ukupan_sem_ozn = new int [vel_pop * isz.ukup_br_isp_1 * ip.br_rok];
	}//else

	p_gena = new (Gen(*[br_smjer]));
	fija = new (Polje_D(*[br_smjer + 1]));

	for(i = 0; i < br_smjer + 1; i++)
		fija[i] = new Polje_D(vel_pop);


	poc_gen_plan = new Polje_I(vel_pop);
	djel_min_udalj = new int [vel_pop];
	odab_elim = new Polje_I(vel_pop);
	selekcija = new Selekcija(vel_pop);
	natalitet = new Natalitet(vel_elim, vel_pop, maska, ip.br_rok);
	mutacija = new Mutacija(vel_pop, ip, isz);


	for(i = 0; i < br_smjer; i++)
		p_gena[i] = new Gen(sj, vp, isz, poc_van, gran_dol_ost_v, gran_dol_ost_u, gran, ip, od_f, i);

	
	fi.reset();

//pretvaranje datuma ispita u Fiks_Ispit povezanoj listi ( prije optimizacije odreðeni datumi ispita ) 
//u genetski kod
	if(ip.br_rok == 3)
	{
		for(i = 0; i < fi.br_cvor; i++)
			fi.set_param((p_gena[0] -> trans_inverz(fi.get_r_d(0), 0)), (p_gena[0] -> trans_inverz(fi.get_r_d(1), 1)), (p_gena[0] -> trans_inverz(fi.get_r_d(2), 2)));
	}
	else
	if(ip.br_rok == 2)
	{
		for(i = 0; i < fi.br_cvor; i++)
			fi.set_param((p_gena[0] -> trans_inverz(fi.get_r_d(0), 0)), (p_gena[0] -> trans_inverz(fi.get_r_d(1), 1)));

	}
	else
	{
		for(i = 0; i < fi.br_cvor; i++)
			fi.set_param((p_gena[0] -> trans_inverz(fi.get_r_d(0), 0)));

	}//else

}//Create


Opt_God :: ~Opt_God()
{
	destrukt();

}//Opt_God

void Opt_God :: destrukt()
{
int i;

	if(djel_ost) delete [] djel_ost;
	if(djel_ost_korjen) delete [] djel_ost_korjen;
	if(ukupan_sem_ozn) delete [] ukupan_sem_ozn;
	if(odab_elim) delete odab_elim;
	if(selekcija) delete selekcija;
	if(natalitet) delete natalitet;
	if(mutacija) delete mutacija;
	if(ukupan_translat) delete ukupan_translat;
	if(ukupan_isp_ozn) delete ukupan_isp_ozn;
	if(ukupan_smjer_ozn) delete ukupan_smjer_ozn;
	if(ukupan_zav_ozn) delete ukupan_zav_ozn;
	if(ukupan_isp_redni_br) delete ukupan_isp_redni_br;
	if(poc_gen_plan) delete poc_gen_plan;
	if(djel_zav) delete djel_zav;
	if(djel_min_udalj) delete [] djel_min_udalj;


	for(i = 0; i < br_smjer; i++)
		p_gena[i] -> destrukt();

	for(i = 0; i < br_smjer + 1; i++)
		fija[i] -> destrukt();

	if(p_gena) delete [] p_gena;
	if(fija) delete [] fija;


	ukupan_sem_ozn = NULL;
	pct = pcu = NULL;
	odab_elim = NULL;
	selekcija = NULL;
	natalitet = NULL;
	mutacija = NULL;
	ukupan_translat = NULL;
	ukupan_isp_ozn = NULL;
	ukupan_zav_ozn = NULL;
	ukupan_smjer_ozn = NULL;
	poc_gen_plan = NULL;
	djel_zav = NULL;
	djel_min_udalj = NULL;
	djel_ost = NULL;
	ukupan_isp_redni_br = NULL;

	p_gena = NULL;
	fija = NULL;

	br_smjer = -1;
	
}

void Opt_God :: isti_isp_fiks(Ispit_Period& ip, Ispit_Stud_Zavod& isz, Fiks_Ispit& fi)
{
	int i, j, k, l;
	int poz_1;
	int br_cop;
	int pozic;
	int sif;
	
	fi.reset();

//pomoæu objekta Fiks_Ispit funkcija osigurava da odreðeni ispiti se održavaju u prije 
//odreðeninm datumima
	for(i = 0; i < fi.br_cvor; i++)
	{
		sif = fi.ispit_cvor();
		pozic = -1;
		for(l = 0; l < isz.br_razl_isp; l++)
			if(sif == isz.razl_isp_ozn_p[l])
			{
				pozic = l;
				break;
			}//if
		
	
			if(pozic > -1)
			{
				for(j = 0; j < br_smjer; j++)
					if(isz.zaj_isp_smj_poz[j * isz.br_razl_isp + pozic] > -1)
					{
						poz_1 = j;
						break;
					}//if

				

				for(j = 0; j < vel_pop; j++)
				for(k = 0; k < ip.br_rok; k++)
					(p_gena[poz_1] -> kromosom[isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + pozic]])[j * isz.br_ispit_p[poz_1 * 2 + isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + pozic]] * ip.br_rok + k * isz.br_ispit_p[poz_1 * 2 + isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + pozic]] + isz.zaj_isp_smj_poz[poz_1 * isz.br_razl_isp + pozic]]
							=
					fi.datum(k);
			
		

				if(isz.zaj_isp_smj_poz[isz.br_razl_isp * br_smjer + i] > 1) 
				{

					br_cop = isz.zaj_isp_smj_poz[isz.br_razl_isp * br_smjer + pozic] - 1;
					for(j = poz_1 + 1; j < br_smjer; j++)
					{
						if(isz.zaj_isp_smj_poz[j * isz.br_razl_isp + pozic] > -1)
						{
							for(k = 0; k < vel_pop * ip.br_rok; k++)
							{
								(p_gena[j] -> kromosom[isz.zaj_isp_smj_sem[j * isz.br_razl_isp + pozic]])[k * isz.br_ispit_p[j * 2 + isz.zaj_isp_smj_sem[j * isz.br_razl_isp + pozic]] + isz.zaj_isp_smj_poz[j * isz.br_razl_isp + pozic]] 
										= 
								(p_gena[poz_1] -> kromosom[isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + pozic]])[k * isz.br_ispit_p[poz_1 * 2 + isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + pozic]] + isz.zaj_isp_smj_poz[poz_1 * isz.br_razl_isp + pozic]];
	

							}//for k
							br_cop--;

						}//if
				

						if(!br_cop) break;

					}//for j

				}//if
			
		}//if -1
	}//for i

}//isti_isp_fiks

void Opt_God :: isti_isp(Ispit_Stud_Zavod & isz, Ispit_Period& ip)
{
	int i, j, k;
	int poz_1;
	int br_cop;
	
//ova funkcija osigurava održavanje ispita iz istih kolegija koji se predaju na razlièitim 
//smjerovima na isti datum. Koristi se poljima Ispit_Stud_Zavod::zaj_isp_smj_sem
//i  Ispit_Stud_Zavod::isz.zaj_isp_smj_poz
	for(i = 0; i < isz.br_razl_isp; i++)
	{
	
		if(isz.zaj_isp_smj_poz[isz.br_razl_isp * br_smjer + i] > 1 )
		{
			for(j = 0; j < br_smjer; j++)
				if(isz.zaj_isp_smj_poz[j * isz.br_razl_isp + i] > -1)
				{
					poz_1 = j;
					break;
				}//if
		


			br_cop = isz.zaj_isp_smj_poz[isz.br_razl_isp * br_smjer + i] - 1;
			for(j = poz_1 + 1; j < br_smjer; j++)
			{
				if(isz.zaj_isp_smj_poz[j * isz.br_razl_isp + i] > -1)
				{
					for(k = 0; k < vel_pop * ip.br_rok; k++)
					{
						(p_gena[j] -> kromosom[isz.zaj_isp_smj_sem[j * isz.br_razl_isp + i]])[k * isz.br_ispit_p[j * 2 + isz.zaj_isp_smj_sem[j * isz.br_razl_isp + i]] + isz.zaj_isp_smj_poz[j * isz.br_razl_isp + i]] 
								= 
						(p_gena[poz_1] -> kromosom[isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + i]])[k * isz.br_ispit_p[poz_1 * 2 + isz.zaj_isp_smj_sem[poz_1 * isz.br_razl_isp + i]] + isz.zaj_isp_smj_poz[poz_1 * isz.br_razl_isp + i]];

					}
					
				br_cop--;

				}//if
				

				if(!br_cop) break;

			}//for j

		}//if

	}//for i

}//isti_isp

void Opt_God :: god_sum_max(Ispit_Period& ip,  Ispit_Stud_Zavod& isz, int iter, int iter_1)
{
	int i, j;


//zbrajanje parcijalnih vrijednosti funkcija dobrote
	for(i = 0; i < (fija[br_smjer] -> duljina); i++)
		(fija[br_smjer] -> m_polje)[i] = (fija[0] -> m_polje)[i];
// ukupan zbroj se smješta u fija[br_smjer] 
	for(i = 1; i < br_smjer; i++)
		for(j = 0; j < vel_pop; j++)
			(fija[br_smjer] -> m_polje)[j] += (fija[i] -> m_polje)[j];


	zavod_fij(ip, isz);	
//odabiranje najbolje jedinke
	for(i = 0; i < (fija[br_smjer] -> duljina); i++)
		if(max_fij < (fija[br_smjer] -> m_polje)[i])
		{
			max_index = i;
			max_fij = (fija[br_smjer] -> m_polje)[i];
			max_iter = iter;
			max_iter_1 = iter_1;
			z_v = djel_zav[i];
			m_u = djel_min_udalj[i];
			d_o = djel_ost[i];
			
		
			
			for(j = 0; j < br_smjer; j++)
				(p_gena[j] ->* (p_gena[j] -> najb))(*(fija[j]), max_index, ip, isz);
		}//if

}//god_sum

void Opt_God :: set_poc_generacija(Ispit_Stud_Zavod& isz, Ispit_Period& ip, int pspg)
{
	int i;
	int b_s_p_g;


	b_s_p_g= (int)((vel_pop * pspg) / 100.0);

	for(i = 0; i < b_s_p_g + 2; i++)
		(*poc_gen_plan)[i] = rand();

	for(i = 0; i < br_smjer; i++)
	{
		(p_gena[i] -> br_smisl_poc_gen) = b_s_p_g;
		p_gena[i] -> pocetna_generacija(*poc_gen_plan, isz, ip);
	}//for i


}//set_poc_gener

void Opt_God :: translat_popun(Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
	int i, j, k, m, l;

// u polja se preslikavaju cijele jedinke odnosno svi smjerovi koji èine jedinku bivaju 
//stavljeni "na jedno mjesto" i pomoæu tih informacija se mogu raèunati kazne
//za pojedine jedinke o preoptereæenosti pojedinih grupa predmeta kod pojedinih jedinki
	if(ip.br_rok == 3)
	{
		if(ip.ljet_jesn)
		{
			
			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
				memcpy(ukupan_translat + i * isz.ukup_br_isp * ip.br_rok + isz.poc_smjer_stud[j] + k * isz.ukup_br_isp, (p_gena[j] -> translat) + i * ip.br_rok * (isz(j, 0) + isz(j, 1)) + k * (isz(j, 0) + isz(j, 1)), (isz(j, 0) + isz(j, 1)) * sizeof(int));
			

		}
		else
		{
			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
			{
				memcpy(ukupan_translat + i * isz.ukup_br_isp * ip.br_rok + isz.poc_smjer_stud[j] + k * isz.ukup_br_isp, (p_gena[j] -> translat) + i * ip.br_rok * isz(j, 0) + k * isz(j, 0), isz(j, 0) * sizeof(int));
				memcpy(ukupan_translat + i * isz.ukup_br_isp * ip.br_rok + isz.poc_smjer_stud[j] + k * isz.ukup_br_isp + isz(j, 0), (p_gena[j] -> translat) + i * ip.br_rok * isz(j, 1) + k * isz(j, 1) + vel_pop * isz(j, 0) * ip.br_rok, isz(j, 1) * sizeof(int));
			
			}//for j
		}//else


			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
			for(m = 0; m < br_k; m++)
			{
				memcpy(ukupan_isp_ozn + i * ip.br_rok * isz.ukup_br_isp + k * isz.ukup_br_isp + isz.poc_smjer_stud[j] + m * isz(j, 0), isz.isp_ozn_p + isz.poc_smjer_stud[j] + m * isz(j, 0), isz(j, m) * sizeof(int));
				memcpy(ukupan_zav_ozn + i * ip.br_rok * isz.ukup_br_isp + k * isz.ukup_br_isp + isz.poc_smjer_stud[j] + m * isz(j, 0), isz.isp_zav_ozn_p + isz.poc_smjer_stud[j] + m * isz(j, 0), isz(j, m) * sizeof(int));
			}//for m

			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
 			for(m = 0; m < br_k; m++)
			for(l = 0; l < isz(j, m); l++)
			{
				ukupan_smjer_ozn[i * ip.br_rok * isz.ukup_br_isp + k * isz.ukup_br_isp + isz.poc_smjer_stud[j] + m * isz(j, 0) + l] = j;
				ukupan_isp_redni_br[i * ip.br_rok * isz.ukup_br_isp + k * isz.ukup_br_isp + isz.poc_smjer_stud[j] + m * isz(j, 0) + l] = l;
				ukupan_sem_ozn[i * ip.br_rok * isz.ukup_br_isp + k * isz.ukup_br_isp + isz.poc_smjer_stud[j] + m * isz(j, 0) + l] = m;
			}
		
		

	}
	else
	{
		if(ip.br_rok == 2)
		{
			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
				memcpy(ukupan_translat + i * isz.ukup_br_isp_1 * ip.br_rok + isz.poc_smjer_stud_1[j] + k * isz.ukup_br_isp_1, (p_gena[j] -> translat) + i * isz(j, 0) * ip.br_rok + k * isz(j, 0), isz(j, 0) * sizeof(int));

		}
		else
		{
			for(i = 0; i < vel_pop; i++)
			for(j = 0; j < br_smjer; j++)
				memcpy(ukupan_translat + i * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j], (p_gena[j] -> translat) + i * isz(j, 0), isz(j, 0) * sizeof(int));
	
	
		}//else

			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
 			for(m = 0; m < br_k; m++)
			{
				memcpy(ukupan_isp_ozn + i * ip.br_rok * isz.ukup_br_isp_1 + k * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j] + m * isz(j, 0), isz.isp_ozn_p + isz.poc_smjer_stud_1[j] + m * isz(j, 0), isz(j, m) * sizeof(int));
				memcpy(ukupan_zav_ozn + i * ip.br_rok * isz.ukup_br_isp_1 + k * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j] + m * isz(j, 0), isz.isp_zav_ozn_p + isz.poc_smjer_stud_1[j] + m * isz(j, 0), isz(j, m) * sizeof(int));
			}//for m

			for(i = 0; i < vel_pop; i++)
			for(k = 0; k < ip.br_rok; k++)
			for(j = 0; j < br_smjer; j++)
 			for(m = 0; m < br_k; m++)
			for(l = 0; l < isz(j, m); l++)
			{
				ukupan_smjer_ozn[i * ip.br_rok * isz.ukup_br_isp_1 + k * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j] + m * isz(j, 0) + l] = j;
				ukupan_isp_redni_br[i * ip.br_rok * isz.ukup_br_isp_1 + k * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j] + m * isz(j, 0) + l] = l;
				ukupan_sem_ozn[i * ip.br_rok * isz.ukup_br_isp_1 + k * isz.ukup_br_isp_1 + isz.poc_smjer_stud_1[j] + m * isz(j, 0) + l] = m;
			}
		
			
			
	}//else

			


	
	for(i = 0; i < vel_pop; i++)
	{
		djel_min_udalj[i] = (p_gena[0] -> djel_min_udalj)[i];
		djel_ost[i] = (p_gena[0] -> djel_ost)[i];
		djel_ost_korjen[i] = (p_gena[0] -> djel_ost_korjen)[i];
	}

	for(j = 1; j < br_smjer; j++)
		for(i = 0; i < vel_pop; i++)
		{
			djel_min_udalj[i] += (p_gena[j] -> djel_min_udalj)[i];
			djel_ost[i] += (p_gena[j] -> djel_ost)[i];
			djel_ost_korjen[i] += (p_gena[j] -> djel_ost_korjen)[i];
		}
	


}//translat_popun

void Opt_God :: zavod_fij(Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
	int i, j, k;
	int djel, djel_p;
	double djel_ukup;
	int djel_kazn_p;
	int dan_ozn;

	translat_popun(ip, isz);

	if(ip.br_rok == 3)
	{
		for(i = 0; i < vel_pop * ip.br_rok; i++)
			p_gena[0] -> shellsort(ukupan_translat + i * isz.ukup_br_isp, ukupan_isp_ozn + i * isz.ukup_br_isp, ukupan_smjer_ozn + i * isz.ukup_br_isp, ukupan_sem_ozn + i * isz.ukup_br_isp, ukupan_isp_redni_br + i * isz.ukup_br_isp, isz.ukup_br_isp);

		for(i = 0; i < vel_pop; i++)
		{
			
			djel = 0;
			djel_kazn_p = 0;
			dan_ozn = ukupan_translat[i * isz.ukup_br_isp];	
			for(k = 0; k < isz.br_grup_pred; k++)
			{
				djel_p = 0;
				for(j = 0; j < isz.ukup_br_isp - 1; j++)
				{
				
					if(
						(ukupan_translat[i * isz.ukup_br_isp + j] == ukupan_translat[i * isz.ukup_br_isp + j + 1])
					&& (ukupan_isp_ozn[i * isz.ukup_br_isp + j] != ukupan_isp_ozn[i * isz.ukup_br_isp + j + 1])
					&& (ukupan_zav_ozn[i * isz.ukup_br_isp + j] == ukupan_zav_ozn[i * isz.ukup_br_isp + j + 1])
					&& (ukupan_zav_ozn[i * isz.ukup_br_isp + j] == dan_ozn)
					
					) 
						djel_p += isz(
											ukupan_smjer_ozn[i * isz.ukup_br_isp + j], 
											ukupan_sem_ozn[i * isz.ukup_br_isp + j], 
											ukupan_isp_redni_br[i * isz.ukup_br_isp + j], 
											ukupan_sem_ozn[i * isz.ukup_br_isp + j + 1], 
											ukupan_isp_redni_br[i * isz.ukup_br_isp + j + 1]
										);

					if(dan_ozn != ukupan_translat[i * isz.ukup_br_isp + j])
						{
							
							if(djel_p > max_stud_grup_pred) djel_kazn_p ++;
							djel_p = 0;
							dan_ozn = ukupan_translat[i * isz.ukup_br_isp + j];
						
						}//if
				}//for j

				
			}//for k
			

			djel_zav[i] = djel_kazn_p;

		}//for i

	}
	else
	{
		for(i = 0; i < vel_pop * ip.br_rok; i++)
			p_gena[0] -> shellsort(ukupan_translat + i * isz.ukup_br_isp_1, ukupan_isp_ozn + i * isz.ukup_br_isp_1, ukupan_smjer_ozn + i * isz.ukup_br_isp_1, ukupan_sem_ozn + i * isz.ukup_br_isp_1, ukupan_isp_redni_br + i * isz.ukup_br_isp_1, isz.ukup_br_isp_1);

		for(i = 0; i < vel_pop; i++)
		{
			djel = 0;
			dan_ozn = ukupan_translat[i * isz.ukup_br_isp_1];	
			djel_kazn_p = 0;

			for(k = 0; k < isz.br_grup_pred; k++)
			{
				djel_p = 0;
				for(j = 0; j < isz.ukup_br_isp_1 - 1; j++)
				{
					if(
						(ukupan_translat[i * isz.ukup_br_isp_1 + j] == ukupan_translat[i * isz.ukup_br_isp_1 + j + 1])
					&& (ukupan_isp_ozn[i * isz.ukup_br_isp_1 + j] != ukupan_isp_ozn[i * isz.ukup_br_isp_1 + j + 1])
					&& (ukupan_zav_ozn[i * isz.ukup_br_isp_1 + j] == ukupan_zav_ozn[i * isz.ukup_br_isp_1 + j + 1])
					&& (ukupan_zav_ozn[i * isz.ukup_br_isp_1 + j] == dan_ozn)
					) 
					{
						djel_p += isz(
											ukupan_smjer_ozn[i * isz.ukup_br_isp_1 + j], 
											ukupan_sem_ozn[i * isz.ukup_br_isp_1 + j], 
											ukupan_isp_redni_br[i * isz.ukup_br_isp_1 + j], 
											ukupan_sem_ozn[i * isz.ukup_br_isp_1 + j + 1], 
											ukupan_isp_redni_br[i * isz.ukup_br_isp_1 + j + 1]
											
										);
					}//if

					if(dan_ozn != ukupan_translat[i * isz.ukup_br_isp_1 + j])
					{
							
						if(djel_p > max_stud_grup_pred) djel_kazn_p ++;
						djel_p = 0;
						dan_ozn = ukupan_translat[i * isz.ukup_br_isp_1 + j];
						
					}//if

				}//for j

			}//for k
			djel_zav[i] = djel;

		}//for i

	}//else
	
//u ovom dijelu se odreðuju kazne za one jedinke koje imaju prebveliko optereæenje 
//odreðene grupe predmeta u jednom danu ( zbroj presjeka broja studenata > max_stud_grup_pred )

	for(i = 0; i < vel_pop; i++)
	{
		//kaznama za preoptereæene grupe predmeta i za minimalnu udaljenost meðu ispitima
		//se množi velikim koeficijentom
		djel_ukup = 1000 * (djel_zav[i] + djel_min_udalj[i]);	
		//raèunanje kazne za maksimalnu udaljenost meðu ispitima istog kolegija i za neravnomjernu dispergiju
		djel_ukup += ((double)djel_ost[i] / djel_ost_korjen[i]) * 30;
		if(!djel_ukup) djel_ukup = 1;
	
		(fija[br_smjer] -> m_polje)[i] /= djel_ukup; // kažnjavanje jedinke
	}//for i



}//zavod_fij


void Opt_God :: start_opt_god(Ispit_Stud_Zavod & isz, Ispit_Period& ip, Fiks_Ispit& fi, mut_korak_gran& mkg, int br_ponavlj, psg_korak_gran& psgkg, UINT& stop, CString** p_rezultati, CMutex *mutex, UINT& opt_u_tijeku)
{
//funkcija koja pokreæe i sinkronizira optimizaciju - komentirana u diplomskom radu
	int i, j, k, l, m, o, p;
	time_t tp, tk;
	int tren_pon;
	int ukupno;
	char str[20];
	//ofstream out("rokovi.dat");
	CSingleLock SingleLock(mutex);
	int gotovo = 0;

	//int b;

	pct->SetRange(0,br_iter + 1);
	pct->SetPos(0);
	pct->SetStep(1);
	
	ukupno = (psgkg.zpsg - psgkg.ppsg) / psgkg.korak + 1;
	ukupno *= (mkg.zpmk - mkg.ppmk) / mkg.korak_k + 1;
	ukupno *= (mkg.zpmb - mkg.ppmb) / mkg.korak_b + 1;
	ukupno *= br_ponavlj;

	pcu->SetRange(0, ukupno);
	pcu->SetPos(0);
	pcu->SetStep(1);
	
	tren_pon = 0;

	for(p = psgkg.ppsg; p <= psgkg.zpsg; p += psgkg.korak)
	for(o = mkg.ppmk; o <= mkg.zpmk; o += mkg.korak_k)
	for(m = mkg.ppmb; m <= mkg.zpmb; m+= mkg.korak_b)
	for(l = 0; l < br_ponavlj; l++)
	{
		
		tren_pon++;

		max_fij = 0;
		max_index = 0;

		time(&tp);
		
		set_poc_generacija(isz, ip, p);

		pct->SetPos(1);
		for(i = 0; i < br_iter; i++)
		{
			for(j = 0; j < 1000; j++)
			{
			
				if(isz.br_smjer > 1)  isti_isp(isz, ip);

				if(fi.br_cvor) isti_isp_fiks(ip, isz, fi);

 				for(k = 0; k < br_smjer; k++)
					((p_gena[k]) ->* (p_gena[k] -> f))(*(fija[k]), isz, ip);

				god_sum_max(ip, isz, i, j);

				selekcija -> odabir_elim(*(fija[br_smjer]), *odab_elim, vel_elim);

				for(k = 0; k < br_smjer; k++)
					natalitet -> krizanje(*odab_elim, *(p_gena[k]), ip, isz, k);

				mutacija -> mut_gena_god(p_gena, br_smjer, m, o, vel_pop, sir_jed, ip, isz);
				
				SingleLock.Lock();
				if(stop)
				{
					j = 1000 + 1;
					i = br_iter + 1;
					p = psgkg.zpsg + 1;
					o = mkg.zpmk + 1;
					l = br_ponavlj + 1;
					m = mkg.zpmb + 1;
					gotovo = 1;
										
				}
				SingleLock.Unlock();
			}//for j
		pct->StepIt();
		

		}//for i

		pcu->StepIt();

		pct->SetPos(0);
		time(&tk);
		tk -= tp;
	
	int b;
		sprintf(str,"%f",max_fij);
		b = clc->InsertItem(tren_pon - 1, str);
		if(b != -1)
		{
		
		_itoa(z_v , str, 10);
		clc->SetItemText(tren_pon - 1, 1, str);
		_itoa(m_u , str, 10);
		clc->SetItemText(tren_pon - 1, 2, str);
		_itoa(max_iter , str, 10);
		clc->SetItemText(tren_pon - 1, 3, str);
		_itoa(p , str, 10);
		clc->SetItemText(tren_pon - 1, 4, str);
		_itoa(o , str, 10);
		clc->SetItemText(tren_pon - 1, 5, str);
		_itoa(m , str, 10);
		clc->SetItemText(tren_pon - 1, 6, str);
		}
		

		ispis(isz, ip, tk, p, o, m, tren_pon, p_rezultati);
		
	
	}//for l

	pcu->SetPos(0);

	SingleLock.Lock();
			opt_u_tijeku = 0;	
			stop = 0;
	SingleLock.Unlock();

	

}//start_opt_god


//popunjava vrijednosti CString objekata koji sadrže rezultate optimizacije s "header" podacima
void Opt_God :: ispis(Ispit_Stud_Zavod & isz, Ispit_Period& ip, int tk, int p, int o, int m, int tren_pon, CString** p_rezultat)
{
	int i;
	CString ret;
	ret ="\r\n";
	char pom[20];

	if(br_smjer > 0)
	{

	
		*(p_rezultat[tren_pon - 1]) += "PONAVLJANJE = "; _itoa(tren_pon, pom, 10);
		
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ". put";
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Postotak mutacije bitova jedinke  = ";
		_itoa(m, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) +=  ret;
		*(p_rezultat[tren_pon - 1]) += "Postotak mutacije jedinki populacije = ";_itoa(o, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) +=  ret;
		*(p_rezultat[tren_pon - 1]) += "Postotak smišljene poèetne generacije jedinki = ";_itoa(p, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Velièina Populacije = ";
		_itoa(vel_pop, pom, 10);*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Maksimalni broj studenata u jednoj grupi predmeta = ";
		_itoa(isz.max_stud_grup_pred, pom, 10);*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Ukupna Funkcija Dobrote = ";sprintf(pom, "%f", max_fij);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) +=  ret;
		*(p_rezultat[tren_pon - 1]) +="Najuspješnija vrijednost postignuta u iteraciji = ";_itoa(max_iter, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Broj \"zavodskih kazni\" = ";_itoa(z_v, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "Broj kazni minimalne udaljenosti  = ";_itoa(m_u, pom, 10);
		*(p_rezultat[tren_pon - 1]) += pom;
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += "________________________________________________";
		*(p_rezultat[tren_pon - 1]) += ret;
		*(p_rezultat[tren_pon - 1]) += ret;

	}

	for(i = 0; i < br_smjer; i++)
		p_gena[i] -> ispis(ip, isz, i, p_rezultat, tren_pon - 1);

	*(p_rezultat[tren_pon - 1]) += "t = ";
	_itoa((int)(tk / 60), pom, 10);
	*(p_rezultat[tren_pon - 1]) += pom;
	*(p_rezultat[tren_pon - 1]) += " min	",
	_itoa((int)(tk - (int)(tk / 60) * 60), pom, 10);
	*(p_rezultat[tren_pon - 1]) += pom;
	*(p_rezultat[tren_pon - 1]) += " s";
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += "===================================================";
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += "===================================================";
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += ret;
	*(p_rezultat[tren_pon - 1]) += ret;
	
}//ispis

