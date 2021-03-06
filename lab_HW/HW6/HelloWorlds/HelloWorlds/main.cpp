#define _CRT_SECURE_NO_WARNINGS
#pragma once
extern "C" {
#include "glmObj.h"
}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include"time.h"
#include <vector>
#include <iostream>
//#include "glmObj.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include"header.h"
#include"Object.h"
// #include"light.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace glm;

GLuint loadTexture(const char *file)
{
	GLuint tex=0;
	int w, h, c;
	unsigned char *data = stbi_load(file, &w, &h, &c, 3);//读入图片文件到data
	if (data)
	{
		glGenTextures(1, &tex);//为读入纹理分配索引值
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//在S方向贴图
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//在T方向贴图
		free(data);
	}
	return tex;
}



void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清楚颜色缓冲以及深度缓冲
	glColor3f(1, 1, 1);//设置颜色为白色

	glMatrixMode(GL_MODELVIEW);//接下来模型视景操作
	glLoadIdentity();//恢复初始坐标系

    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, (cameraPos + lookDir).x, (cameraPos + lookDir).y, (cameraPos + lookDir).z, up.x, up.y, up.z);
	viewMat = lookAt(cameraPos, cameraPos + lookDir, up);//视图矩阵

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);//设置光源的位置属性
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);//设置散射光

	drawScene();

	glutSwapBuffers();
}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w / float(h), 0.1, 100);

	projectionMat = perspective(radians(60.0f), w / float(h), 0.1f, 100.0f);//定义投影矩阵
    //perspective参数意义同gluPerspective
}


void idle(){
	static int time = clock();
	int newT = clock();
    float dt = float(newT - time) / CLOCKS_PER_SEC;//dt:一次循环的持续时间
	time = newT;

	float speed = 10.0;//相机移动速度
	vec3 f = normalize(lookDir);//单位化，得到x轴方向单位向量
	vec3 u = normalize(up);//单位化，得到z轴方向单位向量
	vec3 r = cross(f, u);//返回f,u的叉乘结果—y轴方向单位向量

	if (keyDown[FORWARD])
	{
		cameraPos += f*speed*dt;
	}
	if (keyDown[BACKWORD])
	{
		cameraPos -= f*speed*dt;
	}
	if (keyDown[LEFTMOVE])
	{
		cameraPos -= r*speed*dt;
	}
	if (keyDown[RIGHTMOVE])
	{
		cameraPos += r*speed*dt;
	}
	if (keyDown[UPMOVE])
	{
		cameraPos += u*speed*dt;
	}
	if (keyDown[DOWNMOVE])
	{
		cameraPos -= u*speed*dt;
	}

	glutPostRedisplay();
    //标记当前窗口需要重新绘制。通过glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板
}

void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		keyDown[UPMOVE] = true;
		break;
	case 's':
		keyDown[DOWNMOVE] = true;
		break;
	case 'a':
		keyDown[LEFTMOVE] = true;
		break;
	case 'd':
		keyDown[RIGHTMOVE] = true;
		break;
	case 'z':
		keyDown[FORWARD]=true;
		break;
	case 'c':
		keyDown[BACKWORD]=true;
		break;
	case 'r':
		objectRotating = true;//与旋转物体有关参数
		break;
	case 'k':  //生成一组随机RGB值，改变光源颜色
		diffuse[0] = rand() % 128 / 255.0 + 0.5;
		diffuse[1] = rand() % 128 / 255.0 + 0.5;
		diffuse[2] = rand() % 128 / 255.0 + 0.5;
		break;
	case 'e':
		isDrawTwoEyes=!isDrawTwoEyes;
		break;
	default:
		break;
	}
}


//判定键盘是否松开
void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		keyDown[UPMOVE] = false;
		break;
	case 's':
		keyDown[DOWNMOVE] = false;
		break;
	case 'a':
		keyDown[LEFTMOVE] = false;
		break;
	case 'd':
		keyDown[RIGHTMOVE] = false;
		break;
	case 'z':
		keyDown[FORWARD]=false;
		break;
	case 'c':
		keyDown[BACKWORD]=false;
		break;
	case 'r':
		objectRotating = false;
		break;
	default:
		break;
	}
}


void mouseMove(int x,int y){
	float dx=x-lastX; 
	float dy=y-lastY; 
	lastX=x; lastY=y;

	if(cameraMoving){
		float ratio = 0.1;
		vec3 r = normalize(cross(lookDir, up));
		up = normalize(cross(r, lookDir));

		mat4 rot = rotate(mat4(1.0f), radians(-dx*ratio), vec3(0,1,0));

		lookDir = normalize(vec3(rot*vec4(lookDir, 0)));
		up = normalize((vec3(rot*vec4(up, 0))));
		r = normalize((vec3(rot*vec4(r, 0))));

		//for(int i=0;i<3;i++){
		//	std::cout<<"up2"<<up[i]<<endl;
		//}

		rot = rotate(mat4(1.0f), radians(-dy*ratio), r);
		lookDir = normalize((vec3(rot*vec4(lookDir, 0))));
		up = normalize((vec3(rot*vec4(up, 0))));


	}
	else if(selectedIndex>=0){

		vec4 lastPos = projectionMat*viewMat*vec4(objects[selectedIndex].position, 1);
		float w = lastPos.w;
		lastPos /= lastPos.w;
		lastPos = lastPos*0.5f + 0.5f;

		vec3 destPos = vec3(float(x) / glutGet(GLUT_WINDOW_WIDTH), 1 - float(y) / glutGet(GLUT_WINDOW_HEIGHT), lastPos.z);
		destPos = destPos*2.0f - 1.0f;
		vec4 p = inverse(projectionMat*viewMat)*vec4(destPos*w, w);

		objects[selectedIndex].position = vec3(p);
		
	}
}


void mousePress(int button,int state,int x,int y){
	lastX=x; lastY=y;
	switch(button){
		case GLUT_LEFT_BUTTON:{
			if(state==GLUT_DOWN){
				selectedIndex=-1;
				// float minDis=1000;
				vec2 windowSize = { glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) };
				float minDis = 1000;

				for(int i=0;i<objects.size();i++){
				float dis=length(objects[i].screenPos(projectionMat,viewMat)-vec2(x,y));

					if (minDis > dis)
					{
						minDis = dis;
						if (minDis < 20)
						{
							selectedIndex = i;
						}
					}
				}
				//printf("selected:%d\n", selectedIndex);
			}
			break;
		}
		case GLUT_RIGHT_BUTTON:{
			selectedIndex=-1;
			cameraMoving=state==GLUT_DOWN;
			break;
		}

	}
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	int windowsHandle = glutCreateWindow("Virtual");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	
	glutMotionFunc(mouseMove);
	glutMouseFunc(mousePress);

	glEnable(GL_NORMALIZE);//启用法向量
	glEnable(GL_LIGHTING);//启用灯光源
	glEnable(GL_LIGHT0);//启用0号灯光源

	glClearColor(0.3, 0.3, 0.3, 1.0);//设置刷新时候的颜色值

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


	glEnable(GL_DEPTH_TEST);


	glDisable(GL_CULL_FACE);//关闭面剔除
	glEnable(GL_TEXTURE_2D);//开启纹理功能（二维纹理）
	floorTex = loadTexture("desk.jpg");//设置底板纹理

	initObject();
	eyeInit();

	glutMainLoop();
	return 0;
}
