#include "matrix.h"

#include <complex>
#include <iostream>
#include <time.h>

/*****************************************************************************************/
/*****************************************************************************************/

template<class _Type> bool Matrix<_Type>::Allocate( int Rows, int Cols )
{
	m_nRowNum = (Rows > 0) ? Rows : 0;
	m_nColNum = (Cols > 0) ? Cols : 0;

	/* rezerviraj mjesto za 'm' pokazivaèa na 'm' redaka */
	if( !(m_pdElem = new _Type *[RowNum()]) )	{				
		// nema memorije
		Valid = false;
		return false;
	}
	else {
		for( int i=0; i<RowNum(); i++ )
			if( ColNum() > 0 ) {
				if( !(m_pdElem[i] = new _Type[ColNum()] ) ) {
					// nema memorije
					Valid = false;
					return false;
				}
			}
			else
				m_pdElem[i] = NULL;
	}
	Valid = true;

	return true;
}

template<class _Type> bool Matrix<_Type>::Deallocate()
{
	int		i;

	if( m_pdElem != NULL ) {                             
		if( ColNum() != 0 ) {
			for( i=0; i<RowNum(); i++ )        
				if( m_pdElem[i] != NULL ) {
					delete [](m_pdElem[i]);
				}
		}
		if ( RowNum() != 0 ) {
			delete []m_pdElem;
			m_pdElem = NULL;
		}                                    
	}
	Valid = false;

	return true;
}

/*****************************************************************************************/

template<class _Type> void Matrix<_Type>::Print()
{
	int		i, j;

	for( i=0; i<RowNum(); i++ ) 
	{
		// prelazak u sljedeæi redak
		std::cout << '\n';
		
		for( j=0; j<ColNum(); j++ ) {
			std::cout.width(10);
			std::cout << m_pdElem[i][j];
		}
	}
}

template<class _Type> void Matrix<_Type>::Print( int width, int prec )
{
	int		i, j;

	for( i=0; i<RowNum(); i++ ) 
	{
		// prelazak u sljedeæi redak
		std::cout << '\n';
		
		for( j=0; j<ColNum(); j++ ) {
			std::cout.width(width);
			std::cout.precision(prec);
			std::cout << m_pdElem[i][j];
		}
	}
}

template<class _Type> void Matrix<_Type>::Print(FILE *fp, char *format)
{
	int		i, j;

	for( i=0; i<RowNum(); i++ ) 
	{
		// prelazak u sljedeæi redak
		fputc('\n',fp);
		for( j=0; j<ColNum(); j++ ) {
			fprintf(fp, format, m_pdElem[i][j]);
		}
	}
}

template<class _Type> void Matrix<_Type>::Print(std::ostream& s)
{
	int		i, j;

	for( i=0; i<RowNum(); i++ ) 
	{
		// prelazak u sljedeæi redak
		s << '\n';
		
		for( j=0; j<ColNum(); j++ ) {
			s.width(10);
			s << m_pdElem[i][j];
		}
	}
}

template<class _Type> void Matrix<_Type>::Print(std::ostream& s, int width, int prec)
{
	int		i, j;

	for( i=0; i<RowNum(); i++ ) 
	{
		// prelazak u sljedeæi redak
		s << '\n';
		
		for( j=0; j<ColNum(); j++ ) {
			s.width(width);
			s.precision(prec);
			s << m_pdElem[i][j];
		}
	}
}

template<class _Type> bool Matrix<_Type>::SaveBinary(FILE *fp)
{
	if( fp != NULL && ColNum() > 0 ) {
		int		r, s;

		r = RowNum();
		s = ColNum();
		fwrite(&r, sizeof(int), 1, fp);			// zapiši broj redaka
		fwrite(&s, sizeof(int), 1, fp);			// zapiši broj stupaca
		
		// zapiši elemente redaka
		for( int i=0; i<RowNum(); i++ )
			fwrite(m_pdElem[i], sizeof(_Type), ColNum(), fp);
	}
	else 
		return false;

	return true;
}

template<class _Type> bool Matrix<_Type>::LoadBinary(FILE *fp)
{
	int		r, s;

	fread(&r, sizeof(int), 1, fp);
	fread(&s, sizeof(int), 1, fp);

	if( r>0 && s>0 ) {
		if( RowNum() != r || ColNum() != s ) 
		{
			// ukoliko su razlièitih dimenzija, treba prilagoditi velièinu matrice u koju æe se uèitavati
			// najprije treba provjeriti da li æe biti mjesta za matricu nove velièine
			if( IsMemoryAvailable<_Type>(r,s) == true ) 
			{
				// i tek onda æemo se riješiti stare matrice
				Deallocate();
				if( Allocate(r,s) != true ) {
					// nema memorije
					;
				}
				for( int i=0; i<r; i++ )
					fread(m_pdElem[i], sizeof(_Type), ColNum(), fp);
			}
			else
				return false;
		}
		else {
			for( int i=0; i<r; i++ )
				fread(m_pdElem[i], sizeof(_Type), ColNum(), fp);
		}
	}
	else
		return false;

	return true;
}

/*****************************************************************************************/
/******************									KONSTRUKTORI										**********************/
/*****************************************************************************************/

template<class _Type> Matrix<_Type>::Matrix()
{
	m_nRowNum = 0;
	m_nColNum = 0;
	m_pdElem = NULL;
	Valid = false;
}

template<class _Type> Matrix<_Type>::Matrix( int Rows, int Cols, int nParam )
{
	int     i;

	m_nRowNum = (Rows > 0) ? Rows : 0;
	m_nColNum = (Cols > 0) ? Cols : 0;

	if( RowNum() > 0 )	{
		if( !(m_pdElem = new _Type *[RowNum()]) )         /* rezerviraj mjesto za 'm' pokazivaŸa na 'm' redaka */
		{				
			// nema memorije
			Valid = false;
		}
		else
			if( nParam == CONT_ALLOCATION ) {
				// ovdje æemo alocirati cijelu matricu tako da zauzima kontinuirani
				// blok memorije
				_Type		*pdTmp;

				pdTmp = new _Type[RowNum() * ColNum()];
				
				for( i=0; i<RowNum(); i++ )
					m_pdElem[i] = pdTmp + ColNum()*i;
			}
			else {
				for( i=0; i<RowNum(); i++ )        
					if( ColNum() > 0 ) {
						if( !(m_pdElem[i] = new _Type[ColNum()] ) ) {			
							// nema memorije
							Valid = false;
						} 
						else {
							for( int j=0; j<ColNum(); j++ )
								m_pdElem[i][j] = 0;
						}
					}
					else
						m_pdElem[i] = NULL;
			}
	}
	else {	
		// krivi broj redaka
		Valid = false;
	}
}

template<class _Type> Matrix<_Type>::Matrix( const Matrix<_Type> &Copy )
{
	int     i;

	if( Copy.RowNum() <= 0 )	{	
		// krive dimenzije matrice
		;
	}

	if( Allocate(Copy.RowNum(), Copy.ColNum()) == true ) {
		for( i=0; i<RowNum(); i++ )
			memmove( m_pdElem[i], Copy.m_pdElem[i], sizeof(_Type) * Copy.ColNum() );
	}
	else {
		// nije bilo memorije za alociranje matrice
		;
	}
}

// Copy == COPY -> alocirati æemo novu memoriju za matricu i iskopirati vrijednosti
// Copy == NO_COPY -> samo æemo u novu matricu preuzeti pokazivaèe iz predane matrice
template<class _Type> Matrix<_Type>::Matrix( _Type **Elem, int Row, int Col, int Copy )
{
	int		i;

	if( Copy == COPY ) {
		if( Allocate(Row,Col) == true ) {
			for( i=0; i<RowNum(); i++ )
				memmove( m_pdElem[i], Elem[i], sizeof(_Type) * ColNum() );
		}
		else {
			// nema memorije
			;
		}
	}
	else {
		m_nRowNum = (Row > 0) ? Row : 0;
		m_nColNum = (Col > 0) ? Col : 0;

		if( RowNum() > 0 && ColNum() > 0 )	{
			for( i=0; i<RowNum(); i++ )
				m_pdElem[i] = Elem[i];
		}
	else
		m_pdElem = NULL;
	}
}

template<class _Type> Matrix<_Type>::~Matrix()
{
	Deallocate();
}


template<class _Type> bool Matrix<_Type>::Resize( int NewRowNum, int NewColNum )
{
	Deallocate();
	Allocate(NewRowNum,NewColNum);

	if( IsValid() )
		return true;
	else
		return false;
}

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator+( const Matrix &b ) const
{
	Matrix<_Type>		ret(*this);

	ret += b;
	return ret;
}

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator-( const Matrix &b ) const
{
	Matrix<_Type>		ret(*this);

	ret -= b;
	return ret;
}

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator*( const Matrix &b ) const
{
	int			i, j;
	Matrix	ret(RowNum(), b.ColNum());

	if( ColNum() == b.RowNum() ) 
	{
		// najprije izmnoži matrice
		for( i=0; i<ret.RowNum(); i++ )
			for( j=0; j<ret.ColNum(); j++ ) {
				ret.m_pdElem[i][j] = 0;
				
				for( int k=0; k<ColNum(); k++ )
					ret.m_pdElem[i][j] += m_pdElem[i][k] * b.m_pdElem[k][j];
			}
	}
	else {				
		// krive dimenzije matrice
		;
	}

	return	ret;
}

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator+=( const Matrix &b )
{
	if( RowNum() == b.RowNum() && ColNum() ==b.ColNum() )
	{
		for( int i=0; i<RowNum(); i++ )
			for( int j=0; j<ColNum(); j++ )
				m_pdElem[i][j] += b.m_pdElem[i][j];
	}
	else {			
		// kriva dimenzija matrice
		;
	}

	return *this;
}

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator-=( const Matrix &b )
{
	if( RowNum() == b.RowNum() && ColNum()==b.ColNum() )
	{
		for( int i=0; i<RowNum(); i++ )
			for( int j=0; j<ColNum(); j++ )
				m_pdElem[i][j] -= b.m_pdElem[i][j];
	}
	else {			
		// kriva dimenzija matrice
		;
	}

	return *this;
}

template<class _Type> Matrix<_Type>  Matrix<_Type>::operator*=( const	Matrix &b )
{
	int			i, j;
	Matrix	ret(RowNum(), b.ColNum());

	if( ColNum() == b.RowNum() ) 
	{
		// najprije izmnoži matrice
		for( i=0; i<ret.RowNum(); i++ )
			for( j=0; j<ret.ColNum(); j++ ) {
				ret.m_pdElem[i][j] = 0;
				
				for( int k=0; k<ColNum(); k++ )
					ret.m_pdElem[i][j] += m_pdElem[i][k] * b.m_pdElem[k][j];
			}
		
		// a sada to sve stavi u onu s lijeve strane
		for( i=0; i<ret.RowNum(); i++ )
			for( j=0; j<ret.ColNum(); j++ )
				m_pdElem[i][j] = ret.m_pdElem[i][j];
	}
	else {				
		// krive dimenzije matrice
		;
	}

	return	*this;
}

template<class _Type> Matrix<_Type>	Matrix<_Type>::operator*=( _Type b )
{
	for( int i=0; i<this->RowNum(); i++ )
		for( int j=0; j<this->ColNum(); j++ )
			m_pdElem[i][j] *= (_Type) b;

	return *this;
}

template<class _Type> Matrix<_Type>& Matrix<_Type>::operator=( const Matrix<_Type> &b )
{
	int		i;

	if( m_pdElem != NULL && b.m_pdElem != NULL )
	{
		if( RowNum() != b.RowNum() || ColNum() != b.ColNum() )       	/* ako matrice koje se pridružuju nisu iste dimenzije */
		{
			// Pridruzuju se matrice razlicitih dimenzija (%d,%d)->(%d,%d)!!!", m_nRowNum, m_nColNum, b.m_nRowNum, b.m_nColNum);
			// staru matricu brišemo
			Deallocate();

			// i alociramo novu
			if( Allocate(b.RowNum(), b.ColNum()) != true ) {
				// nema memorije
				;
			}
		}
		for(i=0; i<RowNum(); i++ )
			memmove(m_pdElem[i], b.m_pdElem[i], sizeof(_Type) * b.m_nColNum );
	}

	return *this;
}

template<class _Type> _Type*	Matrix<_Type>::operator[]( int i )
{
	if( i<0 || i>RowNum() )	{
		// Array bound violation in matrix[] !!!;
		;
		return NULL;
	}
	else
		return m_pdElem[i];
}

/*****************************************************************************************/
/*****************************************************************************************/

template<class _Type> Matrix<_Type>& Matrix<_Type>::Transp()
{
	_Type		tmp;

	// provjeriti dimenzije ( možda je potrebno realocirati matricu )
	for( int i=0; i<RowNum(); i++ ) {
		for( int j=0; j<ColNum(); j++ ) {
			tmp = m_pdElem[i][j];
			m_pdElem[i][j] = m_pdElem[j][i];
			m_pdElem[j][i] = tmp;
		}
	}
	
	return *this;
}

/*****************************************************************************************/
/*****************************************************************************************/

template<class _Type> void Matrix<_Type>::Clear( void )
{
	for( int i=0; i<RowNum(); i++ )
		for( int j=0; j<ColNum(); j++ )
			m_pdElem[i][j] = _Type(0);
}

template<class _Type> void Matrix<_Type>::MakeUnitMatrix( void )
{
	if( IsSquare() == true ) {
		this->Clear();
		for( int i=0; i<RowNum(); i++ )
			m_pdElem[i][i] = _Type(1);
	}
}

template<class _Type> void Matrix<_Type>::MakeRandomElements( _Type dMax, _Type dMin )
{
	int			i,j;
	double	transf;

	srand( (unsigned)time( NULL ) );
	transf = (dMax - dMin) / RAND_MAX;

	for( i=0; i<RowNum(); i++ )
		for( j=0; j<ColNum(); j++ )
			m_pdElem[i][j] = (_Type) (rand() * transf + dMin);
}

template<class _Type> bool Matrix<_Type>::IsSymetric( double dTiny )
{
	if( IsSquare() == true ) {
		for( int i=0; i<RowNum(); i++ )
			for( int j=i+1; j<ColNum(); j++ )
				if( m_pdElem[i][j] != m_pdElem[j][i] )
					return false;
	}
	else
		return false;

	return true;
}
/*
template<class _Type> bool Matrix<_Type>::IsOrthogonal( double dTiny )
{
	return false;
}
*/
/*****************************************************************************************/
/*****************************************************************************************/
//	Eksplicitna instancijacija kako bi u biblioteci 
//	imali Matrix veæ definiran za osnovne tipove

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<std::complex>;
