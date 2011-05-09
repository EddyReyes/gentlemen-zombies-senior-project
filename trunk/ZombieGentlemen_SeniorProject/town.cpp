#include "town.h"

town::town()
{
	map = NULL;
	m_object = NULL;
	camera = NULL;
}
town::~town()
{
	if(map)
	map->~XYPlane();
	if(m_object)
	m_object->~object();
	if(camera)
	camera->~dxCamera();
}
void town::init(dxManager * a_dxMgr)
{
	camera = new dxCamera(a_dxMgr);
	map = new XYPlane(a_dxMgr,"images/top_downTest.bmp");
}
void town::update()
{

}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,5.0f);
	map->draw();
}