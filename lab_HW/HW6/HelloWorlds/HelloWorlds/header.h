#pragma once
#include"glm/glm.hpp"
#include"glut.h"

using namespace glm;



#define FORWARD 0
#define BACKWORD 1
#define LEFTMOVE 2
#define RIGHTMOVE 3
#define UPMOVE 4
#define DOWNMOVE 5

#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)

//设置与光源有关的初始参数，
float lightPos1[] = { 0, 5, 0, 1 };//光源位置
float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
float diffuse[] = { 1, 1, 1, 1.0 };//散射光参数
float specular[] = { 1, 1, 1, 1.0 };//镜面光参数

vec3 cameraPos = { 0,10,-10 };//设定摄像机位置
vec3 lookDir = {0,-1,1};//设定摄像机旋转
vec3 up = {0,1,0};//定义上向量


GLuint floorTex = 0;//读取floor.jpg


int lastX = 0, lastY = 0;
float rotateX = 0, rotateY = 0;//X,Y方向旋转参数（绕Z轴旋转）

bool keyDown[] = {false,false,false ,false,false,false };//设置wsad初始状态，keydown=true表示被按下

mat4 projectionMat;//定义位置矩阵-四维
mat4 viewMat;//定义观察矩阵--四维

int selectedIndex = -1;
bool cameraMoving = false;
bool objectRotating = false;

float yaw=0;
float pitch=0;

float flyYAngle=0;
float flyXZAngle=0;
vec3 flyXZAxis;