/*//Tarun Pokra
//3381418 
//material file
//july 24th, 2025. 
*/
#ifndef _OBJECTS_H_
#define _OBJECTS_H_
#include <GL/freeglut.h>
class objects
{
private:
	GLuint sphere, cylinder, arm;
	float radius, stepRad, stepDeg;
	float uCircle[22][3];
	float uCylinder[42][3];
	void drawCircle();
	void drawSquare();
	void drawCube();
	void drawCylinder();
	void drawLimb(int base, int extend, int appendage);
	void drawBody(int bottom, int belt, int torso, int head);
	void drawGun();
public: //ALL THIS STUFF INS PUBLIC, SO IN THE DRAWSCENE IN THE GTA.CPP FILE, I CAN MAKE AS many of these multiple onjects as i want.
	objects();
	void drawCop();
	void drawCopCar();
	void drawRobber1();
	void drawRobber2();
	void drawHelicopter();
	void drawBank();
	void drawDollarBill();
	void drawTank();
};
#endif  // _OBJECTS_H_
// done. 