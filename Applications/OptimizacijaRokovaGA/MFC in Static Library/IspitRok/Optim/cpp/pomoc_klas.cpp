#include "..\h\ispit_rok.h"

Polje_I :: Polje_I()
{
	m_polje = NULL;
	duljina = 0;
}

Polje_I :: Polje_I(int n)
{
	duljina = n;
	m_polje = new int [n];
	if(!m_polje) _ASSERT(0);
	set0();
}

Polje_I :: ~Polje_I()
{
	if(m_polje) delete [] m_polje;
}

int& Polje_I :: operator[](int i)
{
	return m_polje[i];
}

void Polje_I :: set0()
{
	int i;

	for(i = 0; i < duljina; i++) m_polje[i] = 0;
}

Polje_D :: Polje_D()
{
	m_polje = NULL;
	duljina = 0;
}

Polje_D :: Polje_D(int n)
{
	duljina = n;
	if(n) m_polje = new double [n];
	else m_polje = NULL;
	if(!m_polje) _ASSERT(0);
}

Polje_D :: ~Polje_D()
{
	destrukt();
}//~Polje_D

void Polje_D :: destrukt()
{
	if(m_polje) delete [] m_polje;
}//destrukt

double& Polje_D :: operator[](int i)
{
	return m_polje[i];
}

Ispit_Period :: Ispit_Period()
{
	br_rad_dan = 19;
	br_dan = 25;
	br_rok = 2;
	godina = 1;
	ljet_jesn = 0;
}//Ispit_Period

Ispit_Period :: Ispit_Period(int br, int bd, int lj_j, int g)
{
	ljet_jesn = lj_j;
	godina = g;
	br_rok = br;
	if(br_rok > 3) _ASSERT(0);
	if(g < 1 || g > 4) _ASSERT(0);
	br_dan = bd;
	br_rad_dan = bd - (bd / 7) * 2;
}//Ispit_Period

void Ispit_Period :: inic()
{
	br_rad_dan = br_dan - (br_dan / 7) * 2;
}//inic

Ispit_Stud_Zavod :: Ispit_Stud_Zavod()
{
	br_stud_p = NULL;
	isp_ozn_p = NULL;
	poc_smjer_stud = NULL;
	br_ispit_p = NULL;
	razl_isp_p = NULL;
	zaj_isp_smj_sem = NULL;
	zaj_isp_smj_poz = NULL;
	razl_isp_ozn_p = NULL;
	poc_smjer_stud_1 = NULL;
	isp_zav_ozn_p = NULL;
	count = NULL;
	presjek_p = NULL;
	br_smjer = 0;

	
}//Ispit_Stud

//odreðivanje smjera jedinke po poziciji u polju isp_ozn_p
int Ispit_Stud_Zavod :: smjer(int poz, Ispit_Period& ip)
{
	int i;

	if(ip.br_rok == 3)
	{
		for(i = 1; i < br_smjer + 1; i++)
			if(poz < poc_smjer_stud[i]) return (i - 1);

		return (br_smjer - 1);
	}
	else
	{
		for(i = 1; i < br_smjer + 1; i++)
			if(poz < poc_smjer_stud_1[i]) return (i - 1);

		return (br_smjer - 1);
	}//else
	
}//smjer

//utvrðivanje pripadnosti semestru u kojem su predavani ispiti po poziciji jedinke u polju isp_ozn_p
int Ispit_Stud_Zavod :: prvi_drugi(int poz, int smj, Ispit_Period& ip)
{
	int m;

	if(ip.br_rok == 3)
	{
		m = poz - poc_smjer_stud[smj];

		if( m < br_ispit_p[smj * 2]) 
			return 0;
		else 
			return 1;
	}
	else
	{
		return 0;
	}//else

}//prvi_drugi


//odreðivanje pozicije ispita unutar svoje grupe ispita po poziciji u polju isp_ozn_p
int Ispit_Stud_Zavod :: krom_poz(int poz, int smj, Ispit_Period& ip)
{

	int m;

	if(ip.br_rok == 3)
	{
		m = poz - poc_smjer_stud[smj];

		if( m < br_ispit_p[smj * 2]) 
			return m;
		else 
			return (m - br_ispit_p[smj * 2]);
	}
	else
	{
		m = poz - poc_smjer_stud_1[smj];
		return m;
	}//else

}//krom_poz

//èitanje podataka iz datoteke nastavni program i smještanje u podatkovna polja
int Ispit_Stud_Zavod :: podatak_3(ifstream& ifile, char* string, int* podaci)
{
	char* p;
	char* k;
	char pretvorba[20];
	int i;

		ifile >> string;
					

					p = string;

	
					for(i = 0; i < 3; i++)
					{
						p = strchr(p, '#');
						if(!p) return EXIT_FAILURE;
						p++;
					}

					p = string;

	
					for(i = 0; i < 3; i++)
					{
						k = strstr(p, "#");
						strncpy(pretvorba, p, (size_t)(k - p));
						pretvorba[(int)(k - p)] = 0;
						podaci[i] = atoi(pretvorba);
						p = ++k;
					}
		return EXIT_SUCCESS;
}

//èitanje podataka iz datoteke presjek broja studenata i smještanje u podatkovna polja
int Ispit_Stud_Zavod :: podatak_6(ifstream& ifile, char* string, int* podaci)
{

	char* p;
	char* k;
	char pretvorba[20];
	int i;

	ifile >> string;

		p = string;

	
		for(i = 0; i < 6; i++)
		{
			p = strchr(p, '#');
			if(!p) return EXIT_FAILURE;
			p++;
		}

		p = string;

	
		for(i = 0; i < 6; i++)
		{
			k = strstr(p, "#");
			strncpy(pretvorba, p, (size_t)(k - p));
			pretvorba[(int)(k - p)] = 0;
			if(i != 2)podaci[i] = atoi(pretvorba);
			else
				if(pretvorba[0] == 'O') podaci[2] = 1;
				else podaci[2] = 0;
			p = ++k;
		}

		return EXIT_SUCCESS;
}

//popunjavanje podatkovnih polja
int Ispit_Stud_Zavod :: Create(Ispit_Period& ip, CString* ime_1,CString* ime_2, CProgressCtrl& pct)
{
	int i, j, poz, poz_isp;
	int u_br_isp;
	int brjac;
	char string[50];
	int podaci[6];
	int flag;
	int br_isp_u;
	CString cstr_1 = "godina.dat";
	

	destrukt();

	if(ip.godina > 2) 
		max_stud_grup_pred = 25;
	else
		max_stud_grup_pred = 100;

	ifstream infile(*ime_1);

	ofstream ofile(cstr_1);
	

	if(!infile.is_open())
		return EXIT_FAILURE;

	if(!ofile.is_open())
		return EXIT_FAILURE;



	if(ip.br_rok == 3) mnoz = 1;
	else mnoz = 0;

	br_smjer = 0;
	br_isp_u = 0;
	brjac = 0;
	br_grup_pred = 0;
	int flag1;

//_________________________________________________________________________________________
	
//èitanje podataka iz datoteke nastavni plan i izdvajanje podataka koji se odnose na optimiziranu godinu
	while(!infile.eof())
	{
		if(EXIT_FAILURE == podatak_6(infile, string, podaci)) return EXIT_FAILURE;
		

		if((podaci[3] > ip.godina * 2 - 2) && (podaci[3] < ip.godina * 2 + 1) && podaci[2])
		{
			br_isp_u ++;
			flag = 0;
			flag1 = 0;
			if(brjac) ofile <<"\r\n"<<string;
			else { ofile << string; brjac = 1;}
			
			for(i = 0; i < br_smjer; i++)
				if(smjerovi[i] == podaci[1]) flag ++;

			for(i = 0; i < br_grup_pred; i++)
				if(grup_isp[i] == podaci[4]) flag1 ++;


			if(!flag)
			{
				smjerovi[br_smjer] = podaci[1];
				br_smjer ++;
			}

			if(!flag1)
			{
				grup_isp[br_grup_pred] = podaci[4];
				br_grup_pred ++;
			}
		}

	}//while

	infile.close();
	ofile.close();

//_________________________________________________________________________________________


	pct.SetRange(0,br_smjer + 1);
	pct.SetStep(1);
	pct.SetPos(0);
	pct.StepIt();


	br_ispit_p = new int [br_smjer * 2];



//_________________________________________________________________________________________
	
	for(i = 0; i < br_smjer * 2; i++) br_ispit_p[i] = 0;

	ifstream ifile(cstr_1);

	if(!ifile.is_open())
		return EXIT_FAILURE;//srediti


	while(!ifile.eof())
	{
		if(EXIT_FAILURE == podatak_6(ifile, string, podaci)) return EXIT_FAILURE;

		for(i = 0; i < br_smjer; i++)
		{
			if(podaci[1] == smjerovi[i])
			{
				//punjenje br_ispit_p polja s brojem kolegija u pojedinom semestru
				//svaki semestar ima podatak o br ispita u zimskom i ljetnom semestru
				if(podaci[3] == (ip.godina * 2 - 1)) br_ispit_p[i * 2] ++;
					else br_ispit_p[i * 2 + 1] ++;

				 break;
			}
		}
	}//while

	ifile.close();
//_________________________________________________________________________________________


	max_br_isp = 0;
	if(ip.br_rok == 3)
	{
		for(i = 0; i < 2 * br_smjer; i++)
			if(br_ispit_p[i] > max_br_isp) max_br_isp = br_ispit_p[i];
	}
	else
	{
		for(i = 0; i < br_smjer; i++)
			if(br_ispit_p[i * 2] > max_br_isp) max_br_isp = br_ispit_p[i * 2];
	}//else


	poc_smjer_stud = new int [br_smjer + 1];
	if(ip.br_rok == 3)
		poc_smjer_stud_1 = NULL;
	else
		poc_smjer_stud_1 = new int [br_smjer + 1];


	poc_smjer_stud[0] = 0;
	for(i = 1; i < br_smjer + 1; i++)
		poc_smjer_stud[i] = br_ispit_p[(i - 1) * 2] + br_ispit_p[(i - 1) * 2 + 1] + poc_smjer_stud[i - 1];

	if(ip.br_rok < 3)
	{
		poc_smjer_stud_1[0] = 0;
		for(i = 1; i < br_smjer + 1; i++)
			 poc_smjer_stud_1[i] = br_ispit_p[(i - 1) * 2] + poc_smjer_stud_1[i - 1];
	}//odreðivanje poèetka odreðenog smjera u poljima isp_ozn_p, isp_zav_ozn_p
	
	if(ip.br_rok < 3)
	ukup_br_isp_1 = poc_smjer_stud_1[br_smjer];


	ukup_br_isp = poc_smjer_stud[br_smjer];


	br_stud_p = new int [ukup_br_isp];
	if(ip.br_rok == 3)
		isp_ozn_p = new int [ukup_br_isp];
	else
		isp_ozn_p = new int [ukup_br_isp_1];

	

	
	if(ip.br_rok == 3)
		isp_zav_ozn_p = new int [ukup_br_isp];
	else
		isp_zav_ozn_p = new int [ukup_br_isp_1];




//_________________________________________________________________________________________	
	ifile.open(cstr_1);
	
	if(!ifile.is_open())
		return EXIT_FAILURE;


	count = new int [br_smjer * 2];
	for(i = 0; i < br_smjer * 2; i++)
		count[i] = 0;

	while(!ifile.eof())
	{
		if(EXIT_FAILURE == podatak_6(ifile, string, podaci)) return EXIT_FAILURE;

		for(i = 0; i < br_smjer; i++)
		{ 
			if(podaci[1] == smjerovi[i])
			{
				if(ip.br_rok == 3)
				{
					if(podaci[3] == (ip.godina * 2 - 1)) 
					{
						isp_ozn_p[poc_smjer_stud[i] + count[2 * i]] = podaci[0];
						isp_zav_ozn_p[poc_smjer_stud[i] + count[2 * i]] = podaci[4];
						br_stud_p[poc_smjer_stud[i] + count[2 * i]] = podaci[5];
						count[2 * i] ++;
					}
					else 
					{
						isp_ozn_p[poc_smjer_stud[i] + br_ispit_p[i * 2] + count[2 * i + 1]] = podaci[0];
						isp_zav_ozn_p[poc_smjer_stud[i] + br_ispit_p[i * 2] + count[2 * i + 1]] = podaci[4];
						br_stud_p[poc_smjer_stud[i] + br_ispit_p[i * 2] + count[2 * i + 1]] = podaci[5];
						count[2 * i + 1] ++;
					}
				}
				else
				{
					if(podaci[3] == (ip.godina * 2 - 1)) 
					{
						isp_ozn_p[poc_smjer_stud_1[i] + count[2 * i]] = podaci[0];
						isp_zav_ozn_p[poc_smjer_stud_1[i] + count[2 * i]] = podaci[4];
						br_stud_p[poc_smjer_stud_1[i] + count[2 * i]] = podaci[5];
						count[2 * i] ++;
					}
					
				}
					
					
//popunjavanje isp_ozn_p, isp_zav_ozn_p,br_stud_p s podacima dobivenim iz ulaznih datoteka
				break;
			}
		}

	}//while

	ifile.close();
//_________________________________________________________________________________________	

	

//_________________________________________________________________________________________	


	
	int sirina;

	

	ifile.open(*ime_2);

	presjek_p = new int* [br_smjer]; // polje pokazivaèa na int polja ( matrice )

	for(i = 0; i < br_smjer; i++)
	{
		if(ip.br_rok == 3)
			sirina = (br_ispit_p[i * 2] + br_ispit_p[i * 2 + 1]);
		else
			sirina = br_ispit_p[i * 2];

		presjek_p[i] = new int [sirina * sirina];
		
		for(int j = 0; j < sirina; j++)
			for(int l = j + 1; l < sirina; l++)
			{
				
				ifile.close();
			
				ifile.open(*ime_2);
								
				while(!ifile.eof())
				{
					
					if(EXIT_FAILURE == podatak_3(ifile, string, podaci)) return EXIT_FAILURE;
					
					if(ip.br_rok == 3)
					{
						if(
							(podaci[0] == isp_ozn_p[poc_smjer_stud[i] + j] && podaci[1] == isp_ozn_p[poc_smjer_stud[i] + l])
								|| 
							(podaci[0] == isp_ozn_p[poc_smjer_stud[i] + l] && podaci[1] == isp_ozn_p[poc_smjer_stud[i] + j])
							)
						{
							(presjek_p[i])[j * sirina + l] = podaci[2];
							(presjek_p[i])[l * sirina + j] = podaci[2];
							break;
						}
					}
					else
					{
						if(
							(podaci[0] == isp_ozn_p[poc_smjer_stud_1[i] + j] && podaci[1] == isp_ozn_p[poc_smjer_stud_1[i] + l])
								|| 
							(podaci[0] == isp_ozn_p[poc_smjer_stud_1[i] + l] && podaci[1] == isp_ozn_p[poc_smjer_stud_1[i] + j])
							)
						{
							(presjek_p[i])[j * sirina + l] = podaci[2];
							(presjek_p[i])[l * sirina + j] = podaci[2];
							break;
						}
					}

					
//popunjavanje matrica; svaka matrica ( dvodimenzionalna ) sadrži u redovima i stupcima 
//ispite iz odreðenog semestra a na presjecištu matrice se nalazi broj presjeka studenata tih dvaju ispita

				}//while
			}//for k
	pct.StepIt();
	}
	ifile.close();
	

//_________________________________________________________________________________________	


//_________________________________________________________________________________________	


	ifile.open(*ime_1);

	for(i = 0; i < br_smjer; i++)
	{
	
		if(ip.br_rok == 3)
			sirina = (br_ispit_p[i * 2] + br_ispit_p[i * 2 + 1]);
		else
			sirina = br_ispit_p[i * 2];

		
		for(j = 0; j < sirina; j++)
			{
				
				ifile.close();
			
				ifile.open(*ime_1);
								
				while(!ifile.eof())
				{
					
					if(EXIT_FAILURE == podatak_6(ifile, string, podaci)) return EXIT_FAILURE;
					
					if(ip.br_rok == 3)
					{
						if(podaci[0] == isp_ozn_p[poc_smjer_stud[i] + j])
						{
							(presjek_p[i])[j * sirina + j] = podaci[5];
							break;
						}
						
					
					}
					else
					{
						if(podaci[0] == isp_ozn_p[poc_smjer_stud_1[i] + j])
						{
							(presjek_p[i])[j * sirina + j] = podaci[5];
							break;
						}
					
					}
//popunjavanje prijeopisanih matrica brojem presjeka studenata jednog  predmeta
				}//while
			}//for k
		

	}//for i
	ifile.close();
//_________________________________________________________________________________________	

pct.SetPos(0);

if(br_smjer > 2)
{


	if(ip.br_rok ==3) u_br_isp = ukup_br_isp;
	else u_br_isp = ukup_br_isp_1;

	razl_isp_p = new char [u_br_isp];



	for(i = 0; i < u_br_isp; i++) razl_isp_p[i] = 1;


	for(i = 0; i < u_br_isp - 1; i++)
		if(razl_isp_p[i])
			for(j = i + 1; j < u_br_isp; j++)
				if(isp_ozn_p[i] == isp_ozn_p[j]) razl_isp_p[j] = 0;
	
		
	br_razl_isp = 0;
	for(i = 0; i < u_br_isp; i++)
		if(razl_isp_p[i]) br_razl_isp++;



	razl_isp_ozn_p = new int [br_razl_isp];
	poz = -1;
	for(i = 0; i < u_br_isp; i++)
		if(razl_isp_p[i])
			{ 
				poz++;
				razl_isp_ozn_p[poz] = isp_ozn_p[i];
			}//if
	
	zaj_isp_smj_sem = new char [br_razl_isp * (br_smjer + 1)];
	zaj_isp_smj_poz = new char [br_razl_isp * (br_smjer + 1)];

	for(i = 0; i < br_razl_isp * (br_smjer + 1); i++) 
	{
		zaj_isp_smj_sem[i] = 0;
		zaj_isp_smj_poz[i] = -1;
	}//for i
	
	poz_isp = -1;
	for(i = 0; i < u_br_isp - 1; i++)
	if(razl_isp_p[i])
	{
		poz_isp++;
		poz = smjer(i, ip);
	
		zaj_isp_smj_poz[br_razl_isp * poz + poz_isp] = krom_poz(i, poz, ip);
		zaj_isp_smj_sem[br_razl_isp * poz + poz_isp] = prvi_drugi(i, poz, ip);		
		
		for(j = i + 1; j < u_br_isp; j++)
				if(isp_ozn_p[i] == isp_ozn_p[j])
				{
					poz = smjer(j, ip);
					
					zaj_isp_smj_sem[br_razl_isp * poz + poz_isp] = prvi_drugi(j, poz, ip);
			
					zaj_isp_smj_poz[br_razl_isp * poz + poz_isp] = krom_poz(j, poz, ip);
				
				}//if
	}//if


	for(i = 0; i < br_razl_isp; i++)
	{
		poz = 0;
		for(j = 0; j < br_smjer; j++)
		{
			if(zaj_isp_smj_poz[j * br_razl_isp + i] > -1) poz++;
		}//for j
		zaj_isp_smj_poz[br_razl_isp * br_smjer + i] = poz;
	}//for i
//popunjavanje matrica zaj_isp_smj_poz i zaj_isp_smj_sem ( opisano u diplomskom radu )


}//if god
else
{ 	
	razl_isp_p = NULL;
	zaj_isp_smj_sem = NULL;
	zaj_isp_smj_poz = NULL;

}//else god

return EXIT_SUCCESS;

}//Create

Ispit_Stud_Zavod :: ~Ispit_Stud_Zavod()
{
	
	destrukt();

}//~Ispit_Stud

void Ispit_Stud_Zavod :: destrukt()
{
	int i;

	if(br_stud_p) delete [] br_stud_p;
	if(isp_ozn_p) delete [] isp_ozn_p;
	if(poc_smjer_stud) delete [] poc_smjer_stud;
	if(br_ispit_p) delete [] br_ispit_p;
	if(razl_isp_p) delete [] razl_isp_p;
	if(zaj_isp_smj_sem) delete [] zaj_isp_smj_sem;
	if(zaj_isp_smj_poz) delete [] zaj_isp_smj_poz;
	if(razl_isp_ozn_p) delete [] razl_isp_ozn_p;
	if(poc_smjer_stud_1) delete [] poc_smjer_stud_1;
	if(isp_zav_ozn_p) delete [] isp_zav_ozn_p;
	if(count) delete [] count;

	for(i = 0; i < br_smjer; i++)
		delete [] presjek_p[i];

	if(presjek_p) delete [] presjek_p;

	br_stud_p = NULL;
	isp_ozn_p = NULL;
	poc_smjer_stud = NULL;
	br_ispit_p = NULL;
	razl_isp_p = NULL;
	zaj_isp_smj_sem = NULL;
	zaj_isp_smj_poz = NULL;
	razl_isp_ozn_p = NULL;
	poc_smjer_stud_1 = NULL;
	isp_zav_ozn_p = NULL;
	count = NULL;
	presjek_p = NULL;
	br_smjer = 0;


}//destrukt

//vraæa broj studenata u odreðenom smjeru i semestru
int& Ispit_Stud_Zavod :: operator () (int smj, int sem, int i)
{
	return(br_stud_p[poc_smjer_stud[smj] + br_ispit_p[smj * 2] * sem + i]);
}//operator ()

//vraæa presjek broja studenata dvaju ispita iz istog smjera 
int& Ispit_Stud_Zavod :: operator () (int smj, int sem_1, int i1, int sem_2, int i2)
{
	return ((presjek_p[smj])[(br_ispit_p[smj * 2] * sem_1 + i1) * (br_ispit_p[smj * 2] + br_ispit_p[smj * 2 + 1] * mnoz) + br_ispit_p[smj * 2] * sem_2 + i2]);
}//operator ()

//vraæa oznaku ispita iz odreðenog smjera i semestra
int& Ispit_Stud_Zavod :: sif_isp(int smj, int sem, int i)
{ 
	return(isp_ozn_p[poc_smjer_stud[smj] + br_ispit_p[smj * 2] * sem + i]);
}//operator ()

//vraæa broj kolegija u odreðenom smjeru i odreðenom semestru
int& Ispit_Stud_Zavod :: operator () (int smj, int i)
{
	return (br_ispit_p[smj * 2 + i]);

}//operator ()




