#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include"./irrK/irrKlang.h"
#include<iostream>
#include <stdarg.h>
#include <string.h>
extern "C" {
#include "glm.h"
}


using namespace irrklang;
using namespace std;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

GLMmodel* model = NULL;

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f


int wHeight = 0;
int wWidth = 0;

//todo
//hint: some additional parameters may needed here when you operate the teapot


void load_glm() {
	model = glmReadOBJ((char*)"data/CreepySnowmanMedPoly.obj");
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90);
}


void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	gluPerspective(45.0f, whRatio, 0.01f, 10.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}
// void myLighting() {
// 	GLfloat pos[] = { 1, 1, -1, 0 };
// 	glEnable(GL_LIGHTING);
// 	glEnable(GL_LIGHT0);
// 	glLightfv(GL_LIGHT0, GL_POSITION, pos);
// 	glEnable(GL_DEPTH_TEST);
// }
void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 4 };
float center[] = { 0, 0, 0 };
//todo; hint: you may need another ARRAY when you operate the teapot


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],center[0], center[1], center[2],0, 1, 0);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	


	glEnable(GL_LIGHTING);

	GLfloat light_position[] = { 4.0, 4.0, 0.0, 0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	//GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_pos[] = { 4,4,0,1 };

	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	//glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	//glRotatef(-90, 1, 0, 0);
	//glScalef(0.2, 0.2, 0.2);
	glEnable(GL_DEPTH_TEST);
	glScalef(0.5, 0.5, 0.5);
	//glmScale(model, 1.1);
	glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);

	glTranslatef(2.0, 0.0, 0.0);
	glmDraw(model,  GLM_SMOOTH);
	//glutSwapBuffers();					// Draw Scene
	glDisable(GL_LIGHTING);

	//glTranslatef(2.0, 0.0, 0.0);

	//glEnable(GL_LIGHTING);
	//GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_pos[] = { 4,4,0,1 };

	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, white);

	//glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);
	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{



	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	load_glm();
	//myLighting();
	glutMainLoop();

	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
		return 0; // error starting up the engine
	char i = 0;

	while (i != 'q')
	{
		std::cout << "Press any key to play some sound, press 'q' to quit.\n";

		// play a single sound
		engine->play2D("./media/SoundTest.wav");

		std::cin >> i; // wait for user to press some key
	}

	engine->play2D("./media/");


	engine->drop(); // delete engine
	return 0;
}





