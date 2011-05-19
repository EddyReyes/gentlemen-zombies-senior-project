#include "level.h"


level::level()
{
	objMgr = NULL;
	files = NULL;
	m_map = NULL;
	checkpointtxt = NULL;
	camera = NULL;

}
/******************************************************************
* initLevel
* takes in a  text file, and loads all level assets from it
******************************************************************/
void level::initLevel(dxManager* a_dxMgr, dxCamera * a_camera, std::string initFiles)
{
	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initFiles);

	//initialize the data with it
	m_map = new cubeMap(files->getStringAt(0),files->getStringAt(1),a_dxMgr);

	objMgr = new objectManager();
	objMgr->initObjectMgr(a_dxMgr);
	objMgr->initColMap(files->getStringAt(2), m_map);
	objMgr->initImages(files->getStringAt(3));
	objMgr->loadObjectsFromTxtFile(files->getStringAt(4));
	backGrnd = new background();
	backGrnd->initBackground(a_dxMgr, files->getStringAt(5));
	p1HUD = new HUD();
	p1HUD->loadFromFile(files->getStringAt(6), files->getStringAt(7), a_dxMgr);
	p1HUD->initPositions(files->getStringAt(8));

	

	checkpointtxt = new DXText(a_dxMgr,"images/blackTextBox.bmp");
	checkpointtxt->setTextBoxParameters(200,50,600,500,10);
	checkpointtxt->setDialog("CHECKPOINT");
	checkpoint = 20;

	entityMgr = new entityManager();
	entityMgr->init(objMgr, "enemyFiles.txt", "testPlayers.txt", "testStuff.txt", "testCheckPoints.txt");
	m_player = entityMgr->getPlayer(0);
	//m_player = new player;
	//m_player->setObject(objMgr->getObject());	
	//m_player->getObject()->togglePhysics();

	// initialize FPS display data
	FPSText = new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	FPSText->loadFromTxtFile("textParameters.txt");
	FPSText->setDialog("Loading...");

	// physics data is now going to be removed
	/*physicsData = new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	physicsData->loadFromTxtFile("textParameters2.txt");
	physicsData->setDialog("Loading...");*/


	// init camera data
	camera = a_camera;
	
	//  make a cool intro, camare moves in from the side
	camData.point = D3DXVECTOR3(-100, 50, 0);
	camData.pos = D3DXVECTOR3(-100, 50, -12);
	camera->updateCamera3D(camData.pos, camData.point);

	Elapsed = 0;
	FPS = 0;
	timer = 0;
}
/******************************************************************
* update
* takes in the time that has ellapsed since the last update
* and updates the physics with it, as well as checks for collision
* between all objects
******************************************************************/
void level::update(float updateTime)
{
	objMgr->updatePhysics(updateTime);
	objMgr->handleCollision();
	entityMgr->update(updateTime);
	updateDebugData(updateTime);
	updateCamera(updateTime);
	//will check if youur at a checkpoint

	if(!m_player->isAlive())
	{
		timer += updateTime;
		if(timer >= 3)
		{
			// reload all entity data
			entityMgr->resetPlayers();
			// remove all enemies and stuff
			entityMgr->removeEnemies();
			entityMgr->removeStuff();
			// reload all enemies
			entityMgr->loadEnemies(0);
			// reset timer
			timer  = 0;
		}
	}
}

void level::updateCamera(float updateTime)
{
	camData.playerData = m_player->getObject()->getPosition();
	// find the distance between the player and the camera point
	camData.displacement.x = camData.playerData->x - camera->getCameraLook()->x;
	camData.displacement.y = camData.playerData->y - camera->getCameraLook()->y;


	// calculate camera point

	// if the displacement is too small, ignore it
	if(!(camData.displacement.x > 0.001 || camData.displacement.x < -0.001))
		camData.displacement.x = 0;
	if(!(camData.displacement.y > 0.001 || camData.displacement.y < -0.001))
		camData.displacement.y = 0;


	// move camera by a fraction of that distance
	camData.point.x = camData.displacement.x * 0.1f;
	camData.point.y = camData.displacement.y * 0.1f;

	camData.point.x += camera->getCameraLook()->x;
	camData.point.y += camera->getCameraLook()->y;


	// calculate camera position

	// find the distance between the player and the camera point
	camData.displacement.x = camData.playerData->x - camera->getCameraPosition()->x;
	camData.displacement.y = camData.playerData->y - camera->getCameraPosition()->y;

	// if the displacement is too small, ignore it
	if(!(camData.displacement.x > 0.001 || camData.displacement.x < -0.001))
		camData.displacement.x = 0;
	if(!(camData.displacement.y > 0.001 || camData.displacement.y < -0.001))
		camData.displacement.y = 0;

	camData.pos.x = camData.displacement.x * 0.05f;
	camData.pos.y = camData.displacement.y * 0.05f;

	camData.pos.x += camera->getCameraPosition()->x;
	camData.pos.y += camera->getCameraPosition()->y;

	// update camaera
	camera->updateCamera3D(camData.pos, camData.point);
}
void level::updateDebugData(float updateTime)
{
	// display FPS
	FPS++;
	Elapsed += updateTime;

	if(Elapsed >= 1)
	{
		char UpdateBuffer[256];
		sprintf_s(UpdateBuffer, "FPS: %i", FPS);
		FPSText->setDialog(UpdateBuffer);
		Elapsed = 0;
		FPS = 0;
	}

	// display phsics
	/*if(Elapsed >= 0.0)
	{
		char PhysicsBuffer[256];
		if(m_player->getObject()->getPhysics())
		{
			sprintf_s(PhysicsBuffer, "Physics x: %f\nPhysics y: %f", 
				m_player->getObject()->getPhysics()->getXVelocity(), 
				m_player->getObject()->getPhysics()->getYVelocity());
		}
		else
		{
			sprintf_s(PhysicsBuffer, "Physics Disabled");
		}
		physicsData->setDialog(PhysicsBuffer);
	}*/
}
void level::setMusic(char* sound)
{

}
void level::draw()
{
	m_map->draw();
	backGrnd->draw();
	objMgr->draw();
	p1HUD->draw();
	FPSText->draw();
	//physicsData->draw();
}
void level::handleInput(inputData * input, int now)
{
	// up key
	if ((input->keystate[DIK_UP] & 0x80) || (input->keystate[DIK_W] & 0x80))
	{
		m_player->move(0, 12.0f);
	}

	// down key
	if ((input->keystate[DIK_DOWN] & 0x80)|| (input->keystate[DIK_S] & 0x80))
	{
		// down key does NOTHING
	}
	
	// left key
	if ((input->keystate[DIK_LEFT] & 0x80) || (input->keystate[DIK_A] & 0x80))
	{
		m_player->move(-5.0f, 0);
	}

	// right key
	if ((input->keystate[DIK_RIGHT] & 0x80) || (input->keystate[DIK_D] & 0x80))
	{
		m_player->move(5.0f, 0);
	}

	// if neither left or right key are active
	if (!((input->keystate[DIK_LEFT] & 0x80) || (input->keystate[DIK_A] & 0x80))
		&& !((input->keystate[DIK_RIGHT] & 0x80) || (input->keystate[DIK_D] & 0x80)))
	{
		m_player->getObject()->getPhysics()->walkingOff();
	}

	//if ((input->keystate[DIK_B] & 0x80))
	//{
	//	if(now - input->keyLag[DIK_B] > 200)
	//	{
	//		objMgr->getObject()->togglePhysics();
	//		input->keyLag[DIK_B] = now;
	//	}
	//}

	//if ((input->keystate[DIK_G] & 0x80))
	//{
	//	if(now - input->keyLag[DIK_G] > 200)
	//	{
	//		objMgr->indexPrev();
	//		input->keyLag[DIK_G] = now;
	//	}
	//}
	//if ((input->keystate[DIK_H] & 0x80))
	//{
	//	if(now - input->keyLag[DIK_H] > 200)
	//	{
	//		objMgr->indexNext();
	//		input->keyLag[DIK_H] = now;
	//	}
	//}

	if ((input->keystate[DIK_P] & 0x80))
	{
		if(now - input->keyLag[DIK_P] > 200)
		{
			input->keyLag[DIK_P] = now;
			entityMgr->removeEnemies();
		}
	}
	if((input->keystate[DIK_E] & 0x80))
	{
		if(now - input->keyLag[DIK_E] >200)
		{
			input->keyLag[DIK_E] = now;
			entityMgr->loadEnemies(0);
		}
	}
}

void level::loadfromcheckpoint(std::string a_file)
{
	std::fstream temp;

	temp.open(a_file.c_str(),std::fstream::out||std::fstream::app);
	float x,y;
	temp>>x;
	temp>>y;
	m_player->getObject()->setPosition(x,y,0.0f);
}
level::~level()
{
	FPSText->~DXText();
	//physicsData->~DXText();
	m_map->~cubeMap();
	entityMgr->~entityManager();
	objMgr->~objectManager();
	files->~stringArray();
	checkpointtxt->~DXText();
}