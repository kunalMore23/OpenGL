#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Bezier.h"
#include "BSpline3D.h"
#include "Hermite.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <iostream>   

Visualizer::Visualizer(QWidget* parent)
	: QMainWindow(parent)
{
	setupUi();

	// Connect signals to slots
	connect(mStartButton, &QPushButton::clicked, this, &Visualizer::startBtn);
	connect(mStopButton, &QPushButton::clicked, this, &Visualizer::stopBtn);
	connect(mResetButton, &QPushButton::clicked, this, &Visualizer::resetBtn);
	connect(mUpdateButton, &QPushButton::clicked, this, &Visualizer::updateBtn);
	connect(mZoomSlider, &QSlider::valueChanged, this, &Visualizer::zoomSliderChanged);
	connect(mTabWidget, &QTabWidget::currentChanged, this, &Visualizer::onTabChanged); 
	connect(mDrawBezierBtn, &QPushButton::clicked, this, &Visualizer::drawCurveUsingBezier);
	connect(mDrawBezierBtn, &QPushButton::clicked, this, &Visualizer::drawCurveUsingHermite);
	connect(mDrawBezierBtn, &QPushButton::clicked, this, &Visualizer::drawCurveUsingBSpline);
	connect(mClearBtn, &QPushButton::clicked, this, &Visualizer::clearWindow);
}

Visualizer::~Visualizer()
{
}

void Visualizer::setupUi()
{
	resize(720, 700);
	mWidget = new QWidget(this);

	mTabWidget = new QTabWidget(this);

	// Create layouts
	mBaseLayout = new QGridLayout(mWidget);
	mButtonsLayout = new QHBoxLayout(mWidget);
	mVbuttonsLayout = new QVBoxLayout(mWidget);

	mInputButtonsLayout = new QHBoxLayout();
	mVTab2ButtonsLayout = new QVBoxLayout();

	mVPoint1Layout = new QVBoxLayout();
	mVPoint2Layout = new QVBoxLayout();
	mVPoint3Layout = new QVBoxLayout();
	mVPoint4Layout = new QVBoxLayout();

	mPoint1 = new QLabel(this);
	mPoint2 = new QLabel(this);
	mPoint3 = new QLabel(this);
	mPoint4 = new QLabel(this);

	mX1Input = new QLineEdit(mWidget);
	mY1Input = new QLineEdit(mWidget);
	mZ1Input = new QLineEdit(mWidget);

	mX2Input = new QLineEdit(mWidget);
	mY2Input = new QLineEdit(mWidget);
	mZ2Input = new QLineEdit(mWidget);

	mX3Input = new QLineEdit(mWidget);
	mY3Input = new QLineEdit(mWidget);
	mZ3Input = new QLineEdit(mWidget);

	mX4Input = new QLineEdit(mWidget);
	mY4Input = new QLineEdit(mWidget);
	mZ4Input = new QLineEdit(mWidget);

	mDrawBezierBtn = new QPushButton("DrawBezier", mWidget);
	mDrawHermiteButton = new QPushButton("Draw Hermite", mWidget);
	mDrawBSplineButton = new QPushButton("Draw BSpline", mWidget);
	mClearBtn = new QPushButton("Clear", mWidget);

	QWidget* solarSystemTab = new QWidget(mTabWidget);
	QWidget* bezierTab = new QWidget(mTabWidget);
	//QWidget* hermiteTab = new QWidget(mTabWidget);
	//QWidget* bSplineTab = new QWidget(mTabWidget);

	mZoomSlider = new QSlider(Qt::Horizontal, mWidget);

	// Create buttons and input elements
	mStartButton = new QPushButton("Start", mWidget);
	mStopButton = new QPushButton("Stop", mWidget);
	mResetButton = new QPushButton("Reset", mWidget);
	mUpdateButton = new QPushButton("Update", mWidget);
	mTimeInput = new QLineEdit(mWidget);

	// Create OpenGL windows for rendering
	mRenderer = new OpenGLWindow(QColor(135.0f, 206.0f, 250.0f), mWidget);
	mBezierRenderer = new OpenGLWindow(QColor(0.0f, 0.0f, 0.0f), mWidget);
	mHermiteRenderer = new OpenGLWindow(QColor(255.0f, 255.0f, 255.0f), mWidget);
	mBSpline3DRenderer = new OpenGLWindow(QColor(255.0f, 255.0f, 255.0f), mWidget);

	// Create tab widget

	mTabWidget->setFixedSize(720, 700);

	//----------
	mVTab2ButtonsLayout->addWidget(mDrawBezierBtn);
	mVTab2ButtonsLayout->addWidget(mDrawBSplineButton);
	mVTab2ButtonsLayout->addWidget(mDrawHermiteButton);
	mVTab2ButtonsLayout->addWidget(mClearBtn);

	mPoint1->setText("Point1");
	mVPoint1Layout->addWidget(mPoint1, 0, Qt::AlignHCenter);
	//mX1Input->setB
	mX1Input->setPlaceholderText("Enter X Coordinate");
	mVPoint1Layout->addWidget(mX1Input);
	mY1Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint1Layout->addWidget(mY1Input);
	mZ1Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint1Layout->addWidget(mZ1Input);


	mPoint2->setText("Point2");
	mVPoint2Layout->addWidget(mPoint2, 0, Qt::AlignHCenter);
	mX2Input->setPlaceholderText("Enter X Coordinate");
	mVPoint2Layout->addWidget(mX2Input);
	mY2Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint2Layout->addWidget(mY2Input);
	mZ2Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint2Layout->addWidget(mZ2Input);


	mPoint3->setText("Point3");
	mVPoint3Layout->addWidget(mPoint3, 0, Qt::AlignHCenter);
	mX3Input->setPlaceholderText("Enter X Coordinate");
	mVPoint3Layout->addWidget(mX3Input);
	mY3Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint3Layout->addWidget(mY3Input);
	mZ3Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint3Layout->addWidget(mZ3Input);


	mPoint4->setText("Point4");
	mVPoint4Layout->addWidget(mPoint4, 0, Qt::AlignHCenter);
	mX4Input->setPlaceholderText("Enter X Coordinate");
	mVPoint4Layout->addWidget(mX4Input);
	mY4Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint4Layout->addWidget(mY4Input);
	mZ4Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint4Layout->addWidget(mZ4Input);


	mInputButtonsLayout->addLayout(mVTab2ButtonsLayout);
	mInputButtonsLayout->addLayout(mVPoint1Layout);
	mInputButtonsLayout->addLayout(mVPoint2Layout);
	mInputButtonsLayout->addLayout(mVPoint3Layout);
	mInputButtonsLayout->addLayout(mVPoint4Layout);

	mInputButtonsLayout->setAlignment(Qt::AlignTop);
	//-----------
	// Create tabs


	// Set up Solar System tab
	QVBoxLayout* solarSystemLayout = new QVBoxLayout();
	solarSystemLayout->addLayout(mButtonsLayout);
	solarSystemLayout->addWidget(mRenderer, 1);
	solarSystemLayout->addWidget(mZoomSlider);
	solarSystemTab->setLayout(solarSystemLayout);

	QVBoxLayout* bezierLayout = new QVBoxLayout();
	bezierLayout->addLayout(mInputButtonsLayout);
	bezierLayout->addWidget(mBezierRenderer,1);
	bezierTab->setLayout(bezierLayout);

	// Set up Hermite tab
	QVBoxLayout* hermiteLayout = new QVBoxLayout();
	hermiteLayout->addWidget(mHermiteRenderer);
	//hermiteTab->setLayout(hermiteLayout);

	// Set up bSpline tab
	QVBoxLayout* bSplineLayout = new QVBoxLayout();
	bSplineLayout->addWidget(mBSpline3DRenderer);
	//bSplineTab->setLayout(bSplineLayout);

	// Add tabs to the QTabWidget
	mTabWidget->addTab(solarSystemTab, "Solar System Simulator");
	mTabWidget->addTab(bezierTab, "Curves");
	//mTabWidget->addTab(hermiteTab, "Hermite");
	//mTabWidget->addTab(bSplineTab, "bSpline");


	mTimeInput->setPlaceholderText("Enter Minutes");

	// Set central widget
	setCentralWidget(mWidget);

	// Set fixed button widths
	mStartButton->setFixedWidth(140);
	mButtonsLayout->addWidget(mStartButton);
	mStopButton->setFixedWidth(140);
	mButtonsLayout->addWidget(mStopButton);
	mResetButton->setFixedWidth(140);
	mButtonsLayout->addWidget(mResetButton);
	mUpdateButton->setFixedWidth(140);
	mButtonsLayout->addWidget(mUpdateButton);
	mTimeInput->setFixedWidth(140);
	mButtonsLayout->addWidget(mTimeInput);

	// Set up the zoom slider
	mZoomSlider->setRange(0, 100);
	mZoomSlider->setValue(50);
	mVbuttonsLayout->addWidget(mTabWidget);
	mBaseLayout->addLayout(mVbuttonsLayout, 0, 0);
	setWindowTitle(QCoreApplication::translate("Solar Panel Simulator", "Solar Panel Simulator", nullptr));
}


void Visualizer::drawCurveUsingBezier()
{
	mVertices.clear();
	mColors.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	mVertices.push_back(xCoordinate);
	mVertices.push_back(yCoordinate);
	mVertices.push_back(zCoordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	Bezier bezier(p0, p1, p2, p3);
	bezier.drawCurve(p0, p1, p2, p3, mVertices, mColors);

	mVertices.push_back(x3Coordinate);
	mVertices.push_back(y3Coordinate);
	mVertices.push_back(z3Coordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	mBezierRenderer->updateData(mVertices, mColors);
	mVertices.clear();
	mColors.clear();
}

void Visualizer::drawCurveUsingHermite()
{
	mVertices.clear();
	mColors.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	mVertices.push_back(xCoordinate);
	mVertices.push_back(yCoordinate);
	mVertices.push_back(zCoordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	Hermite Hermite(p0, p1, p2, p3);
	Hermite.drawCurve(p0, p1, p2, p3, mVertices, mColors);

	mVertices.push_back(x3Coordinate);
	mVertices.push_back(y3Coordinate);
	mVertices.push_back(z3Coordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	mBezierRenderer->updateData(mVertices, mColors);
	mVertices.clear();
	mColors.clear();
}

void Visualizer::drawCurveUsingBSpline()
{
	mVertices.clear();
	mColors.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	mVertices.push_back(xCoordinate);
	mVertices.push_back(yCoordinate);
	mVertices.push_back(zCoordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	BSpline3D BSpline3D(p0, p1, p2, p3);
	BSpline3D.drawCurveBspline(mVertices, mColors);

	mVertices.push_back(x3Coordinate);
	mVertices.push_back(y3Coordinate);
	mVertices.push_back(z3Coordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	mBezierRenderer->updateData(mVertices, mColors);
	mVertices.clear();
	mColors.clear();
}

void Visualizer::onTabChanged(int tabIndex)
{
	// Show/hide the QSlider based on the selected tab
	if (tabIndex == 0)  // Solar System Simulator tab
	{
		mRenderer->startRendereing();
		mZoomSlider->show();
	}
	else if (tabIndex == 1)
	{
		mRenderer->stopRendereing();
		mRenderer->resetPositions();
		mZoomSlider->hide();
	}
	else
	{
		// Handle other tabs if needed
	}
}

void Visualizer::zoomSliderChanged(float value)
{
	// Adjust the zoom factor based on the slider value
	float zoomFactor = 0.5f + (value / 25.0f) * 1.5f;
	mRenderer->setMultiplier(zoomFactor);
}

void Visualizer::startBtn()
{
	// Start revolving animation
	mRenderer->startRevolving();
}

void Visualizer::stopBtn()
{
	// Stop revolving animation
	mRenderer->stopRevolving();
}

void Visualizer::resetBtn()
{
	// Reset object positions
	mRenderer->resetPositions();
}

void Visualizer::updateBtn()
{
	// Update positions based on user input
	bool ok;
	float numberOfDays = mTimeInput->text().toFloat(&ok);

	if (ok)
	{
		mRenderer->updatePositions(numberOfDays);
	}
}

void Visualizer::clearWindow()
{
	mVertices.clear();
	mColors.clear();
	mBezierRenderer->updateData(mVertices, mColors);
}