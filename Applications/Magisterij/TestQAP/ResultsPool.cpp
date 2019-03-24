#include "GeneticAlgNew.h"
#include "stdafx.h"

bool	ResultsPool::addData( int IterNum, vector<float>& Res ) {
	mapCromProgress[IterNum] = Res;

	return true;
}

bool	ResultsPool::getIterationResults( int IterNum, vector<float>& Res )
{
	std::map<int,std::vector<float> >::const_iterator	p;

	p = mapCromProgress.find(IterNum);
	if( p != mapCromProgress.end() ) {
		Res = p->second;
		return true;
	}

	return false;
}

void	ResultsPool::Print()
{
	std::map<int,std::vector<float> >::const_iterator	p;

	for( p=mapCromProgress.begin(); p!=mapCromProgress.end(); ++p )
	{
		printf("\n Iteration num = %d\n", p->first);
		
		const vector<float>& Res = p->second;
		for( int i=0; i<Res.size(); i++ )
			printf(" %f \n", Res[i] );
	}
}
