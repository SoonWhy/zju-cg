#include "glut.h"

#include<vector>
#include<cmath>
#include<map>
#include<iostream>
using namespace std;

#define PI 3.1415926
#define TORADIAN(x) (x*PI/180.0) 
float radianTheta = TORADIAN(30);
#define CSC(x) (1.0/sin(x))
#define COT(x) (1.0/tan(x))
float angleTheta = 359;


float fTranslate;
float fRotate;
float fScale = 1.0f; // set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool bHu = false;
bool bDesk = false;

int wHeight = 0;
int wWidth = 0;

vector<float> prefix;
vector<float> weight;
vector<pair<float,float>> controlP;
int pointNum;
float edge = 1.0f;
float radius;

float cni(int n,int index){
	float modu=1;
	float domi=1;

	for(int i=n;i>0;i--){
		modu *= i;
	}
	for(int i=index;i>0;i--){
		domi *= i;
	}

	return 1.0*modu/domi;
}

void init(){
	pointNum=11;
	for(int i=0;i<pointNum;i++){
		prefix.push_back(cni(pointNum-1,i));
		
	}

	// p3  p2  p1
	// p4      p0
	// p5  p6  p7
	// controlP.push_back(pair<float, float>(edge-0.2,0));		weight.push_back(0);
	// controlP.push_back(pair<float,float>(edge,0));			weight.push_back(1);
	// controlP.push_back(pair<float, float>(edge,edge));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(0,edge));			weight.push_back(1);
	// controlP.push_back(pair<float, float>(-edge,edge));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(-edge,0));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(-edge,-edge));	weight.push_back(1);
	// controlP.push_back(pair<float, float>(0,-edge));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(edge,-edge));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(edge, 0));		weight.push_back(1);
	// controlP.push_back(pair<float, float>(edge - 0.2, 0));	weight.push_back(0);
	controlP.push_back(pair<float, float>(-8 * edge, edge));	weight.push_back(1);
	controlP.push_back(pair<float, float>(-7 * edge, edge));	weight.push_back(0.2);
	controlP.push_back(pair<float, float>(-5*edge, edge));	weight.push_back(0.2);
	controlP.push_back(pair<float, float>(-3*edge, 1.5*edge));	weight.push_back(0.2);
	controlP.push_back(pair<float, float>(-2*edge, 2*edge));	weight.push_back(0.2);
	controlP.push_back(pair<float, float>(-edge, 3*edge));	weight.push_back(0.1);
	controlP.push_back(pair<float, float>(0, 3*edge));	weight.push_back(5);
	controlP.push_back(pair<float, float>(edge, 3*edge));	weight.push_back(1.5);
	controlP.push_back(pair<float, float>(2*edge, 2*edge));	weight.push_back(5);
	controlP.push_back(pair<float, float>(3*edge, edge));	weight.push_back(5);
	controlP.push_back(pair<float, float>(3*edge, 0));	weight.push_back(1);

	
}

pair<float, float> calPre(float t) {
	pair<float,float> mudu;
	mudu.first = 0;
	mudu.second = 0;
	float domi = 0;

	for (int i = 0; i < pointNum; i++) {
		float temp = prefix[i] * pow(t, i)*pow(1 - t, pointNum - i - 1)*weight[i];
		domi += temp;
		mudu.first += temp * controlP[i].first;
		mudu.second += temp * controlP[i].second;
	}

	mudu.first /= domi;
	mudu.second /= domi;

	//cout <<"normal " <<mudu.first<<", " << mudu.second << endl;

	return mudu;

}

void drawPoint() {
	
	glColor3f(0.0f, 255.0f, 0.0f);
	for (int i = 0; i < pointNum; i++) {
		glBegin(GL_QUADS);

		glVertex3f(controlP[i].first+0.01, controlP[i].second+0.01, 0);
		glVertex3f(controlP[i].first+0.01, controlP[i].second-0.01, 0);
		glVertex3f(controlP[i].first-0.01, controlP[i].second-0.01, 0);
		glVertex3f(controlP[i].first-0.01, controlP[i].second+0.01, 0);

		glEnd();
	}
	

}

void drawLine() {
	
	glColor3f(0.0f, 0.0f, 255.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pointNum; i++) {
		glVertex3f(controlP[i].first, controlP[i].second, 0.0f);
	}
	glEnd();
}


vector<pair<float, float>> temp;

void circleInit() {
		
	for (float t = 0; t <= 1; t += 0.01) {
		temp.push_back(calPre(t));
	}

}

void drawCirc(){

	glColor3f(255.0f, 255.0f, 255.0f);
	glBegin(GL_LINE_STRIP);
	
	//for(float t=0;t<=1;t+=0.01){
	//	pair<float, float> temp = calPre(t);
	//	glVertex3f(temp.first, temp.second, 0.0f);
	//}
	for (long int i = 0; i < temp.size(); i++) {
		glVertex3f(temp[i].first, temp[i].second, 0.0f);
	}


	glEnd();

	//glColor3f(255.0f, 0, 0);
	glBegin(GL_LINE_STRIP);

	//for (float t = 0; t <= 1; t += 0.01) {
	//	pair<float, float> temp = calPre(t);
	//	glVertex3f(temp.first, -temp.second, 0.0f);
	//}
	for (long int i = 0; i < temp.size(); i++) {
		glVertex3f(temp[i].first, temp[i].second, 0.0f);
	}
	glEnd();
}

float lineStep = 0.7;

void finalDraw() {

	circleInit();
	for (float i = 0; i <= 361; i += lineStep) {
		glPushMatrix();
		glRotatef(i,1.0, 0.0, 0.0f);
		drawPoint();
		//drawLine();
		drawCirc();
		glPopMatrix();
		//cout << "angle: " << i << endl;
	}

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

float eye[] = { 0, 0, 25 };
float center[] = { 0, 0, 0 };

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
		eye[2] = eye[2] - 0.3;
		//center[2] = center[2] - 0.5;
		break;
	}
	case 'c':
	{ //todo
		eye[2] = eye[2] + 0.3;
		break;
	}
	case '+':
	{
		if(lineStep>0.2){
			lineStep -= 0.5;
		}
		break;
	}
	case '-':
	{
		if (lineStep < 180) {
			lineStep += 0.5;
		}
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
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);


	finalDraw();

	if (bAnim)
		fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 640);  
	int windowHandle
		= glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	init();

	glutMainLoop();

	return 0;
}


