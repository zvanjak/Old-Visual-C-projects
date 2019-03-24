// Function.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "math.h"
#include "express.h"
#include <ctype.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




IMPLEMENT_SERIAL(CExpression, CObject, 0)




//////////////////////////////////////////////////////////////////////
// CExpression Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Variabile Globale

//parametrii Global(50);




/////////////////////////////////////////////////////////////////////////////////
// Eliberarea memorie ocupate de arbore

void CExpression::elibmem ( arbore a)
{
if (a==NULL) return;
if (a->left!=NULL) elibmem(a->left);
if (a->right!=NULL) elibmem(a->right);
if (a->operatie == '`')
		delete a->valoarestr;
delete a;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpression::CExpression()
{
	m_Arbore = NULL;
	m_definitie = "";
	pozitie = 0;
	m_pvariabile = NULL;
}

CExpression::CExpression(CMapVariabile * vars)
{
	m_Arbore = NULL;
	m_definitie = "";
	pozitie = 0;
	m_pvariabile = vars;
}

CExpression::~CExpression()
{
 elibmem (m_Arbore);
}

void CExpression::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_definitie;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_definitie;
		m_Arbore = NULL;
		pozitie = 0;
		UpdateArbore();
		// After loading this object if it contains variables you should atach a variable 
		// Table to it
	}
}


int CExpression::UpdateArbore()
{
	if (m_definitie.IsEmpty())
		return 0;
	elibmem(m_Arbore); // Eliberarea memoriei ocupate de arbore
	pozitie = 0;
	m_Arbore = expresie();
	if (m_Arbore == NULL)
		return pozitie;
	else return -1;
}

CExpression::arbore CExpression::expresie()
{
	arbore nod;
	arbore arb1 = termen();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	

	while ((m_definitie[pozitie]=='-') || (m_definitie[pozitie]=='+')) 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = termen();
		if  (arb2 == NULL) return NULL;  // In caz de eroare terminate
		nod->right=arb2;
		arb1 = nod;
	}
	return arb1;
}

CExpression::arbore CExpression::termen()
{
	arbore nod;
	arbore arb1 = putere();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	

	while ((m_definitie[pozitie]=='*') || (m_definitie[pozitie]=='/')) 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = putere();
		if  (arb2 == NULL) return NULL;  // In caz de eroare terminate
		nod->right=arb2;
		arb1 = nod;
	}
	return arb1;
}



CExpression::arbore CExpression::putere()
{
	arbore nod = NULL;
	arbore arb1 = factor();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	

	while (m_definitie[pozitie]=='^') 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = factor();
		if  (arb2 == NULL) return NULL;  // In caz de eroare terminate
		nod->right=arb2;
		arb1 = nod;
	}
	return arb1;
}


CExpression::arbore CExpression::factor()
{
 arbore nod = NULL,nod2 = NULL,left = NULL;
 while(m_definitie[pozitie] == ' ' && m_definitie[pozitie] != '\0')
	 pozitie++;

 if (m_definitie[pozitie]=='-')
   {
    nod = new NOD;
    left = new NOD;
    left->right=NULL;
    left->left=NULL;
    left->operatie='!';
    left->valoare=-1;
    nod->left=left;
    nod->operatie='*';
    pozitie++;
	nod->right = expresie();
	if (nod->right == NULL) return NULL;
	return nod;   
 }
 if (m_definitie[pozitie]=='(')
    {
      pozitie++;
      nod = expresie();
      if (nod == NULL) return NULL;
	  pozitie++;
	  return nod;
    }
 else if (m_definitie[pozitie]=='|')
	 {
	   pozitie++;
	   nod2 = expresie();
	   if (nod2 == NULL) return NULL;
	   nod = new NOD;
	   nod->left=nod2;
	   nod->right=NULL;
	   nod->operatie='|';
	   pozitie++;
	   return nod;
	}
     else return identificator();
 return nod;
}

CExpression::arbore CExpression::identificator()
{
	int poz;
	
	arbore nod = NULL,nod2 = NULL;
	poz=pozitie;
	if (m_definitie[pozitie]=='\0') return NULL;
	if (isdigit(m_definitie[pozitie]))	// Este numar ?
		{
			while  ((isdigit(m_definitie[pozitie]) || (m_definitie[pozitie]=='.')))
					 pozitie++;
			nod = new NOD;
			nod->left = NULL; 
			nod->right = NULL;
			nod->operatie = '!';
			nod->valoare = atof(m_definitie.Mid(poz,pozitie-poz));
		}
	if (isalpha(m_definitie[pozitie]))	// Am i an identifier ?
	{
		while  (isalnum(m_definitie[pozitie])) 
				pozitie++;
			
		

		CString id = m_definitie.Mid(poz,pozitie-poz);
		CString nid = id;
		id.MakeUpper();

		if (id =="SIN")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=150;
			return nod;
		}
		if (id =="COS")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=151;
			return nod;
		}
		if (id =="EXP")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=152;
			return nod;
		}
		if (id =="SQRT")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=153;
			return nod;
		}
		if (id =="LOG")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=154;
			return nod;
		}
		if (id =="TG")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=155;
			return nod;
		}
		if (id =="CTG")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=156;
			return nod;
		}
		if (id =="ASIN")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=157;
			return nod;
		}
		if (id =="ACOS")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=158;
			return nod;
		}
		if (id =="ATG")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=159;
			return nod;
		}
		CValue *valoare;
		if (m_pvariabile->Lookup(nid,valoare))
		{
			nod = new NOD;
			nod -> left = NULL;
			nod -> right = NULL;
			nod -> operatie = '`';
			nod -> valoarestr = new CString(nid); 
		
		}
		else 
			return NULL;
	}
	return nod;
        
}

int CExpression::ChangeExpression(CString & expresie)
{
	m_definitie = expresie + '\0';
	return UpdateArbore();
}


// Error code var
int code;


int CExpression::Value(double& valoare)
{
  code=0;
  if (m_Arbore == NULL) return -1;
  valoare=vexp(m_Arbore);
  return (code);
}


double CExpression::vexp ( arbore a )
{
double v;
if (a->operatie==NULL) {code=10;return 0;}
switch(a->operatie) 
 {
 case '+' : return( vexp(a->left)+vexp(a->right) );
 case '-' : return( vexp(a->left)-vexp(a->right) );
 case '*' : return( vexp(a->left)*vexp(a->right) );
 case '/' : v=vexp(a->right) ;
			 if (v==0)
			 {code=DIVISION_BY_0;return -vexp(a->left)/0.001;}
			 else
				return(vexp(a->left)/v);
 case 150 : return(sin(vexp(a->left)));
 case 151 : return(cos(vexp(a->left)));
 case 152 : return(exp(vexp(a->left)));
 case 153 : v=vexp(a->left) ;
			 if (v<0) {code=INVALID_DOMAIN;return 0;}
			 else return(sqrt(v));
 case 154 : v=vexp(a->left) ;
			 if (v<=0) {code=INVALID_DOMAIN;return 0;}
			 else return(log(v));
 case 155 : return (tan (vexp(a->left)));
 case 156 : return (1 / tan (vexp(a->left)));
 case 157 : return (asin (vexp(a->left)));
 case 158 : return (acos (vexp(a->left)));
 case 159 : return (atan (vexp(a->left)));
 case '|' : return(fabs(vexp(a->left)));
 case '^' : return(pow(vexp(a->left),vexp(a->right)));
 case '!' : return (a->valoare);
 default  : {
				if (m_pvariabile==NULL) 
				{
					code=UNDEFINED_VARIABLE;
					return 0;
				}
				CValue *valoare;
				if (!m_pvariabile->Lookup(*a->valoarestr,valoare))
				{
					code=UNDEFINED_VARIABLE;
					return 0;
				}
				else 
				return valoare->GetValue();
			}
 }
}


CExpression::arbore CExpression::GetArbore()
{
	return m_Arbore;
}


CExpression::CExpression(CExpression & expresie)
{
	*this = expresie;
}




CExpression::arbore CExpression::CloneTree()
{
	return clone(m_Arbore);	
}

void CExpression::AtachVariables(CMapVariabile * vars)
{
	m_pvariabile = vars;
}

CExpression::arbore CExpression::clone(arbore arb)
{
	if (arb == NULL)
		return NULL;
	arbore clonArb = new NOD;
	*clonArb = *arb;
	clonArb->left = clone(arb->left);
	clonArb->right = clone(arb->right);
	return clonArb;
}

CExpression& CExpression::operator=(CExpression &expr)
{
	m_definitie = expr.m_definitie;
	m_pvariabile = expr.m_pvariabile;
	pozitie = 0;
	m_Arbore = expr.CloneTree();
	return *this;
}
