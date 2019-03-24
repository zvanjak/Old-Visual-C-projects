// QAPCompareDoc.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"
#include "QAPCompareDoc.h"

#include "DlgSetProblemInstances.h"
#include "DlgOptimizationTabuSearch.h"		// potrebno da bi se preveo SerializeInArchive
#include "DlgTimeToReachSol.h"
#include "DlgAlgDepQualityOfSolution.h"

#include <Optimization\Win32Serialize.h>
#include <QAP\QAP.h>
#include <Optimization\Optimization.h>
#include <QAP\QAPTabuSearch.h>
#include <QAP\QAPGeneticAlg.h>
#include <QAP\QAPSimAnnealing.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareDoc

IMPLEMENT_DYNCREATE(CQAPCompareDoc, CDocument)

CQAPCompareDoc::CQAPCompareDoc()
{
	int		i;

	vecA.resize(10);
	vecB.resize(10);

	vecProblemDefined.resize(10);

	vecBestKnownSol.resize(10);
	vecBestKnownSolLoaded.resize(10);

	for( i=0; i<10; i++ ) {
		strFileName[i] = "";
		vecBestKnownSolLoaded[i] = false;
		vecProblemDefined[i] = FALSE;
	}


	char	fileProblem1[10][50] = { 
			"C:\\QAP\\had12.dat",
			"C:\\QAP\\had20.dat",
			"C:\\QAP\\nug20.dat",
			"C:\\QAP\\nug30.dat",
			"C:\\QAP\\tai30b.dat",
			"C:\\QAP\\tai40b.dat",
			"C:\\QAP\\tai50b.dat",
			"C:\\QAP\\tai60a.dat",
			"C:\\QAP\\tai80a.dat",
			"C:\\QAP\\wil100.dat"
	};
	char	fileSol1[10][50] = {
			"C:\\QAP\\had12.sln",
			"C:\\QAP\\had20.sln",
			"C:\\QAP\\nug20.sln",
			"C:\\QAP\\nug30.sln",
			"C:\\QAP\\tai30b.sln",
			"C:\\QAP\\tai40b.sln",
			"C:\\QAP\\tai50b.sln",
			"C:\\QAP\\tai60a.sln",
			"C:\\QAP\\tai80a.sln",
			"C:\\QAP\\wil100.sln"
		};
	int		size1[10] = { 12, 20, 20, 30, 30, 40, 50, 60, 80, 100 };
	float	time1[10] = { 
			20,
			20,
			30,
			60,
			100,
			200,
			250,
			450,
			900,
			1600
		};

	for( i=0; i<10; i++ ) {
		strcpy(fileProblem[i], fileProblem1[i]);
		strcpy(fileSol[i], fileSol1[i]);
		
		time[i] = time1[i];
		size[i] = size1[i];
	}

}

BOOL CQAPCompareDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CQAPCompareDoc::~CQAPCompareDoc()
{
}


BEGIN_MESSAGE_MAP(CQAPCompareDoc, CDocument)
	//{{AFX_MSG_MAP(CQAPCompareDoc)
	ON_COMMAND(ID_FILE_SET_PROBLEM_INSTANCES, OnSetProblemInstances)
	ON_COMMAND(ID_ALG_DEPENDENCE_TIME, OnAlgDepTimeToReachSolution)
	ON_COMMAND(ID_ALG_DEPENDENCE_QUALITY, OnAlgDepQualityOfSolution)
	ON_COMMAND(ID_COMPARE_TABU_SEARCH, OnCompareTabuSearch)
	ON_COMMAND(ID_COMPARE_SIM_ANN, OnCompareSimAnn)
	ON_COMMAND(ID_COMPARE_GENETIC, OnCompareGenetic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareDoc diagnostics

#ifdef _DEBUG
void CQAPCompareDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQAPCompareDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareDoc serialization

void CQAPCompareDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		for( int i=0; i<10; i++ ) {
			ar << strSize[i];
			ar << strFileName[i];

			ar << vecProblemDefined[i];

			ar << vecA[i];
			ar << vecB[i];

			ar << vecBestKnownSol[i];
			ar << vecBestKnownSolLoaded[i];
		}
	}
	else {
		for( int i=0; i<10; i++ ) {
			ar >> strSize[i];
			ar >> strFileName[i];

			BOOL		in;
			ar >> in;
			vecProblemDefined[i] = in;

			ar >> vecA[i];
			ar >> vecB[i];

			ar >> vecBestKnownSol[i];
			ar >> vecBestKnownSolLoaded[i];
		}
	}
/*
	SerializeInArchive< IterOptContResWithSolutions<float, QAPSolution> >(ar, vecSol);
	SerializeInArchive(ar, vecAlgDesc );
*/
}

/////////////////////////////////////////////////////////////////////////////
// CQAPCompareDoc commands

void CQAPCompareDoc::OnSetProblemInstances() 
{
	CDlgSetProblemInstances		dlg(this);

	int  i;

	for( i=0; i<10; i++ ) {
		dlg.m_strFile[i] = strFileName[i];
		dlg.m_strLabel[i] = strSize[i];
	}

	if( dlg.DoModal() == IDOK ) {
		for( i=0; i<10; i++ ) {
			strFileName[i] = dlg.m_strFile[i];
			strSize[i] = dlg.m_strLabel[i];
		}

		SetModifiedFlag(TRUE);
	}
}

void CQAPCompareDoc::OnAlgDepTimeToReachSolution() 
{
	CDlgTimeToReachSol			dlg(this);

	dlg.DoModal();
}

void CQAPCompareDoc::OnAlgDepQualityOfSolution() 
{
	CDlgAlgDepQualityOfSolution	dlg(this);

	dlg.DoModal();
}

bool LoadSolution( char *strFileName, int *outSize, float *outValue, QAPSolution &outSol )
{
	FILE *fp;

	if( (fp=fopen(strFileName, "r")) != NULL ) {
		int			Size;

		fscanf(fp, "%d", &Size);
		fscanf(fp, "%f", outValue);
		
		int		num = 0;

		outSol.Resize(Size);
		outSol.setValue(*outValue);
		for( int i=1; i<=Size; i++ )
			num += fscanf(fp, "%d", &outSol[i] );

		if( num == Size )
			return true;
	}

	return false;
}

void CQAPCompareDoc::OnCompareSimAnn() 
{
	Math::Matrix<float>		*A;
	Math::Matrix<float>		*B;

	int						i, rep, dummy;
	float					min, sumsq, val, bestvalue;
	QAPSolution		Sol;

	TimeOptTerminator		*inpTerm;
	
	FILE	*fp;

	fp = fopen("C:\\QAP\\SA.txt", "w");

	for( i=0; i<10; i++ ) {
		fprintf(fp, "\n %d  ", size[i]);

		A = new Math::Matrix<float>(size[i], size[i]);
		B = new Math::Matrix<float>(size[i], size[i]);

		LoadProblem(fileProblem[i], &dummy, A, B);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja matrice problema !!!");
		
		LoadSolution(fileSol[i], &dummy, &bestvalue, Sol);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja rješenja problema !!!");

		/////////////////////////////////////////////////////////////////////////////////////
		QAPSolverSimpleSimAnnealing		*pQAP1;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		float T0;
		if( size[i] >= 50 )
			T0 = 100;
		else
			T0 = 50;

		pQAP1 = new QAPSolverSimpleSimAnnealing(size[i], inpTerm, NULL, 0.9999f, T0, 100);
		pQAP1->setA(*A);
		pQAP1->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP1->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		
		delete inpTerm;
		delete pQAP1;
		/////////////////////////////////////////////////////////////////////////////////////
		QAPSolverAutomatedSimAnnealing		*pQAP2;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP2 = new QAPSolverAutomatedSimAnnealing(size[i], inpTerm, NULL, 0.999, 0.9999, 200);
		pQAP2->setA(*A);
		pQAP2->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP2->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP2;
		/////////////////////////////////////////////////////////////////////////////////////
		QAPSolverWWSimAnnealing		*pQAP3;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP3 = new QAPSolverWWSimAnnealing(size[i], inpTerm,NULL, 60, 0.01f, 50);
		pQAP3->setA(*A);
		pQAP3->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP3->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP3;

		/////////////////////////////////////////////////////////////////////////////////////
		QAPSolverConnSimAnnealing		*pQAP4;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP4 = new QAPSolverConnSimAnnealing(size[i], inpTerm, NULL, -1, -1, 100, 0.1f);
		pQAP4->setA(*A);
		pQAP4->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP4->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP4;

		/////////////////////////////////////////////////////////////////////////////////////
		delete A;
		delete B;
	}
}

void CQAPCompareDoc::OnCompareTabuSearch() 
{
	int		TLSize1[10] = { 25, 25, 25, 20, 30, 25, 30, 25, 30, 30 };
	int		TLSize2[10] = { 30, 25, 25, 20, 20, 25, 25, 20, 40, 40 };
	int		TLSize3[10] = { 35, 35, 35, 35, 35, 40, 40, 40, 40, 40 };
	int		TLSize4[10] = { 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 };
	
	int		AspPar[10] = { 500, 500, 1000, 1000, 2000, 2000, 4000, 4000, 6000, 8000 };
	int		TLDelta[10] = { 5, 10, 10, 10, 10, 10, 15, 15, 15, 15 };

	Math::Matrix<float>		*A;
	Math::Matrix<float>		*B;

	int						i, rep, dummy;
	float					min, sumsq, val, bestvalue;
	QAPSolution		Sol;

	TimeOptTerminator		*inpTerm;
	
	FILE	*fp;

	fp = fopen("C:\\QAP\\TabuAlg.txt", "w");

	for( i=0; i<10; i++ ) {
		fprintf(fp, "\n %d  ", size[i]);

		A = new Math::Matrix<float>(size[i], size[i]);
		B = new Math::Matrix<float>(size[i], size[i]);

		LoadProblem(fileProblem[i], &dummy, A, B);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja matrice problema !!!");
		
		LoadSolution(fileSol[i], &dummy, &bestvalue, Sol);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja rješenja problema !!!");

		/////////////////////////////////////////////////////////////////////////////////////
		SimpleTabuSearchQAPSolver		*pQAP1;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP1 = new SimpleTabuSearchQAPSolver(size[i], inpTerm, TLSize1[i]);
		pQAP1->setA(*A);
		pQAP1->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP1->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		
		delete inpTerm;
		delete pQAP1;
		/////////////////////////////////////////////////////////////////////////////////////
		SimpleDiversifyTabuSearchQAPSolver		*pQAP2;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP2 = new SimpleDiversifyTabuSearchQAPSolver(size[i], inpTerm, TLSize2[i], AspPar[i]);
		pQAP2->setA(*A);
		pQAP2->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP2->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP2;
		/////////////////////////////////////////////////////////////////////////////////////
		RobustTabuSearchQAPSolver		*pQAP3;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP3 = new RobustTabuSearchQAPSolver(size[i], inpTerm, TLSize3[i], TLDelta[i]);
		pQAP3->setA(*A);
		pQAP3->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP3->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP3;

		/////////////////////////////////////////////////////////////////////////////////////
		RobustDiversifyTabuSearchQAPSolver		*pQAP4;

		inpTerm = new TimeOptTerminator(time[i]*1000);

		pQAP4 = new RobustDiversifyTabuSearchQAPSolver(size[i], inpTerm, TLSize4[i], TLDelta[i], AspPar[i]);
		pQAP4->setA(*A);
		pQAP4->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP4->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP4;

		/////////////////////////////////////////////////////////////////////////////////////
		delete A;
		delete B;
	}
}

void CQAPCompareDoc::OnCompareGenetic() 
{
	Math::Matrix<float>		*A;
	Math::Matrix<float>		*B;

	int						i, rep, dummy;
	float					min, sumsq, val, bestvalue;
	QAPSolution		Sol;

	TimeOptTerminator		*inpTerm;
	
	FILE	*fp;

	fp = fopen("C:\\QAP\\GA_Alg2.txt", "w");

	for( i=7; i<10; i++ ) {
		fprintf(fp, "\n %d  ", size[i]);

		A = new Math::Matrix<float>(size[i], size[i]);
		B = new Math::Matrix<float>(size[i], size[i]);

		LoadProblem(fileProblem[i], &dummy, A, B);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja matrice problema !!!");
		
		LoadSolution(fileSol[i], &dummy, &bestvalue, Sol);
		if( dummy != size[i] ) 
			AfxMessageBox("Greška kod uèitavanja rješenja problema !!!");

		/////////////////////////////////////////////////////////////////////////////////////
		QAPGenAlgTournamentSelection		*pQAP1;

		inpTerm = new TimeOptTerminator(time[i] * 1000);

		pQAP1 = new QAPGenAlgTournamentSelection(size[i], inpTerm, NULL, 50, 0.01f);
		pQAP1->setA(*A);
		pQAP1->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP1->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		
		delete inpTerm;
		delete pQAP1;
		/////////////////////////////////////////////////////////////////////////////////////
		QAPGenAlgFFGA		*pQAP2;

		inpTerm = new TimeOptTerminator(time[i] * 1000);

		pQAP2 = new QAPGenAlgFFGA(size[i], inpTerm, NULL, 50, 10, 1.3f);
		pQAP2->setA(*A);
		pQAP2->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP2->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP2;
		/////////////////////////////////////////////////////////////////////////////////////
		QAPGenAlgGreedy		*pQAP3;

		inpTerm = new TimeOptTerminator(time[i] * 1000);

		int		immrate;

		if( size[i] <= 30 )
			immrate = 10;
		else if( size[i] <= 80 )
			immrate = 20;
		else
			immrate = 30;

		pQAP3 = new QAPGenAlgGreedy(size[i], inpTerm, NULL, 50, immrate, 100);
		pQAP3->setA(*A);
		pQAP3->setB(*B);

		min		=  1e15f;
		sumsq = 0.0;
		val		=  0.0f;

		for( rep=0; rep<5; rep++ )
		{
			IterOptContResWithSolutions<float, QAPSolution>	Res;
			pQAP3->Optimize(Res);

			val = Res.getBestFuncValue();
			
			sumsq += pow(bestvalue - val, 2);

			if( val < min )	min = val;
		}
		fprintf(fp, "%.0f   %5.2f  ",  min, sqrt(sumsq/5) / bestvalue * 100);
		fflush(fp);

		delete inpTerm;
		delete pQAP3;

		/////////////////////////////////////////////////////////////////////////////////////
		delete A;
		delete B;
	}	
}
