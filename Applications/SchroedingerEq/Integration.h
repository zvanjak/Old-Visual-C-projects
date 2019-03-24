#ifndef	_INTEGRATION_H
#define	_INTEGRATION_H

#define SIGN(a,b) ( (b) >= 0.0 ? fabs(a): -fabs(a) )

static double dMaxArg1, dMaxArg2;
#define DMAX(a,b) (dMaxArg1=(a),dMaxArg2=(b),(dMaxArg1)>(dMaxArg2) ? (dMaxArg1) : (dMaxArg2) )

static double dMinArg1, dMinArg2;
#define DMIN(a,b) (dMinArg1=(a),dMinArg2=(b),(dMinArg1)<(dMinArg2) ? (dMinArg1) : (dMinArg2) )

#define		SAFETY		0.9
#define		PGROW			-0.2
#define		PSHRNK		-0.25
#define		ERRCON		1.89e-4

#define		MAXSTP		10000
#define		TINY			1.e-30

#define		INT_OK								0
#define		STEPSIZE_UNDERFLOW		-1
#define		TO_MANY_STEPS					-2
#define		NO_ALG_SOLUTION				-3

void rkck( float y[], float dydx[], int n, float x, float h, float yout[],
		   float yerr[], void (*derivs)(float, float[], float[]) );

int rkqs( float y[], float dydx[], int n, float *x, float htry, 
					 float eps, float yscal[], float *hdid, float *hnext,
					 void (*derivs)(float, float[], float[]) );

int odeint( float ystart[], int nvar, float x1, float x2, 
						float eps, float h1, float hmin, int *nok, int *nbad,
						void (*derivs)(float, float[], float[]),
	 
						int rkqs( float y[], float dydx[], int n, float *x, float htry, 
											float eps, float yscal[], float *hdid, float *hnext,
											void (*derivs)(float, float[], float[]) ),
	 
						int kmax, int *kount, float *xp, float **yp, float dxsav);


class	DerivsCalcObject {
public:
	virtual void	derivs(float, float[], float[]) = 0;
};

class DiffSys {
public:
	void rkck( float y[], float dydx[], int n, float x, float h, float yout[], float yerr[], 
						 DerivsCalcObject &derivs );

	int RKStepper( float y[], float dydx[], int n, float *x, float htry, 
						 float eps, float yscal[], float *hdid, float *hnext,
						 DerivsCalcObject &derivs);

	int odeint( float ystart[], int nvar, float x1, float x2, 
							float eps, float h1, float hmin, int *nok, int *nbad,
							int kmax, int *kount, float *xp, float **yp, float dxsav,
							DerivsCalcObject &derivs);
};

#endif