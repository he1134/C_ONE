/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain
 ** additional rights. These rights are described in the Nokia Qt LGPL
 ** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
 ** package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>
 #include <QtOpenGL>

 #include <math.h>

 #include "glwidget.h"

 GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(parent)
 {
     object = 0;
     xRot = 0;
     yRot = 0;
     zRot = 0;

     trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
 }

 GLWidget::~GLWidget()
 {
     makeCurrent();
     glDeleteLists(object, 1);
 }

 QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(600, 600);
 }

 void GLWidget::setXRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != xRot) {
         xRot = angle;
         emit xRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setYRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != yRot) {
         yRot = angle;
         emit yRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setZRotation(int angle)
 {
     normalizeAngle(&angle);
     if (angle != zRot) {
         zRot = angle;
         emit zRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::initializeGL()
 {
     qglClearColor(trolltechPurple.dark());
     //object = makeObject();
	 draw_ground();
	 draw_triad();
    /* glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE); */
	 int red_bits, green_bits, blue_bits;
    struct {GLint x, y, width, height;} viewport;
    glEnable(GL_DEPTH_TEST);	/* turn on z-buffer */

    glGetIntegerv(GL_RED_BITS, &red_bits);
    glGetIntegerv(GL_GREEN_BITS, &green_bits);
    glGetIntegerv(GL_BLUE_BITS, &blue_bits);
    glGetIntegerv(GL_VIEWPORT, &viewport.x);
    printf("OpenGL window has %d bits red, %d green, %d blue; viewport is %dx%d\n",
	red_bits, green_bits, blue_bits, viewport.width, viewport.height);

    /* setup perspective camera with OpenGL */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(/*vertical field of view*/ 45.,
	 /*aspect ratio*/ (double) viewport.width/viewport.height,
    /*znear*/ .1, /*zfar*/ 50.);
	 glMatrixMode(GL_MODELVIEW);
    
	//Move away from center
	glTranslatef(0., 0., -5.);
    
	/* camera.zoom = 1;

	camera.tw = 0;
	camera.el = -15;
    camera.az = -25;
    
    camera.atx = 0;
    camera.aty = 0;
    camera.atz = 0; */

 }
 void GLWidget::draw_triad() 
{
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


 void GLWidget::paintGL()
 {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslated(0.0, 0.0, -10.0);
     glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
     glRotated(zRot / 16.0, 0.0, 0.0, 1.0); 
    // glCallList(object); 
	 draw_ground();
	 draw_triad();
	
 }
 //Draw checker board ground plane
void GLWidget::draw_ground() 
{
   float i, j;
   int count = 0;

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

 void GLWidget::resizeGL(int width, int height)
 {
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
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

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     }
     lastPos = event->pos();
 }

 GLuint GLWidget::makeObject()
 {
     GLuint list = glGenLists(1);
     glNewList(list, GL_COMPILE);

     glBegin(GL_QUADS);

     GLdouble x1 = +0.06;
     GLdouble y1 = -0.14;
     GLdouble x2 = +0.14;
     GLdouble y2 = -0.06;
     GLdouble x3 = +0.08;
     GLdouble y3 = +0.00;
     GLdouble x4 = +0.30;
     GLdouble y4 = +0.22;

     quad(x1, y1, x2, y2, y2, x2, y1, x1);
     quad(x3, y3, x4, y4, y4, x4, y3, x3);

     extrude(x1, y1, x2, y2);
     extrude(x2, y2, y2, x2);
     extrude(y2, x2, y1, x1);
     extrude(y1, x1, x1, y1);
     extrude(x3, y3, x4, y4);
     extrude(x4, y4, y4, x4);
     extrude(y4, x4, y3, x3);

     const double Pi = 3.14159265358979323846;
     const int NumSectors = 200;

     for (int i = 0; i < NumSectors; ++i) {
         double angle1 = (i * 2 * Pi) / NumSectors;
         GLdouble x5 = 0.30 * sin(angle1);
         GLdouble y5 = 0.30 * cos(angle1);
         GLdouble x6 = 0.20 * sin(angle1);
         GLdouble y6 = 0.20 * cos(angle1);

         double angle2 = ((i + 1) * 2 * Pi) / NumSectors;
         GLdouble x7 = 0.20 * sin(angle2);
         GLdouble y7 = 0.20 * cos(angle2);
         GLdouble x8 = 0.30 * sin(angle2);
         GLdouble y8 = 0.30 * cos(angle2);

         quad(x5, y5, x6, y6, x7, y7, x8, y8);

         extrude(x6, y6, x7, y7);
         extrude(x8, y8, x5, y5);
     }

     glEnd();

     glEndList();
     return list;
 }

 void GLWidget::quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
                     GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4)
 {
     qglColor(trolltechGreen);

     glVertex3d(x1, y1, -0.05);
     glVertex3d(x2, y2, -0.05);
     glVertex3d(x3, y3, -0.05);
     glVertex3d(x4, y4, -0.05);

     glVertex3d(x4, y4, +0.05);
     glVertex3d(x3, y3, +0.05);
     glVertex3d(x2, y2, +0.05);
     glVertex3d(x1, y1, +0.05);
 }

 void GLWidget::extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
 {
     qglColor(trolltechGreen.dark(250 + int(100 * x1)));

     glVertex3d(x1, y1, +0.05);
     glVertex3d(x2, y2, +0.05);
     glVertex3d(x2, y2, -0.05);
     glVertex3d(x1, y1, -0.05);
 }

 void GLWidget::normalizeAngle(int *angle)
 {
     while (*angle < 0)
         *angle += 360 * 16;
     while (*angle > 360 * 16)
         *angle -= 360 * 16;
 }



