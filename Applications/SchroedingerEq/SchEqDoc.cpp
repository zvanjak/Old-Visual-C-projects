// SchEqDoc.cpp : implementation of the CSchEqDoc class
//

#include "stdafx.h"
#include "SchroedingerEq.h"

#include "SchEqDoc.h"

#include "DlgDefineParameters.h"
#include "DlgPerformIntegration.h"
#include "DlgViewResults.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Globalne varijable za IntFunc
double		Globa1, Globa2, Globb1, Globb2, GlobV0;

/////////////////////////////////////////////////////////////////////////////
// CSchEqDoc

IMPLEMENT_DYNCREATE(CSchEqDoc, CDocument)

BEGIN_MESSAGE_MAP(CSchEqDoc, CDocument)
	//{{AFX_MSG_MAP(CSchEqDoc)
	ON_COMMAND(ID_DEFINE_PARAMETERS, OnDefineParameters)
	ON_COMMAND(ID_PERFORM_INTEGRATION, OnPerformIntegration)
	ON_COMMAND(ID_VIEW_RESULTS, OnViewResults)
	ON_COMMAND(ID_OPTIONS, OnViewOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchEqDoc construction/destruction

CSchEqDoc::CSchEqDoc() : prob(0, 2, 0.8, 1.2, 5.0)
{
	a1 = 0;
	a2 = 2;
	b1 = 0.8f;
	b2 = 1.2f;
	V0 = 5;

	SetPotentialData();
	bPotAdded = false;
	bPotChanged = true;

	bClearAll = false;

	bViewNumInt = true;
}

CSchEqDoc::~CSchEqDoc()
{
}

BOOL CSchEqDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSchEqDoc serialization

void CSchEqDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSchEqDoc diagnostics

#ifdef _DEBUG
void CSchEqDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSchEqDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchEqDoc commands

void CSchEqDoc::OnDefineParameters() 
{
	CDlgDefineParameters		Dlg;
	float		oa1, oa2, ob1, ob2, oV0;

	// pamtimo stare vrijednosti
	Dlg.m_V0 = oV0 = V0;

	Dlg.m_a1 = oa1 = a1;
	Dlg.m_a2 = oa2 = a2;
	Dlg.m_b1 = ob1 = b1;
	Dlg.m_b2 = ob2 = b2;

	if( Dlg.DoModal() == IDOK ) {
		prob.SetData(Dlg.m_a1, Dlg.m_a2, Dlg.m_b1, Dlg.m_b2, Dlg.m_V0);

		a1 = Dlg.m_a1;
		a2 = Dlg.m_a2;
		b1 = Dlg.m_b1;
		b2 = Dlg.m_b2;
		V0 = Dlg.m_V0;
		
		// ako su se promijeniti parametri potencijala
		if( a1 != oa1 || a2 != oa2 || b1 != ob1 || b2 != ob2 || V0 != oV0 ) {
			ClearResults();
			SetPotentialData();
			bPotChanged = true;

			UpdateAllViews(NULL);
		}
	}
}

// Globalne varijable
void IntFunc( double x, Vector<double> &y, Vector<double>	&dydx )
{
	double		V;

	if( x>Globb1 && x < Globb2 )	V = GlobV0;
	else	V = 0;

	dydx[1] = y[2];
	dydx[2] = 2 * (V-y[3]) * y[1];
	dydx[3] = 0.0;
}

void CSchEqDoc::OnPerformIntegration() 
{
	CDlgPerformIntegration		dlg;

	Vector<double>			YStart(3), YStart1(3), YStart2(3);
	
	dlg.m_fNorm = 1e-1;
	dlg.m_fStart = 0;
	dlg.m_fEnd	 = 10;
	dlg.m_fStep  = 0.5;

	if( dlg.DoModal() == IDOK ) 
	{
		int			nEnergy = 0;
		float		E0, EnergyVal[100];

//		ClearResults();
		if( dlg.m_fValues.IsEmpty() != TRUE ) {
			char		*pstr;

			pstr = dlg.m_fValues.GetBuffer(100);
			while( sscanf(pstr, "%f", &EnergyVal[nEnergy++]) > 0 ) {
				while( *pstr != '\0' && *pstr !=' ')
					pstr++;
				if( *pstr == ' ' )	pstr++;
				else break;
			}
		}
		else {
			for( nEnergy=0, E0=dlg.m_fStart; E0<=dlg.m_fEnd; E0+=dlg.m_fStep ) {
				EnergyVal[nEnergy++] = E0;
			}
		}

		for( int i=0; i<nEnergy; i++ ) {
			E0 = EnergyVal[i];
			prob.SetInitialCond(dlg.m_fNorm, E0);

			if( prob.Solve(YStart) == true ) 
			{
				YStart1[1] = 0;
				YStart1[2] = dlg.m_fNorm;		// možemo radi normalizacije
				YStart1[3] = YStart[1];

				YStart2[1] = 0;
				YStart2[2] = YStart[3];
				YStart2[3] = YStart[2];

				int				j, n, nok, nbad, kount, kmax;

				double		xf;
				double		*x;
				double		**y;
				float			*xout, *yout;

				xf = (a2-a1) / 2;
				
				kmax = 2000;
				x	= new double[kmax];
				y = new double *[3];
				for( j=0; j<3; j++ )
					y[j] = new double[kmax];
				y--;

				xout = new float[2*kmax];
				yout = new float[2*kmax];

				Globa1 = a1;
				Globa2 = a2;
				Globb1 = b1;
				Globb2 = b2;
				GlobV0 = V0;

				if( bViewNumInt == true ) {		//			Numerièko integriranje
					Math::ODEIntegrate<double>(YStart1, 3, a1, xf, 1e-8, 1e-3, 0, &nok, &nbad, 200, kount, x, y, 2 * (a2-a1) / kmax, IntFunc);
					// sada to treba prebaciti u xout i yout
					for( j=1; j<=kount; j++ ) {
						xout[j-1] = x[j];
						yout[j-1] = y[1][j];
					}
					n = kount;
					Math::ODEIntegrate<double>(YStart2, 3, a2, xf, 1e-8, 1e-3, 0, &nok, &nbad, 200, kount, x, y, 2 * (a2-a1) / kmax, IntFunc);
					for( j=kount; j>0; j-- ) {
						xout[n] = x[j];
						yout[n] = y[1][j];
						n++;
					}
//					AfxMessageBox("Num");
				}
				else {				// Raèun smetnje
					float		x0, dx;

					x0 = a1;
					dx = (a2-a1)/kmax;
					for( j=0; j<kmax; j++ ) {
						xout[j] = x0;
						yout[j] = CalcPerturbStateFunc(i+1, x0);
						x0 += dx;
					}
					n = kmax;
//					AfxMessageBox("Pert");
				}

				// za gustoæu vjerojatnosti i za odreðivanje normalizacije
				float		*ynorm = new float[2*kmax];
				for( j=0; j<n; j++ ) {
					ynorm[j] = yout[j] * yout[j];
				}

				// na redu je normalizacija
				// obaviti æemo aproksimativno numerièko integriranje
				float		sum, dx;
				sum = 0;
				for( j=1; j<n; j++ ) {
					dx = xout[j] - xout[j-1];
					sum += (ynorm[j] + ynorm[j-1]) / 2 * dx;
				}

				// prikaz gustoæe vjerojatnosti
				for( j=0; j<n; j++ ) 
					yout[j] = (yout[j] * yout[j]) / sum * V0;;
				// prikaz valnih funkcija
//				for( j=0; j<n; j++ ) 
//					yout[j] = yout[j] / sqrt(sum) * V0;;

				AddResult(YStart[1], YStart1, YStart2, n, xout, yout);

				delete ynorm;
			}
		}
	}

	UpdateAllViews(NULL);
}

void CSchEqDoc::OnViewResults() 
{
	CDlgViewResults		dlg;

	int			Num = vecEnergy.size();
	float		*pNum, *pBase, *pPert1, *pPert2;

	if( Num > 0 ) {
		pNum = new float[Num];
		pBase = new float[Num];
		pPert1 = new float[Num];
		pPert2 = new float[Num];
	}

	for( int i=0; i<Num; i++ ) {
		pNum[i] = vecEnergy[i];
		pBase[i] = prob.BaseStateFuncEnergy(i+1);
		pPert1[i] = CalcPerturbation1(i+1);
		pPert2[i] = CalcPerturbation2(i+1);
	}
	
	dlg.nLevelsNum = Num;
	dlg.pNum = pNum;
	dlg.pBase = pBase;
	dlg.pPerturb1 = pPert1;
	dlg.pPerturb2 = pPert2;

	dlg.DoModal();
}

float CSchEqDoc::CalcPerturbation1( int n ) {
	float		a, b, E0, dE;
	
	a = (prob.a2 - prob.a1);
	b = (prob.b2 - prob.b1);

	E0 = prob.BaseStateFuncEnergy(n);
	dE = prob.V0 / a * ( b - 2*a/(4*PI*n) * pow(-1,n) * sin(PI*n*b/a) );

	return E0 + dE;
}

float CSchEqDoc::CalcPerturbation2( int n ) 
{
/*
	int			m, count;
	float		a, b, E0, dE, x1, x2, L, h1, h2;

	a = (prob.a2 - prob.a1) / 2;
	L = 2 * a;
	b = (prob.b2 - prob.b1) / 2;

	E0 = CalcPerturbation1(n);

	count = 0;

	for( m=1; ;m++ ) {
		if( m != n ) {
			x1 = a - b;
			x2 = a + b;
			h1 = 1/(PI*(m-n)) * ( sin(PI*(m-n)*x2/L) - sin(PI*(m-n)*x1/L) );
			h2 = 1/(PI*(m+n)) * ( sin(PI*(m+n)*x2/L) - sin(PI*(m+n)*x1/L) );
			dE = V0 * (h1 - h2);

			E0 += dE*dE / (prob.BaseStateFuncEnergy(n) - prob.BaseStateFuncEnergy(m));

			if( count ++ > 20 )
				break;
		}
	}
*/

	int			p, l, k, count;
	float		a, b, E0, dE, h1, h2;
	
	a = (prob.a2 - prob.a1);
	b = (prob.b2 - prob.b1);
	dE = 0.0;

	E0 = CalcPerturbation1(n);

	count = 0;

	for( p=1; ; p++ ) {

		if( (p-n) % 2 == 0 && p != n) {
			l = (p+n) / 2;
			k = (p-n) / 2;
			h1 = 2./(p-n) * pow(-1,k) * sin(PI*(p-n)*b/2/a);
			h2 = 2./(p+n) * pow(-1,l) * sin(PI*(p+n)*b/2/a) ;
			dE = prob.V0 / PI *  (h1 - h2);
			E0 += dE*dE / (prob.BaseStateFuncEnergy(n) - prob.BaseStateFuncEnergy(p));
			
//			if( fabs(dE) / E0 < 0.001 )
//				break;
			if( count ++ > 20 )
				break;
		}
	}

	return E0;
}

float CSchEqDoc::CalcPerturbStateFunc( int n, float x )
{
		int			p, l, k, count;
		float		a, b, dE, IntMN, h1, h2, y;
		
		a = (prob.a2 - prob.a1);
		b = (prob.b2 - prob.b1);

		count = 0;
		y = prob.BaseStateFunc(n, x);

		for( p=1; ; p++ ) {

			if( (p-n) % 2 == 0 && p != n) {
				l = (p+n) / 2;
				k = (p-n) / 2;
				h1 = 2./(p-n) * pow(-1,k) * sin(PI*(p-n)*b/2/a);
				h2 = 2./(p+n) * pow(-1,l) * sin(PI*(p+n)*b/2/a) ;
				IntMN = prob.V0 / PI *  (h1 - h2);

				dE = (prob.BaseStateFuncEnergy(n) - prob.BaseStateFuncEnergy(p));
				y	 += IntMN /  dE * prob.BaseStateFunc(p,x);
				
				if( count++ > 20 )
					break;
			}
		}

		return y;
}

void CSchEqDoc::ClearResults() {
	vecEnergy.clear();
	vecYStart1.clear();
	vecYStart2.clear();

	for( int i=0; i<vecpXPsi.size(); i++ ) {
		delete []vecpXPsi[i];
		delete []vecpYPsi[i];
	}
	vecpXPsi.clear();
	vecpYPsi.clear();

	vecPntNum.clear();
	vecAdded.clear();
	
	bPotAdded = false;
	bClearAll = true;

	UpdateAllViews(NULL);
}

void CSchEqDoc::SetPotentialData() {
	int			i;
	float		dx, ddx, a1Exp, a2Exp, x;
	
	dx = a2 - a1;
	// iscrtavati æemo potencijala na podruèju 10% širem od same rupe
	a1Exp = a1 - fabs(dx * 0.1);
	a2Exp = a2 + fabs(dx * 0.1);
	ddx = (a2Exp - a1Exp) / POTFUNC_POINTS_NUM;

	for( i=0, x=a1Exp; i<POTFUNC_POINTS_NUM; i++, x+=ddx ) {
		xPot[i] = x;
		yPot[i] = prob.Potential(x);
		if( yPot[i] > 1e10 ) {		// ukoliko je tu potencijal beskonaèan
			if( V0 > 0 )
				yPot[i] = V0 * 2;
			else
				yPot[i] = 100;
		}
	}
}

float CalcAbsPercentageDiff( float x, float y ) {
	return fabs( (y - x) / x ) * 100;
}

template<class _Type>	void Swap( _Type &a, _Type &b )
{
	_Type	h;

	h = a;
	a = b;
	b = h;
}

bool CSchEqDoc::AddResult( double E, Vector<double> &Y1, Vector<double> &Y2, int n, float *pX, float *pY )
{
	int			i, j;
	bool		found;
/*
	float		*x, *y;

	x = new float[n+1];
	y = new float[n+1];
	for( i=0; i<n; i++ ) {
		x[i] = pY[i];
		y[i] = pY[i];
	}
*/
	if( vecEnergy.size() == 0 ) {
		vecEnergy.push_back(E);
		vecYStart1.push_back(Y1);
		vecYStart2.push_back(Y2);
		vecpXPsi.push_back(pX);
		vecpYPsi.push_back(pY);
		vecPntNum.push_back(n);
		vecAdded.push_back(false);
	}
	else {
		found = false;
		for( i=0; i<vecEnergy.size(); i++ ) {
			if( CalcAbsPercentageDiff( E, vecEnergy[i] ) < 5 ) {
				found = true;
				break;
			}
		}
		if( found == false ) {
			vecEnergy.push_back(E);
			vecYStart1.push_back(Y1);
			vecYStart2.push_back(Y2);
			vecpXPsi.push_back(pX);
			vecpYPsi.push_back(pY);
			vecPntNum.push_back(n);
			vecAdded.push_back(false);
		}
	}

/*
	else {
		std::vector<double>::iterator							iterE;
		std::vector< Vector<double> >::iterator		iter1, iter2;

		found = false;
		iterE	= vecEnergy.begin();
		iter1 = vecYStart1.begin();
		iter2 = vecYStart2.begin();

		if( E < *iterE ) {		// da li dolazi na poèetak
			vecEnergy.insert(iterE, E);
			vecYStart1.insert(iter1, Y1);
			vecYStart2.insert(iter1, Y2);
		}
		else {
			for( ; iterE != vecEnergy.end(); iterE++ ) {
				if( E > *iterE ) 
				{
					if( iterE+1 == vecEnergy.end() ) {	// znaèi da je ovaj s kojim ga usporeðujemo zadnji
						if( CalcAbsPercentageDiff(*iterE, E) > 5 )
						{
							vecEnergy.insert(iterE+1, E);
							vecYStart1.insert(iter1+1, Y1);
							vecYStart2.insert(iter2+1, Y2);
						}
					}
					else if ( E < *(iterE+1) && CalcAbsPercentageDiff(*iterE, E)>5 && CalcAbsPercentageDiff(*(iterE+1), E)>5 ) 
					{
						vecEnergy.insert(iterE+1, E);
						vecYStart1.insert(iter1+1, Y1);
						vecYStart2.insert(iter2+1, Y2);
					}
					break;		// treba prekinuti petlju jer tu energiju veæ imamo u listi
				}
			}
		}
	}
*/

	// najprije æemo sortirati u rastuæem poretku
	Vector<double>		Y(3);

	for( i=0; i<vecEnergy.size()-1; i++ )
		for( j=i+1; j<vecEnergy.size(); j++ )
			if( vecEnergy[i] > vecEnergy[j] ) {
				Swap(vecEnergy[i], vecEnergy[j]);
				Swap(vecYStart1[i], vecYStart1[j]);
				Swap(vecYStart2[i], vecYStart2[j]);
				Swap(vecpXPsi[i], vecpXPsi[j]);
				Swap(vecpYPsi[i], vecpYPsi[j]);
				Swap(vecAdded[i], vecAdded[j]);
/*
				h = vecEnergy[j];
				vecEnergy[j] = vecEnergy[i];
				vecEnergy[i] = h;

				Y = vecYStart1[j];
				vecYStart1[j] = vecYStart1[i];
				vecYStart1[i] = Y;

				Y = vecYStart2[j];
				vecYStart2[j] = vecYStart2[i];
				vecYStart2[i] = Y;
*/
			}

	return true;
}


void CSchEqDoc::OnViewOptions() 
{
	CDlgOptions		dlg;

	if( dlg.DoModal() == IDOK ) {
		if( dlg.m_NumInt == 0 )
			bViewNumInt = true;
		else
			bViewNumInt = false;
	}
}
