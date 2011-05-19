#include "entityManager.h"

// constructor/destructor
entityManager::entityManager()
{
	players = NULL;
	enemies = NULL;
	m_stuff = NULL;
	m_checkPoints = NULL;
	fileIndex = 0;
	numPlayers = 0;
	numEnemies = 0;
	numStuff = 0;
	numCheckPoints = 0;
}
entityManager::~entityManager()
{
	// destroy all ojbects pertaining to each entity
	removeAll();
	enemyFiles.~stringArray();
	playerFile.~basic_string();
}

// member functions
bool entityManager::init(objectManager * a_objMgr, std::string a_enemyFiles, std::string a_playerFile, std::string a_stuffFile, std::string a_checkPointFile)
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
		stuffFile = a_stuffFile;
		checkPointFile = a_checkPointFile;
		loadPlayers();
		loadEnemies(0);
		loadStuff();
		loadCheckPoints();
		return true;
	}
}
void entityManager::update(float timePassed)
{
	// update all players
	for(int i = 0; i < numPlayers; i++)
	{
		players[i]->update(timePassed);

		if(players[i]->getObject()->getCollHistory()->getList() && players[i]->isAlive())
		{
			//check for collision with enemies
			for(int j = 0; j < numEnemies; j++)
			{
				for(int g = 0; g < players[i]->getObject()->getCollHistory()->endOfList(); g++)
				{
					if(players[i]->getObject()->getCollHistory()->get(g) == enemies[j]->getObject()->getObjectIndex())
						players[i]->entityDead();
				}
			}
			//check for collision with stuff
			for(int j = 0; j < numStuff; j++)
			{
				for(int g = 0; g < players[i]->getObject()->getCollHistory()->endOfList(); g++)
				{
					if(players[i]->getObject()->getCollHistory()->get(g) == m_stuff[j]->getObject()->getObjectIndex())
					{
						//if(players[i]->getType() == teleporter)
						//{
							// teleporter * tel;
							// tel = m_stuff[j];
							//players[i]->setPosition(tel->getData());
						//}
						//if(players[i]->getType() == armor)

						//if(players[i]->getType() == key)
					}
				}
			}
			for(int j = 0; j < numCheckPoints; j++)
			{
				for(int g = 0; g < players[i]->getObject()->getCollHistory()->endOfList(); g++)
				{
					if(players[i]->getObject()->getCollHistory()->get(g) == m_checkPoints[j]->getObject()->getObjectIndex())
					{
						if(!m_checkPoints[j]->isPickedUp())
							m_checkPoints[j]->pickUp();
					}
				}
			}
			// clear collision history
			players[i]->getObject()->getCollHistory()->resetList();
		}
	}
	
	// update all enemies
	for(int i = 0; i < numEnemies; i++)
	{
		enemies[i]->update(timePassed);
		enemies[i]->getObject()->getCollHistory()->resetList();
	}

	// update all stuff
	for(int i = 0; i < numStuff; i++)
	{
		m_stuff[i]->update(timePassed);
		m_stuff[i]->getObject()->getCollHistory()->resetList();
	}
	
	// update all checkpoints
	for(int i = 0; i < numCheckPoints; i++)
	{
		m_checkPoints[i]->update(timePassed);
		m_checkPoints[i]->getObject()->getCollHistory()->resetList();
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

		file >> enemyType >> x >> y >> direction >> behaviorType;

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
		enemies[i]->getObject()->setSprite(0,0);
		if(enemyType == 'g' || enemyType == 'z') // turn on physics for goombas and ziggy
		{
			enemies[i]->getObject()->togglePhysics();
		}
		enemies[i]->setPosition(x, y);
	}
	numEnemies += size;
}

void entityManager::loadStuff()
{
	std::fstream file(stuffFile.c_str());

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
	if(!m_stuff)
	{
		// if not create a new list
		m_stuff = new stuff * [size];
	}
	else
	{
		// create a new array
		stuff ** tempArray;
		tempArray = new stuff * [numStuff + size];
		// copy over array data
		for(int i = 0; i < numStuff; i++)
		{
			tempArray[i] = m_stuff[i];
		}
		// delete old array and transfer new array into players
		delete [] m_stuff;
		m_stuff = tempArray;
	}

	for(int i = numStuff; i < numStuff + size; i++)
	{
		char stuffType;
		float x, y;

		file >> stuffType >> x >> y;

		if(stuffType == 'a') // load armor
		{
			/*m_stuff[i] = new armor;
			objMgr->loadObjectsFromTxtFile("defaultArmor.txt");*/
		}
		else if(stuffType == 'k') // load key
		{
			/*m_stuff[i] = new key;
			objMgr->loadObjectsFromTxtFile("defaultKey.txt");*/
		}
		else if(stuffType = 'd') // load door
		{
			/*m_stuff[i] = new door;
			objMgr->loadObjectsFromTxtFile("defaultDoor.txt");*/
		}
		else if(stuffType = 't')
		{/*
			m_stuff[i] = new teleporter;
			objMgr->loadObjectsFromTxtFile("defaultTeleporter.txt");*/
		}

		objMgr->indexEnd();
		m_stuff[i]->setObject(objMgr->getObject());
		m_stuff[i]->setPosition(x, y);
		m_stuff[i]->getObject()->setSprite(0,0);
		// toggle collision for some m_stuff
		if(stuffType == 'a' || stuffType == 'k')
		{
			m_stuff[i]->getObject()->toggleCollision();
		}
	}
	numStuff += size;
}

void entityManager::loadCheckPoints()
{
	std::fstream file(checkPointFile.c_str());

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
	if(!m_checkPoints)
	{
		// if not create a new list
		m_checkPoints = new stuff * [size];
	}
	else
	{
		// create a new array
		stuff ** tempArray;
		tempArray = new stuff * [numCheckPoints + size];
		// copy over array data
		for(int i = 0; i < numCheckPoints; i++)
		{
			tempArray[i] = m_checkPoints[i];
		}
		// delete old array and transfer new array into players
		delete [] m_checkPoints;
		m_checkPoints = tempArray;
	}

	for(int i = numCheckPoints; i < numCheckPoints + size; i++)
	{
		float x, y;

		file >> x >> y;

		m_checkPoints[i] = new checkpoint;
		objMgr->loadObjectsFromTxtFile("defaultCheckpoint.txt");

		objMgr->indexEnd();
		m_checkPoints[i]->setObject(objMgr->getObject());
		m_checkPoints[i]->setPosition(x, y);
		m_checkPoints[i]->getObject()->setSprite(0,0);
		// toggle collision for some m_stuff
		m_checkPoints[i]->getObject()->toggleCollision();
	}
	numCheckPoints += size;
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

void entityManager::removeStuff()
{
	// delete all player entities
	if(m_stuff)
	{
		for(int i = 0; i < numStuff; i++)
		{
			// tell object manager to pop that particular
			objMgr->popObject(m_stuff[i]->getObject()->getObjectIndex());
			m_stuff[i]->setObject(NULL);
			delete m_stuff[i];
			m_stuff[i] = NULL;
		}
		delete [] m_stuff;
		m_stuff = NULL;
		// contract object list to prevent it from growing out of control
		objMgr->getList()->contractList();
	}
	// reset count data
	numStuff = 0;
}
void entityManager::removeCheckPoints()
{
	// delete all player entities
	if(m_checkPoints)
	{
		for(int i = 0; i < numCheckPoints; i++)
		{
			// tell object manager to pop that particular
			objMgr->popObject(m_checkPoints[i]->getObject()->getObjectIndex());
			m_checkPoints[i]->setObject(NULL);
			delete m_checkPoints[i];
			m_checkPoints[i] = NULL;
		}
		delete [] m_checkPoints;
		m_checkPoints = NULL;
		// contract object list to prevent it from growing out of control
		objMgr->getList()->contractList();
	}
	// reset count data
	numCheckPoints = 0;
}
void entityManager::removeAll()
{
	// remove EVERYTHING
	removeEnemies();
	removePlayers();
	removeStuff();
	removeCheckPoints();
}
void entityManager::removeAllExceptCheckPoints()
{
	// remove EVERYTHING except for checkpoints
	removeEnemies();
	removePlayers();
	removeStuff();
}

void entityManager::resetPlayers()
{
	for(int i =0; i < numPlayers; i++)
	{
		//players[i]->setPosition();
		players[i]->reset();
	}
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
stuff * entityManager::getStuff(int index)
{
	if(index >= 0 && index < numStuff)
		return (stuff*)m_stuff[index];
	else return NULL;
}