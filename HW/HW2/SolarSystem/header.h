#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<cstdlib>
#include"glut.h"
#include<cmath>
#include"planet.h"
#include"tga.h"
#include"initialize.h"
#include"draw.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float eye[]={0,0,5};
float center[]={0,0,0};

bool isPlanetRun=true;
float timeFactor=1.0f;