#ifndef __QAPNEW_H
#define	__QAPNEW_H

#include "GeneticAlgNew.h"
#include "Matrix.h"
#include "Optimization.h"
#include "Win32Serialize.h"

#include <windows.h>
#include <winbase.h>

#include <vector>
using std::vector;

/***************************************************************************************/
/***************************************************************************************/

class	QAPSolution {
public:
	QAPSolution() : Size(0), Value(0) {}
	QAPSolution( int N ) : Size(N), Value(0), Sol(N,0) {}
	QAPSolution( const QAPSolution &copy ) { Size = copy.Size; Value = copy.Value; Sol = copy.Sol; }

	void		GenerateRandom();
	void		resize( int NewSize ) { Sol.resize(NewSize); Size=NewSize; }
	
	void				operator=( const QAPSolution &b ) { Size=b.Size; Value=b.Value; Sol=b.Sol; }
	int&				operator[](int i) { return Sol[i]; }
	const int&	operator()(int i) const { return Sol[i]; }

	float	getValue() const { return Value; }
	void	setValue( float inValue ) { Value = inValue; }

	int		getSize() const { return Size; }

private:
	int						Size;
	float					Value;
	vector<int>		Sol;

#ifdef __AFX_H__
public:
	friend	void operator<<( CArchive &ar, QAPSolution &data ) {
		ar << data.Size;
		ar << data.Value;
		SerializeInArchive(ar, data.Sol);
	}

	friend	void operator>>( CArchive &ar, QAPSolution &data ) {
		ar >> data.Size;
		ar >> data.Value;
		SerializeInArchive(ar, data.Sol);
	}

	void	Serialize( CArchive &ar ) {
		if( ar.IsStoring() ) {
			ar << this->Size;
			ar << this->Value;
			SerializeInArchive(ar, this->Sol);
//			ar << *this;
		}
		else {
			ar >> this->Size;
			ar >> this->Value;
			SerializeInArchive(ar, this->Sol);
//			ar >> *this;
		}
	}
#endif
};


/***************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////

class HasRefreshFunction {
public:
	virtual	void Refresh( IterativeOptRes<float, QAPSolution> *res, float Best, const QAPSolution *BestSol ) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//	Apstraktni razred koji definira suèelje za QAP problem 

class IQAPSolver {
public:
	//////////////////////////////////////////////////////////////////////////////////////
	// konstruktor
	IQAPSolver( int inFacilityNum );

	int			getFacilityNum() { return nFacilityNum; }
// TODO  -->	void		setFacilityNum( int N ) { nFacilityNum = N; }		// potrebno je odna i realocirati matrice ...

	//////////////////////////////////////////////////////////////////////////////////////
	// Funkcije za rad s funkcijom cilja, za optimizaciju
	//		raèuna vrijednost funkcije cilja za dano rješenje ( virtual zato što se oèekuje 
	//						da bi posebne vrste QAP-a - symmetric, sparse, mogle redefinirati ponašanje )
	virtual	float	OptFunc( QAPSolution &Sol ) = 0;
	//		ovu funkciju æe definirati izvedene klase, ovisno o naèinu optimizacije
	virtual	int		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res ) = 0;
	//		raèuna promjenu u funkciji cilja prilikom zamjene pozicija dviju jedinki
	virtual	float	CalcExchangeValue( int i, int j, const QAPSolution &Sol ) = 0;
	
	//////////////////////////////////////////////////////////////////////////////////////
	// Funkcije kojima izvedeni razred mora dati implementaciju jer se funkcija 
	// PerformRefreshing() oslanja na njih
	//		- sve funkcije mogu vratiti FALSE, ukoliko izvedeni razred ne podržava koncept
//	virtual	bool	IsLastIteration() = 0;
	virtual bool	IsTimeToRefresh(_TypeValue CurrValue) = 0;

	//////////////////////////////////////////////////////////////////////////////////////
	// Funkcije za handlanje refreshinga
	// ovaj funkcija je virtual zato što æe joj Threadable razredi dati drugo znaèenje
	virtual	void		PerformRefreshing( IterativeOptRes<float, QAPSolution> &res, float Best, const QAPSolution *BestSol  );

	void		SetRefreshCallBack( HasRefreshFunction *obj ) { pRefreshObj = obj; }
	void		SetRefreshCallBackPeriod( long inPeriod ) { RefreshCallBackPeriod = inPeriod; }
	
	void		SetSaveResultsPeriod( long inPeriod ) { SaveResultsPeriod = inPeriod; }
	long		GetSaveResultsPeriod() { return SaveResultsPeriod; }

protected:
	int			nFacilityNum;

	bool		bIsMatrixSymetric;				// istina ukoliko su matrice A i B simetriène
	
	long		RefreshCallBackPeriod;		// svakih koliko iteracija se poziva Refresh()
	long		SaveResultsPeriod;				// svakih koliko iteracija se spremaju dobiveni rezultati

	// pokazivaè na objekt koji u sebi ima funkciju Refresh() koja æe se periodièki 
	// pozivati sa rezultatima optimizacije
	HasRefreshFunction	*pRefreshObj;	
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

class QAPSolver : public IQAPSolver {
public:
	//////////////////////////////////////////////////////////////////////////////////////
	// konstruktor
	QAPSolver( int inFacilityNum );

	float		OptFunc( QAPSolution &Sol );
	float		CalcExchangeValue( int i, int j, const QAPSolution &Sol );
	
	//		ovu funkciju æe definirati izvedene klase, ovisno o naèinu optimizacije
	virtual	int		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res ) = 0;

	virtual bool	IsTimeToRefresh(_TypeValue CurrValue) = 0;

	//////////////////////////////////////////////////////////////////////////////////////
	// Osnovni get i set accessori
	void		setA( Matrix<float> &a );
	void		setB( Matrix<float> &a );
	void		setC( Matrix<float> &a );

protected:
	Matrix<float>		A;
	Matrix<float>		B;
	Matrix<float>		C;
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/*
class ISymmetricQAPSolver : public IQAPSolver {
protected:
	SymmetricMatrix<float>		A;
	SymmetricMatrix<float>		B;
	SymmetricMatrix<float>		C;
};
*/

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
/*
class ISparseQAPSolver : public IQAPSolver {
protected:
	SparseMatrix<float>		A;
	SparseMatrix<float>		B;
	SparseMatrix<float>		C;
};
*/

/*****************************************************************************************/
/*****************************************************************************************/

class QAPCrom : public ICromosom {
public:
	QAPCrom();
	QAPCrom(int inFacNum);

	int		GenerateCromosom();
	void	Print();
	void	PrintHorizontal();

	int		getFacilityNum() { return nFacilityNum; }
	void	setFacilityNum( int N );

	QAPSolution&	getSolution() { return Sol; }

	int&	operator[]( int i );		// vraæa se po referenci -> može biti l-value

private:
	int	 nFacilityNum;
	QAPSolution		Sol;  // Sol[i] = slot u koji se stavlja i-ta kuglica
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

class GeneticQAPSolver :	public QAPSolver, 
													public GenAlgTournamentSelection<QAPCrom> {
public:
	GeneticQAPSolver( int inFacNum, int inPopSize, IOptTerminator *pTerm, float inMutProb );
	GeneticQAPSolver( int inFacNum, int inPopSize, long inIterNum, float inMutProb );

	void	PerformMutation();
	
	float	OptFunc( QAPCrom &crom) { return QAPSolver::OptFunc(crom.getSolution()); }
	int		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res );

	bool	IsTimeToRefresh(_TypeValue CurrValue) { return (RefreshCallBackPeriod != 0 ? (CurrIterNum % RefreshCallBackPeriod)==0 : false); }
};

/***************************************************************************************/

class SimAnnealingQAPSolver : public QAPSolver {
public:
	SimAnnealingQAPSolver(int			inFacNum, 
												int			inIterNum = 10000,
												double	inAcceptHigherProb=0.99,
												double	inTempChangeFactor = 0.99,
												int			inPermNum = 100 );

	SimAnnealingQAPSolver(int							inFacNum,
												IOptTerminator	*inpTerm,
												double					inAcceptHigherProb=0.99,
												double					inTempChangeFactor = 0.99,
												int							inPermNum = 100);

	double	CalcRandomChangeConfig( const QAPSolution &Sol );
	double	ChangeConfig( QAPSolution &Sol, int *ind1, int *ind2 );
	double	AverageEnergyInc( QAPSolution &Sol );

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res );

	bool		IsTimeToRefresh(_TypeValue CurrValue) { return (RefreshCallBackPeriod != 0 ? (CurrIterNum % RefreshCallBackPeriod)==0 : false); }

	bool		setOptTerminatorObject( IOptTerminator *pNew ) 
					{
						if( pNew == NULL )
							return false;
						else {
							if( pTermObj != NULL ) {			// najprije treba izbrisati starog
								pNew->CopyState(pTermObj);	// iskopiraj stanje u novi
								delete pTermObj;
							}
							
							pTermObj = pNew;
							return true;
						}
					}

	void		SetAcceptHigherProb(double in) { AcceptHigherProb = in; }
	void		SetTempChangeFactor(double in) { TempChangeFactor = in; }
	void		SetPermNum( int in) { PermNum = in; }

	double	GetAcceptHigherProb() { return AcceptHigherProb; }
	double	GetTempChangeFactor() { return TempChangeFactor; }
	int			GetPermNum() { return PermNum; }
	
protected:
	IOptTerminator	*pTermObj;

	long						CurrIterNum;

	double					AcceptHigherProb;
	double					TempChangeFactor;
	int							PermNum;
};

/*****************************************************************************************/

class IIsTabuMoveQAP {
public:
	virtual	bool	IsTabuMove( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize ) = 0;
	virtual	void	SetInitialAssignment( const QAPSolution	&Sol ) = 0;
	virtual	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize ) = 0;		// moraju znati kada se u algoritmu napravi neki potez
};

class IsTabuMoveSK : public IIsTabuMoveQAP {
public:
	// konstruktor
	IsTabuMoveSK( int N ) : NextVisitAllowed(N,N) { NextVisitAllowed.Clear(); }
	
	bool	IsTabuMove( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize )
	{
		return( NextVisitAllowed[i][j] > CurrIterNum &&
						NextVisitAllowed[j][i] > CurrIterNum );
	}
	void	SetInitialAssignment( const QAPSolution	&Sol ) {}

	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize ) 
	{
		NextVisitAllowed[i][j] = CurrIterNum + TabuListSize;
		NextVisitAllowed[j][i] = CurrIterNum + TabuListSize;
	}

private:
	Matrix<int>		NextVisitAllowed;
};

class IsTabuMoveT : public IIsTabuMoveQAP {
public:
	// konstruktor
	IsTabuMoveT( int N ) : LastTimeAssigned(N,N) 
	{ 
		for( int i=0; i<N; i++ )
			for( int j=0; j<N; j++ )
				LastTimeAssigned[i][j] = -1000000;
	}

	void	SetInitialAssignment( const QAPSolution	&Sol ) 
	{
		// moramo zapamtiti kako su u poèetku ( iteracije 0 ) bile raspodijeljene jedinke
		for( int i=0; i<Sol.getSize(); i++ )
			LastTimeAssigned[i][Sol(i)] = 0;
	}

	bool	IsTabuMove( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize )
	{
		return( LastTimeAssigned[i][CurrSol(j)] >= CurrIterNum-TabuListSize &&
						LastTimeAssigned[j][CurrSol(i)] >= CurrIterNum-TabuListSize 
					);
	}

	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, int TabuListSize )
	{
		LastTimeAssigned[i][CurrSol(j)] = CurrIterNum;
		LastTimeAssigned[j][CurrSol(i)] = CurrIterNum;
	}

private:
	Matrix<int>		LastTimeAssigned;
};

////////////////////////////////////////////////////////////////////////////////////////

class IIsSatisfiedAspiration {
public:
	virtual	bool	IsSatisfiedAspiration(int r, int s, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue) = 0;
	virtual	void	SetInitialAssignment( const QAPSolution	&Sol, float inInitialFuncValue  ) = 0;
	// moraju znati kada se u algoritmu napravi neki potez
	virtual	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue ) = 0;
};

class IsSatisfiedAspirationFirst : public IIsSatisfiedAspiration {
public:
	IsSatisfiedAspirationFirst() {}

	bool	IsSatisfiedAspiration(int r, int s, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue ) {
		return ( CurrFuncValue + MoveValue < BestFuncValue );
	}
	void	SetInitialAssignment( const QAPSolution	&Sol, float inInitialFuncValue ) {
		CurrFuncValue = BestFuncValue = inInitialFuncValue;
	}
	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue) {
		CurrFuncValue += MoveValue;
		if( CurrFuncValue < BestFuncValue )
			BestFuncValue = CurrFuncValue;
	}

private:
	float	CurrFuncValue;
	float	BestFuncValue;
};

class IsSatisfiedAspirationSecond : public IIsSatisfiedAspiration {
public:
	IsSatisfiedAspirationSecond( int inFacNum, long inAspFuncParamT ) 
	{
		pLastAssignedIteration = new Matrix<int>(inFacNum,inFacNum);
		
		for( int i=0; i<inFacNum; i++ )
			for( int j=0; j<inFacNum; j++ )
				(*pLastAssignedIteration)[i][j] = -1000000;

		AspFuncParamT = inAspFuncParamT;
	}

	bool	IsSatisfiedAspiration(int r, int s, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue ) {
		if( (*pLastAssignedIteration)[r][CurrSol(s)] <= CurrIterNum-AspFuncParamT &&
				(*pLastAssignedIteration)[s][CurrSol(r)] <= CurrIterNum-AspFuncParamT )
			return true;
		else
			return false;
	}
	void	SetInitialAssignment( const QAPSolution	&Sol, float inInitialFuncValue  ) {
		for( int i=0; i<Sol.getSize(); i++ )
			(*pLastAssignedIteration)[i][Sol(i)] = 0;
	}
	void	MovePerformed( int i, int j, const QAPSolution &CurrSol, int CurrIterNum, float MoveValue ) {
		(*pLastAssignedIteration)[i][CurrSol(j)] = CurrIterNum;
		(*pLastAssignedIteration)[j][CurrSol(i)] = CurrIterNum;
	}

private:
	long					AspFuncParamT;
	Matrix<int>		*pLastAssignedIteration;
};

////////////////////////////////////////////////////////////////////////////////////////
enum	AspirationFunctionType	{ FIRST, SECOND };
enum	IsTabuMoveType	{ SKORIN_KAPOV, TAILLARD };

class GeneralTabuSearchQAPSolver : public QAPSolver {
public:
	GeneralTabuSearchQAPSolver( 
					int							inFacNum, 
					IOptTerminator	*inpTerm, 
					int							inTabuListSize = 30, 
					int							inDeltaTabuListSize = 5,
					long						inAspFuncParamT = 1000,
					IsTabuMoveType					inTabuMoveType = SKORIN_KAPOV,
					AspirationFunctionType	inAspFuncType = FIRST
		);
	~GeneralTabuSearchQAPSolver();

	bool	FindBestMove( int *best_s, int *best_r, float *BestMoveValue, float FuncValue, float BestSoFar, const QAPSolution &Sol );

	int		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res );
	bool	IsTimeToRefresh(_TypeValue CurrValue) { return (RefreshCallBackPeriod != 0 ? (CurrIterNum % RefreshCallBackPeriod)==0 : false); }

	bool	setOptTerminatorObject(IOptTerminator *pNew );

	void	setTabuListSize( int inSize ) { TabuListSize = inSize; }
	int		getTabuListSize() { return TabuListSize; }

	void	setTabuMoveObj( IIsTabuMoveQAP *pObj ); 

protected:
	// parametri
	int			TabuListSize, DeltaTabuListSize, TabuListSizeChangePeriod ;
	long		AspFuncParamT;
	
	long		CurrIterNum;

	IOptTerminator						*pTermObj;
	IIsTabuMoveQAP						*pTabuMove;
	IIsSatisfiedAspiration		*pAspiration;
};

class SimpleTabuSearchQAPSolver : public GeneralTabuSearchQAPSolver {
public:
	SimpleTabuSearchQAPSolver( 
					int							inFacNum, 
					IOptTerminator	*inpTerm, 
					int							inTabuListSize = 30	);
};

class RobustTabuSearchQAPSolver : public GeneralTabuSearchQAPSolver {
public:
	RobustTabuSearchQAPSolver( 
					int							inFacNum, 
					IOptTerminator	*inpTerm, 
					int							inTabuListSize = 30, 
					int							inDeltaTabuListSize = 5,
					long						inAspFuncParamT = 1000 );
};

////////////////////////////////////////////////////////////////////////////////////////

class TabuSearchQAPSolver : public QAPSolver {
public:
	TabuSearchQAPSolver( int inFacNum, int inTabuListSize, IOptTerminator *inpTerm);
	TabuSearchQAPSolver( int inFacNum, int inTabuListSize, int inIterNum);

	int		Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res );

	bool	IsTimeToRefresh() { return (RefreshCallBackPeriod != 0 ? (CurrIterNum % RefreshCallBackPeriod)==0 : false); }

	bool	setOptTerminatorObject(IOptTerminator *pNew )
				{
					if( pNew == NULL )
						return false;
					else {
						if( pTermObj != NULL ) {	// najprije treba izbrisati starog
							pNew->CopyState(pTermObj);
							delete pTermObj;
						}
						
						pTermObj = pNew;
						return true;
					}
				}

	void	setTabuListSize( int inSize ) { TabuListSize = inSize; }
	int		getTabuListSize() { return TabuListSize; }

protected:
	IOptTerminator	*pTermObj;
	IIsTabuMoveQAP	*pTabuMove;

	int			TabuListSize;
	long		CurrIterNum;
};

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

// uèitava podatke o matricama A i B iz datoteke zadanog imena
int		LoadProblem( char *FileName, int *Size, Matrix<float>	*A, Matrix<float>	*B );
int		LoadProblem( std::string FileName, int *Size, Matrix<float>	*A, Matrix<float>	*B );


/*********************************************************************************/
/*********************************************************************************/

#ifdef WIN32

class ThreadableOptimizationObject {
public:
	ThreadableOptimizationObject() { 
		bInProgress = false; bStopped = false; bTerminate=false; 
		hThread=NULL; hTerminateEvent=NULL; hSemaphore = NULL; 
	}

	virtual void Start(UINT (*ThreadFunc)(LPVOID), LPVOID pParam);
	virtual	void OptimizationFinished();
	virtual void Stop();
	virtual void Continue();
	virtual void Terminate();

	bool		IsInProgress() { return bInProgress; }
	bool		IsStopped() { return bStopped; }

	void		setTerminate( bool bFlag );
	bool		getTerminate() { return bTerminate; }

	HANDLE	getEventHandle() { return hTerminateEvent; }
	HANDLE	getThreadHandle() { return hThread; }

protected:
	HANDLE			hThread;
	HANDLE			hTerminateEvent;
	HANDLE			hSemaphore;

	bool		bInProgress;
	bool		bStopped;
	bool		bTerminate;
};

/*********************************************************************************/

class ThreadableGeneticQAPSolver : public GeneticQAPSolver, public ThreadableOptimizationObject {
public:
	// konstruktor
	ThreadableGeneticQAPSolver( 
				int							inFacNum, 
				int							inPopSize, 
				IOptTerminator	*pTerm, 
				float						inMutProb 
		)	:	GeneticQAPSolver(inFacNum, inPopSize, pTerm, inMutProb ) {}

	ThreadableGeneticQAPSolver( 
				int			inFacNum, 
				int			inPopSize, 
				long		inIterNum, 
				float		inMutProb 
		)	:	GeneticQAPSolver(inFacNum, inPopSize, inIterNum, inMutProb ) {}

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res  );

	void		PerformRefreshing( IterativeOptRes<float, QAPSolution> &res, float Best, const QAPSolution *BestSol  );
};

class ThreadableSimAnnealingQAPSolver : public SimAnnealingQAPSolver, public ThreadableOptimizationObject {
public:
	// konstruktor
	ThreadableSimAnnealingQAPSolver( 
				int			inFacNum, 
				int			inIterNum = 10000,
				double	inAcceptHigherProb=0.99,
				double	inTempChangeFactor = 0.99,
				int			inPermNum = 100 
		)	:	SimAnnealingQAPSolver(inFacNum,inIterNum,inAcceptHigherProb,inTempChangeFactor,inPermNum) {}

	ThreadableSimAnnealingQAPSolver( 
				int							inFacNum, 
				IOptTerminator	*pTerm,
				double					inAcceptHigherProb=0.99,
				double					inTempChangeFactor = 0.99,
				int							inPermNum = 100 
		)	:	SimAnnealingQAPSolver(inFacNum,pTerm,inAcceptHigherProb,inTempChangeFactor,inPermNum) {}

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res  );
};

class ThreadableTabuSearchQAPSolver : public TabuSearchQAPSolver, public ThreadableOptimizationObject {
public:
	// konstruktor
	ThreadableTabuSearchQAPSolver( 
				int inFacNum, 
				int inTabuListSize, 
				int inIterNum 
		)	:	TabuSearchQAPSolver(inFacNum,inTabuListSize,inIterNum) {}

	ThreadableTabuSearchQAPSolver( 
				int							inFacNum, 
				int							inTabuListSize, 
				IOptTerminator	*pTerm
		)	:	TabuSearchQAPSolver(inFacNum,inTabuListSize,pTerm) {}

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res  );
};

class ThreadableSimpleTabuSearchQAPSolver : public SimpleTabuSearchQAPSolver, public ThreadableOptimizationObject {
public:
	// konstruktor
	ThreadableSimpleTabuSearchQAPSolver( 
				int							inFacNum, 
				IOptTerminator	*pTerm,
				int							inTabuListSize = 30
		)	:	SimpleTabuSearchQAPSolver(inFacNum,pTerm,inTabuListSize) {}

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res  );
};

class ThreadableRobustTabuSearchQAPSolver : public RobustTabuSearchQAPSolver, public ThreadableOptimizationObject {
public:
	// konstruktor
	ThreadableRobustTabuSearchQAPSolver( 
				int							inFacNum, 
				IOptTerminator	*pTerm,
				int							inTabuListSize = 30,
				int							inDeltaTabuListSize = 5,
				long						inAspFuncParamT = 5000
		)	:	RobustTabuSearchQAPSolver(inFacNum,pTerm,inTabuListSize,inDeltaTabuListSize,inAspFuncParamT) {}

	int			Optimize( IterOptContResWithSolutions<float,QAPSolution> *Res  );
};

#endif  // WIN32

#endif
