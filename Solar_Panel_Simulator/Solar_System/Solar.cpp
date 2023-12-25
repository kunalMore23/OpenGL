#include "pch.h"
#include "Solar.h"
#include <cmath>
#define PI 3.14159265359f

Solar::Solar()
{
	isRevolving = false;
	mMultiplier = 1.0f;
	orbitX = 0.0f;
	orbitY = -8.0f;
}

Solar::~Solar()
{
}

void Solar::showSolarPanelSystem(floatList& mVertices, floatList& mColors, floatList& mSolarVertices, floatList& mSolarColors)
{
	drawSun(mVertices, mColors);
	drawSolarPanel(mSolarVertices, mSolarColors);
}

void Solar::drawSun(floatList& mVertices, floatList& mColors)
{
	float cx = sunPos->x();
	float cy = sunPos->y();

	for (int i = 0; i < sSegments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(sSegments);
		float x = sRadius * cosf(theta);
		float y = sRadius * sinf(theta);

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
	if (isRevolving)
	{
		rotateSun(mVertices, mColors);
	}
}

void Solar::drawSolarPanel(floatList& mSolarVertices, floatList& mSolarColors)
{
	for (auto& vertex : vertices)
	{
		mSolarVertices.push_back(mSolarPanelCenter->x() + vertex.x());
		mSolarVertices.push_back(mSolarPanelCenter->y() + vertex.y());
		
		mSolarColors.push_back(mSolarPanelColor->x());
		mSolarColors.push_back(mSolarPanelColor->y());
		mSolarColors.push_back(mSolarPanelColor->z());

		vertex.setX(mSolarPanelCenter->x() + vertex.x());
		vertex.setY(mSolarPanelCenter->y() + vertex.y());
	}

	// Add vertices and colors for the supporting column
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

	if (isRevolving)
	{
		// Calculate the vector from the solar panel to the sun
		Point3D panelToSun(sunPos->x() - panelPos->x(), sunPos->y() - panelPos->y(), 0.0f);

		// Calculate the rotation angle to make the solar panel face the sun
		rotationAngle = std::atan2(panelToSun.y(), panelToSun.x()) * (180/PI);

		// Add vertices and colors for the solar panel with rotation
		rotateSolarPanel(mSolarVertices, mSolarColors);
	}

}

Point3D Solar::rotatePoint(Point3D& point, float angleDegrees) {
	float angleRadians = angleDegrees * PI / 180.0;
	float rotatedX = point.x() * cos(angleRadians) - point.y() * sin(angleRadians);
	float rotatedY = point.x() * sin(angleRadians) + point.y() * cos(angleRadians);
	return Point3D(rotatedX, rotatedY, 0.0f);
}

void Solar::rotateSolarPanel(floatList& mVertices, floatList& mColors)
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

void Solar::rotateSun(floatList& mVertices, floatList& mColors)
{
	float theta = (planetAngle)* (PI/180.0f);
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

void Solar::startRevolving()
{
	isRevolving = true;
}

void Solar::stopRevolving()
{
	isRevolving = false;
}

void Solar::setMultiplier(float value)
{
	mMultiplier = value;
}

void Solar::resetPositions()
{
	planetAngle = 0.0f;
}

void Solar::updatePositions(float minutes)
{
	planetAngle += (minutes / 1440) * 360.0f;
}
