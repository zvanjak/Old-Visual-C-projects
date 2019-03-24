#if !defined(AFX_PRIKAZRASPOREDAISPITACTL_H__776B8165_96D6_4826_83CD_844C44A3E43C__INCLUDED_)
#define AFX_PRIKAZRASPOREDAISPITACTL_H__776B8165_96D6_4826_83CD_844C44A3E43C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PrikazRasporedaIspitaCtl.h : Declaration of the CPrikazRasporedaIspitaCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl : See PrikazRasporedaIspitaCtl.cpp for implementation.

class CPrikazRasporedaIspitaCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPrikazRasporedaIspitaCtrl)

// Constructor
public:
	CPrikazRasporedaIspitaCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrikazRasporedaIspitaCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPrikazRasporedaIspitaCtrl();

	DECLARE_OLECREATE_EX(CPrikazRasporedaIspitaCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPrikazRasporedaIspitaCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPrikazRasporedaIspitaCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPrikazRasporedaIspitaCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPrikazRasporedaIspitaCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPrikazRasporedaIspitaCtrl)
	afx_msg short GetItemNameLengthPercentage();
	afx_msg void SetItemNameLengthPercentage(short nNewValue);
	afx_msg short GetAdditionalDataLengthPercentage();
	afx_msg void SetAdditionalDataLengthPercentage(short nNewValue);
	afx_msg BOOL AddRow(LPCTSTR ItemName);
	afx_msg BOOL AddRowTerm(short RowNum, short Term);
	afx_msg BOOL MoveUp();
	afx_msg BOOL MoveDown();
	afx_msg short GetRowNum();
	afx_msg short GetItemNum();
	afx_msg BOOL ClearRowData(short RowNum);
	afx_msg short GetTermNum();
	afx_msg BOOL SetTermNum(short TermNum);
	afx_msg void ClearAllData();
	afx_msg void DrawItself();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CPrikazRasporedaIspitaCtrl)
	void FireRowSelected(short RowNum)
		{FireEvent(eventidRowSelected,EVENT_PARAM(VTS_I2), RowNum);}
	void FireColSelected(short ColNum)
		{FireEvent(eventidColSelected,EVENT_PARAM(VTS_I2), ColNum);}
	void FireTermSelected(short RowNum, short ColNum)
		{FireEvent(eventidTermSelected,EVENT_PARAM(VTS_I2  VTS_I2), RowNum, ColNum);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	bool ResizeControl();
	enum {
	//{{AFX_DISP_ID(CPrikazRasporedaIspitaCtrl)
	dispidItemNameLengthPercentage = 1L,
	dispidAdditionalDataLengthPercentage = 2L,
	dispidAddRow = 3L,
	dispidAddRowTerm = 4L,
	dispidMoveUp = 5L,
	dispidMoveDown = 6L,
	dispidGetRowNum = 7L,
	dispidGetItemNum = 8L,
	dispidClearRowData = 9L,
	dispidGetTermNum = 10L,
	dispidSetTermNum = 11L,
	dispidClearAllData = 12L,
	dispidDrawItself = 13L,
	eventidRowSelected = 1L,
	eventidColSelected = 2L,
	eventidTermSelected = 3L,
	//}}AFX_DISP_ID
	};
private:
	int			StartWith;
	int			AdditionalDataLengthPercentage;
	int			ItemNameLengthPercentage;
	
	int			MaxRowHeight;
	int			MinRowHeight;
	
	float		RowHeight;
	float		ColWidth;
	
	int			AdditionalDataLength;
	int			ItemNameLength;

	int			RowNum;						// broj redaka koji se prikazuje na ekranu
	int			TermNum;
	CRect		rectTableArea;
	CRect		rcOldBounds;

	vector<string>					vecItemName;
	vector< vector<int> >		matItemTerm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIKAZRASPOREDAISPITACTL_H__776B8165_96D6_4826_83CD_844C44A3E43C__INCLUDED)
