#if !defined(AFX_VCSERIESCOLLECTION_H__7AA95219_82CD_4BC8_B66A_1E2C255A7786__INCLUDED_)
#define AFX_VCSERIESCOLLECTION_H__7AA95219_82CD_4BC8_B66A_1E2C255A7786__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcSeries;

/////////////////////////////////////////////////////////////////////////////
// CVcSeriesCollection wrapper class

class CVcSeriesCollection : public COleDispatchDriver
{
public:
	CVcSeriesCollection() {}		// Calls COleDispatchDriver default constructor
	CVcSeriesCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcSeriesCollection(const CVcSeriesCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long Count();
	CVcSeries GetItem(short Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCSERIESCOLLECTION_H__7AA95219_82CD_4BC8_B66A_1E2C255A7786__INCLUDED_)