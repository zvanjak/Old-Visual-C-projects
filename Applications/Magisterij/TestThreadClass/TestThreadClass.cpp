// TestThreadClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestThreadClass.h"

#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void ThreadableOptimizationObject::Start( AFX_THREADPROC ThreadFunc /*UINT (*ThreadFunc)(LPVOID)*/ )
{
	// možemo pokrenuti optimizaciju samo ukoliko veæ nije pokrenuta
	if( bInProgress == false ) 
	{
		bInProgress = true;

		DWORD		IDThread;

        hThread = CreateThread(NULL, 0, 
            (LPTHREAD_START_ROUTINE) ThreadFunc, 
            this,  // pass event handle
            0, &IDThread); 
        if (hThread == NULL) 
        {
            // Error exit.
        }

    hTerminateEvent = CreateEvent( 
					NULL,   // no security attributes
					FALSE,  // auto-reset event object
					FALSE,  // initial state is nonsignaled
					NULL);  // unnamed object
    
	}
}

void ThreadableOptimizationObject::Stop() {
	if( bStopped == false && hThread != NULL ) 
	{
		SuspendThread(hThread);
		bStopped = true;
	}
}

void ThreadableOptimizationObject::Continue() {
	if( bStopped == true && hThread != NULL) 
	{
		ResumeThread(hThread);
		bStopped = false;
	}
}

void ThreadableOptimizationObject::Terminate() 
{
	bTerminate = true;

	WaitForSingleObject(hTerminateEvent, INFINITE);

	cout << "Thread terminated " << endl;
}

/*******************************************************************************/

UINT QAP::ThreadFunc( LPVOID pParam )
{
	QAP		*pQAP = (QAP *) pParam;

	pQAP->Optimize(10);

	SetEvent(pQAP->hTerminateEvent);

	cout << "Thread terminated in ThreadFunc" << endl;
	return 1;
}

void QAP::Optimize(int IterNum) {
	float		x, y;

	for( int i=0; i<IterNum; i++ ) 
	{
		if( bTerminate == true )
			return;

		// problem - što ukoliko bi se pojedina iteracija optimizacije izvršavala dugo
		Sleep(3000);
		
		x = rand() % 360;
		y = sin(x);
		
//		if( i % 100 == 0 ) 
		{
			cout << "x = " << x << "  sin(x) = " << y << endl;
		}
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

	int		i; 
	std::vector<int>		A(10,0), B(5,-1), C;

	for( i=0; i<10; i++ )
		A[i] = i;

	for( i=0; i<10; i++ )
		printf("\n %d", A[i]);

	A = B;

	for( i=0; i<10; i++ )
		printf("\n %d", A[i]);

	C = A;

	for( i=0; i<C.size(); i++ )
		printf("\n %d", C[i]);
/*
	QAP		obj;

	obj.Start(obj.ThreadFunc);
	Sleep(10000);
	obj.Terminate();
	Sleep(5000);
*/

/*
	B	objB(10.f, 5);

	B	objB2(objB);
	B	empty;

	empty = objB2;

	printf("%f %d\n", objB.MemB, objB.Mem );
	printf("%f %d\n", objB2.MemB, objB2.Mem );
	printf("%f %d\n", empty.MemB, empty.Mem );
*/
	return nRetCode;

}



class A {
public:
	A() {}
	A( int inMem ) { Mem=inMem; }
	A( const A &b ) { Mem = b.Mem; }
	A&	operator=( const A &b ) { Mem = b.Mem; return *this; }

	int Mem;
};

class B : public A {
public:
	B() {}
	B( float inMemB , int inMemA) : A(inMemA) { MemB = inMemB; }
	B( const B &b) : A(b)  { MemB = b.MemB; }
	B&	operator=( const B &b ) { A::operator =(b); MemB = b.MemB; return *this; }
	
	float	MemB;
};

