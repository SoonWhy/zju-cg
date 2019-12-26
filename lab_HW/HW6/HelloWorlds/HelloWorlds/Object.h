#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<string>
#include<vector>
#include<iostream>
extern "C" {
#include "glmObj.h"
}
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"eye.h"
using namespace std;
using namespace glm;

class Object {

public:
	string name;

	vec3 position;
	vec2 rotateCoor;
	bool lighting;

	GLMmodel* model;

	vec2 screenPos(mat4 projecttion,mat4 view);
};


vec2 Object::screenPos(mat4 projection,mat4 view){
	vec2 window={glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)};
	vec4 ndc=projection*view*vec4(position, 1);
	ndc=ndc/ndc.w*0.5f+0.5f;
	return vec2(ndc.x,1-ndc.y)*window;
}

Object soccerball;
Object flowers;
Object lightDot;
Object rose_vase;

vector<Object> objects;

void initObject(){

	soccerball.name="soccerball";
	soccerball.rotateCoor={0,0};
	soccerball.lighting=true;
	soccerball.model=glmReadOBJ((char*)"data/soccerball.obj");
	glmUnitize(soccerball.model);
	glmFacetNormals(soccerball.model);
	glmVertexNormals(soccerball.model,90);
	soccerball.position={-2.0,1.0,0};

	flowers.name="flowers";
	flowers.rotateCoor={0,0};
	flowers.lighting=true;
	flowers.model=glmReadOBJ((char*)"data/flowers.obj");
	glmUnitize(flowers.model);
	glmFacetNormals(flowers.model);
	glmVertexNormals(flowers.model,90);
	flowers.position={2.0,1.0,0};


	rose_vase.name="rose_vase";
	rose_vase.rotateCoor={0,0};
	rose_vase.lighting=true;
	rose_vase.model=glmReadOBJ((char*)"data/rose+vase.obj");
	glmUnitize(rose_vase.model);
	glmFacetNormals(rose_vase.model);
	glmVertexNormals(rose_vase.model,90);
	rose_vase.position={0.0,1.0,0};

	lightDot.name="lightDot";
	lightDot.position={0,5,0};

	objects.push_back(soccerball);
	objects.push_back(flowers);
	objects.push_back(lightDot);
	objects.push_back(rose_vase);
}

void drawObj(){


	for(int i=0;i<objects.size();i++){
		objects[i].position.y=objects[i].position.y<1?1:objects[i].position.y;

		if(objects[i].name=="lightDot"){
			lightPos1[0] = objects[i].position.x;
			lightPos1[1] = objects[i].position.y;
			lightPos1[2] = objects[i].position.z;
			glPushMatrix();
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			//保存之前的属性，确保可以返回原渲染路径（此处为纹理和灯光属性）
			glDisable(GL_TEXTURE_2D);//禁用纹理
			glDisable(GL_LIGHTING);//禁用灯光
			glColor3f(diffuse[0], diffuse[1], diffuse[2]);//设置新的颜色（变换光源颜色）
			glTranslatef(objects[i].position.x, objects[i].position.y, objects[i].position.z);
			glScalef(0.1, 0.1, 0.1);//缩放为原来0.1倍
			// drawSphere();//将光源移动到其所在位置
			glutSolidSphere(1.0f,50,50);
			glEnable(GL_TEXTURE_2D);//启用纹理
			glEnable(GL_LIGHTING);//启用灯光
			glPopAttrib();//恢复属性
			glPopMatrix();
		}
		else{
			glPushMatrix();
			objects[i].lighting?glEnable(GL_LIGHTING):glDisable(GL_LIGHTING);
			glTranslatef(objects[i].position.x,objects[i].position.y,objects[i].position.z);
			glRotatef(objects[i].rotateCoor.x,0,1,0);
			glRotatef(objects[i].rotateCoor.y,1,0,0);

			glmDraw(objects[i].model,GLM_MATERIAL|GLM_SMOOTH);
			glPopMatrix();
		}
		
	}
}

void drawPlane()
{
	glPushMatrix();//推送矩阵堆栈
    glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0,0);
	glVertex3f(-1, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 0, 1);
	glEnd();
	glPopMatrix();
}

void drawNormalScene(){

	// glPushMatrix();

	// glRotatef(flyYAngle,0,1.0f,0);

	// glPushMatrix();

	// glRotatef(flyXZAngle,flyXZAxis.x,flyXZAxis.y,flyXZAxis.z);
		//绘制底面
    glBindTexture(GL_TEXTURE_2D, floorTex);//读入底面纹理
	glPushMatrix();
	glScalef(40, 0, 40);//将x,z坐标各扩大十倍
	drawPlane();
	glPopMatrix();

	drawObj();

	// glPopMatrix();

	// glPopMatrix();

}

void drawLeftEye(){
	 GLfloat matrix[16] = { 0. };


    glMatrixMode(GL_PROJECTION);
    // gluLookAt(eye[0], eye[1], eye[2],center[0], center[1], center[2],0, 1, 0);
    // glLoadIdentity();
	glPushMatrix();
    // glLoadIdentity();
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glMultMatrixf(LeftProjectMatrix);
	glMultMatrixf(matrix);

	glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// glTranslated(0.0, 0.0, -Fd);
	glPushMatrix();
	{
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();
		glMultMatrixf(LeftModelViewMatrix);
		glMultMatrixf(matrix);
		glColorMask(1.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		{   
            drawNormalScene();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();
}

void drawRightEye(){
	    glClearDepth(1.0);  
    glClear(GL_DEPTH_BUFFER_BIT);  

    GLfloat matrix[16] = { 0. };
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glMultMatrixf(RightProjectMatrix);
	glMultMatrixf(matrix);

	glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
	glPushMatrix();
	{
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();
		glMultMatrixf(RightModelViewMatrix);
		glMultMatrixf(matrix);

		glColorMask(0.0, 1.0, 1.0, 1.0);

		glPushMatrix();
		{
            drawNormalScene();
		}
        glPopMatrix();
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
}

void drawTwoEyes(){

	float width=glutGet(GLUT_WINDOW_WIDTH)/2;
	float height=glutGet(GLUT_WINDOW_HEIGHT)/2;

	glColorMask(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

    // ====normal
    glViewport(0,height,width,height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(0,0,0);
	// glRotatef(spin, 0.0, 1.0, 0.0);
	drawNormalScene();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glFlush();


	    // ====left
    glViewport(0,0,width,height);
    // drawBall();
    drawLeftEye();

	 // // ====right
    glViewport(width,0,width,height);
    drawRightEye();

	    // // ====both
    glViewport(width,height,width,height);
    drawLeftEye();
    drawRightEye();
}

void drawScene(){
	if(isDrawTwoEyes){
		drawTwoEyes();
	}
	else
	{
		glColorMask(1.0, 1.0, 1.0, 1.0);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		drawNormalScene();
		glFlush();
	}
	
}