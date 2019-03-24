#include "..\h\ispit_rok.h"

Gen :: Gen(int sj, int vp, Ispit_Stud_Zavod& isz, UINT p_v, UINT g_d_o_v, UINT g_d_o_u, granice gran,  Ispit_Period& ip, double od_f, int smj)
{ 
	int i, j;
	double temp, temp1;

	poc_van = p_v;
	gran_dol_ost_v = g_d_o_v;
	gran_dol_ost_u = g_d_o_u;

	sir_jed = sj;
	vel_pop = vp;
	odn_fij = od_f;
	smjer = smj;

	if(sir_jed > 30) _ASSERT(0);
	maska = (int)(pow(2, sir_jed) - 1);

	vel_elim = vel_pop / 2;
	br_grup_krom = vel_pop * ip.br_rok;
	sir_gen[0] = ip.br_rok * isz(smjer, 0);
	sir_gen[1] = ip.br_rok * isz(smjer, 1);
	sir_gen_u = sir_gen[0] + sir_gen[1];
	max = 0;

	for(i = 0; i < ip.br_rok; i++)
		trans_dan[i] = new int [maska + 1];

	trans_krom = new int [maska + 1];

	djel_min_udalj = new int [vel_pop];
	for(i = 0; i < vel_pop; i++)
		djel_min_udalj[i] = 0;

	if(!(vel_pop && ip.br_rok && isz(smjer, 0))) _ASSERT(0);

//alokacija potrebnih polja za normalan rad genetskih algoritama
		krom_1 = new unsigned long [vel_pop * ip.br_rok * isz(smjer, 0)];
		fc_r_1 = new double[vel_pop];
		kromosom[0] = krom_1;
		rez_sort = new int [(sir_gen_u)];
		djel_ost = new int [vel_pop];
		djel_ost_korjen = new double [vel_pop];

		if(ip.br_rok == 3) 
		{
			krom_2 = new unsigned long [vel_pop * ip.br_rok * isz(smjer, 1)];
			kromosom[1] = krom_2;
			translat_2_2 = new int[(sir_gen_u) * vel_pop];
			rez = new int [(sir_gen_u)];
			index_sort = new int [(sir_gen_u) * vel_pop];
			index = new int [(sir_gen_u)];
			translat = new int [(sir_gen_u) * vel_pop];

			if(!ip.ljet_jesn)
			{
				if(sir_gen[0] > sir_gen[1])
				{
					translat_sort_1 = new int [sir_gen[0] * vel_pop];
					translat_sort_2 = new int [sir_gen[0] * vel_pop];
				}
				else
				{	
					translat_sort_1 = new int [sir_gen[1] * vel_pop];
					translat_sort_2 = new int [sir_gen[1] * vel_pop];
				
				}//else

				fc_r_2 = new double[vel_pop];
				djel_r_2 = new int [vel_pop];
				djel_4 = new int [vel_pop];
				translat_6 = NULL;
			}
			else
			{
				translat_sort_1 = new int [(sir_gen_u) * vel_pop];
				translat_sort_2 = new int [(sir_gen_u) * vel_pop];
				translat_6 = new int [sir_gen_u * vel_pop];
				fc_r_2 = NULL;
				djel_r_2 = NULL;
				djel_4 = NULL;
			}//else

			index_cont = new int [(sir_gen_u) * vel_pop];

		}
		else 
		{
			krom_2 = NULL;
			translat_2_2 = NULL;
			fc_r_2 = NULL;
			djel_r_2 = NULL;
			translat_6 = NULL;
 			djel_4 = NULL;
			rez = new int [sir_gen[0]];
			index_sort = new int [sir_gen[0] * vel_pop];
			index = new int [sir_gen[0]];
			index_cont = new int [sir_gen[0] * vel_pop];
			translat = new int [sir_gen[0] * vel_pop];
			translat_sort_1 = new int [sir_gen[0] * vel_pop];
			translat_sort_2 = new int [sir_gen[0] * vel_pop];
		
		}//else

		
	
		fc_1 = new double[vel_pop];
		fc_3 = new double[vel_pop];
		t_f = new F_T [ip.br_rok];
		djel_1 = new int [vel_pop];
		djel_3 = new int [vel_pop];
		djel_r_1 = new int [vel_pop];

		translacija = translat;
		index_s = index_sort;
		index_c = index_cont;
		
		

		if(!(djel_1 && djel_3 && fc_1 && fc_3 && krom_1 && rez && index_sort && index && index_cont && translat && translat_sort_1 && translat_sort_2)) _ASSERT(0);
		if(ip.br_rok == 3)if(!krom_2) _ASSERT(0);
		if(ip.br_rok == 3 && !(ip.ljet_jesn)) if(!(krom_2 && translat_2_2 && fc_r_2 && djel_r_2)) _ASSERT(0);
		if(ip.br_rok == 3 && ip.ljet_jesn) if(!translat_6) _ASSERT(0);

	

		for(i = 0; i < isz(smjer, 0); i++) index[i] = i;
		if(ip.br_rok == 3)
		for(i = 0; i < isz(smjer, 1); i++) index[i + isz(smjer, 0)] = i;

		
		if(ip.br_rok == 1 || ip.br_rok == 2)
		{
			for(i = 0; i <  ip.br_rok * vel_pop; i++)
				memcpy((index_cont + i * isz(smjer, 0)), index, isz(smjer, 0) * sizeof(int));
		}
		else
		if(!ip.ljet_jesn)
		{
			for(i = 0; i <  ip.br_rok * vel_pop; i++)
				memcpy((index_cont + i * isz(smjer, 0)), index, isz(smjer, 0) * sizeof(int));

			for(i = 0; i <  ip.br_rok * vel_pop; i++)
				memcpy((index_cont + sir_gen[0] * vel_pop + i * isz(smjer, 1)), index + isz(smjer, 0), isz(smjer, 1) * sizeof(int));
		}
		else
		{
			
			for(i = 0; i < ip.br_rok * vel_pop; i++)
				memcpy(index_cont + i * (isz(smjer, 0) + isz(smjer, 1)), index, isz(smjer, 0) * sizeof(int));

			for(i = 0; i < ip.br_rok * vel_pop; i++)
				memcpy(index_cont + i * (isz(smjer, 0) + isz(smjer, 1)) + isz(smjer, 0), index + isz(smjer, 0), isz(smjer, 1) * sizeof(int));
		}//else


// smještanje pravih funkcija dekodiranja genetskog koda u polje pokazivaèa
		t_f[0] = &Gen::translat_p;
		for(i = 1; i < ip.br_rok; i++)
			if(i != ip.br_rok - 1) t_f[i] = &Gen::translat_u;
			else t_f[i] = &Gen::translat_z;


		gran_dol_dan = gran.dol_gran_rok;
		gran_gor_dan = gran.gor_gran_rok;
		if(ip.br_rok == 1)
		{
			del_x_v = (double) ip.br_rad_dan  / (double) maska;
			min_disp_dan = 2;
			min_disp_dan_2 = 1;
			del_x_u = 0;

		}
		else
		if(ip.br_rok == 2) 
		{
			if(!(gran.gor_gran_rok_1 % 7))
				temp = (gran.gor_gran_rok_1 / 7 - 1) * 2;
			else
				temp = (gran.gor_gran_rok_1 / 7) * 2;
			del_x_v = (gran.gor_gran_rok_1 - temp) / maska;

			del_x_u = 0;
			min_disp_dan = 2;
			min_disp_dan_2 = 1;

		}
		else
			if(ip.br_rok == 3)
			{
				
				if(!(gran.gor_gran_rok_1 % 7))
					temp = (gran.gor_gran_rok_1 / 7 - 1) * 2;
				else
					temp = (gran.gor_gran_rok_1 / 7) * 2;
				del_x_v = (gran.gor_gran_rok_1 - temp) / maska;

				if(!(gran.gor_gran_rok_2 % 7))
					temp = (gran.gor_gran_rok_2 / 7 - 1) * 2;
				else
					temp = (gran.gor_gran_rok_2 / 7) * 2;

				if(!(gran.dol_gran_rok % 7))
					temp1 = (gran.dol_gran_rok / 7 - 1) * 2;
				else
					temp1 = (gran.dol_gran_rok / 7) * 2;
				del_x_u = ((gran.gor_gran_rok_2 - temp) - (gran.dol_gran_rok - temp1)) / maska;

				min_disp_dan = 2;
				min_disp_dan_2 = 1;

							
			}//if
	
// punjenje pokaziovaèa na funkciju dobrote pravom vrijednosti koja ovisi o kojem se ispitnom periodu radi
		if(ip.br_rok == 1)
		{
			f = &Gen :: fija_cilja_p;
			najb = &Gen :: ukupno_najbolj_p;
		}
		else
			if(ip.br_rok == 2)
			{
				f = &Gen :: fija_cilja_z;
				najb = &Gen :: ukupno_najbolj_z;
			}
			else
				if(!ip.ljet_jesn)
				{
					f = &Gen :: fija_cilja_lj;
					najb = &Gen :: ukupno_najbolj_lj;
				}
				else 
				{
					f = &Gen :: fija_cilja_j;
					najb = &Gen :: ukupno_najbolj_j;
				}//else

//punjenje matrice dekodiranim vrijednostima genetskog koda
	if(ip.br_rok == 3)
	{
		for(i = 0; (unsigned long)i < maska + 1; i++)
		{
			trans_krom[i] = i;
			for(j = 0; j < ip.br_rok; j++)
				(trans_dan[j])[i] = (this ->* t_f[j])(i, ip);

	}//for i
	}
	else
	if(ip.br_rok == 2)
	{
		for(i = 0; (unsigned long)i < maska + 1; i++)
		{
			(trans_dan[0])[i] = (this ->* t_f[0])(i, ip);
			(trans_dan[1])[i] = (this ->* t_f[1])(i, ip);
		}
	}
	else
	{
		for(i = 0; (unsigned long)i < maska + 1; i++)
			(trans_dan[0])[i] = (this ->* t_f[0])(i, ip);
	}

	
}//Gen



Gen :: Gen()
{
	vel_pop = 0;
	rez = NULL;
	djel_ost = NULL;
	vel_elim = 0;
	sir_jed = 0;
	krom_1 = NULL;
	krom_2 = NULL;
	djel_min_udalj = NULL;
	index_sort = NULL;
	index = NULL;
	index_cont = NULL;
	translat_sort_1 = NULL;
	translat = NULL;
	t_f = NULL;
	fc_1 = NULL;
	fc_3 = NULL;
	fc = NULL;
	djel_1 = NULL;
	djel_3 = NULL;
	djel_r_1 = NULL;
	djel_r_2 = NULL;
	translat_2_2 = NULL;
	fc_r_1 = NULL;
	fc_r_2 = NULL;
	djel_4 = NULL;
	rez_sort = NULL;
	translat_6 = NULL;
	djel_ost_korjen = NULL;

}//Gen

void Gen :: destrukt()
{

	if(krom_1) delete [] krom_1;
	if(krom_2) delete [] krom_2;
	if(djel_ost) delete [] djel_ost;
	if(djel_ost_korjen) delete [] djel_ost_korjen;
	if(djel_min_udalj) delete [] djel_min_udalj;
	if(rez) delete []rez;
	if(index_sort) delete []index_sort;
	if(index) delete [] index;
	if(index_cont) delete [] index_cont;
	if(translat_sort_1) delete [] translat_sort_1;
	if(translat) delete []translat;
	if(t_f) delete [] t_f;
	if(fc_1) delete [] fc_1;
	if(fc_3) delete [] fc_3;
	if(djel_1) delete [] djel_1;
	if(djel_3) delete [] djel_3;
	if(djel_r_1) delete [] djel_r_1;
	if(djel_r_2) delete [] djel_r_2;
	if(translat_2_2) delete [] translat_2_2;
	if(fc_r_1) delete [] fc_r_1;
	if(fc_r_2) delete [] fc_r_2;
	if(djel_4) delete [] djel_4;
	if(rez_sort) delete [] rez_sort;
	if(translat_6) delete [] translat_6;
}//destrukt

Gen :: ~Gen()
{
	destrukt();	
}//~Gen

//funkcija koja sortira "ulazna polja"
void Gen :: shellsort(int* polje_s, int* index_sort_1, int* index_sort_2, int n)
{
	int k, q, i;
	unsigned long t;


if((index_sort_1 != NULL) && (index_sort_2 == NULL))
{
	k = n / 2;

	while(k >= 1)
	{
		q = 1;

		while(q)
		{
			q = 0;

			for(i = 0; i <  n  - k; i++)
			{
				
				if(polje_s[i] > polje_s[i+k])
				{
					t = polje_s[i];
					polje_s[i] = polje_s[i + k];
					polje_s[i + k] = t;

					t = index_sort_1[i];
					index_sort_1[i] = index_sort_1[i + k];
					index_sort_1[i + k] = t;

					q = 1;
				}//if
			}//for
		}//while

		k /= 2;

	}//while
}
else
if((index_sort_1 == NULL) && (index_sort_2 == NULL))
{
	k = n / 2;

	while(k >= 1)
	{
		q = 1;

		while(q)
		{
			q = 0;

			for(i = 0; i <  n  - k; i++)
			{
				
				if(polje_s[i] > polje_s[i+k])
				{
					t = polje_s[i];
					polje_s[i] = polje_s[i + k];
					polje_s[i + k] = t;
					q = 1;
				}//if
			}//for
		}//while

		k /= 2;

	}//while
}
else
{
	k = n / 2;

	while(k >= 1)
	{
		q = 1;

		while(q)
		{
			q = 0;

			for(i = 0; i <  n  - k; i++)
			{
				
				if(polje_s[i] > polje_s[i+k])
				{
					t = polje_s[i];
					polje_s[i] = polje_s[i + k];
					polje_s[i + k] = t;

					t = index_sort_1[i];
					index_sort_1[i] = index_sort_1[i + k];
					index_sort_1[i + k] = t;

					t = index_sort_2[i];
					index_sort_2[i] = index_sort_2[i + k];
					index_sort_2[i + k] = t;

					q = 1;
				}//if
			}//for
		}//while

		k /= 2;

	}//while
}
}//shellsort


//funkcija koja sortira "ulazna polja"
void Gen :: shellsort(int* polje_s, int* index_sort_1, int* index_sort_2, int* index_sort_3, int* index_sort_4, int n)
{
	int k, q, i;
	unsigned long t;


	k = n / 2;

	while(k >= 1)
	{
		q = 1;

		while(q)
		{
			q = 0;

			for(i = 0; i <  n  - k; i++)
			{
				
				if(polje_s[i] > polje_s[i+k])
				{
					t = polje_s[i];
					polje_s[i] = polje_s[i + k];
					polje_s[i + k] = t;

					t = index_sort_1[i];
					index_sort_1[i] = index_sort_1[i + k];
					index_sort_1[i + k] = t;

					t = index_sort_2[i];
					index_sort_2[i] = index_sort_2[i + k];
					index_sort_2[i + k] = t;

					t = index_sort_3[i];
					index_sort_3[i] = index_sort_3[i + k];
					index_sort_3[i + k] = t;

					t = index_sort_4[i];
					index_sort_4[i] = index_sort_4[i + k];
					index_sort_4[i + k] = t;

					q = 1;
				}//if
			}//for
		}//while

		k /= 2;

	}//while

}//shellsort

//dekodiranje genetskog koda poèetnog vremenskog perioda 
int Gen :: translat_p(unsigned long k, const Ispit_Period& ip)
{
	
	int temp, temp1;

	
	if(k == maska) k--;
	temp =(int)(k * del_x_v + 1);

	if(temp % 5) 
		temp1 = temp / 5;
	else 
		temp1 = temp / 5 - 1;

	temp += 2 * temp1;
		
	return (temp); 

}//translat_u

//dekodiranje genetskog koda poèetnog unutrašnjeg perioda 
int Gen :: translat_u(unsigned long k, const Ispit_Period& ip)
{
	int temp, temp1, temp2;

	if(k == maska) k--;
	temp =(int)(k * del_x_v + 1);
	temp2 = temp + gran_dol_ost_u;

	if(temp2 % 5) 
		temp1 = temp2 / 5;
	else 
		temp1 = temp2 / 5 - 1;

	temp += 2 * temp1;
	temp += gran_dol_dan;
	
		
	return (temp); 

}//translat_u

//dekodiranje genetskog koda vanjskog vremenskog perioda 
int Gen :: translat_z(unsigned long k, const Ispit_Period& ip)
{
	int temp, temp1, temp2;
	

	
	if(k == maska) k--;
	temp =(int)(k * del_x_v + 1);
	temp2 = temp + gran_dol_ost_v;

	if(temp2 % 5) 
		temp1 = temp2 / 5;
	else 
		temp1 = temp2 / 5 - 1;

	temp += 2 * temp1;
	temp += poc_van;
		
	return (temp); 

}//translat_v

// za zadani datum traži korespondirajuæi genetski kod
int Gen :: trans_inverz(int dan, int rok)
{
	int i;

	for(i = 0; (unsigned long)i < maska + 1; i++)
		if(dan == (trans_dan[rok])[i]) return trans_krom[i];

	return 0;

}//trans_inverz


void Gen :: fija_cilja_1(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	int temp1, temp2;
	int i, j, k, l;
	int djel;
	double f1;
	  
	memcpy(translat_sort_1, translacija, isz(smjer, 0) * ip.br_rok * vel_pop * sizeof(int));
	memcpy(index_s, index_cont, isz(smjer, 0) * ip.br_rok * vel_pop * sizeof(int));
	for(i = 0; i < br_grup_krom; i++) 
		shellsort((translat_sort_1 + i * isz(smjer, 0)), (index_s + i * isz(smjer, 0)), NULL, isz(smjer, 0));

	for(i = 0; i < vel_pop; i ++)
	{

		f1 = 0;
		djel = 0;
		
		for(j = 0; j < ip.br_rok; j++)
		{

			for(k = j * isz(smjer, 0); k < (j + 1) * isz(smjer, 0); k++)
			for(l = k + 1; l < (j + 1) * isz(smjer, 0); l++)
			{
				temp2 = (translat_sort_1[i * sir_gen[0] + l] - translat_sort_1[i * sir_gen[0] + k]);
				temp2 = abs(temp2);
				temp1 = isz(smjer, 0, index_s[i * sir_gen[0] + l], 0, index_s[i * sir_gen[0] + k]);
  
				if(l != k + 1) 
					f1 += sqrt((double)(temp1 *  temp2));
				else
					if(temp2 < min_disp_dan) 
					{
						f1 += 0; 
						djel++;
						if(temp2 < min_disp_dan_2) 
							djel += 2;
					}
					else
						f1 += sqrt((double)(temp1 *  temp2));

			}//for l
		}// for j

		fc_1[i] = f1;

		djel_1[i] = djel;

	}//for i

}//fija_cilja_1

void Gen :: fija_cilja_1_2(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	double f1_2;
	int temp1, temp2;
	int i, j, k, l;
	int djel;
	  
	memcpy(translat_sort_1, translacija, sir_gen[s] * vel_pop * sizeof(int));
	memcpy(index_s, index_c, sir_gen[s] * vel_pop * sizeof(int));
	for(i = 0; i < br_grup_krom; i++) 
		shellsort((translat_sort_1 + i * isz(smjer, s)), (index_s + i * isz(smjer, s)), NULL, isz(smjer, s));


	memcpy(translat_sort_2, translacija, sir_gen[s] * vel_pop * sizeof(int));
	for(i = 0; i < vel_pop; i++)
		shellsort((translat_sort_2 + i * sir_gen[s]), NULL, NULL, sir_gen[s]);


	for(i = 0; i < vel_pop; i ++)
	{


		f1_2 = 0;
		
		
		for(j = 0; j < ip.br_rok; j++)
		{

			for(k = j * isz(smjer, s); k < (j + 1) * isz(smjer, s); k++)
			for(l = k + 1; l < (j + 1) * isz(smjer, s); l++)
			{
				temp2 = (translat_sort_1[i * sir_gen[s] + l] - translat_sort_1[i * sir_gen[s] + k]);
				temp2 = abs(temp2);
				temp1 = isz(smjer, s, index_s[i * sir_gen[s] + l], s, index_s[i * sir_gen[s] + k]);
					f1_2 += sqrt((double)(temp1 *  temp2));
		

			}//for l
		}// for j


		djel = 0;

		for(j = 0; j < sir_gen[s] - 1; j++)
		{
			temp2 = (int)translat_sort_2[i * sir_gen[s] + (j + 1)] - (int)translat_sort_2[i * sir_gen[s] + j];
			if(temp2 < min_disp_dan)
			{
				djel++;
				if(temp2 < min_disp_dan_2) djel += 2;
			}//if
		}//for j


		fc_1[i] = f1_2;

		djel_1[i] = djel;
		
		


	}//for i


}//fija_cilja_1_2



void Gen :: fija_cilja_3(int s, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{

	double f3;
	int temp2;
	int temp1;
	int i, j, k;
	int djel_max;
	int djel_min;

	for(i = 0; i < vel_pop; i ++)
	{

		djel_max = 0;
		djel_min = 0;
		f3 = 0;


		for(j = 0; j < ip.br_rok - 1; j++)
			for(k = 0; k < isz(smjer, s); k++)
			{
				temp2 = translacija[i * sir_gen[s] + (j + 1) * isz(smjer, s) + k]; 
				temp2 -= translacija[i * sir_gen[s] + j * isz(smjer, s) + k];
				temp2 = abs(temp2);
			

				if((int)temp2 > gran_gor_dan) 
					djel_max++;
		
				if((int)temp2 < gran_dol_dan)
					djel_min += (gran_dol_dan - temp2);// * 2;
					
				temp1 = isz(smjer, s, k, s, k);
				f3 += sqrt( (float)temp1 * temp2);
			}//for k

		fc_3[i] = f3;

		djel_3[i] = djel_max;
		
		if(s) djel_min_udalj[i] += djel_min;
		else djel_min_udalj[i] = djel_min;
	}//for i


}//fija_cilja_3

void Gen :: fija_cilja_4(Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	int i, j;
	int  djel;
	int temp;
	//int djel3;

	for(i = 0; i < vel_pop; i++)
	{
		djel = 0;
		for(j = 0; j < (sir_gen_u) - 1; j++)
		{
			temp = translat_2_2[i * (sir_gen_u) + j + 1] - translat_2_2[i * (sir_gen_u) + j];
			if(temp < min_disp_dan_2) 
				djel++;
		}//for j


		djel_4[i] = djel;

	}//for i

}//fija_cilja_4


void Gen :: fija_cilja_5(Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	
	double f5;
	int temp1, temp2;
	int i, j, k, l;
	int djel, djel3;


	memcpy(translat_sort_1, translat, (sir_gen_u) * vel_pop * sizeof(int));
	memcpy(index_sort, index_cont, (sir_gen_u) * vel_pop * sizeof(int));

	for(i = 0; i < br_grup_krom; i++) 
		shellsort((translat_sort_1 + i * (isz(smjer, 0) + isz(smjer, 1))), (index_sort + i * (isz(smjer, 0) + isz(smjer, 1))), (translat_2_2 + i * (isz(smjer, 0) + isz(smjer, 1))), (isz(smjer, 0) + isz(smjer, 1)));


	memcpy(translat_sort_2, translat, (sir_gen_u) * vel_pop * sizeof(int));
	for(i = 0; i < vel_pop; i++)
		shellsort((translat_sort_2 + i * (sir_gen_u)), NULL, NULL, (sir_gen_u));


	for(i = 0; i < vel_pop; i ++)
	{

		f5 = 0;
		
		for(j = 0; j < ip.br_rok; j++)
		{

			for(k = j * (isz(smjer, 0) + isz(smjer, 1)); k < (j + 1) * (isz(smjer, 0) + isz(smjer, 1)); k++)
			for(l = k + 1; l < (j + 1) * (isz(smjer, 0) + isz(smjer, 1)); l++)
			{
				temp2 = (translat_sort_1[i * (sir_gen_u) + l] - translat_sort_1[i * (sir_gen_u) + k]);
				temp2 = abs(temp2);
				temp1 = isz(smjer, translat_2_2[i * (sir_gen_u) + l], index_sort[i * (sir_gen_u) + l], translat_2_2[i * (sir_gen_u) + k], index_sort[i * (sir_gen_u) + k]);
				f5 += sqrt((double)(temp1 *  temp2));
		
			}//for l
		}// for j



		djel = 0;

		for(j = 0; j < (sir_gen_u) - 1; j++)
		{
			temp2 = (int)translat_sort_2[i * (sir_gen_u) + (j + 1)] - (int)translat_sort_2[i * (sir_gen_u) + j];
			if(temp2 < min_disp_dan_2)
				djel++;
	
		}//for j

		djel3 = 0;

		if(sir_gen_u > 2)
		for(j = 0; j < sir_gen_u - 2; j++)
		{
			if(translat_sort_2[i * sir_gen_u + j] == translat_sort_2[i * sir_gen_u + j + 1] == translat_sort_2[i * sir_gen_u + j + 2])
				djel3++;
		}//for j


		
		fc_1[i] = f5;

		djel_1[i] = djel + djel3;


	}//for 

}//fija_cilja_5

void Gen :: fija_cilja_6(Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	double f3;
	int temp2;
	int i, j, k, l;
	int djel_max;
	int djel_min;

	for(i = 0; i < vel_pop; i ++)
	{

		djel_max = 0;
		djel_min = 0;
		f3 = 0;

		for(l = 0; l < 2; l++)
		for(j = 0; j < ip.br_rok - 1; j++)
			for(k = 0; k < isz(smjer, l); k++)
			{
				temp2 = translat[i * (sir_gen_u) + (j + 1) * (isz(smjer, 0) + isz(smjer, 1)) + isz(smjer, 0) * l + k]; 
				temp2 -= translat[i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) + isz(smjer, 0) * l + k];
				temp2 = abs(temp2);
			

				if((int)temp2 > gran_gor_dan) 
					djel_max++;
		
				if((int)temp2 < gran_dol_dan)
					djel_min += (gran_dol_dan - temp2);
					
				
				f3 += sqrt( (float)isz(smjer, l, k, l, k) * temp2);
			}//for k

		fc_3[i] = f3;

		djel_3[i] = djel_max;
		djel_min_udalj[i] = djel_min;
		
	}//for i


}//fija_cilja_6

//funkcija  koja raèuna funkciju dobrote za proljetni ispitni rok
void Gen :: fija_cilja_p(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	int i, j, k;
	int  djel;
	

	djel_max_1 = 0;
	djel_max_4 = 0;

	//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	index_s = index_sort;
	translacija = translat;
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 0); k++)
				translacija[i * sir_gen[0] + j * isz(smjer, 0) + k] = (trans_dan[j])[krom_1[i * sir_gen[0] + j * isz(smjer, 0) + k]];
	
	
	max_j = 0;

	fija_cilja_1(0, isz, ip);// funkcija koja raèuna funkciju dobrote i kazne

	
	for(i = 0; i < vel_pop; i++)
	{
		
		
		djel = djel_1[i] * 2;
		djel_ost[i] = djel;
		djel_ost_korjen[i] = sqrt((double)djel);

		pd[i] = fc_1[i];//punjenje polja u kojem se nalaze vrijednosti funkcije dobrote


	}//for i


}//fija_cilja_p_j


void Gen :: ukupno_najbolj_p(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
		
	
		max = pd[m_i];
			
		f1_max = fc_1[m_i];
		f2_max = 0;
		max_j = 1;
		djel_max = djel_1[m_i];

		memcpy(rez,(translacija + m_i * sir_gen[0]), sir_gen[0] * sizeof(int));
		memcpy(index, index_cont, sir_gen[0] * sizeof(int));
		memcpy(rez_sort, rez, sir_gen[0] * sizeof(int));

		
		shellsort(rez_sort , index, NULL, isz(smjer, 0));

}//ukupno_najbolj_p

//funkcija  koja raèuna funkciju dobrote za proljetni ispitni rok
void Gen :: fija_cilja_z(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	int i, j, k;
	int  djel;
	

	djel_max_1 = 0;
	djel_max_4 = 0;
	//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	//koje sadrže ispite s zimskog semestra
	index_s = index_sort;
	translacija = translat;
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 0); k++)
				translacija[i * sir_gen[0] + j * isz(smjer, 0) + k] = (trans_dan[j])[krom_1[i * sir_gen[0] + j * isz(smjer, 0) + k]];
			
	
	
	max_j = 0;

	

	//funkcija raèuna prvi dio funkcije dobrote ( meðusobni odnosi ispita na ispitnim rokovima )
	// i s time povezane kazne dispergije
	fija_cilja_1_2(0, isz, ip);
	//funkcija raèuna drugi dio funkcije dobrote koji korespondira s udaljenošæu ispita iz istog kolegija na 1. i 2.
	//ispitnom roku i s time povezane kazne min i max udaljenosti meðu ispitima istog kolegija
	fija_cilja_3(0, isz, ip);

	for(i = 0; i < vel_pop; i++)
	{
		
		
		djel = (djel_1[i] + djel_3[i]) * 2;
		djel_ost[i] = djel;
		djel_ost_korjen[i] = sqrt((double)djel);
		if(!djel) djel = 1;

		pd[i] = (fc_1[i] + odn_fij * fc_3[i]);//punjenje polja u kojem se nalaze vrijednosti funkcije dobrote



	}//for i



}// fija_cilja_z

void Gen :: ukupno_najbolj_z(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{

	int i;

		max = pd[m_i];
		f1_max = fc_1[m_i];
		f2_max = fc_3[m_i] * odn_fij;
		max_j = 1;
		djel_max = djel_1[m_i] + djel_3[m_i];

		memcpy(rez,(translacija + m_i * sir_gen[0]), sir_gen[0] * sizeof(int));
		memcpy(index, index_cont, sir_gen[0] * sizeof(int));
		memcpy(rez_sort, rez, sir_gen[0] * sizeof(int));

		for(i = 0; i < ip.br_rok; i++)
			shellsort(rez_sort + isz(smjer, 0) * i, index + isz(smjer, 0) * i, NULL, isz(smjer, 0));
	

}//ukupno_najbolj_z


//funkcija  koja raèuna funkciju dobrote za ljetni ispitni rok
void Gen :: fija_cilja_lj(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{
	int i, j, k;
	int  djel;
		
	max_j = 0;


//--------------------------------------------------------------------------------------------

		//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	//koje sadrže ispite s zimskog semestra

	index_s = index_sort;
	translacija = translat;
	index_c = index_cont;
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 0); k++)
				translacija[i * sir_gen[0] + j * isz(smjer, 0) + k] = (trans_dan[j])[krom_1[i * sir_gen[0] + j * isz(smjer, 0) + k]];
	

		//funkcija raèuna prvi dio funkcije dobrote ( meðusobni odnosi ispita na ispitnim rokovima )
	// i s time povezane kazne dispergije za ispite pedavane u zimskom semestru
	fija_cilja_1_2(0, isz, ip);
		//funkcija raèuna drugi dio funkcije dobrote koji korespondira s udaljenošæu ispita iz istog kolegija na 1. i 2.
	//ispitnom roku i s time povezane kazne min i max udaljenosti meðu ispitima istog kolegija
	//za ispite predavanu u zimskom semestru
	fija_cilja_3(0, isz, ip);
		
	for(i = 0; i < vel_pop; i++)
	{
		fc_r_1[i] = fc_1[i] + odn_fij * fc_3[i];
		djel_r_1[i] = (djel_1[i] + djel_3[i]);
	}//for i

	for(i = 0; i < vel_pop; i++)
		memcpy(translat_2_2 + i * (sir_gen_u), translat_sort_2 + i * sir_gen[0], sir_gen[0] * sizeof(int));


//--------------------------------------------------------------------------------------------

		//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	//koje sadrže ispite s ljetnog semestra
	translacija = translat + vel_pop * sir_gen[0];
	index_s = index_sort + vel_pop * sir_gen[0];
	index_c = index_cont + vel_pop * sir_gen[0];
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 1); k++)
				translacija[i * sir_gen[1] + j * isz(smjer, 1) + k] = (trans_dan[j])[krom_2[i * sir_gen[1] + j * isz(smjer, 1) + k]];


			//funkcija raèuna prvi dio funkcije dobrote ( meðusobni odnosi ispita na ispitnim rokovima )
	// i s time povezane kazne dispergije za ispite pedavane u ljetnom semestru
	fija_cilja_1_2(1, isz, ip);
			//funkcija raèuna drugi dio funkcije dobrote koji korespondira s udaljenošæu ispita iz istog kolegija na 1. i 2.
	//ispitnom roku i s time povezane kazne min i max udaljenosti meðu ispitima istog kolegija
	//za ispite predavanu u ljetnom semestru

	fija_cilja_3(1, isz, ip);
	
	
	for(i = 0; i < vel_pop; i++)
	{
		fc_r_2[i] = fc_1[i] + odn_fij * fc_3[i];
		djel_r_2[i] = (djel_1[i] + djel_3[i]);
	}//for i


	for(i = 0; i < vel_pop; i++)
		memcpy(translat_2_2 + i * (sir_gen_u) + sir_gen[0], translat_sort_2 + i * sir_gen[1], sir_gen[1] * sizeof(int));

	
//--------------------------------------------------------------------------------------------

	for(i = 0; i < vel_pop; i++)
		shellsort(translat_2_2 + i * (sir_gen_u), NULL, NULL, (sir_gen_u));
		
	//funkcija koja raèuna kaznu za ukupnu dispergiju ispita po ispitnim rokovima
	fija_cilja_4(isz, ip);

//--------------------------------------------------------------------------------------------

	for(i = 0; i < vel_pop; i++)
	{
		
		
		djel = djel_r_2[i] * 40 + (djel_r_1[i] + djel_4[i]) * 2;//sumiranje kazni
		djel_ost[i] = djel;
		djel_ost_korjen[i] = sqrt((double)djel);

		if(!djel) djel = 1;

		//punjenje polja u kojem se nalaze vrijednosti funkcije dobrote
		//s vrijednostima ispita iz zimskok i ljetnog semestra
		pd[i] = (fc_r_1[i] + fc_r_2[i]);



	}//for i



}//fija_cilja_lj

void Gen :: ukupno_najbolj_lj(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{

	int i;
		max = pd[m_i];
		f1_max = fc_1[m_i];
		f2_max = fc_3[m_i] * odn_fij;
		djel_max_1 = djel_r_1[m_i];
		djel_max = djel_r_2[m_i];
		djel_max_4 = djel_4[m_i];

		memcpy(rez,(translat + m_i * sir_gen[0]), sir_gen[0] * sizeof(int));
		memcpy(index, index_cont, sir_gen[0] * sizeof(int));
		memcpy(rez_sort, rez, sir_gen[0] * sizeof(int));
	
		memcpy(rez + sir_gen[0],(translat + vel_pop * sir_gen[0] + m_i * sir_gen[1]), sir_gen[1] * sizeof(int));			
		memcpy(index + sir_gen[0], index_cont + sir_gen[0] * vel_pop, sir_gen[1] * sizeof(int));
		memcpy(rez_sort + sir_gen[0], rez + sir_gen[0], sir_gen[1] * sizeof(int));

		for(i = 0; i < ip.br_rok; i++)
		{
			shellsort(rez_sort + i * isz(smjer, 0), index + i * isz(smjer, 0), NULL, isz(smjer, 0));
			shellsort(rez_sort + sir_gen[0] + i * isz(smjer, 1), index + sir_gen[0] + i * isz(smjer, 1), NULL, isz(smjer, 1));
		}//for i
		
}//ukupno_najbolj_lj

//funkcija  koja raèuna funkciju dobrote za ljetni ispitni rok
void Gen :: fija_cilja_j(Polje_D& pd, Ispit_Stud_Zavod& isz, const Ispit_Period& ip)
{

	int i, j, k;
	int  djel;
		
	max_j = 0;

			//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	//koje sadrže ispite s zimskog semestra
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 0); k++)
				translat[i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) + k] = (trans_dan[j])[krom_1[i * sir_gen[0] + j * isz(smjer, 0) + k]];

			//punjenje polja translat s dekodiranim vrijednostima genetskog koda jedinki
	//koje sadrže ispite s ljetnog semestra
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			for(k = 0; k < isz(smjer, 1); k++)
				translat[i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) + isz(smjer, 0) + k] = (trans_dan[j])[krom_2[i * sir_gen[1] + j * isz(smjer, 1) + k]];




	
	for(i = 0; i < vel_pop; i++)
		for(j = 0; j < ip.br_rok; j++)
			 memset(translat_2_2 + i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) , 0, isz(smjer, 0) * sizeof(int));


	for(i = 0; i < vel_pop; i++)
	for(j = 0; j < ip.br_rok; j++)
		for(k = 0; k < isz(smjer, 1); k++)
			translat_2_2[i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) + isz(smjer, 0) + k] = 1;


			//funkcija raèuna prvi dio funkcije dobrote ( meðusobni odnosi ispita na ispitnim rokovima )
	// i s time povezane kazne dispergije za ispite pedavane u zimskom i ljetnom semestru
	fija_cilja_5(isz, ip);
				//funkcija raèuna drugi dio funkcije dobrote koji korespondira s udaljenošæu ispita iz istog kolegija na 1. i 2.
	//ispitnom roku i s time povezane kazne min i max udaljenosti meðu ispitima istog kolegija
	//za ispite predavanu u zimskom i ljetnom semestru
	fija_cilja_6(isz, ip);



	for(i = 0; i < vel_pop; i++)
	{
		fc_r_1[i] = fc_1[i] + odn_fij * fc_3[i];//raèunanje funkcije dobrote
		djel_r_1[i] = (djel_1[i] + djel_3[i]);//raèunanje kazni pojedinih jedinki
	}//for i


	for(i = 0; i < vel_pop; i++)
	{
		
		
		djel = djel_r_1[i] * 2;
		djel_ost[i] = djel;
		djel_ost_korjen[i] = sqrt((double)djel);

		if(!djel) djel = 1;

		//punjenje polja u kojem se nalaze vrijednosti funkcije dobrote
		//s vrijednostima ispita iz zimskok i ljetnog semestra
		pd[i] = fc_r_1[i];

	
	}//for i

}//fija_cilja_j

void Gen :: ukupno_najbolj_j(Polje_D& pd, int m_i, const Ispit_Period& ip, Ispit_Stud_Zavod& isz)
{
	
	int i, j;
			max = pd[m_i];
			f1_max = fc_1[m_i];
			f2_max = fc_3[m_i] * odn_fij;
			djel_max_1 = djel_1[m_i];
			djel_max = djel_r_1[m_i] * 2;;
			djel_max_4 = djel_3[m_i];

		
	
		for(i = 0; i < 2; i++)
		for(j = 0; j < ip.br_rok; j++)
			memcpy(rez + j * isz(smjer, i) + i * sir_gen[0],(translat + m_i * (sir_gen_u) + j * (isz(smjer, 0) + isz(smjer, 1)) + i * isz(smjer, 0)), isz(smjer, i) * sizeof(int));
	
		for(i = 0; i < 2; i++)
		for(j = 0; j < ip.br_rok; j++)
			memcpy(index + j * isz(smjer, i) + i * sir_gen[0],(index_cont + j * (isz(smjer, 0) + isz(smjer, 1)) + i * isz(smjer, 0)), isz(smjer, i) * sizeof(int));
	
		memcpy(rez_sort, rez, (sir_gen_u) * sizeof(int));

		for(i = 0; i < ip.br_rok; i++)
		{
			shellsort(rez_sort + i * isz(smjer, 0), index + i * isz(smjer, 0), NULL, isz(smjer, 0));
			shellsort(rez_sort + sir_gen[0] + i * isz(smjer, 1), index + sir_gen[0] + i * isz(smjer, 1), NULL, isz(smjer, 1));
		}//for i
		


}//ukupno_najbolj_j


void Gen :: provjeri(int* p, int index, int poz, int n)
{
	int i;

	for(i = 0; i < index; i++)
		if(p[i] == poz) 
		{
			provjeri(p, index, ((poz + 1) % n), n);
			return;

		}//if

	p[index] = poz;

}//provjeri

//stvaranje poèetne populacije jedinki
void Gen :: pocetna_generacija(Polje_I& poc_gen_plan, Ispit_Stud_Zavod& isz, Ispit_Period& ip)
{
	int i, j, k, l, m;
	int djel, djel_1, djel_2, poc, poc_1, poc_2, temp;
	double ostatak;
	unsigned long* k_p;
	int razmak[2], ost[2];
	int* mjes;
	
//popunjavanje genetskog koda sluèajnim brojevima
	if(ip.br_rok == 1)
	{

		for(i = 0; i < vel_pop; i++)
		{
			djel = (RAND_MAX / maska) + 1;
			for(j = 0; j < isz(smjer, 0); j++)
				krom_1[i * sir_gen[0] + j] = rand() / djel;
		
		}//for i
	}
	else
	{
		

		if(ip.br_rok == 2)
		{

			ostatak = 100.0;
					
			djel = (int)(ceil(RAND_MAX / (ostatak / 100.0 * maska)) + 1);

				

			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 0); k++)
					krom_1[j * sir_gen[0] + 0 * isz(smjer, 0) + k] = rand() / djel;
			
			
			poc = (int)(preklapanje_v / 100.0 * maska);
			poc = 0;

			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 0); k++)
					krom_1[j * sir_gen[0] + 1 * isz(smjer, 0) + k] = rand() / djel + poc;  	


		}
		else
		if(ip.br_rok == 3)
		{


			poc = (int)(preklapanje_u / 100.0 * maska);
			poc_1 = (int)(preklapanje_v / 100.0 * maska);
			poc = poc_1 = 0;
			
			ostatak = 100;
			djel_1 = (int)(ceil(RAND_MAX / (ostatak / 100.0 * maska)));

			ostatak = 100;
			djel = (int)(ceil(RAND_MAX / (ostatak / 100.0 * maska)) + 1);


			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 0); k++)
					krom_1[j * sir_gen[0] + 0 * isz(smjer, 0) + k] = rand() / djel_1;
			
					
			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 0); k++)
					krom_1[j * sir_gen[0] + 1 * isz(smjer, 0) + k] = rand() / djel + poc;


			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 0); k++)	
					krom_1[j * sir_gen[0] + 2 * isz(smjer, 0) + k] = rand() / djel_1 + poc_1;
			
			
			



			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 1); k++)
					krom_2[j * sir_gen[1] + 0 * isz(smjer, 1) + k] = rand() / djel_1;

			
			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 1); k++)
					krom_2[j * sir_gen[1] + 1 * isz(smjer, 1) + k] = rand() / djel + poc;

			for(j = 0; j < vel_pop; j++)
				for(k = 0; k < isz(smjer, 1); k++)
					krom_2[j * sir_gen[1] + 2 * isz(smjer, 1) + k] = rand() / djel_1 + poc_1;
			

		}//if


		//popunjavanje genetskog koda smislenim vrijednostima u razini zadanog postotka
		djel = (int)(ceil((double)RAND_MAX / (double)(vel_pop - 1)) + 1);
		ostatak = 100.0 - preklapanje_v;

 		
		razmak[0] = maska / (isz(smjer, 0) - 1);
		ost[0] = maska - razmak[0] * (isz(smjer, 0) - 1) + 1;
		
		if(ip.br_rok > 2)
		{
			razmak[1] = maska / (isz(smjer, 1) - 1);
			ost[1] = maska - razmak[1] * (isz(smjer, 1) - 1) + 1;

		
			if(ost[0] > ost[1]) ost[0] = ost[1];
			else ost[1] = ost[0];

			k_p = new unsigned long [ost[0] * isz(smjer, 0) + ost[1] * isz(smjer, 1)];
			mjes = new int [isz(smjer, 0) + isz(smjer, 1)];

		}
		else
		{
			k_p = new unsigned long [ost[0] * isz(smjer, 0)];
			mjes = new int [isz(smjer, 0)];

		}//else
		
		for(i = 0; i < ost[0]; i++)
		for(j = 0; j < isz(smjer, 0); j++)
			k_p[i * isz(smjer, 0) + j] = i + j * razmak[0];

		if(ip.br_rok > 2)
		for(i = 0; i < ost[1]; i++)
		for(j = 0; j < isz(smjer, 1); j++)
			k_p[ost[0] * isz(smjer, 0) + i * isz(smjer, 1) + j] = i + j * razmak[1];
	


		temp = (br_smisl_poc_gen) / ost[0];

		if(ip.br_rok > 2)
			for(i = 0; i < isz(smjer, 0) + isz(smjer, 1); i++) mjes[i] = maska + 1;///inic
		else
			for(i = 0; i < isz(smjer, 0); i++) mjes[i] = maska + 1;///inic

		if(ip.br_rok > 1)
		if(isz(smjer, 0) == isz(smjer, 1)) m = 1;
		else m = 0;

		djel_1 = (RAND_MAX / isz(smjer, 0)) + 1;
		if(ip.br_rok > 2)
		djel_2 = (RAND_MAX / isz(smjer, 1)) + 1;

		for(i = 0; i < ost[0]; i++)
		for(j = 0; j < temp; j++)
		{
			poc = poc_gen_plan[i * temp + j] / djel;
			
				for(l = 0; l < isz(smjer, 0); l++)
				{
					poc_1 = rand() / djel_1;
					provjeri(mjes, l, poc_1, isz(smjer, 0));		
				}//for l

				if(ip.br_rok > 2)
				for(l = 0; l < isz(smjer, 1); l++)
				{
					poc_2 = rand() / djel_2;
					provjeri(mjes + isz(smjer, 0), l, poc_2, isz(smjer, 1));		
				}//for l

			for(k = 0; k < ip.br_rok; k++)
			for(l = 0; l < isz(smjer, 0); l++)
				krom_1[poc * sir_gen[0] + k * isz(smjer, 0) + l] = k_p[i * isz(smjer, 0) + mjes[l]];

			if(ip.br_rok > 2)
			for(k = 0; k < ip.br_rok; k++)
			for(l = 0; l < isz(smjer, 1); l++)
				krom_2[poc * sir_gen[1] + k * isz(smjer, 1) + l] = (k_p[i * isz(smjer, 1) + mjes[l + isz(smjer, 0)]] + m) % maska;
		
		}//for j

			
		if(k_p) delete [] k_p;
		if(mjes) delete [] mjes;
					
	}//if

}//slucajno

//upisivanje rezultata u CStrin objekte
void Gen :: ispis(Ispit_Period& ip, Ispit_Stud_Zavod& isz, int smjer, CString** p_rezultati, int br_ponavlj)
{
	int i, j;
	int* poc_smjer_stud;
	CString ret, ret2;
	char pom[20];

	ret = "\r\n";
	ret2 = "\r\n\r\n";

	if(ip.br_rok == 3) poc_smjer_stud = isz.poc_smjer_stud;
	else poc_smjer_stud = isz.poc_smjer_stud_1;
	
	*(p_rezultati[br_ponavlj]) += ret;
	*(p_rezultati[br_ponavlj]) += "SMJER_";
	_itoa(isz.smjerovi[smjer], pom, 10);
	*(p_rezultati[br_ponavlj]) += pom;
	*(p_rezultati[br_ponavlj]) += ret2;



	for(i = 0; i < ip.br_rok; i++)
	{
		*(p_rezultati[br_ponavlj]) += ret2;
		_itoa(i + 1, pom, 10);
		*(p_rezultati[br_ponavlj]) += pom;
		*(p_rezultati[br_ponavlj]) += ". ISPITNI ROK";
		*(p_rezultati[br_ponavlj]) += ret2;

		for(j = 0; j < isz(smjer, 0); j++)
		{

			*(p_rezultati[br_ponavlj]) += "	Ispit ";
			_itoa(isz.isp_ozn_p[poc_smjer_stud[smjer] + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ") ";
			_itoa(rez[i * isz(smjer, 0) + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ".d		";
			*(p_rezultati[br_ponavlj]) += "Ispit ";
			_itoa(isz.isp_ozn_p[poc_smjer_stud[smjer] + index[i * isz(smjer, 0) + j]], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ") ";
			_itoa(rez_sort[i * isz(smjer, 0) + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ".d		";
			*(p_rezultati[br_ponavlj]) += ret;

		}//for j
		if(ip.br_rok == 3)
		{
			*(p_rezultati[br_ponavlj]) += ret;
			for(j = 0; j < isz(smjer, 1); j++)
			{

			*(p_rezultati[br_ponavlj]) += "	Ispit ";
			_itoa(isz.isp_ozn_p[poc_smjer_stud[smjer] + isz(smjer, 0) + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ") ";
			_itoa(rez[sir_gen[0] + i * isz(smjer, 1) + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ".d		";
			*(p_rezultati[br_ponavlj]) += "Ispit ";
			_itoa(isz.isp_ozn_p[poc_smjer_stud[smjer] + isz(smjer, 0) + index[sir_gen[0] + i * isz(smjer, 1) + j]], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ") ";
			_itoa((int)rez_sort[sir_gen[0] + i * isz(smjer, 1) + j], pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ".d		";
			*(p_rezultati[br_ponavlj]) += ret;

			}//for j
		}//if
				

	}//for i


	
	if(ip.br_rok > 1)
	{
	
		*(p_rezultati[br_ponavlj]) += ret2;

		for(j = 0; j < isz(smjer, 0); j++)
		{
				*(p_rezultati[br_ponavlj]) += "(";
			for(i = 0; i < ip.br_rok - 1; i++)
			{
				_itoa(rez[(i + 1) * isz(smjer, 0) + j] - rez[i * isz(smjer, 0) + j], pom, 10);
				*(p_rezultati[br_ponavlj]) += pom;
				*(p_rezultati[br_ponavlj]) += "-";
			}
				
			_itoa(isz.sif_isp(smjer, 0, j), pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ")  "; 

		}//for j

		*(p_rezultati[br_ponavlj]) += ret;

		for(j = 0; j < isz(smjer, 1); j++)
		{
			*(p_rezultati[br_ponavlj]) += "(";
			for(i = 0; i < ip.br_rok - 1; i++)
			{

				_itoa((rez + sir_gen[0])[(i + 1) * isz(smjer, 1) + j] - (rez + sir_gen[0])[i * isz(smjer, 1) + j], pom, 10);
				*(p_rezultati[br_ponavlj]) += pom;
				*(p_rezultati[br_ponavlj]) += "-";
			}
				
			_itoa(isz.sif_isp(smjer, 1, j), pom, 10);
			*(p_rezultati[br_ponavlj]) += pom;
			*(p_rezultati[br_ponavlj]) += ")  "; 

		}//for j

	*(p_rezultati[br_ponavlj]) += ret2;
	*(p_rezultati[br_ponavlj]) += "donja_granica = ";
	_itoa(gran_dol_dan, pom, 10);
	*(p_rezultati[br_ponavlj]) += pom;
	*(p_rezultati[br_ponavlj]) += "       gornja_granica = ";
	_itoa(gran_gor_dan, pom, 10);
	*(p_rezultati[br_ponavlj]) += pom;

	*(p_rezultati[br_ponavlj]) += ret2;
	*(p_rezultati[br_ponavlj]) += "__________________________________________________";
	*(p_rezultati[br_ponavlj]) += ret2;
	}//else


}//ispis

