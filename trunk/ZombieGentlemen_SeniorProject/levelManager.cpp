#include "levelManager.h"

levelManager::levelManager(void)
{
	m_level = NULL;
	numLevels = 0;
}
levelManager::~levelManager(void)
{
	// destroy level
	if(m_level)
	{
		delete m_level;
		m_level = NULL;
	}

	// destroy filenames
	fileNames->~stringArray();
	delete fileNames;
	fileNames = NULL;

	numLevels = 0;
}
void levelManager::init(std::string filename, dxManager * a_dxMgr, dxCamera * a_camera, sound * a_soundMgr)
{

	// initialize file names
	fileNames = new stringArray;
	fileNames->loadFromTextFile(filename);
	
	// set number of levels
	numLevels = fileNames->getSize();

	// set dxManager and dxCamera pointers
	dxMgr = a_dxMgr;
	camera = a_camera;
	soundMgr = a_soundMgr;
}
bool levelManager::setLevel(int lvlIndex)
{
	if(lvlIndex >= 0 && lvlIndex < numLevels)
	{
		// destroy any level that is currently still running
		if(m_level)
		{
			delete m_level;
			m_level = NULL;
		}
		// initialize lvel pointer
		m_level = new level;
		m_level->initLevel(dxMgr, camera, soundMgr, fileNames->getStringAt(lvlIndex));
		return true;
	}
	else
	{
		MessageBox(NULL, "Level index is out of bounds", "Level Mgr Error", MB_OK);
		return false;
	}
}
level * levelManager::getLevel(){return m_level;}
