#include "dxManager.h"
#include "objectManager.h"
//#include "stringArray.h"
class level
{
private:
	objectManager* ObjMan;
	stringArray* files;
	cubeMap* m_map;
public:
	level();
	level(dxManager*, char*);//initializes objectmanager
	void setMusic(char*);//sets the music for the level
	void draw();
	void handlecollision();
	void pop();
	void moveObject();
	void loadlevel(char*);//clear out the previous level and load a new one from file
	~level();//deconstructor
};