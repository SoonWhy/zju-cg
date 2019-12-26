#pragma once

#include <iostream>
#include <GL\glut.h>
#include <time.h>
#include "HERO.h"

extern "C" {
#include"glm.h"
}

extern GLMmodel* model;




GLuint TexHeroHead[5];	// for the texture of Hero
GLuint TexHeroCloth[2];
GLuint TexHeroArm[3];
GLuint TexHeroLeg[3];

GLuint TexNPCHead[5];	// for the texture of NPC
GLuint TexNPCCloth[2];
GLuint TexNPCArm[3];
GLuint TexNPCLeg[3];

//====================>> NPC's attributes
float npc_move_x = 0;
float npc_move_y = 0;
float npc_move_z = 0;
float npc_turn = 0;
bool npc_shoot_pos = false;

float npc_velocity_z, npc_velocity_xy;
float npc_gravity;
float npc_t;
bool npc_jump = false;

bool npc_walk = false;
bool npc_step = false;

float npc_step_len = 2.0;

//=================================> DrawCube
const GLfloat x1 = -0.5, x2 = 0.5;
const GLfloat Y1 = -0.5, y2 = 0.5;
const GLfloat z1 = -0.5, z2 = 0.5;

int dir[4][2] = { {0,0},{1,0},{1,1},{0,1} };
//指定六个面的四个顶点，每个顶点用3个坐标值表示  
GLfloat point[6][4][3] = {
	{ { x1,Y1,z1 },{ x2,Y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },
	{ { x1,Y1,z1 },{ x2,Y1,z1 },{ x2,Y1,z2 },{ x1,Y1,z2 } },
	{ { x2,Y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,Y1,z2 } },
	{ { x1,Y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,Y1,z2 } },
	{ { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },
	{ { x1,Y1,z2 },{ x2,Y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }
};

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE* filePtr;	// 恅璃硌渀
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap恅璃芛
	unsigned char	*bitmapImage;		// bitmap芞砉杅擂
	int	imageIdx = 0;					// 芞砉弇离坰竘
	unsigned char	tempRGB;			// 蝠遙曹講

	// 眕※媼輛秶+黍§耀宒湖羲恅璃filename 
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) return NULL;
	// 黍bitmap恅璃芞
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 桄痐岆瘁峈bitmap恅璃
	//if (bitmapFileHeader.bfType != BITMAP_ID) {
	//	fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
	//	return NULL;
	//}

	// 黍bitmap陓洘芛
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 蔚恅璃硌渀痄祫bitmap杅擂
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 峈蚾婥芞砉杅擂斐膘逋劂腔囀湔
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 桄痐囀湔岆瘁斐膘傖髡
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 黍bitmap芞砉杅擂
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 黍傖髡
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//蚕衾bitmap笢悵湔腔跡宒岆BGRㄛ狟醱蝠遙R睿B腔硉ㄛ腕善RGB跡宒
	for (imageIdx = 0;
		imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 壽敕bitmap芞砉恅璃
	fclose(filePtr);
	return bitmapImage;
}

void texload(int i, char *filename, GLuint texture[])
{

	BITMAPINFOHEADER bitmapInfoHeader;		// bitmap陓洘芛
	unsigned char*   bitmapData;            // 恇燴杅擂

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 硌隅絞恇燴腔溫湮/坫苤徹薦源宒
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 							//mipmap脯棒(籵都峈ㄛ桶尨郔奻脯) 
		GL_RGB,						//扂蠅洷咡蜆恇燴衄綻﹜蟯﹜懦杅擂
		bitmapInfoHeader.biWidth,	//恇燴遵湍ㄛ斛剕岆nㄛ衄晚遺+2 
		bitmapInfoHeader.biHeight,	//恇燴詢僅ㄛ斛剕岆nㄛ衄晚遺+2 
		0,							//晚遺(0=拸晚遺, 1=衄晚遺) 
		GL_RGB,						//bitmap杅擂腔跡宒
		GL_UNSIGNED_BYTE,			//藩跺晇伎杅擂腔濬倰
		bitmapData);				//bitmap杅擂硌渀  
}


//煦饜恇燴輛杅郪
void inittexture() 
{
	//=============================(Hero)================================
	glGenTextures(5, TexHeroHead);	// 菴珨統杅岆剒猁汜傖梓尨睫腔跺杅, 菴媼統杅岆殿隙梓尨睫腔杅郪
	texload(0, (char*)"face_1.bmp", TexHeroHead);
	texload(1, (char*)"head_1_top.bmp", TexHeroHead);
	texload(2, (char*)"head_1_side.bmp", TexHeroHead);
	texload(3, (char*)"head_1_back.bmp", TexHeroHead);
	texload(4, (char*)"head_1_bottom.bmp", TexHeroHead);

	glGenTextures(2, TexHeroCloth);
	texload(0, (char*)"cloth_1_front.bmp", TexHeroCloth);
	texload(1, (char*)"cloth_1_side.bmp", TexHeroCloth);

	glGenTextures(3, TexHeroArm);
	texload(0, (char*)"arm_1_side.bmp", TexHeroArm);
	texload(1, (char*)"arm_1_top.bmp", TexHeroArm);
	texload(2, (char*)"arm_1_bottom.bmp", TexHeroArm);

	glGenTextures(3, TexHeroLeg);
	texload(0, (char*)"leg_1_side.bmp", TexHeroLeg);
	texload(1, (char*)"leg_1_top.bmp", TexHeroLeg);
	texload(2, (char*)"leg_1_bottom.bmp", TexHeroLeg);

	//=============================(NPC)================================
	glGenTextures(5, TexNPCHead);
	texload(0, (char*)"face_2.bmp", TexNPCHead);
	texload(1, (char*)"head_2_top.bmp", TexNPCHead);
	texload(2, (char*)"head_2_side.bmp", TexNPCHead);
	texload(3, (char*)"head_2_back.bmp", TexNPCHead);
	texload(4, (char*)"head_2_bottom.bmp", TexNPCHead);

	glGenTextures(2, TexNPCCloth);
	texload(0, (char*)"cloth_2_front.bmp", TexNPCCloth);
	texload(1, (char*)"cloth_1_side.bmp", TexNPCCloth);

	glGenTextures(3, TexNPCArm);
	texload(0, (char*)"arm_2_side.bmp", TexNPCArm);
	texload(1, (char*)"arm_1_top.bmp", TexNPCArm);
	texload(2, (char*)"arm_2_bottom.bmp", TexNPCArm);

	glGenTextures(3, TexNPCLeg);
	texload(0, (char*)"leg_1_side.bmp", TexNPCLeg);
	texload(1, (char*)"leg_1_top.bmp", TexNPCLeg);
	texload(2, (char*)"leg_1_bottom.bmp", TexNPCLeg);


}

void drawBottomCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[0][j]);
	}
	glEnd();

}

void drawBackCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[1][j]);
	}
	glEnd();

}

void drawRightCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[2][j]);
	}
	glEnd();

}

void drawLeftCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[3][j]);
	}
	glEnd();

}

void drawFrontCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[4][j]);
	}
	glEnd();

}

void drawTopCube()
{
	int j;
	glBegin(GL_QUADS);
	for (j = 0; j < 4; j++) {
		glTexCoord2iv(dir[j]);
		glVertex3fv(point[5][j]);
	}
	glEnd();
}

void Draw_Hero() // This function draws Hero in the game
{
	int i;
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();



	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	glEnable(GL_LIGHTING);

	GLfloat light_position[] = { 14.0, 14.0, 14.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT5, GL_POSITION, light_position);
	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);

	//glEnable(GL_DEPTH_TEST);
	glTranslatef(2.0f, 0, 0);
	glPushMatrix();
	glRotatef(180, 0, 0, 1);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(10, 10, 10);
	//glmScale(model, 1.1);
	//glEnable(GL_LIGHT5);
	glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);
	//glDisable(GL_LIGHT5);
	glPopMatrix();
	glPopMatrix();


glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Control_Hero() {
	//load_glm();
	glPushMatrix();
	glTranslatef(0, 0, 0);	// move forward or backword
	glRotatef(-90, 0, 0, 1);
	glScalef(0.025, 0.025, 0.025);
	//glRotatef(turn, 0, 0, -1);				// turn right or left
	glTranslatef(-4.5f, -4.5f, 19.5f);		// place the hero at center
	
	Draw_Hero();						// Draw Hero
	glPopMatrix();
}

void Draw_NPC() {
	int i;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置纹理受光照影响
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	glEnable(GL_LIGHTING);

	GLfloat light_position[] = { 4.0, 4.0, 0.0, 0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT5, GL_POSITION, light_position);
	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);

	glEnable(GL_DEPTH_TEST);
	glScalef(0.5, 0.5, 0.5);
	//glmScale(model, 1.1);
	glEnable(GL_LIGHT5);
	glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);
	glDisable(GL_LIGHT5);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Control_NPC() {
	//load_glm();
	glPushMatrix();
	//glTranslatef(30.0f, -4.5f, 0.0f);					// place the npc
	//glTranslatef(npc_move_x, npc_move_y, npc_move_z);	// move forward or backword
	//glRotatef(npc_turn, 0, 0, -1);						// turn right or left
	glRotatef(-90, 0, 0, 1);
	glScalef(0.025, 0.025, 0.025);
	glTranslatef(-4.5f, -4.5f, 19.5f);					// place the npc at center
	
	Draw_NPC();		// Draw NPC
	glPopMatrix();
}