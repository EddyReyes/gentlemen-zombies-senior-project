#include "level.h"


level::level()
{
	ObjMan = NULL;
	files = NULL;
	m_map = NULL;
}
/******************************************************************
* initLevel
* takes in a  text file, and loads all level assets from it
******************************************************************/
void level::initLevel(dxManager* a_dxMgr, std::string initFiles)
{
	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initFiles);

	//initialize the data with it
	m_map = new cubeMap(files->getStringAt(0),files->getStringAt(1),a_dxMgr);

	ObjMan = new objectManager();
	ObjMan->initObjectMgr(a_dxMgr);
	ObjMan->initColMap(files->getStringAt(2), m_map);
	ObjMan->initImages(files->getStringAt(3));
	ObjMan->loadObjectsFromTxtFile(files->getStringAt(4));
	backGrnd = new background();
	backGrnd->initBackground(a_dxMgr, files->getStringAt(5));
	backGrnd->adjustPlanes(m_map, 5);
}
/******************************************************************
* update
* takes in the time that has ellapsed since the last update
* and updates the physics with it, as well as checks for collision
* between all objects
******************************************************************/
void level::update(float updateTime)
{
	ObjMan->updatePhysics(updateTime);
	ObjMan->handleCollision();
}
void level::setMusic(char* sound)
{
	
}



void level::draw()
{
	m_map->draw();
	backGrnd->draw();
	ObjMan->draw();
}
void level::moveObject(D3DXVECTOR3 go)
{
	ObjMan->moveObject(go);
}
level::~level()
{
	m_map->~cubeMap();
	ObjMan->~objectManager();
	files->~stringArray();
}