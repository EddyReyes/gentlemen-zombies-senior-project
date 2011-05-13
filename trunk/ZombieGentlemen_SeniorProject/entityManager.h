#pragma once
#include "entity.h"
#include "player.h"
#include "goomba.h"
#include "ziggy.h"
#include "turret.h"
#include "obstacle.h"
#include "objectManager.h"
#include "stringArray.h"

/****************************************************************
* entityManager
* The purpose of entity manager is to keep track of all entities 
* in the game at any one time. The entity manager also does the following
* load entities
* destroy entities
* update entities

status: BROKEN! WTF!
****************************************************************/


class entityManager
{
private:
	entity ** players;
	entity ** enemies;

	stringArray enemyFiles;
	std::string playerFile;

	int fileIndex;

	int numPlayers, numEnemies;
	objectManager * objMgr;


public:
	// constructor/destructor
	entityManager();
	~entityManager();

	// member functions
	bool init(objectManager * a_objMgr, std::string a_enemyFiles, std::string a_playerFile);
	void update(float timePassed);

	// load functions
	void loadPlayers();
	void loadEnemies(int fileIndex);

	// remove entity
	void removeEnemies();
	void removePlayers();
	void removeAll();

	//accesors
	entity * getEnemy(int index);
	player * getPlayer(int index);
};