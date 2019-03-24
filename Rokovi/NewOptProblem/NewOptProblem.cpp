// NewOptProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProblemData.h"
#include "Presjek.h"

#include "OptProblem.h"

int main(int argc, char* argv[])
{
/*
	PresjekStudData		dat;

	dat.setPresjek(1,2,100);
	dat.setPresjek(2,3,200);
	dat.setPresjek(1,4,300);

	dat.Print();

	printf("\n Presjek %d i %d je %d\n", 1, 4, dat.getPresjek(4,1) );

	IspitDodPodaci	isp(1,1,1,' ', 1);
	Ispit	ispit1(353, "Matematièka analiza I", 1, 622, 1, 'O', 1 );
	Ispit	ispit2(266, "Fizika I", 1, 622, 1, 'O', 1 );

	ispit1.addDodPodaci(2,3,4,'I', 9);

	ispit1.Print();
	ispit2.Print();
*/
/*
	ProblemData			Opt;

	Opt.addPredmet(353, "Matematièka analiza I", 1, 622, 1, 'O', 1 );
	Opt.addPredmet(266, "Fizika I", 1, 622, 1, 'O', 1 );

	cout << Opt.addPresjek(353,266,400) << endl;

	Opt.Print();
*/

	OptProblem		opt("predmet.txt", "nasprog1.txt", "presjek1.txt", "IspitiIstiDan.txt");

	srand(time(NULL));

	opt.Print();

	opt.Optimize();

	return 0;
}
