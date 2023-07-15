
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include <QSlider>
#include "helper.h"
#include <qpushbutton.h>
#ifdef WRITE_JPEGS
#include "pic.h"				// for saving jpeg pictures.  
#endif

#include "transform.h"			// utility functions for vector and matrix transformation  
//#include "display.h"   
#include "interpolator.h"
#include "glwidget2.h"
#include "video_texture.h"


QT_BEGIN_NAMESPACE
class QLabel;
class QWidget;
QT_END_NAMESPACE



//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
	//void gl_init();
	//void light_init();
	int getSliderValue();
public slots:
	void load_Actor();
	void  setSliderValue(int value);
	void setMax(int a);
	void load_Motion();
	void play();
    void repeat();
    void rewind();
	void pause();
	void locate();
	void sub(QString &a);
	void txCall();
	void tyCall();
	void tzCall();
	void rxCall();
	void ryCall();
	void rzCall();
    void dtCall();
	void callBackground();
	void exitCall();
	void valueIn();
	void sliderCall(int val); 

private:
    Helper helper;
	int subValue;
	GLWidget *displayer;
	 QLabel *nativeLabel;
    QLabel *openGLLabel;
   
	QPushButton *loadSkeletonButton;
	QPushButton *loadMotionButton;
	QPushButton *locateButton ;
	QPushButton *interpolateButton;
	QPushButton *exitButton;
	QPushButton *lightButton;
	QPushButton *backgroundButton;

	QPushButton *rewindButton;
	QPushButton *playButton;
    QPushButton *pauseButton;
	QPushButton *repeatButton;
	QSlider *slider ;
	QLabel   *sliderLabel;
	QLabel *labelJoint ;
	QLineEdit *jointEdit;
	QLabel *frameLabel;
	QLineEdit *frameEdit;
	QLabel *subLabel;
	QLineEdit *subEdit;
	QLabel *dtLabel;
	QLineEdit *dtEdit;
	QLabel *txLabel;
	QLineEdit *txEdit;
	QLabel *tyLabel;
	QLineEdit *tyEdit;
	QLabel *tzLabel;
	QLineEdit *tzEdit;
	QLabel *rxLabel;
	QLineEdit *rxEdit;
    QLabel *ryLabel;
	QLineEdit *ryEdit;
	QLabel *rzLabel;
	QLineEdit *rzEdit; 
};
//! [0]

#endif
