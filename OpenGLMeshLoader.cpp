#include <windows.h>
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#define PI 3.14159265

int WIDTH = 1280;
int HEIGHT = 720;

int lives = 3;
int i = 0;

bool flag = true;
bool z = false;
bool trial = true;
bool hany = true;
bool Moustafa = false;

bool topview = false;

float lastx, lasty;
float xrot = 0, yrot = -52, xpos = 180, ypos = 20, zpos = 0;
double speed = 0.020;
double man1x = 120;
double man1z = 20;
double man1y = 0;
bool man1_flag = true;
double temp1;
double hyp1;
double diff1;
double man2x = 110;
double man2z = -20;
double man2y = 0;
bool man2_flag = true;
double man3x = 130;
double man3z = 10;
double man3y = 0;
bool man3_flag = true;
double man4x = 100;
double man4z = -10;
double man4y = 0;
bool man4_flag = true;
bool h = false;
bool h1 = false;
bool h2 = false;
bool h3 = false;


GLuint tex;
GLuint tex2;
GLuint tex3;
GLuint tex4;
GLuint tex5;
GLuint tex6;
GLuint tex8;
GLuint tex9;

bool onstart = true;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 400;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(5, 0, 1);
Vector Up(0, 1, 0);


int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_locker;
Model_3DS model_wardrobe;
Model_3DS model_man;
Model_3DS model_man1;
Model_3DS model_man2;
Model_3DS model_man3;
Model_3DS model_door;
Model_3DS model_gun;




// Textures
GLTexture tex_ground;
GLTexture tex_snow;
GLTexture tex_walls;



//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);


	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specular);


	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 100.0f, 0.0f, 1.0f };
	GLfloat light_position1[] = { 0.0f, -100.0f, 0.0f, 1.0f };
	GLfloat light_position2[] = { 100.0f, 100.0f, 0.0f, 1.0f };
	GLfloat light_position3[] = { 10.0f, 0.0f, 100.0f, 1.0f };
	GLfloat light_position4[] = { 100.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_position5[] = { 0.0f, 100.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position);
	glLightfv(GL_LIGHT5, GL_POSITION, light_position);
}

void camera(void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on teh x-axis (left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera

}

/*void top(void) {
zpos = 70;
xrot = 90;

}
*/
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}
//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing


	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-300, 0, -300);
	glTexCoord2f(5, 0);
	glVertex3f(300, 0, -300);
	glTexCoord2f(5, 5);
	glVertex3f(300, 0, 300);
	glTexCoord2f(0, 5);
	glVertex3f(-300, 0, 300);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}


void drawAim() {
	glPushMatrix();
	glBegin(GL_LINE);
	glNormal3f(0, 0, 1);	// Set quad normal direction.
	glVertex3f(2, 4, 0);
	glVertex3f(2, -4, 0);
	glVertex3f(-2, 4, 0);
	glVertex3f(-2, -4, 0);
	glEnd();
	glPopMatrix();

}

void tree() {
	// Draw Tree Model
	glPushMatrix();
	glScalef(2, 2, 2);
	model_tree.Draw();
	glPopMatrix();
}


void bullet() {
	glPushMatrix();
	//glScaled(0.4,0.4,0.4);
	glRotated(90, 0, 1, 0);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	glutSolidTorus(0.03, 0.20, 30, 30);
	glutSolidTorus(0.03, 0.10, 30, 30);
	gluCylinder(qobj, 0.20, 0.20, 1, 8, 8);
	glTranslated(0, 0, 1);
	gluCylinder(qobj, 0.20, 0.15, 0.3, 8, 8);
	glTranslated(0, 0, 0.3);
	gluCylinder(qobj, 0.15, 0.15, 0.2, 8, 8);
	glTranslated(0, 0, 0.2);
	gluCylinder(qobj, 0.15, 0, 0.5, 8, 8);

	glPopMatrix();

}

void kmra() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-2.1, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(2.1, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(2.1, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-2.1, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void kmra1() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex3);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-2.1, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(2.1, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(2.1, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-2.1, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void kmra2() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex4);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-2.1, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(2.1, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(2.1, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-2.1, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void kmra_nos() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-1.8, 0, -2.4);
	glTexCoord2f(1, 0);
	glVertex3f(1.8, 0, -2.4);
	glTexCoord2f(1, 1);
	glVertex3f(1.8, 0, 2.4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.8, 0, 2.4);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void kmra_nos1() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex3);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-1.8, 0, -2.4);
	glTexCoord2f(1, 0);
	glVertex3f(1.8, 0, -2.4);
	glTexCoord2f(1, 1);
	glVertex3f(1.8, 0, 2.4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.8, 0, 2.4);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void kmra_nos2() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex4);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-1.8, 0, -2.4);
	glTexCoord2f(1, 0);
	glVertex3f(1.8, 0, -2.4);
	glTexCoord2f(1, 1);
	glVertex3f(1.8, 0, 2.4);
	glTexCoord2f(0, 1);
	glVertex3f(-1.8, 0, 2.4);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void wall() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.


}

void draw_welcome() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex5);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void draw_over() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex6);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void draw_win() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex8);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.


}


void wall2() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex3);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.


}

void wall3() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex4);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-6, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.


}

void wall_side_room3() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex4);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-9, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(9, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(9, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-9, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}
void wall_side_room2() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex3);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-9, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(9, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(9, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-9, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}
void wall_side_room1() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-9, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(9, 0, -6);
	glTexCoord2f(1, 1);
	glVertex3f(9, 0, 6);
	glTexCoord2f(0, 1);
	glVertex3f(-9, 0, 6);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.

}

void room(void) {

	//right
	glPushMatrix();
	glTranslated(0, -6, 0);
	wall_side_room1();
	glPopMatrix();




	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, -9, 0);
	kmra();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, -9, 0);
	kmra();
	glPopMatrix();


	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, -9, -3.6);
	kmra_nos();
	glPopMatrix();



	//roof
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 6, 0);
	wall_side_room1();
	glPopMatrix();



	//back
	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, 9, 0);
	kmra();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, 9, 0);
	kmra();
	glPopMatrix();


	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, 9, -3.6);
	kmra_nos();
	glPopMatrix();
	//


	//left
	glPushMatrix();
	glTranslated(0.0, 6, 0.0);//
	wall_side_room1();
	glPopMatrix();




}
void room2(void) {
	// right
	glPushMatrix();
	glTranslated(0, -6, 0);
	wall_side_room2();
	glPopMatrix();




	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, -9, 0);
	kmra1();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, -9, 0);
	kmra1();
	glPopMatrix();

	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, -9, -3.6);
	kmra_nos1();
	glPopMatrix();



	//roof
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 6, 0);
	wall_side_room2();
	glPopMatrix();





	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, 9, 0);
	kmra1();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, 9, 0);
	kmra1();
	glPopMatrix();

	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, 9, -3.6);
	kmra_nos1();
	glPopMatrix();
	//


	//left
	glPushMatrix();
	glTranslated(0.0, 6, 0.0);//
	wall_side_room2();
	glPopMatrix();



}

void room3(void) {
	// right
	glPushMatrix();
	glTranslated(0, -6, 0);
	wall_side_room3();
	glPopMatrix();




	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, -9, 0);
	kmra2();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, -9, 0);
	kmra2();
	glPopMatrix();


	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, -9, -3.6);
	kmra_nos2();
	glPopMatrix();



	//roof
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 6, 0);
	wall_side_room3();
	glPopMatrix();





	//back ********
	//kmra_shmal
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(3.9, 9, 0);
	kmra2();
	glPopMatrix();

	//kmra_ymen
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(-3.9, 9, 0);
	kmra2();
	glPopMatrix();


	//kmra_nos
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glTranslated(0, 9, -3.6);
	kmra_nos2();
	glPopMatrix();
	//



	//left
	glPushMatrix();
	glTranslated(0.0, 6, 0.0);//
	wall_side_room3();
	glPopMatrix();



}


//=======================================================================
// Display Function
//=======================================================================


//void viewtop(void){
//if (topview == false)
//	camera();
//else
//	top();
//}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/*(
	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	*/
	InitLightSource();

	glLoadIdentity();

	/*
	if (topview == false)
	camera();
	else
	*/

	//viewtop();
	camera();

	if (lives == 0) {
		flag = false;
		////draw end
		glPushMatrix();
		glScalef(4, 4, 4);
		glRotated(90, 0, 0, 1.0);
		glTranslated(6, -36, 0);
		xpos = 180;
		ypos = 20;
		zpos = 0;
		xrot = 0;
		yrot = -90;
		draw_over();
		glPopMatrix();
		////
	}

	if (xpos > -82 && xpos < -80 && zpos > -2.6 && zpos <5.3) {
		//flag = false;
		//draw win
		glPushMatrix();
		glScalef(4, 4, 4);
		glRotated(90, 0, 0, 1.0);
		glTranslated(6, -36, 0);
		xpos = 180;
		ypos = 20;
		zpos = 0;
		xrot = 0;
		yrot = -90;
		draw_win();
		glPopMatrix();
	}


	if (flag == true) {
		if (onstart == false) {
			// Draw Ground
			RenderGround();

			if (Moustafa == false) {
				// Draw Man
				glPushMatrix();
				glTranslatef(man1x, man1y, man1z);
				glRotated(diff1, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				model_man.Draw();
				glPopMatrix();

				// Draw Man1
				glPushMatrix();
				glTranslatef(man2x, man2y, man2z);
				glRotated(45, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				model_man1.Draw();
				glPopMatrix();

				// Draw Man2
				glPushMatrix();
				glTranslatef(man3x, man3y, man3z);
				glRotated(45, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				model_man2.Draw();
				glPopMatrix();

				// Draw Man3
				glPushMatrix();
				glTranslatef(man4x, man4y, man4z);
				glRotated(45, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				model_man3.Draw();
				glPopMatrix();
			}
			//draw tree 
			glPushMatrix();
			glTranslatef(140, 0, 35);
			tree();
			glPopMatrix();
			//draw tree2
			glPushMatrix();
			glTranslatef(140, 0, -35);
			tree();
			glPopMatrix();
			//draw tree3
			glPushMatrix();
			glTranslatef(100, 0, 60);
			tree();
			glPopMatrix();
			//draw tree4
			glPushMatrix();
			glTranslatef(100, 0, -60);
			tree();
			glPopMatrix();

			//draw door 

			glPushMatrix();
			glScalef(0.5, 0.38, 0.5);
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, 280);
			model_door.Draw();

			glPopMatrix();


			//draw gun
			glPushMatrix();
			double x = xpos;
			double y = ypos;
			double z = zpos;

			float xr = xrot;
			float yr = yrot;
			//glTranslatef(0,0,0);

			glTranslatef(x - 30, y - 5, z + 40);


			glScalef(0.04, 0.04, 0.04);
			model_gun.Draw();


			glPopMatrix();

			//draw room1
			glPushMatrix();
			glScalef(4, 4, 4);
			glRotatef(90.f, 1, 0, 0);
			glTranslated(-13, 0, -6);
			room();
			glPopMatrix();

			//Draw room2 
			glPushMatrix();
			glScalef(4, 4, 4);
			glRotatef(90.f, 1, 0, 0);
			glTranslated(6.5, 0, -6);
			room2();
			glPopMatrix();


			//Draw room3 
			glPushMatrix();
			glScalef(4, 4, 4);
			glRotatef(90.f, 1, 0, 0);
			glTranslated(26, 0, -6);
			room3();
			glPopMatrix();


			//sky box
			glPushMatrix();
			//glScaled(2,2,2);

			GLUquadricObj * qobj;
			qobj = gluNewQuadric();
			glTranslated(50, 0, 0);
			glRotated(90, 1, 0, 1);
			if (hany == true) {
				glBindTexture(GL_TEXTURE_2D, tex);
			}
			if (hany == false) {
				glBindTexture(GL_TEXTURE_2D, tex9);
			}
			gluQuadricTexture(qobj, true);
			gluQuadricNormals(qobj, GL_SMOOTH);
			gluSphere(qobj, 350, 350, 350);
			gluDeleteQuadric(qobj);

			glPopMatrix();

			if (z == true) {

				bullet();
				glTranslatef(xpos, ypos, zpos);

			}

		}

		if (onstart) {

			glPushMatrix();
			glScalef(4, 4, 4);
			glRotated(90, 0, 0, 1.0);
			glTranslated(6, -36, 0);
			xpos = 180;
			ypos = 20;
			zpos = 0;
			xrot = 0;
			yrot = -90;
			draw_welcome();
			glPopMatrix();
		}


		if (xpos - man1x < 30) {
			h = true;
		}

		if (h == true) {
			// obj movemnent

			double Vx1 = xpos - man1x;
			double Vz1 = zpos - man1z;
			double hyp1 = sqrt(Vx1*Vx1 + Vz1*Vz1);
			//for(int i = 0 ; i< 100000000 ; i++){
			//trial =true;
			//}
			if (!(temp1 == 0)) {
				double third = sqrt(temp1*temp1 + hyp1*hyp1);
				diff1 = atan(third / temp1) * 180 / PI;
				if (trial == true) {
					printf("the xpos is :  %f  and the zpos is : %f ", xpos, zpos);
					trial = false;
				}
			}
			temp1 = hyp1;


			Vx1 /= hyp1;
			Vz1 /= hyp1;
			if (hyp1 <= 5 && man1_flag == true) {

				model_man.visible = false;
				lives--;
				man1_flag = false;

			}

			man1x += Vx1*speed;
			man1z += Vz1*speed;
		}

		if (xpos - man2x < 30) {
			h3 = true;
		}

		if (h3 == true) {
			// obj movemnent
			double Vx2 = xpos - man2x;
			double Vz2 = zpos - man2z;
			double hyp2 = sqrt(Vx2*Vx2 + Vz2*Vz2);


			Vx2 /= hyp2;
			Vz2 /= hyp2;
			if (hyp2 <= 5 && man2_flag == true) {

				model_man1.visible = false;
				lives--;
				man2_flag = false;

			}

			man2x += Vx2*speed;
			man2z += Vz2*speed;
		}

		if (xpos - man3x < 30) {
			h1 = true;
		}

		if (h1 == true) {
			// obj movemnent
			double Vx3 = xpos - man3x;
			double Vz3 = zpos - man3z;
			double hyp3 = sqrt(Vx3*Vx3 + Vz3*Vz3);


			Vx3 /= hyp3;
			Vz3 /= hyp3;
			if (hyp3 <= 5 && man3_flag == true) {
				model_man2.visible = false;
				lives--;
				man3_flag = false;

			}

			man3x += Vx3*speed;
			man3z += Vz3*speed;
		}

		if (xpos - man1x < 30) {
			h2 = true;
		}

		if (h2 == true) {
			// obj movemnent
			double Vx4 = xpos - man4x;
			double Vz4 = zpos - man4z;
			double hyp4 = sqrt(Vx4*Vx4 + Vz4*Vz4);


			Vx4 /= hyp4;
			Vz4 /= hyp4;
			if (hyp4 <= 5 && man4_flag == true) {

				model_man3.visible = false;
				lives--;
				man4_flag = false;
			}

			man4x += Vx4*speed;
			man4z += Vz4*speed;
		}
	}


	glutSwapBuffers();


}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		xrot += 0.5;
		if (xrot >360) xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 0.5;
		if (xrot < -360) xrot += 360;
	}

	if (key == 'w' && !(zpos == -6) && !(zpos == 6))
	{

		if ((xpos > 139 && xpos < 143) && ((zpos>9.7 && zpos <23) || (zpos < -9.7 && zpos > -23))) {
		}

		else {
			float xrotrad, yrotrad;
			yrotrad = (yrot / 180 * 3.141592654f);
			xrotrad = (xrot / 180 * 3.141592654f);
			xpos = float(sin(yrotrad)) + xpos;
			zpos -= float(cos(yrotrad));
			//ypos -= float(sin(xrotrad));
		}

	}


	if (key == 'n') {
		onstart = false;
	}


	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad));
		zpos = float(cos(yrotrad)) + zpos;
		//ypos = float(sin(xrotrad)) + ypos;
	}

	if (key == 'd')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos = (float(cos(yrotrad)) * 0.2) + xpos;
		zpos = (float(sin(yrotrad)) * 0.2) + zpos;
	}

	if (key == 'a')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;
	}

	if (key == 'x') {
		z = true;
	}
	if (key == 'i') {

		if (hany == true) {
			hany = false;
		}
		else {
			hany = true;
		}
	}

	if (key == 'o') {
		if (Moustafa == false) {
			Moustafa = true;
		}
		else {
			Moustafa = false;
		}
	}
	if (key == '1')
	{
		flag = true;
		model_man.visible = true;
		model_man1.visible = true;
		model_man2.visible = true;
		model_man3.visible = true;
		xrot = 0, yrot = -52, xpos = 180, ypos = 20, zpos = 0;
		man1x = 120;
		man1z = 20;
		man1y = 0;
		man1_flag = true;
		man2x = 110;
		man2z = -20;
		man2y = 0;
		man2_flag = true;
		man3x = 130;
		man3z = 10;
		man3y = 0;
		man3_flag = true;
		man4x = 100;
		man4z = -10;
		man4y = 0;
		man4_flag = true;
		h = false;
		h1 = false;
		h2 = false;
		h3 = false;
		onstart = true;
		lives = 3;
	}


	if (key == 27)
	{
		exit(0);
	}
	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================

void myMotion(int x, int y)
{
	y = HEIGHT - y;
	x = WIDTH - x;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;
	x = WIDTH - x;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

void passM(int x, int y)//passive motion function takes 2 parameters the x and y positions of the mouse
						//it allows the user to make use of the mouse motion without clicking on the mouse buttons
{
	//if (topview == true){
	int diffx = x - lastx; //check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot = (float)diffy + xrot; //set the xrot to xrot with the addition of the difference in the y position
	yrot = (float)diffx + yrot;    //set the xrot to yrot with the addition of the difference in the x position
	if (xrot >90) xrot = 90;
	if (xrot <-90) xrot = -90;
	glutPostRedisplay();
	//}
	//else
	//{
	//xrot = 90;
	//zpos =00;
	//}
}

//=======================================================================
// Reshape Function
//=======================================================================


//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	//model_house.Load("Models/house/house.3ds");
	model_tree.Load("Models/tree/Tree1.3ds");
	//model_wardrobe.Load("Models/wardrobe/Wardrobe.3DS");
	model_man.Load("Models/man/E_man.3ds");
	model_man1.Load("Models/man/E_man.3ds");
	model_man2.Load("Models/man/E_man.3ds");
	model_man3.Load("Models/man/E_man.3ds");

	model_door.Load("Models/door/door.3ds");
	model_gun.Load("Models/gun/gun.3ds");


	// Loading texture files
	tex_ground.Load("Textures/ground3.bmp");
	//tex_walls.Load("Textures/walls.bmp");
	//tex_snow.Load("Textures/snow.bmp");
	loadBMP(&tex2, "Textures/metal3.bmp", true);
	loadBMP(&tex3, "Textures/metal1.bmp", true);
	loadBMP(&tex4, "Textures/metal4.bmp", true);
	loadBMP(&tex5, "Textures/game.bmp", true);
	loadBMP(&tex6, "Textures/game1.bmp", true);
	loadBMP(&tex8, "Textures/game2.bmp", true);
	loadBMP(&tex, "Textures/sky2.bmp", true);
	loadBMP(&tex9, "Textures/sky4-jpg.bmp", true);


}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(50, 50);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutIdleFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	//glutMotionFunc(myMotion);

	//glutMouseFunc(myMouse);


	glutPassiveMotionFunc(passM);



	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}