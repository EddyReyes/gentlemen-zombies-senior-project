#include "town.h"

town::town()
{
	map = NULL;
	objects = NULL;
	camera = NULL;
}
town::town(dxManager*)
{

}
town::~town()
{
	if(map)
	map->~XYPlane();
	if(objects)
	objects->~object();
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