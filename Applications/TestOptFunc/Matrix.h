#ifndef MATRIX_H
#define MATRIX_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <iostream>

#define NO_CONT_ALLOCATION		1
#define	CONT_ALLOCATION				2

#define	COPY			1
#define	NO_COPY		2

// provjera 2

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////			        RAZRED MATRIX				        /////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

template<class _Type> class Matrix {
public:
	//	konstruktori i destruktori
	Matrix();
	Matrix( int rows, int cols, int nParam=NO_CONT_ALLOCATION );
	Matrix( const Matrix &Copy );
	Matrix( _Type **Elem, int Row, int Col, int Copy=COPY );
	~Matrix();

	//	matematièke operacije
	Matrix		operator+( const Matrix &b ) const;
	Matrix		operator-( const Matrix &b ) const;
	Matrix		operator*( const Matrix &b ) const;

	Matrix		operator+=( const Matrix &b );
	Matrix		operator-=( const Matrix &b );
	Matrix		operator*=( const Matrix &b );
	Matrix		operator*=( _Type b );
	_Type*		operator[]( int i );

	//	operator pridruživanja
	Matrix&		operator=( const Matrix &b );

	// operacije s matricama
	Matrix&		Transp();

	// pomoæne funkcije za rad s matricom
	void	Clear( void );
	void	MakeUnitMatrix( void );
	void	MakeRandomElements( _Type dMax, _Type dMin );
	bool	Resize( int NewRowNum, int NewColNum );

	int		RowNum() const { return m_nRowNum; }
	int		ColNum() const { return m_nColNum; }
	
	bool	IsSquare( void ) { return (RowNum()==ColNum() ? true : false); }
	bool	IsSymetric( double dTiny = 1e-6 );
//	bool	IsOrthogonal( double dTiny = 1e-6 );
//	bool	IsHermitian(); 

	bool	IsValid() { return Valid; }

	// funkcije za ispis na ekran, stream i u datoteku
	void	Print();
	void	Print(int width, int prec);
	void	Print(FILE *fp, char *format);
	void	Print(std::ostream&);
	void	Print(std::ostream&, int width, int prec);

	bool	SaveBinary(FILE *fp);
	bool	LoadBinary(FILE *fp);

private:
	bool	Allocate( int RowNum, int ColNum );
	bool	Deallocate();

	friend	bool IsMemoryAvailable( int Rows, int Cols );

private:
	//	èlanske varijable
	int			m_nRowNum, m_nColNum;
	_Type		**m_pdElem;

	bool		Valid;		// da li je matrica ispravno alocirana
};

/*****************************************************************************************/
//			Dodatne funkcije

template<class _Type>  bool	IsMemoryAvailable( int Rows, int Cols );

template<class _Type, class _TypeScal>  Matrix<_Type>	 operator*( _TypeScal a, const Matrix<_Type> &b );
template<class _Type, class _TypeScal>  Matrix<_Type>	 operator*( const Matrix<_Type> &a, _TypeScal b );

template<class _Type>	 Matrix<_Type>	 Transp(Matrix<_Type> &a);
template<class _Type>	 Matrix<_Type>*  CreateTransp(Matrix<_Type> &a);

/*****************************************************************************************/
//			Implementacija dodatnih funkcija

template<class _Type> bool	IsMemoryAvailable( int Rows, int Cols )
{
	Matrix<_Type>	a(0,0);

	if( a.Allocate(Rows,Cols) == true ) {
		a.Deallocate();
		return true;
	}
	else
		return false;
}

template<class _Type, class _TypeB> Matrix<_Type>	operator*( _TypeB a, const Matrix<_Type> &b ) {
	Matrix<_Type>	ret(b);

	ret *= (_Type) a;
	return ret;
}

template<class _Type, class _TypeB> Matrix<_Type>	operator*( const Matrix<_Type> &a, _TypeB b  ) {
	Matrix<_Type>	ret(a);

	ret *= (_Type) b;
	return ret;
}

template<class _Type> Matrix<_Type> Transp(Matrix<_Type> &a)
{
	Matrix	ret(a.ColNum(),a.RowNum());

	for( int i=0; i<Ret.RowNum(); i++ )
		for( int j=0; j<Ret.ColNum(); j++ )
			Ret.m_pdElem[i][j] = a[j][i];

/* a može i ovako
	Matrix		ret(a);

	ret.Transp();
	return ret;
*/
}

template<class _Type>	 Matrix<_Type>*  CreateTransp(Matrix<_Type> &a)
{
	Matrix<_Type>		*pMat;

	pMat = new Matrix<_Type>(a.colNum(), a.RowNum());
	
	if( pMat->IsValid() ) {		// ako je matrica ispravno alocirana
		for( int i=0; i<a.RowNum(); i++ )
			for( int j=0; j<a.ColNum(); j++ )
				(*pMat)[j][i] = a[i][j];
	}

	return pMat;
}


#endif