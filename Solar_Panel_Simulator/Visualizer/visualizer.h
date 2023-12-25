#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTimer>
#include "BSpline3D.h"

class OpenGLWindow;

class Visualizer : public QMainWindow
{
	Q_OBJECT

public:
	Visualizer(QWidget* parent = nullptr);
	~Visualizer();

private:
	void setupUi();
	void onTabChanged(int tabIndex);

	void drawCurveUsingBezier();
	void drawCurveUsingHermite();
	void drawCurveUsingBSpline();
	void clearWindow();

private slots:
	void startBtn();
	void stopBtn();
	void resetBtn();
	void updateBtn();
	void zoomSliderChanged(float value);

private:
	QGridLayout* mBaseLayout;

	QVBoxLayout* mVbuttonsLayout;
	QVBoxLayout* mV1inputLayout;
	QVBoxLayout* mV2inputLayout;
	QVBoxLayout* mV3inputLayout;
	QVBoxLayout* mV4inputLayout;
	QVBoxLayout* mV5inputLayout;

	QHBoxLayout* mButtonsLayout;
	QHBoxLayout* mInputBoxLayout;

	QPushButton* mStartButton;
	QPushButton* mStopButton;
	QPushButton* mResetButton;
	QPushButton* mUpdateButton;

	QWidget* mWidget;
	QWidget* mCentralWidget;

	QLineEdit* mTimeInput;
	QTimer* mTimer;
	QSlider* mZoomSlider;
	QTabWidget* mTabWidget;

	OpenGLWindow* mRenderer;
	OpenGLWindow* mBezierRenderer;
	OpenGLWindow* mHermiteRenderer;
	OpenGLWindow* mBSpline3DRenderer;

	//tabs
	QHBoxLayout* mInputButtonsLayout;
	QVBoxLayout* mVTab2ButtonsLayout;
	QPushButton* mDrawBezierBtn;
	QPushButton* mClearBtn;
	QPushButton* mDrawHermiteButton;
	QPushButton* mDrawBSplineButton;

	QVBoxLayout* mVPoint1Layout;
	QLabel* mPoint1;
	QLineEdit* mX1Input;
	QLineEdit* mY1Input;
	QLineEdit* mZ1Input;

	QVBoxLayout*	mVPoint2Layout;
	QLabel*			mPoint2;
	QLineEdit*		mX2Input;
	QLineEdit*		mY2Input;
	QLineEdit*		mZ2Input;

	QVBoxLayout*	mVPoint3Layout;
	QLabel*			mPoint3;
	QLineEdit*		mX3Input;
	QLineEdit*		mY3Input;
	QLineEdit*		mZ3Input;

	QVBoxLayout* mVPoint4Layout;
	QLabel* mPoint4;
	QLineEdit* mX4Input;
	QLineEdit* mY4Input;
	QLineEdit* mZ4Input;

	//drawCurve 
	float xCoordinate;
	float yCoordinate;
	float zCoordinate;
	float x1Coordinate;
	float y1Coordinate;
	float z1Coordinate;
	float x2Coordinate;
	float y2Coordinate;
	float z2Coordinate;
	float x3Coordinate;
	float y3Coordinate;
	float z3Coordinate;

	QLineEdit* mLineEdit;
	QLineEdit* mLineEdit2;
	QLineEdit* mLineEdit3;
	QLineEdit* mLineEdit4;
	QLineEdit* mLineEdit5;
	QLineEdit* mLineEdit6;
	QLineEdit* mLineEdit7;
	QLineEdit* mLineEdit8;
	QLineEdit* mLineEdit9;
	QLineEdit* mLineEdit10;
	QLineEdit* mLineEdit11;
	QLineEdit* mLineEdit12;

	QLineEdit* mLineEdit13;
	QLineEdit* mLineEdit14;
	QLineEdit* mLineEdit15;
	QLineEdit* mLineEdit16;
	QLineEdit* mLineEdit17;
	QLineEdit* mLineEdit18;
	QLineEdit* mLineEdit19;
	QLineEdit* mLineEdit20;
	QLineEdit* mLineEdit21;
	QLineEdit* mLineEdit22;
	QLineEdit* mLineEdit23;
	QLineEdit* mLineEdit24;

	std::vector<float> mVertices;
	std::vector<float> mColors;
	
	std::vector<float> mVerticess;
	std::vector<float> mColorss;
};