#if !defined(AFX_SIMPLEGRAPHCTL_H__41D672CE_8C93_4A68_A851_5B46C16D1457__INCLUDED_)
#define AFX_SIMPLEGRAPHCTL_H__41D672CE_8C93_4A68_A851_5B46C16D1457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define	MAX_GRAPHS		10

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

template<class _Type> class CGraphData {
public:
	CGraphData() {
		PointsNum = 0;
		XVal = YVal = NULL;
	}

	CGraphData(long inPointsNum, const _Type *inCopyPtrX, const _Type *inCopyPtrY ) {
		PointsNum = inPointsNum;
		XVal = new _Type[PointsNum];
		YVal = new _Type[PointsNum];
		memcpy(XVal, inCopyPtrX, sizeof(_Type)*PointsNum);
		memcpy(YVal, inCopyPtrY, sizeof(_Type)*PointsNum);
	}

	~CGraphData() {
		if( XVal != NULL ) {
			delete []XVal;
			XVal = NULL;
		}
		
		if( YVal != NULL ) {
			delete []YVal;
			YVal = NULL;
		}
	}

	bool	GetX( long i, _Type *outX ) { 
		if(i>=0 && i<PointsNum) 
			*outX = XVal[i]; 
		else 
			return false; 
		return true;
	}
	bool	GetY( long i, _Type *outY ) { 
		if(i>=0 && i<PointsNum) 
			*outY = YVal[i]; 
		else 
			return false; 
		return true;
	}
	bool	GetY( _Type  x ) {}

	long	GetPointsNum() { return PointsNum; }

	bool	SetGraphData(long inPointsNum, const _Type *inCopyPtrX, const _Type *inCopyPtrY ) {
		if( XVal != NULL )
			delete []XVal;
		
		if( YVal != NULL )
			delete []YVal;

		PointsNum = inPointsNum;
		XVal = new _Type[PointsNum];
		YVal = new _Type[PointsNum];
		memcpy(XVal, inCopyPtrX, sizeof(_Type)*PointsNum);
		memcpy(YVal, inCopyPtrY, sizeof(_Type)*PointsNum);

		return true;
	}

	bool AnalyseGraph( _Type *outMinX, _Type *outMaxX, _Type *outMinY, _Type *outMaxY ) {
		_Type		Min, Max;
		
		if( XVal==NULL || YVal==NULL )
			return false;

		*outMinX = *outMaxX = XVal[0];
		for( i=0; i<GetPointsNum(); i++ ) {
			if( XVal[i] > *outMaxX )
				*outMaxX = XVal[i];
			if( XVal[i] < *outMinX )
				*outMinX = XVal[i];
		}
		*outMinY = *outMaxY = YVal[0];
		for( i=0; i<GetPointsNum(); i++ ) {
			if( YVal[i] > *outMaxY )
				*outMaxY = YVal[i];
			if( YVal[i] < *outMinY )
				*outMinY = YVal[i];
		}
		return true;
	}

private:
	long		PointsNum;
	_Type		*XVal;
	_Type		*YVal;
};

// SimpleGraphCtl.h : Declaration of the CSimpleGraphCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CSimpleGraphCtrl : See SimpleGraphCtl.cpp for implementation.

class CSimpleGraphCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSimpleGraphCtrl)

// Constructor
public:
	CSimpleGraphCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleGraphCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSimpleGraphCtrl();

	DECLARE_OLECREATE_EX(CSimpleGraphCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSimpleGraphCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSimpleGraphCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSimpleGraphCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CSimpleGraphCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSimpleGraphCtrl)
	CString m_strTitle;
	afx_msg void OnTitleChanged();
	BOOL m_bUseColors;
	afx_msg void OnUseColorsChanged();
	BOOL m_bUseLineStyles;
	afx_msg void OnUseLineStylesChanged();
	BOOL m_bShowLegend;
	afx_msg void OnShowLegendChanged();
	BOOL m_bShowCoordSystem;
	afx_msg void OnShowCoordSystemChanged();
	double m_dStartX;
	afx_msg void OnStartXChanged();
	double m_dEndX;
	afx_msg void OnEndXChanged();
	BOOL m_bAllowDifferentYScale;
	afx_msg void OnAllowDifferentYScaleChanged();
	BOOL m_bShowCommandButtons;
	afx_msg void OnShowCommandButtonsChanged();
	afx_msg short AddGraph(float FAR* XValues, float FAR* YValues, long PointsNum, LPCTSTR Legend);
	afx_msg BOOL RemoveGraph(short GraphID);
	afx_msg BOOL RemoveAllGraphs();
	afx_msg BOOL ShowGraph(BOOL GraphID);
	afx_msg BOOL DrawToMetafile(LPCTSTR FileName, long ExtentX, long ExtentY);
	afx_msg BOOL SetLegendPos(float XPos, float YPos);
	afx_msg BOOL DoesGraphAlreadyExist(float FAR* XValues, float FAR* YValues, long PointsNum);
	afx_msg void ChangeGraphData(short GraphID, float FAR* XValues, float FAR* YValues, long PointsNum, LPCTSTR Legedn);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CSimpleGraphCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CSimpleGraphCtrl)
	dispidTitle = 1L,
	dispidUseColors = 2L,
	dispidUseLineStyles = 3L,
	dispidShowLegend = 4L,
	dispidShowCoordSystem = 5L,
	dispidStartX = 6L,
	dispidEndX = 7L,
	dispidAllowDifferentYScale = 8L,
	dispidShowCommandButtons = 9L,
	dispidAddGraph = 10L,
	dispidRemoveGraph = 11L,
	dispidRemoveAllGraphs = 12L,
	dispidShowGraph = 13L,
	dispidDrawtToMetafile = 14L,
	dispidSetLegendPos = 15L,
	dispidDoesGraphAlreadyExist = 16L,
	dispidChangeGraphData = 17L,
	//}}AFX_DISP_ID
	};

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
	BOOL		m_bViewIntervalChanged;		// kada se promjeni interval iscrtavanja (StartX i EndX)

	CGraphData<float>	Graph[MAX_GRAPHS];

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
	} m_CoordPar;

	struct 
	{
		double	dYLow;
		double	dYUpp;
	} m_Anal[MAX_GRAPHS];

	CButton		*pBox;

public:
	void	AnalyseDataRange();			// analizira podatke za sve grafove unutar kontrole
	void	AnalyseGraphs(const CRect &rcBounds);			// analizira podatke za grafove koji se stvarno prikazuju

	BOOL	IsValidGraphID( int nID );
	BOOL	GetFreeGraph( int *outInd );
	void	DrawCoordSystem( CDC *pDC, const CRect & rcBounds );
	void	DrawAxisScale( CDC *pDC, const CRect &rcBounds, int X0, int Y0, int retCenter );
	void	DrawLegend( CDC *pDC, const CRect &rcBounds );
	int		CenterWithinWindow( CPoint &pntOrigin );

	void	DrawTrajectory( CDC *pDC, const CRect &rcBounds );

	bool	GetWindowsCoord( float x, float y, CPoint *outPnt );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEGRAPHCTL_H__41D672CE_8C93_4A68_A851_5B46C16D1457__INCLUDED)
