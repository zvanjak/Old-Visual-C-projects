#if !defined(AFX_GRAVITYSIMCTL_H__0566A586_C260_11D2_9649_00C0DFE5278A__INCLUDED_)
#define AFX_GRAVITYSIMCTL_H__0566A586_C260_11D2_9649_00C0DFE5278A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GravitySimCtl.h : Declaration of the CGravitySimCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGravitySimCtrl : See GravitySimCtl.cpp for implementation.

class CGravitySimCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGravitySimCtrl)

// Constructor
public:
	CGravitySimCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravitySimCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGravitySimCtrl();

	BEGIN_OLEFACTORY(CGravitySimCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CGravitySimCtrl)

	DECLARE_OLETYPELIB(CGravitySimCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGravitySimCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGravitySimCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGravitySimCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGravitySimCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGravitySimCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGravitySimCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
private:
	int		m_nBodyNum;
	map<string, CBody>	m_arrBody;		// niz koji sadrži podatke o tijelima u simulaciji
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVITYSIMCTL_H__0566A586_C260_11D2_9649_00C0DFE5278A__INCLUDED)
