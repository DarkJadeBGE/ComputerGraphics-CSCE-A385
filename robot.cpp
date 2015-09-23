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
float rotateForWalkMotion = 0;
float rotateUpperTorso_degrees = 0;
float rotateWhole_degrees = 0;
float moveTestX = 0;
float moveTestY = 0;
float moveTestZ= 0;
float xmovement = 0;
float zmovement = 0;
float rotatePointer_degrees = 0;

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

static void createGuns()
{
	glPushMatrix(); // The data for Leg B 
	{
		glPushMatrix();
		glScalef(1, .25, .25);
		table[1].solid();
		glPopMatrix();
		//glTranslatef(0, 2.5, 0); // Placement of the Leg B Lower from it's rotation point.
		glScalef(2, .1, .1);// Sets the size of Leg B lower.
		glPushMatrix();
		glRotatef(90, 0, 1, 0); // rotate
		table[9].solid();// Set's the shape for leg B lower
		glPopMatrix();
	}glPopMatrix();
}

static void createArm(int leftright) // Put a 1 for one side -1 for another side.
{
	glPushMatrix();
	{
		glTranslatef(0, 2.0, 1.5*leftright);
		glRotatef(180, 0, 1, 0);// Set's the initial rotation
		glRotatef(10, 0, 0, 1);// Set's the initial rotation
		glRotatef(rotateForWalkMotion*leftright, 0, 0, 1); // Used for motion.
		glPushMatrix(); // The data for Leg A upper.
		{
			glTranslatef(0, -.75, .5*leftright); // Initial Placement of Leg A Upper
		
			glPushMatrix();
			glTranslatef(0, 0, -.35*leftright);
			glRotatef(270, 0, 0, 1);
			createGuns();
			glPopMatrix();

			glPushMatrix(); // Set's the data for Leg A Lower hinge
			{
				glTranslatef(0, -1, .5); // Set's the placement for the rotation for Leg A Lower.
				glPushMatrix(); // The data for Leg A lower
				{
					{
						
					
					}// insert code here for hand guns
					glRotatef(-rotateForWalkMotion*leftright, 0, 0, 1); // Rotates Leg A lower
					glRotatef(-100, 0, 0, 1); // Initial placement of Leg A lower on the end of leg A Upper.
					glTranslatef(0, -.5, -.5); // Placement of the Leg A Lower from it's rotation point
					glScalef(0.5, 1.5, .5);// Sets the size of Leg A lower.
					table[1].solid();// Set's the shape for leg A lower
					glColor3d(1, 1, 0);// Sets the color for Leg a lower.
				}glPopMatrix();// Used to keep the translate separate of Leg A
			}glPopMatrix(); // End data for Leg A lower
			glColor3d(0, 1, 0); // Yellow (Upper Leg A)
			glScalef(0.5, 1.5, .5);// Sets the size for Leg A Upper.
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

static void createRobot()
{
	glPushMatrix();
	{
		glColor3d(1, 0, 1);// Purple
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
	else if (rotateWhole_degrees != 270)
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
		break;
	case 'L':
		moveLegs();
		moveRight();
		break;
	case 'J':
		moveLegs(); 
		moveLeft();
		break;
	case 'j':
		moveLegs();
		moveLeft();
		break;
	case 'k':
		moveLegs();
		moveDown();
		break;
	case 'K':
		moveLegs();
		moveDown();
		break;
	case 'i':
		moveLegs(); 
		moveUp();
		break;
	case 'I':
		moveLegs();
		moveUp();
		break;
	case 'q':
		moveTestX--;
		break;	
	case 'w':
		moveTestX++;
		break;
	case 'e':
		moveTestY--;
		break;
	case 'r':
		moveTestY++;
		break;
	case 't':
		moveTestZ--;
		break;
	case 'y':
		moveTestZ++;
		break;

		// The default.
	default:
		break;
	}

	glutPostRedisplay();
}