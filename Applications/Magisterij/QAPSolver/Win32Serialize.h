#ifndef	_WIN32_SER
#define _WIN32_SER

#include <afx.h>
#include <string>
#include <vector>

#include <Mathlib\Matrix.h>

using std::string;

void	LoadSTLstring( CArchive &ar, std::string &str );
void	SaveSTLstring( CArchive &ar, std::string &str );

bool	SerializeInArchive( CArchive& ar, Matrix<float>	&mat );

template<class _Type> bool	SerializeInArchive( CArchive &ar, std::vector<_Type> &vec )
{
	int		i, Size;

	if( ar.IsStoring() ) {
		Size = vec.size();
		ar << Size;

		for( i=0; i<Size; i++ )
			ar << vec[i];
	}
	else {
		ar >> Size;

		vec.resize(Size);
		for( i=0; i<Size; i++ )
			ar >> vec[i];
	}
	return true;
}

#endif
