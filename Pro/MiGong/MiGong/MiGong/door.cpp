#include <GL\glut.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "door.h"

using namespace std;
GLfloat step=0.0,s=0.1,move[]={0,0,0};

#define BMP_Header_Length 54
int power_of_two(int n)
{
    if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}

GLuint obj3dmodel::load_texture_obj(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID=0, texture_ID = 0;

    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
        return 0;

    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);

    {
        GLint line_bytes = width * 3;
        while( line_bytes % 4 != 0 )
            ++line_bytes;
        total_bytes = line_bytes * height;
    }
    

    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }
    

    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    

    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if( !power_of_two(width)
           || !power_of_two(height)
           || width > max
           || height > max )
        {
            const GLint new_width = 256;
            const GLint new_height = 256;
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            

            new_line_bytes = new_width * 3;
            while( new_line_bytes % 4 != 0 )
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            

            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if( new_pixels == 0 )
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }
            
    
            gluScaleImage(GL_RGB,
                          width, height, GL_UNSIGNED_BYTE, pixels,
                          new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
            

            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }
    

    glGenTextures(1, &texture_ID);
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    GLint lastTextureID=last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
    free(pixels);
    return texture_ID;
}


void obj3dmodel::parse(const char *filename){
    string s;
    string str;
    ifstream fin(filename);
    if(!fin){
        cout << "Can't open the file.";
        return;
        
    }
    while(getline(fin, str)){
        if (str.substr(0,2)=="vt"){
            texture t;
            istringstream vtdata(str.substr(3));
            vtdata>>t.x>>t.y;
            this->textures.push_back(t);
        }
        else if (str.substr(0,1)=="f"){
            face f;
            int k;
            for(k=0;k<str.length();k++){
                if (str[k]=='/')
                    str[k]=' ';
            }
            //cout<<str<<endl;
            istringstream fdata(str.substr(2));
            fdata>>f.v1>>f.t1>>f.v2>>f.t2>>f.v3>>f.t3;
            //cout<<f.v1<<" "<<f.v2<<" "<<f.v3<<endl;
            //cout<<f.t1<<" "<<f.t2<<" "<<f.t3<<endl;
            faces.push_back(f);
            countf++;
        }
        else if (str.substr(0,1)=="v"){
            vertex v;
            istringstream vdata(str.substr(2));
            vdata>>v.x>>v.y>>v.z;
            //cout<<v.x<<" "<<v.y<<" "<<v.z<<endl;
            this->vertexs.push_back(v);
        }
        else{}
    }
}


void obj3dmodel::draw(){

    int i;
    for(i=0;i<countf;i++){
        vertex v1=vertexs[faces[i].v1-1];
        vertex v2=vertexs[faces[i].v2-1];
        vertex v3=vertexs[faces[i].v3-1];
        texture t1=textures[faces[i].t1-1];
        texture t2=textures[faces[i].t2-1];
        texture t3=textures[faces[i].t3-1];
        glBindTexture(GL_TEXTURE_2D, tex);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);

        glTexCoord2f(t1.x,t1.y);
        glVertex3f(v1.x,v1.y,v1.z);
        glTexCoord2f(t2.x,t2.y);
        glVertex3f(v2.x,v2.y,v2.z);
        glTexCoord2f(t3.x,t3.y);
        glVertex3f(v3.x,v3.y,v3.z);
        glEnd();
    }
}
