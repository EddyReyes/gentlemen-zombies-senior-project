#include "teleporter.h"

teleporter::teleporter()
{
	m_object = NULL;
	animate_state=0;
}
teleporter::~teleporter()
{
}
D3DXVECTOR3 teleporter::getData()
{
	return tele_vec;
}
void teleporter::setData(float x,float y)
{
	tele_vec.x = x;
	tele_vec.y =y;
	tele_vec.z = 0.0f;
}
void teleporter::update(float timePassed)
{
	time += timePassed;
	if(time >= 0.04f)
	{
		animate();
		time = 0;
	}
}
void teleporter::animate()
{
	switch(animate_state)
	{
	case 0:
		m_object->setSprite(0, 0);
		animate_state = 1;
	case 1:
		m_object->setSprite(0, 1);
		animate_state = 2;
	case 2:
		m_object->setSprite(0, 2);
		animate_state = 0;
	}
}