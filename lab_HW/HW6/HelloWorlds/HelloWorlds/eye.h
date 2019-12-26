#pragma once

#include"glut.h"
#include<math.h>


GLfloat PI = 3.1415926;
GLfloat Fd = 5.0;            //fusion distance
GLfloat RealScreenToEyeDistance = 2.0;
GLfloat R;    
GLfloat Sd = 0.05;                        
GLfloat aspect = 1.0;                       
GLfloat fovy = 60.0;                        
GLfloat f;    //f=ctg(fovy/2);


GLfloat LeftModelViewMatrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

GLfloat LeftProjectMatrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

GLfloat RightModelViewMatrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

GLfloat RightProjectMatrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

//for the use of rotating
static GLfloat spin = 0.0;

// test LR eyes
bool isDrawTwoEyes=true;


void eyeInit(){
    R = Fd / RealScreenToEyeDistance;
	f = 1 / tan((fovy*PI) / (2 * 180));
    LeftModelViewMatrix[12]=Sd*R/2.0;
    LeftProjectMatrix[12]=-(Sd*f) / (2.0*Fd*aspect);
	RightModelViewMatrix[12]=-Sd*R / 2.0;
    RightProjectMatrix[12]=(Sd*f) / (2.0*Fd*aspect);
}