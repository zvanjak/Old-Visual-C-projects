// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "graph.h"

/////////////////////////////////////////////////////////////////////////////
// CGraph

IMPLEMENT_DYNCREATE(CGraph, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CGraph properties

CString CGraph::GetTitle()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CGraph::SetTitle(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CGraph::GetXAxisTitle()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CGraph::SetXAxisTitle(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

BOOL CGraph::GetUseColor()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetUseColor(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL CGraph::GetUseLineStyles()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetUseLineStyles(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

BOOL CGraph::GetShowLegend()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetShowLegend(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

BOOL CGraph::GetShowCoordSystem()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetShowCoordSystem(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

BOOL CGraph::GetShowScale()
{
	BOOL result;
	GetProperty(0x7, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetShowScale(BOOL propVal)
{
	SetProperty(0x7, VT_BOOL, propVal);
}

short CGraph::GetScaleType()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetScaleType(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}

short CGraph::GetXAxisVar()
{
	short result;
	GetProperty(0x9, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetXAxisVar(short propVal)
{
	SetProperty(0x9, VT_I2, propVal);
}

short CGraph::GetYAxisVar()
{
	short result;
	GetProperty(0xa, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetYAxisVar(short propVal)
{
	SetProperty(0xa, VT_I2, propVal);
}

short CGraph::GetZAxisVar()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetZAxisVar(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}

short CGraph::GetScaleIntervalsNum()
{
	short result;
	GetProperty(0xc, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetScaleIntervalsNum(short propVal)
{
	SetProperty(0xc, VT_I2, propVal);
}

short CGraph::GetPlotType()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetPlotType(short propVal)
{
	SetProperty(0xd, VT_I2, propVal);
}

double CGraph::GetStartX()
{
	double result;
	GetProperty(0xe, VT_R8, (void*)&result);
	return result;
}

void CGraph::SetStartX(double propVal)
{
	SetProperty(0xe, VT_R8, propVal);
}

double CGraph::GetEndX()
{
	double result;
	GetProperty(0xf, VT_R8, (void*)&result);
	return result;
}

void CGraph::SetEndX(double propVal)
{
	SetProperty(0xf, VT_R8, propVal);
}

short CGraph::GetGraphNum()
{
	short result;
	GetProperty(0x14, VT_I2, (void*)&result);
	return result;
}

void CGraph::SetGraphNum(short propVal)
{
	SetProperty(0x14, VT_I2, propVal);
}

long CGraph::GetPointsNum()
{
	long result;
	GetProperty(0x15, VT_I4, (void*)&result);
	return result;
}

void CGraph::SetPointsNum(long propVal)
{
	SetProperty(0x15, VT_I4, propVal);
}

BOOL CGraph::GetSetLegendPosFlag()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}

void CGraph::SetSetLegendPosFlag(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}

double CGraph::GetDistance()
{
	double result;
	GetProperty(0x11, VT_R8, (void*)&result);
	return result;
}

void CGraph::SetDistance(double propVal)
{
	SetProperty(0x11, VT_R8, propVal);
}

double CGraph::GetAzimuth()
{
	double result;
	GetProperty(0x12, VT_R8, (void*)&result);
	return result;
}

void CGraph::SetAzimuth(double propVal)
{
	SetProperty(0x12, VT_R8, propVal);
}

double CGraph::GetVerticalAngle()
{
	double result;
	GetProperty(0x13, VT_R8, (void*)&result);
	return result;
}

void CGraph::SetVerticalAngle(double propVal)
{
	SetProperty(0x13, VT_R8, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CGraph operations

short CGraph::AddNewGraph(double* pdYVal, long lPointsNum, LPCTSTR pchLegend)
{
	short result;
	static BYTE parms[] =
		VTS_PR8 VTS_I4 VTS_BSTR;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		pdYVal, lPointsNum, pchLegend);
	return result;
}

short CGraph::AddNewGraphWithX(double* pdXVal, double* pdYVal, long lPointsNum, LPCTSTR pchLegend)
{
	short result;
	static BYTE parms[] =
		VTS_PR8 VTS_PR8 VTS_I4 VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		pdXVal, pdYVal, lPointsNum, pchLegend);
	return result;
}

void CGraph::RemoveGraph(short nID)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nID);
}

void CGraph::RemoveAllGraphs()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short CGraph::ShowGraph(short nID, BOOL bShow)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nID, bShow);
	return result;
}

short CGraph::Resize(short nXPercent, short nYPercent)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nXPercent, nYPercent);
	return result;
}

short CGraph::Move(short nXPercent, short nYPercent)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nXPercent, nYPercent);
	return result;
}

void CGraph::SetLegendPos(short nXPercent, short nYPercent)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nXPercent, nYPercent);
}

void CGraph::DrawItself(long* pDC, short x1, short y1, short x2, short y2)
{
	static BYTE parms[] =
		VTS_PI4 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDC, x1, y1, x2, y2);
}

BOOL CGraph::DrawToMetafile(LPCTSTR FileNmae)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FileNmae);
	return result;
}

void CGraph::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
