#ifndef GEN_ALG_H
#define GEN_ALG_H

#define VEL_POP		70

#define ITER_NUM		20000
#define	BR_ISPITA		10
#define BR_ROKOVA		3
#define BR_TERMINA	30

class Gen {
public:
	long	Cromosom[BR_ISPITA];
	int		TerminiIspita[BR_ISPITA][BR_ROKOVA+1];
};

void	GenerateInitialPopulation( Gen Pop[] );
Gen		GenerateGene( int SelectedBitsNum, int Range );
void	SelectRandomNumbers( int a[], int num, int start, int end );
double	Func( Gen a );
Gen		Krizaj( Gen a, Gen b );
void	Mutiraj( Gen Pop[] );

long	SetBit( long a, int n );
long	ClearBit( long a, int n );
bool	IsBitSet( long a, int n );
int		NumberOfBits( long a );
bool	InSet( int a[], int num, int br );

void	PrintPopulation( Gen	Pop[] );
void	PrintConfig( Gen	Pop[] );

#endif // GEN_ALG_H