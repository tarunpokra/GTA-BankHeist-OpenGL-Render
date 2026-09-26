/*
//Tarun Pokra
//3381418 
//material file
//july 27th, 2025
this routine set the materials properties in OpenGL; constants defined material .h.. etc.
//like color of skin, pants, etc. 
here one routine. 
setMaterial material properties based o value that passes through. 
*/
#include "materialStuff.h"
//material paramaterpassed value
void setMaterial(int selection)
{
	switch (selection)
	{
		// dull
		case 0:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black_specular);
			glMaterialfv(GL_FRONT_AND_BACK, 
				GL_AMBIENT_AND_DIFFUSE, black_diffuse) ;
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, black_shininess);
			break;
		//  shiny
		case 1:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black_specular);
			glMaterialfv(GL_FRONT_AND_BACK ,
				 GL_AMBIENT_AND_DIFFUSE, black_diffuse ) ;
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 99.0);
			break;
		//shiny
		case 2:	
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_specular);
			glMaterialfv(GL_FRONT_AND_BACK, 
				GL_AMBIENT_AND_DIFFUSE, white_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, white_shininess ) ;
			break;
		// off white
		case 3:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bank1_specular) ;
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bank1_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, bank1_shininess) ;
			break;
		// skin color
		case 4:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, skin1_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skin1_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, skin1_shininess);
			break;
		// african-american skin
		case 5:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, skin2_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
				 skin2_diffuse );
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, skin2_shininess);
			break ;
		// thr windows
		case 6:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, window_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, window_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, window_shininess);
			break;
		// grren shirt
		case 7:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shirt_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, shirt_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shirt_shininess);
			break;
		// pants
		case 8:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pants_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pants_diffuse) ;
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, pants_shininess);
			break;
		// blue light
		case 9:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blue_shininess);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blue_emissive);
			break;
		// red light
		case 10:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_specular) ;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, red_shininess);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red_emissive);
			break;
		//  dull
		case 12:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, belt_specular) ;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, belt_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, belt_shininess);
			break;
		// red blood
		case 13: ///////////////NOTE MIGHT REMOVE THIS LATER TO MAKE THE SCENE MORE "PG-13"/ school project approripate.
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blood_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blood_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blood_shininess);
			break;
		// green grass
		case 14:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grass_specular) ;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grass_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, grass_shininess);
			break;
		// off-white 2
		case 15:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bank2_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bank2_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, bank2_shininess );
			break;
		// road black

		case 16:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, road_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, road_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, road_shininess);
			break;
		// lane marker yellow
		case 17:
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lane_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lane_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lane_shininess);
			break;
	}
	//  all but the red/blue lights, emitting
	if (selection != 9 || selection != 10)
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_emissive);
}
// done.