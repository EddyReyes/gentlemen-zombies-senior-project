#include "level.h"


level::level()
{
	ObjMan = NULL;
	files = NULL;
	m_map = NULL;
}
level::level(dxManager* a_dxMgr,char* initfiles,float updatespd)//will load a file with the names of files in it
{
	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initfiles);

	//initialize the data with it
	m_map = new cubeMap(files->getStringAt(0),"images/glassPanes2.bmp",a_dxMgr);

	ObjMan = new objectManager();
	ObjMan->initObjectMgr(a_dxMgr);
	ObjMan->initColMap(files->getStringAt(1),m_map);
	ObjMan->initImages(files->getStringAt(2));
	ObjMan->loadObjectsFromTxtFile(files->getStringAt(3));
	ObjMan->updatePhysics(updatespd);
}
void level::loadlevel(char* initfiles)
{
}
void level::update(float update)
{
	ObjMan->updatePhysics(update);
	ObjMan->handleCollision();
}
void level::setMusic(char* sound)
{

}
void level::draw()
{
	m_map->draw();
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