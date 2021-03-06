#include"header.h"

void key(unsigned char k, int x, int y){
	switch(k){
		case 27:
		case ' ':
			isPlanetRun=!isPlanetRun;
			break;
		case 'q':
			exit(0);
			break;
		case 'a':
			eye[0] = eye[0] + 0.05;
			center[0] = center[0] +0.05;
			break;
		case 'd':
			eye[0] = eye[0] - 0.05;
			center[0] = center[0] - 0.05;
			break;
		case 'w': 
			eye[1] = eye[1] + 0.05;
			center[1] = center[1] + 0.05;
			break;
		case 's': 
			eye[1] = eye[1] - 0.05;
			center[1] = center[1] - 0.05;
			break;
		case 'z': 
			eye[2] = eye[2] - 0.05;
			center[2]=center[2]-0.05;
			break;
		case 'c':
			eye[2] = eye[2] + 0.05;
			center[2]=center[2]+0.05;
			break;
		case 'i':
			center[1]=center[1]+0.05;
			break;
		case 'k':
			center[1]=center[1]-0.05;
			break;
		case 'j':
			center[0]=center[0]-0.05;
			break;
		case 'l':
			center[0]=center[0]+0.05;
			break;
		
	}
}


void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio=(GLfloat)width/(GLfloat)height;
	gluPerspective(45.0f, whRatio, 0.005f, 10000000.0f);
	// glOrtho(-4, 4, -4, 4, 0, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// 重置变换矩阵（回到世界坐标系）

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_LIGHTING);
    // GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	// GLfloat light_pos[] = {5,5,5,1};

	// glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	// glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	// glEnable(GL_LIGHT0);

	GLfloat lightColor[]={0.5,0.5,0.5,1};
	GLfloat lightPos[]={0.8,0.8,0.8,1};
	const GLfloat lightType[]={7.0f};
	GLfloat lightEmmision[]={0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,lightColor);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,lightPos);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,lightType);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,lightEmmision);
	glEnable(GL_LIGHT0);

//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	// glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	//glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);

	if(isPlanetRun){
		
		sun.curSelfAngle+=timeFactor/sun.selfRotatTime;
		earth.curSelfAngle+=timeFactor/earth.selfRotatTime;
		earth.curOrbitAngle+=timeFactor/earth.orbitRotatTime;
		moon.curOrbitAngle+=timeFactor/moon.orbitRotatTime;
		mars.curSelfAngle+=timeFactor/mars.selfRotatTime;
		mars.curOrbitAngle+=timeFactor/mars.orbitRotatTime;
		jupiter.curSelfAngle+=timeFactor/jupiter.selfRotatTime;
		jupiter.curOrbitAngle+=timeFactor/jupiter.orbitRotatTime;
	}
	// glColor3f(1,0.5,0.6);


	// printf("%f\n",sun.curSelfAngle);
	draw();
	glEnable(GL_DEPTH_TEST);
	// glutSolidCube(1);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1280,960);  
	int windowHandle = glutCreateWindow("Solar System");

	initialize();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


