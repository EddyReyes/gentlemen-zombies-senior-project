#include "town.h"

town::town()
{
	map = NULL;
	objMgr = NULL;
	camera = NULL;
}
town::~town()
{
	if(map)
	map->~XYPlane();
	if(objMgr)
	objMgr->~object();
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

}