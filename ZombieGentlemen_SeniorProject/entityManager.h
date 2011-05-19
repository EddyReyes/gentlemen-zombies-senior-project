#pragma once
#include "objectManager.h"
#include "stringArray.h"

// entities
#include "entity.h"
#include "player.h"
#include "goomba.h"
#include "ziggy.h"
#include "turret.h"
#include "obstacle.h"
// stuff
#include "stuff.h"
#include "checkpoint.h"

/****************************************************************
* entityManager
* The purpose of entity manager is to keep track of all entities 
* in the game at any one time. The entity manager also does the following
* load entities
* destroy entities
* update entities

bug: when loading second batches, the last object in the list isnt moved
to its correct position
****************************************************************/


class entityManager
{
private:
	entity ** players;
	entity ** enemies;
	stuff ** m_stuff;
	stuff ** m_checkPoints;

	stringArray enemyFiles;
	std::string playerFile;
	std::string stuffFile;
	std::string checkPointFile;

	int checkPnt;

	int numPlayers, numEnemies, numStuff, numCheckPoints;
	objectManager * objMgr;


public:
	// constructor/destructor
	entityManager();
	~entityManager();

	// member functions
	bool init(objectManager * a_objMgr, std::string a_enemyFiles, std::string a_playerFile, std::string a_stuffFile, std:: string a_checkPointFile);
	void update(float timePassed);

	// load functions
	void loadPlayers();
	void loadEnemies(int fileIndex);
	void loadStuff();
	void loadCheckPoints();

	// remove entity
	void removeEnemies();
	void removePlayers();
	void removeStuff();
	void removeCheckPoints();
	void removeAll();
	void removeAllExceptCheckPoints();

	// reset
	void resetPlayers();

	//accesors
	entity * getEnemy(int index);
	player * getPlayer(int index);
	stuff * getStuff(int index);
};