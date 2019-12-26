#include <iostream>
#include <GL\glut.h>
#include <time.h>
#include <math.h>

using namespace std;

double eyeX = 0, eyeY = 0, eyeZ = 15;
double centerX = 0, centerY = 0, centerZ = 0;
double upX = 0, upY = 1, upZ = 0;

double centerchanX=0,centerchanY=0,centerchanZ=0;
//double upchanX=0,upchanY=0,upchanZ=0;//定义并初始化鼠标移动改变glulookat函数参数变化量


int HERO[4] = { 4 , -14 ,-20 , 0 };

int NPC1[4] = { 0 , 0 , -20 , 0 };
bool NPC1_alive = true;
double Bullet[4];
bool fireornot = false;
float firespeed = 0.01f;
bool bullet_dir_cannotchange = true;

int view = 3;

int MAP[900];

GLuint texWall;
GLuint texture_id[2];



bool gameover_flag = true;
float up = 0.0;


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
    
    glRotated(90, 1, 0, 0);
    glutSolidTeapot(0.5);//这里暂时用茶壶代替hero
    
    glPopMatrix();
}

void DrawNPC( int* NPC ) {
    if (NPC1_alive) {
        glColor3b(1.0,0.0,0.0);
        glPushMatrix();
        glTranslatef(NPC[0], NPC[1], -20);
        
        switch (NPC[3])
        {
            case 0:
                glRotatef(90, 0, 0, 1);
                break;
            case 1:
                glRotatef(180, 0, 0, 1);
                break;
            case 2:
                glRotatef(-90, 0, 0, 1);
                break;
            case 3:
                break;
            default:
                break;
        }
        
        
        glutSolidCube(1);
        glPopMatrix();
    }
}

void DrawCube(double x, double y, double z) {
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glBegin(GL_QUADS);
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
        else {
            return 0;
        }
    }
    
}

void Bulletmodel(double x, double y, double z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(0.5);
    glPopMatrix();
}

//鼠标移动改变视角的函数
bool fmouse=false;//检测鼠标模式开启/关闭状态
int lastX=350,lastY=350;//记录上一个鼠标位置
float PI=3.1415;
float radX=0,radY=0;
void mouse(int x,int y){
    if(fmouse){
    //glutSetCursor(GLUT_CURSOR_NONE);//隐藏鼠标的函数
    int chanX=0,chanY=0;
    chanX=x-lastX;
    chanY=y-lastY;
        switch(HERO[3]){
            case 0://up
                radX +=float(PI*chanX/180.0f);
                radY +=float(PI*chanY/180.0f);
                centerchanX=float(7*sin(0.3*radX));
                centerchanY=float(7*cos(0.3*radX));
                centerchanZ=float(7*sin(0.3*radY)-4);
                lastX=x;lastY=y;
                break;
            case 1://left
                radX +=float(PI*chanX/180.0f);
                radY +=float(PI*chanY/180.0f);
                centerchanX=float(7*cos(0.3*radX)*(-1));
                centerchanY=float(7*sin(0.3*radX));
                centerchanZ=float(7*sin(0.3*radY)-4);
                lastX=x;lastY=y;
                break;
            case 2://down
                radX +=float(PI*chanX/180.0f);
                radY +=float(PI*chanY/180.0f);
                centerchanX=float(7*sin(0.3*radX)*(-1));
                centerchanY=float(7*cos(0.3*radX)*(-1));
                centerchanZ=float(7*sin(0.3*radY)-4);
                lastX=x;lastY=y;
                break;
            case 3://right
                radX +=float(PI*chanX/180.0f);
                radY +=float(PI*chanY/180.0f);
                centerchanX=float(7*cos(0.3*radX));
                centerchanY=float(7*sin(0.3*radX)*(-1));
                centerchanZ=float(7*sin(0.3*radY)-4);
                lastX=x;lastY=y;
                break;
            default:
                break;
        }

    }
}

void DrawMAP() {
    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, 700, 700);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    
    glViewport(50, 50, 600, 600);
    
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(eyeX, eyeY, eyeZ, centerX+centerchanX, centerY+centerchanY, centerZ+centerchanZ, upX, upY, upZ);
    //cout<<centerX<<" "<<centerY<<" "<<centerZ<<endl;
    //随鼠标移动glulookat参数改变
    glPushMatrix();
    glTranslatef(-15, -14, 0);
    for (int i = 0; i < 900; i++) {
        if (MAP[i] == 1 || MAP[i] == -1) {
            
            DrawCube(i - i / 30 * 30, i / 30, -20);
        }
        
    }
    glPopMatrix();
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
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


void Draw2DHERO(int x, int y, int head) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(x, y, 0);
    switch (head)
    {
        case 0:
            glBegin(GL_POLYGON);
            glVertex2f(0.1, 0.1);
            glVertex2f(0.9, 0.1);
            glVertex2f(0.5, 0.9);
            glEnd();
            break;
        case 1:
            glBegin(GL_POLYGON);
            glVertex2f(0.1, 0.5);
            glVertex2f(0.9, 0.1);
            glVertex2f(0.9, 0.9);
            glEnd();
            break;
        case 2:
            glBegin(GL_POLYGON);
            glVertex2f(0.5, 0.1);
            glVertex2f(0.9, 0.9);
            glVertex2f(0.1, 0.9);
            glEnd();
            break;
        case 3:
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

void Draw2DMAP() {
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(450, 0, 250, 250);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    
    glViewport(450, 0, 250, 250);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    gluOrtho2D(0, 31, 0, 31);

    Draw2DHERO(HERO[0] + 15, HERO[1] + 14, HERO[3]);
    

    for (int i = 0; i < 900; i++) {

        if (MAP[i] == -1) {
            glColor3f(0, 0, 0);
            DrawSquare(i - i / 30 * 30, i / 30);
        }
    }
}

void display() {
    
    DrawMAP();
    if (view == 1) {

        DrawNPC(NPC1);
    }
    else if (view == 2) {
        DrawHERO();
        DrawNPC(NPC1);

    }
    else if (view == 3) {
        DrawHERO();
        DrawNPC(NPC1);
    }
    
    glutSwapBuffers();
    
}
void init() {
    
    glClearColor(0.8, 0.8, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 0.5, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    
    {
     
        GLfloat light0_position[] = { 10.0f, 10.0f, 0.0f, 1.0f };
        GLfloat light0_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        

        GLfloat light1_position[] = { 10.0f, 10.0f, 0.0f, 1.0f };

        
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        
    }
    
    
}
void initMAP() {
    

    for (int i = 0; i < 900; i++) {
        MAP[i] = 1;
    }

    MAP[19] = 0;

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
        case 0:
            centerX = eyeX;
            centerY = eyeY + 1;
            
            break;
        case 1:
            centerX = eyeX - 1;
            centerY = eyeY;
            break;
        case 2:
            centerX = eyeX;
            centerY = eyeY - 1;
            break;
        case 3:
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
        case 0:
            centerX = eyeX;
            centerY = eyeY + 1;
            eyeY = eyeY - 1.5;
            break;
        case 1:
            centerX = eyeX - 1;
            centerY = eyeY;
            eyeX = eyeX + 1.5;
            break;
        case 2:
            centerX = eyeX;
            centerY = eyeY - 1;
            eyeY = eyeY + 1.5;
            break;
        case 3:
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
    
    int NPCX = NPC[0] + 15;
    int NPCY = NPC[1] + 14;
    
    
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
    
    int HEROX = HERO[0] + 15;
    int HEROY = HERO[1] + 14;
    
    if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN || key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT) {
        NPCmove(NPC1);
    }

    {
        
        if (MAP[HEROY * 30 + (HEROX + 1)] == 1) {
            MAP[HEROY * 30 + (HEROX + 1)] = -1;
        }
        
        if (MAP[HEROY * 30 + (HEROX - 1)] == 1) {
            MAP[HEROY * 30 + (HEROX - 1)] = -1;
        }

        if (MAP[(HEROY + 1) * 30 + HEROX] == 1) {
            MAP[(HEROY + 1) * 30 + HEROX] = -1;
        }
        if (MAP[(HEROY - 1) * 30 + HEROX] == 1) {
            MAP[(HEROY - 1) * 30 + HEROX] = -1;
        }
        if (MAP[(HEROY + 1) * 30 + HEROX - 1] == 1) {
            MAP[(HEROY + 1) * 30 + HEROX - 1] = -1;
        }
        if (MAP[(HEROY + 1) * 30 + HEROX + 1] == 1) {
            MAP[(HEROY + 1) * 30 + HEROX + 1] = -1;
        }
        if (MAP[(HEROY - 1) * 30 + HEROX - 1] == 1) {
            MAP[(HEROY - 1) * 30 + HEROX - 1] = -1;
        }
        
        if (MAP[(HEROY - 1) * 30 + HEROX + 1] == 1) {
            MAP[(HEROY - 1) * 30 + HEROX + 1] = -1;
        }
    }
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
        //当转换视角时关闭鼠标模式
        fmouse=false;
        centerchanX=centerchanY=centerchanZ=0;

    }
    else if (key == '1') {
        changeToFirstSight();
        view = 1;
        //当转换视角时关闭鼠标模式
        fmouse=false;
        centerchanX=centerchanY=centerchanZ=0;

    }
    else if (key == '2') {
        changeToSecondSight();
        view = 2;
        //当转换视角时关闭鼠标模式
        fmouse=false;
        centerchanX=centerchanY=centerchanZ=0;

    }
    else if (key == 'm'){
        fmouse=true;
    }
    //启动鼠标模式
    else if (key == 'r'){
        fmouse=false;
        centerchanX=centerchanY=centerchanZ=0;
    }
    //关闭鼠标模式
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
    glutCreateWindow("1");
    
    initMAP();
    init();
    
    
    glutDisplayFunc(display);
    glutKeyboardFunc(changeSight);
    glutPassiveMotionFunc(mouse);//鼠标响应函数
    glutSpecialFunc(move);
    glutIdleFunc(idle);

    glutMainLoop();
    
    return 0;
}

