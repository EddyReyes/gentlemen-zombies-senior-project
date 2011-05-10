#pragma once
#include "entity.h"
#include "player.h"
#include "goomba.h"
#include "ziggy.h"
#include "turret.h"
#include "objectManager.h"
#include "stringArray.h"

/****************************************************************
* entityManager
* The purpose of entity manager is to keep track of all entities 
* in the game at any one time. The entity manager also does the following
* load entities
* destroy entities
* update entities
****************************************************************/

class entityManager
{
private:
	entity ** players;
	entity ** enemies;

	stringArray objectFiles;
	stringArray enemyFiles;
	std::string playerFile;

	int fileIndex;

	int size;
	objectManager * objMgr;


public:
	// constructor/destructor
	entityManager();
	~entityManager();

	// member functions
	void init(objectManager * a_objMgr, std::string a_objectFiles,
		 std::string a_enemyFiles, std::string playerFile);
	void update(float timePassed);

	// load functions
	void loadPlayers(int fileIndex);
	void loadEnemies(int fileIndex);

	// remove entity
	void removeEnemys();
	void removePlayers();
	void removeAll();

	//accesors
	void getEntity(int index);
	void getPlayer(int index);
};