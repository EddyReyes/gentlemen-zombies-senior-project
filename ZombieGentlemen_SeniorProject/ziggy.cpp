#include "ziggy.h"
#include "dxManager.h"
#include "CustomVertex.h"
/***********************************************************************
 * Makes the ziggy enemy(bird/fish) fly or swim in a wave like pattern * 
 ***********************************************************************/
void ziggy::yMovement()
{
	//ziggy enemy up/down movement
	if (ziggyMovement.posY > 450 &&
		ziggyMovement.posY < 550)
	{
		ziggyMovement.moveY *= 1;
	}
	else ziggyMovement.moveY *= -1;
}
void ziggy::load()
{
	//will load the ziggy flying enemy in game maps

}
void ziggy::update()
{
	/***************************************************************** 
	 * Will update ziggy's position per frame and as soon            *
	 * as the enemy flys or swims from one side to the other it will *
	 * delete from memory                                            *
	 *****************************************************************/
	//assuming that the ziggy enemy starts at the left side of the screen
	for (int i = 0; i < 10; i++)
	{
	ziggyMovement.posX += ziggyMovement.moveX;
	//ziggy moving up and down in a waving motion
	yMovement();
	
		//if the position is greater than the 800 or to the right side of the screen,
		//then move back in the opposite direction
		if(ziggyMovement.posX > WINDOW_WIDTH)
		{
			ziggyMovement.moveX *= -1;
			yMovement();
		}
		//if the position is greater than the 0, then move back in the opposite direction
		if(ziggyMovement.posX < 0)
		{
			ziggyMovement.moveX *= 1;
			yMovement();
		}
		//if the position is greater than or equal to 800, then delete ziggy enemy
		if(ziggyMovement.posX >= WINDOW_WIDTH)
		{
			//need to delete a ziggy object at this point,
			//need help with using a object pointer for ziggy
		}
	}
}