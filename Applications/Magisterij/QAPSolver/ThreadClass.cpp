#include "ThreadClass.h"

void ThreadableOptimizationObject::Start( AFX_THREADPROC ThreadFunc /*UINT (*ThreadFunc)(LPVOID)*/ )
{
	// možemo pokrenuti optimizaciju samo ukoliko veæ nije pokrenuta
	if( bInProgress == false ) 
	{
		bInProgress = true;

		pThread = AfxBeginThread(ThreadFunc, this);

    hTerminateEvent = CreateEvent( 
					NULL,   // no security attributes
					FALSE,  // auto-reset event object
					FALSE,  // initial state is nonsignaled
					NULL);  // unnamed object
    
	}
}

void ThreadableOptimizationObject::Stop() {
	if( bStopped == false && pThread != NULL ) 
	{
		pThread->SuspendThread();
		bStopped = true;
	}
}

void ThreadableOptimizationObject::Continue() {
	if( bStopped == true && pThread != NULL) 
	{
		pThread->ResumeThread();
		bStopped = false;
	}
}

void ThreadableOptimizationObject::Terminate() 
{
	bTerminate = true;

	WaitForSingleObject(hTerminateEvent, INFINITE);

	cout << "Thread terminated " << endl;
}
