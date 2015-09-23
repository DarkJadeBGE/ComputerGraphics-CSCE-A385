/*
* main.cpp
*
*  Created on: Sep 14, 2015
*      Author: tboozeubuntu
*/
/* Tyler Boozer
* Masa Hu
* Brian Kapala
*
* Main.cpp - Task 1 Source Code
* CSCE385
* Professor Cavalcanti
*/

// LINUX or UNIX ONLY
#include <gl/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUMBEROF(x) ((sizeof(x))/(sizeof(x[0])))

static int function_index;
static int slices = 36;
static int stacks = 16;
static double irad = .25;
static double orad = 1.0;
int testVar = 0;
int pastlimit = 0;
GLUquadricObj *g_normalObject = NULL;
GLUquadricObj *g_wireframeObject = NULL;
GLUquadricObj *g_flatshadedObject = NULL;
float changeSpeed = 8;
float rotateForWalkMotion = 0;
float rotateUpperTorso_degrees = 0;
float rotateWhole_degrees = 0;
float xmovement = 0;
float zmovement = 0;
float rotatePointer_degrees = 0;
GLvoid drawDisk1(GLfloat rotation);
GLvoid drawDisk2(GLfloat rotation);

void init_dados(void);
void setup_sceneEffects(void);
void cleanUP_data(void);

static void drawSolidTetrahedron(void)
{
	glutSolidTetrahedron();
}
static void drawWireTetrahedron(void)
{
	glutWireTetrahedron();
}
static void drawSolidCube(void)
{
	glutSolidCube(1);
}
static void drawWireCube(void)
{
	glutWireCube(1);
}
static void drawSolidOctahedron(void)
{
	glutSolidOctahedron();
}
static void drawWireOctahedron(void)
{
	glutWireOctahedron();
}
static void drawSolidDodecahedron(void)
{
	glutSolidDodecahedron();
}
static void drawWireDodecahedron(void)
{
	glutWireDodecahedron();
}
static void drawSolidIcosahedron(void)
{
	glutSolidIcosahedron();
}
static void drawWireIcosahedron(void)
{
	glutWireIcosahedron();
}
static void drawSolidTeapot(void)
{
	glutSolidTeapot(1);
}
static void drawWireTeapot(void)
{
	glutWireTeapot(1);
}
static void drawSolidTorus(void)
{
	glutSolidTorus(irad, orad, slices, stacks);
}
static void drawWireTorus(void)
{
	glutWireTorus(irad, orad, slices, stacks);
}
static void drawSolidSphere(void)
{
	glutSolidSphere(1, slices, stacks);
}
static void drawWireSphere(void)
{
	glutWireSphere(1, slices, stacks);
}
static void drawSolidCone(void)
{
	glutSolidCone(1, 1, slices, stacks);
}
static void drawWireCone(void)
{
	glutWireCone(1, 1, slices, stacks);

}
static void drawSolidCylinder(void)
{
	gluCylinder(g_flatshadedObject,1, 1, 1, slices, stacks);

}
static void drawWireCylinder(void)
{
	gluCylinder(g_wireframeObject, 1, 1, 1, slices, stacks);
}

typedef struct
{
	const char * const name;
	void(*solid) (void);
	void(*wire)  (void);
} entry;

#define ENTRY(e) {#e, drawSolid##e, drawWire##e}
static const entry table[] =
{ 
	ENTRY(Tetrahedron), //0
	ENTRY(Cube),
	ENTRY(Octahedron),
	ENTRY(Dodecahedron),
	ENTRY(Icosahedron),
	ENTRY(Teapot),
	ENTRY(Torus),
	ENTRY(Sphere),
	ENTRY(Cone),
	ENTRY(Cylinder) //9
};
#undef ENTRY

GLvoid drawSpinner(GLfloat rotation, double x, double y, double z, double speed, double radiusa, int r, int g, int b, double translate)
{

	glPushMatrix();
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
	glColor3ub(r, g, b);
	glTranslatef(x, y, z);
	glRotatef(rotation* radiusa * speed + translate, 0.0, 0.0, 1.0);
	glScalef(radiusa, .1, .01);
	table[7].solid();
	glPopMatrix();
}

GLvoid drawSpinnerSet(GLfloat rotation, double x, double y, double z, double speed, int r, int g, int b, double radiusa)
{
	drawSpinner(rotation, x, y, z, speed, radiusa, r, g, b, 0);
	drawSpinner(rotation, x, y, z, speed, radiusa, r, g, b, 90);
}

void setup_sceneEffects(void)
{
	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// enable using glColor to change material properties
	// we'll use the default glColorMaterial setting (ambient and diffuse)
	glEnable(GL_COLOR_MATERIAL);

	// set the default blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set up the fog parameters for reflections
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, -100.0);
	glFogf(GL_FOG_END, 100.0);

	// enable line anti-aliasing and make the lines slightly bigger than default
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.5f);
}

void init_dados(void)
{
	setup_sceneEffects();
	// create a normal quadric (uses default settings)
	g_normalObject = gluNewQuadric();

	g_wireframeObject = gluNewQuadric();
	gluQuadricDrawStyle(g_wireframeObject, GLU_LINE);

	// create an object that uses flat shading
	g_flatshadedObject = gluNewQuadric();
	gluQuadricNormals(g_flatshadedObject, GLU_FLAT);
}

void cleanUP_data(void)
{  // delete all quadratic objects
	if (g_normalObject)
		gluDeleteQuadric(g_normalObject);
	if (g_wireframeObject)
		gluDeleteQuadric(g_wireframeObject);
	if (g_flatshadedObject)
		gluDeleteQuadric(g_flatshadedObject);
}

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ar > .5)
		glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	else
		glFrustum(-1.0, 1.0, -1 / ar, 1 / ar, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void createLeg(int leftright) // Put a 1 for one side -1 for another side.
{
	// Leg A
	glPushMatrix();
	{
		// Rotates Leg A upper
		glRotatef(10, 0, 0, 1);// Set's the initial rotation
		glRotatef(rotateForWalkMotion*leftright, 0, 0, 1); // Used for motion.
		// End rotates Leg A upper.
		glPushMatrix(); // The data for Leg A upper.
		{
			glTranslatef(0, -.75, .5*leftright); // Initial Placement of Leg A Upper
			glPushMatrix(); // Set's the data for Leg A Lower hinge
			{
				glTranslatef(0, -1, .5); // Set's the placement for the rotation for Leg A Lower.
				glPushMatrix(); // The data for Leg A lower
				{
					glRotatef(-rotateForWalkMotion*leftright, 0, 0, 1); // Rotates Leg A lower
					glRotatef(-20, 0, 0, 1); // Initial placement of Leg A lower on the end of leg A Upper.
					glTranslatef(0, -1, -.5); // Placement of the Leg A Lower from it's rotation point.

					glPushMatrix(); // The data for Leg B 
					{
						glRotatef(10, 0, 0, 1);
						glTranslatef(.25, -1, 0); // Placement of the Leg B Lower from it's rotation point.
						glScalef(1.5, .5, .5);// Sets the size of Leg B lower.
						table[1].solid();// Set's the shape for leg B lower
						//glColor3d(1, 1, 0);// Sets the color for Leg B lower.
					}glPopMatrix();// Used to keep the translate separate of Leg B

					glScalef(0.5, 2, .5);// Sets the size of Leg A lower.
					table[1].solid();// Set's the shape for leg A lower
					glColor3d(1, 1, 0);// Sets the color for Leg a lower.
				}glPopMatrix();// Used to keep the translate separate of Leg A
			}glPopMatrix(); // End data for Leg A lower
			glColor3d(0, 1, 0); // Yellow (Upper Leg A)
			glScalef(0.5, 2, .5);// Sets the size for Leg A Upper.
			table[1].solid(); // Sets the shape for leg A Upper.
		}glPopMatrix(); // End data for leg A Upper
	}glPopMatrix();
}

static void createArm(int leftright) // Put a 1 for one side -1 for another side.
{
	// Leg A
	glPushMatrix();
	{
		glTranslatef(0, 2.5, 1.5*leftright);
		// Rotates Leg A upper
		glRotatef(180, 0, 1, 0);// Set's the initial rotation
		glRotatef(10, 0, 0, 1);// Set's the initial rotation
		glRotatef(rotateForWalkMotion*leftright, 0, 0, 1); // Used for motion.
		// End rotates Leg A upper.
		glPushMatrix(); // The data for Leg A upper.
		{
			glTranslatef(0, -.75, .5*leftright); // Initial Placement of Leg A Upper
			glPushMatrix(); // Set's the data for Leg A Lower hinge
			{
				glTranslatef(0, -1, .5); // Set's the placement for the rotation for Leg A Lower.
				glPushMatrix(); // The data for Leg A lower
				{
					glRotatef(-rotateForWalkMotion*leftright, 0, 0, 1); // Rotates Leg A lower
					glRotatef(-20, 0, 0, 1); // Initial placement of Leg A lower on the end of leg A Upper.
					glTranslatef(0, -1, -.5); // Placement of the Leg A Lower from it's rotation point.

					
					glScalef(0.5, 2, .5);// Sets the size of Leg A lower.
					table[1].solid();// Set's the shape for leg A lower
					glColor3d(1, 1, 0);// Sets the color for Leg a lower.
				}glPopMatrix();// Used to keep the translate separate of Leg A
			}glPopMatrix(); // End data for Leg A lower
			glColor3d(0, 1, 0); // Yellow (Upper Leg A)
			glScalef(0.5, 2, .5);// Sets the size for Leg A Upper.
			table[1].solid(); // Sets the shape for leg A Upper.
		}glPopMatrix(); // End data for leg A Upper
	}glPopMatrix();
}

static void createHead()
{
	glPushMatrix(); // The data for Leg B 
	{
		glPushMatrix(); // The data for Leg B 
		{
			glTranslatef(0, 3, 0); // Placement of the Leg B Lower from it's rotation point.
			glScalef(1, 1, 1);// Sets the size of Leg B lower.
			table[1].solid();// Set's the shape for leg B lower
			glColor3d(1, 1, 0);// Sets the color for Leg B lower.
		}glPopMatrix();// Used to keep the translate separate of Leg B
		glTranslatef(0, 2.5, 0); // Placement of the Leg B Lower from it's rotation point.
		glScalef(.25, 1,.25);// Sets the size of Leg B lower.
		glRotatef(90, 1, 0, 0); // rotate
		table[9].solid();// Set's the shape for leg B lower
		glColor3d(1, 1, 0);// Sets the color for Leg B lower.
	}glPopMatrix();// Used to keep the translate separate of Leg B

}

static void display(void)
{
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t*90.0;
	int ViewPosX = 0, ViewPosZ = -8;
	static GLfloat rotation = 0.0;
	rotation += 0.1;
	int limita = 0;
	int limitb = 0;
	srand(300);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_LIGHTING);
	glColor3d(0, 0, 1);

	//InitialObject
	glPushMatrix();
	{
		glColor3d(1, 0, 1);// Purple
		glTranslatef(ViewPosX, 0, ViewPosZ);// Set Position Figure
		glTranslatef(xmovement/10, 0, zmovement/10);
		glRotatef(rotateWhole_degrees, 0.0, 1, 0.0); // rotate
		
		glPushMatrix();
		{
			glRotatef(rotateUpperTorso_degrees, 0.0, 1, 0.0); // rotate
			createHead();
			createArm(1);
			createArm(-1);
			glTranslatef(0, 1.25, 0);// Set Position Figure
			glColor3d(1, 0, 1);// Purple
			glScalef(.5, 2, 1.5);
			table[1].solid();

		}glPopMatrix();
		createLeg(1);
		createLeg(-1);
		glScalef(.5,.5,.5);
		table[1].solid();
	}glPopMatrix();
	glDisable(GL_LIGHTING);
	glPopAttrib();
	glutSwapBuffers();
}

static void moveLegs()
{

	if (pastlimit == false)
	{
		rotateForWalkMotion=rotateForWalkMotion+3;
		testVar=testVar+3;
		if (testVar > 20)
		{
			pastlimit = true;
		}
	}
	else if (pastlimit == true)
	{
		rotateForWalkMotion = rotateForWalkMotion - 3;
		testVar= testVar-3;
		if (testVar < -20)
		{
			pastlimit = false;
		}
	}
}

static void rotationWholePos()
{
	if (rotateWhole_degrees >= 360)
		rotateWhole_degrees = 0;
	rotateWhole_degrees = rotateWhole_degrees + 5;
}

static void rotationWholeNeg()
{
	if (rotateWhole_degrees <= 0)
		rotateWhole_degrees = 360;
	rotateWhole_degrees = rotateWhole_degrees - 4;
}

static void moveRight()
{
	if (rotateWhole_degrees == 0 || rotateWhole_degrees == 360)
	{
	}
	else if (rotateWhole_degrees < 360 && rotateWhole_degrees > 180)
	{
		rotationWholePos();
	}
	else if (rotateWhole_degrees > 0 && rotateWhole_degrees <= 180)
	{
		rotationWholeNeg();
	}
}

static void moveLeft()
{
	if (rotateWhole_degrees == 180)
	{
	}
	else if ((rotateWhole_degrees == 360 && rotateWhole_degrees < 180) || (rotateWhole_degrees >= 0 && rotateWhole_degrees < 180))
	{
		rotationWholePos();
	}
	else if (rotateWhole_degrees < 360 && rotateWhole_degrees > 180)
	{
		rotationWholeNeg();
	}
}

static void moveUp()
{
	if (rotateWhole_degrees == 90)
	{
	}
	else if (rotateWhole_degrees > 90 && rotateWhole_degrees < 270)
	{
		rotationWholeNeg();
	}
	else if (rotateWhole_degrees < 90 || rotateWhole_degrees >= 270)
	{
		rotationWholePos();
	}
}

static void moveDown()
{
	if (rotateWhole_degrees == 270)
	{
	}
	else if (rotateWhole_degrees > 90 && rotateWhole_degrees < 270)
	{
		rotationWholePos();
	}
	else if (rotateWhole_degrees !=270)
	{
		rotationWholeNeg();
	}
}

static void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// This is meant to set the button for the speed of the spinning.
	case '1':
		changeSpeed = 8;
		break;
	case '2':
		changeSpeed = 25;
		break;
	case '3':
		changeSpeed = 50;
		break;
		// This is meant to change the direction of the rotation of the windmills.
		// Rotates left windmill
	case 'd':
		rotateUpperTorso_degrees++;
		break;
	case 'f':
		rotateUpperTorso_degrees--;
		break;
	case 'D':
		rotateUpperTorso_degrees++;
		break;
	case 'F':
		rotateUpperTorso_degrees--;
		break;

	case 'l':
		moveLegs(); 
		moveRight();
		xmovement++;
		break;
	case 'L':
		moveLegs();
		moveRight();
		xmovement++;
		break;
	case 'J':
		moveLegs(); 
		moveLeft();
		xmovement--;
		break;
	case 'j':
		moveLegs();
		moveLeft();
		xmovement--;
		break;
	case 'k':
		moveLegs();
		moveDown();
		zmovement++;
		break;
	case 'K':
		moveLegs();
		moveDown();
		zmovement++;
		break;
	case 'i':
		moveLegs(); 
		moveUp();
		zmovement--;
		break;
	case 'I':
		moveLegs();
		moveUp();
		zmovement--;
		break;


		// The default.
	default:
		break;
	}

	glutPostRedisplay();
}

static void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP:    ++function_index; break;
	case GLUT_KEY_PAGE_DOWN:  --function_index; break;
	case GLUT_KEY_UP:         orad *= 2;        break;
	case GLUT_KEY_DOWN:       orad /= 2;        break;

	case GLUT_KEY_RIGHT:      irad *= 2;        break;
	case GLUT_KEY_LEFT:       irad /= 2;        break;

	default:
		break;
	}

	if (0 > function_index)
		function_index = NUMBEROF(table) - 1;

	if (NUMBEROF(table) <= (unsigned)function_index)
		function_index = 0;
}

static void idle(void)
{
	glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[])
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	init_dados();
	glutCreateWindow("Cuddly Robot");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_FRONT_AND_BACK);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

	glutMainLoop();
	cleanUP_data();
	return EXIT_SUCCESS;
}


