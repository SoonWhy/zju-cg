#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL\glut.h>
#include "ScreenShot.h"

using namespace std;

#define HEADER_SIZE 18	// as TGA file
int num = 0;			// record # of screen shot

void TakeScreenshot()
{
	FILE *out_file;
	unsigned char *buffer;
	unsigned char temp;
	string filename = "screenshot_";
	string filetype = ".TGA";
	int w = 700;
	int h = 700;
	int buf_size = HEADER_SIZE + (w * h * 3);
	int i;
	

	// open file for output	
	string output = filename + to_string(num) + filetype;
	num++;
	if (!(out_file = fopen(output.c_str(), "wb")))
	{
		return;
	}

	// allocate mem to read from frame buf
	if (!(buffer = (unsigned char *)calloc(1, buf_size)))
	{
		return;
	}

	// set header info
	buffer[2] = 2;	// uncompressed
	buffer[12] = w & 255;
	buffer[13] = w >> 8;
	buffer[14] = h & 255;
	buffer[15] = h >> 8;
	buffer[16] = 24;	// 24 bits per pix

	// read frame buf
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, buffer + HEADER_SIZE);

	// RGB to BGR
	for (i = HEADER_SIZE; i < buf_size; i += 3)
	{
		temp = buffer[i];
		buffer[i] = buffer[i + 2];
		buffer[i + 2] = temp;
	}

	// write header + color buf to file
	fwrite(buffer, sizeof(unsigned char), buf_size, out_file);

	// cleanup
	fclose(out_file);
	free(buffer);
}