#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "matrix.h"
#include <vector>
#include "GeneticAlg.h"

int CmpQAP( const void *a, const void *b );

class	QAPResults {
public:
	float	FuncVal;
	long	IterNum;
};

/*****************************************************************************************/
/*****************************************************************************************/
// Quadratic Assignement Problem
//	opæenita klasa koja rasporeðuje 'n' razlièitih vrsta kuglica, od kojih svake ima 'l'
//  komada, u 'm' razlièitih slotova
//		n - broj tipova kuglica
//		l - broj kuglica svakog tipa ( da li omoguæiti da to bude l[i], i=1..n ??? )
//		m - broj slotova u koji treba razmjestiti kuglice

class QAP {
public:
	// funkcije iz zadanih podataka ( matrica A,Z,O,R ) raèunaju matrice A,B,C standardnog QAP-a
	bool		CalculateA();
	bool		CalculateB();
	bool		CalculateC();

protected:
	Matrix<float>		**A;		// matrica udaljenosti meðu pojedinim slotovima
	Matrix<float>		**Z;		// matrica želja profesora
	Matrix<float>		**O;		// 
	Matrix<float>		**R;
};

/*****************************************************************************************/
/*****************************************************************************************/
// Simple Quadratic Assignement Problem
//	klasa koja opisuje problem kod kojeg 'n' kuglica treba rasporediti u 'n' slotova
class	QAPSimple {
public:
	QAPSimple(int inFacilityNum);

	int		N() { return FacilityNum; }

	virtual void	Optimize() = 0;
	float					OptFunc(std::vector<int> &Sol);

	void	SetMatrices( const Matrix<float> &a, const Matrix<float> &b, const Matrix<float> &c );
	void	SetA( const Matrix<float> &a );
	void	SetB( const Matrix<float> &b );
	void	SetC( const Matrix<float> &c );

protected:
	int		FacilityNum;

	Matrix<float>		A;		// matrica toka izmeðu kuglice 'i' i kuglice 'j'
	Matrix<float>		B;		// matrica udaljenosti meðu pojedinim slotovima
	Matrix<float>		C;		// trošak stavljanja kuglice 'i' na mjesto 'j'
};

/*****************************************************************************************/
/*****************************************************************************************/
//

class QAPCrom : public Cromosom {
public:
	QAPCrom();
	QAPCrom(int inFacNum);

	int		GenerateCromosom();
	void	Print();

	int		N() { return FacilityNum; }
	void	SetFacilityNum( int N );

	int&	operator[]( int i );		// vraæa se po referenci -> može biti l-value

private:
	int	 FacilityNum;
	std::vector<int>	Sol;  // Sol[i] = slot u koji se stavlja i-ta kuglica

	// radi QAPSimpleGenetic::OptFunc() koja treba pristupiti Sol[i]
	friend	class QAPSimpleGenetic;	
};

/*****************************************************************************************/

class QAPSimpleGenetic : public QAPSimple, public GenAlgTournamentSelection<QAPCrom> {
public:
	QAPSimpleGenetic( int inFacNum, int inPopSize, int inIterNum, float inMutProb );

	void		PerformMutation();

	void		Optimize();
	float		OptFunc( QAPCrom &a ) { return QAPSimple::OptFunc(a.Sol); }
};

/*****************************************************************************************/
/*****************************************************************************************/
// Schedule Quadratic Assignement Problem
//	klasa koja opisuje problem kod kojeg 'N' kuglica ( od kojih svake ima 'L' komada )
//	treba rasporediti u 'M' slotova
//			N - ItemNum
//			M - SlotNum
//			L - ItemMultiplicity

class QAPSchedule {
public:
	QAPSchedule(int inItemNum, int inItemMulNum, int inSlotNum);
	~QAPSchedule() { A.~Matrix(); B.~Matrix(); C.~Matrix(); }

	virtual QAPResults	Optimize() = 0;
	
	float		OptFunc(Matrix<int> &Sol);

	int		N() { return ItemNum; }
	int		M() { return SlotNum; }
	int		L() { return ItemMultiplicity; }

	void	SetMatrices( const Matrix<float> &a, const Matrix<float> &b, const Matrix<float> &c );
	void	SetA( const Matrix<float> &a );
	void	SetB( const Matrix<float> &b );
	void	SetC( const Matrix<float> &c );

protected:
	int		ItemNum;
	int		ItemMultiplicity;
	int		SlotNum;

	Matrix<float>		A;
	Matrix<float>		B;
	Matrix<float>		C;
};

/*****************************************************************************************/

class QAPScheduleCrom : public Cromosom {
public:
	QAPScheduleCrom();
	QAPScheduleCrom(int inItemNum, int inItemMulNum, int inSlotNum);
	~QAPScheduleCrom();

	int		GenerateCromosom();
	void	Print();

	int		N() { return ItemNum; }
	int		M() { return SlotNum; }
	int		L() { return ItemMultiplicity; }

	bool	SetParameters(int inItemNum, int inItemMulNum, int inSlotNum);

	bool	SetItemNum( int inItemNum );
	bool	SetItemMulNum( int inItemMulNum );
	bool	SetSlotNum( int inSlotNum );

	int*	operator[]( int i );		// vraæa se po referenci -> može biti l-value
	QAPScheduleCrom&	operator=( QAPScheduleCrom &b );

private:
	int		ItemNum;
	int		ItemMultiplicity;
	int		SlotNum;
	
	Matrix<int>	Sol;  // Sol[i][j] = slot u koji se stavlja i-ti Item, j-tog podroka

	// radi QAPSimpleGenetic::OptFunc() koja treba pristupiti Sol[i]
	friend	class QAPScheduleGenetic;	
};

/*****************************************************************************************/

typedef void(*PFCB_RETRIEVE)(OptResults *res);

class HasRefreshData {
public:
	virtual	void RefreshData( OptResults *res ) = 0;
};

class QAPScheduleGenetic : public QAPSchedule, public GenAlgTournamentSelection<QAPScheduleCrom> {
public:
	QAPScheduleGenetic(int inItemNum, int inItemMulNum, int inSlotNum, int inPopSize, int inIterNum, float inMutProb );
	~QAPScheduleGenetic();

	void				PerformMutation();
	float				OptFunc( QAPScheduleCrom &a ) { return QAPSchedule::OptFunc(a.Sol); }

	QAPResults	Optimize();

	void		SetCallBackRetrieveResults( PFCB_RETRIEVE	f ) { pfCallBackRetrieve = f; }
	void		SetCallBackObj ( HasRefreshData *obj ) { pObj = obj; }

	void		SetCallBackPeriod( long inPeriod );

private:
	PFCB_RETRIEVE			pfCallBackRetrieve;
	HasRefreshData		*pObj;
	
	long		CallBackPeriod;
	
	bool		bTerminateItself;				// ukoliko se izvršava u svojoj niti, da zna kad treba završiti
	bool		bTerminationPerformed;	// istina kad je zaustavljanje optimizacije obavljeno
};
