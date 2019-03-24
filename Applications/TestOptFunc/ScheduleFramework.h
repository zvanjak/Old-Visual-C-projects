#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;


/***************************************************************************************/

#ifndef SHEDULE_FRAMEWORK_H
#define SHEDULE_FRAMEWORK_H

const int MAX_ITEMS = 10;

class	ScheduleFramework {
public:
	ScheduleFramework( int inExamNum=10, int inTermNum=20, int inBrPodrokova=3 );

	virtual	void		Optimize() = 0;

	string	GetName( int i );
	bool		SetName( int i, string Name );

//	float		Get
public:
	int			ExamNum, TermNum, BrPodrokova;

	string	ItemName[MAX_ITEMS];	// "imena" kuglica koje rasporeðujemo
	float		Presjek[10][10];
};

#endif