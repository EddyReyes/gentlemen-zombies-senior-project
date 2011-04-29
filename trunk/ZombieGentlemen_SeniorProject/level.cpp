#include "level.h"


level::level()
{
	ObjMan = NULL;
	files = NULL;
	m_map = NULL;
}
level::level(dxManager* a_dxMgr,char* initfiles)//will load a file with the names of files in it
{
	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initfiles);

	//initialize the data with it
	//code that isn't working correctly commented so project won't crash
	m_map = new cubeMap(files->getStringAt(0),files->getStringAt(1),a_dxMgr);

	ObjMan = new objectManager();
	//ObjMan->initColMap(
}
void level::loadlevel(char* initfiles)
{
}
void level::setMusic(char* sound)
{

}
void level::draw()
{
}
void level::handlecollision()
{

}
void level::moveObject()
{
}
level::~level()
{
	//ObjMan->~objectManager();
	files->~stringArray();
}