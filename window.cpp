

#include <QtGui>
#include <algorithm>
#include "glwidget2.h"
#include "widget.h"
#include "window.h"

//! [0]
Window::Window()
    : QWidget()
{
 //   Widget *native = new Widget(&helper, this);
    displayer = new GLWidget(&helper, this);
	//displayer = new GLWidget;
	//displayer = new GLWidget();
   
    openGLLabel = new QLabel(tr("OpenGL"));
    openGLLabel->setAlignment(Qt::AlignHCenter);
	loadSkeletonButton = new QPushButton("Load Actor");
	loadMotionButton = new QPushButton("Load Motion");
	locateButton = new QPushButton("Locate");
	interpolateButton = new QPushButton("Interpolate");
	exitButton = new QPushButton("Exit");
	lightButton = new QPushButton("Light");
	backgroundButton = new QPushButton("Background");

	rewindButton = new QPushButton("Rewind");
	playButton = new QPushButton("Play");
    pauseButton = new QPushButton("Pause");
	repeatButton = new QPushButton("Repeat");
	slider = new QSlider(Qt::Horizontal);
	slider->setSingleStep(1);
	slider->setTickInterval(1);
	slider->setValue(0);
	sliderLabel= new QLabel("");
	labelJoint = new QLabel("Joint");
	jointEdit = new QLineEdit();
	jointEdit->setText("-1");
	frameLabel = new QLabel("Frame Steps");
	frameEdit = new QLineEdit();
	frameEdit->setText("1");
	subLabel = new QLabel("Sub");
	subEdit = new QLineEdit();
	subEdit->setText("0");
	dtLabel = new QLabel("dt");
	dtEdit = new QLineEdit();
	dtEdit->setText("0");
	txLabel = new QLabel("tx");
	txEdit = new QLineEdit();
	txEdit->setText("0");
	tyLabel = new QLabel("ty");
	tyEdit = new QLineEdit();
	tyEdit->setText("0");
	tzLabel = new QLabel("tz");
	tzEdit = new QLineEdit();
	tzEdit->setText("0");
	rxLabel = new QLabel("rx");
	rxEdit = new QLineEdit();
	rxEdit->setText("0");
    ryLabel = new QLabel("ry");
	ryEdit = new QLineEdit();
	ryEdit->setText("0");
	rzLabel = new QLabel("rz");
	rzEdit = new QLineEdit();
	rzEdit->setText("0");

  

    QGridLayout *layout = new QGridLayout;
   
    layout->addWidget(displayer, 0, 1);
   // layout->addWidget(nativeLabel, 1, 0);
    layout->addWidget(openGLLabel, 1, 1);
	layout->addWidget(loadSkeletonButton, 2, 0);
    layout->addWidget(loadMotionButton, 2, 1);
	layout->addWidget(locateButton, 2, 2);
    layout->addWidget(interpolateButton,2, 3);
	layout->addWidget(exitButton,3, 0);
	layout->addWidget(lightButton,3, 1);
	layout->addWidget(backgroundButton,3, 2);
	layout->addWidget(rewindButton,4, 0);
	layout->addWidget(playButton,4, 1);
	layout->addWidget(pauseButton,4, 2);
	layout->addWidget(repeatButton,4, 3);
	layout->addWidget(sliderLabel,5, 0);
	layout->addWidget(slider,5, 1);
	layout->addWidget(labelJoint,6, 0);
	layout->addWidget(jointEdit,6, 1);
	layout->addWidget(frameLabel,6, 2);
	layout->addWidget(frameEdit,6, 3);
	layout->addWidget(subLabel,7, 0);
	layout->addWidget(subEdit,7, 1);
	layout->addWidget(dtLabel,7, 2);
	layout->addWidget(dtEdit,7, 3);
	layout->addWidget(txLabel,8, 0);
	layout->addWidget(txEdit,8, 1);
	layout->addWidget(tyLabel,8, 2);
	layout->addWidget(tyEdit,8, 3);
    layout->addWidget(tzLabel,9, 0);
	layout->addWidget(tzEdit,9, 1);
	layout->addWidget(rxLabel,9, 2);
	layout->addWidget(rxEdit,9, 3);
	layout->addWidget(ryLabel,10, 0);
	layout->addWidget(ryEdit,10, 1);
	layout->addWidget(rzLabel,10, 2);
	layout->addWidget(rzEdit,10, 3);

    setLayout(layout);
	QObject::connect(loadSkeletonButton, SIGNAL(clicked()),this,SLOT(load_Actor()));
	QObject::connect(loadMotionButton, SIGNAL(clicked()),this,SLOT(load_Motion()));
	QObject::connect(playButton, SIGNAL(clicked()),this,SLOT(play()));
	QObject::connect(rewindButton, SIGNAL(clicked()),this,SLOT(rewind()));
	QObject::connect(pauseButton, SIGNAL(clicked()),this,SLOT(pause()));
	QObject::connect(repeatButton, SIGNAL(clicked()),this,SLOT(repeat()));
	QObject::connect(locateButton, SIGNAL(clicked()),this,SLOT(locate()));
	QObject::connect(backgroundButton, SIGNAL(clicked()),this,SLOT(callBackground()));
	QObject::connect(slider, SIGNAL(valueChanged(int)),
             this, SLOT(sliderCall(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)),
             displayer, SLOT(updateValue(int)));
	QObject::connect(displayer, SIGNAL(sliderValueChanged(int )),
             this, SLOT(setSliderValue(int )));

	QObject::connect(displayer, SIGNAL(setMaximumValue(int )),
             this, SLOT(setMax(int )));
	
    //gl_init();
	//light_init();
	QObject::connect(subEdit, SIGNAL(textChanged(const QString &)),
             this, SLOT(sub(const QString &)));
	QObject::connect(dtEdit, SIGNAL(textChanged(const QString &)),
             this, SLOT(dtCall(const QString &)));
    
	setLayout(layout);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), displayer, SLOT(animate()));
   /* connect(timer, SIGNAL(timeout()), displayer, SLOT(animate())); */
    timer->start(44); 

    setWindowTitle(tr("Motion Capture Data Viewer"));
}

void Window::rewind()
{
	if(displayer->m_pMotion[0] != NULL)
	{
		
		Rewind=ON; Play=OFF; Repeat=OFF; 
        displayer->setRewind();
	}
}
void Window::callBackground(){
    if (Light ==0) Light =1;
	else Light =0;
	if (Background==0) Background = 1;
	else Background = 0;
	displayer->redisplay();
}
void Window::repeat()
{
	if(displayer->m_pMotion[0] != NULL)
	{
		
		 Rewind=OFF; Play=ON; Repeat=ON; 
		 displayer->setRepeat();
		
	}
}
void Window::pause()
{
	if(displayer->m_pMotion[0] != NULL)
	{
		 Play=OFF; Repeat=OFF; 
		 displayer->setPause();
		
	}
}
void Window::play()
{
	if(displayer->m_pMotion[0] != NULL)
	{
		 Play=ON; Rewind=OFF; 
		 displayer->setPlayOn();
         //playC = ON;
		// displayer->play();
		
	}
}



void Window::load_Motion() 
{
	
//if (bActorExist == true)
//		{
			displayer->load_Motion();
			/* char *filename;
		    QFileDialog::Options options;
			options |= QFileDialog::DontUseNativeDialog;
			QString selectedFilter;
			QString fileName = QFileDialog::getOpenFileName(this,
				tr("Open Actor File "), "C:\\Qt\\myProject\\viewer\\",tr("Text Files (*.AMC)"));
			std::string actorFile = fileName.toStdString();
			char *retPtr(new char[actorFile.length() + 1]);
			strcpy(retPtr,actorFile.c_str());
			//filename = fl_file_chooser("Select filename","*.AMC","");
			if(filename != NULL)
			{
				//Read motion (.amc) file and create a motion
				pSampledMotion = new Motion(retPtr, MOCAP_SCALE,pActor);

				//set sampled motion for display
				displayer->loadMotion(pSampledMotion);               
			
				//Tell actor to perform the first pose ( first posture )
//				pActor->setPosture(displayer.m_pMotion->m_pPostures[0]);          
				maxFrames = 0;
				if ( (displayer->m_pMotion[displayer->numActors-1]->m_NumFrames - 1) > maxFrames)
				{
					maxFrames = (displayer->m_pMotion[displayer->numActors-1]->m_NumFrames - 1);
				//	frame_slider->maximum((double)maxFrames+1);

				}
                nFrameNum=maxFrames;
			//	nFrameNum=(int) frame_slider->value() -1;
				// display
	///////	oct		for (int i = 0; i < displayer->numActors; i++)
	/////	oct			displayer->m_pActor[i]->setPosture(displayer->m_pMotion[i]->m_pPostures[displayer->m_pMotion[i]->GetPostureNum(nFrameNum)]);
			//	Fl::flush();
				displayer->redraw();
			}
			*/
 //  }
}

void Window::load_Actor() 
{
	displayer->load_Actor();
	/*
	char *filename;
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Actor File "), "C:\\Qt\\myProject\\viewer\\",tr("Text Files (*.ASF)"));
	std::string actorFile = fileName.toStdString();
	char *retPtr(new char[actorFile.length() + 1]);

    copy(actorFile.begin(), actorFile.end(), retPtr);
    retPtr[actorFile.length()] = '\0';
	pActor = new Skeleton(retPtr, MOCAP_SCALE);
	pActor->setBasePosture();
	displayer->loadActor(pActor);
	bActorExist = true;
	displayer->redraw();
	*/
}
// locate rotation center at the (root.x, 0, root.z)
void Window::locate()
{
   if(bActorExist && displayer->m_pMotion[0] != NULL)
   {
      camera.zoom = 1;
      camera.atx = pActor->m_RootPos[0];  
      camera.aty = 0;
      camera.atz = pActor->m_RootPos[2];
   }
   displayer->redraw();
}
/*
void Window::light_init() 
{
    
    GLfloat white8[] = {.8, .8, .8, 1.};
    GLfloat white2[] = {.2, .2, .2, 1.};
    GLfloat black[] = {0., 0., 0., 1.};
    GLfloat mat_shininess[] = {50.};		

    GLfloat light0_position[] = {-25., 25., 25., 0.}; 

    GLfloat light1_position[] = {-25., 25., -25., 0.};
    GLfloat red[] = {1., .3, .3, 5.};

    GLfloat light2_position[] = {25., 25., -5., 0.};
    GLfloat blue[] = {.3, .4, 1., 25.};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white2);	
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white8);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
   // glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
   // glLightfv(GL_LIGHT0, GL_SPECULAR, white);
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
  //  glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
   // glLightfv(GL_LIGHT3, GL_SPECULAR, white);
    glEnable(GL_LIGHT3);

    glEnable(GL_NORMALIZE);	
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	
       if(Light) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
}


void Window::gl_init() 
{
    int red_bits, green_bits, blue_bits;
    struct {GLint x, y, width, height;} viewport;
    glEnable(GL_DEPTH_TEST);	

    glGetIntegerv(GL_RED_BITS, &red_bits);
    glGetIntegerv(GL_GREEN_BITS, &green_bits);
    glGetIntegerv(GL_BLUE_BITS, &blue_bits);
    glGetIntegerv(GL_VIEWPORT, &viewport.x);
    printf("OpenGL window has %d bits red, %d green, %d blue; viewport is %dx%d\n",
	red_bits, green_bits, blue_bits, viewport.width, viewport.height);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.,
	 (double) viewport.width/viewport.height,
	 .1, 50.);

    
    glMatrixMode(GL_MODELVIEW);
    
	
	glTranslatef(0., 0., -5.);
    
	camera.zoom = 1;

	camera.tw = 0;
	camera.el = -15;
    camera.az = -25;
    
    camera.atx = 0;
    camera.aty = 0;
    camera.atz = 0;
}

*/


void Window::valueIn()
{
   displayer->m_SpotJoint = (jointEdit->text()).toInt();
   nFrameInc = (frameEdit->text()).toInt();
   // glwindow->redraw();
}
void Window::sliderCall(int val)
{
	if (displayer->m_pMotion[0] != NULL)
	{
		if(displayer->m_pMotion[0]->m_NumFrames > 0) 
		{
			nFrameNum=(int) val -1;
			QString number;
			number.setNum(nFrameNum);
			sliderLabel->setText(number);
			
			for (int i = 0; i < displayer->numActors; i++){
//				if(displayer.m_pMotion[i]->m_NumFrames > 0)
					displayer->m_pActor[i]->setPosture(displayer->m_pMotion[i]->m_pPostures[displayer->m_pMotion[i]->GetPostureNum(nFrameNum)]);
			//Fl::flush();
					
			}
			displayer->redraw();
			//slider->setValue(nFrameNum);
			

		}
	}
}
void Window::setMax(int theMax)
{
	slider->setMaximum(theMax);
	slider->setValue(0);
	QString number;
    number.setNum(0);
    sliderLabel->setText(number);
}
void  Window::setSliderValue(int value)
{
	QString number;
    number.setNum(value);
	sliderLabel->setText(number);
	return slider->setValue(value);
}
void Window::sub(QString &a)
{
	int subnum;
	subnum = a.toInt();
	subValue = subnum;
	QString theNumber;
	theNumber.setNum(displayer->numActors-1,10);
	if (subnum < 0) subEdit->setText("0");
	else if (subnum > displayer->numActors-1) subEdit->setText(theNumber);
	 else
	{
		// Change values of other inputs to match subj num
		QString theFieldValue;
		dtEdit->setText(theFieldValue.setNum(displayer->m_pMotion[subnum]->offset,10));
		txEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->tx));
		tyEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->ty));
		tzEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->tz));
		rxEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->rx));
		ryEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->ry));
		rzEdit->setText(theFieldValue.sprintf("%f2.2",displayer->m_pActor[subnum]->rz));
		
	}
	displayer->redraw();
}

void Window::dtCall()
{
	int subnum,max = 0;
	subnum = subValue;
	QString theNumber;
	theNumber.setNum(displayer->numActors-1,10);
	//subnum = (int)subEdit->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pMotion[subnum]->SetTimeOffset((dtEdit->text()).toInt());	
		//printf("Shifting subject %d by %d\n",subnum,(int)dtEdit->value());
		for (int i = 0; i < displayer->numActors; i++)
		{
			if ((displayer->m_pMotion[i]->m_NumFrames - 1 - displayer->m_pMotion[i]->offset) > max)
				max = (displayer->m_pMotion[i]->m_NumFrames - 1 - displayer->m_pMotion[i]->offset);
		}
		maxFrames = max;
		slider->setMaximum(maxFrames+1);
		displayer->m_pActor[subnum]->setPosture(displayer->m_pMotion[subnum]->m_pPostures[displayer->m_pMotion[subnum]->GetPostureNum(nFrameNum)]);
	}
	displayer->redraw();
}


void Window::txCall()
{
	int subnum = subValue;
	
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->tx = (txEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::tyCall()
{
	int subnum = subValue;
	//subnum = (int)sub_input->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->ty = (tyEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::tzCall()
{
	int subnum = subValue;
	//subnum = (int)sub_input->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->tz = (tzEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::rxCall()
{
	int subnum = subValue;
	//subnum = (int)sub_input->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->rx = (rxEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::ryCall()
{
	int subnum = subValue;
	//subnum = (int)sub_input->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->ry = (ryEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::rzCall()
{
	int subnum = subValue;
	//subnum = (int)sub_input->value();
	if (subnum < displayer->numActors && subnum >= 0)
	{
		displayer->m_pActor[subnum]->rz = (rzEdit->text()).toDouble();
	}
	displayer->redraw();
}

void Window::exitCall() 
{
	//DEBUG: uncomment
	exit(1);
}

/*
	{
		filename = fl_file_chooser("Select filename","*.ASF","");
		if(filename != NULL)
		{
			//Remove old actor
			//if(pActor != NULL) 
			//	delete pActor; 
			//Read skeleton from asf file
			pActor = new Skeleton(filename, MOCAP_SCALE);

			//Set the rotations for all bones in their local coordinate system to 0
			//Set root position to (0, 0, 0)
			pActor->setBasePosture();
			displayer.loadActor(pActor);
			bActorExist = true;
			glwindow->redraw();
		}
	}
	*/

//! [0]
