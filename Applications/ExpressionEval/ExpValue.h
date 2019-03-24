// ExpValue.h: interface for the CExpValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPVALUE_H__AC8E70D5_333D_11D2_89A8_00002145DF63__INCLUDED_)
#define AFX_EXPVALUE_H__AC8E70D5_333D_11D2_89A8_00002145DF63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Value.h"

class CExpValue : public CValue  
{
public:
	virtual void UpdateValue(void);
	virtual double GetValue(void);
	CExpValue();
	virtual ~CExpValue();

};

#endif // !defined(AFX_EXPVALUE_H__AC8E70D5_333D_11D2_89A8_00002145DF63__INCLUDED_)
