#if !defined(AFX_VCLIGHT_H__3EC7FA18_0195_44A5_807B_CCAF19FC4CFE__INCLUDED_)
#define AFX_VCLIGHT_H__3EC7FA18_0195_44A5_807B_CCAF19FC4CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcLightSources;

/////////////////////////////////////////////////////////////////////////////
// CVcLight wrapper class

class CVcLight : public COleDispatchDriver
{
public:
	CVcLight() {}		// Calls COleDispatchDriver default constructor
	CVcLight(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLight(const CVcLight& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	float GetAmbientIntensity();
	void SetAmbientIntensity(float newValue);
	float GetEdgeIntensity();
	void SetEdgeIntensity(float newValue);
	BOOL GetEdgeVisible();
	void SetEdgeVisible(BOOL bNewValue);
	CVcLightSources GetLightSources();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCLIGHT_H__3EC7FA18_0195_44A5_807B_CCAF19FC4CFE__INCLUDED_)
