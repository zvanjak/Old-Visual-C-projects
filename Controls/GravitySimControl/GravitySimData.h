class Vector3D {
public:
//	Vector3D();
	Vector3D(double x=0, double y=0, double z=0);

	Vector3D	operator+( const Vector3D &b );
	Vector3D	operator-( const Vector3D &b );
	double		operator*( const Vector3D &b );	// skalarni umnožak
	Vector3D	operator&( const Vector3D &b );	// vektorski umnožak

	Vector3D	operator*( double b );
	Vector3D	operator/( double b );

	friend	Vector3D	operator*( double a, const Vector3D &b );

	Vector3D&	operator=( const Vector3D &b );

private:
	double	m_dX;
	double	m_dY;
	double	m_dZ;
};

class CBody {
public:
	CBody(double dMass, double dCharge, Vector3D vecSpeed, Vector3D vecPos);

private:
	double		m_dMass;			// masa
	double		m_dCharge;		// naboj
	Vector3D	m_vecSpeed;		// brzina
	Vector3D	m_vecPos;			// pozicija
};
