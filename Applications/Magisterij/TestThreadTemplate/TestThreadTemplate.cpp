// TestThreadTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//class A;
//typedef void(A::*pMember)();

class A {
public:
	A() {}
	void func( void (A::*a)() );
};

void A::func( void (A::*a)() )
{
	(this->*a)();
}

/*******************************************************************************/
/*******************************************************************************/

//		typedef void (ObjectType::*PtrMemberFunc)();
//		TData(ObjectType *inThis, PtrMemberFunc inFunc );
//TData< class ObjectType, class Param >::TData(ObjectType *inpThis, PtrMemberFunc inFunc)

class IQAPSolver {
public:
	virtual void Optimize( void ) = 0;
};

class QAPGenetic : public IQAPSolver {
public:
	void Optimize( void ) { }
};

class	Genetic {
public:
	Genetic() {}
	void Optimize( void ) {}
};

/*******************************************************************************/
template< class ObjectType > class TData {
	public:
		TData(ObjectType *inThis, void (ObjectType::*inFunc)() );

	private:
		ObjectType			*pThis;
		void (ObjectType::*Function)() ;
};

TData< class ObjectType >::TData(ObjectType *inpThis, void (ObjectType::*inFunc)())
{
	pThis = inpThis;
	Function = inFunc;
}
/*******************************************************************************/
class TData2 {
	public:
		TData2(Genetic *inThis, void (Genetic::*inFunc)() );

	private:
		Genetic			*pThis;
		void (Genetic::*Function)() ;
};

TData2::TData2(Genetic *inpThis, void (Genetic::*inFunc)())
{
	pThis = inpThis;
	Function = inFunc;
}
/*******************************************************************************/
class TData3 {
	public:
		TData3(IQAPSolver *inThis, void (IQAPSolver::*inFunc)() );

	private:
		IQAPSolver		*pThis;
		void (IQAPSolver::*Function)() ;
};

TData3::TData3(IQAPSolver *inpThis, void (IQAPSolver::*inFunc)())
{
	pThis = inpThis;
	Function = inFunc;
}

int main(int argc, char* argv[])
{
	Genetic		obj;

	// ovdje je greška - ne zna prebaciti Genetic u ObjectType
//	TData<Genetic>	a(&obj, &Genetic::Optimize);
	TData2					b(&obj, &Genetic::Optimize);

	QAPGenetic			obj2;
	TData3					c(&obj2, &IQAPSolver::Optimize);
	return 0;
}
