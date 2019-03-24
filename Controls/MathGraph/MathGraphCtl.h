#if !defined(AFX_MATHGRAPHCTL_H__81936D37_BE53_11D1_AFF7_0000C03E618C__INCLUDED_)
#define AFX_MATHGRAPHCTL_H__81936D37_BE53_11D1_AFF7_0000C03E618C__INCLUDED_

#include "d:\Users\Zvone\Projects\Projects Visual C++\Libraries\Mathlib\mathlib.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MathGraphCtl.h : Declaration of the CMathGraphCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMathGraphCtrl : See MathGraphCtl.cpp for implementation.

#define MAX_GRAPHS				5
#define	NONE_SELECTED			-1

#define	TRAJECTORY		0
#define PHASE_PLOT		1
#define SURFACE				2
#define	FITT_LINEAR		3
#define FITT_POLYNOM	4

struct STATISTIC
{
	double	dMean, dVariance;
	double	dStdDev, dAvergDev;
	double	dSkew, dKurtosis;
};

class CMathGraphCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMathGraphCtrl)

// Constructor
public:
	CMathGraphCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathGraphCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMathGraphCtrl();

	BEGIN_OLEFACTORY(CMathGraphCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CMathGraphCtrl)

	DECLARE_OLETYPELIB(CMathGraphCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMathGraphCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMathGraphCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMathGraphCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMathGraphCtrl)
	short m_xAxisVar;
	short m_yAxisVar;
	short m_zAxisVar;
	CString m_strTitle;
	afx_msg void OnTitleChanged();
	short m_graphType;
	afx_msg void OnGraphTypeChanged();
	BOOL m_bShowLegend;
	afx_msg void OnShowLegendChanged();
	BOOL m_bUseColors;
	afx_msg void OnUseColorsChanged();
	BOOL m_bUseLineStyles;
	afx_msg void OnUseLineStylesChanged();
	afx_msg short GetCurveNum();
	afx_msg short AddNewGraph(LPCTSTR pchLegend, LPCTSTR pchYAxis);
	afx_msg void RemoveGraph(short nCurveNum);
	afx_msg short AddPoint(short nID, double dX, double dY);
	afx_msg short AddPoint3D(short nID, double dX, double dY, double dZ);
	afx_msg void SetLegend(short nID, LPCTSTR pchLegend);
	afx_msg void SetDim(short nDim);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMathGraphCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMathGraphCtrl)
	dispidCurveNum = 9L,
	dispidTitle = 4L,
	dispidGraphType = 5L,
	dispidShowLegend = 6L,
	dispidUseColors = 7L,
	dispidUseLineStyles = 8L,
	dispidXAxisVar = 1L,
	dispidYAxisVar = 2L,
	dispidZAxisVar = 3L,
	dispidAddNewGraph = 10L,
	dispidRemoveGraph = 11L,
	dispidAddPoint = 12L,
	dispidAddPoint3D = 13L,
	dispidSetLegend = 14L,
	//}}AFX_DISP_ID
	};
private:
	void	AnalyseDataRange();
	void	DrawCoordSystem( CDC *pDC, const CRect & rcBounds, double dMulX, double dMulY );
	void	DrawTrajectory( CDC *pDC, const CRect &rcBounds );
	void	DrawPhase( CDC *pDC, const CRect &rcBounds );
	void	DrawSurface( CDC *pDC, const CRect &rcBounds );

	int		GetFirstFreeGraph();
	bool	IsValidGraphID( int nCurveNum );
	
	int		m_nCurveNum;
	int		m_nSelectedGraph;

	double		m_dXLow, m_dXUpp;
	double		m_dYLowTot, m_dYUppTot;
	double		m_dYLow[MAX_GRAPHS], m_dYUpp[MAX_GRAPHS];
	bool			m_bAnalyseDataValid;

	CString		m_strXAxis;
	CString		m_astrYAxis[MAX_GRAPHS];
	CString		m_strZAxis;

	CString		m_astrLegend[MAX_GRAPHS];
	
	Vector		*m_apvecX[MAX_GRAPHS];
	Vector		*m_apvecY[MAX_GRAPHS];
	Vector		*m_pvecZ;
	
	long		m_alPointsNum[MAX_GRAPHS];
	bool		m_abFreeGraph[MAX_GRAPHS];
	
	struct	STATISTIC		m_Stat[MAX_GRAPHS];
	bool		m_bStatUpdated;

//	enum	{ TRAJECTORY=1, PHASE_PLOT=2, SURFACE=3, FITT_LINEAR=4, FITT_POLYNOM=5 } m_eType;
	enum	{ PLOT_2D=1, PLOT_3D=2 } m_eDim;

	COLORREF	m_Colors[MAX_GRAPHS];
	int				m_Styles[MAX_GRAPHS];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHGRAPHCTL_H__81936D37_BE53_11D1_AFF7_0000C03E618C__INCLUDED)
