#if !defined(AFX_SURFACEPLOTCTL_H__7E0D9EEA_075A_11D2_914A_00C0DFE52874__INCLUDED_)
#define AFX_SURFACEPLOTCTL_H__7E0D9EEA_075A_11D2_914A_00C0DFE52874__INCLUDED_

//#include "d:\Users\Zvone\Projects\Projects Visual C++\Mathlib\mathlib.h"
#include "D:\Users\Zvone\Projects\Projects Visual C++\Libraries\MathLib\mathlib.h"

struct VERTEX
{
	double	x;
	double	y;
	double	z;
	double	h;
};

struct CPointDouble
{
	double x, y;
};

struct DATA_ANALYSE_PARAMETERS
{
	double		m_dXMin, m_dXMax;
	double		m_dYMin, m_dYMax;
	double		m_dZMin, m_dZMax;
};

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// SurfacePlotCtl.h : Declaration of the CSurfacePlotCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CSurfacePlotCtrl : See SurfacePlotCtl.cpp for implementation.

class CSurfacePlotCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSurfacePlotCtrl)

// Constructor
public:
	CSurfacePlotCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurfacePlotCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSurfacePlotCtrl();

	DECLARE_OLECREATE_EX(CSurfacePlotCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSurfacePlotCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSurfacePlotCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSurfacePlotCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CSurfacePlotCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSurfacePlotCtrl)
	double m_dRho;
	afx_msg void OnDistanceChanged();
	double m_dTheta;
	afx_msg void OnVerticalAngleChanged();
	double m_dAlpha;
	afx_msg void OnAzimuthChanged();
	BOOL m_bHideLines;
	afx_msg void OnHideLinesChanged();
	float m_fStretch;
	afx_msg void OnStretchChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CSurfacePlotCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CSurfacePlotCtrl)
	dispidDistance = 1L,
	dispidVerticalAngle = 2L,
	dispidAzimuth = 3L,
	dispidHideLines = 4L,
	dispidStretch = 5L,
	//}}AFX_DISP_ID
	};
private:
	Matrix		*m_matT;
	Point3D		*pointLookTo;

	long			m_lPointsNumCoord1, m_lPointsNumCoord2;

	Matrix		*m_matZBuff;
	CPoint		**m_pTransf;		// sadrži (transformirane)ekranske koordinate toèaka površine
	
	// u ovim nizovima æemo sortirati poligone po udaljenosti od oka
	//  (PolyOrderX[i], PolyOrderY[i]) identificira poligon koji je i-ti po redu po udaljenosti
	long			*m_plPolyOrderX, *m_plPolyOrderY;

	enum			{ CARTESIAN_COORD,	CYLINDRICAL_COORD } m_enCoordSystemType;
	
	struct		DATA_ANALYSE_PARAMETERS		m_DataAnal;

	BOOL			m_bNeedCoordRecalc;
	BOOL			m_bPlotTypeChanged;

	double		m_dScaleScreenCoord;

	double		m_dScreenMinX, m_dScreenMaxX;
	double		m_dScreenMinY, m_dScreenMaxY;
	double		m_dMulX, m_dMulY;

	// toèke na y i y-osima za kartezijev koordinatni sistem
	double		*m_pdXVal;
	double		*m_pdYVal;
	// toèke sa (r,theta) koordinatom za cilindrièni koordinatni sistem
	double		*m_pdRVal;
	double		*m_pdThetaVal;

	Matrix		*m_matZVal;

	void	DrawSurface(CDC * pDC, CRect rcBounds);
	void	PlotAxis();
	void	Set3DData();
	void	PlotBox( CDC *pDC );
	void	DrawLine( CDC *pDC, VERTEX v1, VERTEX v2, Matrix *T );

	void	TransformToScreenCoord( void );
	void	AnalyseData( void );

	CPointDouble	TransfToDoublePoint( double *point, Matrix *T );
	CPoint				TransfToPoint( double *point, Matrix *T );
	CPointDouble	TransfVertexToPoint( VERTEX point, Matrix *T );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACEPLOTCTL_H__7E0D9EEA_075A_11D2_914A_00C0DFE52874__INCLUDED)
