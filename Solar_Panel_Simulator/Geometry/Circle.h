#pragma once
#include "Point3D.h"
#include <vector>

class GEOMETRY_API Circle : public Point3D
{
public:
	Circle();
	Circle(Point3D gCenter, float gRadius);
	~Circle();

private:
	void makeCircle();
	void colorCicle(std::vector<float>& mVertices, std::vector<float>& mColors, Point3D uColor);

private:
	std::vector<Point3D> mPoints;
	float radius;
	Point3D center;
	int sSegments = 600;
	Point3D color;
};