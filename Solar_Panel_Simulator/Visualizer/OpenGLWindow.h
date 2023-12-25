#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <cmath>
#include <string>
#include "Solar_Panel_System.h"
#include "BSpline3D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

namespace Solar_Panel_Simulator
{
	class OpenGLWindow;
}

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	OpenGLWindow(const QColor& background, QWidget* parent);
	~OpenGLWindow();

	void startRendereing();
	void stopRendereing();
	void setMultiplier(float value);
	void startRevolving();
	void stopRevolving();
	void resetPositions();
	void updatePositions(float minutes);

	void updateSolarPanelData();
	void updateData(std::vector<float>& vertices, std::vector<float>& colors);

	void mouseMoveEvent(QMouseEvent* event);

protected:
	void paintGL() override;
	void initializeGL() override;

	QString fetchShader(QString fileName);

private slots:
	void shaderWatcher();
	
private:
	void reset();

private:
	QQuaternion rotationAngle;   //rotation properties
	QPoint lastPos;

private:
	GLfloat mMultiplier;
	bool isRevolving;
	GLint m_zoomUniform;

	floatList mVertices;
	floatList mColors;

	float* mVerticesData;
	float* mColorsData;

	double mZoomFactor;
	QOpenGLShaderProgram* mProgram = nullptr;
	QColor mBackground;
	QMetaObject::Connection mContextWatchConnection;
	QTimer* mTimer;
	Solar_Panel_System* solar;

	GLint m_posAttr = 0;
	GLint m_colAttr = 0;
	GLint m_matrixUniform = 0;

	QFileSystemWatcher* mShaderWatcher;
};
