#pragma once
#include "Geometry.h"
#include<iostream>
#include "pch.h"
class GEOMETRY_API Point3D
{
public:
	Point3D();
	Point3D(float uX, float uY, float uZ);
	~Point3D();

	float x();
	float y();
	float z();

	void setX(float uX);
	void setY(float uY);
	void setZ(float uZ);

private:
	float mX;
	float mY;
	float mZ;

	// Friend declaration to allow the operator<< function access private members
	friend std::ostream& operator<<(std::ostream& os, const Point3D& point);
};
