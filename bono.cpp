#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
#include<windows.h>
#include<math.h>
#include<time.h>

GLfloat speed=0;
GLfloat key=0;
GLint user=0;
GLint target=6;
GLint score=0;
GLint count = 0;
int viewState = 0;
int soundState = 0;
GLUquadricObj* cyl;
int moveState = 0;

static GLfloat m1 = 0.0f;
static GLfloat m2 = 0.3f;


static GLfloat m = 0.0f;

GLfloat verticesW[][3] = {{-1.0,-0.3,-0.7},{1.0,-0.3, -0.7},
	{1.0,0.3,-0.7}, {-1.0,0.3,-0.7}, {-1.0,-0.3,0.7}, 
	{1.0,-0.3,0.7}, {1.0,0.3,0.7}, {-1.0,0.3,0.7}};
GLfloat colorsW[] = {0.0,0.2,0.4};

void polygonW(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glVertex3fv(verticesW[a]);
		glVertex3fv(verticesW[b]);
		glVertex3fv(verticesW[c]);
		glVertex3fv(verticesW[d]);
	glEnd();
}
void Water()
{
	polygonW(0,3,2,1);
	polygonW(2,3,7,6);
	polygonW(1,2,6,5);
	polygonW(0,3,7,4);
	polygonW(4,5,6,7);
	polygonW(0,1,5,4);
}

//hammer
GLfloat vertices[][3] = {{-0.15,-0.15,-0.15},{0.0,-0.15,-0.15},
{0.0,0.0,-0.15}, {-0.15,0.0,-0.15}, {-0.15,-0.15,0.15}, 
{0.0,-0.15,0.15}, {0.0,0.0,0.15}, {-0.15,0.0,0.15}};

GLfloat colors[] = {1,0.2,0.5,0,0};

static GLfloat angle = 0.0f;

int mouseState = 0;
GLfloat moveX = 0;
GLfloat moveY = 0;
GLfloat moveZ = 0;

void polygon(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(colors);

		glVertex3fv(vertices[a]);

		glColor3fv(colors);

		glVertex3fv(vertices[b]);

		glColor3fv(colors);

		glVertex3fv(vertices[c]);

		glColor3fv(colors);

		glVertex3fv(vertices[d]);
	glEnd();
}

void cube()
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(1,2,6,5);
	polygon(0,1,5,4);
	polygon(0,4,7,3);
	polygon(5,6,7,4);
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y){
	if(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		count++;

		GLint viewport[4];
		GLdouble mvMatrix[16], projMatrix[16];
		GLint realy;
		GLdouble wx,wy,wz;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX,mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		realy = viewport[3] - (GLint)Y-1;
		gluUnProject((GLdouble)X, (GLdouble) realy, 0.1, mvMatrix, projMatrix, viewport, &wx, &wy, &wz);
		moveX = wx;
		moveY = wy;
		moveZ = wz;
		mouseState = 1;

		if(X>=125 && X<262)
			user=1;
		if(X>=262 && X<383)
			user=5;
		if(X>=383 && X<562)
			user=2;
		if(X>=562 && X<700)
			user=4;
		if(X>=700 && X<800)
			user=3;
		
	}
}

void MyMouseMove(GLint X, GLint Y) {
	GLint viewport[4];
	GLdouble mvMatrix[16], projMatrix[16];
	GLint realy;
	GLdouble wx,wy,wz;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	realy = viewport[3] - (GLint)Y-1;
	gluUnProject((GLdouble)X, (GLdouble)realy, 0.1, mvMatrix, projMatrix, viewport, &wx, &wy, &wz);
	moveX = wx;
	moveY = wy;
	moveZ = wz;
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	angle += 4.0f;

	if(angle > 90.0f) {
		angle = 0.0f;
		mouseState = 0;
	}
    
	glutPostRedisplay();
	glutTimerFunc(5, TimerFunction, 1);
}

void DrawHammer(){
	glPushMatrix();
		glTranslatef(moveX, moveY, moveZ);
		glColor3f(0.0, 0.0, 0.0);
		if(mouseState == 1){
			glRotatef(angle, 0 ,0.0,-1.0);
		}
		glTranslatef(0.0,0.25,0.0);
		cyl=gluNewQuadric();
		glRotatef(90,1.0,0.0,0.0);
		gluCylinder(cyl, 0.05, 0.05, 0.50, 50, 1);
		glPushMatrix();
			glTranslatef(0.0, 0.09 , 0.03);
			glRotatef(90.0f,0.0,1.0,0.0);
			cube();
		glPopMatrix();

	glPopMatrix();
}

void text()
{
    char text1[30];
	char text2[20];
	char text3[20];
	char text4[20];
	char text5[20];
	char text6[30];
		
	sprintf(text1, "score: %d", score);
	glColor3f(0, 0, 0);
	glRasterPos3f(-0.9,1.0,-0.6);
	for(int i = 0; text1[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
	sprintf(text2, "   #   #");
	glColor3f(0, 0, 0);
	glRasterPos3f(0.65,0.9,-0.6);
	for(int i = 0; text2[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
	sprintf(text3, "  w   e");
	glColor3f(0, 0, 0);
	glRasterPos3f(0.65,0.86,-0.6);
	for(int i = 0; text3[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text3[i]);
	sprintf(text4, "#   #   #");
	glColor3f(0, 0, 0);
	glRasterPos3f(0.65,0.8,-0.6);
	for(int i = 0; text4[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text4[i]);
	sprintf(text5, "a   s   d");
	glColor3f(0, 0, 0);
	glRasterPos3f(0.65,0.76,-0.6);
	for(int i = 0; text5[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text5[i]);
	sprintf(text6, "[keyboard shottcut key]");
	glColor3f(0, 0, 0);
	glRasterPos3f(0.5,1.0,-0.6);
	for(int i = 0; text6[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text6[i]);


}

void finishText(){
	char text1[32];
	char text2[32];
	sprintf(text1, "         finish!");
	glColor3f(0, 0, 0);
	glRasterPos3f(-0.25,0.5,-0.6);
	for(int i = 0; text1[i] != '\0'; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
	sprintf(text2, "your score is %d!!", score);
	glColor3f(0, 0, 0);
	glRasterPos3f(-0.25,0.4,-0.6);
	for(int i = 0; text2[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
}

////////////////////
void glInit(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[]={3.0f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat position[]={400.0, 300.0, -700.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void MyKeyboard(unsigned char KeyPressed, int x, int y){
	count++;
	switch (KeyPressed){
		case 'a':
			user=1;
			break;
		case 's':
			user=2;
			break;
		case 'd':
			user=3;
			break;
		case 'e':
			user=4;
			break;
		case 'w':
			user=5;
			break;
	}
}

void DrawWater(){
	glPushMatrix();
	glColor4f(0.0, 0.4, 0.8, 0.2);
	glTranslatef(0.0, -0.5, 0.0);
	Water();
	glPopMatrix();
}

void DrawSweat(){
	cyl=gluNewQuadric();
	glPushMatrix();
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glPushMatrix();
		glTranslatef(-0.22, 0.0, 0.0);
		gluSphere(cyl, 0.015, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.013, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.011, 10, 10);
	glPopMatrix();
	glTranslatef(0.0, 0.04, 0.0);
	glPushMatrix();
		glTranslatef(-0.22, 0.0, 0.0);
		gluSphere(cyl, 0.015, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.013, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.011, 10, 10);
	glPopMatrix();
	glTranslatef(0.0, -0.08, 0.0);
	glPushMatrix();
		glTranslatef(-0.22, 0.0, 0.0);
		gluSphere(cyl, 0.015, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.013, 10, 10);
		glTranslatef(-0.05, 0.0, 0.0);
		gluSphere(cyl, 0.011, 10, 10);
	glPopMatrix();
	glPopMatrix();
}

void DrawBody(){
	glPushMatrix();
	glColor3f(0.0, 0.8, 1.0);
	cyl=gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(cyl, 0.2, 0.2, 0.3, 50, 1);
	glPopMatrix();
}

void drawLeftEye(){
	glTranslatef(-0.08, 0.1, 0.13);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.025, 10, 10);
	glPopMatrix();
	glPushMatrix();
}

void drawRightEye(){
	glTranslatef(0.08, 0.1, 0.13);
	gluSphere(cyl, 0.025, 10, 10);
	glPopMatrix();
	glPushMatrix();
}

void drawNose(){
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, 0.06, 0.17);
	gluSphere(cyl, 0.025, 10, 10);
	glPopMatrix();
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.03, 0.05, 0.15);
	gluSphere(cyl, 0.045, 10, 10);
	glPopMatrix();
	glPushMatrix();
	
	glTranslatef(0.03, 0.05, 0.15);
	gluSphere(cyl, 0.045, 10, 10);
	glPopMatrix();
}

void DrawHead(){
	glTranslatef(0.0, 0.02, 0.0);
	glPushMatrix();
	cyl=gluNewQuadric();
	glColor3f(0.0, 0.8, 1.0);
	gluSphere(cyl, 0.20, 30, 10);

	drawLeftEye();
	drawRightEye();

	if(target==user){
		glColor3f(0.7, 0.7, 1.0);
		DrawSweat();
	} 

	drawNose();
}

void DrawBonobono(){
	DrawBody();
	DrawHead();
}
void Move(){
	float i=0;
	i=abs(sin(speed)*0.3);

	glPushMatrix();
	glTranslatef(0.0, i, 0);

}

void Start(){
	srand(time(NULL));
	target = rand()%5+1;
	DrawWater();

	glRotatef(180.0, 0, 1, 0);

	glTranslatef(0.7, -0.5, 0.2);
	if(target==1){
		Move();
		DrawBonobono();
	}
	glPopMatrix();

	glTranslatef(-0.7, 0.0, 0);
	if(target==2){
		Move();
		DrawBonobono();
	}
	glPopMatrix();

	glTranslatef(-0.7, 0.0, 0.0);
	if(target==3){
		Move();
		DrawBonobono();
	}
	glPopMatrix();

	glTranslatef(0.3, 0.0, -0.5);
	if(target==4){
		Move();
		DrawBonobono();
	}
	glPopMatrix();

	glTranslatef(0.8, 0.0, 0.0);
	if(target==5){
		Move();
		DrawBonobono();
	}
	glPopMatrix();

	glPushMatrix();
	DrawHammer();
	glPopMatrix();

	if(user==target){
		score += 10;
		user=0;
		if(soundState==0)
			sndPlaySound(TEXT("gun.wav"), SND_ASYNC|SND_NOSTOP);
		else
			sndPlaySound(TEXT("cash.wav"), SND_ASYNC|SND_NOSTOP);

		if(count==10)
			key=3;
	}

	glutSwapBuffers();
}


void MyDisplay(){
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(viewState == 0)
		gluLookAt(0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if(viewState == 1)
		gluLookAt(0.0, 0.0, 0.1, 0.02, 0.02, 0.0, 0.0, 0.1, 0.0);
	if(viewState == 2)
		gluLookAt(0.0, 0.0, 0.1, 0.0, 0.02, 0.0, 0.0, 0.1, 0.0);

	glPushMatrix();
	glRotatef(-8.0, 1.0, 0.0, 0.0);
	text();
	if(count == 10)
		finishText();
	glPopMatrix();

	if((key!=3) && (count <= 10)){
		Start();
		glPopMatrix();
	}
}

void MyTimer(int Value){
	if(key==1)
		speed+=0.1;
	if(key==2)
		speed+=0.2;
	if(key==3)
		speed += 0.1;
	
	glutPostRedisplay();
	glutTimerFunc(45, MyTimer, 1);
}

void MyMainMenu(int entryID){
	key=entryID; 
	if(entryID == 6)
		viewState = 0;
	if(entryID == 7)
		viewState = 1;
	if(entryID == 8)
		viewState = 2;
	if(entryID == 9) {
		viewState = 0;
		count = 0;
		score = 0;
		key = 1;
	}
	if(entryID == 4)
		soundState = 0;
	if(entryID == 5)
		soundState = 1;
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Catching the Bonobono");
	glInit();

	glutMouseFunc(MyMouseClick);
	glutPassiveMotionFunc(MyMouseMove);
	glutTimerFunc(20, TimerFunction, 1);

	GLint subSound = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("gun", 4);
	glutAddMenuEntry("cash", 5);

	GLint subView = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("2D", 6);
	glutAddMenuEntry("3D(1)", 7);
	glutAddMenuEntry("3D(2)", 8);

	GLint MyMainMenuID=glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("start", 1);
	glutAddMenuEntry("advanced", 2);
	glutAddMenuEntry("pause", 3);
	glutAddMenuEntry("restart", 9);
	glutAddSubMenu("sound", subSound);
	glutAddSubMenu("view", subView);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(60, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}