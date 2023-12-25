#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(Point3D p1, Point3D p2, Point3D p3, Point3D p4)
	: mP1(p1), mP2(p2), mP3(p3), mP4(p4),
	mL1(p1, p2), mL2(p2, p3), mL3(p3, p4), mL4(p4, p1)
{
}

Rectangle::~Rectangle()
{

}