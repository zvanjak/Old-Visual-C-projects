// SimpleGraphCtl.cpp : Implementation of the CSimpleGraphCtrl ActiveX Control class.

#include "stdafx.h"
#include "SimpleGraph.h"
#include "SimpleGraphCtl.h"
#include "SimpleGraphPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSimpleGraphCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSimpleGraphCtrl, COleControl)
	//{{AFX_MSG_MAP(CSimpleGraphCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSimpleGraphCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSimpleGraphCtrl)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "Title", m_strTitle, OnTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "UseColors", m_bUseColors, OnUseColorsChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "UseLineStyles", m_bUseLineStyles, OnUseLineStylesChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "ShowLegend", m_bShowLegend, OnShowLegendChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "ShowCoordSystem", m_bShowCoordSystem, OnShowCoordSystemChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "StartX", m_dStartX, OnStartXChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "EndX", m_dEndX, OnEndXChanged, VT_R8)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "AllowDifferentYScale", m_bAllowDifferentYScale, OnAllowDifferentYScaleChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CSimpleGraphCtrl, "ShowCommandButtons", m_bShowCommandButtons, OnShowCommandButtonsChanged, VT_BOOL)
	DISP_FUNCTION(CSimpleGraphCtrl, "AddGraph", AddGraph, VT_I2, VTS_PR4 VTS_PR4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CSimpleGraphCtrl, "RemoveGraph", RemoveGraph, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CSimpleGraphCtrl, "RemoveAllGraphs", RemoveAllGraphs, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSimpleGraphCtrl, "ShowGraph", ShowGraph, VT_BOOL, VTS_BOOL)
	DISP_FUNCTION(CSimpleGraphCtrl, "DrawToMetafile", DrawToMetafile, VT_BOOL, VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION(CSimpleGraphCtrl, "SetLegendPos", SetLegendPos, VT_BOOL, VTS_R4 VTS_R4)
	DISP_FUNCTION(CSimpleGraphCtrl, "DoesGraphAlreadyExist", DoesGraphAlreadyExist, VT_BOOL, VTS_PR4 VTS_PR4 VTS_I4)
	DISP_FUNCTION(CSimpleGraphCtrl, "ChangeGraphData", ChangeGraphData, VT_EMPTY, VTS_I2 VTS_PR4 VTS_PR4 VTS_I4 VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CSimpleGraphCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSimpleGraphCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSimpleGraphCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSimpleGraphCtrl, 1)
	PROPPAGEID(CSimpleGraphPropPage::guid)
END_PROPPAGEIDS(CSimpleGraphCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSimpleGraphCtrl, "SIMPLEGRAPH.SimpleGraphCtrl.1",
	0xfa54aee2, 0xb3c1, 0x4897, 0xaf, 0xda, 0x19, 0xd2, 0xfd, 0xed, 0x9b, 0x3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSimpleGraphCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSimpleGraph =
		{ 0xcf614461, 0x608b, 0x40f3, { 0xa4, 0x62, 0xcf, 0x40, 0x94, 0x53, 0xf, 0xe2 } };
const IID BASED_CODE IID_DSimpleGraphEvents =
		{ 0x611cb629, 0xefbb, 0x4e44, { 0xb5, 0x19, 0x94, 0x3, 0xb6, 0x90, 0xff, 0x77 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSimpleGraphOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSimpleGraphCtrl, IDS_SIMPLEGRAPH, _dwSimpleGraphOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::CSimpleGraphCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSimpleGraphCtrl

BOOL CSimpleGraphCtrl::CSimpleGraphCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_SIMPLEGRAPH,
			IDB_SIMPLEGRAPH,
			afxRegApartmentThreading,
			_dwSimpleGraphOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::CSimpleGraphCtrl - Constructor

CSimpleGraphCtrl::CSimpleGraphCtrl()
{
	InitializeIIDs(&IID_DSimpleGraph, &IID_DSimpleGraphEvents);

	// TODO: Initialize your control's instance data here.
	m_strTitle = "";

	m_bShowCommandButtons = FALSE;
	m_bUseColors = FALSE;
	m_bUseLineStyles = TRUE;

	m_bShowLegend = TRUE;
	m_pntLegendPos = CPoint(60,85);
		
	m_bShowCoordSystem = TRUE;

	m_bViewContentChanged = FALSE;
	m_dExtraWidth = m_dExtraHeight = 10;

	m_dStartX = 0.;
	m_dEndX = 1.0;
	m_bViewIntervalChanged = FALSE;

	m_dScaleScreenCoord = 5;

	m_dScreenMaxX = -1e30;
	m_dScreenMinX = 1e30;
	m_dScreenMaxY = -1e30;
	m_dScreenMinY = 1e30;

	m_nGraphNum = 0;
	m_nSelected = -1;
	
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
		m_PlotPar.adMulY[i] = 1.;
		m_bFreeGraph[i] = TRUE;
		m_bShowGraph[i] = TRUE;

		m_Anal[i].dYLow = 1e30;
		m_Anal[i].dYUpp = -1e30;
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
	m_Styles[4] = PS_DASHDOTDOT;
/*
	float x[200], y1[200], y2[200], y3[200], y4[200], y5[200], sig;

	sig = 1.;

	for( i=0; i<200; i++ )
	{
		x[i] = (float) (i / 200. * 15 - 7.);
		
		y1[i] = (float) (20*sin(x[i]));
		y2[i] = (float) (15*cos(x[i]+0.7));
		y3[i] = (float) ((x[i]+2)*(x[i]-3)*(x[i]-6));
		y3[i] /= 3.f;
		y4[i] = (float) (7/sig/sqrt(6.28) * exp(-(x[i]-8)*(x[i]-7)/(2*sig*sig)));
		y5[i] = (float) (20*exp(-x[i]/5) * cos(x[i]*5));
	}
	m_dEndX = 15.0;

	AddGraph(x, y1, 200, "Graph 1 - sinus");
	AddGraph(x, y2, 200, "Graph 2 - kosinus");
	AddGraph(x, y3, 200, "Graph 3 - polinom 3. stupnja");
	AddGraph(x, y4, 200, "Graph 4 - Gaussova krivulja");
	AddGraph(x, y5, 200, "Graph 5 - amplitudna modulacija");

	m_strTitle = "Proba grafova";
	m_bViewContentChanged = TRUE;
*/
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::~CSimpleGraphCtrl - Destructor

CSimpleGraphCtrl::~CSimpleGraphCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::OnDraw - Drawing function

void CSimpleGraphCtrl::OnDraw(CDC* pDC, const CRect& rcBounds, const CRect& rcInvalid)
{
	pDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	pDC->SetMapMode(MM_ANISOTROPIC);
	
//	if( m_nCalledBy == ON_DRAW )
	pDC->SetWindowExt(1, -1);
//	else
//		pDC->SetWindowExt(rcBounds.Width(),-rcBounds.Height());

	CFont		tmpFont, *pPrevFont;
	CSize		size;
	tmpFont.CreateFont(	rcBounds.Height()*4/36/3, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
											OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Roman");
	pPrevFont = pDC->SelectObject(&tmpFont);
	size			= pDC->GetTextExtent(m_strTitle);
	
	pDC->TextOut( rcBounds.left + (rcBounds.Width() - size.cx)/2, 
								rcBounds.top - size.cy/2, m_strTitle);
	pDC->SelectObject(pPrevFont);

	if( m_bViewIntervalChanged == TRUE )
	{
		AnalyseDataRange();
		AnalyseGraphs(rcBounds);

		m_bViewIntervalChanged = FALSE;
	}
	if( m_bViewContentChanged == TRUE )
	{
		AnalyseGraphs(rcBounds);
		
		m_bViewContentChanged = FALSE;
	}

	DrawTrajectory(pDC,rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::DoPropExchange - Persistence support

void CSimpleGraphCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::OnResetState - Reset control to default state

void CSimpleGraphCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl::AboutBox - Display an "About" box to the user

void CSimpleGraphCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_SIMPLEGRAPH);
	dlgAbout.DoModal();
}


void CSimpleGraphCtrl::DrawTrajectory( CDC *pDC, const CRect &rcBounds )
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

	pDC->SetWindowOrg((int) (m_AnalPar.dXLow*m_PlotPar.dMulX - m_dExtraWidth) 
													+ m_PlotPar.pntOrg.x*rcBounds.Width()/100, 
										(int) (m_AnalPar.dYUppTot*m_PlotPar.dMulY + m_dExtraHeight) 
													+ m_PlotPar.pntOrg.y*rcBounds.Height()/100 );

	DrawCoordSystem(pDC, rcBounds);

	color = RGB(0,0,0);
	style = PS_SOLID;

	float		x, y;
	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) && m_bShowGraph[i] == TRUE )
		{
			if( m_bUseColors == TRUE )
				color = m_Colors[i];
			if( m_bUseLineStyles == TRUE )
				style = m_Styles[i];

			penTmp = new CPen(style, rcBounds.Height()/1000+1, color);
			pDC->SelectObject(penTmp);

			if( Graph[i].GetPointsNum() > 0 )
			{
				Graph[i].GetX(0, &x);
				if( x >= m_dStartX && x <= m_dEndX )
				{
					Graph[i].GetY(0, &y);
					
					pDC->MoveTo((int) (x * m_PlotPar.dMulX), (int) (y * m_PlotPar.dMulY) );
					bStarted = TRUE;
				}
				else
					bStarted = FALSE;

				for( j=1; j<Graph[i].GetPointsNum(); j++ )
				{
					Graph[i].GetX(j, &x);
					if( x >= m_dStartX && x <= m_dEndX )
					{
						Graph[i].GetY(j, &y);
						
						if( bStarted == TRUE )
							pDC->LineTo((int) (x * m_PlotPar.dMulX), (int) (y * m_PlotPar.dMulY));
						else
						{
							pDC->MoveTo((int) (x * m_PlotPar.dMulX), (int) (y * m_PlotPar.dMulY) );
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

void CSimpleGraphCtrl::DrawCoordSystem( CDC *pDC, const CRect & rcBounds )
{
	CPen		*pPrevPen, tmpPen;
	CPoint	pntCenter;
	double	x,y, mulx, muly;
	int			retCenter, nPenWidth;
	int			X0, Y0;				// koordinate centra koordinatnog sustav (tj. sjecista osi)

	nPenWidth = rcBounds.Width() / 250;

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

	DrawLegend(pDC, rcBounds);
}

void CSimpleGraphCtrl::DrawAxisScale( CDC *pDC, const CRect &rcBounds, int X0, int Y0, int retCenter )
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
					OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Arial" );
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

				if( /*m_nCalledBy == DRAW_ITSELF*/ 1 )
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

void CSimpleGraphCtrl::DrawLegend( CDC *pDC, const CRect &rcBounds )
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
		OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Arial" );
	aFonts[1].CreateFont(nFontSize2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Arial" );
	
	// ispisi legendu
	if( m_bShowLegend == TRUE )
	{
		int		nX1, nY1, nX2, nY2, nLenX;
		CSize	sz;
		
		pPrevFont = pDC->SelectObject(&aFonts[1]);

		nLenX = 0;
		nLegendEntriesNum=0;
		for( i=0; i<MAX_GRAPHS; i++ ) {
			if( !m_aszLegend[i].IsEmpty() ) {
				nLegendEntriesNum++;

				sz = pDC->GetTextExtent(m_aszLegend[i]);
				if( sz.cx > nLenX )
					nLenX = sz.cx;
			}
		}

		if( nLegendEntriesNum > 0 )
		{
			COLORREF	color;
			int				style, nDiffY;

			nDiffY = nFontSize2 * 4 / 3;

			nX1 = (int) ((print.x - nFontSize2/3));
			nY1 = (int) ((print.y + nFontSize2/3));
			nX2 = nX1 + (int) (6*nFontSize2 + nLenX);
			nY2 = nY1 - (int) (2*nFontSize2 + nDiffY * nLegendEntriesNum);
			
//			pDC->SelectObject(&tmpPen);
//			pDC->Rectangle(nX1, nY1, nX2, nY2 );

			pPrevFont = pDC->SelectObject(&aFonts[0]);
//			pDC->TextOut((int) ((print.x)), (int) (print.y-10), "Legenda :");
			pDC->TextOut((int) ((print.x - 15 * nFontSize2/5)), (int) (print.y-5), "Legenda :");
			
			color = RGB(0,0,0);
			style = PS_SOLID;

			for( i=0; i<MAX_GRAPHS; i++ )
			{
				if( !m_aszLegend[i].IsEmpty() )
				{
					if( m_bUseColors == TRUE )
						color = m_Colors[i];
					if( m_bUseLineStyles == TRUE )
						style = m_Styles[i];

					penTmp = new CPen(style, rcBounds.Height()/1000+1, color);
					pDC->SelectObject(penTmp);

					pDC->MoveTo((int) ((print.x -30)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );
					pDC->LineTo((int) ((print.x + 20)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );
//					pDC->MoveTo((int) ((print.x + nFontSize2/2)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );
//					pDC->LineTo((int) ((print.x + nFontSize2*3)),(int) ((print.y - nDiffY*(i+1) - nFontSize2/2)) );

					delete penTmp;

					pDC->SelectObject(&aFonts[1]);
					pDC->TextOut((int) ((print.x + 30/*nFontSize2*7/2*/)), (int) ((print.y - nDiffY*(i+1) )), m_aszLegend[i] );
				}
			}
			pDC->SelectObject(pPrevFont);
		}
	}
}

int CSimpleGraphCtrl::CenterWithinWindow( CPoint &pntOrigin )
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

void CSimpleGraphCtrl::AnalyseDataRange( void )
{
	float		x, y;
	double	ymax, ymin;
	int			i, j;

	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) )
		{
			ymax = -1e30;
			ymin = 1e30;
			
			for( j=0; j<Graph[i].GetPointsNum(); j++ )
			{
				Graph[i].GetX(j, &x);

				if( x >= m_dStartX && x <= m_dEndX )
				{
					Graph[i].GetY(j, &y);

					if( y > ymax )
						ymax = y;
					if( y < ymin )
						ymin = y;
				}
			}
			
			m_Anal[i].dYLow = ymin;
			m_Anal[i].dYUpp = ymax;
		}

	m_AnalPar.dXLow = 1e30;
	m_AnalPar.dXUpp = -1e30;
	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) )
			for( j=0; j<Graph[i].GetPointsNum(); j++ )
			{
				Graph[i].GetX(j, &x);

				if( x >= m_dStartX && x <= m_dEndX )
				{
					if( x < m_AnalPar.dXLow )
						m_AnalPar.dXLow = x;
					if( x > m_AnalPar.dXUpp )
						m_AnalPar.dXUpp = x;
				}
			}
}

void CSimpleGraphCtrl::AnalyseGraphs( const CRect &rcBounds )
{
	int			i;

	m_AnalPar.dYLowTot = 1e30;
	m_AnalPar.dYUppTot = -1e30;

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
	
	m_dExtraWidth = rcBounds.Width() * 0.04;
	// ako nema naslova, onda æemo manje suziti ekran po y-osi sužavati 
	if( m_strTitle.IsEmpty() )
		m_dExtraHeight = rcBounds.Height() * 0.02;
	else
		m_dExtraHeight = rcBounds.Height() * 0.08;

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

BOOL CSimpleGraphCtrl::IsValidGraphID( int nID )
{
	if( nID >= 0 && nID < MAX_GRAPHS )
		if( m_bFreeGraph[nID] == FALSE )
		{
/*
			if( m_apdYVal[nID] == NULL )
				ASSERT(1);									// ovo se ne bi smjelo desiti, graf je zauzet, a nije alocirana memorija za tocke
*/			
			return TRUE;
		}
	return FALSE;
}

BOOL	CSimpleGraphCtrl::GetFreeGraph( int *outInd )
{
	for( int i=0; i<MAX_GRAPHS; i++ )
		if( m_bFreeGraph[i] == TRUE ) {
			*outInd = i;
			return TRUE;
		}
	
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl message handlers

void CSimpleGraphCtrl::OnTitleChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnUseColorsChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnUseLineStylesChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnShowLegendChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnShowCoordSystemChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnStartXChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnEndXChanged() 
{
	SetModifiedFlag();
}

void CSimpleGraphCtrl::OnAllowDifferentYScaleChanged() 
{
	SetModifiedFlag();
}

short CSimpleGraphCtrl::AddGraph(float FAR* XValues, float FAR* YValues, long PointsNum, LPCTSTR Legend) 
{
	int	GraphID;

	if( GetFreeGraph(&GraphID) == TRUE ) 
	{
		Graph[GraphID].SetGraphData(PointsNum, XValues, YValues);

		m_nGraphNum++;
		m_aszLegend[GraphID] = Legend;
		m_bFreeGraph[GraphID] = FALSE;
		m_bShowGraph[GraphID] = TRUE;
	}
	else
		return FALSE;		// nema više slobodnih grafova

	AnalyseDataRange();
	m_bViewContentChanged = TRUE;

	InvalidateControl();

	return 0;
}

void CSimpleGraphCtrl::ChangeGraphData(short GraphID, float FAR* XValues, float FAR* YValues, long PointsNum, LPCTSTR Legend) 
{
	if( IsValidGraphID(GraphID) ) 
	{
		Graph[GraphID].SetGraphData(PointsNum, XValues, YValues);

		m_aszLegend[GraphID] = Legend;
		
		AnalyseDataRange();
		m_bViewContentChanged = TRUE;

		InvalidateControl();
	}
}

BOOL CSimpleGraphCtrl::RemoveGraph(short GraphID) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

BOOL CSimpleGraphCtrl::RemoveAllGraphs() 
{
	for( int i=0; i<MAX_GRAPHS; i++ ) {
		if(m_bFreeGraph[i] == FALSE ) {
			Graph[i].~CGraphData();
			m_bFreeGraph[i] = TRUE;
			m_bShowGraph[i] = FALSE;
			m_aszLegend[i] = "";
		}
	}
	m_nGraphNum = 0;

	return TRUE;
}

BOOL CSimpleGraphCtrl::ShowGraph(BOOL GraphID) 
{
	// TODO: Add your dispatch handler code here

	return TRUE;
}

void CSimpleGraphCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	m_bViewIntervalChanged = TRUE;
	InvalidateControl();	
}

void CSimpleGraphCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonDown(nFlags, point);
}

void CSimpleGraphCtrl::OnShowCommandButtonsChanged() 
{
	if( m_bShowCommandButtons == TRUE ) {
		pBox = new CButton();
		pBox->Create("Left",BS_PUSHBUTTON | WS_VISIBLE, CRect(0,0,50,15), this, 87678);
		pBox->ShowWindow(TRUE);
	}

	SetModifiedFlag();
}

BOOL CSimpleGraphCtrl::DrawToMetafile(LPCTSTR FileName, long ExtentX, long ExtentY) 
{
	CMetaFileDC		meta;
	meta.Create(FileName);
	
	CClientDC		dc(this);
	dc.SetMapMode(MM_ANISOTROPIC);
	
	meta.SetAttribDC(dc.m_hAttribDC);

	CRect		rcBounds(0,0,ExtentX,-ExtentY);

	CFont		tmpFont, *pPrevFont;
	CSize		size;
	tmpFont.CreateFont(	rcBounds.Height()*4/36/3, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
											OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Roman");
	pPrevFont = meta.SelectObject(&tmpFont);
	size			= meta.GetTextExtent(m_strTitle);
	
	meta.TextOut( rcBounds.left + (rcBounds.Width() - size.cx)/2, 
								rcBounds.top - size.cy/2, m_strTitle);
	meta.SelectObject(pPrevFont);

	AnalyseGraphs(rcBounds);
	DrawTrajectory(&meta,rcBounds);

	m_bViewContentChanged = TRUE;
	InvalidateControl();

	return TRUE;
}

BOOL CSimpleGraphCtrl::SetLegendPos(float XPos, float YPos) 
{
	m_pntLegendPos = CPoint((int) XPos,(int) YPos);

	return TRUE;
}

BOOL CSimpleGraphCtrl::DoesGraphAlreadyExist(float FAR* XValues, float FAR* YValues, long PointsNum ) 
{
	float		x, y;

	for( int i=0; i<MAX_GRAPHS; i++ ) {
		if( IsValidGraphID(i) ) 
		{
			if( Graph[i].GetPointsNum() == PointsNum ) {
				for( int j=0; j<PointsNum; j++ ) {
					Graph[i].GetX(j, &x);
					Graph[i].GetY(j, &y);
					
					if( x!=XValues[j] || y!=YValues[j] )
						break;
				}
				// ukoliko smo prošli kroz cijelo polje i svi su bili isti, to je to
				if( j == PointsNum )
					return TRUE;
			}
		}
	}
	return FALSE;
}
