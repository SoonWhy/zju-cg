// glutEx1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#define _CRT_SECURE_NO_WARNINGS

#if defined(WIN32)
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#pragma comment(lib, "glew32.lib")
#include <glew.h>
#include "glut.h"
#include "wglew.h"
#include "glew.h"
//#include "glxew.h"

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

#define BITMAP_ID 0x4D42
#define imageweight 64
#define imageheight 64

GLubyte image[imageheight][imageweight][3];

// texure ID
unsigned int texture[4];
int hu = 0;

int mode = 1;

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;					   // 文件指针
	BITMAPFILEHEADER bitmapFileHeader; // bitmap文件头
	unsigned char *bitmapImage;		   // bitmap图像数据
	int imageIdx = 0;				   // 图像位置索引
	unsigned char tempRGB;			   // 交换变量

	// 以“二进制+读”模式打开文件filename
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功
	if (!bitmapImage)
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据 error
	// fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	//  fread(bitmapImage,bitmapInfoHeader->biSizeImage,filePtr);
	//Size followed by number of items.That should work OK then!
	fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

	// std::cout<<bitmapImage<<std::endl;
	// std::cout<<bitmapInfoHeader;

	// 确认读入成功
	if (bitmapImage == NULL)
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}

void texload(int i, char *filename)
{

	BITMAPINFOHEADER bitmapInfoHeader; // bitmap信息头
	unsigned char *bitmapData;		   // 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D,
				 0,							//mipmap层次(通常为，表示最上层)
				 GL_RGB,					//我们希望该纹理有红、绿、蓝数据
				 bitmapInfoHeader.biWidth,  //纹理宽带，必须是n，若有边框+2
				 bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2
				 0,							//边框(0=无边框, 1=有边框)
				 GL_RGB,					//bitmap数据的格式
				 GL_UNSIGNED_BYTE,			//每个颜色数据的类型
				 bitmapData);				//bitmap数据指针
}

void makeImage()
{
	int i, j, c;
	for (i = 0; i < imageheight; i++)
	{
		for (j = 0; j < imageweight; j++)
		{
			c = ((i & 8) ^ (j & 8)) * 255;
			image[i][j][0] = (GLubyte)c;
			image[i][j][1] = (GLubyte)0;
			image[i][j][2] = (GLubyte)0;
		}
	}
}

void init()
{
	//todo
	glGenTextures(4, texture);

	texload(0, (char *)"Crack.bmp");
	texload(1, (char *)"Spot.bmp");
	texload(2, (char *)"id.bmp");

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ.
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, imageweight, imageheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);


	const GLubyte *extensions = glGetString(GL_EXTENSIONS);
	bool multiTexturingSupported = strstr((const char *)extensions, "GL_ARB_multitexture ") != NULL;

	GLint maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);
	printf("Texture Units available = %d\n", maxTextureUnits);

	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)wglGetProcAddress("glMultiTexCoord4fARB");
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}

//����Ⱦ����
void Texture_desk();
void Draw_Leg();

void Draw() // This function draws a triangle with RGB colors
{

	if (mode == 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glPushMatrix();
		// glTranslatef(0,0,1);
		glRotatef(90,1,0,0);
		glutSolidTeapot(1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glFlush();
	}
	else
	{
		
		//todo
		// define how to mix texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glPushMatrix();
		glTranslatef(0, 0, 3.5);
		glScalef(5, 4, 1);
		Texture_desk();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.5, 1, 1.5);
		Draw_Leg();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.5, 1, 1.5);
		Draw_Leg();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.5, -1, 1.5);
		Draw_Leg();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.5, -1, 1.5);
		Draw_Leg();
		glPopMatrix();
	}

}

void Texture_desk()
{
	//todo

	// if (mode == 2)
	// {
	// 	glPushMatrix();
		
	// 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// 	glEnable(GL_TEXTURE_2D);
	// 	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// 	// glutSolidCube(1);


	// 	// front and back
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(0.5f, 0.5f, 0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(-0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(-0.5f, 0.5f, 0.5f);
	// 	glEnd();
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(0.5f, 0.5f, -0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(0.5f, -0.5f, -0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(-0.5f, -0.5f, -0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(-0.5f, 0.5f, -0.5f);
	// 	glEnd();

	// 	// left and right
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(-0.5f, 0.5f, 0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(-0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(-0.5f, -0.5f, -0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(-0.5f, 0.5f, -0.5f);
	// 	glEnd();
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(0.5f, 0.5f, 0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(0.5f, -0.5f, -0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(0.5f, 0.5f, -0.5f);
	// 	glEnd();

	// 	// top and bottom
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(0.5f, 0.5f, -0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(0.5f, 0.5f, 0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(-0.5f, 0.5f, 0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(-0.5f, 0.5f, -0.5f);
	// 	glEnd();
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2i(1, 1);
	// 	glVertex3f(0.5f, -0.5f, -0.5f);
	// 	glTexCoord2i(1, 0);
	// 	glVertex3f(0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 0);
	// 	glVertex3f(-0.5f, -0.5f, 0.5f);
	// 	glTexCoord2i(0, 1);
	// 	glVertex3f(-0.5f, -0.5f, -0.5f);
	// 	glEnd();

	// 	glPopMatrix();

	// 	glDisable(GL_TEXTURE_2D);

	// 	glFlush();
	// }
	// // 	/*glEnable(GL_BLEND);
	// // 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	// // 	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	// //glEnable(GL_BLEND);
	// //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// else if (mode == 3)
	// {

		glPushMatrix();
		
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //设置纹理受光照影响
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		if(mode==3){		
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //设置纹理受光照影响
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
		}

		// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD_SIGNED);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_SUBTRACT);



		// front and back
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();

		// left and right
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();

		// top and bottom
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 1);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 1, 0);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 0);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glMultiTexCoord2fARB(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2fARB(GL_TEXTURE1, 0, 1);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glEnd();

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);

		glPopMatrix();

		glFlush();

		// glDisable(GL_BLEND);
	// }
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	Texture_desk();
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
	//todo
	case 'a':
	{ //todo, hint: eye[] and center[] are the keys to solve the problems
		eye[1] = eye[1] - 0.1;
		center[1] = center[1] - 0.1;
		break;
	}
	case 'd':
	{ //todo
		eye[0] = eye[0] + 0.1;
		center[0] = center[0] + 0.1;
		break;
	}
	case 'w':
	{
		eye[1] = eye[1] + 0.1;
		center[1] = center[1] + 0.1;
		break;
	}
	case 's':
	{ //todo
		eye[0] = eye[0] - 0.1;
		center[0] = center[0] - 0.1;
		break;
	}
	case 'z':
	{ //todo
		eye[2] = eye[2] - 0.1;
		//center[2] = center[2] - 0.5;
		break;
	}
	case 'c':
	{ //todo
		eye[2] = eye[2] + 0.1;
		break;
	}
	case '1':
	{
		mode = 1;
		break;
	}
	case '2':
	{
		mode = 2;
		break;
	}
	case '3':
	{
		mode = 3;
		break;
	}
	}
	updateView(wHeight, wWidth);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
			  center[0], center[1], center[2],
			  0, 1, 0); // ������0��0��0�����ӵ����� (0,5,50)��Y������

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

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0); // Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw();

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

	init();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
