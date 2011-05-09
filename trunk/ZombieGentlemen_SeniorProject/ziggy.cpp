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
		ziggyMovement.moveY *= 1; // THIS STATEMENT COULD BE REMOVED, TECHNICALLY IT DOESNT REALLY DO ANYTHING
	}
	else ziggyMovement.moveY *= -1;

	/************************************************************************
	* COMMENT
	* THIS LOGIC WILL DO THE FOLLOWING
	IF THE STATEMENT if (ziggyMovement.posY > 450 &&
						 ziggyMovement.posY < 550)

	RETURNS TRUE, THEN IT WILL MULTIPLY BY ONE, ESSENTIALLY MAKING IT EAQUAL ITSELF,

	IF FALSE THEN IT WILL BECOME NEGATIVE WHICH IS THE DESIRED EFFECT, SO REMOVING THE FIRST
	STATEMENT SHOULD BE SAFE

	************************************************************************/


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

	// FOR NOW DONT WORRY TOO MUCH ABOUT DELETING IT FROM MEMORY, THIS WILL BE
	// COVERED LATER


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

	/************************************************************************
	* COMMENT
	* A NEW DATA TYPE WAS CREATED TO FACILITATE THIS. ITS NOT PART OF THE DESIGN,
	IM NOT GOING TO REMOVE IT, BUT YOU SHOULD NOT BE USING IT. THE FOLLOWING ARE 
	INSTRUCTIONS FOR ACCESSING THE POSITION DATA OF THE OBJECT

	1. make a D3DXVECTOR3 * and call it pos. It is safe to do it within this function,
	since it is temporary. It does not need to be a part of the actual class.
	2. retreive the position pointer of the object like this:  m_object->getPosition();
	and assign it to pos.
	3. now pos points to the position data for the object. From here you can manipulate the
	position data like so: pos->x += moveX;
	4. Calculate your movement data, which can also be created inside this function.
	5. Manipulate the position data of the object using the move data.
	6. remember to update the collision rect like this: m_object->getCollisionRect()->update();
	7. Your done, the object should be moveing now

	IF YOU HAVE MORE QUESTIONS LET ME KNOW. I WOULD COMMENT ON YOUR CURRENT LOGIC, BUT SEEING AS
	ITS NOT USING THE RIGHT DATA, I WOULD RATHER WE FIX THAT FIRST, THEN GET BACK TO THE LOGIC,
	ALSO ANY LOGIC USING THE WINDOW WIDTH ISNT GOING TO WORK, THE WINDOW WIDTH DOESNT AFFECT THE GAME
	WORLD. AVOID USING WINDOW WIDTH.
	************************************************************************/

}