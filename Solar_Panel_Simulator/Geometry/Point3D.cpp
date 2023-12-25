#include "pch.h"
#include "Point3D.h"

Point3D::Point3D() :
	mX(0.0),
	mY(0.0),
	mZ(0.0)
{

}

Point3D::Point3D(float uX, float uY, float uZ) :
	mX(uX),
	mY(uY),
	mZ(uZ)
{

}

Point3D::~Point3D()
{

}

float Point3D::x()
{
	return mX;
}
float Point3D::y()
{
	return mY;
}
float Point3D::z()
{
	return mZ;
}

void Point3D::setX(float uX)
{
	mX = uX;
}

void Point3D::setY(float uY)
{
	mY = uY;
}

void Point3D::setZ(float uZ)
{
	mZ = uZ;
}

// Overloaded << operator to allow streaming of Point3D objects
std::ostream& operator<<(std::ostream& os, const Point3D& point)
{
	os << "Point(" << point.mX << ", " << point.mY << ", " << point.mZ << ")";
	return os;
}