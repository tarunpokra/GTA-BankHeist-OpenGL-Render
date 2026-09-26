/*//Tarun Pokra
//3381418 
//material file
//july 24th, 2025
he purpose of the class "objects" here is create basic 2D and 3D shapes that can be 
geometrically transformed to show real world objects placed in the render.
a lot of Routines here.
objects - Initializes variables needed to make a circle and cylinder
drawCircle - Draws a circle, rad1 circle is
			made up of 20 individual triangle slices.
drawSquareraws  square in the x y plane,
drawCubsquares to form a unit cube with  bottom  as  square above.
drawCylinde a cylinder of height 1, rad 1 by connecting 2 of  circles above wit a bunch rectangles.
drawLimb  Draws a small and a limb, such as an arm, an places a sphere at the end of as a hand.
drawBodyrent sizes, stacked on top of one another to represent ower body, waist, and torso. sphere for head
drawGun Transformsseries of cubes to represent a gun.
drawCop Positions  body  limbs above into a shape representing a person standing with their gun drawn and pointed in front of them 
drawCopCar of cubes, rectangles and triangles to simulate the body of a police car with lights on top.The wheels are represented with cylinders.
drawRobber1  Arranges the body parts mentioned above to represent a man holding his hands in the air.  A gun is placed in front of this figure, as if it is dropped on the ground.
drawRobber2 - Arranges the body parts mentioned above to represent a person lying dead in an awkward position.  2 red circles are positioned near the body to represent a blood stain, and 
a sphere is placed near the body to represent a shoe that came off. etc. 
drawBank Uses a series of cubes, rectangles, triangles, and cylinders to represent a  building with a tri. roof and columns along the front face.
drawDollorbill - makes about 130 bills randomly on the ground, using a for loop, increment upto 130
drawTank - a green military tank is made, pointing at the bank.
drawHelicopter - theres a black helicopter circuling the bank by the police cars.
there was blood on the ground from the robbers, but i deleted it to amke the render/scene more appropruiate for a course project.
*/
#include "objFile.h"
#include <GL/freeglut.h>
#include "materialStuff.h"
#include <math.h>
#define PI 3.14159265
#define SLICES 20
objects::objects()
{
	// set initial circle values
	radius = 1.0;
	stepRad = (2 * PI) / SLICES;
	stepDeg = 360.0 / SLICES ;
	// unit circle initial points
	uCircle [0][0] = 0.0;
	uCircle [0][1] = 0.0;
	uCircle [0][2] = 0.0;
	// set points for circles and cylinders
	for (int i = 0; i <= SLICES; ++i)
	{	
		uCircle[i+1][0] = radius * cosf(stepRad * i ) ;	
		uCircle[i+1][1] = 0.0;
		uCircle[i+1][2] = radius * sinf(stepRad *i ) ;
		uCylinder[2*i][0] = uCircle[i+ 1 ][   0];
		uCylinder[2*i][1] = uCircle[i+ 1][1];
		
		uCylinder[2*i][2] = uCircle [i +  1][2];
		uCylinder[2*i+1][0] = uCircle[i+1][0 ] ;
		uCylinder[2*i+1][1] = uCircle[i+1][1]  + radius ;
		uCylinder[2*i+1] [ 2 ]  = uCircle [i+1][2] ;
	}
}
//make circle
void objects::drawCircle()
{
	glBegin(GL_TRIANGLE_FAN);		
		for(int i = 0; i < SLICES  + 2 ; i++ )
		{
			glVertex3fv(uCircle[i ] ) ;
		}
	glEnd();
}
// draw a unit square
void objects::drawSquare ()
{
	glBegin(GL_QUADS);	
		glVertex3f(-0.5, 0.0, 0.5 ) ;
		glVertex3f(0.5, 0.0, 0.5 ) ;
		glVertex3f(0.5, 0.0 ,  -0.5 ) ;
		glVertex3f(-0.5, 0.0, -0.5);
	glEnd();
}
// unit cube

void objects::drawCube()
{
	glMatrixMode(GL_MODELVIEW
	) ;
	drawSquare();
	glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0 ) ;
		drawSquare() ;
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.5, 0.5, 0.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		drawSquare();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.5, 0.5, 0.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		drawSquare();
	glPopMatrix() ;
	glPushMatrix();
		glTranslatef(0.0, 0.5, 0.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		drawSquare() ;
	glPopMatrix() ;
	glPushMatrix();
		glTranslatef(0.0, 0.5, -0.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		drawSquare();
	glPopMatrix();
}
//unit cylinder made here.
void objects::drawCylinder()
{
	glMatrixMode(GL_MODELVIEW);
	drawCircle();
	glPushMatrix();
		glTranslatef(0.0, radius, 0.0);
		drawCircle() ;
	glPopMatrix();
	glBegin(GL_QUADS ) ;
		for(int i = 0; i < SLICES; ++i)
		{
			glVertex3fv(uCylinder [2*i + 2 ]);	
			glVertex3fv ( uCylinder [2*i+3]) ;
			glVertex3fv(uCylinder[2*i+1]) ;
			glVertex3fv(uCylinder[2*i]);
		}
	glEnd();
}
//limb of 2 cylinders for  arm/leg  sphere for the hand/foot, etc.
void objects::drawLimb(int base, int forelimb, int appendage)
{
	glMatrixMode(GL_MODELVIEW);	
	setMaterial(base );
	glPushMatrix();
		glScalef( 0.5, 0.5,  0.5 );
		drawCylinder();
	glPopMatrix();
	setMaterial(forelimb);
	glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glScalef(0.5, 1.5, 0.5);
		drawCylinder();
	glPopMatrix();
	setMaterial(appendage) ;
	glPushMatrix();
		glTranslatef(0.0, 2.5, 0.0);
		glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}
// draw a body consisting of 3 cylinders for the trunk, and a sphere for the head
void objects::drawBody(int bottom, int belt, int torso, int head)
{	
	glMatrixMode(GL_MODELVIEW);	
	setMaterial(bottom);
	glPushMatrix();
		glScalef(1.0, 0.4, 1.0);
		drawCylinder() ;
	glPopMatrix();
	setMaterial(belt);
	glPushMatrix();
		glTranslatef(0.0, 0.4, 0.0);
		glScalef(1.0, 0.1, 1.0 ) ;
		drawCylinder() ;
	glPopMatrix();
	setMaterial(torso);
	glPushMatrix();
		glTranslatef(0.0, 0.5, .0);
		glScalef(1.0, 1.5, 1.0);
		drawCylinder();
	glPopMatrix();
	setMaterial(head);
	glPushMatrix();
		glTranslatef(0.0, 3.0, 0.0);
		glutSolidSphere(1.0, 20, 20);
	glPopMatrix();
}
//gun made of cubes and a circles etc.
void objects::drawGun()
{
	glMatrixMode(GL_MODELVIEW);	
	// barre
	setMaterial(1);
	glPushMatrix();
		glScalef(3.0, 1.0, 1.0 );
		drawCube();
	glPopMatrix();
	// handles
	glPushMatrix();
		glTranslatef(1.0, -1.0, 0.0);
		drawCube();
	glPopMatrix();
	// sights and stuff, etc.
	glPushMatrix();
		glTranslatef( 1.0, 1.0 , 0.25);
		glScalef(0.25, 0.25, 0.25 ) ;
		drawCube();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.0, 1.0, -0.25 ) ; 
		glScalef(0.25, 0.25, 0.25) ;
		drawCube();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.25, 1.0 ,  0.0 );
		glScalef(0.25, 0.25, 0.25);
		drawCube();
	glPopMatrix();
	// inside barrel
	setMaterial(0);
	glPushMatrix();
		glTranslatef(-1.01, 0.25, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0 ) ;
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(0.5, 1.0, 0.5);
		drawCircle();
	glPopMatrix();
}
// make police officer pointing gun
void objects::drawCop ()
{	
	glMatrixMode(GL_MODELVIEW);	
	glPushMatrix () ;
		glTranslatef(0.0, 3.0, 0.0 );
		drawBody(8, 12, 7, 4 ) ;
		//the arms
		glPushMatrix () ;
			glTranslatef ( 1.0, 1.5 ,  0.0 );
			glRotatef(-90.0, 0.0, 1.0, 0.0 ) ;
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			drawLimb(7, 4, 4) ;
		glPopMatrix() ;
		glPushMatrix ();
			glTranslatef(-1.0, 1.9 , 0.0 ) ;
			glRotatef(-150.0, 1.0, 0.0, 0.0); 
			drawLimb(7, 4, 4);
//changing x to z
		glPopMatrix();
		// the legs
		glPushMatrix() ;
			glTranslatef(-0.5, 0.0, 0.0) ;
			glRotatef(160.0, 1.0, 0.0 , 0.0 );
			drawLimb(8, 8, 1 );
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.5, 0.0, 0.0 );
			glRotatef(-160.0, 1.0, 0.0 , 0.0);
			drawLimb(8, 8 , 1 );
		glPopMatrix();
		// the pistol
		glPushMatrix() ;
			glTranslatef(1.0, 2.0, 3.0 );
			glRotatef(90.0, 0.0, 1.0 ,  0.0 );
			glScalef(0.5, 0.5, 0.5 );
			drawGun ();
		glPopMatrix ();
	glPopMatrix ();
}
// draw a police car with cubes, rectangles and triangles

void objects::drawCopCar()
{	
	glMatrixMode(GL_MODELVIEW) ;	
	glPushMatrix() ;
		glTranslatef(0.0, 1.0, 0.0);
		// draw lower body
		setMaterial(2);
		glPushMatrix();
			glScalef(5.0, 2.0, 8.0);
			drawCube();
		glPopMatrix() ;
		glBegin(GL_QUADS);
			glVertex3f(-2.5, 0.0, 4.0);
			glVertex3f(-2.5, 0.0, 6.0);
			glVertex3f(2.5, 0.0, 6.0);
			glVertex3f(2.5, 0.0, 4.0);
			glVertex3f(-2.5, 0.0, 6.0);			
			glVertex3f(2.5, 0.0, 6.0);			
			glVertex3f(2.5, 1.0, 6.0);			
			glVertex3f(-2.5, 1.0, 6.0);
			glVertex3f(-2.5, 1.0, 6.0);			
			glVertex3f(2.5, 1.0, 6.0);			
			glVertex3f(2.5, 2.0, 4.0);			
			glVertex3f(-2.5, 2.0, 4.0);		
			glVertex3f(-2.5, 0.0, 4.0);		
			glVertex3f(-2.5, 0.0, 6.0);			
			glVertex3f(-2.5, 1.0, 6.0);			
			glVertex3f(-2.5, 2.0, 4.0);			
			glVertex3f(2.5, 0.0, 4.0);		
			glVertex3f(2.5, 2.0, 4.0);			
			glVertex3f(2.5, 1.0, 6.0);			
			glVertex3f(2.5, 0.0, 6.0);		
		glEnd();
		// draw upper body
		setMaterial(1);		
		glPushMatrix();		
			glTranslatef(0.0, 2.0, 0.0);			
			glScalef(5.0, 2.0, 5.0);			
			drawCube();
		glPopMatrix();
		// draw lighting
		setMaterial ( 10 ) ;  // red
		glPushMatrix();
			glTranslatef(1.25, 4.0, 0.0);		
			glScalef(2.5, 1.0, 1.0)		;
			drawCube();
		glPopMatrix();
		setMaterial(9);  // blue
		glPushMatrix();					glTranslatef(-1.25, 4.0, 0.0);
			
			glScalef(2.5, 1.0, 1.0);
			drawCube();
		glPopMatrix();
	// draw windshields	
		setMaterial(6);	
		glBegin(GL_QUADS);	
			glVertex3f(-2.5, 2.0, 4.0);
			glVertex3f(2.5, 2.0, 4.0);
					glVertex3f(2.5, 4.0, 2.5);
			
			glVertex3f(-2.5, 4.0, 2.5);	
		glVertex3f(-2.5, 2.0, -3.5) ;	
			glVertex3f(2.5, 2.0, -3.5);		
			glVertex3f(2.5, 4.0, -2.5);		
			glVertex3f(-2.5, 4.0, -2.5);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(-2.5, 2.0, 4.0);	
			glVertex3f(-2.5, 4.0, 2.5);
			glVertex3f(-2.5, 2.0, 2.5);
			glVertex3f(2.5, 2.0, 4.0);
			glVertex3f(2.5, 4.0, 2.5);			
			glVertex3f(2.5, 2.0, 2.5);
			glVertex3f(-2.5, 2.0, -3.5);		
			glVertex3f(-2.5, 2.0, -2.5);		
			glVertex3f(-2.5, 4.0, -2.5);		
		glVertex3f(2.5, 2.0, -3.5) ;			
			glVertex3f(2.5, 2.0, -2.5);			
			glVertex3f(2.5, 4.0, -2.5);
		glEnd();
		// make windows.etc
		//glPushMatrix();
			glPushMatrix();
				glTranslatef(-2.51, 2.75, 1.25);				
				glRotatef(90.0, 0.0, 1.0, 0.0);				
				glRotatef(90.0, 1.0, 0.0, 0.0);				
				glScalef(1.5, 1.0, 1.25);				
				drawSquare();
			glPopMatrix();
			glPushMatrix();				
				glTranslatef(-2.51, 2.75, -1.25);				
				glRotatef(90.0, 0.0, 1.0, 0.0);				
				glRotatef(90.0, 1.0, 0.0, 0.0);				
				glScalef(1.5, 1.0, 1.25);				
				drawSquare();				
				glRotatef(180.0, 0.0, 1.0, 0.0);			
				drawSquare();
			glPopMatrix();
			glRotatef(180.0, 0.0, 1.0, 0.0);
			glPushMatrix();			
				glTranslatef(-2.51, 2.75, 1.25);			
				glRotatef(90.0, 0.0, 1.0, 0.0);				
				glRotatef(90.0, 1.0, 0.0, 0.0);				
				glScalef(1.5, 1.0, 1.25);				
				drawSquare();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.51, 2.75, -1.25);			
				glRotatef(90.0, 0.0, 1.0, 0.0);				
				glRotatef(90.0, 1.0, 0.0, 0.0);				
				glScalef(1.5, 1.0, 1.25);			
				drawSquare();			
				glRotatef(180.0, 0.0, 1.0, 0.0);			
				drawSquare();
			glPopMatrix();
		//glPopMatrix();
		// draw wheels
		setMaterial(0);		
		glPushMatrix();		
			glTranslatef(-2.5, 0.0, 4.0);			
			glRotatef(90.0, 0.0, 0.0, 1.0);			
			glScalef(1.0, 0.5, 1.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(2.5, 0.0, 4.0 ) ;		
			glRotatef(-90.0, 0.0, 0.0, 1.0);
			glScalef(1.0, 0.5, 1.0);			
			drawCylinder();		
		glPopMatrix();
		glPushMatrix();		
			glTranslatef(-2.5, 0.0, -2.5);		
			glRotatef(90.0, 0.0, 0.0, 1.0);			
			glScalef(1.0, 0.5, 1.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(2.5, 0.0, -2.5);			
			glRotatef(-90.0, 0.0, 0.0, 1.0);			
			glScalef(1.0, 0.5, 1.0);			
			drawCylinder();
		glPopMatrix();
	glPopMatrix();
}
// draw a robber with hands raised using the body, etc. parts, 
void objects::drawRobber1()
{
	glPushMatrix();
		glTranslatef(0.0, 3.0, 0.0);
		drawBody(0, 0, 0, 4);
		//arm		
		glPushMatrix();			
			glTranslatef(1.0, 1.5, 0.0);			
			glRotatef(-20.0, 0.0, 0.0, 1.0);		
			drawLimb(0, 0, 4);
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(-1.0, 1.5, 0.0);			
			glRotatef(20.0, 0.0, 0.0, 1.0);			
			drawLimb(0, 0, 4);
		glPopMatrix();
		//legs		
		glPushMatrix();		
			glTranslatef(-0.5, 0.0, 0.0);			
			glRotatef(180.0, 1.0, 0.0, 0.0);		
			drawLimb(0, 0, 0);
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(0.5, 0.0, 0.0);			
			glRotatef(180.0, 1.0, 0.0, 0.0);			
			drawLimb(0, 0, 0);
		glPopMatrix();
	glPopMatrix();
	// gun
	glPushMatrix();
		glTranslatef(0.0, 0.0, 3.0) ;
		glRotatef(45.0, 0.0, 1.0, 0.0);	
		glRotatef(90.0, 1.0, 0.0, 0.0);		
		glScalef(0.5, 0.5, 0.5);				drawGun();
	glPopMatrix();
}
// draw a dead robber with blood using the body part routines above

void objects::drawRobber2()
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0) ;
		glRotatef(90.0, 1.0, 0.0, 0.0);
		drawBody(0, 0, 0 , 5 );
		//arms
		glPushMatrix();
			glTranslatef(0.8, 1.6, 0.0);
			glRotatef(-140.0, 0.0, 0.0, 1.0);
			drawLimb(0, 0, 5) ;
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.8, 1.5, 0.0);
			glRotatef(40.0, 0.0, 0.0, 1.0);
			drawLimb(0, 0, 5) ;
		glPopMatrix();
		//legs
		glPushMatrix();
			glTranslatef(-0.5, 0.0, 0.0 );
			glRotatef ( 180.0 , 1.0, 0.0, 0.0);
			drawLimb(0, 0, 0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef(40.0, 0.0, 0.0, 1.0);			
			glRotatef(180.0, 1.0, 0.0, 0.0);						drawLimb(0, 0, 5);
		glPopMatrix();
	glPopMatrix();	
	// a missing shoe
	setMaterial(1);	
	glPushMatrix();	
		glTranslatef(3.0, 0.5, -5.0);
		glutSolidSphere(0.5, 20, 20);
	glPopMatrix();	
}
	// draw a blood stain 
/*
	setMaterial(13); // COMMENTED OUT TO MAKE SCENE MORE APPRORIPATE. ETC.
	glPushMatrix();
		glTranslatef(1.0, 0.01, 2.5)
		drawCircle()
		glPushMatrix()
			glTranslatef(0.5, 0.00, 1.0)
			glScalef(1.0, 0.0, 0.5)
			drawCircle(
		glPopMatrix()
	glPopMatrix()
}
*/
// draw a bank building with cylinders, triangles, squares cubes etc.
void objects::drawBank()
{
	glMatrixMode(GL_MODELVIEW);	
	//draw main buildin
	setMaterial(3);
	glPushMatrix();	
		glScalef(20.0, 10.0, 20.0);	
		drawCube();
	glPopMatrix();	
	// draw steps
	setMaterial(15);
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 11.5);
		glScalef(20.0, 3.0, 3.0);		
		drawCube();
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.66);			
			glScalef(1.0, 0.66, 0.33);			
			drawCube();			
			glPushMatrix();			
				glTranslatef(0.0, 0.0, 1.0);
								glScalef(1.0, 0.5, 1.0);
				
				drawCube();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	// draw columns
	setMaterial(3);
	glPushMatrix();
		glTranslatef(-9.0, 3.0, 12.0);	
		glScalef(0.5, 7.0, 0.5);		
		drawCylinder();
		glPushMatrix();
			glTranslatef(4.0, 0.0, 0.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(8.0, 0.0, 0.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(28.0, 0.0, 0.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(32.0, 0.0, 0.0);			
			drawCylinder();
		glPopMatrix();
		glPushMatrix();			
			glTranslatef(36.0, 0.0, 0.0);			
			drawCylinder();
		glPopMatrix();
	glPopMatrix();		
	//  roof
	setMaterial(15);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-10.0, 10.0, -10.0);	
		glVertex3f(-10.0, 10.0, 13.0);		
		glVertex3f(10.0, 10.0, -10.0);		
		glVertex3f(10.0, 10.0, 13.0);		
		glVertex3f(0.0, 15.0, -10.0);		
		glVertex3f(0.0, 15.0, 13.0);		
		glVertex3f(-10.0, 10.0, -10.0);		
		glVertex3f(-10.0, 10.0, 13.0);
	glEnd();
	glBegin(GL_TRIANGLES);		
		glVertex3f(-10.0, 10.0, 13.0);		
		glVertex3f(10.0, 10.0, 13.0);		
		glVertex3f(0.0, 15.0, 13.0);		
		glVertex3f(-10.0, 10.0, -10.0);		
		glVertex3f(10.0, 10.0, -10.0);				glVertex3f(0.0, 15.0, -10.0);

	glEnd();
	setMaterial(3);
	glBegin(GL_TRIANGLES);
		glVertex3f(-8.0, 11.0, 13.01);	
		glVertex3f(8.0, 11.0, 13.01);				glVertex3f(0.0, 14.0, 13.01);
	glEnd();
	// draw doors	
	setMaterial(12);	
	glBegin(GL_QUADS);	
		glVertex3f(-3.0, 3.0, 10.01);	
		glVertex3f(0.0, 3.0, 10.01);		
		glVertex3f(0.0, 8.0, 10.01);		
		glVertex3f(-3.0, 8.0, 10.01);
		glVertex3f(0.0, 3.0, 10.01);		
		glVertex3f(3.0, 3.0, 10.01);		
		glVertex3f(3.0, 8.0, 10.01);		
		glVertex3f(0.0, 8.0, 10.01);
	glEnd();		
}
/*
void objects::drawHelicopter() {
    // Basic helicopter body
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);  // dark gray
        glScalef(2.0f, 0.5f, 0.5f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tail
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glScalef(1.5f, 0.1f, 0.1f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Main rotor
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);  // black blades
        glTranslatef(0.0f, 0.3f, 0.0f);
        glScalef(3.0f, 0.05f, 0.1f);
        glutSolidCube(1.0);
    glPopMatrix();
}
*/

/*
void objects::drawHelicopter() {
    // Helicopter body (fuselage)
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f); // Dark gray body
        glScalef(2.0f, 0.5f, 0.5f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cockpit (rounded front)
    glPushMatrix();
        glColor3f(0.3f, 0.3f, 0.3f); // Slightly lighter gray
        glTranslatef(1.1f, 0.0f, 0.0f);
        glutSolidSphere(0.3f, 16, 16);
    glPopMatrix();

    // Tail boom
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(-1.8f, 0.0f, 0.0f);
        glScalef(2.0f, 0.1f, 0.1f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Tail rotor
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(-2.8f, 0.0f, 0.0f);
        glScalef(0.6f, 0.05f, 0.6f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Main rotor
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f); // Black rotor blades
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScalef(3.5f, 0.05f, 0.3f);
        glutSolidCube(1.0);
    glPopMatrix();
}
*/
void objects::drawHelicopter()
{
    // Body of helicopter
    glColor3f(0.3f, 0.3f, 0.3f); // dark grey
    glutSolidCube(1.0f);

    // Tail
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -1.5f);
        glScalef(0.2f, 0.2f, 2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
    // main rotor blade 1 horizontal blade
    glPushMatrix();
        glTranslatef(0.0f, 0.6f, 0.0f); // Position above the body
        glScalef(3.0f, 0.05f, 0.2f);   // Long and thin
        glColor3f(0.1f, 0.1f, 0.1f);   // dark blade
        glutSolidCube(1.0f);
    glPopMatrix();

    // Main rotor blade 2, perpendicular, etc.
    glPushMatrix();
        glTranslatef(0.0f, 0.6f, 0.0f); // Same height as other blade
        glScalef(0.2f, 0.05f, 3.0f);   // Same size, perpendicular direction
        glColor3f(0.1f, 0.1f, 0.1f);
        glutSolidCube(1.0f);
    glPopMatrix();
    // Tail rotor
    glPushMatrix();
        glTranslatef(0.0f, 0.2f, -2.5f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Rotate to vertical
        glScalef(0.6f, 0.05f, 0.1f);       // Small rotor
        glColor3f(0.1f, 0.1f, 0.1f);
        glutSolidCube(1.0f);
    glPopMatrix();
}
//money
void objects::drawDollarBill()
{
    glColor3f(0.0f, 0.6f, 0.0f);  // Bright green
    glBegin(GL_QUADS);
        glVertex3f(-0.3f, 0.0f, -0.15f);
        glVertex3f( 0.3f, 0.0f, -0.15f);
        glVertex3f( 0.3f, 0.0f,  0.15f);
        glVertex3f(-0.3f, 0.0f,  0.15f);
    glEnd();
}
// military tank 
void objects::drawTank()
{
    // Placeholder tank made of a body and turret
    glPushMatrix();
        // Body
        glColor3f(0.2f, 0.5f, 0.2f); // army green
        glScalef(2.0f, 0.5f, 1.0f);
        glutSolidCube(2.0);
    glPopMatrix();
    glPushMatrix();
        // Turret
        glTranslatef(0.0f, 1.0f, 0.0f);
        glColor3f(0.3f, 0.3f, 0.3f);
        glutSolidSphere(0.7, 20, 20);
    glPopMatrix();
    glPushMatrix();
        // Barrel
        glTranslatef(1.0f, 1.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
        glColor3f(0.1f, 0.1f, 0.1f);
        glScalef(1.5f, 0.1f, 0.1f);
        glutSolidCube(1.0);
    glPopMatrix();
}
// done. 