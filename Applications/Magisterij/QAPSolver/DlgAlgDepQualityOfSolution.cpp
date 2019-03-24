// DlgAlgDepQualityOfSolution.cpp : implementation file
//

#include "stdafx.h"
#include "qapsolver.h"

#include "DlgAlgDepQualityOfSolution.h"
#include "QAPCompareDoc.h"

#include <vector>

#include <Mathlib\Matrix.h>
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
// CDlgAlgDepQualityOfSolution dialog


CDlgAlgDepQualityOfSolution::CDlgAlgDepQualityOfSolution( CQAPCompareDoc *inpDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlgDepQualityOfSolution::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlgDepQualityOfSolution)
	m_nRepetitionNum = 0;
	//}}AFX_DATA_INIT

	pDoc = inpDoc;

	m_strPar[0] = _T("");
	m_strPar[1] = _T("");
	m_strPar[2] = _T("");
	m_strPar[3] = _T("");

	m_strValues[0] = _T("");
	m_strValues[1] = _T("");
	m_strValues[2] = _T("");
	m_strValues[3] = _T("");
	
	m_fFrom[0] = 0.0f;
	m_fFrom[1] = 0.0f;
	m_fFrom[2] = 0.0f;
	m_fFrom[3] = 0.0f;

	m_fStep[0] = 0.0f;
	m_fStep[1] = 0.0f;
	m_fStep[2] = 0.0f;
	m_fStep[3] = 0.0f;

	m_fTo[0] = 0.0f;
	m_fTo[1] = 0.0f;
	m_fTo[2] = 0.0f;
	m_fTo[3] = 0.0f;

	for( int i=0; i<10; i++ )
		m_fTime[i] = 100;

	m_nRepetitionNum = 3;

	m_ParNum = 0;
}


void CDlgAlgDepQualityOfSolution::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlgDepQualityOfSolution)
	DDX_Control(pDX, IDC_ALG_TYPE, m_ctrlSelAlgType);
	DDX_Text(pDX, IDC_REPETITION_NUM, m_nRepetitionNum);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_PARNAME1, m_strPar[0]);
	DDX_Text(pDX, IDC_PARNAME2, m_strPar[1]);
	DDX_Text(pDX, IDC_PARNAME3, m_strPar[2]);
	DDX_Text(pDX, IDC_PARNAME4, m_strPar[3]);
	DDX_Text(pDX, IDC_PAR_VALUES1, m_strValues[0]);
	DDX_Text(pDX, IDC_PAR_VALUES2, m_strValues[1]);
	DDX_Text(pDX, IDC_PAR_VALUES3, m_strValues[2]);
	DDX_Text(pDX, IDC_PAR_VALUES4, m_strValues[3]);
	DDX_Text(pDX, IDC_RANGE_FROM1, m_fFrom[0]);
	DDX_Text(pDX, IDC_RANGE_FROM2, m_fFrom[1]);
	DDX_Text(pDX, IDC_RANGE_FROM3, m_fFrom[2]);
	DDX_Text(pDX, IDC_RANGE_FROM4, m_fFrom[3]);
	DDX_Text(pDX, IDC_RANGE_STEP1, m_fStep[0]);
	DDX_Text(pDX, IDC_RANGE_STEP2, m_fStep[1]);
	DDX_Text(pDX, IDC_RANGE_STEP3, m_fStep[2]);
	DDX_Text(pDX, IDC_RANGE_STEP4, m_fStep[3]);
	DDX_Text(pDX, IDC_RANGE_TO1, m_fTo[0]);
	DDX_Text(pDX, IDC_RANGE_TO2, m_fTo[1]);
	DDX_Text(pDX, IDC_RANGE_TO3, m_fTo[2]);
	DDX_Text(pDX, IDC_RANGE_TO4, m_fTo[3]);
	DDX_Text(pDX, IDC_SOL_VALUE1, m_fTime[0]);
	DDX_Text(pDX, IDC_SOL_VALUE2, m_fTime[1]);
	DDX_Text(pDX, IDC_SOL_VALUE3, m_fTime[2]);
	DDX_Text(pDX, IDC_SOL_VALUE4, m_fTime[3]);
	DDX_Text(pDX, IDC_SOL_VALUE5, m_fTime[4]);
	DDX_Text(pDX, IDC_SOL_VALUE6, m_fTime[5]);
	DDX_Text(pDX, IDC_SOL_VALUE7, m_fTime[6]);
	DDX_Text(pDX, IDC_SOL_VALUE8, m_fTime[7]);
	DDX_Text(pDX, IDC_SOL_VALUE9, m_fTime[8]);
	DDX_Text(pDX, IDC_SOL_VALUE10, m_fTime[9]);
}


BEGIN_MESSAGE_MAP(CDlgAlgDepQualityOfSolution, CDialog)
	//{{AFX_MSG_MAP(CDlgAlgDepQualityOfSolution)
	ON_CBN_SELCHANGE(IDC_ALG_TYPE, OnSelchangeAlgType)
	ON_BN_CLICKED(IDC_START_CMD, OnStartAlgDepQualityCmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlgDepQualityOfSolution message handlers

void CDlgAlgDepQualityOfSolution::OnSelchangeAlgType() 
{
	switch( this->m_ctrlSelAlgType.GetCurSel() ) 
	{
		// Simple tabu search
		case 0 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "";
							m_strPar[2] = "";
							m_strPar[3] = "";
							
							m_ParNum = 1;

							break;
		// Simple diversify
		case 1 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Aspiration T:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							
							break;
		// Robust
		case 2 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Delta t.l.size:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;

							break;
		// Robust diversify
		case 3 : 	m_strPar[0] = "Tabu list size:"; 
							m_strPar[1] = "Delta t.l.size:";
							m_strPar[2] = "Aspiration T:";
							m_strPar[3] = "";

							m_ParNum = 3;
							break;
		// Simple Burkard-Rendl
		case 4 : 	m_strPar[0] = "T0 :"; 
							m_strPar[1] = "Temp.change.factor :";
							m_strPar[2] = "Iter.on temp:";
							m_strPar[3] = "";

							m_ParNum = 3;
							break;
		// Sim.ann. automated
		case 5 : 	m_strPar[0] = "Accept higher prob."; 
							m_strPar[1] = "Temp.change factor";
							m_strPar[2] = "Iter.on temp:";
							m_strPar[3] = "";

							m_ParNum = 3;
							break;
		// Wilhelm-Ward
		case 6 : 	m_strPar[0] = "Epoch num:"; 
							m_strPar[1] = "Eps: ";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							break;
		// Connoly
		case 7 : 	m_strPar[0] = "T0;"; 
							m_strPar[1] = "";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 1;
							break;
		// Automated Connoly
		case 8 : 	m_strPar[0] = ""; 
							m_strPar[1] = "";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 0;
							break;
		// 3-tournament selection
		case 9 : 	m_strPar[0] = "Pop.size:"; 
							m_strPar[1] = "Mutation prob. ";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							break;
		// FFGA
		case 10: 	m_strPar[0] = "Per generation:"; 
							m_strPar[1] = "R:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							break;
		// Greedy GA
		case 11: 	m_strPar[0] = "Immigration rate:"; 
							m_strPar[1] = "Local search rate:";
							m_strPar[2] = "";
							m_strPar[3] = "";

							m_ParNum = 2;
							break;

	}
	UpdateData(FALSE);
}

BOOL CDlgAlgDepQualityOfSolution::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlSelAlgType.AddString("Tabu search - simple");
	m_ctrlSelAlgType.AddString("Tabu search - simple diversifying");
	m_ctrlSelAlgType.AddString("Tabu search - robust");
	m_ctrlSelAlgType.AddString("Tabu search - robust diversifying");

	m_ctrlSelAlgType.AddString("Sim.ann. - Simple Burkard-Rendl");
	m_ctrlSelAlgType.AddString("Sim.ann. - Automated");
	m_ctrlSelAlgType.AddString("Sim.ann. - Wilhelm-Ward alg");
	m_ctrlSelAlgType.AddString("Sim.ann. - Connoly");
	m_ctrlSelAlgType.AddString("Sim.ann. - Automated Connoly");

	m_ctrlSelAlgType.AddString("Genetic - 3-tournament selection");
	m_ctrlSelAlgType.AddString("Genetic - FFGA");
	m_ctrlSelAlgType.AddString("Genetic - Greedy GA");
	
//	m_ctrlSelAlgType.AddString("GRASP");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlgDepQualityOfSolution::OnStartAlgDepQualityCmd() 
{
	FILE		*fp;
	char		fname[200];

	int		i, j, start;
	char	str[100], param[30];

	UpdateData();

	// najprije treba pokupiti parametre
	float		fPar[4][10];
	int			nValueNum[4];		// koliko ima vrijednosti za dani parametar

	for( i=0; i<m_ParNum; i++ ) {
		strcpy(str, LPCTSTR(m_strValues[i]) );

		// parsiramo string, oèekujemo da su vrijednosti odvojene zarezom
		j = 0;
		nValueNum[i] = 0;
		start = 0;
		while( str[j] != '\0' ) {
			if( str[j] == ',' ) {
				strncpy(param, str+start, j-start);
				
				fPar[i][nValueNum[i]++] = atof(param);
				memset(param,0,30);			// praznimo string

				start = j+1;
			}
			j++;
		}
	}

	IOptTerminator	*inpTerm;

	float		val, min, max, sum, sumsq, bestvalue;

	switch( this->m_ctrlSelAlgType.GetCurSel() ) 
	{
		int		i, j, k, l, rep, size;

		case 0:
			SimpleTabuSearchQAPSolver	*pQAP;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\TabuSearch-Simple_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP = new SimpleTabuSearchQAPSolver( size, inpTerm, fPar[0][0]);
					pQAP->setA(pDoc->vecA[i]);
					pQAP->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// za svaku kombinaciju parametara treba ponoviti izraèunavanje odreðeni broj putaž
					for( j=0; j<nValueNum[0]; j++ ) 
					{
						max = -1e10f;
						min =  1e10f;
						sum =  0.0f;
						sumsq = 0.0f;
						val =  0.0f;

						pQAP->setTabuListSize(fPar[0][j]);

						// ponavljamo optimizaciju odreðeni broj puta
						for( rep=0; rep<m_nRepetitionNum; rep++ )
						{
							IterOptContResWithSolutions<float, QAPSolution>	Res;
							pQAP->Optimize(Res);

							val = Res.getBestFuncValue();
							
							sum		+= val;
							sumsq += pow(bestvalue - val, 2);

							if( val < min )	min = val;
							if( val > max )	max = val;
						}

						// zapisujemo rezultate u datoteku
						fprintf(fp, "%d   %.0f   %.0f   %.1f   %5.2f\n", (int) fPar[0][j], min, max, sum/m_nRepetitionNum, sqrt(sumsq/m_nRepetitionNum)/bestvalue*100);
						fflush(fp);
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP;
				}
			}
			break;
		case 1:
			SimpleDiversifyTabuSearchQAPSolver	*pQAP1;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\TabuSearch-SimpleDiversify_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP1 = new SimpleDiversifyTabuSearchQAPSolver( size, inpTerm, fPar[0][0], fPar[1][0]);
					pQAP1->setA(pDoc->vecA[i]);
					pQAP1->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom aspiracijskog parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%d    ", (int) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP1->setTabuListSize(fPar[0][j]);
							pQAP1->setAspirationParamT(fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
								pQAP1->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
						}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP1;
				}
			}
			break;
		case 2:
			RobustTabuSearchQAPSolver	*pQAP2;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\TabuSearch-Robust_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP2 = new RobustTabuSearchQAPSolver( size, inpTerm, fPar[0][0], fPar[1][0]);
					pQAP2->setA(pDoc->vecA[i]);
					pQAP2->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom delta tabu list size parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%d    ", (int) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP2->setTabuListSize(fPar[0][j]);
							pQAP2->setDeltaTabuListSize(fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
								pQAP2->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
					}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP2;
				}
			}
			break;
		case 3:
			RobustDiversifyTabuSearchQAPSolver	*pQAP3;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\TabuSearch-RobustDiversify_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP3 = new RobustDiversifyTabuSearchQAPSolver( size, inpTerm, fPar[0][0], fPar[1][0], fPar[2][0]);
					pQAP3->setA(pDoc->vecA[i]);
					pQAP3->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom delta tabu list size parametra
					fprintf(fp, "      ");
					// u prvi redak stavljamo aspiracijski parametar
					int		m;
					for( k=0; k<nValueNum[2]; k++ ) {
						// ali ga ponavljamo više puta (onoliko koliko ima parametara za delta)
						for( m=0; m<4; m++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							for( l=0; l<nValueNum[1]; l++ )
								fprintf(fp, "%5d ", (int) fPar[2][k] );
					}
					fprintf(fp, "\n");
					// sada zapisujemo parametar delta
					for( m=0; m<nValueNum[2]; m++ )
						for( k=0; k<nValueNum[1]; k++ ) 
							for( l=0; l<4; l++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
								fprintf(fp, "%5d ", (int) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( l=0; l<nValueNum[2]; l++ )
							for( k=0; k<nValueNum[1]; k++ ) 
							{
								max = -1e10f;
								min =  1e10f;
								sum =  0.0f;
								sumsq = 0.0;
								val =  0.0f;

								pQAP3->setTabuListSize((int) fPar[0][j]);
								pQAP3->setDeltaTabuListSize((int) fPar[1][j]);
								pQAP3->setAspirationParamT((int) fPar[2][l]);

								// ponavljamo optimizaciju odreðeni broj puta
								for( rep=0; rep<m_nRepetitionNum; rep++ )
								{
									IterOptContResWithSolutions<float, QAPSolution>	Res;
									pQAP3->Optimize(Res);

									val = Res.getBestFuncValue();
									
									sum += val;
									sumsq += pow(bestvalue - val, 2);

									if( val < min )	min = val;
									if( val > max )	max = val;
								}

								// zapisujemo rezultate u datoteku
								fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
								fflush(fp);
							}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP3;
				}
			}
			break;
		case 4:
			QAPSolverSimpleSimAnnealing	*pQAP4;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\SA_BurkardRendl_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP4 = new QAPSolverSimpleSimAnnealing( size, inpTerm, NULL, fPar[0][0], fPar[1][0], (int) fPar[2][0]);
					pQAP4->setA(pDoc->vecA[i]);
					pQAP4->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom delta tabu list size parametra
					fprintf(fp, "      ");
					// u prvi redak stavljamo IterNumOnTemp
					int		m;
					for( k=0; k<nValueNum[2]; k++ ) {
						// ali ga ponavljamo više puta
						for( m=0; m<4; m++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							for( l=0; l<nValueNum[1]; l++ )
								fprintf(fp, "%5d ", (int) fPar[2][k] );
					}
					fprintf(fp, "\n");
					// sada zapisujemo parametar delta
					for( m=0; m<nValueNum[2]; m++ )
						for( k=0; k<nValueNum[1]; k++ ) 
							for( l=0; l<4; l++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
								fprintf(fp, "%.4f ", fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%f   ",  fPar[0][j] );

						for( l=0; l<nValueNum[2]; l++ )
							for( k=0; k<nValueNum[1]; k++ ) 
							{
								max = -1e10f;
								min =  1e10f;
								sum =  0.0f;
								sumsq = 0.0;
								val =  0.0f;

								pQAP4->SetT0(fPar[0][j]);
								pQAP4->SetTempChangeFactor(fPar[1][j]);
								pQAP4->SetIterNumOnTemp((int) fPar[2][l]);

								// ponavljamo optimizaciju odreðeni broj puta
								for( rep=0; rep<m_nRepetitionNum; rep++ )
								{
									IterOptContResWithSolutions<float, QAPSolution>	Res;
									pQAP4->Optimize(Res);

									val = Res.getBestFuncValue();
									
									sum += val;
									sumsq += pow(bestvalue - val, 2);

									if( val < min )	min = val;
									if( val > max )	max = val;
								}

								// zapisujemo rezultate u datoteku
								fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
								fflush(fp);
							}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP4;
				}
			}
			break;
		case 5:
			QAPSolverAutomatedSimAnnealing	*pQAP5;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\SA_Automated_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP5 = new QAPSolverAutomatedSimAnnealing( size, inpTerm, NULL, fPar[0][0], fPar[1][0], (int) fPar[2][0]);
					pQAP5->setA(pDoc->vecA[i]);
					pQAP5->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom delta tabu list size parametra
					fprintf(fp, "      ");
					// u prvi redak stavljamo aspiracijski parametar
					int		m;
					for( k=0; k<nValueNum[2]; k++ ) {
						// ali ga ponavljamo više puta (onoliko koliko ima parametara za delta)
						for( m=0; m<4; m++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							for( l=0; l<nValueNum[1]; l++ )
								fprintf(fp, "%5d ", (int) fPar[2][k] );
					}
					fprintf(fp, "\n");
					// sada zapisujemo parametar delta
					for( m=0; m<nValueNum[2]; m++ )
						for( k=0; k<nValueNum[1]; k++ ) 
							for( l=0; l<4; l++ )		// ispisujemo 4 puta jer æemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
								fprintf(fp, "%.4f ", fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite AcceptHigherProb
					{
						fprintf(fp, "%.3f ", fPar[0][j] );

						for( l=0; l<nValueNum[2]; l++ )
							for( k=0; k<nValueNum[1]; k++ ) 
							{
								max = -1e10f;
								min =  1e10f;
								sum =  0.0f;
								sumsq = 0.0;
								val =  0.0f;

								pQAP5->SetAcceptHigherProb(fPar[0][j]);
								pQAP5->SetTempChangeFactor(fPar[1][j]);
								pQAP5->SetPermNum((int) fPar[2][l]);

								// ponavljamo optimizaciju odreðeni broj puta
								for( rep=0; rep<m_nRepetitionNum; rep++ )
								{
									IterOptContResWithSolutions<float, QAPSolution>	Res;
									pQAP5->Optimize(Res);

									val = Res.getBestFuncValue();
									
									sum += val;
									sumsq += pow(bestvalue - val, 2);

									if( val < min )	min = val;
									if( val > max )	max = val;
								}

								// zapisujemo rezultate u datoteku
								fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
								fflush(fp);
							}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP5;
				}
			}
			break;
		case 6:
			QAPSolverWWSimAnnealing		*pQAP6;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\SA_WilhelmWard_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP6 = new QAPSolverWWSimAnnealing( size, inpTerm, NULL, (int) fPar[0][0], (float) fPar[1][0], 0);
					pQAP6->setA(pDoc->vecA[i]);
					pQAP6->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom aspiracijskog parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%6.4f    ", (float) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP6->SetEpochIterNum(fPar[0][j]);
							pQAP6->SetEps(fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
								pQAP6->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
						}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP6;
				}
			}
			break;
		case 7 :
			QAPSolverConnSimAnnealing		*pQAP7;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\SA_Conn_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP7 = new QAPSolverConnSimAnnealing( size, inpTerm, NULL, -1, -1, fPar[0][0], 0.1f);
					pQAP7->setA(pDoc->vecA[i]);
					pQAP7->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// za svaku kombinaciju parametara treba ponoviti izraèunavanje odreðeni broj putaž
					for( j=0; j<nValueNum[0]; j++ ) 
					{
						max = -1e10f;
						min =  1e10f;
						sum =  0.0f;
						sumsq = 0.0f;
						val =  0.0f;

						pQAP7->setT0(fPar[0][j]);

						// ponavljamo optimizaciju odreðeni broj puta
						for( rep=0; rep<m_nRepetitionNum; rep++ )
						{
							IterOptContResWithSolutions<float, QAPSolution>	Res;
							pQAP7->Optimize(Res);

							val = Res.getBestFuncValue();
							
							sum		+= val;
							sumsq += pow(bestvalue - val, 2);

							if( val < min )	min = val;
							if( val > max )	max = val;
						}

						// zapisujemo rezultate u datoteku
						fprintf(fp, "%d   %.0f   %.0f   %.1f   %5.2f\n", (int) fPar[0][j], min, max, sum/m_nRepetitionNum, sqrt(sumsq/m_nRepetitionNum)/bestvalue*100);
						fflush(fp);
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP7;
				}
			}
			break;
		case 9:
			QAPGenAlgTournamentSelection	*pQAP9;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\GA_Tournament_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP9 = new QAPGenAlgTournamentSelection( size, inpTerm, NULL, (int) fPar[0][0], (float) fPar[1][0]);
					pQAP9->setA(pDoc->vecA[i]);
					pQAP9->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom aspiracijskog parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%6.4f    ", (float) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP9->setPopulationSize(fPar[0][j]);
							pQAP9->setMutationProb(fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
								pQAP9->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
						}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP9;
				}
			}
			break;
		case 10:
			QAPGenAlgFFGA	*pQAP10;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\GA_FFGA_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP10 = new QAPGenAlgFFGA( size, inpTerm, NULL, 50, (int) fPar[0][0], (float) fPar[1][0]);
					pQAP10->setA(pDoc->vecA[i]);
					pQAP10->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom aspiracijskog parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%6.4f    ", (float) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP10->setPerGeneration(fPar[0][j]);
							pQAP10->setR(fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
+								pQAP10->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
						}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP10;
				}
			}
			break;
		case 11:
			QAPGenAlgGreedy	*pQAP11;

			// ponavljati æemo odreðeni broj puta
			for( i=0; i<10; i++ ) {
				if( pDoc->vecProblemDefined[i] == TRUE ) 
				{
					size = pDoc->vecA[i].RowNum();
					
					sprintf(fname, "C:\\QAP\\GA_Greedy_%03d.txt", size);
					fp = fopen(fname, "w");

					inpTerm = new TimeOptTerminator(m_fTime[i]);
					
					pQAP11 = new QAPGenAlgGreedy( size, inpTerm, NULL, 50, (int) fPar[0][0], (int) fPar[1][0]);
					pQAP11->setA(pDoc->vecA[i]);
					pQAP11->setB(pDoc->vecB[i]);
							
					bestvalue = pDoc->vecBestKnownSol[i].getValue();

					// najprije u datoteku treba zapisati prvi redak s opisom aspiracijskog parametra
					fprintf(fp, "      ");
					for( k=0; k<nValueNum[1]; k++ ) 
						for( l=0; l<4; l++ )		// ispisujemo 4 puta je ræemo za svaku vrijednost imati 4 stupca (min,max,avg,std)
							fprintf(fp, "%d  ", (int) fPar[1][k] );
					fprintf(fp, "\n");

					for( j=0; j<nValueNum[0]; j++ ) // ide kroz razlièite velièine tabu liste
					{
						fprintf(fp, "%d   ", (int) fPar[0][j] );

						for( k=0; k<nValueNum[1]; k++ ) 
						{
							max = -1e10f;
							min =  1e10f;
							sum =  0.0f;
							sumsq = 0.0;
							val =  0.0f;

							pQAP11->setImmigration((int) fPar[0][j]);
							pQAP11->setLocalSearch((int) fPar[1][j]);

							// ponavljamo optimizaciju odreðeni broj puta
							for( rep=0; rep<m_nRepetitionNum; rep++ )
							{
								IterOptContResWithSolutions<float, QAPSolution>	Res;
								pQAP11->Optimize(Res);

								val = Res.getBestFuncValue();
								
								sum += val;
								sumsq += pow(bestvalue - val, 2);

								if( val < min )	min = val;
								if( val > max )	max = val;
							}

							// zapisujemo rezultate u datoteku
							fprintf(fp, "%.0f   %.0f   %.1f   %5.2f   ",  min, max, sum/m_nRepetitionNum,sqrt(sumsq/m_nRepetitionNum) / bestvalue * 100);
							fflush(fp);
						}
						fprintf(fp, "\n");
					}
					fclose(fp);

					delete inpTerm;
					delete pQAP11;
				}
			}
			break;
	}
}
