#include "..\h\ispit_rok.h"

Fiks_Ispit :: Fiks_Ispit()
{
	glava = NULL;
	glava = NULL;
	trenutni = NULL;
	predhodni = NULL;
	sljedeci = NULL;
	br_cvor = 0;
}//Fiks_Ispit

void Fiks_Ispit :: destrukt()
{
	int i;

	trenutni = glava;

	for(i = 0; i < br_cvor; i++)
	{
		sljedeci = trenutni -> sljedeci;
		delete trenutni;
		trenutni = sljedeci;
	}//for i
}

Fiks_Ispit :: ~Fiks_Ispit()
{
	destrukt();

}//~Fiks_Ispit


//oduzimanje jednog èvora iz povezane liste
void Fiks_Ispit :: oduzmi_cvor(int sif)
{
	int i;
	int kont;

	kont = 0;
	trenutni = glava;
	predhodni = NULL;

	for(i = 0; i < br_cvor; i++)
	{
		if((trenutni -> sifra) == sif )
		{
			if(!predhodni)
			{
				glava = trenutni -> sljedeci;
				delete trenutni;
				br_cvor --;
				kont = 1;
			}//if
			else
			{
				(predhodni -> sljedeci) = (trenutni -> sljedeci);
				delete trenutni;
				br_cvor --;
				kont = 1;
			}//else
			
		}//if

		
		if(kont) break;
		else
		{
			predhodni = trenutni;
			trenutni = trenutni -> sljedeci;
		}//else

	}//for i

}//oduzmi_cvor

//promjena vrijednosti datuma jednog èvora povezane liste
void Fiks_Ispit :: promjeni_cvor(int sif, int d_r_0, int d_r_1, int d_r_2)
{
	int i;
	int kont;

	kont = 0;
	trenutni = glava;


	for(i = 0; i < br_cvor; i++)
	{
		
		if((trenutni -> sifra) == sif)	
		{

			(trenutni -> datum_rok[0]) = d_r_0;
			(trenutni -> datum_rok[1]) = d_r_1;
			(trenutni -> datum_rok[2]) = d_r_2;
			
			kont = 1;

		}//if
		
		if(kont) break;
		else trenutni = (trenutni -> sljedeci);

	}//for i

}//promjeni_cvor

//postavljanje pokazivaèa na poèetak spojene liste
void Fiks_Ispit :: reset()
{
	trenutni = glava;
	predhodni = glava;
}//reset

// dohvaæanje datuma na èiji èvor gleda pokazivaè trenutni
int& Fiks_Ispit :: datum(int rok)
{
	return (trenutni -> datum_rok[rok]);

}//datum

//funkcija koja se koristi prilikom pregledavanja oznaka ispita koji se nalaze u spojnoj listi
int Fiks_Ispit :: ispit_cvor()
{

	trenutni = predhodni;
	predhodni = (trenutni -> sljedeci);

	return (trenutni -> sifra);

}//ispit_cvor

int Fiks_Ispit :: get_r_d(int rok)
{

	return(trenutni -> datum_rok[rok]);

}//get_r_d_0

//postavljanje parametara èvora spojene liste
void Fiks_Ispit ::set_param(int k_r_0, int k_r_1, int k_r_2)
{

	predhodni = trenutni;
	trenutni = (trenutni -> sljedeci);


	(predhodni -> datum_rok[0]) = k_r_0;
	(predhodni -> datum_rok[1]) = k_r_1;
	(predhodni -> datum_rok[2]) = k_r_2;

}//set_param

//postavljanje parametara èvora spojene liste
void Fiks_Ispit ::set_param(int k_r_0, int k_r_1)
{

	predhodni = trenutni;
	trenutni = (trenutni -> sljedeci);


	(predhodni -> datum_rok[0]) = k_r_0;
	(predhodni -> datum_rok[1]) = k_r_1;

}//set_param

//postavljanje parametara èvora spojene liste
void Fiks_Ispit ::set_param(int k_r_0)
{

	predhodni = trenutni;
	trenutni = (trenutni -> sljedeci);


	(predhodni -> datum_rok[0]) = k_r_0;

}//set_param

//dodavanje novog èvora u spojnu listu
void Fiks_Ispit :: dodaj_cvor(int sif, int d_r_0, int d_r_1, int d_r_2)
{
	
	if(!br_cvor)
	{
		br_cvor ++;
		glava = new cvor;
		(glava -> datum_rok[0]) = d_r_0;
		(glava -> datum_rok[1]) = d_r_1;
		(glava -> datum_rok[2]) = d_r_2;
		
		(glava -> sljedeci) = NULL;
		(glava -> sifra) = sif;
		kraj = glava;
		predhodni_k = glava;

	}
	else
	{
		kraj = new cvor;
		(kraj -> datum_rok[0]) = d_r_0;
		(kraj -> datum_rok[1]) = d_r_1;
		(kraj -> datum_rok[2]) = d_r_2;
		(kraj -> sljedeci) = NULL;
		(kraj -> sifra) = sif;
		(predhodni_k -> sljedeci) = kraj;
		predhodni_k = kraj;
		br_cvor ++;

	}//else
}//dodaj_cvor

