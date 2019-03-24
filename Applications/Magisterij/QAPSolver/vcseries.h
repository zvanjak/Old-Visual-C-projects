#if !defined(AFX_VCSERIES_H__0E1C0498_089E_447F_ADDF_5AE74B78296D__INCLUDED_)
#define AFX_VCSERIES_H__0E1C0498_089E_447F_ADDF_5AE74B78296D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcPen;
class CVcSeriesPosition;
class CVcSeriesMarker;
class CVcStatLine;
class CVcDataPoints;

/////////////////////////////////////////////////////////////////////////////
// CVcSeries wrapper class

class CVcSeries : public COleDispatchDriver
{
public:
	CVcSeries() {}		// Calls COleDispatchDriver default constructor
	CVcSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcSeries(const CVcSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetSecondaryAxis();
	void SetSecondaryAxis(BOOL bNewValue);
	long GetSeriesType();
	void SetSeriesType(long nNewValue);
	CVcPen GetGuideLinePen();
	BOOL GetShowLine();
	void SetShowLine(BOOL bNewValue);
	CVcPen GetPen();
	CVcSeriesPosition GetPosition();
	CVcSeriesMarker GetSeriesMarker();
	CVcStatLine GetStatLine();
	CVcDataPoints GetDataPoints();
	CString GetLegendText();
	void SetLegendText(LPCTSTR lpszNewValue);
	void Select();
	BOOL GetShowGuideLine(long axisID);
	void SetShowGuideLine(long axisID, BOOL bNewValue);
	long GetTypeByChartType(long chartType);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCSERIES_H__0E1C0498_089E_447F_ADDF_5AE74B78296D__INCLUDED_)
