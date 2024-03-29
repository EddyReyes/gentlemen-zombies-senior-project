#include "level.h"


level::level()
{
	objMgr = NULL;
	files = NULL;
	m_map = NULL;
	checkpointtxt = NULL;
	camera = NULL;
	state = levelLoading;
	pauseScreen = NULL;
	soundMgr = NULL;
}
/******************************************************************
* initLevel
* takes in a  text file, and loads all level assets from it
******************************************************************/
void level::initLevel(dxManager* a_dxMgr, dxCamera * a_camera, sound * a_soundMgr, std::string initFiles)
{
	// init camera data
	camera = a_camera;

	// init sound data
	soundMgr = a_soundMgr;

	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initFiles);

	//initialize the data with it
	m_map = new cubeMap(files->getStringAt(0),files->getStringAt(1),a_dxMgr);

	// init object manager
	objMgr = new objectManager();
	objMgr->initObjectMgr(a_dxMgr);
	objMgr->initColMap(files->getStringAt(2), m_map);
	objMgr->initImages(files->getStringAt(3));
	objMgr->loadObjectsFromTxtFile(files->getStringAt(4));

	// init entity manager
	entityMgr = new entityManager();
	entityMgr->init(objMgr, a_soundMgr, files->getStringAt(5), files->getStringAt(6), files->getStringAt(7), files->getStringAt(8));
	// set player pointer
	m_player = entityMgr->getPlayer(0);


	// init backgrounds
	backGrnd = new background();
	backGrnd->initBackground(a_dxMgr, files->getStringAt(9));
	

	// init HUD
	p1HUD = new HUD();
	p1HUD->loadFromFile(files->getStringAt(10), a_dxMgr);
	p1HUD->initPositions(files->getStringAt(11));
	p1HUD->setPlayer(m_player);
	p1HUD->update(0);

	// initialize FPS display data
	FPSText = new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	FPSText->loadFromTxtFile("textParameters.txt");
	FPSText->setDialog("Loading...");
	// initially toggle FPS as off
	FPSText->toggleImage();
	FPSText->toggleText();

	// init stats display data
	statsDisplay= new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	statsDisplay->loadFromTxtFile("statsDisplayParameters.txt");
	statsDisplay->setDialog("Loading...");

	// init pause screen
	pauseScreen = new HudImage(a_dxMgr, "images/paused.bmp");
	pauseScreen->setParameters(1920, 1080, 0, 0);

	// init win screen
	winScreen = new HudImage(a_dxMgr, "images/victoryCondition.bmp");
	winScreen ->setParameters(1920, 1080, 0, 0);
	
	//  make a cool intro, camare moves in from the side
	camData.point = D3DXVECTOR3(-50, -30, 0);
	camData.pos = D3DXVECTOR3(-50, -30, -12);
	camera->updateCamera3D(camData.pos, camData.point);

	Elapsed = 0;
	FPS = 0;
	timer = 0;
	
	soundMgr->stopSound(soundMenu);
	soundMgr->SetVolume(soundLevel, -1400);
	soundMgr->playSoundLoop(soundLevel);
}
/******************************************************************
* update
* takes in the time that has ellapsed since the last update
* and updates the physics with it, as well as checks for collision
* between all objects
******************************************************************/
bool level::update(float updateTime)
{
	// check if update time is too large
	if(updateTime > 0.05) // FPS is less than 20
	{
		updateTime *= 0.5;
	}

	switch(state)
	{
	case levelLoading:
		// start level after 3 seconds second
		timer += updateTime;
		if(timer >= 3)
		{
			state = levelPlay;
			// reload all entity data
			entityMgr->resetPlayers();
			timer = 0;
		}
		break;

	case levelPlay:
		stats.timer += updateTime; // update the game play timer
		objMgr->updatePhysics(updateTime);
		objMgr->handleCollision();
		entityMgr->update(updateTime);
		p1HUD->update(updateTime);

		// if player dies respawn
		if(!m_player->isAlive())
		{
			timer += updateTime;
			if(timer >= 3)
			{
				// reload all entity data
				entityMgr->resetPlayers();
				stats.numDeaths++; // update number of deaths
				// remove all enemies and stuff
				entityMgr->removeEnemies();
				entityMgr->removeStuff();
				// reload all enemies
				entityMgr->loadEnemies(entityMgr->getCheckPoint()+1);
				entityMgr->loadStuff();
				// reset timer
				timer  = 0;
			}
		}
		// check for victory condition
		if(entityMgr->getVictoryCondition())
		{
			state = levelWin;
			char statsBuffer[256];
			if(stats.timer <= 60)
				sprintf_s(statsBuffer, "Stats:\nTime: %4.2f sec\nDeaths: %i", stats.timer, stats.numDeaths);
			else
			{
				int minutes, seconds;
				minutes = (int)stats.timer/60;
				seconds = (int)stats.timer % 60;
				sprintf_s(statsBuffer, "Stats:\nTime: %imin %isec \nDeaths: %i", minutes, seconds, stats.numDeaths);
				statsDisplay->setFontSize(40);
			}
			statsDisplay->setDialog(statsBuffer);
			soundMgr->playSound(soundQuote1 + rand() % 5);
		}
		break;

	case levelWin:
		timer += updateTime;
		if(timer >= 5)
		{
			soundMgr->stopSound(soundLevel);
			soundMgr->playSoundLoop(soundMenu);
			return false;
		}
		break;
	}
	// update camera and debug data
	if(state != levelLoading)
	{
		updateDebugData(updateTime);
		updateCamera(updateTime);
	}
	return true;
}

void level::updateCamera(float updateTime)
{
	camData.playerData = m_player->getObject()->getPosition();
	// find the distance between the player and the camera point
	camData.displacement.x = camData.playerData->x - camera->getCameraLook()->x;
	camData.displacement.y = camData.playerData->y - camera->getCameraLook()->y;


	// calculate camera point

	// if the displacement is too small, ignore it
	if(!(camData.displacement.x > 0.000001 || camData.displacement.x < -0.000001))
		camData.displacement.x = 0;
	if(!(camData.displacement.y > 0.000001 || camData.displacement.y < -0.000001))
		camData.displacement.y = 0;


	// move camera by a fraction of that distance
	if((camData.displacement.x > 0.01 || camData.displacement.x < -0.01))
		camData.point.x = camData.displacement.x * updateTime * 3.8f;
	else
		camData.point.x = camData.displacement.x * 0.1f;
	if((camData.displacement.y > 0.01 || camData.displacement.y < -0.01))
		camData.point.y = camData.displacement.y * updateTime * 3.8f;
	else
		camData.point.y = camData.displacement.y * 0.1f;


	camData.point.x += camera->getCameraLook()->x;
	camData.point.y += camera->getCameraLook()->y;


	// calculate camera position

	// optional: offset position over player slightly
	float offset = 0.01f;

	// find the distance between the player and the camera point
	camData.displacement.x = camData.playerData->x - camera->getCameraPosition()->x;
	camData.displacement.y = camData.playerData->y - camera->getCameraPosition()->y;

	// if the displacement is too small, ignore it
	if(!(camData.displacement.x > 0.000001 || camData.displacement.x < -0.000001))
		camData.displacement.x = 0;
	if(!(camData.displacement.y > 0.000001 || camData.displacement.y < -0.000001))
		camData.displacement.y = 0;

		// move camera by a fraction of that distance
	if((camData.displacement.x > 0.01 || camData.displacement.x < -0.01))
		camData.pos.x = camData.displacement.x * updateTime * 1.2f;
	else
		camData.pos.x = camData.displacement.x * 0.05f;
	if((camData.displacement.y > 0.01 || camData.displacement.y < -0.01))
		camData.pos.y = camData.displacement.y * updateTime * 1.2f;
	else
		camData.pos.y = camData.displacement.y * 0.05f;

	camData.pos.x += camera->getCameraPosition()->x;
	camData.pos.y += camera->getCameraPosition()->y + offset;

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
}
void level::draw()
{
	m_map->draw();
	backGrnd->draw();
	objMgr->draw();
	p1HUD->draw();
	FPSText->draw();
	
	switch(state)
	{
	case levelPaused:// check if game is paused
		pauseScreen->draw();
		break;
	case levelWin: // check if game level is over
		winScreen->draw();
		statsDisplay->draw();
		break;
	default:
		break;
	}
}
void level::handleInput(inputData * input, int now)
{
	if(state == levelPlay) // only allow movement if game is in play mode
	{
		// keyboard input

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


		// xbox controller input

		if(input->xcont->IsConnected())
		{
			// up
			if (input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				m_player->move(0, 12.0f);
			}

			// down
			if (input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				// down key does NOTHING
			}

			// left
			if (input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				m_player->move(-5.0f, 0);
			}

			// right
			if (input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				m_player->move(5.0f, 0);
			}

			// if neither left or right are active

			if ((!(input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				&& !(input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
				&& (!((input->keystate[DIK_LEFT] & 0x80) || (input->keystate[DIK_A] & 0x80))
			&& !((input->keystate[DIK_RIGHT] & 0x80) || (input->keystate[DIK_D] & 0x80))))
			{
				m_player->getObject()->getPhysics()->walkingOff();
			}

			if(!m_player->isAlive())
			{
				input->xcont->Vibrate(65535,65535);
			}
			else
			{
				input->xcont->Vibrate();
			}
		}
	}

	// pause (any state except win)
	if(state != levelWin)
	{
		if ((input->keystate[DIK_P] & 0x80) || (input->xcont->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START))
		{
			if(now - input->keyLag[DIK_P] > 400)
			{
				switch(state)
				{
				case levelPlay:
					state = levelPaused;
					break;
				case levelPaused:
					state = levelPlay;
					break;
				}
				input->keyLag[DIK_P] = now;
			}
		}
	}

	if ((input->keystate[DIK_R] & 0x80))
	{
		if(now - input->keyLag[DIK_R] > 200)
		{
			input->keyLag[DIK_R] = now;
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

	// debugging
	if ((input->keystate[DIK_C] & 0x80))
	{
		if(now - input->keyLag[DIK_C] > 200)
		{
			input->keyLag[DIK_C] = now;
			if(camData.pos.z == -12.0f)
			{
				camData.pos.z = -25.0f;
			}
			else
				camData.pos.z = -12.0f;
		}
	}
	if((input->keystate[DIK_K] & 0x80))
	{
		if(now - input->keyLag[DIK_K] >200)
		{
			input->keyLag[DIK_K] = now;
			m_player->keyPickup();
		}
	}
	if((input->keystate[DIK_F] & 0x80))
	{
		if(now - input->keyLag[DIK_F] >200)
		{
			input->keyLag[DIK_F] = now;
			FPSText->toggleImage();
			FPSText->toggleText();
		}
	}

}
level::~level()
{
	delete FPSText;
	delete m_map;
	delete entityMgr;
	delete objMgr;
	delete files;
	delete checkpointtxt;
	delete pauseScreen;
	delete winScreen;
	delete statsDisplay;
}
int level::getState(){return int(state);}