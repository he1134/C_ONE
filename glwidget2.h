#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
//#include <QtOpenGL>
//#include <QColor>
//#include <QGLPixelBuffer>
#include "skeleton.h"
#include "motion.h"
#include "skeleton.h"
#include "motion.h"
//#include "display.h"
#include "transform.h"
#include "types.h"
typedef struct _MouseT {
  int button;
  int x;
  int y;
} MouseT;


typedef struct _CameraT {
  double zoom;
  double tw;
  double el;
  double az;
  double tx;
  double ty;
  double tz;
  double atx;
  double aty;
  double atz;
} CameraT;


/***************  Types *********************/
enum {OFF, ON};

//static GLWidget displayer;		

static Skeleton *pActor = NULL;			// Actor info as read from ASF file
static bool bActorExist = false;		// Set to true if actor exists

static Motion *pSampledMotion = NULL;	// Motion information as read from AMC file
static Motion *pInterpMotion = NULL;	// Interpolated Motion 

//static GLWidget *displayer;
static int nFrameNum, nFrameInc=1;		// Current frame and frame increment


//static MouseT mouse;					// Keeping track of mouse input 
static CameraT camera;					// Structure about camera setting 

static int Play=OFF, Rewind=OFF;		// Some Flags for player
static int Repeat=OFF;

#ifdef WRITE_JPEGS
static int Record=OFF; 
static char *Record_filename;			// Recording file name 
#endif

static int PlayInterpMotion=ON;			// Flag which desides which motion to play (pSampledMotion or pInterpMotion)	

static int Background=ON, Light=OFF;	// Flags indicating if the object exists    

static int recmode = 0;
static int piccount=0;
static char * argv2;
static int maxFrames=0;
static int showed = 0;

//! [0]
class Helper;
QT_BEGIN_NAMESPACE
class QPaintEvent;
class QWidget;
QT_END_NAMESPACE

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
	GLWidget(QWidget *parent);
    GLWidget(Helper *helper, QWidget *parent);
	QSize minimumSizeHint() const;
     QSize sizeHint() const;
	//set actor for display
	void loadActor(Skeleton *pActor);
		//set motion for display
	void loadMotion(Motion *pMotion);
	void normalizeAngle(int *angle);
	void rotateBy(int xAngle, int yAngle, int zAngle);
    void setPlayOn();
	void setPause();
	void setRepeat();
	void setRewind();
	void redraw();
	void gl_init();
	void light_init();
	void draw_ground();
	void cameraView(void);
	void draw_triad();
	void redisplay();
	//Draw a particular bone
	void drawBone(Bone *ptr,int skelNum);
	//Draw the skeleton hierarchy
	void traverse(Bone *ptr,int skelNum);
	void set_display_list(Bone *bone, GLuint *pBoneList);
	
	void play();
    void repeat();
    void rewind();
	void pause();
//	QSize sizeHint() const;
	void timerEvent(QTimerEvent *);
      
		//display the scene (actor, ground plane ....)
	void show();
	void load_Actor();
	void load_Motion();
	//void setSliderValue(int newValue);
	//void setMaximum(int newValue);
	void draw_vector(float *a, float *b);
	void draw_bone_axis();
   // static void draw_bone_axis();

public slots:
	void animate();
     void setXRotation(int angle);
     void setYRotation(int angle);
     void setZRotation(int angle);
	 void setMaximum(int newValue);
	 void updateValue(int newValue);
	 void setSliderValue(int newValue);
/*
signals:
     void xRotationChanged(int angle);
     void yRotationChanged(int angle);
     void zRotationChanged(int angle);
*/
     signals:
	 void sliderValueChanged(int newValue);
	 void setMaximumValue(int newValue);
protected:
    void paintEvent(QPaintEvent *event);
	void initializeGL();
	void paintGL();
     void resizeGL(int width, int height);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
	 void setupViewport(int width, int height);



	
	void locate();
	void sub(QString &a);
	void txCall();
	void tyCall();
	void tzCall();
	void rxCall();
	void ryCall();
	void rzCall();
    void dtCall();
	void exitCall();
	void valueIn(); 
	void sliderCall(int val);
	

public:
		int m_SpotJoint;		//joint whose local coordinate system is drawn
		int numActors;
		Skeleton *m_pActor[MAX_SKELS];		//pointer to current actor
		Motion *m_pMotion[MAX_SKELS];		//pointer to current motion	

private:
    Helper *helper;
	QColor trolltechGreen;
  QColor trolltechPurple;
    int elapsed;
	unsigned int m_BoneList[MAX_SKELS];		//display list with bones
	int xRot;
     int yRot;
     int zRot;
	 int mySliderValue;
     QPoint lastPos;
	CameraT camera;
	int Light;
	int Background;
	int playC;
	int rewindC;
	int repeatC;
	int pauseC;
	int PlayInterpMotionC;

};
//! [0]

#endif
