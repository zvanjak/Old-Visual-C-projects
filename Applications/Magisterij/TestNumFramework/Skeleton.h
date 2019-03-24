#ifndef __SKELETON_H
#define __SKELETON_H

#define WM_REFRESH_MESSAGE (WM_USER + 100)

/////////////////////////////////////////////////////////////////////////////////////////
template<class _TResult> class IExchangeDataObject {
public:
	IExchangeDataObject( HWND inhWnd ) {
		m_hWnd = inhWnd;
	}

	virtual void SetResult( _TResult &res ) { m_Result = res; PostMessage(m_hWnd, WM_REFRESH_MESSAGE, 0, 0); }
	virtual void GetResult( _TResult *res ) { *res = m_Result; }
	virtual void Free() { }

private:
	HWND			m_hWnd;
	_TResult	m_Result;
};

/////////////////////////////////////////////////////////////////////////////////////////
template<class _TResult> class IVisualizationObject {
public:
	IVisualizationObject() { pExch = NULL; }

	void	CreateExchangeObject( HWND inhWnd ) {
		pExch = new IExchangeDataObject<_TResult>(inhWnd);
	}
	IExchangeDataObject<_TResult>		*GetExchangePtr() { return pExch; }

private:
	IExchangeDataObject<_TResult>		*pExch;
};

/////////////////////////////////////////////////////////////////////////////////////////
template<class _TResult> class ISaveResultObject {
public:
	virtual void AddCalcResult(_TResult &res ) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
template<class _TResult> class ICalculateObject {
public:
	virtual void Calculate( _TResult &outResult ) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
template<class _TResult> class ThreadParameters {
public:
	ThreadParameters(	ISaveResultObject<_TResult>			&Save,
										ICalculateObject<_TResult>			&Calc,
										IExchangeDataObject<_TResult>		&Exch
									)	: objSave(Save), objCalc(Calc), objExch(Exch) {}

	ISaveResultObject<_TResult>			&objSave;
	ICalculateObject<_TResult>			&objCalc;
	IExchangeDataObject<_TResult>		&objExch;	
};

/****************************************************************************************/
/****************************************************************************************/

template<class _TResult> class ThreadableCalcObject : public ICalculateObject<_TResult> {
public:
	/////////////////////////////////////////////////////////////////////////////////////////
	ThreadableCalcObject( IExchangeDataObject<_TResult> *inpExch, ISaveResultObject<_TResult> *inpSave)
					: pExch(inpExch), pSave(inpSave) 
	{
		CurrIterNum = 0;
		
		hThread	= NULL;
		hTerminateEvent = NULL;
		
		bStopped = false;
		bTerminateThread = false;
		bCalcInProgress = false;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	static UINT ThreadFunc( LPVOID pPar ) {
		ThreadParameters<_TResult>	*pThrPar = static_cast<ThreadParameters<_TResult> *>(pPar);

		_TResult	outResult;

		pThrPar->objCalc.Calculate(outResult);
		pThrPar->objSave.AddCalcResult(outResult);

		delete pThrPar;

		return 1;
	}

	void Start() {
		ThreadParameters<_TResult>	*pThrPar = new ThreadParameters<_TResult>(*pSave, 
																																					*this, 
																																					*pExch);

		hTerminateEvent = CreateEvent( NULL,   // no security attributes
																	 FALSE,  // auto-reset event object
																	 FALSE,  // initial state is nonsignaled
																	 NULL);  // unnamed object

		DWORD		IDThread;
		hThread = CreateThread( NULL, 0,
														(LPTHREAD_START_ROUTINE) ThreadFunc, 
														pThrPar,  
														0, &IDThread); 
		if (hThread == NULL)
				return;		// Error
		bCalcInProgress = true;

//		SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
	}
	
	void Stop() {
		if( bStopped == false && hThread != NULL ) 
		{
			SuspendThread(hThread);
			bStopped = true;
		}
	}

	void Continue() {
		if( bStopped == true && hThread != NULL) 
		{
			ResumeThread(hThread);
			bStopped = false;
		}
	}
	void Terminate() {
		if( bCalcInProgress == true ) {
			// ukoliko je nit zaustavljena, treba je ponovno pokrenuti
			if( bStopped == true )
				Continue();

			bTerminateThread = true;
			// sada moramo èekati da dobijemo potvrdu od worker thread da je završila
			WaitForSingleObject(hTerminateEvent, INFINITE);
			bCalcInProgress = false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	virtual	void	Initialize() = 0;
	virtual	void	PerformIteration(_TResult &res) = 0;

	virtual bool	IsOptimizationFinished() = 0;
	virtual	bool	IsTimeToRefresh() = 0;

	void Calculate( _TResult	&outResult ) {
		_TResult	res;

		Initialize();
		CurrIterNum = 0;

		while( IsOptimizationFinished() != true ) {
			PerformIteration(res);

			if( bTerminateThread != false ) 
			{
				outResult = res;
				// moramo obavijestiti objekt za vizualizaciju da smo završili
				SetEvent(hTerminateEvent);
				return;
			}
			if( IsTimeToRefresh() == true ) {
				pExch->SetResult(res);
			}
		}
		outResult = res;
	}
private:
	long	CurrIterNum;

	IExchangeDataObject<_TResult>	*pExch;
	ISaveResultObject<_TResult>		*pSave;

	HANDLE	hThread;
	HANDLE	hTerminateEvent;
	
	bool	bStopped;
	bool	bTerminateThread;
	bool	bCalcInProgress;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class ThreadablePrimSolver : public ThreadableCalcObject<long> {
public:
	ThreadablePrimSolver( IExchangeDataObject<long> *pExch, 
												ISaveResultObject<long>   *pSave,
												long inStart, long inEnd 
											) 
				: ThreadableCalcObject<long>(pExch,pSave)
	{
		lStart = inStart;
		lEnd = inEnd;
	}

	void Initialize() {
		CurrInvestigate = lStart;
		LastFound = -1;
	}
	void PerformIteration(long &res) {
		CurrInvestigate++;

		for( int i=2; i<sqrt(CurrInvestigate); i++ )
			if( CurrInvestigate % i == 0 )
				return;

		res = LastFound = CurrInvestigate;
	}
	bool	IsOptimizationFinished() {
		if( CurrInvestigate >= lEnd )
			return true;
		else
			return false;
	}
	bool	IsTimeToRefresh() {
		if( CurrInvestigate % 100 == 0 )
			return true;
		else
			return false;
	}

private:
	long	lStart, lEnd;

	long	CurrInvestigate;
	long	LastFound;
};

#endif