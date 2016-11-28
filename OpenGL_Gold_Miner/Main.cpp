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
	quadObj = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
	gluDeleteQuadric(quadObj);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);                   
	glEnable(GL_DEPTH_TEST);  
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_SMOOTH);  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);     
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	float x = Converter::getX(hook.getX());
	float y = Converter::getY(hook.getY());
	glVertex3d(0, 1, -3);
	glVertex3d(x, y, -3);
	glEnd();
	for (Mineral mineral:minerals)
	{
		drawMineral(mineral);			   	
	}
	drawHook(hook);
	drawInfo(timeLeft, score);
	glutSwapBuffers();  
}

void reshape(int w, int h)
{
	if (h == 0) h = 1;             
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();            							  
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
	drawText("Time left", timeLeft, -0.6, 0.5);
	drawText("Score", score, -0.6, 0.4);
}

void drawText(string key, int value, float x, float y)
{
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);
	glTranslatef(x, y, -3);
	glRasterPos2d(x, y);
	key = key + ": "+ to_string(value);
	for (int n = 0; n<key.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, key[n]);
	}
}


void drawHook(Hook hook)
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, hook.getColor());
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
	GLfloat boulderColor[] = { 0.5,0.5,0.5 };
	GLfloat goldColor[] = { 1,0.8,0.2 };
	GLfloat diamondColor[] = { 0,1,0.5 };

	const map<MineralTypes, GLfloat*>colors = {
		{ Boulder,boulderColor },
		{ Gold,goldColor },
		{ SmallBoulder,boulderColor },
		{ SmallGold,goldColor },
		{ Diamond,diamondColor }
	};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, colors.at(mineral.getType()));
	glLoadIdentity();                 
	float x = Converter::getX(mineral.getX());
	float y = Converter::getY(mineral.getY());
	float z = Converter::getZ(mineral.getZ());
	float radius = Converter::getLength(mineral.getR());
	glTranslatef(x, y, -3);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(radius, 30, 16);
}

void hookTimer(int value) {
	processHookTimer();
	glutTimerFunc(30, hookTimer, 0); 
}

void levelTimer(int value) {
	processLevelTimer();
	glutTimerFunc(1000, levelTimer, 0); 
}
void renderTimer(int value) {
	glutPostRedisplay();   
	glutTimerFunc(30, renderTimer, 0); 
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
	float pos[4] = { 1,-1,1,1 };
	float dir[3] = { -1,1,-3 };

	glEnable(GL_DEPTH_TEST);
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