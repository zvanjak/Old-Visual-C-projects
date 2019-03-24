#include "..\h\ispit_rok.h"

Selekcija :: Selekcija()
{
	kumul = NULL;
}//Selekcija

Selekcija :: Selekcija(int n)
{
	kumul = new double [n];
	
}//Selekcija

Selekcija :: ~Selekcija()
{
	if(kumul) delete [] kumul;
}//Selekcija

//raèunanje vrijednosti eliminacije
void Selekcija :: windowing(Polje_D& pd)
{
	int i;
	double max1, sum = 0;

	if(pd.m_polje) max1 = pd[0];

	for(i = 1; i < pd.duljina; i++) 
		if(pd[i] > max1) 
		max1 = pd[i];
	

	for(i = 0; i < pd.duljina; i++) 
	{
		pd[i] = max1 - pd[i];	
		sum += pd[i];
	}

	for(i = 0; i < pd.duljina; i++) 
		pd[i] /= sum;


}//windowing

//kumuliranje vrijednosti eliminacije
void Selekcija :: kumulacija(Polje_D& pd)
{
	int i;

	windowing(pd);

	if(pd.m_polje) 
		kumul[0] = pd[0];

	for(i = 1; i < pd.duljina; i++)
		kumul[i] = pd[i] + kumul[i-1];


}//kumulacija

//odabiranje eliminiranih jedinki
void Selekcija :: odabir_elim(Polje_D& pd, Polje_I& pi, int vel_elim)
{
	int i, j, k, s = 0;
	double sum = 1, tocka, djel, temp;


	kumulacija(pd);

	pi.set0();

	
	for(i = 0; i < vel_elim; i++)
	{
		tocka = (double) rand();
		djel =  RAND_MAX / sum;
		tocka /= djel;

		if(tocka < kumul[0]) 
		{
			pi[0] = 1;//oznaèavanje eliminirane jedinke s jedinicom
			sum = sum - kumul[0];
			for(j = 1; j < pd.duljina; j++) 
				kumul[j] = kumul[j] - kumul[0];
			kumul[0] = 0;
		}//if
		else 
		for(j = 1; j < pd.duljina; ++j)
		{
			if(tocka < kumul[j]) 
			{

				pi[j] = 1;//oznaèavanje eliminirane jedinke s jedinicom
				temp = kumul[j] - kumul[j - 1];
				sum -= temp;
				for(k = j; k < pd.duljina; k++) 
					kumul[k] -= temp;
				j = pd.duljina;

			}//if

		}//for j


	}//for i

	
}//odabir_elim

Natalitet :: Natalitet()
{
	vel_elim = 0;
	vel_pop = 0;
	dijet_rod_p = NULL;
	mode = -1;
	maska = 0;
}

Natalitet :: Natalitet(int v_e, int v_p, int m, int br_rok)
{
	
	int i;
	vel_elim = v_e;
	vel_pop = v_p;
	maska = m;

	dijet_rod_p = new int [vel_elim * 3];
	for(i = 0; i < vel_elim * 3; i++ )
		dijet_rod_p[i] = 0;

	if(!dijet_rod_p) _ASSERT(0);
	if(vel_elim < vel_pop / 2) mode = 0;
	else mode = 1;

	if(br_rok == 3) br_k = 2;
	else br_k = 1;

	mode = 1;
}//Natalitet


int Natalitet :: provjera(Polje_I& pi)
{
	int i, s = 0;

	for(i = 0; i < vel_pop; i++)
		if(pi[i]) s++;

	if(s == vel_elim) return 0;
	else return 1;
}//provjera

void Natalitet :: popravak(Polje_I& pi)
{
	int i, s = 0, j;	
	
	for(i = 0; i < vel_pop; i++) if(pi[i])s++;
	j = 0;
	if(s != vel_elim) 
	{
		s = vel_elim - s;
		while(s)
		{
			if(!pi[j])
			{
				pi[j] = 1;
				s--;
			}
			j++;
		}
	}

}//popravak


Natalitet :: ~Natalitet()
{
	if(dijet_rod_p) delete [] dijet_rod_p;
}

void Natalitet::roditelji_dijete(Polje_I& pi)
{
	int i, j, k;//, c;
	

	if(provjera(pi))
	{
	
		popravak(pi);
	}


		j = 0;
		k = 0;
		for(i = 0; i < vel_pop; i++)
		{
			if(pi[i]) 
			{
				dijet_rod_p[(j + 1) * 3 - 1] = i;
				j++;
			}//if
			else
			{
				dijet_rod_p[k * 3] = i;
				k++;
			}//else
		

		}//for i

		//u polje dijet_rod_p se stavljaju pozicije roditelja i djeteta u polju genetskog koda koji se nalazi u objektu Gen
		for(i = 0; i < vel_elim - 1; i++)
			dijet_rod_p[i * 3 + 1] = dijet_rod_p[(i + 1) * 3];
			dijet_rod_p[vel_elim * 3 - 2] = dijet_rod_p[0];


}

void Natalitet :: krizanje(Polje_I& pi, Gen& g, Ispit_Period& ip, Ispit_Stud_Zavod& isz, int smjer)
{
	int i, j;
	int r;
	int k;

	roditelji_dijete(pi);
	

	//križanje roditelja na osnovu informacija iz polja dijet_rod_p
	for(k = 0; k < br_k; k++)
	for(i = 0; i < vel_elim; i++)
	{
		for(j = 0; j < ip.br_rok * isz(smjer,k); j++)
		{
			r = rand();
			r &= maska;
			(g.kromosom[k])[dijet_rod_p[i * 3 + 2] * g.sir_gen[k] + j] = 
			((g.kromosom[k])[dijet_rod_p[i * 3] * g.sir_gen[k] + j] & (g.kromosom[k])[dijet_rod_p[i * 3 + 1] * g.sir_gen[k] + j]) | 
			(r & ((g.kromosom[k])[dijet_rod_p[i * 3] * g.sir_gen[k] + j] ^ (g.kromosom[k])[dijet_rod_p[i * 3 + 1] * g.sir_gen[k] + j]));

		}//for j
	}//for i
}//krizanje

Mutacija :: Mutacija()
{
	pos_mut_bit = 0;
	pos_mut_krom = 0;
	br_mut_krom = 0;
	djel_gen = 0;
	ozraceni = NULL;
	djel_krom = NULL;
	djel_pozic = NULL;
	br_mut_bit_krom = NULL;
}//Mutacija

Mutacija :: Mutacija(int vel_pop, Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{

	if(ip.br_rok == 3) br_k = 2;
	else br_k = 1;

	br_mut_bit_krom = new int [2 * isz.br_smjer];
	djel_krom = new int [2 * isz.br_smjer];
	djel_pozic = new int [2 * isz.br_smjer];
	ozraceni = new int [vel_pop];

	if(!(ozraceni && djel_pozic && djel_krom && br_mut_bit_krom)) _ASSERT(0);

}//Mutacija

void Mutacija :: inic_mut(int pmb, int pmk, int vel_pop, int sir_jed, Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
	int i;

	pos_mut_bit = pmb;
	pos_mut_krom = pmk;
	br_mut_krom = vel_pop * pmk / 100 ;
	djel_gen = RAND_MAX / vel_pop + 1;

	for(i = 0; i < isz.br_smjer; i++)
	{
			
		br_mut_bit_krom[i * 2 + 0] = ip.br_rok * isz(i, 0) * sir_jed * pmb / 100;
		br_mut_bit_krom[i * 2 + 1] = ip.br_rok * isz(i, 1) * sir_jed * pmb / 100;

	
		
		djel_krom[i * 2 + 0] = RAND_MAX / (2 * br_mut_bit_krom[i * 2 + 0] + 1);//????
		djel_krom[i * 2 + 0]++;
		djel_krom[i * 2 + 1] = RAND_MAX / (2 * br_mut_bit_krom[i * 2 + 1] + 1);//????
		djel_krom[i * 2 + 1]++;

		djel_pozic[i * 2 + 0] = RAND_MAX / (sir_jed * ip.br_rok * isz(i, 0)) + 1;
		djel_pozic[i * 2 + 1] = RAND_MAX / (sir_jed * ip.br_rok * isz(i, 1)) + 1;

	}//for i

}//inic_mut

Mutacija :: ~Mutacija()
{
	if(ozraceni) delete [] ozraceni;
	if(br_mut_bit_krom) delete [] br_mut_bit_krom;
	if(djel_krom) delete [] djel_krom;
	if(djel_pozic) delete [] djel_pozic;

}//~Mutacija



void Mutacija :: mut_gena(Gen& g, int smjer)
{
	int i, j, br, pozic, temp, k;


	for(k = 0; k < br_k; k++)
	for(i = 0; i < br_mut_krom; i++)
	{
		br = rand();
		br /= djel_krom[smjer * 2 + k];
		if(br < 0) br = 0;
		for(j = 0; j < br; j++)
		{
			//mutacija genetskog koda koji se nalazi u objektu Gen
			temp = 1;
			pozic = rand() / djel_pozic[smjer * 2 + k];
			temp = temp << (pozic % g.sir_jed);
			(g.kromosom[k])[ozraceni[i] * g.sir_gen[k] + pozic / g.sir_jed] ^= temp;

		}//for j

	}//for i

}//mut_gena

void Mutacija :: inic_poz_gen()
{
	int i;

	for(i = 0; i < br_mut_krom; i++)
		ozraceni[i] = rand() / djel_gen;//odreðivanje jedinki koje æe biti mutirane

}//inic


void Mutacija :: mut_gena_god(Gen** g, int br_smjer, int pmb, int pmk, int vel_pop, int sir_jed, Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
	int i;

	inic_mut(pmb, pmk, vel_pop, sir_jed, ip, isz);

	inic_poz_gen();
	for(i = 0; i < br_smjer; i++)
		mut_gena(*(g[i]), i);

}//mut_gena_god

