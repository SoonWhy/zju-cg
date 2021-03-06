// glutEx1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#define _CRT_SECURE_NO_WARNINGS

#if defined(WIN32)
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "glew32.lib")
#include <glew.h>
#include "glut.h"
#include "wglew.h"
#include "glew.h"
//#include "glxew.h"

#include<iostream>
#include<vector>
#include<cmath>
#include<map>

#define PI 3.1415926
#define TORADIAN(x) (x*PI/180.0) 
#define CSC(x) (1.0/sin(x))
#define COT(x) (1.0/tan(x))

using namespace std;

float fTranslate;
float fRotate;
float fScale = 1.0f; // set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool bHu = false;
bool bDesk = false;

int wHeight = 0;
int wWidth = 0;


// homework4
int mEquation = 4;

float angleTheta=359;
float radianTheta;

float angleAlpha;
float radianAlpha;

float weight;
float radius;

vector<pair<float,float>> controlP;
int pointNum = 0;

void init()
{
	
	pointNum = 4;
	
	radianTheta=TORADIAN(angleTheta);

	angleAlpha = (360-angleTheta)/2;
	radianAlpha = TORADIAN(angleAlpha);

	// csc alpha
	radius=CSC(radianAlpha);
	cout << "radius: "<<radius << endl;


	controlP.clear();
	
	controlP.push_back(pair<float,float>(-1,0));
	float px=radius*COT(radianAlpha/2);
	//float py=tan(TORADIAN(90-angleAlpha/2));
	float py = -radius * (1 + cos(radianAlpha));
	controlP.push_back(pair<float,float>(-px,py));
	controlP.push_back(pair<float,float>(px,py));
	controlP.push_back(pair<float,float>(1,0));


	for (int i = 0; i < pointNum; i++) {
		cout << "control point" << i << ":" << controlP[i].first << "," << controlP[i].second << endl;
	}

	weight=1.0*(mEquation -2)/ mEquation;
	weight*=((controlP[3].first-controlP[0].first)*(controlP[2].first-controlP[1].first)+(controlP[3].second-controlP[0].second)*(controlP[2].second-controlP[1].second));
	weight/=((controlP[2].first-controlP[0].first)*(controlP[2].first-controlP[1].first)+(controlP[2].second-controlP[0].second)*(controlP[2].second-controlP[1].second));

	cout << "current weight: " << weight << endl;

}
float ratio = 1.3 / radius;

void drawP() {
	glPushMatrix();
	ratio = 1.3 / radius;

	glTranslatef(0, 1, 0);
	glScalef(ratio, ratio, ratio);

	glColor3f(0.0f, 255.0f, 0.0f);
	for (int i = 0; i < pointNum; i++) {
		glBegin(GL_QUADS);

		glVertex3f(controlP[i].first + 0.1, controlP[i].second + 0.1, 0);
		glVertex3f(controlP[i].first + 0.1, controlP[i].second - 0.1, 0);
		glVertex3f(controlP[i].first - 0.1, controlP[i].second - 0.1, 0);
		glVertex3f(controlP[i].first - 0.1, controlP[i].second + 0.1, 0);

		glEnd();
	}

	glPopMatrix();
}


void drawLine() {

	glPushMatrix();
	ratio = 1.3 / radius;

	glTranslatef(0, 1, 0);
	glScalef(ratio, ratio, ratio);

	glColor3f(0.0f, 0.0f, 255.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pointNum; i++) {
		glVertex3f(controlP[i].first, controlP[i].second, 0.0f);
	}
	glEnd();

	glPopMatrix();
}

void Draw()
{
	glPushMatrix();
	ratio = 1.3 / radius;
	
	glTranslatef(0, 1, 0);
	glScalef(ratio, ratio, ratio);

	glBegin(GL_LINE_STRIP);

	for(float u=0;u<=1;u+=0.000001){
		float px,py;
		float domi;
		domi=1+2*(u-1)*u+(mEquation-2)*(u-1)*u*cos(radianAlpha);
		px=2*u-1;
		px/=domi;
		py=(mEquation-2)*(u-1)*u*sin(radianAlpha);
		py/=domi;

		glVertex3f(px,py,0);
		//cout << "p " << px << "," << py << endl;
	}

	glEnd();
	glPopMatrix();
	
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity();			 // Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp)
	{
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else
	{
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0) // Prevent A Divide By Zero By
	{
		height = 1; // Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q':
	{
		exit(0);
		break;
	}
	case 'p':
	{
		bPersp = !bPersp;
		break;
	}

	case ' ':
	{
		bAnim = !bAnim;
		break;
	}
	case 'o':
	{
		bWire = !bWire;
		break;
	}

	case '+':
	{
		if (angleTheta < 359) {
			angleTheta += 1;
			init();
		}
		break;
	}
	case '-':
	{
		if (angleTheta > 60) {
			angleTheta -= 1;
			init();
		}
		break;
	}
		//todo
	}

	updateView(wHeight, wWidth);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
			  center[0], center[1], center[2],
			  0, 1, 0);

	if (bWire)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_pos[] = {5, 5, 5, 1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	Draw();
	drawP();
	drawLine();

	if (bAnim)
		fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	init();

	glutMainLoop();
	return 0;
}
