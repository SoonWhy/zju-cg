#define _CRT_SECURE_NO_WARNINGS


#if defined(WIN32)
#  include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "glew32.lib") 
#include <glew.h>
#include "glut.h"
#include "wglew.h"
#include "glew.h"
using namespace std;

/*旋转角每次的累加量*/
double speed = 0.1;

/*每个视口里的图形旋转的角度*/
double rotate_left_up = 0;
double rotate_right_up = 0;
double rotate_left_down = 0;
double rotate_right_down = 0;



void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}
/*以画正方形为例*/
void draw_cube() {
	//绘制一个正方形
	//为了看上去比较美观，每个顶点我设置了不同颜色
	// glBegin(GL_POLYGON);
	// glColor3f(1.0, 0.0, 0.0);
	// glVertex2f(0.99, 0.99);
	// glColor3f(0.0, 1.0, 0.0);
	// glVertex2f(0.99, -0.99);
	// glColor3f(0.0, 0.0, 1.0);
	// glVertex2f(-0.99, -0.99);
	// glColor3f(1.0, 1.0, 0.0);
	// glVertex2f(-0.99, 0.99);
	// glEnd();
	//glPushMatrix();
	//glPushMatrix();
	//glTranslatef(0, 0, 4 + 0.8);
	//glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	////todo; hint: when operate the teapot, you may need to change some parameters
	//glRotatef(0, 0, 1.0, 0);
	//glutSolidTeapot(1);
	//glPopMatrix();


	//glPushMatrix();
	//glTranslatef(0, 0, 3.5);
	//glScalef(5, 4, 1);
	//glutSolidCube(1.0);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(1.5, 1, 1.5);
	//Draw_Leg();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-1.5, 1, 1.5);
	//Draw_Leg();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(1.5, -1, 1.5);
	//Draw_Leg();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-1.5, -1, 1.5);
	//Draw_Leg();
	//glPopMatrix();
	//glPopMatrix();
	glutWireCube(1);
	glTranslatef(1, 0, 0);
	glRotatef(30, 1, 0, 0);
	glutWireCube(2);

}

/*左上的视口*/
void port_left_up() {
	glViewport(0, 300, 300, 300);//创建原点在(0,300),宽高均为300的视口
	glLoadIdentity();
	glTranslatef(0.99, -0.99, 0);//移动坐标，这样整个图形就只有一部分会在这个视口里被看见
	glRotatef(rotate_left_up, 0, 0, 1);//绕z轴旋转
	draw_cube();//绘制正方形
	rotate_left_up += speed;//改变角度
	if (rotate_left_up == 360) {//角度累加到360时清空
		rotate_left_up = 0;
	}
}

/*左下的视口*/
void port_left_down() {
	glViewport(0, 0, 300, 300);//创建原点在(0,0),宽高均为300的视口
	glLoadIdentity();
	glTranslatef(0.99, 0.99, 0);//移动坐标，这样整个图形就只有一部分会在这个视口里被看见
	glRotatef(rotate_left_down, 0, 0, 1);//绕z轴旋转
	draw_cube();//绘制正方形
	rotate_left_down += speed;//改变角度
	if (rotate_left_down == 360) {//角度累加到360时清空
		rotate_left_down = 0;
	}
}

/*右上的视口*/
void port_right_up() {
	glViewport(300, 300, 300, 300);//创建原点在(300,300),宽高均为300的视口
	glLoadIdentity();
	glTranslatef(-0.99, -0.99, 0);//移动坐标，这样整个图形就只有一部分会在这个视口里被看见
	glRotatef(rotate_right_up, 0, 0, 1);//绕z轴旋转
	draw_cube();//绘制正方形
	rotate_right_up += speed;//改变角度
	if (rotate_right_up == 360) {//角度累加到360时清空
		rotate_right_up = 0;
	}
}

/*右下的视口*/
void port_right_down() {
	glViewport(300, 0, 300, 300);//创建原点在(300,0),宽高均为300的视口
	glLoadIdentity();
	glTranslatef(-0.99, 0.99, 0);//移动坐标，这样整个图形就只有一部分会在这个视口里被看见
	glRotatef(rotate_right_down, 0, 0, 1);//绕z轴旋转
	draw_cube();//绘制正方形
	rotate_right_down += speed;//改变角度
	if (rotate_right_down == 360) {//角度累加到360时清空
		rotate_right_down = 0;
	}
}

/*清晰起见，用白线区分四个视口*/
void draw_lines() {
	//画分割线，区分四个视口
	glViewport(0, 0, 600, 600);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);//线的颜色设置为白色   
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0);
	glVertex2f(1.0, 0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();
}

/*起绘制作用的函数，在glutDisplayFunc中调用*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glRotatef(0, 0, 1.0f, 0);			// Rotate around Y axis
	//glRotatef(-90, 1, 0, 0);
	//glScalef(0.2, 0.2, 0.2);
	//创建四个视口
	port_left_up();
	port_left_down();
	port_right_up();
	port_right_down();
	draw_lines();//画线区分
	glutSwapBuffers();//交换缓冲区，以显示图像
}

/*空闲时调用，用来重绘画面实现动画*/
void idle() {
	display();//重调display函数
}

/*必要的初始化*/
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*gluOrtho2D(-1.0, 1.0, -1.0, 1.0);*/
	//gluPerspective(45)
	
}

void reshape(int width,int height) {
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	
	gluPerspective(45.0f, whRatio, 0.5f,10.0f);
	//gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

/*主函数*/
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CG-HW3");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}