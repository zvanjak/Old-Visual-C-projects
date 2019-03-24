#if !defined(AFX_MSCHART_H__95C6F467_9A41_4B20_95DD_500E355F627A__INCLUDED_)
#define AFX_MSCHART_H__95C6F467_9A41_4B20_95DD_500E355F627A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcTitle;
class CVcFootnote;
class CVcBackdrop;
class CVcLegend;
class CVcDataGrid;
class CVcPlot;

/////////////////////////////////////////////////////////////////////////////
// CMSChart wrapper class

class CMSChart : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMSChart)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x3a2b370c, 0xba0a, 0x11d1, { 0xb1, 0x37, 0x0, 0x0, 0xf8, 0x75, 0x3f, 0x5d } };
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

// Operations
public:
	BOOL GetAutoIncrement();
	void SetAutoIncrement(BOOL bNewValue);
	BOOL GetRandomFill();
	void SetRandomFill(BOOL bNewValue);
	long GetChartType();
	void SetChartType(long nNewValue);
	short GetColumn();
	void SetColumn(short nNewValue);
	short GetColumnCount();
	void SetColumnCount(short nNewValue);
	CString GetColumnLabel();
	void SetColumnLabel(LPCTSTR lpszNewValue);
	short GetColumnLabelCount();
	void SetColumnLabelCount(short nNewValue);
	short GetColumnLabelIndex();
	void SetColumnLabelIndex(short nNewValue);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	CString GetFootnoteText();
	void SetFootnoteText(LPCTSTR lpszNewValue);
	BOOL GetRepaint();
	void SetRepaint(BOOL bNewValue);
	short GetRow();
	void SetRow(short nNewValue);
	short GetRowCount();
	void SetRowCount(short nNewValue);
	CString GetRowLabel();
	void SetRowLabel(LPCTSTR lpszNewValue);
	short GetRowLabelCount();
	void SetRowLabelCount(short nNewValue);
	short GetRowLabelIndex();
	void SetRowLabelIndex(short nNewValue);
	short GetSeriesColumn();
	void SetSeriesColumn(short nNewValue);
	long GetSeriesType();
	void SetSeriesType(long nNewValue);
	BOOL GetShowLegend();
	void SetShowLegend(BOOL bNewValue);
	long GetDrawMode();
	void SetDrawMode(long nNewValue);
	long GetBorderStyle();
	void SetBorderStyle(long nNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetHWnd();
	CVcTitle GetTitle();
	CVcFootnote GetFootnote();
	CString GetTitleText();
	void SetTitleText(LPCTSTR lpszNewValue);
	BOOL GetStacking();
	void SetStacking(BOOL bNewValue);
	long GetTextLengthType();
	void SetTextLengthType(long nNewValue);
	BOOL GetAllowSelections();
	void SetAllowSelections(BOOL bNewValue);
	BOOL GetAllowSeriesSelection();
	void SetAllowSeriesSelection(BOOL bNewValue);
	BOOL GetAllowDynamicRotation();
	void SetAllowDynamicRotation(BOOL bNewValue);
	short GetActiveSeriesCount();
	CVcBackdrop GetBackdrop();
	CVcLegend GetLegend();
	CVcDataGrid GetDataGrid();
	CVcPlot GetPlot();
	BOOL GetAllowDithering();
	void SetAllowDithering(BOOL bNewValue);
	BOOL GetDoSetCursor();
	void SetDoSetCursor(BOOL bNewValue);
	BOOL GetChart3d();
	VARIANT GetChartData();
	void SetChartData(const VARIANT& newValue);
	long GetMousePointer();
	void SetMousePointer(long nNewValue);
	void Refresh();
	void EditPaste();
	void EditCopy();
	void Layout();
	void ToDefaults();
	void SelectPart(short part, short index1, short index2, short index3, short index4);
	void GetSelectedPart(short* part, short* index1, short* index2, short* index3, short* index4);
	void TwipsToChartPart(long xVal, long yVal, short* part, short* index1, short* index2, short* index3, short* index4);
	long GetOLEDragMode();
	void SetOLEDragMode(long nNewValue);
	long GetOLEDropMode();
	void SetOLEDropMode(long nNewValue);
	void OLEDrag();
	LPUNKNOWN GetDataSource();
	void SetRefDataSource(LPUNKNOWN newValue);
	CString GetDataMember();
	void SetDataMember(LPCTSTR lpszNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSCHART_H__95C6F467_9A41_4B20_95DD_500E355F627A__INCLUDED_)
