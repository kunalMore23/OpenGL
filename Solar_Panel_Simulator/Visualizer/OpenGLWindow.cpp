#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QFile>

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) : mBackground(background), mMultiplier{ 1.0f }
{
	//initializeGL();
	mTimer = new QTimer(this);
	solar = new Solar_Panel_System();
	setParent(parent);
	setMinimumSize(500, 250);
	isRevolving = false;
	// Adjust the interval as needed

	const QStringList fileList = { "../vShader.glsl", "../fShader.glsl" };
	mShaderWatcher = new QFileSystemWatcher(fileList, this);
	connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
		QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

		rotationAngle = rotX * rotY * rotationAngle;
		update();
	}
	lastPos = event->pos();
}

void OpenGLWindow::startRendereing()
{
	connect(mTimer, &QTimer::timeout, this, &OpenGLWindow::updateSolarPanelData);
	mTimer->start(32);
}

void OpenGLWindow::stopRendereing()
{
	mTimer->stop();

}

OpenGLWindow::~OpenGLWindow()
{
	reset();
}

void OpenGLWindow::reset()
{
	makeCurrent();
	delete mProgram;
	mProgram = nullptr;
	doneCurrent();
	QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::updateData(std::vector<float>& vertices, std::vector<float>& colors)
{
	mVertices.clear();
	mColors.clear();
	mVertices = vertices;
	mColors = colors;
	update();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mProgram->bind();

	QMatrix4x4 matrix;
	//matrix.ortho(-6.0f * 1.475, 6.0f * 1.475, -6.0f * 1.475f, 6.0f * 1.475, 0.1f, 100.0f);
    matrix.ortho(-30.0f, 30.0f, -30.0f, 30.0f, 0.1f, 10.0f);
	mProgram->setUniformValue(m_zoomUniform, mMultiplier);
	matrix.translate(0, 0, -2);
	matrix.rotate(rotationAngle);

	mProgram->setUniformValue(m_matrixUniform, matrix);

	mVerticesData = mVertices.data();
	mColorsData = mColors.data();

	int size = mVertices.size();

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, mVerticesData);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColorsData);

	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);

	glDrawArrays(GL_LINES, 0, size / 2);

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);

	mProgram->release();
}

void OpenGLWindow::updateSolarPanelData()
{
	mVertices.clear();
	mColors.clear();
	solar->showSolarPanelSystem(mVertices, mColors);
	update();
}

void OpenGLWindow::startRevolving()
{
	mTimer->start(32);
}

void OpenGLWindow::stopRevolving()
{
	mTimer->stop();
}

void OpenGLWindow::setMultiplier(float value)
{
	mMultiplier = value;
}

void OpenGLWindow::resetPositions()
{
	updateSolarPanelData();
}

void OpenGLWindow::updatePositions(float minutes)
{
	updateSolarPanelData();
}

void OpenGLWindow::shaderWatcher()
{
	QString vertexShaderSource = fetchShader("../vShader.glsl");
	QString fragmentShaderSource = fetchShader("../fShader.glsl");

	mProgram->release();
	mProgram->removeAllShaders();

	mProgram = new QOpenGLShaderProgram(this);

	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

	mProgram->link();
}

void OpenGLWindow::initializeGL()
{
	QString vertexShaderSource = fetchShader("../vShader.glsl");
	QString fragmentShaderSource = fetchShader("../fShader.glsl");
	
	initializeOpenGLFunctions();

	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

	mProgram->link();

	m_posAttr = mProgram->attributeLocation("posAttr");
	m_colAttr = mProgram->attributeLocation("colAttr");
	m_matrixUniform = mProgram->uniformLocation("matrix");
	m_zoomUniform = mProgram->uniformLocation("zoom");

	if (m_posAttr == -1 || m_colAttr == -1 || m_matrixUniform == -1)
	{
		qDebug() << "Shader attribute or uniform location error.";
		// Handle the error appropriately, e.g., return or throw an exception
	}

	glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
}

QString OpenGLWindow::fetchShader(QString fileName)
{
	QFile* file = new QFile(fileName);

	if (!file->open(QFile::ReadOnly | QFile::Text))
	{
		std::cerr << "Invalid File !";
		return "Invalid File !";
	}
	QTextStream stream(file);
	QString fileString = stream.readLine();

	while (!stream.atEnd())
	{
		fileString.append(stream.readLine());
	}
	file->close();
	delete file;
	return fileString;
}
