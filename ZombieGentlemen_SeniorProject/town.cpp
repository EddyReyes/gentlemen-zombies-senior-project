#include "town.h"

town::town()
{
	map = NULL;
	m_object = NULL;
	camera = NULL;
	m_points = NULL;
}
town::~town()
{
	if(map)
	map->~XYPlane();
	if(m_object)
	m_object->~object();
	if(camera)
	camera->~dxCamera();
	delete [] m_points;
}
void town::init(dxManager * a_dxMgr)
{
	camera = new dxCamera(a_dxMgr);
	map = new XYPlane(a_dxMgr,"images/top_downTest.bmp");
	map->setParam(D3DXVECTOR3(-10.0f,10.0f,0.0f),20,20);
	m_object = new object(a_dxMgr,"images/cursor.bmp");
	m_points = new D3DXVECTOR3 [4];
	m_points[0] = D3DXVECTOR3(5.0f,5.0f,0.0f);
	m_points[1] = D3DXVECTOR3(-5.0f,5.0f,0.0f);
	m_points[2] = D3DXVECTOR3(-5.0f,-5.0f,0.0f);
	m_points[3] = D3DXVECTOR3(5.0f,-5.0f,0.0f);
	m_object->setPosition(m_points[3]);

}
int town::update(inputData * input,int now)
{
	D3DXVECTOR3 temp(m_object->getPosition()->x,m_object->getPosition()->y,0.0f);
	if(input->keystate[DIK_W] & 0x80||input->keystate[DIK_UP])
	{
		if(now - input->keyLag[DIK_W] > 200||now - input->keyLag[DIK_UP] > 200)
		{
			if(temp == m_points[3])
				m_object->setPosition(m_points[0]);
			if(temp == m_points[2])
				m_object->setPosition(m_points[1]);
		}
	}
	if(input->keystate[DIK_A] & 0x80||input->keystate[DIK_LEFT])
	{
		if(now - input->keyLag[DIK_A] > 200||now - input->keyLag[DIK_LEFT] > 200)
		{
			if(temp == m_points[1])
				m_object->setPosition(m_points[0]);
			if(temp == m_points[2])
				m_object->setPosition(m_points[3]);
		}
	}
	if(input->keystate[DIK_D] & 0x80||input->keystate[DIK_RIGHT])
	{
		if(now - input->keyLag[DIK_D] > 200||now - input->keyLag[DIK_RIGHT] > 200)
		{
			if(temp == m_points[0])
				m_object->setPosition(m_points[1]);
			if(temp == m_points[3])
				m_object->setPosition(m_points[2]);
		}
	}
	if(input->keystate[DIK_S] & 0x80||input->keystate[DIK_DOWN])
	{
		if(now - input->keyLag[DIK_S] > 200||now - input->keyLag[DIK_DOWN] > 200)
		{
			if(temp == m_points[0])
				m_object->setPosition(m_points[3]);
			if(temp == m_points[1])
				m_object->setPosition(m_points[2]);
		}
	}
	if(input->keystate[DIK_RETURN])
	{
		if(now - input->keyLag[DIK_RETURN] > 200)
		{
			if(temp == m_points[0])
				return 0;
			if(temp == m_points[1])
				return 1;
			if(temp == m_points[2])
				return 2;
			if(temp == m_points[3])
				return 3;
		}
	}
	return -1;
}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,25.0f);
	map->draw();
	m_object->draw();
}