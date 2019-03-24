
#if !defined(AFX_TESTTHREADCLASS_H__E14C5551_609F_45D8_817F_F98D4E7A1128__INCLUDED_)
#define AFX_TESTTHREADCLASS_H__E14C5551_609F_45D8_817F_F98D4E7A1128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ThreadableOptimizationObject {
public:
	ThreadableOptimizationObject() { bInProgress = false; bStopped = false; }

	virtual void Start(UINT (*ThreadFunc)(LPVOID));
	virtual void Stop();
	virtual void Continue();
	virtual void Terminate();

	HANDLE			hThread;
	HANDLE			hTerminateEvent;

	bool		bInProgress;
	bool		bStopped;
	bool		bTerminate;
};

class QAP : public ThreadableOptimizationObject {
public:
	QAP() {}

	void	Optimize( int IterNum );

	static	UINT ThreadFunc( LPVOID pParam );
};


#endif // !defined(AFX_TESTTHREADCLASS_H__E14C5551_609F_45D8_817F_F98D4E7A1128__INCLUDED_)
