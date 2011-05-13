#include "entityManager.h"

// constructor/destructor
entityManager::entityManager()
{
	players = NULL;
	enemies = NULL;
	fileIndex = 0;
	numPlayers = 0;
	numEnemies = 0;
}
entityManager::~entityManager()
{
	// destroy all ojbects pertaining to each entity
	removeAll();
	enemyFiles.~stringArray();
	playerFile.~basic_string();
}

// member functions
bool entityManager::init(objectManager * a_objMgr, std::string a_enemyFiles, std::string a_playerFile)
{
	// get pointer for the objectManager
	objMgr = a_objMgr;
	
	enemyFiles.loadFromTextFile(a_enemyFiles);
	
	// make sure there are file names inside the enemy filename string array
	if(enemyFiles.getSize() == 0)
	{
		MessageBox(NULL, "No enemy files were loaded", "Entity Manager Error", MB_OK);
		return false;
	}
	else
	{
		playerFile = a_playerFile;
		loadPlayers();
		loadEnemies(0);
		return true;
	}
}
void entityManager::update(float timePassed)
{
	// update all players
	for(int i = 0; i < numPlayers; i++)
	{
		players[i]->update(timePassed);
	}
	
	// update all enemies
	for(int i = 0; i < numEnemies; i++)
	{
		enemies[i]->update(timePassed);
	}

	/**********************************************************
	* In the future function ality for removing and loading new enemies will be added here
	**********************************************************/
}

// load functions
void entityManager::loadPlayers()
{
	std::fstream file(playerFile.c_str());

	int size = 0;
	// count the number of strings in the text file
	file.peek();
	while(!file.eof())
	{
		int c;
		c = file.get();
		if(c == '\n' || file.eof()) 
		{size++;}
	}
	
	// clear fstream flags
	file.clear();
	// set fstream get pointer back to the beginning
	file.seekg(0, std::ios::beg);
	
	// check if there is already an existing array
	if(!players)
	{
		// if not create a new list
		players = new entity * [size];
	}
	else
	{
		// create a new array
		entity ** tempArray;
		tempArray = new entity * [numPlayers + size];
		// copy over array data
		for(int i = 0; i < numPlayers; i++)
		{
			tempArray[i] = players[i];
		}
		// delete old array and transfer new array into players
		delete [] players;
		players = tempArray;
	}

	for(int i = numPlayers; i < numPlayers + size; i++)
	{
		players[i] = new player();

		float x, y;

		file >> x >> y;

		objMgr->loadObjectsFromTxtFile("defaultPlayer.txt");
		objMgr->indexEnd();
		objMgr->getObject()->togglePhysics();
		players[i]->setObject(objMgr->getObject());
		players[i]->setPosition(x, y);
	}
	numPlayers += size;
}
void entityManager::loadEnemies(int fileIndex)
{
	std::string * fileName = enemyFiles.getStringPtrAt(fileIndex);
	std::fstream file(fileName->c_str());

	int size = 0;
	// count the number of strings in the text file
	file.peek();
	while(!file.eof())
	{
		int c;
		c = file.get();
		if(c == '\n' || file.eof()) 
		{size++;}
	}
	
	// clear fstream flags
	file.clear();
	// set fstream get pointer back to the beginning
	file.seekg(0, std::ios::beg);
	
	// make the corresponding amount of entity pointers
	// check if there is already an existing array
	if(!enemies)
	{
		// if new create a new list
		enemies = new entity * [size];
	}
	else
	{
		// create a new array
		entity ** tempArray;
		tempArray = new entity * [numEnemies + size];
		// copy over array data
		for(int i = 0; i < numEnemies; i++)
		{
			tempArray[i] = enemies[i];
		}
		// delete old array and transfer new array into players
		delete [] enemies;
		enemies = tempArray;
	}

	for(int i = numEnemies; i < numEnemies + size; i++)
	{
		char enemyType, direction, behaviorType;
		/**********************************************************
		* In the future direction and behavior type will change the behavior of the turrets
		**********************************************************/
		float x, y;
		int imageIndex;

		file >> enemyType >> x >> y >> imageIndex >> direction >> behaviorType;

		if(enemyType == 't') // load turret
		{
			enemies[i] = new turret();
			objMgr->loadObjectsFromTxtFile("defaultTurret.txt");
		}
		else if(enemyType == 'z') // load ziggy
		{
			enemies[i] = new ziggy();
			objMgr->loadObjectsFromTxtFile("defaultZiggy.txt");
		}
		else if(enemyType == 'g') // load goomba
		{
			enemies[i] = new goomba();
			objMgr->loadObjectsFromTxtFile("defaultGoomba.txt");
		}
		else if(enemyType == 'o') // load obstacle
		{
			enemies[i] = new obstacle();
			objMgr->loadObjectsFromTxtFile("defaultObstacle.txt");
		}

		objMgr->indexEnd();
		enemies[i]->setObject(objMgr->getObject());
		enemies[i]->setPosition(x, y);
	}
	numEnemies += size;
}

// remove entity
void entityManager::removeEnemies()
{

	// delete all enemie entities
	if(enemies)
	{
		for(int i = 0; i < numEnemies; i++)
		{
			// tell object manager to pop that particular
			objMgr->popObject(enemies[i]->getObject()->getObjectIndex());
			enemies[i]->setObject(NULL);
			enemies[i]->~entity();
			delete enemies[i];
			enemies[i] = NULL;
		}
		delete [] enemies;
		enemies = NULL;
		// contract object list to prevent it from growing out of control
		objMgr->getList()->contractList();
	}
	// reset count data
	numEnemies = 0;
}
void entityManager::removePlayers()
{
	// delete all player entities
	if(players)
	{
		for(int i = 0; i < numPlayers; i++)
		{
			// tell object manager to pop that particular
			objMgr->popObject(players[i]->getObject()->getObjectIndex());
			players[i]->setObject(NULL);
			players[i]->~entity();
			delete players[i];
			players[i] = NULL;
		}
		delete [] players;
		players = NULL;
		// contract object list to prevent it from growing out of control
		objMgr->getList()->contractList();
	}
	// reset count data
	numPlayers = 0;
}
void entityManager::removeAll()
{
	// remove both enemies and players
	removeEnemies();
	removePlayers();
}

//accesors
entity * entityManager::getEnemy(int index)
{
	if(index >= 0 && index < numEnemies)
		return enemies[index];
	else return NULL;
}
player * entityManager::getPlayer(int index)
{
	if(index >= 0 && index < numPlayers)
		return (player*)players[index];
	else return NULL;
}