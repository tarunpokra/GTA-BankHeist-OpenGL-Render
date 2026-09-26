/*
//Tarun Pokra
//3381418 
//Course Project, with option one.
//GRAND THEFT AUTO VICE CITY INSPIRED HEIST.
//Basically this project is inspired by Grand Theft Auto, simply because this is a graphics course so it made sense. The program makes a scene with a background with:
a textured background;
at least five different 3D composite objects, each made up of at least five geometric shapes;
at least two light sources with different lighting colours;
an animation, interaction, or shadow effect;
an atmospheric attenuation effect.
Basically, inspired by GTA video games, there are thieves at a central bank trying to flee, but there is one cop that does justice. the police car lights are flashing, etc.
You can also rotate the program for other angles as well.
//theres also tanks, and swat helicopters, etc, and money bills all over the ground.
////////////////////NOTE: I used vs code to edit, but compiled and ran everything in the MSYS2 MINGW64 TERMINAL.///////// OBVIOUSLY ALL
// REQUIRED LIBRARIES AND INSTALL FILES WERE PROPERLY PLACED "fREEGLUT", ETC. Screenshots of output and my local desktop terminal are given.
Here are some routines similar structure set up to assignments:
int main - intit. glut library and createsthe display windowIt also calls several routines to display stuff. also right click menu.
init. -  background colour of window depth testing, lighting, paramaters, enables fog in the scene, stores the current time.
reshaping -the viewing projection propertie
display - the viewing properties
rendering - displays background scene objects and textured walls
drawScene -displays composite objects. 
flashing on the passage of time, lights will simulate flashing cop car flashing lights
makeImage download and load images file then stores color data values for use in texturing
rotMenu = menu callback function which allows user to rotate  view in either a clockwise/anti etc.
*/
#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include "objFile.h"
#include "materialStuff.h"
#include <time.h>
#include "vector3.h"
#define PI 3.14159265 //removed it earlier as a CONSTANT. 
using namespace std; //less keys after this.
//  view position
float rotVal = (PI / 3); //init values placed.
float viewRadius = 27.0;
vector3 viewer(viewRadius * cosf(rotVal), 
20, viewRadius * sinf(rotVal));
// lighting constants
static const  GLfloat lightPosition0[] = 
{ 30.0, 100.0, 20.0, 0.0 };
static   const GLfloat lightPosition1 []   = 
{ 10.5, 3.0 , -7.0, 1.0 };
static const GLfloat lightPosition2[ ] = 
{ 9.5, 3.0,  -9.0, 1.0 };
static const   GLfloat white_light[] = 
{ 1.0, 1.0, 1.0,  1.0 } ;
static const  GLfloat red_light[] = 
{ 1.0, 0.0, 0.0, 1.0 };
static const GLfloat blue_light[] = 
{ 0.0, 0.0, 1.0, 1.0 };
static const GLfloat red_direction[] = 
{ 0.0, 0.0, -1.0 };
static const GLfloat blue_direction[]  = 
{ 0.0, 0.0, -1.0 };
static const GLfloat spot_cutoff =  45.0 ;
static const GLfloat spot_exp = 2.5;
static const GLfloat lmodel_ambient[] = 
{ 0.7, 0.7, 0.7, 1.0 };
GLubyte *image;
//ptr?
//unsigned char * l_texture;
GLubyte * l_texture;
BITMAPFILEHEADER fileheader; 
BITMAPINFOHEADER infoheader;
RGBTRIPLE rgb;
GLuint texName;
// create object to access scene elemets
objects obs;
// time storage variables
clock_t start_time, time_now;
// load texture file and store values
void makeImage () 
{
	int i, j= 0 ;
	FILE *l_file ;
	string fn =  "city_downtown_cartoon.bmp"; //made this has for a background. 
	const char * filename =  fn.c_str ();
	// open image file, return if error
	fopen_s(&l_file, filename, "rb");
	if ( l_file ==  NULL ) return;
	// read file header and header info

	fread (&fileheader, sizeof(fileheader ), 1, l_file ) ;
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);
	// allocate space for the image file
	l_texture = (GLubyte *) malloc(
		infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	// read data
	j =  0 ;
	for (i=0; i < infoheader.biWidth*
		infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file); 
		l_texture[j+0] = (GLubyte) rgb.rgbtRed; // Red 
		l_texture[j+1] = (GLubyte) rgb.rgbtGreen; // Green 
		l_texture[j+2] = (GLubyte) rgb.rgbtBlue; // blue 
		l_texture[j+3] = (GLubyte) 255; // Alpha
		j += 4 ; // next pos.
	}
	fclose(l_file ) ; // Closes the file stream
}
// initialize
void initialize()
{
	//background color
	
	glClearColor(0.5, 0.5, 0.5,  0.0 ) ;
	// allow depth checking
	glEnable(GL_DEPTH_TEST ) ;
	//enable lightings., etc.
	// the sun light here.
	glEnable(GL_LIGHTING ) ;
	glEnable(GL_LIGHT0 ) ;
	glLightfv(GL_LIGHT0, 
		GL_POSITION, lightPosition0) ;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light ) ;
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light );
	glEnable(GL_LIGHT1); //red l
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, 
		red_direction);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);
	// blue light- not enabled.
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT2, 
		GL_SPOT_DIRECTION, blue_direction ) ;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light ) ;
	glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light) ;
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff );
	glLightf ( GL_LIGHT2, GL_SPOT_EXPONENT, spot_exp);
	// lighting parameters, etc.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient) ;
	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 }; //i made some fog.
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.02);
	glFogf(GL_FOG_START, -45.0);
	glFogf(GL_FOG_END, 45.0 );
	glEnable(GL_FOG);
	makeImage(); //textures
	glPixelStorei( GL_UNPACK_ALIGNMENT,  1) ;
	glGenTextures(1 , &texName ) ;
	glBindTexture(GL_TEXTURE_2D,  texName ) ;
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MAG_FILTER, GL_LINEAR  );
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		infoheader.biWidth, infoheader.biHeight, 
		0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture) ;
	// time	
	start_time = clock () ;
}
// put every elements in positions, etc.
void drawScene()
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);

	// Draw bank
	glPushMatrix();
		glTranslatef(-20.0, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glScalef(1.3, 1.3, 1.3);
		obs.drawBank();
	glPopMatrix();

	// Draw 5 police cars and 5 officers in a row
	for (int i = 0; i < 5; ++i)
	{
		// Cop car
		glPushMatrix();
			glTranslatef(10.0f + i * 8.0f, 0.0f, -8.0f);
			glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.5, 0.5, 0.5);
			obs.drawCopCar();
		glPopMatrix();
		// Officer next to the car
		glPushMatrix();
			glTranslatef(10.0f + i * 8.0f, 0.0f, -2.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.5, 0.5, 0.5);
			obs.drawCop();
		glPopMatrix();
	}

	// Robber 1
	glPushMatrix();
		glTranslatef(2.0, 0.0, 5.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		obs.drawRobber1();
	glPopMatrix();
	// Robber 2
	glPushMatrix();
		glTranslatef(3.0, 0.0, 10.0);
		glRotatef(-60.0, 0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		obs.drawRobber2();
	glPopMatrix();
	// Robber 3 (new)
	glPushMatrix();
		glTranslatef(5.0, 0.0, 7.0);  // Adjust position as needed
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		obs.drawRobber1(); // or use drawRobber2() if you want variety
	glPopMatrix();
/*
	// Police Helicopter in the air
	glPushMatrix();
    	glTranslatef(0.0f, 10.0f, -5.0f); // Position above the scene
    	glRotatef(30.0f, 0.0f, 1.0f, 0.0f); // Rotate slightly for realism
    	glScalef(1.5f, 1.5f, 1.5f); // Make it bigger if needed
    	obs.drawHelicopter();
	glPopMatrix();
*/
// Police Helicopter in the air
// Helicopter 
glPushMatrix();
    glTranslatef(4.0f, 15.0f, -10.0f);   // raise y to 15.0f
    glRotatef(230.0f, 0.0f, 1.0f, 0.0f);
    glScalef(2.5f, 2.5f, 2.5f);
    obs.drawHelicopter();
glPopMatrix();
glDisable(GL_LIGHTING);
srand(42);
for (int i = 0; i < 130; ++i) {
    float x = -20.0f + static_cast<float>(rand() % 60);
    float z = -20.0f + static_cast<float>(rand() % 60);
    float angle = rand() % 360;
    glPushMatrix();
        glTranslatef(x, 0.01f, z);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        obs.drawDollarBill();
    glPopMatrix();
}
// Set dark green color (disable lighting temporarily)
glDisable(GL_LIGHTING);
glColor3f(0.0f, 0.3f, 0.0f);  // dark green
glPushMatrix();
    glTranslatef(10.0f, 0.0f, -15.0f);  // near first police car  // position in front of bank
    glRotatef(216.0f, 0.0f, 1.0f, 0.0f);
    glScalef(3.0f, 3.0f, 3.0f);          // size bigger
    obs.drawTank();
glPopMatrix();
glEnable(GL_LIGHTING);  // re-enable lighting after
}
void render()
{//rendering here.
	//backgound detail
	glBegin(GL_QUADS ) ;
		setMaterial ( 14);
		glVertex3f(-30.0, -0.02, -30.0);
		glVertex3f(-30.0, -0.02, 30.0) ;
		glVertex3f(30.0, -0.02, 30.0);
		glVertex3f(30.0, -0.02, -30.0 ) ;
		// roa
		setMaterial(16 ) ;
		glColor3f(0.1,  0.1, 0.1 ) ;
		glVertex3f(12.0, -0.01, -30.0 ) ;
		glVertex3f ( 12.0, -0.01, 30.0 );
		glVertex3f(-8.0,  -0.01, 30.0);
		glVertex3f(-8.0, -0.01, -30.0 );
	glEnd () ;
	// text walls.
	glEnable( GL_TEXTURE_2D) ;
	glBegin (GL_QUADS);
		glTexCoord2d(0.0, 0.0); 
		glVertex3f(-30.0, -0.01, -30.0 ) ;
		glTexCoord2d (1.0, 0.0); 
		glVertex3f(30.0, -0.01, -30.0);
		glTexCoord2d (1.0, 1.0); 
		glVertex3f(30.0, 30.0, -30.0);
		glTexCoord2d(0.0,  1.0); 
		glVertex3f( -30.0, 30.0, -30.0);
		glTexCoord2d(0.0, 0.0); 
		glVertex3f(-30.0, -0.01, 30.0);
		glTexCoord2d(1.0, 0.0); glVertex3f
		(-30.0, -0.01, -30.0);
	
		glTexCoord2d(1.0, 1.0); 
		glVertex3f(-30.0, 30.0, -30.0);
		glTexCoord2d(0.0, 1.0); 
		glVertex3f(-30.0, 30.0, 30.0 ) ;
		glTexCoord2d(0.0, 0.0); glVertex3f (30.0, -0.01, -30.0);
		glTexCoord2d(1.0, 0.0); glVertex3f(30.0, -0.01, 30.0);
		glTexCoord2d(1.0, 1.0); glVertex3f(30.0,
			 30.0, 30.0);
		glTexCoord2d(0.0, 1.0); glVertex3f(30.0, 30.0, -30.0 ) ;
		glTexCoord2d(0.0, 0.0); glVertex3f(30.0, -0.01,  30.0) ;
		glTexCoord2d(1.0, 0.0); glVertex3f(-30.0, -0.01, 30.0);
		glTexCoord2d(1.0, 1.0); glVertex3f(-30.0, 30.0, 30.0);
		glTexCoord2d(0.0, 1.0
		); glVertex3f(30.0, 30.0, 30.0);
	glEnd();
	glDisable(GL_TEXTURE_2D) ;
	// road street linings. 
	setMaterial(17);
	// se properties
	glLineWidth(10.0) ;
	glLineStipple(3, 0x00FF) ;
	glEnable(GL_LINE_STIPPLE );
	glBegin(GL_LINES );
		glVertex3f(2.0, 0.0, 29.99 ) ;
		glVertex3f(2.0, 0.0, -29.99 ) ;
	glEnd ();
	glDisable(GL_LINE_STIPPLE) ;
	glLineWidth(1.0) ;
	// create more objs.
	glPushMatrix() ;
	glTranslatef(0.0, 0.01, 0.0);
		drawScene();
	glPopMatrix();
}
// showing reg.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | 
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity () ;
	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //initial values.
	render();
	glutSwapBuffers () ;
}
// alternate lighting.
void flash()
{	
	time_now = clock();
	if (((time_now - start_time) / CLOCKS_PER_SEC ) >= 1.0)
	{
		if (glIsEnabled(GL_LIGHT1)) 
		{
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
		}
		else
		{
			glDisable(GL_LIGHT2);
			glEnable(GL_LIGHT1);
		}
		start_time =  time_now ;
		display () ;
	}
}
// reshape registry
void reshape(int w, int h) // w and h.
{
	glViewport(0, 0, (GLsizei ) w,  ( GLsizei) h ) ;
	glMatrixMode(GL_PROJECTION );
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0); //perspective
	glMatrixMode(GL_MODELVIEW 
	);
}
// rotating the on the angle.
void rotMenu(GLint selection)
{	
	if (selection == 0) //clockwise
	{
		rotVal += PI  / 6;
		if (rotVal  >= ((2 * PI) - (PI / 180 ) ) )
			rotVal =  0.0 ;
	}
	// rotate scene anticlockwise (clockwise view)
	else
	{	
		rotVal -= 3.14159 / 6 ;
		if (rotVal <= (-(2 * PI) + (PI / 180)))
			rotVal = 0.0 ;
	}
	viewer.x = viewRadius * cosf(rotVal); //view co-ordinates.
	viewer.z =viewRadius *  sinf ( rotVal ) ;
}
// int main stuff
int main(int argc, char **argv)
{
	glutInit( &argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE |
		 GLUT_RGB | GLUT_DEPTH) ;
	glutInitWindowSize(500, 500);
  	glutInitWindowPosition(50, 50);
	int windowHandle = glutCreateWindow("Course Project GTA VICE CITY FAILED HEIST");
	glutSetWindow(windowHandle );
	glutDisplayFunc( display) ;
	glutReshapeFunc (reshape);
	glutIdleFunc( flash);
	initialize();
	glutCreateMenu(rotMenu); //sub menu for rotating, etc.
		glutAddMenuEntry("rotate clockwise", 0);
		glutAddMenuEntry("Rotate anticlockwise " , 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON ) ; // made into the right click.
    glutMainLoop();
}
// done. 