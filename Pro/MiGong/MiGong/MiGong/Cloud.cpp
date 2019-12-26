#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <GL\glut.h>
extern "C" {
#include"glm.h"
}


GLMmodel* model = NULL;

void initialModel() {
	model = glmReadOBJ("data/dolphins.obj");
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90);
}


void DrawSphere(float X, float Y, float Z)
{

	glPushMatrix();

	glRotatef(0, 1.0f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 0.0f);
	glRotatef(0, 0.0f, 0.0f, 1.0f);

	glTranslatef(X, Y, Z);

	//glLineWidth(3.0);
	//glColor3f(1, 1, 1);

	//glBegin(GL_LINE_LOOP);/// don¡¦t workglPointSize( 0.0 );
	//GLUquadricObj *quadric;
	//quadric = gluNewQuadric();

	//gluQuadricDrawStyle(quadric, GLU_FILL);
	//gluSphere(quadric, .5, 36, 18);

	//gluDeleteQuadric(quadric);

	glEnable(GL_DEPTH_TEST);
	glScalef(0.5, 0.5, 0.5);
	//glmScale(model, 1.1);
	glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);


	glEndList();

	glEnd();

	glPopMatrix();

}

void ControlCloud(float X, float Y, float Z ) {
	float cloud_x = 0.5;
	float cloud_y = 0.6;
	float cloud_z = 0.1;
	int num = 6;
	int i, y;

	glPushMatrix();
	glTranslatef(X, Y, Z);
	glTranslatef(-1, -0.5, -0.5);
	for (i = 0; i < num; i++) {
		DrawSphere(0 + cloud_x * i, 0, 0 - cloud_z * (i % 2));
	}

	for (i = 0; i < num - 1; i++) {
		DrawSphere(0 + cloud_x * i + cloud_x / 2, 0 + cloud_y, 0 - cloud_z * (i % 2));
	}

	for (i = 0; i < num - 1; i++) {
		DrawSphere(0 + cloud_x * i + cloud_x / 2, 0 - cloud_y, 0 - cloud_z * (i % 2));
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(X, Y, Z);
	glTranslatef(-1, -0.5, -0.5);
	for (i = 0; i < num - 1; i++) {
		DrawSphere(0 + cloud_x * i + cloud_x / 2, 0 + cloud_y / 2, 0 + cloud_z * (i % 2) + cloud_z * 3);
	}

	for (i = 0; i < num - 1; i++) {
		DrawSphere(0 + cloud_x * i + cloud_x / 2, 0 - cloud_y / 2, 0 + cloud_z * (i % 2) + cloud_z * 3);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(X, Y, Z);
	glTranslatef(-1, -0.5, -0.5);
	for (i = 0; i < num - 2; i++) {
		DrawSphere(0 + cloud_x * i + cloud_x, 0, 0 + cloud_z * (i % 2) + cloud_z * 5);
	}
	glPopMatrix();
}