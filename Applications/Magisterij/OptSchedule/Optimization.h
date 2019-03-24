#ifndef __OPTIMIZATION_H
#define __OPTIMIZATION_H

#pragma warning (disable : 4786)

#include <afx.h>

#include <time.h>
#include <assert.h>

#include <map>
#include <vector>
#include <string>

using std::string;

#include "Win32Serialize.h"
#include "OptimizationResults.h"

#include "OptRefresher.h"
#include "OptSaver.h"
#include "OptTerminator.h"

#define WM_REFRESH_MESSAGE (WM_USER + 100)

/**************************************************************************************/
/**************************************************************************************/

class	AlgParam
{
public:
	AlgParam() {}
	AlgParam(string inName, string inValue, char inType ) : Name(inName), Value(inValue), Type(inType) {}
	
	string		Name;
	string		Value;
	char			Type;

#ifdef __AFX_H__
	friend	void operator<<( CArchive &ar, AlgParam &data ) {
		SaveSTLstring(ar, data.Name);
		SaveSTLstring(ar, data.Value);
		ar << data.Type;
	}
	friend	void operator>>( CArchive &ar, AlgParam &data ) {
		LoadSTLstring(ar, data.Name);
		LoadSTLstring(ar, data.Value);
		ar >> data.Type;
	}

	void	Serialize( CArchive &ar ) {
		if( ar.IsStoring() ) {
			ar << *this;
		}
		else {
			ar >> *this;
		}
	}

#endif
};

bool	SerializeInArchiveAlgParamVec( CArchive &ar, std::vector<AlgParam> &vec );

// eksplicitna instancijacija
#ifdef __AFX_H__
	template <> bool SerializeInArchive<AlgParam>( CArchive &ar, std::vector<AlgParam> &);
#endif

/**************************************************************************************/
/**************************************************************************************/

class AlgDescription {
private:
	string		Type;
	string		Subtype;
	string		OptID;

	std::vector<AlgParam>		vecParam;

public:
	AlgDescription() {}
	AlgDescription(string inType, string inSubtype) { Type=inType; Subtype=inSubtype; }
	~AlgDescription() {
		vecParam.clear();		// pitanje da li je uopæe potrebno
	}

	// get i set accessori
	void	setOptID( string inOptID ) { OptID = inOptID; }
	void	setAutomaticOptID();

	void	setType( string inType ) { Type = inType; }
	void	setSubtype( string inSubtype ) { Subtype = inSubtype; }

	void	getOptID( string &outOptID ) { outOptID = OptID; }
	void	getType( string &outType ) { outType = Type; }
	void	getSubtype( string &outSubtype ) { outSubtype = Subtype; }
	
	string	getOptID() { return OptID; }
	string	getType() { return  Type; }
	string	getSubtype() { return Subtype; }

	bool		getParamInString( char *str );

	void	addParam( string inName, string inValue, char inParamType );
	void	addParam( string inName, long inValue, char *format, char inParamType );
	void	addParam( string inName, float inValue, char *format, char inParamType );

	int		getParamNum() { return vecParam.size(); }

	bool	getParam( int ParamNum, string &outName, string &outValue, char &outParamType );
	bool	changeParam( string ParamName, string inNewValue, char inNewType );

#ifdef __AFX_H__
	friend	void operator<<( CArchive &ar, AlgDescription &data ) {
		SaveSTLstring(ar, data.Type);
		SaveSTLstring(ar, data.Subtype);
		SaveSTLstring(ar, data.OptID);

		SerializeInArchiveAlgParamVec(ar, data.vecParam);
	}
	friend	void operator>>( CArchive &ar, AlgDescription &data ) {
		LoadSTLstring(ar, data.Type);
		LoadSTLstring(ar, data.Subtype);
		LoadSTLstring(ar, data.OptID);

		SerializeInArchiveAlgParamVec(ar, data.vecParam);
	}

	void	Serialize( CArchive &ar ) {
		if( ar.IsStoring() )
			ar << *this;
		else
			ar >> *this;
	}
#endif
};


/************************************************************************************/
/*************************************************************************************/

template<class TypeValue, class TypeSol> class IOptimization {
public:
	virtual	TypeValue		OptFunc( TypeSol	&a ) = 0;
};

/************************************************************************************/
/*************************************************************************************/

template<class TypeValue, class TypeSol>
class IIterativeOptimization
{
protected:
	IOptTerminator		*pTermObj;
	
	IOptSaver<TypeValue, TypeSol>		*pSaveObj;
	IOptRefresher<TypeValue, TypeSol>		*pRefreshObj;

	bool				bBestValuesInitialized;
	TypeValue		CurrFuncValue, BestFuncValue;
	TypeSol			CurrSolution, BestSolution;

	long		CurrIterNum;
	float		TimeStarted;

	bool		bTerminate;

	Chronometer	Watch;	// kronometar mjeri koliko dugo se izvršavala optimizacija

public:
	IIterativeOptimization() {
		pTermObj = NULL;
		pRefreshObj = NULL;
		pSaveObj = NULL;
		
		bBestValuesInitialized = false;
		bTerminate = false;
	}
	IIterativeOptimization( IOptTerminator	*inpTerm,
													IOptRefresher<TypeValue, TypeSol>	*inpRefresh,
													IOptSaver<TypeValue, TypeSol>	*inpSave )  {
		pTermObj = inpTerm;
		pRefreshObj = inpRefresh;
		pSaveObj = inpSave;

		bBestValuesInitialized = false;
		bTerminate = false;
	}

	bool	SetOptTerminatorObject(IOptTerminator *pNew);
	bool	SetOptSaverObject(IOptSaver<TypeValue, TypeSol> *pNew);
	bool	SetOptRefresherObject(IOptRefresher<TypeValue, TypeSol> *pNew);

	////////////////////////////////////////////////////////////////////////////////////
	// ove funkcije æe morati definirati algoritmi za optimizaciju
	virtual	bool				Initialize() = 0;
	virtual	bool				PerformIteration() = 0;

	// funkcija koja se optimira
	virtual	TypeValue		OptFunc( TypeSol	&a ) = 0;
	
	virtual	long	Optimize( IterOptContResWithSolutions<TypeValue, TypeSol> &res )
	{
		Initialize();
		pTermObj->Start();
		Watch.Start();
		
		CurrIterNum = 0;
		while( pTermObj->IsOptimizationFinished() == false ) 
		{
			// neka izvedeni algoritam obavi svoj korak iteraicje
			PerformIteration();

			// a onda ide Refresh
			if( pRefreshObj->IsTimeToRefresh(CurrFuncValue) ) {
				IterativeOptRes<TypeValue, TypeSol> 	opt(CurrFuncValue, CurrSolution, Watch.GetRunningTime(), CurrIterNum );
				pRefreshObj->PerformRefreshing(opt, BestFuncValue, &BestSolution);
			}
			// pa snimanje rezultata
			if( pSaveObj->IsTimeToSave(CurrFuncValue) ) {
				res.addNewResult(CurrIterNum, CurrFuncValue);
			}
			// pa sljedeæi korak iteracije
			pTermObj->NextStep(&BestFuncValue);

			CurrIterNum++;

			// ukoliko je bTerminate netko postavio na true, prekini optimizaciju
			if( bTerminate == true )
				break;
		}

		SaveFinalResults(res);
		return 0;
	}

	virtual	bool	SaveFinalResults(IterOptContResWithSolutions<TypeValue, TypeSol> &Res);
};

class QAP : public IIterativeOptimization<float, float>
{
};


template<class TypeValue, class TypeSol>
class IThreadableIterativeOptimization : public IIterativeOptimization<TypeValue, TypeSol>
{
protected:
	HANDLE			hThread;
	HANDLE			hTerminateEvent;
	HANDLE			hSemaphore;

	bool		bInProgress;
	bool		bStopped;
	bool		bTerminate;

public:
	IThreadableIterativeOptimization() { 
		bInProgress = false; bStopped = false; bTerminate=false; 
		hThread=NULL; hTerminateEvent=NULL; hSemaphore = NULL; 
	}

	virtual void Start(UINT (*ThreadFunc)(LPVOID), LPVOID pParam);
	virtual void Stop();
	virtual void Continue();
	virtual void Terminate();

	bool		IsInProgress() { return bInProgress; }
	bool		IsStopped() { return bStopped; }

	void		setTerminate( bool bFlag );
	bool		getTerminate() { return bTerminate; }

	HANDLE	getEventHandle() { return hTerminateEvent; }
	HANDLE	getThreadHandle() { return hThread; }

	long	Optimize( IterOptContResWithSolutions<TypeValue, TypeSol> &res );
};

/**********************************************************************************/

template<class TypeValue, class TypeSol>
bool	IIterativeOptimization<TypeValue, TypeSol>::SetOptTerminatorObject(IOptTerminator *pNew) {
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
template<class TypeValue, class TypeSol> 
bool	IIterativeOptimization<TypeValue, TypeSol>::SetOptSaverObject(IOptSaver<TypeValue, TypeSol> *pNew) {
		if( pNew == NULL )
			return false;
		else {
			if( pSaveObj != NULL ) {	// najprije treba izbrisati starog
				pNew->CopyState(pSaveObj);
				delete pSaveObj;
			}
			
			pSaveObj = pNew;
			return true;
		}
	}
template<class TypeValue, class TypeSol> 
bool	IIterativeOptimization<TypeValue, TypeSol>::SetOptRefresherObject(IOptRefresher<TypeValue, TypeSol> *pNew) {
		if( pNew == NULL )
			return false;
		else {
			if( pRefreshObj != NULL ) {	// najprije treba izbrisati starog
				pNew->CopyState(pRefreshObj);
				delete pRefreshObj;
			}
			
			pRefreshObj = pNew;
			return true;
		}
	}

template<class TypeValue, class TypeSol> 
bool	IIterativeOptimization<TypeValue,TypeSol>::SaveFinalResults(IterOptContResWithSolutions<TypeValue, TypeSol> &Res) {
	float	TimeElapsed = (clock() - TimeStarted) * 1000.f / CLOCKS_PER_SEC;

	Res.setBestFuncValue(BestFuncValue);
	Res.setSolution(BestSolution);
	Res.setIterNum(CurrIterNum);
	Res.setOptimDuration(Watch.GetRunningTime());

	return true;
}


/*********************************************************************************/
/*********************************************************************************/

/************************************************************************************/

template<class _TypeValue, class _TypeSol> class IRefreshableOptimizationObject {
private:
	long				RefreshCallBackPeriod;	// svakih koliko iteracija se poziva Refresh()
	bool				RefreshOnEveryImprovement;

	_TypeValue	BestValueSoFar;					// da bi mogli znati kada nam se poboljšava funkcija cilja
	bool				BestValueInitialized;

protected:
	// pokazivaè na objekt koji u sebi ima funkciju Refresh() koja æe se periodièki 
	// pozivati sa rezultatima optimizacije
	HasRefreshFunction<_TypeValue, _TypeSol>	*pRefreshObj;	

	// pokazivaè na mjesto u memoriji gdje æe se upisivati rezultati tijekom optimizacije
	CExchangeData<_TypeValue, _TypeSol>		*pExData;

public:
	IRefreshableOptimizationObject() {
		RefreshCallBackPeriod = 100;
		pRefreshObj = NULL;
		pExData = NULL;

		RefreshOnEveryImprovement = false;
		BestValueInitialized = false;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Funkcije kojima izvedeni razred mora dati implementaciju jer se funkcija 
	// PerformRefreshing() oslanja na njih
	//		- sve funkcije mogu vratiti FALSE, ukoliko izvedeni razred ne podržava koncept
	virtual bool	IsTimeToRefresh(_TypeValue CurrValue) = 0;

	//////////////////////////////////////////////////////////////////////////////////////
	// Funkcije za handlanje refreshinga
	// ovaj funkcija je virtual zato što æe joj Threadable razredi dati drugo znaèenje

//	virtual	void		PerformRefreshing( IterativeOptRes<_TypeValue, _TypeSol> &CurrSol, _TypeValue Best, const _TypeSol *BestSol  ) {
//		if( pRefreshObj != NULL )
//			pRefreshObj->Refresh(&CurrSol, Best, BestSol);
//	}

	virtual	void		PerformRefreshing( IterativeOptRes<_TypeValue, _TypeSol> &CurrSol, _TypeValue Best, const _TypeSol *BestSol  ) {
		if( pExData != NULL ) {
			pExData->SetData(CurrSol, Best, BestSol);
			PostMessage(pExData->hWnd, WM_REFRESH_MESSAGE, NULL, NULL);
		}
	}

	void		SetRefreshCallBack( HasRefreshFunction<_TypeValue, _TypeSol> *obj ) { pRefreshObj = obj; }
	void		SetRefreshExData( CExchangeData<_TypeValue, _TypeSol>	*pIn ) { pExData = pIn; }
	
	void		SetRefreshCallBackPeriod( long inPeriod ) { RefreshCallBackPeriod = inPeriod; }
	long		GetRefreshCallBackPeriod() { return RefreshCallBackPeriod; }

	void		SetRefreshOnEveryImprovement( bool in ) { RefreshOnEveryImprovement = in; }
	bool		GetRefreshOnEveryImprovement( void ) { return RefreshOnEveryImprovement; }
};

template<class _TypeValue, class _TypeSol>
class IIterativeOptimizationObject {
protected:
	IOptTerminator		*pTermObj;
	
	IOptRefresher<_TypeValue, _TypeSol>		*pRefreshObj;
	IOptSaver<_TypeValue, _TypeSol>				*pSaveObj;

public:
	IIterativeOptimizationObject() {
		pTermObj = NULL;
		pRefreshObj = NULL;
		pSaveObj = NULL;
	}
	IIterativeOptimizationObject( IOptTerminator	*inpTerm,
																IOptRefresher<_TypeValue, _TypeSol>	*inpRefresh,
																IOptSaver<_TypeValue, _TypeSol>			*inpSave ) 
	{
		pTermObj = inpTerm;
		pRefreshObj = inpRefresh;
		pSaveObj = inpSave;
	}

	void		SetSaveResultsPeriod( long inPeriod ) { SaveResultsPeriod = inPeriod; }
	long		GetSaveResultsPeriod() { return SaveResultsPeriod; }

	bool		SetOptTerminatorObject(IOptTerminator *pNew) {
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
	bool		SetOptSaverObject(IOptSaver<_TypeValue, _TypeSol> *pNew) {
		if( pNew == NULL )
			return false;
		else {
			if( pSaveObj != NULL ) {	// najprije treba izbrisati starog
				pNew->CopyState(pSaveObj);
				delete pSaveObj;
			}
			
			pSaveObj = pNew;
			return true;
		}
	}
	bool		SetOptRefresherObject(IOptRefresher<_TypeValue, _TypeSol> *pNew) {
		if( pNew == NULL )
			return false;
		else {
			if( pRefreshObj != NULL ) {	// najprije treba izbrisati starog
				pNew->CopyState(pRefreshObj);
				delete pRefreshObj;
			}
			
			pRefreshObj = pNew;
			return true;
		}
	}
	
	void		SetRefreshExData( CExchangeData<_TypeValue, _TypeSol> * inpExData ) {
		assert(pRefreshObj != NULL);
		pRefreshObj->AssignPointerToExchangeData(inpExData);
	}
	void		PerformRefreshing( IterativeOptRes<_TypeValue, _TypeSol> &CurrSol, _TypeValue Best, const _TypeSol *BestSol  ) {
		if( pRefreshObj != NULL ) {
			pRefreshObj->PerformRefreshing(CurrSol, Best, BestSol);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// implementirana suèelja od IOpt agregiranih objekata
	void		StartOptimization() { 
		pTermObj->Start();
		pRefreshObj->Start();
		pSaveObj->Start();
	}
	void		NextStep( void *pData ) { 
		pTermObj->NextStep(pData); 
		pRefreshObj->NextStep(pData);
		pSaveObj->NextStep(pData);
	}
	void		CopyState( IOptTerminator	*copy ) { pTermObj->CopyState(copy); }
	void		CopyState( IOptRefresher<_TypeValue, _TypeSol>	*copy ) { pRefreshObj->CopyState(copy); }
	void		CopyState( IOptSaver<_TypeValue, _TypeSol>			*copy ) { pSaveObj->CopyState(copy); }

	bool		IsOptimizationFinished() { return pTermObj->IsOptimizationFinished(); }
	bool		IsTimeToRefresh(_TypeValue CurrFuncValue) { return pRefreshObj->IsTimeToRefresh(CurrFuncValue); }
	bool		IsTimeToSave(_TypeValue CurrFuncValue) { return pSaveObj->IsTimeToSave(CurrFuncValue); }
};

/**************************************************************************************/
/**************************************************************************************/

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

#endif  // WIN32



//template class IIterativeOptimization<float, float>;

#endif	//__OPTIMIZATION_H