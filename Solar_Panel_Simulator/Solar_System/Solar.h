#include "Point3D.h"
#include <vector>

#include "pch.h"

using floatList = std::vector<float>;

class SOLARSYSTEM_API Solar
{
public:
    Solar();
    ~Solar();

    void showSolarPanelSystem(floatList& mVertices, floatList& mColors, floatList& mSolarVertices, floatList& mSolarColors);

    void drawSun(floatList& mVertices, floatList& mColors);
    void drawSolarPanel(floatList& mSolarVertices, floatList& mSolarColors);

    void setMultiplier(float value);
    void startRevolving();
    void stopRevolving();
    void resetPositions();
    void updatePositions(float minutes);


private:
    Point3D rotatePoint(Point3D& point, float angleDegrees);
    void rotateSun(floatList& vertices, floatList& colors);
    void rotateSolarPanel(floatList& mVertices, floatList& mColors);

private:
    Point3D* sunColor = new Point3D(255.0f, 215.0f, 0.0f);
    float mMultiplier;
    float planetAngle = 0.0f;
    float orbitX;
    float orbitY;
    bool isRevolving;

    Point3D* sunPos = new Point3D(7.5f, 0.0f, 0.0f);;
    float sRadius = 1.0f;
    int sSegments = 600;

    // solar panel properties
    Point3D* mSolarPanelCenter = new Point3D(0.0f, -7.45f, 0.0f);
    Point3D* mSolarPanelColor = new Point3D(0.25f, 0.25f, 0.25f);
    float mPanelHeight = 2.4f;
    float mPanelWidth = 0.1f;
    Point3D* panelPos = new Point3D(0.0f, 7.45f, 0.0f);

    float halfWidth = mPanelWidth / 2;
    float halfHeight = mPanelHeight / 2;

    // Define the vertices of the rectangle
    std::vector<Point3D> vertices =
    {
        Point3D(-halfWidth, -halfHeight, 0),
        Point3D(halfWidth, -halfHeight, 0),
        Point3D(halfWidth, halfHeight, 0),
        Point3D(-halfWidth, halfHeight, 0)
    };

    //properties of base of solar panel
    Point3D* basePos = new Point3D(0.0f, -8.0f, 0.0f);
    float mBaseHeight = 0.5f;
    float mBaseWidth = 0.05f;
    float rotationAngle = 0.0f;
};