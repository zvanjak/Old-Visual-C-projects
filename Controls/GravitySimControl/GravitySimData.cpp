#include <math.h>
#include "GravitySimData.h"

CBody::CBody(double dMass, double dCharge, Vector3D vecSpeed, Vector3D vecPos )
{
	m_dMass = dMass;
	m_dCharge = dCharge;
	m_vecSpeed = vecSpeed;
	m_vecPos = vecPos;
}

/****************************************************************************/
/****************************************************************************/

Vector3D::Vector3D(double x, double y, double z)
{
	m_dX = x;
	m_dY = y;
	m_dZ = z;
}

Vector3D	Vector3D::operator+( const Vector3D &b )
{
	return Vector3D(m_dX + b.m_dX, m_dY + b.m_dY, m_dZ + b.m_dZ);
}

Vector3D	Vector3D::operator-( const Vector3D &b )
{
	return Vector3D(m_dX - b.m_dX, m_dY - b.m_dY, m_dZ - b.m_dZ);
}

double	Vector3D::operator*( const Vector3D &b )	// skalarni umnožak
{
	return (m_dX * b.m_dX + m_dY * b.m_dY + m_dZ * b.m_dZ);
}

Vector3D	Vector3D::operator&( const Vector3D &b )	// vektorski umnožak
{
	Vector3D	vecRet;

	vecRet.m_dX = m_dY * b.m_dZ - m_dZ * b.m_dY;
	vecRet.m_dY = -(m_dX * b.m_dZ - m_dZ * b.m_dX);
	vecRet.m_dZ = m_dX * b.m_dY - m_dY * b.m_dX;

	return vecRet;
}

Vector3D	Vector3D::operator*( double b )
{
	return Vector3D(m_dX * b, m_dY * b, m_dZ * b);
}

Vector3D	Vector3D::operator/( double b )
{
	return Vector3D(m_dX / b, m_dY / b, m_dZ / b);
}

Vector3D	operator*( double a, const Vector3D &b )
{
	return Vector3D(a * b.m_dX, a * b.m_dY, a * b.m_dZ);
}

Vector3D&	Vector3D::operator=( const Vector3D &b )
{
	m_dX = b.m_dX;
	m_dY = b.m_dY;
	m_dZ = b.m_dZ;

	return *this;
}