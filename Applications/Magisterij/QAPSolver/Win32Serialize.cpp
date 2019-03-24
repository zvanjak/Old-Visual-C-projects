#include "stdafx.h"
#include <Optimization\Win32Serialize.h>

void	LoadSTLstring( CArchive &ar, std::string &str )
{
	CString	temp;
	ar >> temp;
	str = string(LPCTSTR(temp));
}

void	SaveSTLstring( CArchive &ar, std::string &str )
{
	CString	temp(str.c_str());
	ar << temp;
}

bool	SerializeInArchive( CArchive& ar, Matrix<float>	&mat )
{
	if( ar.IsStoring() ) {		// snimanje
		ar << mat.RowNum();
		ar << mat.ColNum();

		int		i, j;
		for( i=1; i<=mat.RowNum(); i++ )
			for( j=1; j<=mat.ColNum(); j++ )
				ar << mat[i][j];
	}
	else {		// uèitavanje
		int		i, j, Rows, Cols;

		ar >> Rows;
		ar >> Cols;

		mat.Resize(Rows, Cols);
		for( i=1; i<=mat.RowNum(); i++ )
			for( j=1; j<=mat.ColNum(); j++ )
				ar >> mat[i][j];
	}
	return true;
}
