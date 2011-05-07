#include "town.h"

town::town()
{
	camera = NULL;
	map = NULL;
}
town::town(dxManager* a_dxMgr)
{
	map = new XYPlane(a_dxMgr,"images/top_downTest.bmp");
	camera = new dxCamera(a_dxMgr);
}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,5.0f);
	map->draw();
}
town::~town()
{
	map->~XYPlane();
	camera->~dxCamera();
}