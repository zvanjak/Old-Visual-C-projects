// Function.h : main header file for the FUNCTION application
//



#if !defined(AFX_FUNCTION_H__893B59C6_B160_11D1_8170_00002145DF91__INCLUDED_)
#define AFX_FUNCTION_H__893B59C6_B160_11D1_8170_00002145DF91__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif



/////////////////////////////////////////////////////////////////////////////
// Definirea tipului arbore




/////////////////////////////////////////////////////////////////////////////
// Functie care elibereaza memoria ocupata de arbore


/////////////////////////////////////////////////////////////////////////////
// Definire Tipuri de date 


#include "afxtempl.h"
#include "value.h"


// Tree evaluation variables

#define DIVISION_BY_0 1
#define ILEGAL_OPERATION 2
#define UNDEFINED_VARIABLE 3
#define INVALID_DOMAIN 4

typedef CTypedPtrMap<CMapStringToOb,CString,CValue *> CMapVariabile;


/////////////////////////////////////////////////////////////////////////////


class CExpression: public CObject  
{

public:
	DECLARE_SERIAL(CExpression);
	
	
	CExpression &operator=(CExpression& expr);
	void AtachVariables(CMapVariabile *vars);
	CExpression(CExpression & expresie);
	
	struct nod 
	{
		struct nod *left,*right;
		unsigned char operatie; 
		union { double valoare;
		CString *valoarestr;};
	} ;
	
	typedef nod NOD;
	typedef nod *arbore;
	
	arbore CloneTree(void);
	int UpdateArbore(void);		// Update the tree
	arbore GetArbore();
	int Value(double & valoare);	// gets the value of the expression
	int ChangeExpression(CString& expresie);	// Change expression
	virtual void Serialize(CArchive& ar);		// The serialization function
	
	CExpression();
	CExpression(CMapVariabile * vars);
	virtual ~CExpression();

private:
	CMapVariabile * m_pvariabile;	// pointer to value table
	CString m_definitie;			// the expression in string
	int pozitie;					// string parsing variable
	arbore m_Arbore;				// the expresion as a binary tree
	
	double vexp ( arbore a );
	arbore factor (void);			// the partial expresion parsing functions
	arbore identificator(void);
	arbore putere(void);
	arbore termen(void);
	arbore expresie(void);
	void elibmem ( arbore a);
	arbore clone(arbore arb);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNCTION_H__893B59C6_B160_11D1_8170_00002145DF91__INCLUDED_)
