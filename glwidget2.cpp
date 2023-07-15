
#include <QtGui>
#include <QtOpenGL>
 #include <math.h>
#include "glwidget2.h"
#include "helper.h"

//! [0]
//extern void redisplay();
GLWidget::GLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	elapsed = 0;
    setFixedSize(300, 300);
   // setAutoFillBackground(false);
	 trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
	m_SpotJoint = -1;
	numActors = 0;
	mySliderValue=0;
	//setAttribute(Qt::WA_PaintOnScreen);
   // setAttribute(Qt::WA_NoSystemBackground);
	m_pActor[0] = NULL;
	m_pMotion[0] = NULL;
	Light=0;
	Background=1;
	playC=OFF;
	rewindC=OFF;
	repeatC=OFF;
	pauseC=ON;
	PlayInterpMotionC=ON;
	//gl_init();
	//light_init();
 /* trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
	initializeGL();
	 qglColor(Qt::black);
     renderText(-0.35, 0.4, 0.0, "Multisampling enabled");
     renderText(0.15, 0.4, 0.0, "Multisampling disabled"); */
	//glDraw();
	//light_init();
}
GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(640, 480);
   // setAutoFillBackground(true);
	//setAttribute(Qt::WA_PaintOnScreen);
   // setAttribute(Qt::WA_NoSystemBackground);
	//setAutoBufferSwap(false);
	 trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
	m_SpotJoint = -1;
	numActors = 0;
	m_pActor[0] = NULL;
	m_pMotion[0] = NULL;
	//gl_init();
	Light=0;
	Background=1;
	playC=OFF;
	rewindC=OFF;
	repeatC=OFF;
	pauseC=ON;
	PlayInterpMotionC=ON;
	//gl_init();
	//light_init();
	/*initializeGL();
	 qglColor(Qt::black);
     renderText(-0.35, 0.4, 0.0, "Multisampling enabled");
     renderText(0.15, 0.4, 0.0, "Multisampling disabled"); */
	//glDraw();
	//light_init();
}

void GLWidget::setSliderValue(int newValue)
{
    if (newValue != mySliderValue) {
        mySliderValue = newValue;
        emit sliderValueChanged(newValue);
    }
}
void GLWidget::updateValue(int newValue)
{
    mySliderValue = newValue;
}
void GLWidget::setMaximum(int newValue)
{
  emit setMaximumValue(newValue);
	//emit valueChanged(newValue);

}

void GLWidget::animate()
{
    if(playC==ON) 
		play();
	if (rewindC==ON)
		rewind();
	updateGL();
    //elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    //repaint();
}
void GLWidget::setXRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != xRot) {
         xRot = angle;
         //emit xRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setYRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != yRot) {
         yRot = angle;
        // emit yRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setZRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != zRot) {
         zRot = angle;
        // emit zRotationChanged(angle);
         updateGL();
     }
 }

void GLWidget::paintGL()
 {
	// redisplay();
	 
	  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 
	///////////////////////// glLoadIdentity();
	/////////////////////// glTranslated(0.0, 0.0, -10.0); 
    //  glLoadIdentity();
    // glTranslated(0.0, 0.0, -10.0); 
 /*  glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotated(yRot / 16.0, 0.0, 1.0, 0.0); 
     glRotated(zRot / 16.0, 0.0, 0.0, 1.0);   */
	// makeCurrent();
     show();
	 
	 redisplay();
	// show();
    // glCallList(object); 
	// draw_ground();
	// draw_triad();
   // redisplay();
	/* QPainter painter;
    painter.begin(this);
	 qglColor(Qt::black);
     renderText(-0.35, 0.4, 0.0, "Multisampling enabled");
     renderText(0.15, 0.4, 0.0, "Multisampling disabled");
	 painter.setPen(Qt::white);

	 painter.drawText(20, 40, "This is a test fps");
	 painter.end();
	 */
 }
 
void GLWidget::resizeGL(int width, int height)
 {
     int side = qMin(width, height);
 //    glViewport((width - side) / 2, (height - side) / 2, side, side);
    
	 struct {GLint x, y, width, height;} viewport;
  /*   glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	   gluPerspective( 45.,
	 (double) width/height,
	 .1,  50.); */
	//  	 glViewport(640, 480, 480, 480);
	   
    int red_bits, green_bits, blue_bits;
	
    glGetIntegerv(GL_RED_BITS, &red_bits);
    glGetIntegerv(GL_GREEN_BITS, &green_bits);
    glGetIntegerv(GL_BLUE_BITS, &blue_bits);
    //glGetIntegerv(GL_VIEWPORT, &viewport.x);
   // printf("OpenGL window has %d bits red, %d green, %d blue; viewport is %dx%d\n",
	//red_bits, green_bits, blue_bits, viewport.width, viewport.height);
    setupViewport(width, width);
  
	/////////////////////////ooooooosetupViewport(width, height);
  /*  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.,
	  (double) width/heigth,
    .1,  100.);  
	glMatrixMode(GL_MODELVIEW); */
  /*   glLoadIdentity();
     float aspect = width/(float)(height ? height : 1);
     glFrustum(-aspect, aspect, -1, 1, 10, 100);
     glTranslatef(-0.5f, -0.5f, -0.5f);
     glTranslatef(0.0f, 0.0f, -15.0f); 
	 glMatrixMode(GL_MODELVIEW); 
	 //glMatrixMode(GL_MODELVIEW); */
   
    //////glMatrixMode(GL_MODELVIEW); 
	/* latest
	float ratio = 1.0f * width / height;

	gluPerspective(45,ratio,1,1000);
//	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.tx,camera.ty , camera.tz, 
		  	-camera.atx, -camera.aty, -camera.atz,
			0.0f,1.0f,0.0f);   latest */
	/*gluLookAt(0.0,0.0 , 0.0, 
		  	-0.5, -0.5, -0.5,
			0.0f,1.0f,0.0f); */
 // latest  glMatrixMode(GL_MODELVIEW);  
    
	//Move away from center
	///glTranslatef(0., 0., -5.);
     //glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
    // glMatrixMode(GL_MODELVIEW); 
	/* glViewport(0, 0, width, height); */
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     float aspect = width/(float)(height ? height : 1);
     glFrustum(-aspect, aspect, -1, 1, 5, 50);
     glTranslatef(-0.5f, -0.5f, -0.5f);
     glTranslatef(0.0f, 0.0f, -15.0f);
	 glMatrixMode(GL_MODELVIEW);   
 }

  void GLWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
	  
 }

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();
	/*  if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     } */
    /* if (event->buttons() & Qt::LeftButton) {
         rotateBy(8 * dy, 8 * dx, 0);
     } else if (event->buttons() & Qt::RightButton) {
         rotateBy(8 * dy, 0, 8 * dx);
     } */
    // lastPos = event->pos();
	 
	 if (event->buttons() & Qt::LeftButton) {
		 if(abs(dx) > abs(dy))
			camera.az += (GLdouble) (dy);          
         else
            camera.el -= (GLdouble) (dy);
	 }
	 else if (event->buttons() & Qt::RightButton) {
		 camera.tx += (GLdouble) cos(camera.az/180.0*3.141)*dx/10.0;
		 camera.tz += (GLdouble) sin(camera.az/180.0*3.141)*dx/10.0;
         camera.ty -= (GLdouble) dy/10.0; //FLTK's origin is at the left_top corner
		 
		camera.atx = -camera.tx;
		camera.aty = -camera.ty;
		 camera.atz = -camera.tz;
 } /* else if (event->buttons() & Qt::MiddleButton) {
		// camera.tx += (GLdouble) cos(camera.az/180.
	  if(abs(dy) > abs(dx))
        {
		glScalef(1+dy/100.,1+dy/100.,1+dy/100.);	
       
		}  */
		
		/* camera.tx += (GLdouble) cos(camera.az/180.0*3.141)*dx/10.0;
		 camera.tz += (GLdouble) sin(camera.az/180.0*3.141)*dx/10.0;
         camera.ty -= (GLdouble) dy/10.0; //FLTK's origin is at the left_top corner

		 camera.atx = -camera.tx;
		 camera.aty = -camera.ty;
		 camera.atz = -camera.tz; 
         setXRotation(xRot + 16 * dy);
         setYRotation(yRot + 16 * dx); 
     } else if (event->buttons() & Qt::RightButton) {
		 camera.tx += (GLdouble) cos(camera.az/180.0*3.141)*dx/10.0;
		 camera.tz += (GLdouble) sin(camera.az/180.0*3.141)*dx/10.0;
         camera.ty -= (GLdouble) dy/10.0; //FLTK's origin is at the left_top corner

		 camera.atx = -camera.tx;
		 camera.aty = -camera.ty;
		 camera.atz = -camera.tz; */
		/* if(abs(dy) > abs(dx))
        {
		glScalef(1+dy/100.,1+dy/100.,1+dy/100.);	
       //     camera.zoom -= (GLdouble) delta_y/100.0;
       //     if(camera.zoom < 0.) camera.zoom = 0;
		}
        setXRotation(xRot + 16 * dy);
         setZRotation(zRot + 16 * dx);  */
   //  } 

     lastPos = event->pos();
 }

  void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
 {
     xRot += xAngle;
     yRot += yAngle;
     zRot += zAngle;
     updateGL();
 }
void GLWidget::initializeGL(){
	
     //object = makeObject();
	makeCurrent();
	qglClearColor(trolltechPurple.dark());
     //object = makeObject();
    /* glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE); */
	gl_init();
	light_init();
	draw_ground();
	draw_triad();
    /* glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE); */
	
	redisplay();
	//updateGL();
}

//Pre-draw the bones using quadratic object drawing function
//and store them in the display list
void GLWidget::set_display_list(Bone *bone, GLuint *pBoneList)
{
   int j;
   GLUquadricObj *qobj;
   makeCurrent();
   	int numbones = numBonesInSkel(bone[0]);
   *pBoneList = glGenLists(numbones);
   qobj=gluNewQuadric();

   gluQuadricDrawStyle(qobj, (GLenum) GLU_FILL);
   gluQuadricNormals(qobj, (GLenum) GLU_SMOOTH);
   for(j=0;j<numbones;j++)
   {
      glNewList(*pBoneList + j, GL_COMPILE);
      glScalef(bone[j].aspx, bone[j].aspy, 1.);
      gluSphere(qobj, bone[j].length/2.0, 20, 20);
      glEndList();
   }
}

//Set actor for display
void GLWidget::loadActor(Skeleton *pActor)
{
	//set a pointer to the actor info
	if (numActors > MAX_SKELS) return;

	m_pActor[numActors++] = pActor;

	//Create the display list for the skeleton.
	//All the bones are the elongated spheres centered at (0,0,0).
	//The axis of elongation is the X axis.
	set_display_list(m_pActor[numActors-1]->getRoot(), &m_BoneList[numActors-1]);
}

//Draws the world coordinate axis
void GLWidget::draw_bone_axis() 
{
	
   makeCurrent();
   glBegin(GL_LINES);
   // draw x axis in red, y axis in green, z axis in blue 
   glColor3f(1., .2, .2);
   glVertex3f(0., 0., 0.);
   glVertex3f(.5, 0., 0.);

   glColor3f(.2, 1., .2);
   glVertex3f(0., 0., 0.);
   glVertex3f(0., .5, 0.);

   glColor3f(.2, .2, 1.);
   glVertex3f(0., 0., 0.);
   glVertex3f(0., 0., .5);

   glEnd();
}
//Draws a line from point a to point b
void GLWidget::draw_vector(float *a, float *b) 
{
   makeCurrent();
   glBegin(GL_LINES);
   glColor3f(.5, .5, .5);
   glVertex3f(a[0], a[1], a[2]);
   glVertex3f(b[0], b[1], b[2]);
   glEnd();
}


void GLWidget::drawBone(Bone *pBone,int skelNum)
{
	static float z_dir[3] = {0., 0., 1.};
	float r_axis[3], mag, theta;
    makeCurrent();
	//Tranform (rotate) from the local coordinate system of this bone to it's parent
	//This step corresponds to doing: ModelviewMatrix = M_k * (rot_parent_current)
	glMultMatrixd((double*)&pBone->rot_parent_current);     

	//Draw the local coordinate system for the selected bone.
	if(pBone->idx == m_SpotJoint)
		draw_bone_axis();

	//rotate AMC 
	//This step corresponds to doing: ModelviewMatrix *= R_k+1
	if(pBone->doftz) glTranslatef(0.,0.,pBone->tz);
	if(pBone->dofty) glTranslatef(0.,pBone->ty,0.);
	if(pBone->doftx) glTranslatef(pBone->tx,0.,0.);
	
	
	if(pBone->dofz) glRotatef(pBone->drz, 0., 0., 1.);
	if(pBone->dofy) glRotatef(pBone->dry, 0., 1,  0.);
	if(pBone->dofx) glRotatef(pBone->drx, 1., 0., 0.);

	glColor3f(1., 1., 0.1);

	//Store the current ModelviewMatrix (before adding the translation part)
	glPushMatrix();

	//Compute tx, ty, tz - translation from pBone to it's child (in local coordinate system of pBone)
	float tx = pBone->dir[0]*pBone->length;
	float ty = pBone->dir[1]*pBone->length;
	float tz = pBone->dir[2]*pBone->length;


	// Use the current ModelviewMatrix to display the current bone
	// Rotate the bone from its canonical position (elongated sphere 
	// with its major axis parallel to X axis) to its correct orientation
	if(pBone->idx == root)
		glCallList(m_BoneList[skelNum] + pBone->idx);
	else
	{ 
		//translate to the center of the bone
		glTranslatef(tx/2.0, ty/2.0, tz/2.0);

		//Compute the angle between the canonical pose and the correct orientation 
		//(specified in pBone->dir) using cross product.
		//Using the formula: r_axis = z_dir x pBone->dir
		
		v3_cross(z_dir, pBone->dir, r_axis);

		theta =  GetAngle(z_dir, pBone->dir, r_axis);
		
		glRotatef(theta*180./M_PI, r_axis[0], r_axis[1], r_axis[2]);;
		glCallList(m_BoneList[skelNum] + pBone->idx);
	}

	glPopMatrix(); 

	// Finally, add the translation component to the ModelviewMatrix
	// This step corresponds to doing: M_k+1 = ModelviewMatrix += T_k+1
	glTranslatef(tx, ty, tz);

}
void GLWidget::light_init() 
{
    /* set up OpenGL to do lighting
     * we've set up three lights */

    /* set material properties */
	makeCurrent();
    GLfloat white8[] = {.8, .8, .8, 1.};
    GLfloat white2[] = {.2, .2, .2, 1.};
    GLfloat black[] = {0., 0., 0., 1.};
    GLfloat mat_shininess[] = {50.};		/* Phong exponent */

    GLfloat light0_position[] = {-25., 25., 25., 0.}; /* directional light (w=0) */
    GLfloat white[] = {11., 11., 11., 5.};

    GLfloat light1_position[] = {-25., 25., -25., 0.};
    GLfloat red[] = {1., .3, .3, 5.};

    GLfloat light2_position[] = {25., 25., -5., 0.};
    GLfloat blue[] = {.3, .4, 1., 25.};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white2);	/* no ambient */
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white8);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    /* set up several lights */
    /* one white light for the front, red and blue lights for the left & top */

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
    glEnable(GL_LIGHT2);

//mstevens
	GLfloat light3_position[] = {0., -25., 0., 0.6};
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT3, GL_SPECULAR, white);
    glEnable(GL_LIGHT3);

    glEnable(GL_NORMALIZE);	/* normalize normal vectors */
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	/* two-sided lighting*/

    /* do the following when you want to turn on lighting */
    if(Light) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
}
void GLWidget::setupViewport(int width, int height)
 {
     makeCurrent();
	 int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
    // glOrtho(-0.5, +0.5, +0.5, -0.5, 0.1, 50.0);
	  gluPerspective(/*vertical field of viw*/ 45.,
	/*aspect ratio*/ (double) width/height,
	/*znear*/ .1, /*zfar*/ 50.);
     //glMatrixMode(GL_MODELVIEW);
 }

void GLWidget::gl_init() 
{
    int red_bits, green_bits, blue_bits;
	makeCurrent();
    struct {GLint x, y, width, height;} viewport;
    glEnable(GL_DEPTH_TEST);	/* turn on z-buffer */
   // glViewport(640, 480, 480, 480);
   /* glGetIntegerv(GL_RED_BITS, &red_bits);
    glGetIntegerv(GL_GREEN_BITS, &green_bits);
    glGetIntegerv(GL_BLUE_BITS, &blue_bits);
	 glViewport(640, 480, 480, 480);
    glGetIntegerv(GL_VIEWPORT, &viewport.x);
    printf("OpenGL window has %d bits red, %d green, %d blue; viewport is %dx%d\n",
	red_bits, green_bits, blue_bits, viewport.width, viewport.height); */
   // setupViewport(viewport.width, viewport.height);
    /* setup perspective camera with OpenGL */
  /*  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.,
	  (double) viewport.width/viewport.height,
     .1,  50.); 

    
    glMatrixMode(GL_MODELVIEW); 
    
	//Move away from center
	glTranslatef(0., 0., -5.); */
    
	camera.zoom = 1;

	camera.tw = 0;
	camera.el = -15;
    camera.az = -25;
    
    camera.atx = 0;
    camera.aty = 0;
    camera.atz = 0;

	camera.tx = -0.5;
    camera.ty = -0.5;
    camera.tz = -0,5;
	
}



void GLWidget::traverse(Bone *ptr,int skelNum)
{
	makeCurrent();
   if(ptr != NULL)
   {
      glPushMatrix();
      drawBone(ptr,skelNum);
      traverse(ptr->child,skelNum);
      glPopMatrix();
      traverse(ptr->sibling,skelNum);
   }
}
QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }

//Draw the skeleton
void GLWidget::show()
{
	makeCurrent();
	      //  static int showed = 0;
        if (showed == 0){
				for (int i = 0; i < numActors; i++)
					set_display_list(m_pActor[i]->getRoot(), &m_BoneList[i]);
                showed = 1;
        }

   glPushMatrix();

   //Translate the root to the correct position (it is (0,0,0) if no motion is loaded)
//   glTranslatef(m_pActor->m_RootPos[0], m_pActor->m_RootPos[1], m_pActor->m_RootPos[2]);

   //draw the skeleton starting from the root
   for (int i = 0; i < numActors; i++)
   {
		glPushMatrix();
		glTranslatef(MOCAP_SCALE*m_pActor[i]->tx,MOCAP_SCALE*m_pActor[i]->ty,MOCAP_SCALE*m_pActor[i]->tz);
		glRotatef(m_pActor[i]->rx,1,0,0);
		glRotatef(m_pActor[i]->ry,0,1,0);
		glRotatef(m_pActor[i]->rz,0,0,1);
	   traverse(m_pActor[i]->getRoot(),i);
   
		glPopMatrix();
   }
   glPopMatrix();
}

void GLWidget::loadMotion(Motion *pMotion)
{
	if (numActors - 1 > MAX_SKELS) return;
//set a pointer to the new motion

	////////////////if(m_pMotion[numActors-1]!=NULL) 
	////////////////	delete m_pMotion[numActors-1];
	m_pMotion[numActors-1] = pMotion;
}
//! [0]

//! [1]

void GLWidget::redraw()
{
    //elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
	/*if (!valid()){
		gl_init();
		light_init();    
	} */
	makeCurrent();
	show();
	redisplay();
	//}
}
//! [1]

//! [2]

void GLWidget::paintEvent(QPaintEvent *event)
{
	updateGL();
	/*
     QPainter painter;
    painter.begin(this);
	 qglColor(Qt::black);
     renderText(-0.35, 0.4, 0.0, "Multisampling enabled");
     renderText(0.15, 0.4, 0.0, "Multisampling disabled");
	 painter.setPen(Qt::red);
     painter.setRenderHint(QPainter::Antialiasing);
	 painter.drawText(20, 40, "This is a test fps");
	 painter.end();
	//redisplay();
    //painter.begin(this);
    //painter.setRenderHint(QPainter::Antialiasing);
    //helper->paint(&painter, event, elapsed);
	redisplay();
   // painter.end();
   */
}


//Draw checker board ground plane
void GLWidget::draw_ground() 
{
   float i, j;
   int count = 0;
   makeCurrent();
   GLfloat white4[] = {.4, .4, .4, 1.};
   GLfloat white1[] = {.1, .1, .1, 1.};
   GLfloat green5[] = {0., .5, 0., 1.};
   GLfloat green2[] = {0., .2, 0., 1.};
   GLfloat black[] = {0., 0., 0., 1.};
   GLfloat mat_shininess[] = {7.};		/* Phong exponent */
	
   glBegin(GL_QUADS);

   for(i=-15.;i<=15.;i+=1) 
   {
      for(j=-15.;j<=15.;j+=1) 
      {			 
		if((count%2) == 0) 
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white4);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white1);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
			glColor3f(.6, .6, .6);
		}
		else 
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);	
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green5);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green2);
//			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
			glColor3f(.8, .8, .8);
		}

		glNormal3f(0.,0.,1.);

		glVertex3f(j,  0, i);
		glVertex3f(j,  0, i+1);
		glVertex3f(j+1,0, i+1);
		glVertex3f(j+1,0, i);
		count++;
	  }
   }

   glEnd();
}

void GLWidget::cameraView(void)
{
    makeCurrent();
	glTranslated(camera.tx, camera.ty, camera.tz);
    glTranslated(camera.atx, camera.aty, camera.atz);

    glRotated(-camera.tw, 0.0, 1.0, 0.0);
    glRotated(-camera.el, 1.0, 0.0, 0.0);
    glRotated(camera.az, 0.0, 1.0, 0.0); 
    
	glTranslated(-camera.atx, -camera.aty, -camera.atz);
    glScaled(camera.zoom, camera.zoom, camera.zoom);
}
void GLWidget::setPlayOn(){
	playC=ON;
	rewindC=OFF;
}
void GLWidget::setPause(){
	
	playC=OFF;
	repeatC=OFF;
}
void GLWidget::setRepeat(){
	rewindC= OFF;
	playC=ON;
	repeatC=ON;
} 
void GLWidget::setRewind(){
	rewindC= ON;
	playC=OFF;
	repeatC=OFF;
}
void GLWidget::rewind(void){
	if (m_pMotion[0] != NULL){
			nFrameNum=0;
			for (int i = 0; i < numActors; i++)
				m_pActor[i]->setPosture(m_pMotion[i]->m_pPostures[m_pMotion[i]->GetPostureNum(nFrameNum)]);
			rewindC=OFF;
	}
}

void GLWidget::play(void){
	if (m_pMotion[0] != NULL){
			if(nFrameNum >= maxFrames)  
			{
				if(Repeat == ON)
				{
					nFrameNum=0;
					for (int i = 0; i < numActors; i++)
						m_pActor[i]->setPosture(m_pMotion[i]->m_pPostures[m_pMotion[i]->GetPostureNum(nFrameNum)]);
				}
				else
				{
					for (int i = 0; i < numActors; i++)
						m_pActor[i]->setPosture(m_pMotion[i]->m_pPostures[m_pMotion[i]->GetPostureNum(nFrameNum)]);
				}
			}
			else
				 for (int i = 0; i < numActors; i++)
					 m_pActor[i]->setPosture(m_pMotion[i]->m_pPostures[m_pMotion[i]->GetPostureNum(nFrameNum)]);

#ifdef WRITE_JPEGS
			if(Record==ON) 
				glwindow->save(Record_filename);
#endif
			
			if (nFrameNum < maxFrames)
				nFrameNum += nFrameInc;
			show();
	}
}

void GLWidget::draw_triad() 
{
    makeCurrent();
	glBegin(GL_LINES);

   /* draw x axis in red, y axis in green, z axis in blue */
   glColor3f(1., .2, .2);
   glVertex3f(0., 0., 0.);
   glVertex3f(1., 0., 0.);

   glColor3f(.2, 1., .2);
   glVertex3f(0., 0., 0.);
   glVertex3f(0., 1., 0.);

   glColor3f(.2, .2, 1.);
   glVertex3f(0., 0., 0.);
   glVertex3f(0., 0., 1.);

   glEnd();
}

/*
 * redisplay() is called by Player_Gl_Window::draw().
 *
 * The display is double buffered, and FLTK swap buffers when
 * Player_Gl_Window::draw() returns.  The GL context associated with this
 * instance of Player_Gl_Window is set to be the current context by FLTK
 * when it calls draw().
 */
void GLWidget::redisplay() 
{
	/* QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.end(); */
	//makeCurrent();
    if(Light) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);

    /* clear image buffer to black */
   //glClearColor(0, 0, 0, 0);
   // glEnable(GL_DEPTH_TEST);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); /* clear image, zbuf */

    glPushMatrix();			/* save current transform matrix */
 
    cameraView();

    glLineWidth(2.);		/* we'll draw background with thick lines */

    if (Background)
    { 
       draw_triad();		/* draw a triad in the origin of the world coord */
       draw_ground();
    }

    if (bActorExist) show();

    glPopMatrix();			/* restore current transform matrix */
	//updateGL();

}
/*
QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }
 */
void GLWidget::timerEvent(QTimerEvent *)
 {
     update();
 }


void GLWidget::load_Motion() 
{
//if (bActorExist == true)
//		{
			char *filename;
		    QFileDialog::Options options;
			options |= QFileDialog::DontUseNativeDialog;
			QString selectedFilter;
			QString fileName = QFileDialog::getOpenFileName(this,
				tr("Open Actor File "), "C:\\Users\\ohje\\projects\\finalProject\\",tr("Text Files (*.AMC)"));
			std::string actorFile = fileName.toStdString();
			char *retPtr(new char[actorFile.length() + 1]);
			strcpy(retPtr,actorFile.c_str());
			//filename = fl_file_chooser("Select filename","*.AMC","");
			if(fileName != NULL)
			{
				//Read motion (.amc) file and create a motion
				pSampledMotion = new Motion(retPtr, MOCAP_SCALE,pActor);

				//set sampled motion for display
				loadMotion(pSampledMotion);               
			
				//Tell actor to perform the first pose ( first posture )
//				pActor->setPosture(displayer.m_pMotion->m_pPostures[0]);          
				maxFrames = 0;
				if ( (m_pMotion[numActors-1]->m_NumFrames - 1) > maxFrames)
				{
					maxFrames = (m_pMotion[numActors-1]->m_NumFrames - 1);
					setMaximum(maxFrames+1);
					//parent->setMaximum(maxFrames+1);
				//	frame_slider->maximum((double)maxFrames+1);

				}
				mySliderValue =0;
				nFrameNum = mySliderValue;
                //nFrameNum=maxFram
				//nFrameNum=(int) (parent->getSliderValue() -1);
				// display
		for (int i = 0; i < numActors; i++)
			m_pActor[i]->setPosture(m_pMotion[i]->m_pPostures[m_pMotion[i]->GetPostureNum(nFrameNum)]);
			//	Fl::flush();
		show();
				updateGL();
			}
  // }
}

void GLWidget::load_Actor() 
{
	char *filename;
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Actor File "), "C:\\Users\\ohje\\projects\\finalProject\\",tr("Text Files (*.ASF)"));
	std::string actorFile = fileName.toStdString();
	char *retPtr(new char[actorFile.length() + 1]);

    copy(actorFile.begin(), actorFile.end(), retPtr);
    retPtr[actorFile.length()] = '\0';
	pActor = new Skeleton(retPtr, MOCAP_SCALE);
	pActor->setBasePosture();
	loadActor(pActor);
	bActorExist = true;
	updateGL();
}
void GLWidget::normalizeAngle(int *angle)
 {
     while (*angle < 0)
         *angle += 360 * 16;
     while (*angle > 360 * 16)
         *angle -= 360 * 16;
 }
/*
// locate rotation center at the (root.x, 0, root.z)
void GLWidget::locate()
{
   if(bActorExist && m_pMotion[0] != NULL)
   {
      camera.zoom = 1;
      camera.atx = pActor->m_RootPos[0];  
      camera.aty = 0;
      camera.atz = pActor->m_RootPos[2];
   }
   redraw();
}
*/





