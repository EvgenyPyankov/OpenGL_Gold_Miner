#include <GL/glut.h>
#include "Mineral.h"
#include "LevelGenerator.h"
#include "Constants.h"
#include "Converter.h"
#include "Hook.h"
#include <string>

using namespace std;

void keyPressed(int key, int x, int y);
void drawHook(Hook hook);
void drawMineral(Mineral mineral);
void drawInfo(int timeLeft, int score);
void renderTimer(int value);
void finishLevel();
void levelTimer(int value);
void hookTimer(int value);
void processHookTimer();
void processLevelTimer();
int detectCollision();
void drawText(string key, int value, float x, float y);
TCHAR * getGameResultText();

vector<Mineral> minerals;
Levels currentLevel;
Hook hook;
int mineral;
int timeLeft;
int score;
int maxScore;
float ambient[4] = { 0.5, 0.5, 0.5, 1 };


void initGame()
{
	currentLevel = One;
	minerals = LevelGenerator::getMinerals(currentLevel);
	hook = Hook(0.5, 0.0, 0.5);
	mineral = -1;
	timeLeft = LEVEL_TIME;
	score = 0;
	maxScore = 0;

	for (Mineral mineral : minerals)
	{
		maxScore += mineralValues.at(mineral.getType());
	}

}

void init(void)
{
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	
	GLUquadricObj *quadObj;
	GLfloat front_color[] = { 0,1,0,1 };
	GLfloat back_color[] = { 0,0,1,1 };
	quadObj = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_color);
	/*glPushMatrix();
	glRotated(110, -1, 1, 0);
	gluCylinder(quadObj, 1, 0.5, 2, 10, 10);
	glPopMatrix();*/
	gluDeleteQuadric(quadObj);


	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_shininess[] = { 50.0 };
	//GLfloat light_position[] = { 0, 1, 1, 0.0 };
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//for (Mineral mineral:minerals)
	//{
	//	float x = Converter::getX(mineral.getX());
	//	float y = Converter::getY(mineral.getY());
	//	float z = Converter::getZ(mineral.getZ());
	//	float radius = Converter::getLength(mineral.getR());
	//	/*glTranslatef(0, 0, 0);
	//	glutSolidSphere(1, 30, 16);
	//	glFlush();*/
	//	glTranslatef(x, y, z);
	//	glutSolidSphere(radius, 30, 16);
	//	
	//}
	//glFlush();




	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

									// Render a color-cube consisting of 6 quads with different colors
	//glLoadIdentity();                 // Reset the model-view matrix
	////glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen4
	//glTranslatef(0, 0, -7.0);

	//glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	//								  // Top face (y = 1.0f)
	//								  // Define vertices in counter-clockwise (CCW) order with normal pointing out
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glVertex3f(-1.0f, 1.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f);

	//// Bottom face (y = -1.0f)
	//glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);

	//// Front face  (z = 1.0f)
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, 1.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, 1.0f);

	//// Back face (z = -1.0f)
	//glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);

	//// Left face (x = -1.0f)
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(-1.0f, 1.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f);

	//// Right face (x = 1.0f)
	//glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glEnd();  // End of drawing color-cube

	//		  // Render a pyramid consists of 4 triangles
	//glLoadIdentity();                  // Reset the model-view matrix
	//glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen

	//glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	//								 // Front
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(1.0f, -1.0f, 1.0f);

	//// Right
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(1.0f, -1.0f, -1.0f);

	//// Back
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	//glVertex3f(-1.0f, -1.0f, -1.0f);

	//// Left
	//glColor3f(1.0f, 0.0f, 0.0f);       // Red
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);       // Green
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glEnd();   // Done drawing the pyramid
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	/*glVertex3d(0, 1, -5);
	glVertex3d(0, -1, -5);*/
	float x = Converter::getX(hook.getX());
	float y = Converter::getY(hook.getY());
	//float z = Converter::getZ(hook.getZ());
	glVertex3d(0, 1, -3);
	glVertex3d(x, y, -3);
	glEnd();

			   for (Mineral mineral:minerals)
			   {
				   drawMineral(mineral);
			   	
			   }
			   drawHook(hook);
	/*		   glColor3d(1.0, 0.0, 0.0);
			   glRasterPos2d(0.1, 0.1);
			   string s = "hello";
			   for (int n = 0; n<s.size(); ++n) {
				   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[n]);
			   }*/
			  // glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');

			   drawInfo(timeLeft, score);
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
	//processHookTimer();
}



void reshape(int w, int h)
{
	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//if (w <= h)
	//	glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,
	//		1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	//else
	//	glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
	//		1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.5, 0.5, 2.5, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);

	// Compute aspect ratio of the new window
	if (h == 0) h = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	// Set the viewport to cover the new window
	glViewport(0, 0, w, h);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
								  // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN: hook.pullHook(); break;
	}
}

void drawInfo(int timeLeft, int score)
{
	//glLoadIdentity();
	//int x0 = Converter::getX(0.01);
	//int y0 = Converter::getY(0.01);
	//string s = to_string(timeLeft);
	//wchar_t  buffer[100];
	//wsprintf(buffer, TEXT("Time left: %d"), timeLeft);
	//TextOut(hdc, x0, y0, buffer, lstrlen(buffer));
	//x0 = Converter::getX(0.01);
	//y0 = Converter::getY(0.05);
	//wsprintf(buffer, TEXT("Score: %d"), score);
	//TextOut(hdc, x0, y0, buffer, lstrlen(buffer));
	drawText("Time left", timeLeft, -0.6, 0.5);
	drawText("Score", score, -0.6, 0.4);
}

void drawText(string key, int value, float x, float y)
{
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);
	glTranslatef(x, y, -3);
	//glLoadIdentity();    //Reset model-view matrix
	//glPushMatrix();
	//glTranslatef(0, 0, 0.0f);  //Translate to (xPos,yPos)
	glRasterPos2d(x, y);
	key = key + ": "+ to_string(value);
	for (int n = 0; n<key.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key[n]);
	}

}


void drawHook(Hook hook)
{
	glLoadIdentity(); 

	float x = Converter::getX(hook.getX());
	float y = Converter::getY(hook.getY());
	float z = Converter::getZ(hook.getZ());
	float radius = Converter::getLength(hook.getRadius());
	glTranslatef(x, y, -3);
	glutSolidSphere(radius, 30, 16);
}

void drawMineral(Mineral mineral)
{
	glLoadIdentity();                 // Reset the model-view matrix

	float x = Converter::getX(mineral.getX());
	float y = Converter::getY(mineral.getY());
	float z = Converter::getZ(mineral.getZ());
	float radius = Converter::getLength(mineral.getR());
	/*glTranslatef(0, 0, 0);
	glutSolidSphere(1, 30, 16);
	glFlush();*/
	glTranslatef(x, y, -3);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(radius, 30, 16);
}

void hookTimer(int value) {
	//glutPostRedisplay();    // Post a paint request to activate display()
	processHookTimer();
	glutTimerFunc(30, hookTimer, 0); // subsequent timer call at milliseconds
}

void levelTimer(int value) {
	//glutPostRedisplay();    // Post a paint request to activate display()
	processLevelTimer();
	glutTimerFunc(1000, levelTimer, 0); // subsequent timer call at milliseconds
}
void renderTimer(int value) {
	glutPostRedisplay();    // Post a paint request to activate display()
	glutTimerFunc(30, renderTimer, 0); // subsequent timer call at milliseconds
}

TCHAR * getGameResultText()
{
	double tmp = (double)score / maxScore;
	if (tmp > 0.9)
		return winMessage;
	return loseMessage;
}

void finishLevel()
{
	TCHAR *resultText = getGameResultText();
	MessageBox(NULL,
		resultText,
		TEXT("Game over"),
		NULL);
	initGame();
}

void processLevelTimer()
{
	if (timeLeft == 0)
		finishLevel();
	else
		timeLeft--;
}

void processHookTimer()
{
	hook.calculatePosition();
	if (mineral >= 0)
	{
		minerals[mineral].setX(hook.getX());
		minerals[mineral].setY(hook.getY());
		if (hook.getHookState() == Aiming) {
			score += mineralValues.at(minerals[mineral].getType());
			minerals.erase(minerals.begin() + mineral);
			mineral = -1;
		}

	}
	else
	{
		mineral = detectCollision();
		if (mineral >= 0) {
			hook.grabMineral(minerals[mineral].getType());
		}
	}
}

int detectCollision()
{
	double xHook = hook.getX();
	double yHook = hook.getY();
	for (int i = 0; i<minerals.size(); i++)
	{
		double x = xHook - minerals[i].getX();
		double y = yHook - minerals[i].getY();
		if ((x*x + y*y) < minerals[i].getR()*minerals[i].getR()) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char** argv)
{
	initGame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);




	GLfloat mat_specular[] = { 1,1,1,1 };
	float pos[4] = { 3,3,3,1 };
	float dir[3] = { -1,-1,-1 };


	glEnable(GL_DEPTH_TEST);

	//  glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);


	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	init();
	glutTimerFunc(0, renderTimer, 0);
	glutTimerFunc(0, hookTimer, 0);
	glutTimerFunc(0, levelTimer, 0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyPressed);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glutMainLoop();
	return 0;
}