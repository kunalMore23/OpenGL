#include "pch.h"
#include "Solar_Panel_System.h"
#include<cmath>

#define PI 3.14159265359f

Solar_Panel_System::Solar_Panel_System()
{
	isRevolving = false;
	sunPos = new Point3D(7.5f, 0.0f, 0.0f);
	mMultiplier = 1.0f;
	orbitX = 0.0f;
	orbitY = -8.0f;
}

Solar_Panel_System::~Solar_Panel_System()
{
}

void Solar_Panel_System::showSolarPanelSystem(floatList& mVertices, floatList& mColors)
{
	//drawSun(mVertices, mColors);
	//drawSun(floatListVertices, mColors, float cx, float cy, float radius, int segments, const QVector3D & planetColor)
	drawOrbitingPlanets(mVertices, mColors);
	drawSolarPanel(mVertices, mColors);
}

void Solar_Panel_System::drawSun(floatList& mVertices, floatList& mColors, float cx, float cy, float radius, int segments, const Point3D& planetColor)
{
	for (int i = 0; i < segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		mVertices.push_back(cx + x);
		mVertices.push_back(cy + y);

		mColors.push_back(sunColor->x() / 255.0f);
		mColors.push_back(sunColor->y() / 255.0f);
		mColors.push_back(sunColor->z() / 255.0f);

		mVertices.push_back(cx);
		mVertices.push_back(cy);

		mColors.push_back(sunColor->x() / 255.0f);
		mColors.push_back(sunColor->y() / 255.0f);
		mColors.push_back(sunColor->z() / 255.0f);
	}
}

void Solar_Panel_System::drawOrbitingPlanets(floatList& mVertices, floatList& mColors)
{
	float theta = ((planetAngle)*(PI) / (180.0f));
	orbitX = 7.5f * cosf(theta);
	orbitY = -8.0 + 8.0f * sinf(theta);
	sunPosition.setX(orbitX);
	sunPosition.setY(orbitY);
	drawSun(mVertices, mColors, orbitX, orbitY, 1.0f, 600, Point3D(255.0f, 215.0f, 0.0f));
	planetAngle += mMultiplier * 0.28f;

	// Keep the angle within 360 degrees
	if (planetAngle >= 180.0f) {
		planetAngle -= 180.0f;
		orbitX = 0.0f;
		orbitX = -8.0f;
	}
}

void Solar_Panel_System::drawSolarPanel(floatList& mSolarVertices, floatList& mSolarColors)
{
	// Calculate the vector from the solar panel to the sun
	Point3D panelToSun(sunPosition.x() - panelPos->x(), sunPosition.y() - panelPos->y(), 0.0f);

	// Calculate the rotation angle to make the solar panel face the sun
	float rotationAngle = ((atan2(panelToSun.y(), panelToSun.x()))*(180.0f/PI));

	Point3D color = Point3D(0.25f, 0.25f, 0.25f);
	// Add vertices and colors for the solar panel with rotation
	addRotatedRectangle(mSolarVertices, mSolarColors, panelPos->x(), panelPos->y(), mPanelWidth, mPanelHeight, rotationAngle, color);

	mSolarVertices.push_back(basePos->x() - mBaseWidth / 2);
	mSolarVertices.push_back(basePos->y());

	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);

	mSolarVertices.push_back(basePos->x() + mBaseWidth / 2);
	mSolarVertices.push_back(basePos->y());

	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);

	mSolarVertices.push_back(basePos->x() + mBaseWidth / 2);
	mSolarVertices.push_back(basePos->y() + mBaseHeight);

	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);

	mSolarVertices.push_back(basePos->x() - mBaseWidth / 2);
	mSolarVertices.push_back(basePos->y() + mBaseHeight);

	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);
	mSolarColors.push_back(0.0f);

}

void Solar_Panel_System::addRotatedRectangle(floatList& mVertices, floatList& mColors, float centerX, float centerY, float width, float height, float rotationAngle, Point3D& color)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;

	// Define the vertices of the rectangle
	std::vector<Point3D> vertices =
	{
		Point3D(-halfWidth, -halfHeight, 0),
		Point3D(halfWidth, -halfHeight, 0),
		Point3D(halfWidth, halfHeight, 0),
		Point3D(-halfWidth, halfHeight, 0)
	};

	// Apply rotation to the vertices with an additional 90-degree offset
	float cosTheta = cos(rotationAngle + 90.0f);
	float sinTheta = sin(rotationAngle + 90.0f);

	for (auto& vertex : vertices)
	{
		float rotatedX = centerX + (vertex.x() * cosTheta - vertex.y() * sinTheta);
		float rotatedY = centerY + (vertex.x() * sinTheta + vertex.y() * cosTheta);

		mVertices.push_back(rotatedX);
		mVertices.push_back(rotatedY);

		mColors.push_back(color.x());
		mColors.push_back(color.y());
		mColors.push_back(color.z());
	}
}
Point3D Solar_Panel_System::rotatePoint(Point3D& point, float angleDegrees)
{
	float angleRadians = angleDegrees * PI / 180.0;
	float rotatedX = point.x() * cos(angleRadians) - point.y() * sin(angleRadians);
	float rotatedY = point.x() * sin(angleRadians) + point.y() * cos(angleRadians);
	return Point3D(rotatedX, rotatedY, 0.0f);
}

void Solar_Panel_System::rotateSolarPanel(floatList& mVertices, floatList& mColors)
{
	// Manually create the rotation matrix
	float rotationAngle = 90.0f;  // Your rotation angle
	for (auto& vertex : vertices)
	{
		Point3D rotatedVertex = rotatePoint(vertex, rotationAngle);

		mVertices.push_back(mSolarPanelCenter->x() + rotatedVertex.x());
		mVertices.push_back(mSolarPanelCenter->y() + rotatedVertex.y());

		mColors.push_back(mSolarPanelColor->x());
		mColors.push_back(mSolarPanelColor->y());
		mColors.push_back(mSolarPanelColor->z());
	}
}


void Solar_Panel_System::rotateSun(floatList& mVertices, floatList& mColors)
{
	float theta = (planetAngle) * (PI / 180.0f);
	orbitX = 7.5f * cosf(theta);
	orbitY = -8.0 + 8.0f * sinf(theta);
	sunPos->setX(orbitX);
	sunPos->setY(orbitY);
	planetAngle += mMultiplier * 0.28f;

	// Keep the angle within 360 degrees
	if (planetAngle >= 180.0f) {
		planetAngle -= 180.0f;
		orbitX = 0.0f;
		orbitX = -8.0f;
	}
}

void Solar_Panel_System::startRevolving()
{
	isRevolving = true;
}

void Solar_Panel_System::stopRevolving()
{
	isRevolving = false;
}

void Solar_Panel_System::setMultiplier(float value)
{
	mMultiplier = value;
}

void Solar_Panel_System::resetPositions()
{
	planetAngle = 0.0f;
}

void Solar_Panel_System::updatePositions(float minutes)
{
	planetAngle += (minutes / 1440) * 360.0f;
}
