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
	m_object->setPosition(m_points[0]);

}
void town::update()
{

}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,25.0f);
	map->draw();
	m_object->draw();
}