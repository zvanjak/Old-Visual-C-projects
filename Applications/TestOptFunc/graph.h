#if !defined(AFX_GRAPH_H__2779BE3F_D18E_469B_AEC2_F9CDE15171F6__INCLUDED_)
#define AFX_GRAPH_H__2779BE3F_D18E_469B_AEC2_F9CDE15171F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CGraph wrapper class

class CGraph : public CWnd
{
protected:
	DECLARE_DYNCREATE(CGraph)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x106d39e8, 0xc7af, 0x11d1, { 0xaf, 0xfe, 0x0, 0x0, 0xc0, 0x3e, 0x61, 0x8c } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetTitle();
	void SetTitle(LPCTSTR);
	CString GetXAxisTitle();
	void SetXAxisTitle(LPCTSTR);
	BOOL GetUseColor();
	void SetUseColor(BOOL);
	BOOL GetUseLineStyles();
	void SetUseLineStyles(BOOL);
	BOOL GetShowLegend();
	void SetShowLegend(BOOL);
	BOOL GetShowCoordSystem();
	void SetShowCoordSystem(BOOL);
	BOOL GetShowScale();
	void SetShowScale(BOOL);
	short GetScaleType();
	void SetScaleType(short);
	short GetXAxisVar();
	void SetXAxisVar(short);
	short GetYAxisVar();
	void SetYAxisVar(short);
	short GetZAxisVar();
	void SetZAxisVar(short);
	short GetScaleIntervalsNum();
	void SetScaleIntervalsNum(short);
	short GetPlotType();
	void SetPlotType(short);
	double GetStartX();
	void SetStartX(double);
	double GetEndX();
	void SetEndX(double);
	short GetGraphNum();
	void SetGraphNum(short);
	long GetPointsNum();
	void SetPointsNum(long);
	BOOL GetSetLegendPosFlag();
	void SetSetLegendPosFlag(BOOL);
	double GetDistance();
	void SetDistance(double);
	double GetAzimuth();
	void SetAzimuth(double);
	double GetVerticalAngle();
	void SetVerticalAngle(double);

// Operations
public:
	short AddNewGraph(double* pdYVal, long lPointsNum, LPCTSTR pchLegend);
	short AddNewGraphWithX(double* pdXVal, double* pdYVal, long lPointsNum, LPCTSTR pchLegend);
	void RemoveGraph(short nID);
	void RemoveAllGraphs();
	short ShowGraph(short nID, BOOL bShow);
	short Resize(short nXPercent, short nYPercent);
	short Move(short nXPercent, short nYPercent);
	void SetLegendPos(short nXPercent, short nYPercent);
	void DrawItself(long* pDC, short x1, short y1, short x2, short y2);
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__2779BE3F_D18E_469B_AEC2_F9CDE15171F6__INCLUDED_)
