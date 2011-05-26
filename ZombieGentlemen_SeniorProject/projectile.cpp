#include "projectile.h"

projectile::projectile()
{
	type = entityProjectile;
	m_object = NULL;
	state = projectileIdle;
	horizontal = right;
	vertical = up;
	time = 0;
	speed = 1;
}
projectile::~projectile()
{

}
void projectile::init(D3DXVECTOR3 initPos, float a_speed)
{
	pos = initPos;
	speed = a_speed;
}

void projectile::update(float timePassed)
{
	if(state == projectileFire)
	{
		time += timePassed;
		if(time <= 1.0f)
		{
			firing(timePassed);
			time = 0;
		}
		else
		{
			reset();
		}
	}
}

void projectile::animate()
{
	switch(state)
	{

	case projectileFire:
		m_object->setSprite(0, 0);
		break;

	case projectileHit:
		m_object->setSprite(0, 1);
		break;
	}
}
void projectile::reset()
{
	state = projectileIdle;
	m_object->setPosition(pos);
}
void projectile::firing(float updateTime)
{
	D3DXVECTOR3 * position;
	position = m_object->getPosition();
	switch(horizontal)
	{
	case none:
		switch(vertical)
		{
		case none:
			// do nothing
			break;
		case up: // move up
			position->y += speed * 2 * updateTime;
			break;
		case down: // move down
			position->y -= speed * 2 * updateTime;
			break;
		}
		break;
	case left: // move left
		switch(vertical)
		{
		case none:
			position->x -= speed * 2 * updateTime;
			break;
		case up: // move up
			position->y += speed * updateTime;
			position->x -= speed * updateTime;
			break;
		case down: // move down
			position->y -= speed * updateTime;
			position->x -= speed * updateTime;
			break;
		}
		break;
	case right: // move right
		switch(vertical)
		{
		case none:
			position->x += speed * 2 * updateTime;
			break;
		case up: // move up
			position->y += speed * updateTime;
			position->x += speed * updateTime;
			break;
		case down: // move down
			position->y -= speed * updateTime;
			position->x += speed * updateTime;
			break;
		}
		break;
	}
}
void projectile::setDirection(int wallState, int state)
{
	// decides what direction the projectiles will fire based on turret state
	enum turretPosition {faceRight, faceDown, faceUp, faceLeft};
	enum turretState {fortyFiveRight, ninety, fortyFiveLeft};
	
	switch(wallState)
	{
	case faceRight:

		switch(state)
			{
			case fortyFiveRight:
				vertical = down;
				horizontal = right;
				break;

			case ninety:
				vertical = noneVert;
				horizontal = right;
				break;

			case fortyFiveLeft:
				vertical = up;
				horizontal = right;
				break;
			}
		break;
	case faceDown:
		switch(state)
			{
			case fortyFiveRight:
				vertical = down;
				horizontal = left;
				break;

			case ninety:
				vertical = down;
				horizontal = noneHor;
				break;

			case fortyFiveLeft:
				vertical = down;
				horizontal = right;
				break;
			}
		break;

	case faceUp:
		switch(state)
			{
			case fortyFiveRight:
				vertical = up;
				horizontal = right;
				break;

			case ninety:
				vertical = up;
				horizontal = noneHor;
				break;

			case fortyFiveLeft:
				vertical = up;
				horizontal = left;
				break;
			}
		break;

	case faceLeft:
		switch(state)
			{
			case fortyFiveRight:
				vertical = up;
				horizontal = left;
				break;

			case ninety:
				vertical = noneVert;
				horizontal = left;
				break;

			case fortyFiveLeft:
				vertical = down;
				horizontal = left;
				break;
			}
		break;
	}
}
void projectile::setSpeed(float a_speed){speed = a_speed;}
void projectile::hit(){state = projectileHit;}
void projectile::fire(){state = projectileFire;}