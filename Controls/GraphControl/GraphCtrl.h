#if !defined(AFX_GRAPHCTRL_H__106D39F6_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_)
#define AFX_GRAPHCTRL_H__106D39F6_C7AF_11D1_AFFE_0000C03E618C__INCLUDED_

//#include "d:\Users\Zvone\Projects\Projects Visual C++\Libraries\Mathlib\mathlib.h"
#include "matrix.h"

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

class Point3D {
public:
	double x, y, z;

	friend double	GetX( Point3D a );
	friend double	GetY( Point3D a );
	friend double	GetZ( Point3D a );

	Point3D( double inX, double inY, double inZ ) : x(inX), y(inY), z(inZ) {}
};

double	GetX( Point3D a )
{
	return a.x;
}
double	GetY( Point3D a )
{
	return a.y;
}
double	GetZ( Point3D a )
{
	return a.z;
}

#define	MAX_GRAPHS		5

#define	TRAJECTORY		1
#define	PHASE_2D			2
#define	PHASE_3D			3

#define SCALE_SAME		1
#define SCALE_DIFF		2

#define WRONG_POINTS_NUM		1
#define MAX_GRAPH_NUM				2
#define NO_X_AXIS_VALUES		3

#define	CENTER_WITHIN_WINDOW		1
#define	X_AXIS_WITHIN_WINDOW		2
#define	Y_AXIS_WITHIN_WINDOW		3
#define	NO_AXIS_WITHIN_WINDOW		-1

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GraphCtrl.h : Declaration of the CGraphCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGraphCtrl : See GraphCtrl.cpp for implementation.

class CGraphCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGraphCtrl)

// Constructor
public:
	CGraphCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGraphCtrl();

	DECLARE_OLECREATE_EX(CGraphCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGraphCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGraphCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGraphCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGraphCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGraphCtrl)
	CString m_strTitle;
	afx_msg void OnTitleChanged();
	CString m_strXAxisTitle;
	afx_msg void OnXAxisTitleChanged();
	BOOL m_bUseColor;
	afx_msg void OnUseColorChanged();
	BOOL m_bUseLineStyles;
	afx_msg void OnUseLineStylesChanged();
	BOOL m_bShowLegend;
	afx_msg void OnShowLegendChanged();
	BOOL m_bShowCoordSystem;
	afx_msg void OnShowCoordSystemChanged();
	BOOL m_bShowScale;
	afx_msg void OnShowScaleChanged();
	short m_nScaleType;
	afx_msg void OnScaleTypeChanged();
	short m_nXAxisVar;
	afx_msg void OnXAxisVarChanged();
	short m_nYAxisVar;
	afx_msg void OnYAxisVarChanged();
	short m_nZAxisVar;
	afx_msg void OnZAxisVarChanged();
	short m_nScaleIntervalsNum;
	afx_msg void OnScaleIntervalsNumChanged();
	short m_nPlotType;
	afx_msg void OnPlotTypeChanged();
	double m_dStartX;
	afx_msg void OnStartXChanged();
	double m_dEndX;
	afx_msg void OnEndXChanged();
	BOOL m_setLegendPosFlag;
	afx_msg void OnSetLegendPosFlagChanged();
	double m_dRho;
	afx_msg void OnDistanceChanged();
	double m_dAlpha;
	afx_msg void OnAzimuthChanged();
	double m_dTheta;
	afx_msg void OnVerticalAngleChanged();
	afx_msg short GetGraphNum();
	afx_msg long GetPointsNum();
	afx_msg short AddNewGraph(double FAR* pdYVal, long lPointsNum, LPCTSTR pchLegend);
	afx_msg short AddNewGraphWithX(double FAR* pdXVal, double FAR* pdYVal, long lPointsNum, LPCTSTR pchLegend);
	afx_msg void RemoveGraph(short nID);
	afx_msg void RemoveAllGraphs();
	afx_msg short ShowGraph(short nID, BOOL bShow);
	afx_msg short Resize(short nXPercent, short nYPercent);
	afx_msg short Move(short nXPercent, short nYPercent);
	afx_msg void SetLegendPos(short nXPercent, short nYPercent);
	afx_msg void DrawItself(long FAR* pDC, short x1, short y1, short x2, short y2);
	afx_msg BOOL DrawToMetafile(LPCTSTR FileNmae);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGraphCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGraphCtrl)
	dispidTitle = 1L,
	dispidXAxisTitle = 2L,
	dispidUseColor = 3L,
	dispidUseLineStyles = 4L,
	dispidShowLegend = 5L,
	dispidShowCoordSystem = 6L,
	dispidShowScale = 7L,
	dispidScaleType = 8L,
	dispidXAxisVar = 9L,
	dispidYAxisVar = 10L,
	dispidZAxisVar = 11L,
	dispidScaleIntervalsNum = 12L,
	dispidPlotType = 13L,
	dispidStartX = 14L,
	dispidEndX = 15L,
	dispidGraphNum = 20L,
	dispidPointsNum = 21L,
	dispidSetLegendPosFlag = 16L,
	dispidDistance = 17L,
	dispidAzimuth = 18L,
	dispidVerticalAngle = 19L,
	dispidAddNewGraph = 22L,
	dispidAddNewGraphWithX = 23L,
	dispidRemoveGraph = 24L,
	dispidRemoveAllGraphs = 25L,
	dispidShowGraph = 26L,
	dispidResize = 27L,
	dispidMove = 28L,
	dispidSetLegendPos = 29L,
	dispidDrawItself = 30L,
	dispidDrawToMetafile = 31L,
	//}}AFX_DISP_ID
	};

	private:
		enum	{ ON_DRAW = 0, DRAW_ITSELF = 1, DRAW_METAFILE } m_nCalledBy;

		short		m_nGraphNum;
		short		m_nSelected;
		long		m_lPointsNum;

		double	m_dExtraWidth, m_dExtraHeight;	// koliki postotak ekrana æe biti rub ( odnosno neæe se iscrtavati )

		CString	m_aszLegend[MAX_GRAPHS];
		CPoint	m_pntLegendPos;					// raspon 0-100 = unutar pravokutnika, postotak x i y koordinate na kojoj ce se iscrtavati legenda

		BOOL		m_bFreeGraph[MAX_GRAPHS];		// koji su ID zauzeti a koji su slobodni
		BOOL		m_bShowGraph[MAX_GRAPHS];		// koji se grafovi prikazuju, a koji ne

		COLORREF	m_Colors[MAX_GRAPHS];
		int				m_Styles[MAX_GRAPHS];

		BOOL		m_bViewContentChanged;		// kada se promjeni sadrzaj prozora (promjeni se x,y ili z var kod faznog dijagram, doda se novi graf)
		BOOL		m_bViewTypeChanged;				// kada se promjeni vrsta iscrtavanja u prozoru
		BOOL		m_bViewIntervalChanged;		// kada se promjeni interval iscrtavanja (StartX i EndX)
		BOOL		m_bNeedRecalc;						// kada treba ponovo izraèunati projekcije toèaka ( 3D fazni dijagram )

		double	*m_pdXVal;
		double	*m_apdYVal[MAX_GRAPHS];


		Matrix<float>		*m_matT;
		Point3D		*pointLookTo;
		
		CPoint		*m_pTransf;		// sadrži (transformirane)ekranske koordinate toèaka površine
		
		double		m_dScaleScreenCoord;
		double		m_dScreenMinX, m_dScreenMaxX;
		double		m_dScreenMinY, m_dScreenMaxY;

		struct PLOT_PARAMETERS
		{
			CPoint	pntOrg;							// koliko je posto ishodiste pomaknuto iz "pravog" ishodista
			
			double	dMulX, dMulY;				// x i y povecanje kod crtanja faznog dijagrama
			double	adMulY[MAX_GRAPHS];	// y povecanje za svaku trajektoriju posebno
		} m_PlotPar;

		struct ANAL_PARAMETERS
		{
			double	dXLow, dXUpp;					// min. i max. x za interval koji se prikazuje i za grafove koji se prikazuju

			double	dYLowTot, dYUppTot;		// min. i max. ukupni y kao i gore
			double	dYLow[MAX_GRAPHS], dYUpp[MAX_GRAPHS];		// min. i max. y za svaki graf posebno

			short		nMinY, nMaxY;					// kod kojeg grafa se javljaju min. i max. y
		} m_AnalPar;

		struct	COORD_SYS_PARMETERS			// da znamo granice kod iscrtavanja koordinatnog sistema
		{
			double	dXAxisLow, dXAxisUpp;
			double	dYAxisLow, dYAxisUpp;
			double	dZAxisLow, dZAxisUpp;
		} m_CoordPar;

		struct 
		{
			double	dYLow;
			double	dYUpp;
		} m_Anal[MAX_GRAPHS];

	public:
		void	AnalyseDataRange();			// analizira podatke za sve grafove unutar kontrole
		void	AnalyseGraphs(const CRect &rcBounds);			// analizira podatke za grafove koji se stvarno prikazuju

		BOOL	IsValidGraphID( int nID );
		int		GetFreeGraph( void );
		void	DrawCoordSystem( CDC *pDC, const CRect & rcBounds );
		void	DrawAxisScale( CDC *pDC, const CRect &rcBounds, int X0, int Y0, int retCenter );
		void	DrawLegend( CDC *pDC, const CRect &rcBounds );
		int		CenterWithinWindow( CPoint &pntOrigin );

		void	DrawTrajectory( CDC *pDC, const CRect &rcBounds );
		void	DrawPhase( CDC *pDC, const CRect &rcBounds );
		void	DrawPhase3D( CDC *pDC, const CRect &rcBounds );

		void	Set3DData();
		void	TransformToScreenCoord( void );
		void	DrawLine( CDC *pDC, VERTEX v1, VERTEX v2, Matrix<float> *T );
	
		CPointDouble	TransfToDoublePoint( double *point, Matrix<float> *T );
		CPoint				TransfToPoint( double *point, Matrix<float> *T );
		CPointDouble	TransfVertexToPoint( VERTEX point, Matrix<float> *T );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHCTRL_H__106D39F6_C7AF_11D1_AFFE_0000C03E618C__INCLUDED)
