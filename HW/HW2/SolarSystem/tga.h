#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<cstdbool>
#include<cstring>
#include"glut.h"
#include<cstdio>
#include<cstdlib>

class texture{

public:
    GLuint width;
    GLuint height;
    GLuint format;
    GLubyte *data;

public:
    bool loadTga(const char *path);

};


GLuint loadTexture(const char * path);