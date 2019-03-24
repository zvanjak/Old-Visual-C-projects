// SurfacePlotCtl.cpp : Implementation of the CSurfacePlotCtrl ActiveX Control class.

#include "stdafx.h"
#include "SurfacePlot.h"
#include "SurfacePlotCtl.h"
#include "SurfacePlotPpg.h"

#include "D:\Users\Zvone\Projects\Projects Visual C++\Libraries\MathLib\mathlib.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSurfacePlotCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSurfacePlotCtrl, COleControl)
	//{{AFX_MSG_MAP(CSurfacePlotCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSurfacePlotCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSurfacePlotCtrl)
	DISP_PROPERTY_NOTIFY(CSurfacePlotCtrl, "Distance", m_dRho, OnDistanceChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CSurfacePlotCtrl, "VerticalAngle", m_dTheta, OnVerticalAngleChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CSurfacePlotCtrl, "Azimuth", m_dAlpha, OnAzimuthChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CSurfacePlotCtrl, "HideLines", m_bHideLines, OnHideLinesChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSurfacePlotCtrl, "Stretch", m_fStretch, OnStretchChanged, VT_R4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CSurfacePlotCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSurfacePlotCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSurfacePlotCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSurfacePlotCtrl, 1)
	PROPPAGEID(CSurfacePlotPropPage::guid)
END_PROPPAGEIDS(CSurfacePlotCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSurfacePlotCtrl, "SURFACEPLOT.SurfacePlotCtrl.1",
	0x7e0d9edc, 0x75a, 0x11d2, 0x91, 0x4a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSurfacePlotCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSurfacePlot =
		{ 0x7e0d9eda, 0x75a, 0x11d2, { 0x91, 0x4a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };
const IID BASED_CODE IID_DSurfacePlotEvents =
		{ 0x7e0d9edb, 0x75a, 0x11d2, { 0x91, 0x4a, 0, 0xc0, 0xdf, 0xe5, 0x28, 0x74 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSurfacePlotOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSurfacePlotCtrl, IDS_SURFACEPLOT, _dwSurfacePlotOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::CSurfacePlotCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSurfacePlotCtrl

BOOL CSurfacePlotCtrl::CSurfacePlotCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SURFACEPLOT,
			IDB_SURFACEPLOT,
			afxRegApartmentThreading,
			_dwSurfacePlotOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::CSurfacePlotCtrl - Constructor

CSurfacePlotCtrl::CSurfacePlotCtrl()
{
	InitializeIIDs(&IID_DSurfacePlot, &IID_DSurfacePlotEvents);

	// TODO: Initialize your control's instance data here.
	m_matT = new Matrix(4,4);
	pointLookTo = new Point3D(0,0,0);

	m_bHideLines = TRUE;
	m_bNeedCoordRecalc = TRUE;
	m_bPlotTypeChanged = TRUE;

	// pošto su nam koordinate na ekranu integeri, ukoliko dobijemo male vrijednosti ekranskih koordinata
	// prilikom transfromacije pogleda, dobiæemo "diskretizirane" krivulje
	// Zato æemo svaku ekransku koordinatu množiti sa m_dScaleScreenCoord
	m_dScaleScreenCoord = 100;

	m_dScreenMaxX = -1e30;
	m_dScreenMinX = 1e30;
	m_dScreenMaxY = -1e30;
	m_dScreenMinY = 1e30;

	int			i, j;

	m_pdXVal = NULL;
	m_pdYVal = NULL;
	m_pdRVal = NULL;
	m_pdThetaVal = NULL;

	double	x,y;
	m_enCoordSystemType = CARTESIAN_COORD;

	m_lPointsNumCoord1 = 50;
	m_lPointsNumCoord2 = 25;

	m_pdXVal = new double[m_lPointsNumCoord1];
	m_pdYVal = new double[m_lPointsNumCoord2];
	m_matZVal = new Matrix(m_lPointsNumCoord1, m_lPointsNumCoord2);

	for( i=0; i<m_lPointsNumCoord1; i++ )
		m_pdXVal[i] = i-25.;
	for( j=0; j<m_lPointsNumCoord2; j++ )
		m_pdYVal[j] = j-12.5;

	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			x = m_pdXVal[i];
			y = m_pdYVal[j];
//			(*m_matZVal)[i][j] = x*sin(y/5.) + y*cos(y/5.);
			(*m_matZVal)[i][j] = /*-75*exp(-(x*x+y*y)/100)*/ -(10*sin(x/10)*cos(y/5) * exp(x*x / 20 / 20));
		}

/*
	double	r, theta;
	m_enCoordSystemType = CYLINDRICAL_COORD;

	m_lPointsNumCoord1 = 50;
	m_lPointsNumCoord2 = 50;

	m_pdRVal = new double[m_lPointsNumCoord1];
	m_pdThetaVal = new double[m_lPointsNumCoord2];
	m_matZVal = new Matrix(m_lPointsNumCoord1, m_lPointsNumCoord2);

	for( i=0; i<m_lPointsNumCoord1; i++ )
		m_pdRVal[i] = i / 10.;
	for( j=0; j<m_lPointsNumCoord2; j++ )
		m_pdThetaVal[j] = j / (m_lPointsNumCoord2-1.) * 2 * 3.14159;

	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			r = m_pdRVal[i];
			theta = m_pdThetaVal[j];
			(*m_matZVal)[i][j] = -r * sin(r*4);
		}
*/	
	m_dRho = 10000;
	m_dTheta = 10;
	m_dAlpha = 45;

	m_fStretch = 1.5;

	// ova matrica æe sadržavati udaljenosti od poligona (koji predstavlja element površine)
	// do oka promatraèa
	m_matZBuff = new Matrix(m_lPointsNumCoord1, m_lPointsNumCoord2);
	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
			(*m_matZBuff)[i][j] = 0.0;
	
	m_plPolyOrderX = new long[(m_lPointsNumCoord1-1)*(m_lPointsNumCoord2-1)];
	m_plPolyOrderY = new long[(m_lPointsNumCoord1-1)*(m_lPointsNumCoord2-1)];

	// rezerviramo memoriju za podatke o transformiranim toèkama
	m_pTransf = (CPoint **) new  CPoint*[m_lPointsNumCoord1];
	for( i=0; i<m_lPointsNumCoord1; i++ )
		m_pTransf[i] = (CPoint *) new CPoint[m_lPointsNumCoord2];
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::~CSurfacePlotCtrl - Destructor

CSurfacePlotCtrl::~CSurfacePlotCtrl()
{
	// TODO: Cleanup your control's instance data here.
	delete m_matT;
	delete pointLookTo;

	if( m_pdXVal != NULL )
		delete []m_pdXVal;
	if( m_pdYVal != NULL )
		delete []m_pdYVal;
	if( m_pdRVal != NULL )
		delete []m_pdRVal;
	if( m_pdThetaVal != NULL )
		delete []m_pdThetaVal;

	delete m_matZVal;

	delete m_matZBuff;
	
	delete []m_plPolyOrderX;
	delete []m_plPolyOrderY;
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::OnDraw - Drawing function

void CSurfacePlotCtrl::OnDraw(
			CDC* pDC, const CRect& rcBounds, const CRect& rcInvalid)
{
	CBrush	brushBack(RGB(10, 200, 200));
	pDC->FillRect(rcBounds, &brushBack);
	pDC->SetWindowExt(rcBounds.Width(),-rcBounds.Height());
	pDC->SetMapMode(MM_ANISOTROPIC);

	DrawSurface(pDC, rcBounds);
	
//	if( m_enCoordSystemType == CARTESIAN_COORD )
//		PlotBox(pDC);
}

void CSurfacePlotCtrl::DrawSurface(CDC * pDC, const CRect rcBounds )
{
	CPoint				point;

	double	X, Y;
	int			i, j, k, l, size_x, size_y;

	if( m_bNeedCoordRecalc == TRUE )
	{
		Set3DData();
		TransformToScreenCoord();
		
		m_bNeedCoordRecalc = FALSE;
	}

	AnalyseData();

	GetControlSize(&size_x, &size_y);

	X = size_x / (m_dScreenMaxX - m_dScreenMinX);
	Y = size_y / (m_dScreenMaxY - m_dScreenMinY);
	m_dMulX = m_dMulY = ( X < Y ) ? X / 1.2 : Y / 1.2;

	pDC->SetWindowOrg((int)((m_dScreenMaxX + m_dScreenMinX)/2 * m_dMulX - size_x/2),
										(int)((m_dScreenMaxY + m_dScreenMinY)/2 * m_dMulY - size_y/2) );

	// draw with a thick blue pen
  CPen penBlue(PS_SOLID, 1, RGB(0, 0, 255));
  CPen* pOldPen = pDC->SelectObject(&penBlue);

  // and a solid red brush
	CBrush *brushRed[255], *pOldBrush;
	 
	for( int br=0; br<255; br++ ) {
		brushRed[br] = new CBrush(RGB(0,0,br));
	}
		
	if( m_bHideLines == TRUE )
	{
		CPoint	poly[4];

		// najprije treba izraèunati max i min Z koordinatu
		double		minZ = 1e38;
		double		maxZ = -1e38;
		for( i=0; i<m_lPointsNumCoord1-1; i++ )	{
			for( j=0; j<m_lPointsNumCoord2-1; j++ )
			{
				k = m_plPolyOrderX[i*(m_lPointsNumCoord2-1) + j];
				l = m_plPolyOrderY[i*(m_lPointsNumCoord2-1) + j];

				poly[0].x = (int) ((m_pTransf[k][l].x * m_dMulX) * m_fStretch);
				poly[0].y = (int) ((m_pTransf[k][l].y * m_dMulY) * m_fStretch);
				poly[1].x = (int) ((m_pTransf[k+1][l].x * m_dMulX) * m_fStretch);
				poly[1].y = (int) ((m_pTransf[k+1][l].y * m_dMulY) * m_fStretch);
				poly[2].x = (int) ((m_pTransf[k+1][l+1].x * m_dMulX) * m_fStretch);
				poly[2].y = (int) ((m_pTransf[k+1][l+1].y * m_dMulY) * m_fStretch);
				poly[3].x = (int) ((m_pTransf[k][l+1].x * m_dMulX) * m_fStretch);
				poly[3].y = (int) ((m_pTransf[k][l+1].y * m_dMulY) * m_fStretch);

				double	value = ((*m_matZVal)[i][j] + (*m_matZVal)[i+1][j] + (*m_matZVal)[i+1][j+1] + (*m_matZVal)[i][j+1]) / 4;

				if( value < minZ ) minZ = value;
				if( value > maxZ ) maxZ = value;
			}
		}

		for( i=0; i<m_lPointsNumCoord1-1; i++ )	{
			for( j=0; j<m_lPointsNumCoord2-1; j++ )
			{
				k = m_plPolyOrderX[i*(m_lPointsNumCoord2-1) + j];
				l = m_plPolyOrderY[i*(m_lPointsNumCoord2-1) + j];

				poly[0].x = (int) ((m_pTransf[k][l].x * m_dMulX) * m_fStretch);
				poly[0].y = (int) ((m_pTransf[k][l].y * m_dMulY) * m_fStretch);
				poly[1].x = (int) ((m_pTransf[k+1][l].x * m_dMulX) * m_fStretch);
				poly[1].y = (int) ((m_pTransf[k+1][l].y * m_dMulY) * m_fStretch);
				poly[2].x = (int) ((m_pTransf[k+1][l+1].x * m_dMulX) * m_fStretch);
				poly[2].y = (int) ((m_pTransf[k+1][l+1].y * m_dMulY) * m_fStretch);
				poly[3].x = (int) ((m_pTransf[k][l+1].x * m_dMulX) * m_fStretch);
				poly[3].y = (int) ((m_pTransf[k][l+1].y * m_dMulY) * m_fStretch);

				double	value = ((*m_matZVal)[i][j] + (*m_matZVal)[i+1][j] + (*m_matZVal)[i+1][j+1] + (*m_matZVal)[i][j+1]) / 4;
				int			intValue = (int) ((value - minZ) / (maxZ - minZ) * 255);

				if( intValue < 0 || intValue > 255 )
					AfxMessageBox("Keloza");

				int			ind = intValue % 255;
				
				pOldBrush = pDC->SelectObject(brushRed[ind]);
	
				pDC->Polygon(poly,4);
			}
		}

		// Put back the old objects.
//		pDC->SelectObject(pOldPen);
//		pDC->SelectObject(pOldBrush);

	}
	else
	{
		// iscrtavamo linije površine paralelne sa y-osi
		for( i=0; i<m_lPointsNumCoord1; i++ )
		{
			pDC->MoveTo((int) (m_pTransf[i][0].x * m_dMulX * m_fStretch), (int) (m_pTransf[i][0].y * m_dMulY * m_fStretch));
			for( j=0; j<m_lPointsNumCoord2; j++ )
				pDC->LineTo((int) (m_pTransf[i][j].x * m_dMulX * m_fStretch), (int) (m_pTransf[i][j].y * m_dMulY * m_fStretch));
		}
		// iscrtavamo linije površine paralelne sa x-osi
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			pDC->MoveTo((int) (m_pTransf[0][j].x * m_dMulX * m_fStretch), (int) (m_pTransf[0][j].y * m_dMulY * m_fStretch) );
			for( i=0; i<m_lPointsNumCoord1; i++ )
				pDC->LineTo((int) (m_pTransf[i][j].x * m_dMulX * m_fStretch), (int) (m_pTransf[i][j].y * m_dMulY * m_fStretch)) ;
		}
	}
}

void CSurfacePlotCtrl::TransformToScreenCoord( void )
{
	CPointDouble	transfP;
	double	p[4];
	double	x, y, z, xo, yo, zo, dist;
	double	x1, y1, x2, y2, x3, y3, x4, y4;
	int			i, j, k, l, ord_i, ord_j;
	int			nAlreadyOrdered = 0;

	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			if( m_enCoordSystemType == CARTESIAN_COORD )
			{
				p[0] = m_pdXVal[i];
				p[1] = m_pdYVal[j];
			}
			else
			{
				p[0] = m_pdRVal[i] * cos(m_pdThetaVal[j]);
				p[1] = m_pdRVal[i] * sin(m_pdThetaVal[j]);
			}
			p[2] = (*m_matZVal)[i][j];
			p[3] = 1.0;

			transfP = TransfToDoublePoint( p, m_matT );

			m_pTransf[i][j].x = (long) (transfP.x * m_dScaleScreenCoord);
			m_pTransf[i][j].y = (long) (transfP.y * m_dScaleScreenCoord);
		}

	if( m_bHideLines == TRUE )
	{
		// sada æemo izraèunati udaljenosti od oka za sve poligone, i poredati ih po toj udaljnosti
		// koordinate oka
		xo = GetX(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * cos(m_dAlpha * 3.141/180);
		yo = GetY(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * sin(m_dAlpha * 3.141/180);
		zo = GetZ(*pointLookTo) + m_dRho * sin(m_dTheta * 3.141/180);
		
		for( i=0; i<m_lPointsNumCoord1-1; i++ )
			for( j=0; j<m_lPointsNumCoord2-1; j++ )
			{
				if( m_enCoordSystemType == CARTESIAN_COORD )
				{
					// raèunamo koordinate površine u sredini poligona
					x = (m_pdXVal[i] + m_pdXVal[i+1]) / 2;
					y = (m_pdYVal[j] + m_pdYVal[i+1]) / 2;
					z = ((*m_matZVal)[i][j] + (*m_matZVal)[i+1][j] + (*m_matZVal)[i+1][j+1] + (*m_matZVal)[i][j+1]) / 4;
				}
				else
				{
					// kod cilindriènog sustava, stranice poligona nemaju nužno po dvije iste x- i y-koordinate
					x1 = m_pdRVal[i] * cos(m_pdThetaVal[j]);
					y1 = m_pdRVal[i] * sin(m_pdThetaVal[j]);
					x2 = m_pdRVal[i] * cos(m_pdThetaVal[j+1]);
					y2 = m_pdRVal[i] * sin(m_pdThetaVal[j+1]);
					x3 = m_pdRVal[i+1] * cos(m_pdThetaVal[j]);
					y3 = m_pdRVal[i+1] * sin(m_pdThetaVal[j]);
					x4 = m_pdRVal[i+1] * cos(m_pdThetaVal[j+1]);
					y4 = m_pdRVal[i+1] * sin(m_pdThetaVal[j+1]);

					x = (x1 + x2 + x3 + y4) / 4;
					y = (y1 + y2 + y3 + y4) / 4;
					z = ((*m_matZVal)[i][j] + (*m_matZVal)[i+1][j] + (*m_matZVal)[i+1][j+1] + (*m_matZVal)[i][j+1]) / 4;
				}

				// raèunamo udaljenost poligona od oka
				dist = sqrt((x-xo)*(x-xo) + (y-yo)*(y-yo) + (z-zo)*(z-zo) );
				(*m_matZBuff)[i][j] = dist;

				for( k=0; k<nAlreadyOrdered; k++ )
				{
					ord_i = m_plPolyOrderX[k];
					ord_j = m_plPolyOrderY[k];

					if( dist < (*m_matZBuff)[ord_i][ord_j] )
					{
						// ubacujemo ga na to mjesto, a ostale pomièemo za jedno mjesto dalje
						for( l=nAlreadyOrdered; l>k; l-- )
						{
							m_plPolyOrderX[l] = m_plPolyOrderX[l-1];
							m_plPolyOrderY[l] = m_plPolyOrderY[l-1];
						}
						break;
					}
				}
				m_plPolyOrderX[k] = i;
				m_plPolyOrderY[k] = j;
				nAlreadyOrdered++;
			}
	}
}

void CSurfacePlotCtrl::AnalyseData( void )
{
	int			i, j;
	double	max = -1e38, min=1e38;

	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			if( m_pTransf[i][j].x < m_dScreenMinX )
				m_dScreenMinX = m_pTransf[i][j].x;
			if( m_pTransf[i][j].x > m_dScreenMaxX )
				m_dScreenMaxX = m_pTransf[i][j].x;

			if( m_pTransf[i][j].y < m_dScreenMinY )
				m_dScreenMinY = m_pTransf[i][j].y;
			if( m_pTransf[i][j].y > m_dScreenMaxY )
				m_dScreenMaxY = m_pTransf[i][j].y;
		}

	// najprije treba naæi maksimalnu i minimalnu vrijednost z-koordinate
	for( i=0; i<m_lPointsNumCoord1; i++ )
		for( j=0; j<m_lPointsNumCoord2; j++ )
		{
			if( (*m_matZVal)[i][j] > max )
				max = (*m_matZVal)[i][j];

			if( (*m_matZVal)[i][j] < min )
				min = (*m_matZVal)[i][j];
		}
	m_DataAnal.m_dZMin = min;
	m_DataAnal.m_dZMax = max;

	if( m_enCoordSystemType == CARTESIAN_COORD )
	{
		max = -1e30;
		min = 1e30;
		for( i=0; i<m_lPointsNumCoord1; i++ )
		{
			if( m_pdXVal[i] > max )
				max = m_pdXVal[i];
			if( m_pdXVal[i] < min )
				min = m_pdXVal[i];
		}
		m_DataAnal.m_dXMin = min;
		m_DataAnal.m_dXMax = max;

		max = -1e30;
		min = 1e30;
		for( i=0; i<m_lPointsNumCoord2; i++ )
		{
			if( m_pdYVal[i] > max )
				max = m_pdYVal[i];
			if( m_pdYVal[i] < min )
				min = m_pdYVal[i];
		}
		m_DataAnal.m_dYMin = min;
		m_DataAnal.m_dYMax = max;
	}
	else
	{
		double		max_x, max_y, x, y, min_x, min_y;

		max_x = max_y = -1e30;
		min_x = min_y = 1e30;
		for( i=0; i<m_lPointsNumCoord1; i++ )
			for( j=0; j<m_lPointsNumCoord2; j++ )
			{
				x = m_pdRVal[i] * cos(m_pdThetaVal[j]);
				y = m_pdRVal[i] * sin(m_pdThetaVal[j]);

				if( x > max_x )
					max_x = x;
				if( x < min_x )
					min_x = x;

				if( y > max_y )
					max_y = y;
				if( y < min_y )
					min_y = y;
			}
		m_DataAnal.m_dXMin = min_x;
		m_DataAnal.m_dXMax = max_x;

		m_DataAnal.m_dYMin = min_y;
		m_DataAnal.m_dYMax = max_y;
	}
}

void CSurfacePlotCtrl::Set3DData()
{
	double		x, y, z;
	
	x = GetX(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * cos(m_dAlpha * 3.141/180);
	y = GetY(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * sin(m_dAlpha * 3.141/180);
	z = GetZ(*pointLookTo) + m_dRho * sin(m_dTheta * 3.141/180);
	
	Point3D		pointEye(x,y,z);

	*m_matT = GetProjectionMatrix(pointEye, *pointLookTo);
}

CPointDouble	CSurfacePlotCtrl::TransfToDoublePoint( double *point, Matrix *T )
{
	int		i, j;
	double	Transf[4];
	CPointDouble	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		for( j=0; j<4; j++ )
			Transf[i] += point[j] * T->GetElem(j,i);
	}
	
	ret.x = (int) ((Transf[0] / Transf[3]) * m_dScaleScreenCoord);
	ret.y = (int) ((Transf[1] / Transf[3]) * m_dScaleScreenCoord);

	return	ret;
}

CPoint	CSurfacePlotCtrl::TransfToPoint( double *point, Matrix *T )
{
	int		i, j;
	double	Transf[4];
	CPoint	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		for( j=0; j<4; j++ )
			Transf[i] += point[j] * T->GetElem(j,i);
	}
	
	ret.x = (long) (Transf[0] / Transf[3] * m_dScaleScreenCoord);
	ret.y = (long) (Transf[1] / Transf[3] * m_dScaleScreenCoord);

	return	ret;
}

CPointDouble	CSurfacePlotCtrl::TransfVertexToPoint( VERTEX point, Matrix *T )
{
	int		i;
	double	Transf[4];
	CPointDouble	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		Transf[i] += point.x * T->GetElem(0,i);
		Transf[i] += point.y * T->GetElem(1,i);
		Transf[i] += point.z * T->GetElem(2,i);
		Transf[i] += point.h * T->GetElem(3,i);
	}
	
	ret.x = (Transf[0] / Transf[3] * m_dScaleScreenCoord);
	ret.y = (Transf[1] / Transf[3] * m_dScaleScreenCoord);

	return	ret;
}
void CSurfacePlotCtrl::PlotBox( CDC *pDC )
{
	int			i;
	VERTEX	vertex[8];

	for( i=0; i<8; i++ )
		if( i<4 )
			vertex[i].x = m_DataAnal.m_dXMin;
		else
			vertex[i].x = m_DataAnal.m_dXMax;
	
	for( i=0; i<8; i++ )
		if( i==0 || i==3 || i==4 || i==7 )
			vertex[i].z = m_DataAnal.m_dZMin;
		else
			vertex[i].z = m_DataAnal.m_dZMax;

	for( i=0; i<8; i++ )
		if( i==0 || i==1 ||i==4 || i==5 )
			vertex[i].y = m_DataAnal.m_dYMin;
		else
			vertex[i].y = m_DataAnal.m_dYMax;
	
	for( i=0; i<8; i++ )
		vertex[i].h = 1.0;

	DrawLine(pDC, vertex[0], vertex[1], m_matT );
	DrawLine(pDC, vertex[1], vertex[2], m_matT );
	DrawLine(pDC, vertex[2], vertex[3], m_matT );
	DrawLine(pDC, vertex[3], vertex[0], m_matT );
	DrawLine(pDC, vertex[0], vertex[4], m_matT );
	DrawLine(pDC, vertex[1], vertex[5], m_matT );
	DrawLine(pDC, vertex[2], vertex[6], m_matT );
	DrawLine(pDC, vertex[3], vertex[7], m_matT );
	DrawLine(pDC, vertex[4], vertex[5], m_matT );
	DrawLine(pDC, vertex[5], vertex[6], m_matT );
	DrawLine(pDC, vertex[6], vertex[7], m_matT );
	DrawLine(pDC, vertex[7], vertex[4], m_matT );
}

void CSurfacePlotCtrl::DrawLine( CDC *pDC, VERTEX v1, VERTEX v2, Matrix *T )
{
	CPointDouble	transf1, transf2;
	CPoint	point;

	transf1 = TransfVertexToPoint( v1, m_matT );
	transf2 = TransfVertexToPoint( v2, m_matT );

	point.x = (long) (transf1.x * m_dScaleScreenCoord * m_dMulX);
	point.y = (long) (transf1.y * m_dScaleScreenCoord * m_dMulY);

	pDC->MoveTo(point);

	point.x = (long) (transf2.x * m_dScaleScreenCoord * m_dMulX);
	point.y = (long) (transf2.y * m_dScaleScreenCoord * m_dMulY);

	pDC->LineTo(point);
}

/*
void CSurfacePlotCtrl::PlotAxis()
{
	{
		CPointDouble	CoordAxis[4];
		double	p[4], xMax;
		int			i;

		xMax = m_PlotPar.m_nWinExtX / 2 / m_PlotPar.m_dMulX;

		
		p[0]=GetX(*m_PlotPar.pointLookTo); p[1]=GetY(*m_PlotPar.pointLookTo); p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[0] = TransfToDoublePoint( p, m_PlotPar.m_matT );
		
		p[0]=GetX(*m_PlotPar.pointLookTo)+xMax/2; p[1]=GetY(*m_PlotPar.pointLookTo); p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[1] = TransfToDoublePoint( p, m_PlotPar.m_matT );
		
		p[0]=GetX(*m_PlotPar.pointLookTo); p[1]=GetY(*m_PlotPar.pointLookTo)+xMax/2; p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[2] = TransfToDoublePoint( p, m_PlotPar.m_matT );

		p[0]=GetX(*m_PlotPar.pointLookTo); p[1]=GetY(*m_PlotPar.pointLookTo); p[2]=GetZ(*m_PlotPar.pointLookTo)+xMax/5; p[3]=1;
		CoordAxis[3] = TransfToDoublePoint( p, m_PlotPar.m_matT );

		tmpPen.CreatePen(PS_SOLID, 8, RGB(0,0,0) );
		pPrevPen = pDC->SelectObject(&tmpPen);

		for( i=1; i<4; i++ )
		{
			pDC->MoveTo( (int) CoordAxis[0].x, (int) CoordAxis[0].y );
			pDC->LineTo( (int) (CoordAxis[i].x * m_PlotPar.m_dMulX), (int) (CoordAxis[i].y * m_PlotPar.m_dMulY) );
		}

		const char *name;
		CFont		tmpFont, *pPrevFont;
		
		if( nCalledBy == 0 )
			tmpFont.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
							OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );
		else
			tmpFont.CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
							OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );

		pPrevFont = pDC->SelectObject(&tmpFont);

		name = pDoc->m_DES.GetVarName(m_PlotPar.m_anPlottingVars[0]);
		pDC->TextOut( (int) (CoordAxis[1].x * m_PlotPar.m_dMulX)+10, (int) (CoordAxis[1].y * m_PlotPar.m_dMulY)+10, name );
		
		name = pDoc->m_DES.GetVarName(m_PlotPar.m_anPlottingVars[1]);
		pDC->TextOut( (int) (CoordAxis[2].x * m_PlotPar.m_dMulX)+10, (int) (CoordAxis[2].y * m_PlotPar.m_dMulY)+10, name );

		name = pDoc->m_DES.GetVarName(m_PlotPar.m_anPlottingVars[2]);
		pDC->TextOut( (int) (CoordAxis[3].x * m_PlotPar.m_dMulX)+10, (int) (CoordAxis[3].y * m_PlotPar.m_dMulY)+10, name );

		pDC->SelectObject(pPrevFont);

		// a sada definiramo koordinate za pravokutnik koji æe se iscrtavati u x-y ravnini
		p[0]=GetX(*m_PlotPar.pointLookTo)+xMax/2; p[1]=GetY(*m_PlotPar.pointLookTo)-xMax/2; p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[0] = TransfToDoublePoint( p, m_PlotPar.m_matT );
		p[0]=GetX(*m_PlotPar.pointLookTo)+xMax/2; p[1]=GetY(*m_PlotPar.pointLookTo)+xMax/2; p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[1] = TransfToDoublePoint( p, m_PlotPar.m_matT );
		p[0]=GetX(*m_PlotPar.pointLookTo)-xMax/2; p[1]=GetY(*m_PlotPar.pointLookTo)+xMax/2; p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[2] = TransfToDoublePoint( p, m_PlotPar.m_matT );
		p[0]=GetX(*m_PlotPar.pointLookTo)-xMax/2; p[1]=GetY(*m_PlotPar.pointLookTo)-xMax/2; p[2]=GetZ(*m_PlotPar.pointLookTo); p[3]=1;
		CoordAxis[3] = TransfToDoublePoint( p, m_PlotPar.m_matT );

		pDC->MoveTo( (int) (CoordAxis[0].x * m_PlotPar.m_dMulX), (int) (CoordAxis[0].y * m_PlotPar.m_dMulY) );
		for( i=1; i<4; i++ )
			pDC->LineTo( (int) (CoordAxis[i].x * m_PlotPar.m_dMulX), (int) (CoordAxis[i].y * m_PlotPar.m_dMulY) );
		pDC->LineTo( (int) (CoordAxis[0].x * m_PlotPar.m_dMulX), (int) (CoordAxis[0].y * m_PlotPar.m_dMulY) );
		
		pDC->SelectObject(pPrevPen);
	}
}
*/
/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::DoPropExchange - Persistence support

void CSurfacePlotCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::OnResetState - Reset control to default state

void CSurfacePlotCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl::AboutBox - Display an "About" box to the user

void CSurfacePlotCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_SURFACEPLOT);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl message handlers

void CSurfacePlotCtrl::OnDistanceChanged() 
{
	m_bNeedCoordRecalc = TRUE;

	SetModifiedFlag();
	InvalidateControl();
}

void CSurfacePlotCtrl::OnVerticalAngleChanged() 
{
	m_bNeedCoordRecalc = TRUE;

	SetModifiedFlag();
	InvalidateControl();
}

void CSurfacePlotCtrl::OnAzimuthChanged() 
{
	m_bNeedCoordRecalc = TRUE;

	SetModifiedFlag();
	InvalidateControl();
}

void CSurfacePlotCtrl::OnHideLinesChanged() 
{
	m_bPlotTypeChanged = TRUE;

	SetModifiedFlag();
	InvalidateControl();
}

void CSurfacePlotCtrl::OnStretchChanged() 
{
	SetModifiedFlag();
	InvalidateControl();
}
