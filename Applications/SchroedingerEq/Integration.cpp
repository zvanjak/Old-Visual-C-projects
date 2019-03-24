#include "stdafx.h"

#include "Integration.h"

/****************************************************************/
//							Simple ODE integration
/****************************************************************/

int rkqs( float y[], float dydx[], int n, float *x, float htry, 
					 float eps, float yscal[], float *hdid, float *hnext,
					 void (*derivs)(float, float[], float[]) )
/*	RK 5-og reda sa pracenjem lokalne greske zaokruzivanja da bi se osigurala tocnost i 
	prilagodila duljina koraka.
	ULAZ:
		vektor zavisnih varijabli  -  y[1..n]
		i njegove derivacije   -  dydx[1..n],   i to u pocetnoj tocki nezavisne varijable x
		duljina koraka(pocetna za probu)  -  htry
		zahtijevana tocnost	 -  eps
		i vektor sa kojim se skalira greska  -  yscal[1..n]
	IZLAZ:
		y i x -  zamijenjeni sa novim vrijednostima
		hdid  -  postignuta duljina koraka
		hnext -  predvidjena duljina koraka u slijedecem koraku

	(*derivs) - korisnicka rutina koja racuna derivacije (desne strane sistema jednadzbi)
	
	Primjer za derivs:

	dy1/dx = f1(x,y1,y2)
	dy2/dx = f2(x,y1,y2)

	void System(float x, float *y, float *dxdy )
	{
		dxdy[0] = f1(x, y[0], y[1] );
		dxdy[1] = f2(x, y[0], y[1] );
	}
*/
{
	int			i;
	float	errmax, h, htemp, xnew;
	float	*yerr, *ytemp;

	yerr = new float[n];
	ytemp = new float[n];
	h = htry;

	for(;;)
	{
		rkck(y,dydx,n,*x,h,ytemp,yerr,derivs);
		errmax = 0.0;
		for( i=0; i<n; i++ )
			errmax = DMAX(errmax, fabs(yerr[i]/yscal[i]));
		errmax /= eps;

		if( errmax <= 1.0 )
			break;

		htemp = SAFETY * h * pow(errmax,PSHRNK);
		h = (h >= 0.0 ? DMAX(htemp, 0.1*h) : DMIN(htemp, 0.1*h));

		xnew = (*x) + h;
		if( xnew == *x )
		{
			fprintf(stderr, "\n stepsize underflow in rkqs!!!");

			return STEPSIZE_UNDERFLOW;
		}
	}
	if( errmax > ERRCON )
		*hnext = SAFETY * h * pow(errmax, PGROW);
	else
		*hnext = 5.0 * h;

	*x += (*hdid=h);
	for( i=0; i<n; i++ )
		y[i] = ytemp[i];
	
	delete [] ytemp;
	delete []yerr;

	return INT_OK;
}

//	Algoritam rutina na RK-metodu
//	implementira osnovnu formulu metodu i pocinjuci od zavisnih varijabli y[i] u x
//	racuna y u x+h
void rkck( float y[], float dydx[], int n, float x, float h, float yout[],
		   float yerr[], void (*derivs)(float, float[], float[]) )
/*
	Dobivsi vrijednosti za n varijabli y[1..n] i njihovih derivacija 
	dydx[1..n] poznatih u x, koristi cash-Karpovu RK metodu da napreduje 
	s rijesenjem preko intervala h i vraca varijable u yout[1..n]
	Takodjer vraca lokalnu gresku zaokruzivanja u yerr
*/
{
	int		i;
	static float a2=0.2, a3=0.3, a4=0.6, a5=1, a6=0.875, 
		b21=0.2, b31=3.0/40.0, b32=9.0/40.0, b41=0.3, b42=-0.9, b43=1.2,
		b51=-11.0/54.0, b52=2.5, b53=-70.0/27.0, b54=35.0/27.0,
		b61=1631.0/55296.0, b62=175.0/512.0, b63=575.0/13824.0,
		b64=44275.0/110592.0, b65=253.0/4096.0, 
		c1=37.0/378.0, c3=250.0/621.0, c4=125.0/594.0, c6=512.0/1771.0,
		dc5=-277.00/14336.0;
	float	dc1=c1-2825.0/27648.0, dc3=c3-18575.0/48384.0,
		dc4=c4-13525.0/55296.0, dc6=c6-0.25;

	float	*ak2, *ak3, *ak4, *ak5, *ak6, *ytemp;
	
	ak2 = new float[n];
	ak3 = new float[n];
	ak4 = new float[n];
	ak5 = new float[n];
	ak6 = new float[n];
	ytemp = new float[n];

	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + b21*h*dydx[i];

	(*derivs)(x+a2*h, ytemp, ak2);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b31*dydx[i] + b32*ak2[i]);

	(*derivs)(x+a3*h, ytemp, ak3);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b41*dydx[i] + b42*ak2[i] + b43*ak3[i]);

	(*derivs)(x+a4*h, ytemp, ak4);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b51*dydx[i] + b52*ak2[i] + b53*ak3[i] + b54*ak4[i]);

	(*derivs)(x+a5*h, ytemp, ak5);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b61*dydx[i] + b62*ak2[i] + b63*ak3[i] + b64*ak4[i] + b65*ak5[i]);

	(*derivs)(x+a6*h, ytemp, ak6);
	for( i=0; i<n; i++ )
		yout[i] = y[i] + h*(c1*dydx[i] + c3*ak3[i] + c4*ak4[i] + c6*ak6[i]);

	for( i=0; i<n; i++ )
		yerr[i] = h*(dc1*dydx[i] + dc3*ak3[i] + dc4*ak4[i] + dc5*ak5[i] + dc6*ak6[i]);

	delete []ak2;
	delete []ak3;
	delete []ak4;
	delete []ak5;
	delete []ak6;
	delete []ytemp;
}

int odeint( float ystart[], int nvar, float x1, float x2, 
						float eps, float h1, float hmin, int *nok, int *nbad,
						void (*derivs)(float, float[], float[]),
	 
						int rkqs( float y[], float dydx[], int n, float *x, float htry, 
											float eps, float yscal[], float *hdid, float *hnext,
											void (*derivs)(float, float[], float[]) ),
	 
						int kmax, int *kount, float *xp, float **yp, float dxsav)
//	ystart[] - vektor poèetnih vrijednosti
//  nvar  - koliko ima dif. jednadžbi
//  nok, nbad - broj dobrih i loših poduzetih koraka
//  h1 - poèetna duljina koraka
//  hmin - minimalna dozvoljena duljina koraka ( može biti 0 )
//  derivs - korisnikova rutina koja raèuna derivacije u danoj toèki
//  rkqs - stepper rutina
//  kmax - koliko maksimalno izraèunatih vrijednosti y da se zapatmi
//  dxsav - razmak izmeðu dvije vrijednosti koje su zapamæene
//		POVRATNE VRIJEDNOSTI
//  xp[1..kmax] - u kojim toèkama su izraèunate vrijednosti y
//  yp[1..nvar][1..kmax] - vrijednosti varijabli
{
	int		nstp, i;
	float	xsav, x, hnext, hdid, h;
	float	*yscal, *y, *dydx;

	yscal = new float[nvar];
	y = new float[nvar];
	dydx = new float[nvar];
	
	x=x1;
	h = SIGN(h1, x2-x1);
	*nok = (*nbad) = *kount = 0;
	for( i=0; i<nvar; i++ )
		y[i] = ystart[i];
	if( kmax > 0 ) xsav = x - dxsav*2.0;

	for( nstp=1; nstp<=MAXSTP; nstp++ )
	{
		(*derivs)(x,y,dydx);
		for( i=0; i<nvar; i++ )
		{
			yscal[i] = fabs(y[i]) + fabs(dydx[i]*h) + TINY;
			if( yscal[i] < 1 )
				yscal[i] = 1;
		}

		if( kmax > 0 && *kount < kmax-1 && fabs(x-xsav) > fabs(dxsav) )
		{
			xp[(*kount)] = x;
			for( i=0; i<nvar; i++ )
				yp[i][*kount] = y[i];
			(*kount)++;
			xsav = x;
		}
		if( (x+h-x2)*(x+h-x1) > 0.0 ) 
			h=x2 - x;

		(*rkqs)(y,dydx,nvar,&x,h,eps,yscal,&hdid,&hnext,derivs);
		if( hdid == h)
			++(*nok);
		else
			++(*nbad);

		if( (x-x2)*(x2-x1) >= 0.0 )
		{
			for( i=0; i<nvar; i++ )
				ystart[i] = y[i];
			if( kmax )
			{
				xp[(*kount)++] = x;
				for( i=0; i<nvar; i++ )
					yp[i][*kount] = y[i];
			}

			delete [] dydx;
			delete []y;
			delete []yscal;
			return INT_OK;
		}
		if( fabs(hnext) <= hmin )
		{
//			fprintf(stdout, "\n Step size too small in odeint!!!");
//			printf("\n trenutni x = %12.8f", x );

			return STEPSIZE_UNDERFLOW;
		}
		h = hnext;
	}
//	fprintf(stdout, "\nToo many steps in odeint!!!");
//	printf("\n trenutni x = %12.8f", x );

	delete [] dydx;
	delete []y;
	delete []yscal;
	
	return TO_MANY_STEPS;
}

#include "stdafx.h"

#include "Integration.h"

/****************************************************************/
/****************************************************************/
//							DiffSys
/****************************************************************/
/****************************************************************/

int DiffSys::RKStepper( float y[], float dydx[], int n, float *x, float htry, 
					 float eps, float yscal[], float *hdid, float *hnext, DerivsCalcObject &derivs  )
/*	RK 5-og reda sa pracenjem lokalne greske zaokruzivanja da bi se osigurala tocnost i 
	prilagodila duljina koraka.
	ULAZ:
		vektor zavisnih varijabli  -  y[1..n]
		i njegove derivacije   -  dydx[1..n],   i to u pocetnoj tocki nezavisne varijable x
		duljina koraka(pocetna za probu)  -  htry
		zahtijevana tocnost	 -  eps
		i vektor sa kojim se skalira greska  -  yscal[1..n]
	IZLAZ:
		y i x -  zamijenjeni sa novim vrijednostima
		hdid  -  postignuta duljina koraka
		hnext -  predvidjena duljina koraka u slijedecem koraku

	(*derivs) - korisnicka rutina koja racuna derivacije (desne strane sistema jednadzbi)
	
	Primjer za derivs:

	dy1/dx = f1(x,y1,y2)
	dy2/dx = f2(x,y1,y2)

	void System(float x, float *y, float *dxdy )
	{
		dxdy[0] = f1(x, y[0], y[1] );
		dxdy[1] = f2(x, y[0], y[1] );
	}
*/
{
	int			i;
	float	errmax, h, htemp, xnew;
	float	*yerr, *ytemp;

	yerr = new float[n];
	ytemp = new float[n];
	h = htry;

	for(;;)
	{
		rkck(y,dydx,n,*x,h,ytemp,yerr, derivs);
		errmax = 0.0;
		for( i=0; i<n; i++ )
			errmax = DMAX(errmax, fabs(yerr[i]/yscal[i]));
		errmax /= eps;

		if( errmax <= 1.0 )
			break;

		htemp = SAFETY * h * pow(errmax,PSHRNK);
		h = (h >= 0.0 ? DMAX(htemp, 0.1*h) : DMIN(htemp, 0.1*h));

		xnew = (*x) + h;
		if( xnew == *x )
		{
			fprintf(stderr, "\n stepsize underflow in rkqs!!!");

			return STEPSIZE_UNDERFLOW;
		}
	}
	if( errmax > ERRCON )
		*hnext = SAFETY * h * pow(errmax, PGROW);
	else
		*hnext = 5.0 * h;

	*x += (*hdid=h);
	for( i=0; i<n; i++ )
		y[i] = ytemp[i];
	
	delete [] ytemp;
	delete []yerr;

	return INT_OK;
}

//	Algoritam rutina na RK-metodu
//	implementira osnovnu formulu metodu i pocinjuci od zavisnih varijabli y[i] u x
//	racuna y u x+h
void DiffSys::rkck( float y[], float dydx[], int n, float x, float h, float yout[], 
									 float yerr[], DerivsCalcObject &derivs  )
/*
	Dobivsi vrijednosti za n varijabli y[1..n] i njihovih derivacija 
	dydx[1..n] poznatih u x, koristi cash-Karpovu RK metodu da napreduje 
	s rijesenjem preko intervala h i vraca varijable u yout[1..n]
	Takodjer vraca lokalnu gresku zaokruzivanja u yerr
*/
{
	int		i;
	static float a2=0.2, a3=0.3, a4=0.6, a5=1, a6=0.875, 
		b21=0.2, b31=3.0/40.0, b32=9.0/40.0, b41=0.3, b42=-0.9, b43=1.2,
		b51=-11.0/54.0, b52=2.5, b53=-70.0/27.0, b54=35.0/27.0,
		b61=1631.0/55296.0, b62=175.0/512.0, b63=575.0/13824.0,
		b64=44275.0/110592.0, b65=253.0/4096.0, 
		c1=37.0/378.0, c3=250.0/621.0, c4=125.0/594.0, c6=512.0/1771.0,
		dc5=-277.00/14336.0;
	float	dc1=c1-2825.0/27648.0, dc3=c3-18575.0/48384.0,
		dc4=c4-13525.0/55296.0, dc6=c6-0.25;

	float	*ak2, *ak3, *ak4, *ak5, *ak6, *ytemp;
	
	ak2 = new float[n];
	ak3 = new float[n];
	ak4 = new float[n];
	ak5 = new float[n];
	ak6 = new float[n];
	ytemp = new float[n];

	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + b21*h*dydx[i];

	derivs.derivs(x+a2*h, ytemp, ak2);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b31*dydx[i] + b32*ak2[i]);

	derivs.derivs(x+a3*h, ytemp, ak3);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b41*dydx[i] + b42*ak2[i] + b43*ak3[i]);

	derivs.derivs(x+a4*h, ytemp, ak4);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b51*dydx[i] + b52*ak2[i] + b53*ak3[i] + b54*ak4[i]);

	derivs.derivs(x+a5*h, ytemp, ak5);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b61*dydx[i] + b62*ak2[i] + b63*ak3[i] + b64*ak4[i] + b65*ak5[i]);

	derivs.derivs(x+a6*h, ytemp, ak6);
	for( i=0; i<n; i++ )
		yout[i] = y[i] + h*(c1*dydx[i] + c3*ak3[i] + c4*ak4[i] + c6*ak6[i]);

	for( i=0; i<n; i++ )
		yerr[i] = h*(dc1*dydx[i] + dc3*ak3[i] + dc4*ak4[i] + dc5*ak5[i] + dc6*ak6[i]);

	delete []ak2;
	delete []ak3;
	delete []ak4;
	delete []ak5;
	delete []ak6;
	delete []ytemp;
}

int DiffSys::odeint( float ystart[], int nvar, float x1, float x2, 
						float eps, float h1, float hmin, int *nok, int *nbad,
						int kmax, int *kount, float *xp, float **yp, float dxsav,
						DerivsCalcObject &derivs )
//	ystart[] - vektor poèetnih vrijednosti
//  nvar  - koliko ima dif. jednadžbi
//  nok, nbad - broj dobrih i loših poduzetih koraka
//  h1 - poèetna duljina koraka
//  hmin - minimalna dozvoljena duljina koraka ( može biti 0 )
//  derivs - korisnikova rutina koja raèuna derivacije u danoj toèki
//  rkqs - stepper rutina
//  kmax - koliko maksimalno izraèunatih vrijednosti y da se zapatmi
//  dxsav - razmak izmeðu dvije vrijednosti koje su zapamæene
//		POVRATNE VRIJEDNOSTI
//  xp[1..kmax] - u kojim toèkama su izraèunate vrijednosti y
//  yp[1..nvar][1..kmax] - vrijednosti varijabli
{
	int		nstp, i;
	float	xsav, x, hnext, hdid, h;
	float	*yscal, *y, *dydx;

	yscal = new float[nvar];
	y = new float[nvar];
	dydx = new float[nvar];
	
	x=x1;
	h = SIGN(h1, x2-x1);
	*nok = (*nbad) = *kount = 0;
	for( i=0; i<nvar; i++ )
		y[i] = ystart[i];
	if( kmax > 0 ) xsav = x - dxsav*2.0;

	for( nstp=1; nstp<=MAXSTP; nstp++ )
	{
		derivs.derivs(x,y,dydx);
		for( i=0; i<nvar; i++ )
		{
			yscal[i] = fabs(y[i]) + fabs(dydx[i]*h) + TINY;
			if( yscal[i] < 1 )
				yscal[i] = 1;
		}

		if( kmax > 0 && *kount < kmax-1 && fabs(x-xsav) > fabs(dxsav) )
		{
			xp[(*kount)] = x;
			for( i=0; i<nvar; i++ )
				yp[i][*kount] = y[i];
			(*kount)++;
			xsav = x;
		}
		if( (x+h-x2)*(x+h-x1) > 0.0 ) 
			h=x2 - x;

		RKStepper(y,dydx,nvar,&x,h,eps,yscal,&hdid,&hnext, derivs);
		if( hdid == h)
			++(*nok);
		else
			++(*nbad);

		if( (x-x2)*(x2-x1) >= 0.0 )
		{
			for( i=0; i<nvar; i++ )
				ystart[i] = y[i];
			if( kmax )
			{
				xp[(*kount)++] = x;
				for( i=0; i<nvar; i++ )
					yp[i][*kount] = y[i];
			}

			delete [] dydx;
			delete []y;
			delete []yscal;
			return INT_OK;
		}
		if( fabs(hnext) <= hmin )
		{
//			fprintf(stdout, "\n Step size too small in odeint!!!");
//			printf("\n trenutni x = %12.8f", x );

			return STEPSIZE_UNDERFLOW;
		}
		h = hnext;
	}
//	fprintf(stdout, "\nToo many steps in odeint!!!");
//	printf("\n trenutni x = %12.8f", x );

	delete [] dydx;
	delete []y;
	delete []yscal;
	
	return TO_MANY_STEPS;
}