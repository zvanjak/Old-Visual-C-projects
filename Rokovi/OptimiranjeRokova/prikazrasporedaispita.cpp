// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "prikazrasporedaispita.h"

/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspita

IMPLEMENT_DYNCREATE(CPrikazRasporedaIspita, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspita properties

short CPrikazRasporedaIspita::GetItemNameLengthPercentage()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void CPrikazRasporedaIspita::SetItemNameLengthPercentage(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

short CPrikazRasporedaIspita::GetAdditionalDataLengthPercentage()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}

void CPrikazRasporedaIspita::SetAdditionalDataLengthPercentage(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CPrikazRasporedaIspita operations

BOOL CPrikazRasporedaIspita::AddRow(LPCTSTR ItemName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ItemName);
	return result;
}

BOOL CPrikazRasporedaIspita::AddRowTerm(short RowNum, short Term)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		RowNum, Term);
	return result;
}

BOOL CPrikazRasporedaIspita::MoveUp()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CPrikazRasporedaIspita::MoveDown()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short CPrikazRasporedaIspita::GetRowNum()
{
	short result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

short CPrikazRasporedaIspita::GetItemNum()
{
	short result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

void CPrikazRasporedaIspita::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
