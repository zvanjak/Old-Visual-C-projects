// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CSimpleGraph wrapper class

class CSimpleGraph : public CWnd
{
protected:
	DECLARE_DYNCREATE(CSimpleGraph)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xfa54aee2, 0xb3c1, 0x4897, { 0xaf, 0xda, 0x19, 0xd2, 0xfd, 0xed, 0x9b, 0x3 } };
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
	BOOL GetUseColors();
	void SetUseColors(BOOL);
	BOOL GetUseLineStyles();
	void SetUseLineStyles(BOOL);
	BOOL GetShowLegend();
	void SetShowLegend(BOOL);
	BOOL GetShowCoordSystem();
	void SetShowCoordSystem(BOOL);
	double GetStartX();
	void SetStartX(double);
	double GetEndX();
	void SetEndX(double);
	BOOL GetAllowDifferentYScale();
	void SetAllowDifferentYScale(BOOL);
	BOOL GetShowCommandButtons();
	void SetShowCommandButtons(BOOL);

// Operations
public:
	short AddGraph(float* XValues, float* YValues, long PointsNum, LPCTSTR Legend);
	BOOL RemoveGraph(short GraphID);
	BOOL RemoveAllGraphs();
	BOOL ShowGraph(BOOL GraphID);
	BOOL DrawtToMetafile(LPCTSTR FileName, long ExtentX, long ExtentY);
	BOOL SetLegendPos(float XPos, float YPos);
	BOOL DoesGraphAlreadyExist(float* XValues, float* YValues, long PointsNum);
	void AboutBox();
};
