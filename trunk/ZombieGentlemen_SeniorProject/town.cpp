#include "town.h"

town::town()
{
	map = NULL;
	object = NULL;
	camera = NULL;
}
town::town(dxManager *a_dxMgr)
{
	camera = new dxCamera(a_dxMgr);
	map = new XYPlane(a_dxMgr,"images/top_downTest.bmp");
}
town::~town()
{
	if(map)
	map->~XYPlane();
	if(object)
	object->~object();
	if(camera)
	camera->~dxCamera();
}
void town::init()
{

}
void town::update()
{

}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,5.0f);
	map->draw();
}