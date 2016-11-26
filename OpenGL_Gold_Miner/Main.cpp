#include <GL/glut.h>
#include "Mineral.h"
#include "LevelGenerator.h"
#include "Constants.h"
#include "Converter.h"

vector<Mineral> minerals;
Levels currentLevel;

void initGame()
{
	currentLevel = One;
	minerals = LevelGenerator::getMinerals(currentLevel);
}

void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0, 1, 1, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

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

			   for (Mineral mineral:minerals)
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
			   	glutSolidSphere(radius, 30, 16);
			   	
			   }

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
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

int main(int argc, char** argv)
{
	initGame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}