#pragma once
#include "Line.h"

class GEOMETRY_API Rectangle : public Line
{
public:
	Rectangle();
	Rectangle(Point3D p1, Point3D p2, Point3D p3, Point3D p4);
	~Rectangle();

private:
	Point3D mP1;
	Point3D mP2;
	Point3D mP3;
	Point3D mP4;

	Line mL1;
	Line mL2;
	Line mL3;
	Line mL4;
};