// PrikazRasporedaIspitaCtl.cpp : Implementation of the CPrikazRasporedaIspitaCtrl ActiveX Control class.

#include "stdafx.h"
#include "PrikazRasporedaIspita.h"
#include "PrikazRasporedaIspitaCtl.h"
#include "PrikazRasporedaIspitaPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPrikazRasporedaIspitaCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPrikazRasporedaIspitaCtrl, COleControl)
	//{{AFX_MSG_MAP(CPrikazRasporedaIspitaCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPrikazRasporedaIspitaCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPrikazRasporedaIspitaCtrl)
	DISP_PROPERTY_EX(CPrikazRasporedaIspitaCtrl, "ItemNameLengthPercentage", GetItemNameLengthPercentage, SetItemNameLengthPercentage, VT_I2)
	DISP_PROPERTY_EX(CPrikazRasporedaIspitaCtrl, "AdditionalDataLengthPercentage", GetAdditionalDataLengthPercentage, SetAdditionalDataLengthPercentage, VT_I2)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "AddRow", AddRow, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "AddRowTerm", AddRowTerm, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "MoveUp", MoveUp, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "MoveDown", MoveDown, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "GetRowNum", GetRowNum, VT_I2, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "GetItemNum", GetItemNum, VT_I2, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "ClearRowData", ClearRowData, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "GetTermNum", GetTermNum, VT_I2, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "SetTermNum", SetTermNum, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "ClearAllData", ClearAllData, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrikazRasporedaIspitaCtrl, "DrawItself", DrawItself, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CPrikazRasporedaIspitaCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPrikazRasporedaIspitaCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPrikazRasporedaIspitaCtrl)
	EVENT_CUSTOM("RowSelected", FireRowSelected, VTS_I2)
	EVENT_CUSTOM("ColSelected", FireColSelected, VTS_I2)
	EVENT_CUSTOM("TermSelected", FireTermSelected, VTS_I2  VTS_I2)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPrikazRasporedaIspitaCtrl, 1)
	PROPPAGEID(CPrikazRasporedaIspitaPropPage::guid)
END_PROPPAGEIDS(CPrikazRasporedaIspitaCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPrikazRasporedaIspitaCtrl, "PRIKAZRASPOREDAISPITA.PrikazRasporedaIspitaCtrl.1",
	0x58e19248, 0xa94f, 0x4762, 0xb5, 0x43, 0xf, 0x1c, 0xd6, 0xc3, 0xb7, 0x1d)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPrikazRasporedaIspitaCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPrikazRasporedaIspita =
		{ 0x1030f5cf, 0xfa20, 0x413b, { 0x82, 0x4f, 0xc0, 0xd8, 0x9d, 0x37, 0x27, 0x2d } };
const IID BASED_CODE IID_DPrikazRasporedaIspitaEvents =
		{ 0x285f6332, 0x4359, 0x418f, { 0xbe, 0xf2, 0xb1, 0xf6, 0x9a, 0x5f, 0xb6, 0x78 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPrikazRasporedaIspitaOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPrikazRasporedaIspitaCtrl, IDS_PRIKAZRASPOREDAISPITA, _dwPrikazRasporedaIspitaOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::CPrikazRasporedaIspitaCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPrikazRasporedaIspitaCtrl

BOOL CPrikazRasporedaIspitaCtrl::CPrikazRasporedaIspitaCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PRIKAZRASPOREDAISPITA,
			IDB_PRIKAZRASPOREDAISPITA,
			afxRegApartmentThreading,
			_dwPrikazRasporedaIspitaOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::CPrikazRasporedaIspitaCtrl - Constructor

CPrikazRasporedaIspitaCtrl::CPrikazRasporedaIspitaCtrl()
{
	InitializeIIDs(&IID_DPrikazRasporedaIspita, &IID_DPrikazRasporedaIspitaEvents);

	// TODO: Initialize your control's instance data here.
	int		ControlWidth, ControlHeight, ItemNum;

	GetControlSize(&ControlWidth, &ControlHeight);

	ItemNameLengthPercentage = 25;
	AdditionalDataLengthPercentage = 5;
	ResizeControl();

	ItemNum = vecItemName.size();

	TermNum = 20;
	RowNum = ItemNum;				// broj redaka koji se ispisuje na ekranu
	StartWith = 0;

	MinRowHeight = 16;
	MaxRowHeight = 30;

	RowHeight = (float) ControlHeight / (ItemNum + 2);		// + 2 za najgornji i najdonji redak u kojem se nalaze dodatne informacije
	if( RowHeight < MinRowHeight ) {
		RowHeight = MinRowHeight;
	}
	else if( RowHeight > MaxRowHeight ) {
		RowHeight = MaxRowHeight;
//		RowNum = (float) ControlHeight / RowHeight - 2;
	}
	RowNum = (float) ControlHeight / RowHeight - 2;

	if( RowNum > ItemNum ) 
		RowNum = ItemNum;

	rectTableArea = CRect(ItemNameLength,RowHeight,ControlWidth-AdditionalDataLength,ControlHeight-RowHeight);

	ColWidth = (float) rectTableArea.Width() / TermNum;

/*
	char		str[50];
	for( int i=0; i<40; i++ ) {
		sprintf(str, "Redak%2d", i);
		AddRow(str);
	}	

	AddRowTerm(0,5);
	AddRowTerm(0,10);
	AddRowTerm(0,17);
*/
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::~CPrikazRasporedaIspitaCtrl - Destructor

CPrikazRasporedaIspitaCtrl::~CPrikazRasporedaIspitaCtrl()
{
	// TODO: Cleanup your control's instance data here.
	for( int i=0; i<matItemTerm[i].size(); i++ )
		matItemTerm[i].~vector();
	
	matItemTerm.~vector();
	vecItemName.~vector();
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::OnDraw - Drawing function

void CPrikazRasporedaIspitaCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	rcOldBounds = rcBounds;

	// da izbrišemo prethodni sadržaj
	pdc->FillSolidRect(rcBounds, RGB(255,255,255));

	ResizeControl();

	pdc->MoveTo(0,RowHeight);
	pdc->LineTo(rectTableArea.Width(), RowHeight);

	int		i, j;

	for( i=0; i<RowNum+2; i++ ) {
		pdc->MoveTo(0, RowHeight*i);
		pdc->LineTo(ItemNameLength+rectTableArea.Width(), RowHeight*i);
	}

	for( j=0; j<TermNum+1; j++ ) {
		pdc->MoveTo(ItemNameLength + j*ColWidth, 0);
		pdc->LineTo(ItemNameLength + j*ColWidth, RowHeight*(GetRowNum()+1));
	}

	CFont		tmpFont, *pPrevFont;
	tmpFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
										OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Times New Roman" );
	
	pPrevFont = pdc->SelectObject(&tmpFont);
	for( i=0; i<RowNum; i++ )
		pdc->TextOut(0, RowHeight*(i+1)+1, vecItemName[i+StartWith].c_str(), vecItemName[i+StartWith].length());
	pdc->SelectObject(pPrevFont);

	for( i=0; i<RowNum; i++ ) {
		for( j=0; j<matItemTerm[i + StartWith].size(); j++ ) {
			int		x, y, pos;

			pos = matItemTerm[i + StartWith][j];
			if( pos < GetTermNum() ) {
				x = rectTableArea.left + ColWidth * pos + ColWidth / 2;
				y = rectTableArea.top + RowHeight * i + RowHeight / 2;

				pdc->Ellipse(x,y,x+5, y+5);
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::DoPropExchange - Persistence support

void CPrikazRasporedaIspitaCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::OnResetState - Reset control to default state

void CPrikazRasporedaIspitaCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl::AboutBox - Display an "About" box to the user

void CPrikazRasporedaIspitaCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_PRIKAZRASPOREDAISPITA);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspitaCtrl message handlers

short CPrikazRasporedaIspitaCtrl::GetItemNameLengthPercentage() 
{
	return ItemNameLengthPercentage;
}

void CPrikazRasporedaIspitaCtrl::SetItemNameLengthPercentage(short nNewValue) 
{
	// naziv i dodatni podaci ne smiju zauzimati više od 60% prostora kontrole
	if( nNewValue > 0 && nNewValue < 100 && (nNewValue + AdditionalDataLengthPercentage) < 60) {
		ItemNameLengthPercentage = nNewValue;
		ResizeControl();

		SetModifiedFlag();
	}
}

short CPrikazRasporedaIspitaCtrl::GetAdditionalDataLengthPercentage() 
{
	return AdditionalDataLengthPercentage;
}

void CPrikazRasporedaIspitaCtrl::SetAdditionalDataLengthPercentage(short nNewValue) 
{
	// naziv i dodatni podaci ne smiju zauzimati više od 60% prostora kontrole
	if( nNewValue > 0 && nNewValue < 100 && (nNewValue + ItemNameLengthPercentage) < 60) {
		ItemNameLengthPercentage = nNewValue;
		ResizeControl();

		SetModifiedFlag();
	}
}

bool CPrikazRasporedaIspitaCtrl::ResizeControl()
{
	int		ControlWidth, ControlHeight;

	GetControlSize(&ControlWidth, &ControlHeight);

	ItemNameLength = ControlWidth * ItemNameLengthPercentage / 100;
	AdditionalDataLength = ControlWidth * AdditionalDataLengthPercentage / 100;

	int		ItemNum = vecItemName.size();

	RowHeight = (float) ControlHeight / (ItemNum + 2);		// + 2 za najgornji i najdonji redak u kojem se nalaze dodatne informacije
	if( RowHeight < MinRowHeight ) {
		RowHeight = MinRowHeight;
	}
	else if( RowHeight > MaxRowHeight ) {
		RowHeight = MaxRowHeight;
//		RowNum = (float) ControlHeight / RowHeight - 2;
	}
	RowNum = (float) ControlHeight / RowHeight - 2;
	
	if( RowNum > ItemNum )
		RowNum = ItemNum;

	rectTableArea = CRect(ItemNameLength,RowHeight,ControlWidth-AdditionalDataLength,ControlHeight-RowHeight);

	int r = ControlWidth-AdditionalDataLength;

	ColWidth = (float) rectTableArea.Width() / TermNum;
//	ColWidth = (ControlWidth - ItemNameLength - AdditionalDataLength) / TermNum;

	return true;
}

BOOL CPrikazRasporedaIspitaCtrl::AddRow(LPCTSTR ItemName) 
{
	int	sz = vecItemName.size();

//	ASSERT(sz==RowNum);					// nešto nije u redu

	vecItemName.resize(sz+1);
	vecItemName[sz] = string(ItemName);

	matItemTerm.resize(sz+1);

//	RowNum++;

	ResizeControl();
	InvalidateControl();

	return TRUE;
}

BOOL CPrikazRasporedaIspitaCtrl::AddRowTerm(short inRowNum, short inTerm) 
{
	int	sz = vecItemName.size();

//	ASSERT( sz==RowNum);					// nešto nije u redu

	if( inRowNum < 0 || inRowNum >= sz || inTerm < 0 )
		return false;
	else {
		int	RowSize = matItemTerm[inRowNum].size();

		matItemTerm[inRowNum].resize(RowSize+1);
		matItemTerm[inRowNum][RowSize] = inTerm;
	}

	ResizeControl();
//	InvalidateControl();

	return TRUE;
}

BOOL CPrikazRasporedaIspitaCtrl::MoveUp() 
{
	if( StartWith > 0 ) 
	{
		StartWith--;
		InvalidateControl();

		return TRUE;
	}
	else
		return FALSE;
}

BOOL CPrikazRasporedaIspitaCtrl::MoveDown() 
{
	if( StartWith + RowNum < vecItemName.size() )
	{
		StartWith++;
		InvalidateControl();

		return TRUE;
	}
	else
		return FALSE;
}

short CPrikazRasporedaIspitaCtrl::GetRowNum() 
{
	return RowNum;
}

short CPrikazRasporedaIspitaCtrl::GetItemNum() 
{
	return vecItemName.size();
}

BOOL CPrikazRasporedaIspitaCtrl::ClearRowData(short RowNum) 
{
	if( RowNum >= 0 && RowNum < GetRowNum() ) {
		matItemTerm[RowNum].resize(0);

		InvalidateControl();
		return TRUE;
	}
	else
		return FALSE;
}

void CPrikazRasporedaIspitaCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int		r, c;

	if( point.x < ItemNameLength ) {
		r = point.y / RowHeight - 1;
		
		if( r < GetRowNum() )
			FireRowSelected(r);
	}
	else {
		if( point.y < RowHeight) {
			c = (point.x - ItemNameLength) / ColWidth;
			
			if( c < TermNum )
				FireColSelected(c);
		}
		else {
			r = point.y / RowHeight - 1;
			c = (point.x - ItemNameLength) / ColWidth;

			FireTermSelected(r,c);
		}
	}
	
	COleControl::OnLButtonDown(nFlags, point);
}

short CPrikazRasporedaIspitaCtrl::GetTermNum() 
{
	return TermNum;
}

BOOL CPrikazRasporedaIspitaCtrl::SetTermNum(short inTermNum) 
{
	// TODO: Add your dispatch handler code here
	if( inTermNum > 0 ) {
		if( TermNum != inTermNum ) {
			TermNum = inTermNum;
			InvalidateControl();
		}
		return TRUE;
	}
	return FALSE;
}

void CPrikazRasporedaIspitaCtrl::ClearAllData() 
{
	for( RowNum=0; RowNum<matItemTerm.size(); RowNum++ ) {
		matItemTerm[RowNum].erase(matItemTerm[RowNum].begin(), matItemTerm[RowNum].end());
	}
	DrawItself();
}

void CPrikazRasporedaIspitaCtrl::DrawItself() 
{
	int		x, y;
	GetControlSize(&x, &y);
	CRect		rcBounds(0,0,x,y);

	CDC		*pdc = GetDC();

	rcOldBounds = rcBounds;

	// da izbrišemo prethodni sadržaj
	pdc->FillSolidRect(rcBounds, RGB(255,255,255));

	ResizeControl();

	pdc->MoveTo(0,RowHeight);
	pdc->LineTo(rectTableArea.Width(), RowHeight);

	int		i, j;

	for( i=0; i<RowNum+2; i++ ) {
		pdc->MoveTo(0, RowHeight*i);
		pdc->LineTo(ItemNameLength+rectTableArea.Width(), RowHeight*i);
	}

	for( j=0; j<TermNum+1; j++ ) {
		pdc->MoveTo(ItemNameLength + j*ColWidth, 0);
		pdc->LineTo(ItemNameLength + j*ColWidth, RowHeight*(GetRowNum()+1));
	}

	CFont		tmpFont, *pPrevFont;
	tmpFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
										OUT_TT_PRECIS, CLIP_LH_ANGLES, DEFAULT_QUALITY, DEFAULT_PITCH , "Times New Roman" );
	
	pPrevFont = pdc->SelectObject(&tmpFont);
	for( i=0; i<RowNum; i++ )
		pdc->TextOut(0, RowHeight*(i+1)+1, vecItemName[i+StartWith].c_str(), vecItemName[i+StartWith].length());
	pdc->SelectObject(pPrevFont);

	for( i=0; i<RowNum; i++ ) {
		for( j=0; j<matItemTerm[i + StartWith].size(); j++ ) {
			int		x, y, pos;

			pos = matItemTerm[i + StartWith][j];
			if( pos < GetTermNum() ) {
				x = rectTableArea.left + ColWidth * pos + ColWidth / 2;
				y = rectTableArea.top + RowHeight * i + RowHeight / 2;

				pdc->Ellipse(x,y,x+5, y+5);
			}
		}
	}
}
