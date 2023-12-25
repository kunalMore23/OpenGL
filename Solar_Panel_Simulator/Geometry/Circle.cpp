#include "pch.h"
#include "Circle.h"
#include<vector>

Circle::Circle()
{

}

Circle::Circle(Point3D gCenter, float gRadius)
	: center(gCenter),
	radius(gRadius)
{
	makeCircle();
}

Circle::~Circle()
{

}

void Circle::makeCircle()
{
	mPoints.push_back(center);

	for (int i = 0; i < sSegments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(sSegments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		mPoints.push_back(Point3D(center.x() + x, center.y() + y, 0.0));
	}
}

void Circle::colorCicle(std::vector<float>& mVertices, std::vector<float>& mColors, Point3D uColor)
{
	mVertices.clear();
	mColors.clear();
	color = uColor;
	for (auto point : mPoints)
	{
		mVertices.push_back(point.x());
		mVertices.push_back(point.y());

		mColors.push_back(color.x() / 255.0f);
		mColors.push_back(color.y() / 255.0f);
		mColors.push_back(color.z() / 255.0f);

		mVertices.push_back(center.x());
		mVertices.push_back(center.y());

		mColors.push_back(color.x() / 255.0f);
		mColors.push_back(color.y() / 255.0f);
		mColors.push_back(color.z() / 255.0f);
	}
}