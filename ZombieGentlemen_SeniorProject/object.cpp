#include "object.h"

object::object()
{
	plane = NULL;
	cube = NULL;
	collRect = NULL;
	targetCollRect = NULL;
	collisionToggle = true;
	colliding = false;
	collData = 0;
	oldCollData = 0;
	phys = NULL;
}
object::object(dxManager* a_dxMgr, std::string imgFile)
{
	plane = new XYPlane(a_dxMgr, imgFile);
	cube = NULL;
	collRect = new collisionRect();
	collRect->initRect(plane);
	collisionToggle = true;
	colliding = false;
	collData = 0;
	oldCollData = 0;
	phys = NULL;
}

object::object(XYPlane * a_plane)
{
	plane = a_plane;
	cube = NULL;
	collRect = new collisionRect();
	collRect->initRect(plane);
	collisionToggle = true;
	colliding = false;
	collData = 0;
	oldCollData = 0;
	phys = NULL;
}
object::object(dxCube * a_cube)
{
	plane = NULL;
	cube = a_cube;
	collRect = new collisionRect();
	collRect->initRect(a_cube);
	collisionToggle = true;
	colliding = false;
	collData = 0;
	oldCollData = 0;
	phys = NULL;
}

object::~object()
{
	// call destructors
	// destroy plane
	if(plane)
	{
		plane->~XYPlane();
	}
	// destroy cube
	if(cube)
	{
		cube->~dxCube();
	}
	// destory the collision rect
	collRect->~collisionRect();

	// destroy the physics data
	phys->~physics();

	// handle pointers
	collRect = NULL;
	plane = NULL;
	cube = NULL;
	phys = NULL;
}
/********************************************************************************
* loadParameters
* loads the parameters for any object using a text file
* instructions: send in a text file with the parameters in this order, separated by 
* a space
* x, y, z, width, height, rows, columns, left offset, top offset, right offset, 
* bottom offset
********************************************************************************/
void object::loadParametersFromTxtFile(std::string filename)
{
	std::fstream file(filename.c_str());
	D3DXVECTOR3 pos;
	float width, height, depth;
	int imageRows, imageColumns;
	FloatRect offset;
	// the size of the data we are going to create
	file >> pos.x >> pos.y >> pos.z >> width >> height >> depth >> imageRows >> imageColumns
		>> offset.left >> offset.top >> offset.right >> offset.bottom;
	if(plane)
	{
		plane->setParam(pos.x, pos.y, pos.z, width, height);
		plane->setImageRowsColumns(imageRows, imageColumns);
	}
	if(cube)
	{
		cube->setParam(pos.x, pos.y, pos.z, width, height, depth);
		cube->setImageRowsColumns(imageRows, imageColumns);
	}
	collRect->setOffset(&offset);
	collRect->update();
	recordPosition();
}
void object::loadParameters(float x, float y, float z, float width, float height, float depth,
							int imageRows, int imageColumns, float leftOffset, float topOffset, float rightOffset,
							float bottomOffset)
{
	if(plane)
	{
		plane->setParam(x, y, z, width, height);
		plane->setImageRowsColumns(imageRows, imageColumns);
	}
	if(cube)
	{
		cube->setParam(x, y, z, width, height, depth);
		cube->setImageRowsColumns(imageRows, imageColumns);
	}
	collRect->setOffset(leftOffset, rightOffset, topOffset, bottomOffset);
	collRect->update();
	recordPosition();
}
void object::draw()
{
	if(plane)
	{
		plane->draw();
	}
	if(cube)
	{
		cube->draw();
	}
}

void object::checkCollision()
{
	if(!colliding)
	{
		colliding = collRect->collided(targetCollRect->getRect());
	}

	if(collRect->collided(targetCollRect->getRect()))
		collData |= collRect->classify(targetCollRect->getRect());
}

void object::updatePhysics()
{
	if(phys)
	{
		//phys->onGroundOff();
		if(collData)
		{
			// check for top side collision
			if(collidingTop)
			{
				// if verticle collision occured, kill vertical velocity
				phys->killYVel();
			}
			// check for bottom side collision
			if(collidingBottom)
			{
				phys->onGroundOn();
			}
			else
			{
				// check for left side collision
				if(collidingLeft)
				{
					// if horizontal collision occured, kill horizontal velocity
					phys->killXVel();
				}
				// check for right side collision
				if(collidingRight)
				{
					// if horizontal collision occured, kill horizontal velocity
					phys->killXVel();
				}
			}
			if(phys->isjumpingAllowed())
			{
				// check for left side collision
				if(collidingLeft)
				{
					// if horizontal collision occured, kill horizontal velocity
					phys->killXVel();
				}
				// check for right side collision
				if(collidingRight)
				{
					// if horizontal collision occured, kill horizontal velocity
					phys->killXVel();
				}
			}
			if((collidingTop &&  collidingBottom) && (collidingRight || collidingLeft))
			{
				phys->killXVel();
			}
		}
	}
}


void object::clear()
{
	if(phys)
	{
		phys->updateMovePermissions();
	}
	colliding = false;
	
	oldCollData = collData;
	collData = 0;
}

void object::recordPosition()
{
	if(plane)
	{
		oldPos = *plane->getPosition();
	}
	if(cube)
	{
		oldPos = *cube->getPosition();
	}
}

bool object::isColliding(){return colliding;}

collisionRect * object::getCollisionRect(){return collRect;}
XYPlane * object::getXYPlane(){return plane;}
dxCube * object::getDxCube(){return cube;}

void object::setPosition(float a_x, float a_y, float a_z)
{
	if(plane)
	{
		plane->setPosition(a_x, a_y, a_z);
	}
	if(cube)
	{
		cube->setPosition(a_x, a_y, a_z);
	}
	collRect->update();
}
void object::setPosition(D3DXVECTOR3 vec)
{
	if(plane)
	{
		plane->setPosition(vec.x, vec.y, vec.z);
	}
	if(cube)
	{
		cube->setPosition(vec.x, vec.y, vec.z);
	}
	collRect->update();
}
/************************************************************************************
* handleCollision
* reverts the position of the object to the old position recorded previously
************************************************************************************/
void object::handleCollision()
{
	// revert position
	if(plane)
	{
		plane->setPosition(oldPos);
	}
	if(cube)
	{
		cube->setPosition(oldPos);
	}
	collRect->update();
}
void object::setTargetCollision(collisionRect * a_collRect)
{
	targetCollRect = a_collRect;
}
void object::toggleImage()
{
	if(plane)
	{
		plane->toggleImage();
	}
	if(cube)
	{
		cube->toggleCube();
	}
}
void object::toggleCollision(){collisionToggle = !collisionToggle;}
void object::collisionToggleOn(){collisionToggle = true;}
void object::collisionToggleOff(){collisionToggle = false;}

D3DXVECTOR3 * object::getPosition()
{
	if(plane)
	{
		return plane->getPosition();
	}
	if(cube)
	{
		return cube->getPosition();
	}
	return NULL;
}
void object::togglePhysics()
{
	if(phys)
	{
		phys->~physics();
		phys = NULL;
	}
	else
	{
		phys = new physics();
	}
}
physics * object::getPhysics()
{
	if(this != NULL)
		return phys;
	else return NULL;
}
bool object::setSprite(int row, int column)
{
	if(plane)
	{
		return plane->selectTextureSource(row, column);
	}
	if(cube)
	{
		return cube->selectTextureSource(row, column);
	}
	return false;
}
int object::getCollData(){return oldCollData;}