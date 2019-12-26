#include <iostream>
#include <GL\glut.h>
#include <time.h>
#include "HERO.h"
#include "ScreenShot.h"
#include "Cloud.h"
#include "door.h"

extern "C" {
#include"glm.h"
}

GLMmodel* model = NULL;
void load_glm() {
	model = glmReadOBJ("data/al.obj");
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90);
}

using namespace std;

obj3dmodel obj;
GLint boxList;

double eyeX = 0, eyeY = 0, eyeZ = 15;
double centerX = 0, centerY = 0, centerZ = 0;
double upX = 0, upY = 1, upZ = 0;
double centerchanX = 0, centerchanY = 0, centerchanZ = 0;
//double upchanX=0,upchanY=0,upchanZ=0;//���岢��ʼ������ƶ��ı�glulookat���������仯��

//�����ʼ����
int HERO[4] = { 4 , -14 ,-20 , 0 };//x,y,z,����(��0 ��1 ��2 ��3)

int NPC1[4] = { 0 , 0 , -20 , 0 };
bool NPC1_alive = true;
int NPC2[4] = { -11 , 9 , -20 , 0 };
bool NPC2_alive = true;
int NPC3[4] = { 4 , 7 , -20 , 0 };
bool NPC3_alive = true;
int NPC4[4] = { -8 , -11 , -20 , 0 };
bool NPC4_alive = true;

double Bullet[4];
bool fireornot = false;
float firespeed = 0.1f;
bool bullet_dir_cannotchange = true;

int view = 3;

int MAP[900];//30*30�ĵ�ͼ

GLuint texWall;

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;
GLuint texture_id[100];

///////////////////////////////////////////////////////////////////////
//̫���ĽǶ�
GLfloat sun_angle = 0.0f;
double pi = atan(1) * 4;

void DrawCube(double x, double y, double z, int textid);

bool gameover_flag = false;
float up = 0.0;
void gameover() {
	if (gameover_flag == true) {
		if (up < 15) {
			up += 0.01;
		}
		glPushMatrix();
		glScalef(10, 3, 3);
		DrawCube(0, -15 + up, -1, 2);
		glPopMatrix();
	}
}

bool youwin_flag = false;
float down = 0.0;
void youwin() {
	if (youwin_flag == true) {
		if (down < 15) {
			down += 0.01;
		}
		glPushMatrix();
		glScalef(10, 3, 3);
		DrawCube(0, 15 - down, -1, 3);
		glPopMatrix();
	}
}

//��������
void DrawHERO() {

	glPushMatrix();
	glTranslatef(HERO[0], HERO[1], -20);

	switch (HERO[3])
	{
	case 0://up
		glRotatef(90, 0, 0, 1);
		break;
	case 1://left
		glRotatef(180, 0, 0, 1);
		break;
	case 2://down
		glRotatef(-90, 0, 0, 1);
		break;
	case 3://right
		break;
	default:
		break;
	}

	Control_Hero();
	glPopMatrix();
}

void DrawNPC( int* NPC , int NPC_alive) {
	if (NPC_alive) {
		glPushMatrix();
		glTranslatef(NPC[0], NPC[1], -20);

		switch (NPC[3])
		{
		case 0://up
			glRotatef(90, 0, 0, 1);
			break;
		case 1://left
			glRotatef(180, 0, 0, 1);
			break;
		case 2://down
			glRotatef(-90, 0, 0, 1);
			break;
		case 3://right
			break;
		default:
			break;
		}

		Control_NPC();
		glPopMatrix();
	}
}

//װ���������texture_id[i]����
void loadTexture(int i, char* filename) {
	FILE* pfile = fopen(filename, "rb");
	if (pfile == 0) {
		cout << "can not open" << filename << endl;
	}
	//��ȡͼ���С
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	//�����������ݳ���
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;
	//��ȡ��������
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	glBindTexture(GL_TEXTURE_2D, texture_id[i]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth, imageheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

}
//����һ����ʾ֮ǰ����Щ��������Ϊ����ά��ͼ׼����
//��һ��С��򲢰�texture_id[0]�������ã�0��������ǽ��
void DrawCube(double x, double y, double z , int textid) {

	glPushMatrix();
	glTranslatef(x, y, z);

	glBindTexture(GL_TEXTURE_2D, texture_id[textid]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);    //����  
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);    //����  
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS);    //ǰ��  
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);    //����  
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS);    //����  
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);    //����  
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	glPopMatrix();
}

int crash() {

	int bulletX = Bullet[0] + 15;
	int bulletY = Bullet[1] + 14;
	if (MAP[bulletY * 30 + bulletX] == 1) {
		return 1;
	}
	else {
		if (fabs(Bullet[0] - NPC1[0]) < 0.1 &&  fabs(Bullet[1] - NPC1[1]) < 0.1 && NPC1_alive == true) {
			NPC1_alive = false;
			return 1;
		}

		if (fabs(Bullet[0] - NPC2[0]) < 0.1 &&  fabs(Bullet[1] - NPC2[1]) < 0.1 && NPC2_alive == true) {
			NPC2_alive = false;
			return 1;
		}

		if (fabs(Bullet[0] - NPC3[0]) < 0.1 &&  fabs(Bullet[1] - NPC3[1]) < 0.1 && NPC3_alive == true) {
			NPC3_alive = false;
			return 1;
		}

		if (fabs(Bullet[0] - NPC4[0]) < 0.1 &&  fabs(Bullet[1] - NPC4[1]) < 0.1 && NPC4_alive == true) {
			NPC4_alive = false;
			return 1;
		}
	}
	return 0;
}

void Bulletmodel(double x, double y, double z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();
}


//����ƶ��ı��ӽǵĺ���
bool fmouse = false;//������ģʽ����/�ر�״̬
int lastX = 350, lastY = 350;//��¼��һ�����λ��
float PI = 3.1415;
float radX = 0, radY = 0;
void mouse(int x, int y) {
	if (fmouse) {
		//glutSetCursor(GLUT_CURSOR_NONE);//�������ĺ���
		int chanX = 0, chanY = 0;
		chanX = x - lastX;
		chanY = y - lastY;
		switch (HERO[3]) {
		case 0://up
			radX += float(PI*chanX / 180.0f);
			radY += float(PI*chanY / 180.0f);
			centerchanX = float(7 * sin(0.3*radX));
			centerchanY = float(7 * cos(0.3*radX));
			centerchanZ = float(7 * sin(0.3*radY) - 4);
			lastX = x; lastY = y;
			break;
		case 1://left
			radX += float(PI*chanX / 180.0f);
			radY += float(PI*chanY / 180.0f);
			centerchanX = float(7 * cos(0.3*radX)*(-1));
			centerchanY = float(7 * sin(0.3*radX));
			centerchanZ = float(7 * sin(0.3*radY) - 4);
			lastX = x; lastY = y;
			break;
		case 2://down
			radX += float(PI*chanX / 180.0f);
			radY += float(PI*chanY / 180.0f);
			centerchanX = float(7 * sin(0.3*radX)*(-1));
			centerchanY = float(7 * cos(0.3*radX)*(-1));
			centerchanZ = float(7 * sin(0.3*radY) - 4);
			lastX = x; lastY = y;
			break;
		case 3://right
			radX += float(PI*chanX / 180.0f);
			radY += float(PI*chanY / 180.0f);
			centerchanX = float(7 * cos(0.3*radX));
			centerchanY = float(7 * sin(0.3*radX)*(-1));
			centerchanZ = float(7 * sin(0.3*radY) - 4);
			lastX = x; lastY = y;
			break;
		default:
			break;
		}

	}
}

//����
void DrawBullet() {
	
	if (fireornot == true) {
		
		if (bullet_dir_cannotchange == true) {
			Bullet[0] = HERO[0];
			Bullet[1] = HERO[1];
			Bullet[2] = HERO[2];
			Bullet[3] = HERO[3];
			bullet_dir_cannotchange = false;
		}

		if (Bullet[3] < 0.1 && Bullet[3] > -0.1) {
			Bulletmodel(Bullet[0], Bullet[1] + firespeed, Bullet[2]);
			if (crash() == 0) {
				Bullet[1] += firespeed;
			}
			else {
				bullet_dir_cannotchange = true;
				fireornot = false;
			}
		}
		else if (Bullet[3] < 1.1 && Bullet[3] > 0.9) {
			Bulletmodel(Bullet[0] - firespeed, Bullet[1], Bullet[2]);
			if (crash() == 0) {
				Bullet[0] -= firespeed;
			}
			else {
				bullet_dir_cannotchange = true;
				fireornot = false;
			}
		}
		else if (Bullet[3] < 2.1 && Bullet[3] > 1.9) {
			Bulletmodel(Bullet[0], Bullet[1] - firespeed, Bullet[2]);
			if (crash() == 0) {
				Bullet[1] -= firespeed;
			}
			else {
				bullet_dir_cannotchange = true;
				fireornot = false;
			}
		}
		else if (Bullet[3] < 3.1 && Bullet[3] > 2.9) {
			Bulletmodel(Bullet[0] + firespeed, Bullet[1], Bullet[2]);
			if (crash() == 0) {
				Bullet[0] += firespeed;
			}
			else {
				bullet_dir_cannotchange = true;
				fireornot = false;
			}
		}
	}


}

//����ͼ
void DrawMAP() {
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, 700, 700);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);//���п���

	glViewport(50, 50, 600, 600);

	//////////////////////////////////////////////////////////////////////
	//glDisable(GL_LIGHT1);
	//glEnable(GL_LIGHT0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//��������ģʽ
	glEnable(GL_LIGHTING);
	//�۹��,1Ϊ̫����2Ϊͷ�����µĹ⣬3Ϊ����ǰ���Ĺ�

	//���徵�����������ɫ
	GLfloat white1[] = { 1.0,1.0, 1.0, 1.0 };
	GLfloat white2[] = { 1.0,1.0, 1.0, 1.0 };
	GLfloat white3[] = { 1.0,1.0, 1.0, 1.0 };
	//����۹��λ��
	GLfloat spot1_pos[] = { -70 * cos(sun_angle*pi / 180),0.0f,70 * sin(sun_angle*pi / 180) - 20,1.0f };
	//����������������������������������������������������������������������������������������������
	GLfloat spot2_pos[] = { HERO[0],HERO[1],HERO[2] + 12,1.0f };//12Ϊ����ͷ���߶�,Ҫ��
	//������������������������������������������������������������������������������������������
	GLfloat spot3_pos[] = { HERO[0],HERO[1],HERO[2] + 0.2,1.0f };//10Ϊ�����ͷ�߶ȣ�Ҫ��
	//����۹�����䷽��
	GLfloat spot1_angle[] = { 70 * cos(sun_angle*pi / 180),0.0f,-70 * sin(sun_angle*pi / 180) + 20 };
	GLfloat spot2_angle[] = { 0.0f,0.0f,-1.0f };
	GLfloat spot3_angle[] = { 0.0f,0.0f,0.0f };
	//�۹�ƽǶ�,���۹�ƹ�Ȧ��С
	GLfloat Angle1 = 50.0f;
	GLfloat Angle2 = 5.0f;
	GLfloat Angle3 = 5.0f;
	//���廷������ɫ
	GLfloat color1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color2[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color3[] = { 1.0,1.0,1.0,1.0 };

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//��������ģʽ
	glEnable(GL_LIGHTING);

	//1�ž۹�ƣ�̫��

	//���û�����ɷ�
	glLightfv(GL_LIGHT1, GL_AMBIENT, color1);
	//���þ����ɷ�
	glLightfv(GL_LIGHT1, GL_SPECULAR, white1);
	//���������ɷ�
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white1);
	//�۹��λ��
	glLightfv(GL_LIGHT1, GL_POSITION, spot1_pos);
	//�ü��Ƕ�
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, Angle1);
	//��Դ����
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot1_angle);
	//�ۼ���
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.);
	//����1�Ź�Դ
	glEnable(GL_LIGHT1);

	//̫���Ƕȸ���
	sun_angle += 0.05;

	//2�ţ������Ϸ����µľ۹��

	//���û�����ɷ�
	glLightfv(GL_LIGHT2, GL_AMBIENT, color2);
	//���þ����ɷ�
	glLightfv(GL_LIGHT2, GL_SPECULAR, white2);
	//���������ɷ�
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white2);
	//�۹��λ��
	glLightfv(GL_LIGHT2, GL_POSITION, spot2_pos);
	//�ü��Ƕ�
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, Angle2);
	//��Դ����
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot2_angle);
	//�ۼ���
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5);
	//����2�Ź�Դ
	//(GL_LIGHT2);

	//3�ţ���������ľ۹��

	//x,y,z,����(��0 ��1 ��2 ��3)
	if (HERO[3] == 0) spot3_angle[1] = 1.0f;
	if (HERO[3] == 1) spot3_angle[0] = -1.0f;
	if (HERO[3] == 2) spot3_angle[1] = -1.0f;
	if (HERO[3] == 3) spot3_angle[0] = 1.0f;
	//���û�����ɷ�
	glLightfv(GL_LIGHT3, GL_AMBIENT, color3);
	//���þ����ɷ�
	glLightfv(GL_LIGHT3, GL_SPECULAR, white3);
	//���������ɷ�
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white3);
	//�۹��λ��
	glLightfv(GL_LIGHT3, GL_POSITION, spot3_pos);
	//�ü��Ƕ�
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, Angle3);
	//��Դ����
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_angle);
	//�ۼ���
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10);
	//����3�Ź�Դ
	glEnable(GL_LIGHT3);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�ص�����
	gluPerspective(50, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ, centerX + centerchanX, centerY + centerchanY, centerZ + centerchanZ, upX, upY, upZ);

	//����ά��ͼ
	glPushMatrix();
	glTranslatef(-15, -14, 0);
	for (int i = 0; i < 900; i++) {
		if (MAP[i] == 1 || MAP[i] == -1) {

			DrawCube(i - i / 30 * 30, i / 30, -20 ,0);
		}

	}
	glPopMatrix();
	//���ذ�

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);//һ�������ǵذ�
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(14, 15, -20.5);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-15, 15, -20.5);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(-15, -14.9, -20.5);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(14, -14.9, -20.5);
	glEnd();
	glPopMatrix();
}

//��һ��������
void DrawSquare(int x, int y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glEnd();
	glPopMatrix();
}

//��ά������������һ����ɫ�������α�ʾ
void Draw2DHERO(int x, int y, int head) {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(x, y, 0);
	switch (head)
	{
	case 0://up
		glBegin(GL_POLYGON);
		glVertex2f(0.1, 0.1);
		glVertex2f(0.9, 0.1);
		glVertex2f(0.5, 0.9);
		glEnd();
		break;
	case 1://left
		glBegin(GL_POLYGON);
		glVertex2f(0.1, 0.5);
		glVertex2f(0.9, 0.1);
		glVertex2f(0.9, 0.9);
		glEnd();
		break;
	case 2://down
		glBegin(GL_POLYGON);
		glVertex2f(0.5, 0.1);
		glVertex2f(0.9, 0.9);
		glVertex2f(0.1, 0.9);
		glEnd();
		break;
	case 3://right
		glBegin(GL_POLYGON);
		glVertex2f(0.9, 0.5);
		glVertex2f(0.1, 0.9);
		glVertex2f(0.1, 0.1);
		glEnd();
		break;
	default:
		break;
	}
	glPopMatrix();
}

//��ά�ĵ�ͼ
void Draw2DMAP() {

	glEnable(GL_SCISSOR_TEST);
	glScissor(450, 0, 250, 250);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	glViewport(450, 0, 250, 250);
	//////////////////////////////////////////////////////////
	//glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluOrtho2D(0, 31, 0, 31);
	//�����
	Draw2DHERO(HERO[0] + 15, HERO[1] + 14, HERO[3]);

	//����ά��ͼ
	for (int i = 0; i < 900; i++) {
		//if (MAP[i] == 1){
		//	glColor3f(0, 0, 0);
		//	DrawSquare(i - i / 30 * 30,i / 30);
		//}
		if (MAP[i] == -1) {
			glColor3f(0, 0, 0);
			DrawSquare(i - i / 30 * 30, i / 30);
		}
	}


}

GLint GenboxList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	obj.draw();

	glEndList();

	//glNewList(lid + 1, GL_COMPILE);

	//DrawBunny();

	//glEndList();
	return lid;
}

void display() {

	DrawMAP();
	gameover();
	youwin();
	ControlCloud(0, 0 ,-15);
	ControlCloud(5, 10, -15);
	ControlCloud(-6, 5, -15);
	ControlCloud(-10, -8, -15);
	ControlCloud(3, -5, -15);

	{
		glPushMatrix();
		glTranslatef(5, 12.5, -15);
		//glScalef(0.2, 0.2, 0.2);
		//glRotatef(89, 0, 0, 0);
		glCallList(boxList);
		glPopMatrix();
	}


	if (view == 1) {

		Draw2DMAP();
		DrawNPC(NPC1, NPC1_alive);
		DrawNPC(NPC2, NPC2_alive);
		DrawNPC(NPC3, NPC3_alive);
		DrawNPC(NPC4, NPC4_alive);
		DrawBullet();
	}
	else if (view == 2) {
		DrawHERO();
		DrawNPC(NPC1, NPC1_alive);
		DrawNPC(NPC2, NPC2_alive);
		DrawNPC(NPC3, NPC3_alive);
		DrawNPC(NPC4, NPC4_alive);
		Draw2DMAP();
		DrawBullet();
	}
	else if (view == 3) {

		DrawHERO();
		DrawNPC(NPC1, NPC1_alive);
		DrawNPC(NPC2, NPC2_alive);
		DrawNPC(NPC3, NPC3_alive);
		DrawNPC(NPC4, NPC4_alive);
		DrawBullet();
	}
	
	glutSwapBuffers();

}
void init() {

	glClearColor(0.8, 0.8, 0.8, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//���ö�ά����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1, 0.5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glShadeModel(GL_SMOOTH);     //ʹ��ƽ����������  
	glEnable(GL_DEPTH_TEST);     //�޳�������  
	glEnable(GL_CULL_FACE);      //���������α���  
	glFrontFace(GL_CCW);      //�������ʱ�뷽��Ϊ����  

	/////////////////////////////////////////////////////////////////////////////////////
	//{ 
	//	//����ͼ��Դ
	//	GLfloat light0_position[] = { 10.0f, 10.0f, 0.0f, 1.0f };
	//	GLfloat light0_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	//	GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

	//	//һ��ͼ��Դ
	//	GLfloat light1_position[] = { 10.0f, 10.0f, 0.0f, 1.0f };
	//	GLfloat light1_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//	GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	//	//glEnable(GL_LIGHTING);
	//	glEnable(GL_DEPTH_TEST);

	//}


}
void initMAP() {

	//��ʼ���Թ�MAP[900]����
	for (int i = 0; i < 900; i++) {
		MAP[i] = 1;
	}
	//���
	MAP[19] = 0;
	//�յ�
	MAP[871 + 20] = 0;
	for (int i = 0; i < 28; i++) {
		if (i != 10) {

			MAP[i + 31] = 0;
			if (i != 25)
				MAP[i + 841] = 0;
		}
	}
	MAP[61 + 5] = 0;
	MAP[61 + 22] = 0;
	MAP[61 + 3] = 0;
	MAP[61 + 13] = 0;

	MAP[811 + 27] = 0;
	MAP[811 + 25] = 0;
	for (int i = 0; i < 28; i++) {
		if (i != 4 && i != 15) {
			MAP[i + 91] = 0;
		}
		else {
			MAP[i + 811] = 0;
		}
	}
	MAP[121 + 1] = 0;
	MAP[121 + 18] = 0;
	for (int i = 0; i < 5; i++) {
		MAP[i + 781] = 0;
		MAP[i + 781 + 10] = 0;
		MAP[i + 781 + 15] = 0;
		MAP[i + 781 + 23] = 0;
	}
	for (int i = 0; i < 10; i++) {
		if (i != 3) {
			MAP[i + 751 + 3] = 0;
			MAP[i + 751 + 15] = 0;
		}
	}
	MAP[721 + 3] = 0;
	MAP[721 + 19] = 0;
	for (int i = 0; i < 28; i++) {
		if (i != 7)
			MAP[i + 151] = 0;
	}
	for (int i = 0; i < 28; i++) {
		if (i != 7 && i != 18)
			MAP[i + 691] = 0;
	}
	MAP[661 + 27] = 0;
	MAP[661 + 15] = 0;
	MAP[661] = 0;
	MAP[631] = 0;
	MAP[631 + 27] = 0;
	for (int i = 0; i < 10; i++) {
		MAP[631 + i + 15] = 0;
		MAP[631 + i + 3] = 0;
	}
	for (int i = 0; i < 4; i++) {
		MAP[601 + i] = 0;
		MAP[601 + i + 10] = 0;
		MAP[601 + i + 24] = 0;
	}
	for (int i = 0; i < 10; i++) {
		if (i != 4)
			MAP[571 + i + 3] = 0;
		MAP[571 + i + 17] = 0;
	}
	MAP[541 + 1] = 0;
	MAP[541 + 2] = 0;
	MAP[541 + 3] = 0;
	MAP[541 + 10] = 0;
	MAP[541 + 18] = 0;
	MAP[511 + 1] = 0;
	for (int i = 7; i < 28; i++) {
		if (i != 16)
			MAP[511 + i] = 0;
	}
	for (int i = 0; i < 7; i++) {
		MAP[481 + i] = 0;
		if (i != 3)
			MAP[481 + i + 12] = 0;
	}
	MAP[451 + 27] = 0;
	MAP[481 + 27] = 0;
	MAP[451 + 3] = 0;
	MAP[451 + 5] = 0;
	MAP[451 + 13] = 0;
	for (int i = 0; i < 5; i++) {
		MAP[451 + i + 18] = 0;
	}
	for (int i = 0; i < 5; i++) {
		MAP[421 + 2 + i] = 0;
		MAP[421 + 10 + i] = 0;
		MAP[421 + i + 23] = 0;
	}
	MAP[421 + 20] = 0;
	MAP[391] = 0;
	MAP[391 + 1] = 0;
	MAP[391 + 2] = 0;
	MAP[391 + 13] = 0;
	MAP[391 + 27] = 0;
	MAP[361 + 27] = 0;
	MAP[361 + 13] = 0;
	MAP[361] = 0;
	MAP[181 + 5] = 0;
	MAP[181 + 10] = 0;
	MAP[181 + 20] = 0;
	for (int i = 0; i < 28; i++) {
		if (i != 4 && i != 7 && i != 15)
			MAP[i + 211] = 0;
	}
	MAP[241] = 0;
	MAP[241 + 27] = 0;
	for (int i = 3; i < 7; i++) {
		if (i != 5) {
			MAP[i + 241] = 0;
			MAP[i + 241 + 10] = 0;
		}

	}
	MAP[271] = 0;
	MAP[271 + 1] = 0;
	for (int i = 4; i < 7; i++) {
		MAP[i + 271] = 0;
		MAP[i + +271 + 5] = 0;
		MAP[i + 271 + 12] = 0;
		MAP[i + 271 + 15] = 0;
		MAP[i + 271 + 18] = 0;
	}
	MAP[301 + 21] = 0;
	MAP[301 + 27] = 0;
	for (int i = 1; i < 5; i++) {
		MAP[i + 301] = 0;
		MAP[i + 301 + 12] = 0;
	}
	MAP[301 + 11] = 0;
	MAP[331] = 0;
	MAP[331 + 1] = 0;
	for (int i = 4; i < 14; i++) {
		if (i != 10)
			MAP[i + 331] = 0;
		MAP[i + 331 + 14] = 0;
	}

}


void changeToFirstSight() {

	eyeX = HERO[0];
	eyeY = HERO[1];
	eyeZ = HERO[2];

	switch (HERO[3])
	{
	case 0://up
		centerX = eyeX;
		centerY = eyeY + 1;

		break;
	case 1://left
		centerX = eyeX - 1;
		centerY = eyeY;
		break;
	case 2://down
		centerX = eyeX;
		centerY = eyeY - 1;
		break;
	case 3://right
		centerX = eyeX + 1;
		centerY = eyeY;
		break;
	default:
		break;
	}
	centerZ = eyeZ;

	upX = 0;
	upY = 0;
	upZ = 1;
}

void changeToSecondSight() {
	eyeX = HERO[0];
	eyeY = HERO[1];
	eyeZ = HERO[2] + 1;

	switch (HERO[3])
	{
	case 0://up
		centerX = eyeX;
		centerY = eyeY + 1;
		eyeY = eyeY - 1.5;
		break;
	case 1://left
		centerX = eyeX - 1;
		centerY = eyeY;
		eyeX = eyeX + 1.5;
		break;
	case 2://down
		centerX = eyeX;
		centerY = eyeY - 1;
		eyeY = eyeY + 1.5;
		break;
	case 3://right
		centerX = eyeX + 1;
		centerY = eyeY;
		eyeX = eyeX - 1.5;
		break;
	default:
		break;
	}
	centerZ = eyeZ;

	upX = 0;
	upY = 0;
	upZ = 1;
}


void NPCmove(int * NPC) {
	int NPC_direction = rand() % 4;

	int NPCX = NPC[0] + 15;//19
	int NPCY = NPC[1] + 14;//0


	if (NPC_direction == 0) 
	{
		NPC[3] = 0;
		if (MAP[(NPCY + 1) * 30 + NPCX] == 0) NPC[1]++;
	}
	else if (NPC_direction == 1) 
	{
		NPC[3] = 1;
		if (MAP[(NPCY - 1) * 30 + NPCX] == 0) NPC[1]--;
	}
	else if (NPC_direction == 2) 
	{
		NPC[3] = 2;
		if (MAP[NPCY * 30 + NPCX - 1] == 0) NPC[0]--;
	}
	else if (NPC_direction == 3) 
	{
		NPC[3] = 3;
		if (MAP[NPCY * 30 + NPCX + 1] == 0) NPC[0]++;
	}
}

void move(int key, int x, int y) {

	int HEROX = HERO[0] + 15;//19
	int HEROY = HERO[1] + 14;//0

	if (key == GLUT_KEY_F2) TakeScreenshot();

	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN || key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT) {
		NPCmove(NPC1);
		NPCmove(NPC2);
		NPCmove(NPC3);
		NPCmove(NPC4);
	}
	//�жϵ�ͼ�Ƿ��߹�
	{
		//right
		if (MAP[HEROY * 30 + (HEROX + 1)] == 1) {
			MAP[HEROY * 30 + (HEROX + 1)] = -1;
		}
		//left
		if (MAP[HEROY * 30 + (HEROX - 1)] == 1) {
			MAP[HEROY * 30 + (HEROX - 1)] = -1;
		}
		//up
		if (MAP[(HEROY + 1) * 30 + HEROX] == 1) {
			MAP[(HEROY + 1) * 30 + HEROX] = -1;
		}
		//down
		if (MAP[(HEROY - 1) * 30 + HEROX] == 1) {
			MAP[(HEROY - 1) * 30 + HEROX] = -1;
		}
		//upleft
		if (MAP[(HEROY + 1) * 30 + HEROX - 1] == 1) {
			MAP[(HEROY + 1) * 30 + HEROX - 1] = -1;
		}
		//upright
		if (MAP[(HEROY + 1) * 30 + HEROX + 1] == 1) {
			MAP[(HEROY + 1) * 30 + HEROX + 1] = -1;
		}
		//downleft
		if (MAP[(HEROY - 1) * 30 + HEROX - 1] == 1) {
			MAP[(HEROY - 1) * 30 + HEROX - 1] = -1;
		}

		//downright
		if (MAP[(HEROY - 1) * 30 + HEROX + 1] == 1) {
			MAP[(HEROY - 1) * 30 + HEROX + 1] = -1;
		}
	}
	//������ͼ�µ��ƶ�
	if (view == 3) {
		if (key == GLUT_KEY_UP) {
			if (HERO[3] != 0) {
				HERO[3] = 0;
				if (MAP[(HEROY + 1) * 30 + HEROX] == 0) HERO[1]++;
			}
			else {
				if (MAP[(HEROY + 1) * 30 + HEROX] == 0) HERO[1]++;
			}
		}
		if (key == GLUT_KEY_DOWN) {
			if (HERO[3] != 2) {
				HERO[3] = 2;
				if (MAP[(HEROY - 1) * 30 + HEROX] == 0 && HEROY > 0) HERO[1]--;
			}
			else {
				if (MAP[(HEROY - 1) * 30 + HEROX] == 0 && HEROY > 0) HERO[1]--;
			}
		}
		if (key == GLUT_KEY_LEFT) {
			if (HERO[3] != 1) {
				HERO[3] = 1;
				if (MAP[HEROY * 30 + HEROX - 1] == 0) HERO[0]--;
			}
			else {
				if (MAP[HEROY * 30 + HEROX - 1] == 0) HERO[0]--;
			}
		}
		if (key == GLUT_KEY_RIGHT) {
			if (HERO[3] != 3) {
				HERO[3] = 3;
				if (MAP[HEROY * 30 + HEROX + 1] == 0) HERO[0]++;
			}
			else {
				if (MAP[HEROY * 30 + HEROX + 1] == 0) HERO[0]++;
			}
		}

		if (key == GLUT_KEY_F1) {
			fireornot = true;
		}
	}
	else {
		//��һ��ͼ�µ��ƶ�

		if (key == GLUT_KEY_UP) {
			switch (HERO[3])
			{
			case 0:
				if (MAP[(HEROY + 1) * 30 + HEROX] == 0)
					HERO[1]++;
				break;
			case 1:
				if (MAP[HEROY * 30 + (HEROX - 1)] == 0)
					HERO[0]--;
				break;
			case 2:
				if (MAP[(HEROY - 1) * 30 + HEROX] == 0 && HEROY > 0)
					HERO[1]--;
				break;
			case 3:
				if (MAP[HEROY * 30 + (HEROX + 1)] == 0)
					HERO[0]++;
				break;
			default:
				break;
			}

		}
		if (key == GLUT_KEY_DOWN) {
			switch (HERO[3])
			{
			case 0:
				HERO[3] = 2;
				break;
			case 1:
				HERO[3] = 3;
				break;
			case 2:
				HERO[3] = 0;
				break;
			case 3:
				HERO[3] = 1;
				break;
			default:
				break;
			}

		}
		if (key == GLUT_KEY_LEFT) {
			HERO[3] = (HERO[3] + 1) % 4;
		}
		if (key == GLUT_KEY_RIGHT) {
			HERO[3] = (HERO[3] + 3) % 4;
		}		
		if (key == GLUT_KEY_F1) {
			fireornot = true;
		}
		if (view == 1) {
			changeToFirstSight();
		}
		else if (view == 2) {
			changeToSecondSight();
		}



	}
	if (HEROX + HEROY * 30 == 871 + 20) youwin_flag = true;
	if (HERO[0] == NPC1[0] && HERO[1] == NPC1[1]) gameover_flag = true;
	if (HERO[0] == NPC2[0] && HERO[1] == NPC2[1]) gameover_flag = true;
	if (HERO[0] == NPC3[0] && HERO[1] == NPC3[1]) gameover_flag = true;
	if (HERO[0] == NPC4[0] && HERO[1] == NPC3[1]) gameover_flag = true;
	init();
	display();
}


void changeSight(unsigned char key, int x, int y) {


	if (key == '3') {

		eyeX = 0;
		eyeY = 0;
		eyeZ = 15;

		centerX = 0;
		centerY = 0;
		centerZ = 0;

		upX = 0;
		upY = 1;
		upZ = 0;

		view = 3;
		//��ת���ӽ�ʱ�ر����ģʽ
		fmouse = false;
		centerchanX = centerchanY = centerchanZ = 0;

	}
	else if (key == '1') {
		changeToFirstSight();
		view = 1;
		//��ת���ӽ�ʱ�ر����ģʽ
		fmouse = false;
		centerchanX = centerchanY = centerchanZ = 0;

	}
	else if (key == '2') {
		changeToSecondSight();
		view = 2;
		//��ת���ӽ�ʱ�ر����ģʽ
		fmouse = false;
		centerchanX = centerchanY = centerchanZ = 0;

	}
	else if (key == 'm') {
		fmouse = true;
	}
	//�������ģʽ
	else if (key == 'r') {
		fmouse = false;
		centerchanX = centerchanY = centerchanZ = 0;
	}
	//�ر����ģʽ
	else {
		goto here;
	}
here:
	init();
	display();
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(300, 50);
	glutInitWindowSize(700, 700);
	glutCreateWindow("�Թ�");

	obj.parse("box.txt");


	initMAP();

	glGenTextures(5, texture_id);
	loadTexture(0, "wall.bmp");
	loadTexture(1, "floor.bmp");
	loadTexture(2, "gameover.bmp");
	loadTexture(3, "youwin.bmp");
	obj.tex = obj.load_texture_obj("box.bmp");
	boxList = GenboxList();
	load_glm();
	glutDisplayFunc(display);
	glutKeyboardFunc(changeSight);
	glutPassiveMotionFunc(mouse);//�����Ӧ����
	glutSpecialFunc(move);
	glutIdleFunc(idle);
	init();
	inittexture();
	glutMainLoop();

	return 0;
}