#include "pch.h"
#include "Line.h"
#include<cmath>


Line::Line()
{

}

Line::Line(Point3D uP1, Point3D uP2)
	: mP1(uP1),
	mP2(uP2)
{
}

Line::~Line()
{

}

Point3D Line::p1()
{
	return mP1;
}

Point3D Line::p2()
{
	return mP2;
}

float Line::length()
{
	setLength();
	return mLength;
}

void Line::setLength()
{
	mLength = sqrt(pow((mP1.x() - mP2.x()), 2.0f) + pow((mP1.y() - mP2.y()), 2.0f) + pow((mP1.z() - mP2.z()), 2.0f));
}

void Line::setP1(Point3D uP1)
{
	mP1 = uP1;
}

void Line::setP2(Point3D uP2)
{
	mP2 = uP2;
}
