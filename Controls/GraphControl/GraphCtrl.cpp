// GraphCtrl.cpp : Implementation of the CGraphCtrl ActiveX Control class.

#include "stdafx.h"
#include "GraphControl.h"
#include "GraphCtrl.h"
#include "GraphPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>

IMPLEMENT_DYNCREATE(CGraphCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGraphCtrl, COleControl)
	//{{AFX_MSG_MAP(CGraphCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGraphCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGraphCtrl)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "Title", m_strTitle, OnTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "XAxisTitle", m_strXAxisTitle, OnXAxisTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "UseColor", m_bUseColor, OnUseColorChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "UseLineStyles", m_bUseLineStyles, OnUseLineStylesChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ShowLegend", m_bShowLegend, OnShowLegendChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ShowCoordSystem", m_bShowCoordSystem, OnShowCoordSystemChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ShowScale", m_bShowScale, OnShowScaleChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ScaleType", m_nScaleType, OnScaleTypeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "XAxisVar", m_nXAxisVar, OnXAxisVarChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "YAxisVar", m_nYAxisVar, OnYAxisVarChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ZAxisVar", m_nZAxisVar, OnZAxisVarChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "ScaleIntervalsNum", m_nScaleIntervalsNum, OnScaleIntervalsNumChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "PlotType", m_nPlotType, OnPlotTypeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "StartX", m_dStartX, OnStartXChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "EndX", m_dEndX, OnEndXChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "SetLegendPosFlag", m_setLegendPosFlag, OnSetLegendPosFlagChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "Distance", m_dRho, OnDistanceChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "Azimuth", m_dAlpha, OnAzimuthChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CGraphCtrl, "VerticalAngle", m_dTheta, OnVerticalAngleChanged, VT_R8)
	DISP_PROPERTY_EX(CGraphCtrl, "GraphNum", GetGraphNum, SetNotSupported, VT_I2)
	DISP_PROPERTY_EX(CGraphCtrl, "PointsNum", GetPointsNum, SetNotSupported, VT_I4)
	DISP_FUNCTION(CGraphCtrl, "AddNewGraph", AddNewGraph, VT_I2, VTS_PR8 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGraphCtrl, "AddNewGraphWithX", AddNewGraphWithX, VT_I2, VTS_PR8 VTS_PR8 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGraphCtrl, "RemoveGraph", RemoveGraph, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CGraphCtrl, "RemoveAllGraphs", RemoveAllGraphs, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGraphCtrl, "ShowGraph", ShowGraph, VT_I2, VTS_I2 VTS_BOOL)
	DISP_FUNCTION(CGraphCtrl, "Resize", Resize, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CGraphCtrl, "Move", Move, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CGraphCtrl, "SetLegendPos", SetLegendPos, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CGraphCtrl, "DrawItself", DrawItself, VT_EMPTY, VTS_PI4 VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CGraphCtrl, "DrawToMetafile", DrawToMetafile, VT_BOOL, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGraphCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGraphCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGraphCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGraphCtrl, 1)
	PROPPAGEID(CGraphPropPage::guid)
END_PROPPAGEIDS(CGraphCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGraphCtrl, "GRAPHCONTROL.GraphCtrl.1",
	0x106d39e8, 0xc7af, 0x11d1, 0xaf, 0xfe, 0, 0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGraphCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGraph =
		{ 0x106d39e6, 0xc7af, 0x11d1, { 0xaf, 0xfe, 0, 0, 0xc0, 0x3e, 0x61, 0x8c } };
const IID BASED_CODE IID_DGraphEvents =
		{ 0x106d39e7, 0xc7af, 0x11d1, { 0xaf, 0xfe, 0, 0, 0xc0, 0x3e, 0x61, 0x8c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGraphOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGraphCtrl, IDS_GRAPH, _dwGraphOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::CGraphCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGraphCtrl

BOOL CGraphCtrl::CGraphCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GRAPH,
			IDB_GRAPH,
			afxRegApartmentThreading,
			_dwGraphOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::CGraphCtrl - Constructor

CGraphCtrl::CGraphCtrl()
{
	InitializeIIDs(&IID_DGraph, &IID_DGraphEvents);

	// TODO: Initialize your control's instance data here.
	m_nCalledBy = ON_DRAW;

	m_strTitle = "";
	m_strXAxisTitle = "";

	m_bUseColor = TRUE;
	m_bUseLineStyles = FALSE;

	m_bShowLegend = TRUE;
	m_pntLegendPos = CPoint(30,30);
		
	m_bShowCoordSystem = TRUE;
	m_bShowScale = TRUE;

	m_bViewContentChanged = FALSE;
	m_bViewTypeChanged = FALSE;
	m_bNeedRecalc = TRUE;

	m_nPlotType = TRAJECTORY;
	m_nScaleIntervalsNum = 2;
	m_nScaleType = SCALE_SAME;

	m_dExtraWidth = m_dExtraHeight = 10;

	m_dStartX = 0.;
	m_dEndX = 1.0;
	m_bViewIntervalChanged = FALSE;

	m_nXAxisVar = 0;
	m_nYAxisVar = 1;
	m_nZAxisVar = 4;

	m_matT = new Matrix<float>(4,4);
	pointLookTo = new Point3D(0,0,0);
	m_pTransf = NULL;

	m_dRho = 10000;
	m_dTheta = 50;
	m_dAlpha = 45;

	m_dScaleScreenCoord = 5;

	m_dScreenMaxX = -1e30;
	m_dScreenMinX = 1e30;
	m_dScreenMaxY = -1e30;
	m_dScreenMinY = 1e30;

	m_nGraphNum = 0;
	m_nSelected = -1;
	
	m_pdXVal = NULL;
	m_lPointsNum = 0;
	
	m_AnalPar.dXLow = -1.0;
	m_AnalPar.dXUpp = 1.0;
	m_AnalPar.dYLowTot = -1.0;
	m_AnalPar.dYUppTot = 1.0;
	m_PlotPar.pntOrg.x = 0;
	m_PlotPar.pntOrg.y = 0;
	m_PlotPar.dMulX = m_PlotPar.dMulY = 1.;
	for( int i=0; i<MAX_GRAPHS; i++ )
	{
		m_apdYVal[i] = NULL;
		m_PlotPar.adMulY[i] = 1.;
		m_bFreeGraph[i] = FALSE;
		m_bShowGraph[i] = TRUE;

		m_Anal[i].dYLow = 0;
		m_Anal[i].dYUpp = 0;
	}

	m_Colors[0] = RGB(0,0,0);
	m_Colors[1] = RGB(255,0,0);
	m_Colors[2] = RGB(0,255,0);
	m_Colors[3] = RGB(0,0,255);
	m_Colors[4] = RGB(155,70,155);

	m_Styles[0] = PS_SOLID;
	m_Styles[1] = PS_DASH;
	m_Styles[2] = PS_DOT;
	m_Styles[3] = PS_DASHDOT;
	m_Styles[4] = PS_SOLID;


	double	x[200], y1[200], y2[200], y3[200], y4[200], y5[200], sig;

	sig = 1.;

	for( i=0; i<200; i++ )
	{
		x[i] = i / 200. * 15 - 7.;
		
		y1[i] = 20*sin(x[i]);
		y2[i] = 15*cos(x[i]+0.7);
		y3[i] = (x[i]+2)*(x[i]-3)*(x[i]-6);
		y3[i] /= 3.;
		y4[i] = 7/sig/sqrt(6.28) * exp(-(x[i]-8)*(x[i]-7)/(2*sig*sig));
		
		y5[i] = 20*exp(-x[i]/5) * cos(x[i]*5);
	}
	m_dEndX = 15.0;

	AddNewGraphWithX(x, y1, 200, "Graph 1 - sinus");
	AddNewGraph(y2,200, "Graph 2 - kosinus");
	AddNewGraph(y3,200, "Graph 3 - polinom 3. stupnja");
	AddNewGraph(y4,200, "Graph 4 - Gaussova krivulja");
	AddNewGraph(y5,200, "Graph 5 - amplitudna modulacija");

	m_strTitle = "Proba grafova";
	m_bViewContentChanged = TRUE;
	m_bViewTypeChanged = TRUE;

}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::~CGraphCtrl - Destructor

CGraphCtrl::~CGraphCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if( m_pdXVal != NULL )
		delete []m_pdXVal;
	
	for( int i=0; i<MAX_GRAPHS; i++ )
		if( m_apdYVal[i] != NULL )
			delete []m_apdYVal[i];

	if( m_pTransf != NULL )
		delete []m_pTransf;
}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::OnDraw - Drawing function

void CGraphCtrl::OnDraw(CDC* pDC, const CRect& rcBounds, const CRect& rcInvalid)
{
	pDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	pDC->SetMapMode(MM_ANISOTROPIC);
	
	if( m_nCalledBy == ON_DRAW )
		pDC->SetWindowExt(1, -1);
	else if( m_nCalledBy = DRAW_METAFILE ) {
		// MetaFile kreira OutputDC device-context, a potreban nam je i Attrib, kako bi
		// funkcije GetExtent i sliène mogle raditi
		CWindowDC		dc(this);
		pDC->SetAttribDC(dc.m_hAttribDC);
	}
	else
		pDC->SetWindowExt(rcBounds.Width(),-rcBounds.Height());

	CFont		tmpFont, *pPrevFont;
	CSize		size;
	tmpFont.CreateFont(	rcBounds.Height()*4/36/3, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
											OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Roman");
	pPrevFont = pDC->SelectObject(&tmpFont);
	size			= pDC->GetTextExtent(m_strTitle);
	
	pDC->TextOut( rcBounds.left + (rcBounds.Width() - size.cx)/2, 
								rcBounds.top - size.cy/2, m_strTitle);
	pDC->SelectObject(pPrevFont);

	if( m_bViewIntervalChanged == TRUE || m_bViewTypeChanged == TRUE )
	{
		AnalyseDataRange();
		AnalyseGraphs(rcBounds);

		m_bViewIntervalChanged = FALSE;
		m_bViewTypeChanged = FALSE;
	}
	if( m_bViewContentChanged == TRUE )
	{
		AnalyseGraphs(rcBounds);
		
		m_bViewContentChanged = FALSE;
	}

	switch(m_nPlotType)
	{
		case TRAJECTORY	:	DrawTrajectory(pDC,rcBounds); break;
		case PHASE_2D		: DrawPhase(pDC, rcBounds);	break;
		case PHASE_3D		: DrawPhase3D(pDC, rcBounds); break;
	}
	m_nCalledBy = ON_DRAW;
}

void CGraphCtrl::DrawTrajectory( CDC *pDC, const CRect &rcBounds )
{
	int				i, j, style;
	CPen			*penTmp;
	BOOL			bStarted;
	COLORREF	color;

	m_dExtraWidth = rcBounds.Width() * 0.04;
	// ako nema naslova, onda æemo manje suziti ekran po y-osi sužavati 
	if( m_strTitle.IsEmpty() )
		m_dExtraHeight = rcBounds.Height() * 0.02;
	else
		m_dExtraHeight = rcBounds.Height() * 0.08;

//	AnalyseGraphs(rcBounds);

	pDC->SetWindowOrg((int) (m_AnalPar.dXLow*m_PlotPar.dMulX - m_dExtraWidth) + m_PlotPar.pntOrg.x*rcBounds.Width()/100, 
										(int) (m_AnalPar.dYUppTot*m_PlotPar.dMulY + m_dExtraHeight) + m_PlotPar.pntOrg.y*rcBounds.Height()/100 );

	DrawCoordSystem(pDC, rcBounds);

	color = RGB(0,0,0);
	style = PS_SOLID;

	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) && m_bShowGraph[i] == TRUE )
		{
			if( m_bUseColor == TRUE )
				color = m_Colors[i];
			if( m_bUseLineStyles == TRUE )
				style = m_Styles[i];

			penTmp = new CPen(style, rcBounds.Height()/500+1, color);
			pDC->SelectObject(penTmp);

			if( m_lPointsNum > 0 )
			{
				if( m_pdXVal[0] >= m_dStartX && m_pdXVal[0] <= m_dEndX )
				{
					pDC->MoveTo((int) (m_pdXVal[0]*m_PlotPar.dMulX), (int) (m_apdYVal[i][0]*m_PlotPar.dMulY) );
					bStarted = TRUE;
				}
				else
					bStarted = FALSE;

				for( j=1; j<m_lPointsNum; j++ )
				{
					if( m_pdXVal[j] >= m_dStartX && m_pdXVal[j] <= m_dEndX )
					{
						if( bStarted == TRUE )
							pDC->LineTo((int) (m_pdXVal[j]*m_PlotPar.dMulX), (int) (m_apdYVal[i][j]*m_PlotPar.dMulY));
						else
						{
							pDC->MoveTo((int) (m_pdXVal[j]*m_PlotPar.dMulX), (int) (m_apdYVal[i][j]*m_PlotPar.dMulY) );
							bStarted = TRUE;
						}
					}
					else
						bStarted = FALSE;
				}
			}
			delete penTmp;
		}
}

void CGraphCtrl::DrawPhase( CDC *pDC, const CRect &rcBounds )
{
	// najprije provjeri da li su za x i y os odabrane vazece varijable
	if( IsValidGraphID(m_nXAxisVar) && IsValidGraphID(m_nYAxisVar) )
	{
		int		j, xVar, yVar;
		int		x, y;

		m_dExtraWidth = rcBounds.Width() * 0.04;
		// ako nema naslova, onda æemo manje suziti ekran po y-osi sužavati 
		if( m_strTitle.IsEmpty() )
			m_dExtraHeight = rcBounds.Height() * 0.02;
		else
			m_dExtraHeight = rcBounds.Height() * 0.08;

		xVar = m_nXAxisVar;
		yVar = m_nYAxisVar;

		x = (int) (m_Anal[xVar].dYLow*m_PlotPar.dMulX - m_dExtraWidth) + m_PlotPar.pntOrg.x*rcBounds.Width()/100;
		y =	(int) (m_Anal[yVar].dYUpp*m_PlotPar.dMulY + m_dExtraHeight) + m_PlotPar.pntOrg.y*rcBounds.Height()/100;

		pDC->SetWindowOrg(x,y);

		DrawCoordSystem(pDC, rcBounds);

		if( m_lPointsNum > 0 )
		{
			pDC->MoveTo((int) (m_apdYVal[xVar][0]*m_PlotPar.dMulX), (int) (m_apdYVal[yVar][0]*m_PlotPar.dMulY) );

			for( j=1; j<m_lPointsNum; j++ )
				pDC->LineTo((int) (m_apdYVal[xVar][j]*m_PlotPar.dMulX), (int) (m_apdYVal[yVar][j]*m_PlotPar.dMulY));
		}
	}
	else
		AfxMessageBox("Wrong x or y variables ");
}

void CGraphCtrl::DrawPhase3D( CDC *pDC, const CRect &rcBounds )
{
	if( IsValidGraphID(m_nXAxisVar) && IsValidGraphID(m_nYAxisVar) && IsValidGraphID(m_nZAxisVar) )
	{
		int		i, xVar, yVar, zVar, size_x, size_y;
		int		x, y;

		m_dExtraWidth = rcBounds.Width() * 0.04;
		// ako nema naslova, onda æemo manje suziti ekran po y-osi sužavati 
		if( m_strTitle.IsEmpty() )
			m_dExtraHeight = rcBounds.Height() * 0.02;
		else
			m_dExtraHeight = rcBounds.Height() * 0.08;

		xVar = m_nXAxisVar;
		yVar = m_nYAxisVar;
		zVar = m_nZAxisVar;

		GetControlSize(&size_x, &size_y);

		x = (int) (m_dScreenMinX * m_PlotPar.dMulX - m_dExtraWidth) + m_PlotPar.pntOrg.x*rcBounds.Width()/100;
		y =	(int) (m_dScreenMaxY * m_PlotPar.dMulY + m_dExtraHeight) + m_PlotPar.pntOrg.y*rcBounds.Height()/100;
		pDC->SetWindowOrg(x,y);

		if( m_lPointsNum > 0 )
		{
			pDC->MoveTo((int) (m_pTransf[0].x * m_PlotPar.dMulX), (int) (m_pTransf[0].y * m_PlotPar.dMulY) );

			for( i=1; i<m_lPointsNum; i++ )
				pDC->LineTo((int) (m_pTransf[i].x * m_PlotPar.dMulX), (int) (m_pTransf[i].y * m_PlotPar.dMulY));
		}

		DrawCoordSystem(pDC, rcBounds);
	}
	else
	{
		AfxMessageBox("Wrong x or y or z variables ");
		m_bNeedRecalc = TRUE;
	}
}

void CGraphCtrl::TransformToScreenCoord( void )
{
	Set3DData();

	if( m_pTransf == NULL )
		m_pTransf = new CPoint[m_lPointsNum];

	CPointDouble	transfP;
	double	p[4];
	int			i;

	for( i=0; i<m_lPointsNum; i++ )
	{
		p[0] = m_apdYVal[m_nXAxisVar][i];
		p[1] = m_apdYVal[m_nYAxisVar][i];
		p[2] = m_apdYVal[m_nZAxisVar][i];
		p[3] = 1.0;

		transfP = TransfToDoublePoint( p, m_matT );

		m_pTransf[i].x = (long) (transfP.x * m_dScaleScreenCoord);
		m_pTransf[i].y = (long) (transfP.y * m_dScaleScreenCoord);
	}

	m_bNeedRecalc = FALSE;
}

void CGraphCtrl::Set3DData()
{
	double		x, y, z;
	
	x = GetX(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * cos(m_dAlpha * 3.141/180);
	y = GetY(*pointLookTo) + m_dRho * cos(m_dTheta * 3.141/180) * sin(m_dAlpha * 3.141/180);
	z = GetZ(*pointLookTo) + m_dRho * sin(m_dTheta * 3.141/180);
	
	Point3D		pointEye(x,y,z);

//	*m_matT = GetProjectionMatrix(pointEye, *pointLookTo);
}

CPointDouble	CGraphCtrl::TransfToDoublePoint( double *point, Matrix<float> *T )
{
	int			i, j;
	double	Transf[4];
	CPointDouble	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		for( j=0; j<4; j++ )
			Transf[i] += point[j] * (*T)[j][i];
	}
	
	ret.x = (int) ((Transf[0] / Transf[3]) * m_dScaleScreenCoord);
	ret.y = (int) ((Transf[1] / Transf[3]) * m_dScaleScreenCoord);

	return	ret;
}

CPoint	CGraphCtrl::TransfToPoint( double *point, Matrix<float> *T )
{
	int			i, j;
	double	Transf[4];
	CPoint	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		for( j=0; j<4; j++ )
			Transf[i] += point[j] * (*T)[j][i];
	}
	
	ret.x = (long) (Transf[0] / Transf[3] * m_dScaleScreenCoord);
	ret.y = (long) (Transf[1] / Transf[3] * m_dScaleScreenCoord);

	return	ret;
}

CPointDouble	CGraphCtrl::TransfVertexToPoint( VERTEX point, Matrix<float> *T )
{
	int			i;
	double	Transf[4];
	CPointDouble	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		Transf[i] += point.x * (*T)[0][i];
		Transf[i] += point.y * (*T)[1][i];
		Transf[i] += point.z * (*T)[2][i];
		Transf[i] += point.h * (*T)[3][i];
	}
	
	ret.x = (Transf[0] / Transf[3] * m_dScaleScreenCoord);
	ret.y = (Transf[1] / Transf[3] * m_dScaleScreenCoord);

	return	ret;
}

void CGraphCtrl::DrawCoordSystem( CDC *pDC, const CRect & rcBounds )
{
	CPen		*pPrevPen, tmpPen;
	CPoint	pntCenter;
	double	x,y, mulx, muly;
	int			retCenter, nPenWidth;
	int			X0, Y0;				// koordinate centra koordinatnog sustav (tj. sjecista osi)

	nPenWidth = rcBounds.Width() / 250;

	if( m_nPlotType == TRAJECTORY || m_nPlotType == PHASE_2D )
	{
		int			x0, y0, x1, y1;
		x0 = (int) (m_CoordPar.dXAxisLow * m_PlotPar.dMulX);
		x1 = (int) (m_CoordPar.dXAxisUpp * m_PlotPar.dMulX);
		y0 = (int) (m_CoordPar.dYAxisLow * m_PlotPar.dMulY);
		y1 = (int) (m_CoordPar.dYAxisUpp * m_PlotPar.dMulY);
		
		tmpPen.CreatePen(PS_SOLID, nPenWidth, RGB(0,0,0) );
		pPrevPen = pDC->SelectObject(&tmpPen);

		retCenter = CenterWithinWindow(pntCenter);
		if( retCenter == CENTER_WITHIN_WINDOW)
		{
			x = m_CoordPar.dXAxisLow;
			y = m_CoordPar.dYAxisLow;
			X0 = 0;
			Y0 = 0;
			mulx = m_PlotPar.dMulX;
			muly = m_PlotPar.dMulY;

			pDC->MoveTo(0, (int) (m_CoordPar.dYAxisLow * m_PlotPar.dMulY) );
			pDC->LineTo(0, (int) (m_CoordPar.dYAxisUpp * m_PlotPar.dMulY) );

			pDC->MoveTo((int) (m_CoordPar.dXAxisLow * m_PlotPar.dMulX), 0);
			pDC->LineTo((int) (m_CoordPar.dXAxisUpp * m_PlotPar.dMulX), 0);

		}
		else if( retCenter == X_AXIS_WITHIN_WINDOW )
		{
			x = m_CoordPar.dXAxisLow * m_PlotPar.dMulX;// + 8;
			y = 0;
			X0 = (int) x;
			Y0 = 0;

			pDC->MoveTo((int) x, (int) (m_CoordPar.dYAxisLow * m_PlotPar.dMulY) );
			pDC->LineTo((int) x, (int) (m_CoordPar.dYAxisUpp * m_PlotPar.dMulY) );
	
			pDC->MoveTo((int) (m_CoordPar.dXAxisLow * m_PlotPar.dMulX), 0);
			pDC->LineTo((int) (m_CoordPar.dXAxisUpp * m_PlotPar.dMulX), 0);
		}
		else if( retCenter == Y_AXIS_WITHIN_WINDOW )
		{
			x = 0;
			y = m_CoordPar.dYAxisUpp * m_PlotPar.dMulY;// - 8;
			X0 = 0;
			Y0 = (int) y;

			pDC->MoveTo((int) (m_CoordPar.dXAxisLow * m_PlotPar.dMulX), (int) y);
			pDC->LineTo((int) (m_CoordPar.dXAxisUpp * m_PlotPar.dMulX), (int) y);

			pDC->MoveTo(0, (int) (m_CoordPar.dYAxisLow * m_PlotPar.dMulY) );
			pDC->LineTo(0, (int) (m_CoordPar.dYAxisUpp * m_PlotPar.dMulY) );
		}
		else
		{
			x = m_CoordPar.dXAxisLow * m_PlotPar.dMulX;// + 8;
			y = m_CoordPar.dYAxisUpp * m_PlotPar.dMulY;// - 8;
			X0 = (int) x;
			Y0 = (int) y;

			pDC->MoveTo((int) x, (int) (m_CoordPar.dYAxisLow * m_PlotPar.dMulY) );
			pDC->LineTo((int) x, (int) (m_CoordPar.dYAxisUpp * m_PlotPar.dMulY) );
			
			pDC->MoveTo((int) (m_CoordPar.dXAxisLow * m_PlotPar.dMulX), (int) y);
			pDC->LineTo((int) (m_CoordPar.dXAxisUpp * m_PlotPar.dMulX), (int) y);
		}

		DrawAxisScale(pDC, rcBounds, X0, Y0, retCenter );

		pDC->SelectObject(pPrevPen);

		if( m_nPlotType == TRAJECTORY )
			DrawLegend(pDC, rcBounds);
	}
	else if( m_nPlotType == PHASE_3D )
	{
		CPointDouble	pnt;
		CPoint				pos;
		VERTEX				vertex[4];
		double				k, min;
		
		min = fabs(m_Anal[m_nXAxisVar].dYUpp);
		if( (k = fabs(m_Anal[m_nYAxisVar].dYUpp)) < min )
			min = k;
		if( (k = fabs(m_Anal[m_nZAxisVar].dYUpp)) < min )
			min = k;

		vertex[0].x = 0;
		vertex[0].y = 0;
		vertex[0].z = 0;

		vertex[1].x = min*2;
		vertex[1].y = 0;
		vertex[1].z = 0;

		vertex[2].x = 0; 
		vertex[2].y = min*2;
		vertex[2].z = 0; 

		vertex[3].x = 0;
		vertex[3].y = 0;
		vertex[3].z = min*2;

		for( int i=0; i<4; i++ )		vertex[i].h = 1.0;

		DrawLine(pDC, vertex[0], vertex[1], m_matT );
		DrawLine(pDC, vertex[0], vertex[2], m_matT );
		DrawLine(pDC, vertex[0], vertex[3], m_matT );

		int			nFontSize = rcBounds.Height() / 25;
		CFont		tmpFont, *pPrevFont;
		
		tmpFont.CreateFont(nFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
						OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );
		pPrevFont = pDC->SelectObject(&tmpFont);
	
		CString		strCoordAxisName[3];
		strCoordAxisName[0] = "X";
		strCoordAxisName[1] = "Y";
		strCoordAxisName[2] = "Z";

		for( i=1; i<4; i++ )
		{
			pnt = TransfVertexToPoint(vertex[i], m_matT);
			
			pos.x = (int) (pnt.x * m_dScaleScreenCoord * m_PlotPar.dMulX);
			pos.y = (int) (pnt.y * m_dScaleScreenCoord * m_PlotPar.dMulY);
			
			pDC->TextOut(pos.x - nFontSize/4, (int)(pos.y + nFontSize/2.5), strCoordAxisName[i-1]);
		}

		pDC->SelectObject(pPrevFont);
	}
}

void CGraphCtrl::DrawLine( CDC *pDC, VERTEX v1, VERTEX v2, Matrix<float> *T )
{
	CPointDouble	transf1, transf2;
	CPoint	point;

	transf1 = TransfVertexToPoint( v1, m_matT );
	transf2 = TransfVertexToPoint( v2, m_matT );

	point.x = (long) (transf1.x * m_dScaleScreenCoord * m_PlotPar.dMulX);
	point.y = (long) (transf1.y * m_dScaleScreenCoord * m_PlotPar.dMulY);

	pDC->MoveTo(point);

	point.x = (long) (transf2.x * m_dScaleScreenCoord * m_PlotPar.dMulX);
	point.y = (long) (transf2.y * m_dScaleScreenCoord * m_PlotPar.dMulY);

	pDC->LineTo(point);
}

void CGraphCtrl::DrawAxisScale( CDC *pDC, const CRect &rcBounds, int X0, int Y0, int retCenter )
{
	double	mulx, muly;
	int			px, py;
	int			i, nFontSize;
	char		str[100];

	nFontSize = rcBounds.Height() / 37;
	mulx = m_PlotPar.dMulX;
	muly = m_PlotPar.dMulY;

	double	dx, dy, SS, SSy, Start, Starty, dist, disty, val;
	char		szFormat[20];
	int			num, addmulx, order, delta;

	CFont		tmpFont, *pPrevFont;
	
	tmpFont.CreateFont(nFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
					OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );
	addmulx = 1;

	dx = m_CoordPar.dXAxisUpp - m_CoordPar.dXAxisLow;
	SS = pow( 10, floor(log10(fabs(dx))) );
	Start = SS * floor( ( m_CoordPar.dXAxisLow + SS * 0.95 ) / SS );

	if( 2*SS > dx )
	{
		dist = SS / 4;
		num = 10;
		Start = SS * floor((m_CoordPar.dXAxisLow + dist) / SS );
	}
	else
	{
		dist = SS;
		num = (int) (floor(dx/SS)) + 1;
	}

	for( i=0; i<num; i++ )
	{
		val = Start + i*dist;
		if( val > m_CoordPar.dXAxisLow && val < m_CoordPar.dXAxisUpp )
		{
			order = (int) floor(log10(fabs(val)));
			memset( szFormat, 0, 20 );
			if( order > 2 || order < -2 )
				sprintf(szFormat, "%%5.3e");
			else
				sprintf(szFormat, "%%4.%df", -order+2 );
	
			px = (int) ((val) * mulx);
			py = (int) Y0;
			pDC->MoveTo( px, py - nFontSize/4 );
			pDC->LineTo( px, py + nFontSize/4 );
			sprintf(str, szFormat, (float) val );

			if( val == 0  && (retCenter == Y_AXIS_WITHIN_WINDOW || retCenter == CENTER_WITHIN_WINDOW) )
				;
			else
			{
				pPrevFont = pDC->SelectObject(&tmpFont);
				delta = pDC->GetTextExtent(str).cx;

				if( m_nCalledBy == DRAW_ITSELF )
					pDC->TextOut( px - strlen(str)*nFontSize/4, py - nFontSize/2, str );
				else
					pDC->TextOut( px - delta/2, py - nFontSize/2, str );
				pDC->SelectObject(pPrevFont);
			}
		}
	}

	dy = m_CoordPar.dYAxisUpp - m_CoordPar.dYAxisLow;
	SSy = pow( 10, floor(log10(fabs(dy))) );
	Starty = SSy * floor( ( m_CoordPar.dYAxisLow + SSy * 0.95 ) / SSy );

	if( 2*SSy > dy )
	{
		disty = SSy / 4;
		num = 10;
		Starty = SSy * floor((m_CoordPar.dYAxisLow + disty) / SSy );
	}
	else
	{
		disty = SSy;
		num = (int) (floor(dy/SSy)) + 1;
	}

	for( i=0; i<num; i++ )
	{
		val = Starty + i*disty;
		if( val > m_CoordPar.dYAxisLow && val < m_CoordPar.dYAxisUpp )
		{
			order = (int) floor(log10(fabs(val)));
			memset( szFormat, 0, 20 );
			if( order > 2 || order < -2 )
				sprintf(szFormat, "%%5.3e" );
			else
				sprintf(szFormat, "%%4.%df", -order+2 );

			px = (int) X0;
			py = (int) ((val) * muly);
			pDC->MoveTo( px - nFontSize/4, py );
			pDC->LineTo( px + nFontSize/4, py );
			sprintf(str, szFormat, (float) val );

			if( val == 0  && (retCenter == X_AXIS_WITHIN_WINDOW || retCenter == CENTER_WITHIN_WINDOW) )
				;
			else
			{
				pPrevFont = pDC->SelectObject(&tmpFont);
				pDC->TextOut( px + nFontSize/2, py + nFontSize*addmulx/2, str );
				pDC->SelectObject(pPrevFont);
			}
		}
	}
}

void CGraphCtrl::DrawLegend( CDC *pDC, const CRect &rcBounds )
{
	CPoint	print(0,0);
	CFont		*pPrevFont, aFonts[2];
	CPen		*pPrevPen, tmpPen, *penTmp;
	int			nLegendEntriesNum=0, i, nPenWidth, nFontSize, nFontSize2;
			
//		pDC->SetWindowOrg((int) (m_AnalPar.dXLow*m_PlotPar.dMulX - m_dExtraWidth) + m_PlotPar.pntOrg.x*rcBounds.Width()/100, 
//										(int) (m_AnalPar.dYUppTot*m_PlotPar.dMulY + m_dExtraHeight) + m_PlotPar.pntOrg.y*rcBounds.Height()/100 );
//			print = m_pntLegendPos;
//			pDC->DPtoLP(&print);
	double		dDiffX, dDiffY;

	dDiffX = m_CoordPar.dXAxisUpp - m_CoordPar.dXAxisLow;
	dDiffY = m_CoordPar.dYAxisUpp - m_CoordPar.dYAxisLow;
	print.x = (int) ((dDiffX * 1.16 * (m_pntLegendPos.x/100.) + m_CoordPar.dXAxisLow - dDiffX*0.08) * m_PlotPar.dMulX - m_PlotPar.pntOrg.x*rcBounds.Width()/100);
	print.y = (int) ((dDiffY * 1.16 * (m_pntLegendPos.y/100.) + m_CoordPar.dYAxisLow - dDiffY*0.08) * m_PlotPar.dMulY - m_PlotPar.pntOrg.y*rcBounds.Height()/100 );

	nPenWidth = rcBounds.Width() / 300;
	nFontSize = rcBounds.Height() / 36;
	nFontSize2 = rcBounds.Height() / 40;

	tmpPen.CreatePen(PS_SOLID, nPenWidth, RGB(0,0,0) );
	pPrevPen = pDC->SelectObject(&tmpPen);

	aFonts[0].CreateFont(nFontSize, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );
	aFonts[1].CreateFont(nFontSize2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Ariel" );
	
	// ispisi legendu
	if( m_bShowLegend == TRUE )
	{
		int		nX1, nY1, nX2, nY2, nMaxLegendLength, nMax, nTmp;
		
		nMax = 0;
		nMaxLegendLength = 0;
		nLegendEntriesNum=0;
		for( i=0; i<MAX_GRAPHS; i++ )
		{
			if( !m_aszLegend[i].IsEmpty() )
			{
				nLegendEntriesNum++;
				if( (nTmp=m_aszLegend[i].GetLength()) > nMaxLegendLength )
				{
					nMaxLegendLength = nTmp;
					nMax = i;
				}
			}
		}
		if( nLegendEntriesNum > 0 )
		{
			COLORREF	color;
			int				style, nDiffY, nLenX;

			pPrevFont = pDC->SelectObject(&aFonts[1]);

			if( m_nCalledBy == DRAW_ITSELF )
			{
				nDiffY = nFontSize2 * 4 / 3;
				nLenX = nFontSize2 * m_aszLegend[nMax].GetLength() / 4;
			
				m_nCalledBy = ON_DRAW;
			}
			else
			{
				nDiffY = pDC->GetTextExtent("Abraka").cy * 4 / 3;
				nLenX = pDC->GetTextExtent(m_aszLegend[nMax]).cx ;
			}
			nX1 = (int) ((print.x - nFontSize2/3));
			nY1 = (int) ((print.y + nFontSize2/3));
			nX2 = nX1 + (int) (4*nFontSize2 + nLenX);
			nY2 = nY1 - (int) (2*nFontSize2 + nDiffY * nLegendEntriesNum);
			
			pDC->SelectObject(&tmpPen);
			pDC->Rectangle(nX1, nY1, nX2, nY2 );

			pPrevFont = pDC->SelectObject(&aFonts[0]);
			pDC->TextOut((int) ((print.x + nFontSize2/5)), (int) (print.y), "Legenda :");
			
			color = RGB(0,0,0);
			style = PS_SOLID;

			for( i=0; i<MAX_GRAPHS; i++ )
			{
				if( !m_aszLegend[i].IsEmpty() )
				{
					if( m_bUseColor == TRUE )
						color = m_Colors[i];
					if( m_bUseLineStyles == TRUE )
						style = m_Styles[i];

					penTmp = new CPen(style, rcBounds.Height()/500+1, color);
					pDC->SelectObject(penTmp);

					pDC->MoveTo((int) ((print.x + nFontSize2/2)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );
					pDC->LineTo((int) ((print.x + nFontSize2*2)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );

					delete penTmp;

					pDC->SelectObject(&aFonts[1]);
					pDC->TextOut((int) ((print.x + nFontSize2*5/2)), (int) ((print.y - nDiffY*(i+1) )), m_aszLegend[i] );
				}
			}
			pDC->SelectObject(pPrevFont);
		}
	}
}

int CGraphCtrl::CenterWithinWindow( CPoint &pntOrigin )
{
	BOOL		retX, retY;

//	if( m_AnalPar.dXUpp >= 0 && m_AnalPar.dXLow <= 0 )
	if( m_CoordPar.dXAxisUpp >= 0 && m_CoordPar.dXAxisLow <= 0 )
	{
		retY = TRUE;			// znaèi da je Y-os vidljiva u prozoru
		pntOrigin.x = 0;
	}
	else
		retY = FALSE;

//	if( m_AnalPar.dYUppTot >= 0 && m_AnalPar.dYLowTot <= 0 )
	if( m_CoordPar.dYAxisUpp >= 0 && m_CoordPar.dYAxisLow <= 0 )
	{
		retX = TRUE;
		pntOrigin.y = 0;
	}
	else
		retX = FALSE;

	if( retX == TRUE && retY == TRUE )
		return CENTER_WITHIN_WINDOW;
	else if( retX == TRUE )
		return X_AXIS_WITHIN_WINDOW;
	else if( retY == TRUE )
		return Y_AXIS_WITHIN_WINDOW;
	else
		return NO_AXIS_WITHIN_WINDOW;
}

void CGraphCtrl::AnalyseDataRange( void )
{
	double	ymax, ymin;
	int			i, j;

	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) )
		{
			ymax = -1e30;
			ymin = 1e30;
			
			for( j=0; j<m_lPointsNum; j++ )
			{
				if( m_nPlotType == TRAJECTORY && (m_pdXVal[j] >= m_dStartX && m_pdXVal[j] <= m_dEndX)
						|| m_nPlotType == PHASE_2D || m_nPlotType == PHASE_3D )
				{
					if( m_apdYVal[i][j] > ymax )
						ymax = m_apdYVal[i][j];
					if( m_apdYVal[i][j] < ymin )
						ymin = m_apdYVal[i][j];
				}
			}
			
			m_Anal[i].dYLow = ymin;
			m_Anal[i].dYUpp = ymax;
		}

	m_AnalPar.dXLow = 1e30;
	m_AnalPar.dXUpp = -1e30;
	for( i=0; i<m_lPointsNum; i++ )
	{
		if( m_pdXVal[i] >= m_dStartX && m_pdXVal[i] <= m_dEndX )
		{
			if( m_pdXVal[i] < m_AnalPar.dXLow )
				m_AnalPar.dXLow = m_pdXVal[i];
			if( m_pdXVal[i] > m_AnalPar.dXUpp )
				m_AnalPar.dXUpp = m_pdXVal[i];
		}
	}
}

void CGraphCtrl::AnalyseGraphs( const CRect &rcBounds )
{
	int			i;

	m_AnalPar.dYLowTot = 1e30;
	m_AnalPar.dYUppTot = -1e30;

	if( m_nPlotType == TRAJECTORY || m_nPlotType == PHASE_2D )
	{
		for( i=0; i<MAX_GRAPHS; i++ )
		{
			if( IsValidGraphID(i) && m_bShowGraph[i] == TRUE )
			{
				if( m_Anal[i].dYLow < m_AnalPar.dYLowTot )
				{
					m_AnalPar.dYLowTot = m_Anal[i].dYLow;
					m_AnalPar.nMinY = i;
				}
				if( m_Anal[i].dYUpp > m_AnalPar.dYUppTot )
				{
					m_AnalPar.dYUppTot = m_Anal[i].dYUpp;
					m_AnalPar.nMaxY = i;
				}
			}
		}
	}
	else if( m_nPlotType == PHASE_3D )
	{
		if( m_bNeedRecalc == TRUE )
		{
			TransformToScreenCoord();
			m_bNeedRecalc = FALSE;
		}

		m_dScreenMaxX = m_dScreenMaxY = -1e30;
		m_dScreenMinX = m_dScreenMinY = 1e30;

		for( i=0; i<m_lPointsNum; i++ )
		{
			if( m_pTransf[i].x < m_dScreenMinX )
				m_dScreenMinX = m_pTransf[i].x;
			if( m_pTransf[i].x > m_dScreenMaxX )
				m_dScreenMaxX = m_pTransf[i].x;

			if( m_pTransf[i].y < m_dScreenMinY )
				m_dScreenMinY = m_pTransf[i].y;
			if( m_pTransf[i].y > m_dScreenMaxY )
				m_dScreenMaxY = m_pTransf[i].y;
		}
	}
	
	m_dExtraWidth = rcBounds.Width() * 0.04;
	// ako nema naslova, onda æemo manje suziti ekran po y-osi sužavati 
	if( m_strTitle.IsEmpty() )
		m_dExtraHeight = rcBounds.Height() * 0.02;
	else
		m_dExtraHeight = rcBounds.Height() * 0.08;

	if( m_nPlotType == TRAJECTORY )
	{
		if( m_nGraphNum > 0 )
		{
			m_PlotPar.dMulX = (rcBounds.Width() - 2*m_dExtraWidth) / (m_AnalPar.dXUpp - m_AnalPar.dXLow);
			
			for( int i=0; i<MAX_GRAPHS; i++ )
				if( IsValidGraphID(i) && m_bShowGraph[i] == TRUE )
					m_PlotPar.adMulY[i] = (rcBounds.Height() - 2*m_dExtraHeight) / (m_AnalPar.dYUppTot - m_AnalPar.dYLowTot);
			
			m_PlotPar.dMulY = (rcBounds.Height() - 2*m_dExtraHeight) / (m_AnalPar.dYUppTot - m_AnalPar.dYLowTot);

			m_CoordPar.dXAxisLow = m_AnalPar.dXLow;
			m_CoordPar.dXAxisUpp = m_AnalPar.dXUpp;
			m_CoordPar.dYAxisLow = m_AnalPar.dYLowTot;
			m_CoordPar.dYAxisUpp = m_AnalPar.dYUppTot;
		}
		else
		{
			m_PlotPar.dMulX = 1.;
			for( i=0; i<MAX_GRAPHS; i++ )
				m_PlotPar.adMulY[i] = 1.;
		}
	}
	else if( m_nPlotType == PHASE_2D )
	{
		int		xVar, yVar;

		xVar = m_nXAxisVar;
		yVar = m_nYAxisVar;

		m_PlotPar.dMulX = (rcBounds.Width() - 2*m_dExtraWidth) / (m_Anal[xVar].dYUpp - m_Anal[xVar].dYLow);
		m_PlotPar.dMulY = (rcBounds.Height() - 2*m_dExtraHeight) / (m_Anal[yVar].dYUpp - m_Anal[yVar].dYLow);

		m_CoordPar.dXAxisLow = m_Anal[xVar].dYLow;
		m_CoordPar.dXAxisUpp = m_Anal[xVar].dYUpp;
		m_CoordPar.dYAxisLow = m_Anal[yVar].dYLow;
		m_CoordPar.dYAxisUpp = m_Anal[yVar].dYUpp;
	}
	else if( m_nPlotType == PHASE_3D )
	{
		int			xVar, yVar, zVar;

		xVar = m_nXAxisVar;
		yVar = m_nYAxisVar;
		zVar = m_nZAxisVar;

/*		GetControlSize(&size_x, &size_y);

		X = size_x / (m_dScreenMaxX - m_dScreenMinX);
		Y = size_y / (m_dScreenMaxY - m_dScreenMinY);
		m_PlotPar.dMulX = X;
		m_PlotPar.dMulY = Y;
*/

		m_PlotPar.dMulX = (rcBounds.Width() - 2*m_dExtraWidth) / (m_dScreenMaxX - m_dScreenMinX);
		m_PlotPar.dMulY = (rcBounds.Height() - 2*m_dExtraHeight) / (m_dScreenMaxY - m_dScreenMinY);

		m_CoordPar.dXAxisLow = m_Anal[xVar].dYLow;
		m_CoordPar.dXAxisUpp = m_Anal[xVar].dYUpp;
		m_CoordPar.dYAxisLow = m_Anal[yVar].dYLow;
		m_CoordPar.dYAxisUpp = m_Anal[yVar].dYUpp;
		m_CoordPar.dZAxisLow = m_Anal[zVar].dYLow;
		m_CoordPar.dZAxisUpp = m_Anal[zVar].dYUpp;
	}
}

BOOL CGraphCtrl::IsValidGraphID( int nID )
{
	if( nID >= 0 && nID < MAX_GRAPHS )
		if( m_bFreeGraph[nID] == FALSE )
		{
			if( m_apdYVal[nID] == NULL )
				ASSERT(1);									// ovo se ne bi smjelo desiti, graf je zauzet, a nije alocirana memorija za tocke
			
			return TRUE;
		}
	return FALSE;
}

int	CGraphCtrl::GetFreeGraph( void )
{
	for( int i=0; i<MAX_GRAPHS; i++ )
		if( m_bFreeGraph[i] == TRUE )
			return i;
	
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::DoPropExchange - Persistence support

void CGraphCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::OnResetState - Reset control to default state

void CGraphCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl::AboutBox - Display an "About" box to the user

void CGraphCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GRAPH);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl message handlers

void CGraphCtrl::OnTitleChanged() 
{
	m_bViewTypeChanged = TRUE;

	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnXAxisTitleChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnUseColorChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnUseLineStylesChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnShowLegendChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnShowCoordSystemChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnShowScaleChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnScaleTypeChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnXAxisVarChanged() 
{
	if( m_nPlotType == PHASE_2D || m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;
	}

	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnYAxisVarChanged() 
{
	if( m_nPlotType == PHASE_2D || m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;
	}

	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnZAxisVarChanged() 
{
	if( m_nPlotType == PHASE_2D || m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;
	}

	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnScaleIntervalsNumChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnPlotTypeChanged() 
{
	m_bViewTypeChanged = TRUE;

	if( m_nPlotType == PHASE_3D && m_bNeedRecalc)
		TransformToScreenCoord();

	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnStartXChanged() 
{
	m_bViewIntervalChanged = TRUE;
	InvalidateControl();
	SetModifiedFlag();
}

void CGraphCtrl::OnEndXChanged() 
{
	m_bViewIntervalChanged = TRUE;
	InvalidateControl();
	SetModifiedFlag();
}

short CGraphCtrl::AddNewGraph(double FAR* pdYVal, long lPointsNum, LPCTSTR pchLegend) 
{
	int		ret;

	if( m_nGraphNum > 0 )
	{
		int	nID = GetFreeGraph();
		if( nID >= 0 && nID < MAX_GRAPHS )
		{
			if( lPointsNum == m_lPointsNum )
			{
				m_apdYVal[nID] = new double[lPointsNum];
				memcpy(m_apdYVal[nID], pdYVal, sizeof(double) * lPointsNum);

				m_aszLegend[nID] = pchLegend;

				m_bFreeGraph[nID] = FALSE;
				m_bShowGraph[nID] = TRUE;
				m_nGraphNum++;
				ret=nID;
			
				AnalyseDataRange();
				m_bViewContentChanged = TRUE;
			}
			else	ret=WRONG_POINTS_NUM;
		}
		else	ret=MAX_GRAPH_NUM;
	}
	else	ret=NO_X_AXIS_VALUES;

	InvalidateControl();
	return ret;
}

short CGraphCtrl::AddNewGraphWithX(double FAR* pdXVal, double FAR* pdYVal, long lPointsNum, LPCTSTR pchLegend) 
{
	RemoveAllGraphs();

	m_pdXVal = new double[lPointsNum];
	memcpy(m_pdXVal, pdXVal, sizeof(double)*lPointsNum);
	m_apdYVal[0] = new double[lPointsNum];
	memcpy(m_apdYVal[0], pdYVal, sizeof(double)*lPointsNum);

	m_aszLegend[0] = pchLegend;

	m_bFreeGraph[0] = FALSE;
	m_bShowGraph[0] = TRUE;
	m_lPointsNum = lPointsNum;
	m_nGraphNum = 1;

	AnalyseDataRange();
	m_bViewContentChanged = TRUE;

	InvalidateControl();
	
	return 0;
}

void CGraphCtrl::RemoveGraph(short nID) 
{
	if( IsValidGraphID(nID) )
	{
		delete []m_apdYVal[nID];
		m_apdYVal[nID] = NULL;
		m_aszLegend[nID] = "";

		m_bFreeGraph[nID] = TRUE;
		m_nGraphNum--;

		if( m_nGraphNum == 0 )			// znaci da su uklonjeni svi grafovi, pa treba maknuti i podatke za x-os
		{
			delete []m_pdXVal;
			m_pdXVal = NULL;
			m_lPointsNum = 0;
		}

		AnalyseDataRange();
		m_bViewContentChanged = TRUE;
	}
	
	InvalidateControl();
}

void CGraphCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// ako postavljamo poziciju na ekranu gdje æe se nalaziti legenda
	CClientDC dc(this);

	dc.Ellipse(point.x, point.y, point.x+5, point.y+5);

	if( m_setLegendPosFlag == TRUE )
	{
		int		x, y;
		GetControlSize(&x, &y);

		m_pntLegendPos.x = point.x * 100 / x;
		m_pntLegendPos.y = 100 - point.y * 100 / y;
		
		InvalidateControl();

		m_setLegendPosFlag = FALSE;
	}
	// samo kod crtanja trajektorije mozemo birati neki od grafova
	else if( m_nPlotType == TRAJECTORY )
	{
/*
		char		str[200];
		CClientDC dc(this);

		sprintf(str, "Fizicke : x = %d, y = %d", point.x, point.y);
		AfxMessageBox(str);
		
		int		x, y;
		GetControlSize(&x, &y);

		dc.DPtoLP(&point);
		sprintf(str, "Logicke : x = %d, y = %d", point.x, point.y);
		AfxMessageBox(str);
*/
	}
	
	COleControl::OnLButtonDown(nFlags, point);
}

void CGraphCtrl::RemoveAllGraphs() 
{
	for( int i=0; i<MAX_GRAPHS; i++ )
		RemoveGraph(i);
	
	if( m_pdXVal != NULL )
		delete []m_pdXVal;
	m_lPointsNum = 0;
	m_bViewContentChanged = TRUE;

	InvalidateControl();
}

short CGraphCtrl::GetGraphNum() 
{
	return m_nGraphNum;
}

long CGraphCtrl::GetPointsNum() 
{
	return m_lPointsNum;
}


short CGraphCtrl::ShowGraph(short nID, BOOL bShow) 
{
	if( IsValidGraphID(nID) )
	{
		m_bShowGraph[nID] = bShow;
		InvalidateControl();

		return 1;
	}
	else
		return -1;
}

short CGraphCtrl::Resize(short nXPercent, short nYPercent) 
{
	InvalidateControl();

	return 0;
}

short CGraphCtrl::Move(short nXPercent, short nYPercent) 
{
	m_PlotPar.pntOrg.x -= nXPercent;
	m_PlotPar.pntOrg.y += nYPercent;

	InvalidateControl();

	return 0;
}

void CGraphCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	m_bViewTypeChanged = TRUE;
	InvalidateControl();	
}

void CGraphCtrl::SetLegendPos(short nXPercent, short nYPercent) 
{
	if( nXPercent >=0 && nXPercent < 100 )
		m_pntLegendPos.x = nXPercent;
	
	if( nYPercent >=0 && nYPercent < 100 )
		m_pntLegendPos.y = nYPercent;

	InvalidateControl();
}

void CGraphCtrl::DrawItself(long FAR* pdc, short x1, short y1, short x2, short y2) 
{
	CDC *pDC = (CDC *) pdc;
	CRect rcBounds(x1,y1,x2,y2), rcInvalid(x1,y1,x2,y2);

	m_nCalledBy = DRAW_ITSELF;
	OnDraw(pDC,rcBounds, rcInvalid);
}


void CGraphCtrl::OnSetLegendPosFlagChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CGraphCtrl::OnDistanceChanged() 
{
	// TODO: Add notification handler code
	if( m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;

		InvalidateControl();
	}
	SetModifiedFlag();
}

void CGraphCtrl::OnAzimuthChanged() 
{
	// TODO: Add notification handler code
	if( m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;

		InvalidateControl();
	}
	SetModifiedFlag();
}

void CGraphCtrl::OnVerticalAngleChanged() 
{
	// TODO: Add notification handler code
	if( m_nPlotType == PHASE_3D )
	{
		m_bViewContentChanged = TRUE;
		m_bNeedRecalc = TRUE;

		InvalidateControl();
	}
	SetModifiedFlag();
}

BOOL CGraphCtrl::DrawToMetafile(LPCTSTR FileName) 
{
	CMetaFileDC		meta;
	meta.Create(FileName);

	CRect rcBounds, rcInvalid;
	GetRectInContainer(rcBounds);
	rcInvalid = rcBounds;

	m_nCalledBy = DRAW_METAFILE;
	OnDraw(&meta,rcBounds, rcInvalid);

	meta.Close();

	return TRUE;
}
