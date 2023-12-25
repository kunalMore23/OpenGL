#pragma once
#include "Point3D.h"

class GEOMETRY_API Line : public Point3D
{
public:
	Line();
	Line(Point3D uP1, Point3D uP2);
	~Line();

	Point3D p1();
	Point3D p2();
	float length();

	void setP1(Point3D uP1);
	void setP2(Point3D uP2);

private:
	void setLength();

private:
	Point3D mP1;
	Point3D mP2;
	float mLength;
};

