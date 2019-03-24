// MathGraphCtl.cpp : Implementation of the CMathGraphCtrl ActiveX Control class.

#include "stdafx.h"
#include "MathGraph.h"
#include "MathGraphCtl.h"

#include "MathGraphPpg.h"
#include "MathGraphSecPage.h"
#include "MathGraphStatPage.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMathGraphCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_MSG_MAP(CMathGraphCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMathGraphCtrl)
	DISP_PROPERTY(CMathGraphCtrl, "XAxisVar", m_xAxisVar, VT_I2)
	DISP_PROPERTY(CMathGraphCtrl, "YAxisVar", m_yAxisVar, VT_I2)
	DISP_PROPERTY(CMathGraphCtrl, "ZAxisVar", m_zAxisVar, VT_I2)
	DISP_PROPERTY_NOTIFY(CMathGraphCtrl, "Title", m_strTitle, OnTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CMathGraphCtrl, "GraphType", m_graphType, OnGraphTypeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CMathGraphCtrl, "ShowLegend", m_bShowLegend, OnShowLegendChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CMathGraphCtrl, "UseColors", m_bUseColors, OnUseColorsChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CMathGraphCtrl, "UseLineStyles", m_bUseLineStyles, OnUseLineStylesChanged, VT_BOOL)
	DISP_PROPERTY_EX(CMathGraphCtrl, "CurveNum", GetCurveNum, SetNotSupported, VT_I2)
	DISP_FUNCTION(CMathGraphCtrl, "AddNewGraph", AddNewGraph, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CMathGraphCtrl, "RemoveGraph", RemoveGraph, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CMathGraphCtrl, "AddPoint", AddPoint, VT_I2, VTS_I2 VTS_R8 VTS_R8)
	DISP_FUNCTION(CMathGraphCtrl, "AddPoint3D", AddPoint3D, VT_I2, VTS_I2 VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION(CMathGraphCtrl, "SetLegend", SetLegend, VT_EMPTY, VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CMathGraphCtrl, "SetDim", SetDim, VT_EMPTY, VTS_I2)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMathGraphCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMathGraphCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMathGraphCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMathGraphCtrl, 3)
	PROPPAGEID(CMathGraphPropPage::guid)
	PROPPAGEID(CMathGraphSecPage::guid)
	PROPPAGEID(CMathGraphStatPage::guid)
END_PROPPAGEIDS(CMathGraphCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMathGraphCtrl, "MATHGRAPH.MathGraphCtrl.1",
	0x81936d29, 0xbe53, 0x11d1, 0xaf, 0xf7, 0, 0, 0xc0, 0x3e, 0x61, 0x8c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMathGraphCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMathGraph =
		{ 0x81936d27, 0xbe53, 0x11d1, { 0xaf, 0xf7, 0, 0, 0xc0, 0x3e, 0x61, 0x8c } };
const IID BASED_CODE IID_DMathGraphEvents =
		{ 0x81936d28, 0xbe53, 0x11d1, { 0xaf, 0xf7, 0, 0, 0xc0, 0x3e, 0x61, 0x8c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMathGraphOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMathGraphCtrl, IDS_MATHGRAPH, _dwMathGraphOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMathGraphCtrl

BOOL CMathGraphCtrl::CMathGraphCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MATHGRAPH,
			IDB_MATHGRAPH,
			afxRegInsertable | afxRegApartmentThreading,
			_dwMathGraphOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("MathGraph.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 ZPM";


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CMathGraphCtrl::CMathGraphCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CMathGraphCtrl::CMathGraphCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::CMathGraphCtrl - Constructor

CMathGraphCtrl::CMathGraphCtrl()
{
	InitializeIIDs(&IID_DMathGraph, &IID_DMathGraphEvents);

	// TODO: Initialize your control's instance data here.
	int		i;

	m_nCurveNum = 0;
	m_xAxisVar = 0;
	m_yAxisVar = 0;
	m_zAxisVar = 0;

	for( i=0; i<MAX_GRAPHS; i++ )
	{
		m_abFreeGraph[i] = true;
		
		m_astrYAxis[i] = "";
		m_astrLegend[i] = "";

		m_apvecX[i] = NULL;
		m_apvecY[i] = NULL;
		m_alPointsNum[i] = 0;
	}
	m_pvecZ = NULL;

	m_strXAxis = "";
	m_strZAxis = "";

	m_bStatUpdated = false;
	
	m_graphType = TRAJECTORY;
	m_eDim = PLOT_2D;

	m_nSelectedGraph = NONE_SELECTED;
	m_bUseColors = TRUE;
	m_bUseLineStyles = FALSE;
	m_bShowLegend = FALSE;

	m_Colors[0] = RGB(0,0,0);
	m_Colors[1] = RGB(255,0,0);
	m_Colors[2] = RGB(0,255,0);
	m_Colors[3] = RGB(0,0,255);
	m_Colors[4] = RGB(255,0,120);

	m_Styles[0] = PS_SOLID;
	m_Styles[1] = PS_DASH;
	m_Styles[2] = PS_DOT;
	m_Styles[3] = PS_DASHDOT;
	m_Styles[4] = PS_SOLID;

	short	ret1, ret2;

	ret1 = AddNewGraph("graf 1", "legenda 1");
	ret2 = AddNewGraph("graf 2", "Legenda 2");

	for( i=0; i<50; i++ )
	{
		AddPoint( ret1, i/50.*7, sin(i/50.*7) );
		AddPoint( ret2, i/50.*7, cos(i/50.*7 + 0.5) ); //, sin(i/50.*7) * 2);
	}
/*	AddPoint(ret1, -30, 30);
	AddPoint(ret1, -10, -30);
	AddPoint(ret1, 10, 50);
	AddPoint(ret1, 50, -20);
	AddPoint(ret1, 70, -50);
	AddPoint(ret2, -20, 30);
	AddPoint(ret2, 10, 80);
	AddPoint(ret2, 50, 30);
	AddPoint(ret2, 70, 70);
	AddPoint(ret2, 100, -30);*/
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::~CMathGraphCtrl - Destructor

CMathGraphCtrl::~CMathGraphCtrl()
{
	for( int i=0; i<MAX_GRAPHS; i++ )
	{
		if( IsValidGraphID(i) )
		{
			if( m_apvecX[i] != NULL )
				delete m_apvecX[i];
			if( m_apvecY[i] != NULL )
				delete m_apvecY[i];
		}
	}
	if( m_pvecZ != NULL )
		delete m_pvecZ;
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::OnDraw - Drawing function

void CMathGraphCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	CSize size = pdc->GetWindowExt();

	if( m_bAnalyseDataValid == false )
	{
		AnalyseDataRange();
		m_bAnalyseDataValid = true;
	}

	switch(m_graphType)
	{
		case TRAJECTORY : DrawTrajectory(pdc, rcBounds);	break;
		case PHASE_PLOT	: DrawPhase(pdc, rcBounds);	break;
		case SURFACE		:	DrawSurface(pdc, rcBounds);	break;
	}

}

void CMathGraphCtrl::DrawCoordSystem( CDC *pDC, const CRect & rcBounds, double dMulX, double dMulY )
{
	// PROBLEM ZA RIJESITI - sto ako x ili y-os ispadaju van ekrana za iscrtavanje
	// iscrtavamo x-os
	pDC->MoveTo((int) (m_dXLow * dMulX), 0);
	pDC->LineTo((int) (m_dXUpp * dMulX), 0);

	// iscrtavamo y-os
	pDC->MoveTo(0, (int) (m_dYLowTot * dMulY));
	pDC->LineTo(0, (int) (m_dYUppTot * dMulY));
}

void CMathGraphCtrl::DrawTrajectory( CDC *pDC, const CRect &rcBounds )
{
	int				i, j, style;
	CPen			*penTmp;
	COLORREF	color;

	double		dExtraWidth = rcBounds.Width() * 0.08;
	double		dExtraHeight = rcBounds.Height() * 0.08;
	double		dMulX, dMulY;

	if( m_nCurveNum > 0 )
	{
		dMulX = (rcBounds.Width() - 2*dExtraWidth) / (m_dXUpp - m_dXLow);
		dMulY = (rcBounds.Height() - 2*dExtraHeight) / (m_dYUppTot - m_dYLowTot);
	}
	else
	{
		dMulX = rcBounds.Width() / 100;
		dMulY = rcBounds.Height() / 100;
	}

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(1,-1);
	pDC->SetWindowOrg((int) (m_dXLow*dMulX - dExtraWidth),(int) (m_dYUppTot*dMulY + dExtraHeight));

	DrawCoordSystem(pDC, rcBounds, dMulX, dMulY);

	color = RGB(0,0,0);
	style = PS_SOLID;

	for( i=0; i<MAX_GRAPHS; i++ )
		if( IsValidGraphID(i) )
		{
			if( m_bUseColors == TRUE )
				color = m_Colors[i];
			if( m_bUseLineStyles == TRUE )
				style = m_Styles[i];

			penTmp = new CPen(style, 1, color);
			pDC->SelectObject(penTmp);

			if( m_alPointsNum[i] > 0 )
			{
				pDC->MoveTo((int) ((*m_apvecX[i])[0]*dMulX), (int) ((*m_apvecY[i])[0]*dMulY) );

				for( j=1; j<m_alPointsNum[i]; j++ )
					pDC->LineTo((int) ((*m_apvecX[i])[j]*dMulX), (int) ((*m_apvecY[i])[j]*dMulY));
			}
			delete penTmp;
		}
}

void CMathGraphCtrl::DrawPhase( CDC *pDC, const CRect &rcBounds )
{
	// najprije treba ustanoviti u kojim granicama nam se krecu vrijednosti
	// m_xAxisVar - varijabla na x-osi
	// m_yAxisVar - varijabla na y-osi
	// m_zAxisVar - varijabla na z-osi
	int				i, j, style;
	CPen			*penTmp;
	COLORREF	color;

	if( m_eDim == PLOT_2D )
	{
		double		dExtraWidth = rcBounds.Width() * 0.08;
		double		dExtraHeight = rcBounds.Height() * 0.08;
		double		dMulX, dMulY, dXUpp, dXLow, dYUpp, dYLow;

		if( m_xAxisVar != m_yAxisVar && IsValidGraphID(m_xAxisVar) && IsValidGraphID(m_yAxisVar ) )
		{
			dXUpp = m_dYUpp[m_xAxisVar];
			dXLow = m_dYLow[m_xAxisVar];
			dYUpp = m_dYUpp[m_yAxisVar];
			dYLow = m_dYLow[m_yAxisVar];

			dMulX = (rcBounds.Width() - 2*dExtraWidth) / (dXUpp - dXLow);
			dMulY = (rcBounds.Height() - 2*dExtraHeight) / (dYUpp - dYLow);

			pDC->SetMapMode(MM_ANISOTROPIC);
			pDC->SetWindowExt(1,-1);
			pDC->SetWindowOrg((int) (dXLow*dMulX - dExtraWidth),(int) (dYUpp*dMulY + dExtraHeight));

			DrawCoordSystem(pDC, rcBounds, dMulX, dMulY);

			color = RGB(0,0,0);
			style = PS_SOLID;

			if( m_bUseColors == TRUE )
				color = m_Colors[i];
			if( m_bUseLineStyles == TRUE )
				style = m_Styles[i];

			penTmp = new CPen(style, 1, color);
			pDC->SelectObject(penTmp);

			if( m_alPointsNum[i] > 0 )
			{
				pDC->MoveTo((int) ((*m_apvecX[i])[0]*dMulX), (int) ((*m_apvecY[i])[0]*dMulY) );

				for( j=1; j<m_alPointsNum[i]; j++ )
					pDC->LineTo((int) ((*m_apvecX[i])[j]*dMulX), (int) ((*m_apvecY[i])[j]*dMulY));

				delete penTmp;
			}
		}
		else
		{
			dMulX = rcBounds.Width() / 100;
			dMulY = rcBounds.Height() / 100;
		}

	}
}

void CMathGraphCtrl::DrawSurface( CDC *pDC, const CRect &rcBounds )
{
}

/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::DoPropExchange - Persistence support

void CMathGraphCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::OnResetState - Reset control to default state

void CMathGraphCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
	AnalyseDataRange();
	InvalidateControl();
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl::AboutBox - Display an "About" box to the user

void CMathGraphCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MATHGRAPH);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl message handlers

short CMathGraphCtrl::GetCurveNum() 
{
	return m_nCurveNum;
}

short CMathGraphCtrl::AddNewGraph(LPCTSTR pchLegend, LPCTSTR pchYAxis) 
{
	int		nID;
	
	if( ( nID=GetFirstFreeGraph() ) >= 0 )
	{
		m_astrYAxis[nID] = pchYAxis;
		m_astrLegend[nID] = pchLegend;
		
		// pocetna duljina vektora ce biti 100, pa ce se poslije realocirati ako bude potrebno
		m_apvecX[nID] = new Vector(100);
		m_apvecY[nID] = new Vector(100);
		
		// ako je to prvi graf koji dodajemo u kontrolu, onda alocirati i prostor za Z koordinatu
		if( GetCurveNum() == 0 )
			m_pvecZ = new Vector(100);

		m_nCurveNum++;
		m_abFreeGraph[nID] = false;
		m_bAnalyseDataValid = false;

		return nID;
	}
	else
		return -1;
}

void CMathGraphCtrl::RemoveGraph(short nCurveNum) 
{
	if( IsValidGraphID( nCurveNum ) )
	{
		m_astrLegend[nCurveNum] = "";
		m_astrYAxis[nCurveNum] = "";

		delete m_apvecX[nCurveNum];
		delete m_apvecY[nCurveNum];
		m_apvecX[nCurveNum] = NULL;
		m_apvecY[nCurveNum] = NULL;

		m_abFreeGraph[nCurveNum] = true;
		m_bAnalyseDataValid = false;
		m_nCurveNum--;
	}
}

int CMathGraphCtrl::GetFirstFreeGraph()
{
	for( int i=0; i<MAX_GRAPHS; i++ )
		if( m_abFreeGraph[i] == true )
			return i;

	return -1;
}

bool CMathGraphCtrl::IsValidGraphID( int nCurveNum )
{
	if( nCurveNum >= 0 && nCurveNum < MAX_GRAPHS )
		if( m_abFreeGraph[nCurveNum] == false )
			return true;
	
	return false;
}

short CMathGraphCtrl::AddPoint(short nID, double dX, double dY) 
{
	// provjera da li je ID grafa ispravan
	if( IsValidGraphID(nID) )
	{
		// provjeriti da li ima mjesta za dodavanje nove tocke
		if( m_alPointsNum[nID] >= m_apvecX[nID]->GetDim() )
		{
			// ako nema, realocirati nizove
			int	nNewDim = m_apvecX[nID]->GetDim() * 2;
			
			m_apvecX[nID]->Realloc(nNewDim);
			m_apvecY[nID]->Realloc(nNewDim);
			m_pvecZ->Realloc(nNewDim);
		}
		// odredi na koje mjesto ubacujemo tocku, i povecaj ukupan broj tocaka
		int		num = m_alPointsNum[nID]++;

		(*m_apvecX[nID])[num] = dX;
		(*m_apvecY[nID])[num] = dY;
//		(*m_pvecZ)[num] = 0.0;

		m_bAnalyseDataValid = false;
		m_bStatUpdated = false;
	}

	return 0;
}

short CMathGraphCtrl::AddPoint3D(short nID, double dX, double dY, double dZ) 
{
	// provjera da li je ID grafa ispravan
	if( IsValidGraphID(nID) )
	{
		// provjeriti da li ima mjesta za dodavanje nove tocke
		if( m_alPointsNum[nID] >= m_apvecX[nID]->GetDim() )
		{
			// ako nema, realocirati nizove
			int	nNewDim = m_apvecX[nID]->GetDim() * 2;
			
			m_apvecX[nID]->Realloc(nNewDim);
			m_apvecY[nID]->Realloc(nNewDim);
			m_pvecZ->Realloc(nNewDim);
		}
		// odredi na koje mjesto ubacujemo tocku, i povecaj ukupan broj tocaka
		int		num = m_alPointsNum[nID]++;

		(*m_apvecX[nID])[num] = dX;
		(*m_apvecY[nID])[num] = dY;
		(*m_pvecZ)[num] = dZ;

		m_bAnalyseDataValid = false;
		m_bStatUpdated = false;
	}

	return 0;
}

void CMathGraphCtrl::SetLegend(short nID, LPCTSTR pchLegend) 
{
	if( IsValidGraphID(nID) )
		m_astrLegend[nID] = pchLegend;

	SetModifiedFlag();
}

void CMathGraphCtrl::AnalyseDataRange()
{
	int		i, j;
	double	xmin, xmax, ymin, ymax;

	m_dYLowTot = xmin = 1e30;
	m_dYUppTot = xmax = -1e30;

	for( j=0; j<MAX_GRAPHS; j++ )
	{
		if( IsValidGraphID(j) )
		{
			ymin = 1e30;
			ymax = -1e30;
			
			for( i=0;i<m_alPointsNum[j]; i++ )
			{
				if( (*m_apvecX[j])[i] > xmax )
					xmax = (*m_apvecX[j])[i];
				if( (*m_apvecX[j])[i] < xmin )
					xmin = (*m_apvecX[j])[i];

				if( (*m_apvecY[j])[i] > ymax )
					ymax = (*m_apvecY[j])[i];
				if( (*m_apvecY[j])[i] < ymin )
					ymin = (*m_apvecY[j])[i];
			}
			
			m_dYLow[j] = ymin;
			m_dYUpp[j] = ymax;
			
			if( m_dYUppTot < ymax )
				m_dYUppTot = ymax;
			if( m_dYLowTot > ymin )
				m_dYLowTot = ymin;
		}
	}

	m_dXLow = xmin;
	m_dXUpp = xmax;
}

void CMathGraphCtrl::SetDim(short nDim) 
{
	if( nDim == 3 )
		m_eDim = PLOT_3D;
	else
		m_eDim = PLOT_2D;
}

void CMathGraphCtrl::OnTitleChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CMathGraphCtrl::OnGraphTypeChanged() 
{
	// TODO: Add notification handler code
	InvalidateControl();
	SetModifiedFlag();
}

void CMathGraphCtrl::OnShowLegendChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CMathGraphCtrl::OnUseColorsChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CMathGraphCtrl::OnUseLineStylesChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}
