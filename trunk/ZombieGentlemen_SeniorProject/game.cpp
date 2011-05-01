//#define physics
#include "game.h"

#ifdef testEnvironment

game::game(HWND * a_wndHandle, HINSTANCE * a_hInstance)
{
	m_hInstance = a_hInstance;
	m_wndHandle = a_wndHandle;
}
bool game::initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr)
{

	dxMgr = a_dxMgr;
	inputMgr = a_inputMgr;
	soundMgr = a_soundMgr;

	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	camera = new dxCamera(dxMgr);
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -10.0f;

	QueryPerformanceFrequency(&timerFreq);
	Elapsed  = 0;
	FPS = 0;
	FPSText = new DXText(dxMgr, "images/BlackTextBox.bmp");
	FPSText->textInfo("Arial", 18,
					 D3DCOLOR_ARGB(255, 255, 255, 255),
					 "Loading...");
	FPSText->setTextBoxParameters(200, 50, 200, 500, 8);

	keyLag = new int [256];
	for(int i = 0; i < 256; i++){keyLag[i] = 0;}
	postion.x=0.0f;
	postion.y=0.0f;

	lvl = new level(dxMgr,"testfiles2.txt");
	//enemy = new EnemyCharacter(dxMgr, "images/arrows2.bmp");
	player = new PlayerCharacter(dxMgr, "images/armorBar.bmp");
	//player->initPlayerSpriteSheet(1,1);
	//player->setPlayerSprite(0,0);
	//player->setPosition(0, 4, 0);

	//enemy->initEnemieSpriteSheet(1,4);
	//enemy->setEnemieSprite(0, 3);
	//enemy->setPosition(1, 4, 0);

	setMusic();

	SetSprites();
	// set the starting point for the cursor
	curX = WINDOW_WIDTH/2;
	curY = WINDOW_HEIGHT/2;
	cursor->setPosition((float)curX, (float)curY);
	background->setPosition(0,0);
	return true;
}
void game::setMusic()
{
	//Load sound (filename, bufferID) in this case the first buffer is 0
	soundMgr->LoadSound("sound/Combat music.wav", 0);
	//SetVolume(bufferID, Volume)
	soundMgr->SetVolume(0, -2000);
	//play sound playSound(bufferID) in this case the first buffer is 0
	soundMgr->playSound(0);
}
void game::SetSprites()
{
	cursor = new HudImage(dxMgr,"images/cursor.dds");
	cursor->setSize(20, 20);
	background = new HudImage(dxMgr,"images/Lake level.dds");
	background->setSize(100, 100);
	dialog = new DXText(dxMgr, "images/Game_Dialog.bmp");
	dialog->textInfo("Arial", 24,
					 D3DCOLOR_ARGB(255, 0, 0, 255),
					 "That's a new face. Nobody ever comes around here"
					 " after the town was destroyed.  What do you need?");
	dialog->setTextBoxParameters(500, 250, 10, 40, 25);
	/*----------------------------------------------------------------------*
	 *                         HUD IMAGE TESTING                            *
	 *---------------------------------------------------------------------**/
	hudStuff = new HUD(dxMgr);
	//player = new ;
	hudStuff->setPlayer(player);
	hudStuff->setHudImage("images/new_hud.bmp");
	hudStuff->setBarHolderImage("images/bar_holder.bmp");
	hudStuff->setHealthBarImage("images/healthBar.bmp");
	hudStuff->setBarHolder2Image("images/bar_holder2.bmp");
	hudStuff->setArmorBarImage("images/armorBar.bmp");
	hudStuff->setWeaponImage("images/shovel_weapon.bmp");
	hudStuff->setBagOfMoneyImage("images/moneyBag.bmp");
	hudStuff->setPlayerIDImage("images/WillConcept.bmp");
	hudStuff->setCurrencyValue("images/moneyTextBox.bmp");
	hudStuff->initDefaultPositions(2.0, 0.0);

			
	
	//--------------------------------------------------------------------
	
	// set the starting point for the circle sprite
	background->setPosition(0,0);

}

void game::update()
{

	//update time
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceCounter(&timeStart);
	lvl->update(now);
	// Handle Input using Direct Input
	handleInput();
	// draw to the screen using Direct3D
	draw();

	// update high resolution timer
	QueryPerformanceCounter(&timeEnd);
	UpdateSpeed = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;

	hudStuff->updateCurrencyValue();
	UpdateFPS();

}
void game::UpdateFPS()
{
	FPS++;
	Elapsed += UpdateSpeed;

	if(Elapsed >= 1)
	{
		char UpdateBuffer[50];
		sprintf_s(UpdateBuffer, "FPS: %i \nTime elapsed: %f", FPS, Elapsed);
		FPSText->setDialog(UpdateBuffer);
		Elapsed = 0;
		FPS = 0;
	}
}


void game::handleInput()
{
	inputMgr->reAcquireDevices();
	inputMgr->updateKeyboardState(); 
	keystate = inputMgr->getKeyboardState();
	inputMgr->updateMouseState();
	mouseState = *(inputMgr->getMouseState());
	int cameraLag = 0;



	// keyboard
	if(keystate[DIK_ESCAPE] & 0x80)
	{
		PostQuitMessage(0);
	}
	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		player->moveplayer(postion.x,postion.y+=0.05);
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		player->moveplayer(postion.x,postion.y-=0.05);
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		player->moveplayer(postion.x-=0.05,postion.y);
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		player->moveplayer(postion.x+=0.05,postion.y);
	}
	
	/******HUD Money Incriment************/
	if((keystate[DIK_SPACE]& 0x80))
	{
		if(now - keyLag[DIK_SPACE] > 150)
		{
			player->addMoney(1);
			keyLag[DIK_SPACE] = now;
		}
	}
	//******keydown for HEALTH BAR********/
	if((keystate[DIK_Z]& 0x80))
	{
		if(now - keyLag[DIK_Z] > 150)
		{
			hudStuff->updateHealthBarDamage();
			
			keyLag[DIK_Z] = now;
		}
	}
	//******keydown for ARMOR BAR********/
	if((keystate[DIK_X]& 0x80))
	{
		if(now - keyLag[DIK_X] > 150)
		{
			hudStuff->updateArmorBarDamage(1);		
			keyLag[DIK_X] = now;
		}
	}
	//******keydown for using a healthPack********/
	if((keystate[DIK_C]& 0x80))
	{
		if(now - keyLag[DIK_C] > 150)
		{
			//displays weapon type
			hudStuff->useHealthPack();
			keyLag[DIK_C] = now;
			
		}
	}

	//******keydown for using a armorPack********/
	if((keystate[DIK_Q]& 0x80))
	{
		if(now - keyLag[DIK_Q] > 150)
		{
			//displays weapon type
			hudStuff->useArmorPickUp();
			keyLag[DIK_Q] = now;
			
		}
	}
	//******keydown for WEAPON DISPLAY********/
	if((keystate[DIK_F1]& 0x80))
	{
		if(now - keyLag[DIK_F1] > 150)
		{
			//displays weapon type
			hudStuff->updateWeapon("images/shovel_weapon.bmp");
			keyLag[DIK_F1] = now;
		}
	}
	//******keydown for WEAPON DISPLAY2********/
	if((keystate[DIK_F2]& 0x80))
	{
		if(now - keyLag[DIK_F2] > 150)
		{
			//displays weapon type
			hudStuff->updateWeapon("images/club.bmp");
			keyLag[DIK_F2] = now;
		}
	}
	//******keydown for WEAPON DISPLAY3********/
	if((keystate[DIK_F3]& 0x80))
	{
		if(now - keyLag[DIK_F3] > 150)
		{
			//displays weapon type
			hudStuff->updateWeapon("images/sword.bmp");
			keyLag[DIK_F3] = now;
		}
	}
	
	// mouse movement
	curX += mouseState.lX*1.5f;
	curY += mouseState.lY*1.5f;
	cursor->setPosition((float)curX, (float)curY);
}
void game::draw()
{
	dxMgr->beginRender();
	camera->SetupCamera2D(cameraX, cameraY, cameraZ);

	lvl->draw();
	player->Draw();
	
	//enemy->Draw();
	hudStuff->draw();	

	//background->drawSprite();

	cursor->draw();

	FPSText->draw();

	//dialog->draw();

	dxMgr->endRender();
}
game::~game()
{		
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
		
	// release sprites
	cursor->~HudImage();
	//testTile->~XYPlane();
	player->~PlayerCharacter();
	//enemy->~EnemyCharacter();
	dialog->~DXText();
	hudStuff->~HUD();
	FPSText->~DXText();
}
#endif


#ifndef testEnvironment

game::game(HWND * a_wndHandle, HINSTANCE * a_hInstance)
{
	m_hInstance = a_hInstance;
	m_wndHandle = a_wndHandle;
}
bool game::initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr)
{
	// initiallize game data
	dxMgr = a_dxMgr;
	inputMgr = a_inputMgr;
	soundMgr = a_soundMgr;
	m_currentgamestate = menu;
	m_charstate = char_idle;
	//instantiate menu
	/*mainMenu = new Menu(dxMgr,"MenuArt.txt","options.txt");
	mainMenu->setParam(800,600,0,0);*/

	// initialize timer data
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceFrequency(&timerFreq);
	Elapsed  = 0;
	FPS = 0;

	// initialize FPS display data
	FPSText = new DXText(dxMgr, "images/BlackTextBox.bmp");
	FPSText->loadFromTxtFile("textParameters.txt");
	FPSText->setDialog("Loading...");

	physicsData = new DXText(dxMgr, "images/BlackTextBox.bmp");
	physicsData->loadFromTxtFile("textParameters2.txt");
	physicsData->setDialog("Loading...");

	// initialize key lag data
	keyLag = new int [256];
	for(int i = 0; i < 256; i++){keyLag[i] = 0;}

	camera = new dxCamera(dxMgr);
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -10.0f;

	lvl1 = new level(dxMgr,"testfiles.txt");
	setMusic();
	return true;
}
void game::setMusic()
{
	//Load sound (filename, bufferID) in this case the first buffer is 0
	soundMgr->LoadSound("sound/Combat music.wav", 0);
	//SetVolume(bufferID, Volume)
	soundMgr->SetVolume(0, -2000);
	//play sound playSound(bufferID) in this case the first buffer is 0
	soundMgr->playSound(0);
}
void game::update()
{

	//update time
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceCounter(&timeStart);
	
	// Handle Input using Direct Input
	handleInput();
	// handle collision & update physics
	lvl1->update(UpdateSpeed);
	float ycoord = lvl1->getobject()->getPosition()->y;
	float xcoord = lvl1->getobject()->getPosition()->x;
	cameraX = xcoord;
	cameraY = ycoord;

	// draw to the screen using Direct3D
	draw();

	// update high resolution timer
	QueryPerformanceCounter(&timeEnd);
	UpdateSpeed = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;

	updateDebugData();
}
void game::updateDebugData()
{
	// display FPS
	FPS++;
	Elapsed += UpdateSpeed;

	if(Elapsed >= 1)
	{
		char UpdateBuffer[256];
		sprintf_s(UpdateBuffer, "FPS: %i", FPS);
		FPSText->setDialog(UpdateBuffer);
		Elapsed = 0;
		FPS = 0;
	}

	// display phsics
	if(Elapsed >= 0.0)
	{
		char PhysicsBuffer[256];
		if(lvl1->getObjectPhysic())
		{
			sprintf_s(PhysicsBuffer, "Physics x: %f\nPhysics y: %f", 
				lvl1->getObjectPhysic()->getXVelocity(), 
				lvl1->getObjectPhysic()->getYVelocity());
		}
		else
		{
			sprintf_s(PhysicsBuffer, "Physics Disabled");
		}
		physicsData->setDialog(PhysicsBuffer);
	}
}

void game::handleGamState()
{
	if(m_currentgamestate == menu)
	{
		int check = mainMenu->update(keystate,now,keyLag);
		if(check == 1)
		{
			 mainMenu->~Menu();
			 m_currentgamestate = adventure_mode;
		}
		else if(check == 2)
		{
			PostQuitMessage(0);
		}
		else
		{
			m_charstate = char_jump;
		}
	}
}


void game::handleInput()
{
	inputMgr->reAcquireDevices();
	inputMgr->updateKeyboardState(); 
	keystate = inputMgr->getKeyboardState();
	inputMgr->updateMouseState();
	mouseState = *(inputMgr->getMouseState());
 	float cameraMove = 0.05f;
	int cameraLag = 0;

	// keyboard
	//mainMenu->update(keystate,now,keyLag);

	if(keystate[DIK_ESCAPE] & 0x80)
	{
		PostQuitMessage(0);
	}

	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		if(lvl1->getObjectPhysic())
		{
			lvl1->getObjectPhysic()->setYVelocity(12.0f);
		}
		else
			lvl1->moveObject(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		/*if(lvl1->getObjectPhysic())
		{
			lvl1->getObjectPhysic()->setYVelocity(-0.05f);
		}
		else*/
			lvl1->moveObject(D3DXVECTOR3(0.0f, -0.05f, 0.0f));
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		if(lvl1->getObjectPhysic())
		{
			if(lvl1->getObjectPhysic()->canMoveLeft())
			{
				lvl1->getObjectPhysic()->walkingOn();
				lvl1->getObjectPhysic()->setXVelocity(-8.0f);
			}
		}
		else
			lvl1->moveObject(D3DXVECTOR3(-0.05f, 0.0f, 0.0f));
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		if(lvl1->getObjectPhysic())
		{
			if(lvl1->getObjectPhysic()->canMoveRight())
			{
				lvl1->getObjectPhysic()->walkingOn();
				lvl1->getObjectPhysic()->setXVelocity(8.0f);
			}
		}
		else
			lvl1->moveObject(D3DXVECTOR3(0.05f, 0.0f, 0.0f));
	}
	
	if (!((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
		&& !((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80)))
	{
		if(lvl1->getObjectPhysic())
		{
			lvl1->getObjectPhysic()->walkingOff();
		}
	}
	

	if ((keystate[DIK_B] & 0x80))
	{
		if(now - keyLag[DIK_B] > 200)
		{
			lvl1->getManager()->getObject()->togglePhysics();
			keyLag[DIK_B] = now;
		}
	}

	if ((keystate[DIK_G] & 0x80))
	{
		if(now - keyLag[DIK_G] > 200)
		{
			lvl1->getManager()->indexPrev();
			keyLag[DIK_G] = now;
		}
	}
	if ((keystate[DIK_H] & 0x80))
	{
		if(now - keyLag[DIK_H] > 200)
		{
			lvl1->getManager()->indexNext();
			keyLag[DIK_H] = now;
		}
	}

	if ((keystate[DIK_P] & 0x80))
	{
		if(now - keyLag[DIK_P] > 200)
		{
			lvl1->getManager()->pop();
			keyLag[DIK_P] = now;
		}
	}
	//test key
	if((keystate[DIK_E] & 0x80))
	{
		if(now - keyLag[DIK_E] >200)
		{
			lvl1->~level();
			lvl1 = new level(dxMgr,"testfiles2.txt");
		}
	}

	// camera movement
	/*if ((keystate[DIK_NUMPAD4] & 0x80) || (keystate[DIK_J] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD4] > cameraLag)
		{
			cameraX-= cameraMove;
			keyLag[DIK_NUMPAD4] = now;
		}
	}
	if ((keystate[DIK_NUMPAD6] & 0x80) || (keystate[DIK_L] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD6] > cameraLag)
		{
			cameraX += cameraMove;
			keyLag[DIK_NUMPAD6] = now;
		}
	}
	if ((keystate[DIK_NUMPAD2] & 0x80) || (keystate[DIK_K] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD2] > cameraLag)
		{
			cameraY -= cameraMove;
			keyLag[DIK_NUMPAD2] = now;
		}
	}
	if ((keystate[DIK_NUMPAD8] & 0x80) || (keystate[DIK_I] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD8] > cameraLag)
		{
			cameraY+= cameraMove;
			keyLag[DIK_NUMPAD8] = now;
		}
	}*/
		
	if ((keystate[DIK_NUMPAD7] & 0x80) || (keystate[DIK_U] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD7] > cameraLag)
		{
			if(cameraZ < -1.1)
			{
				cameraZ += cameraMove;
				keyLag[DIK_NUMPAD7] = now;
			}
		}
	}
	if ((keystate[DIK_NUMPAD9] & 0x80) || (keystate[DIK_O] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD9] > cameraLag)
		{
			cameraZ -= cameraMove;
			keyLag[DIK_NUMPAD9] = now;
		}
	}
}
void game::draw()
{
	dxMgr->beginRender();

	camera->SetupCamera2D(cameraX, cameraY, cameraZ);
	//camera->updateCamera3D(D3DXVECTOR3(cameraX, cameraY, cameraZ), D3DXVECTOR3(0, 0, 0)); 

	lvl1->draw();
	//mainMenu->Draw();

	camera->SetHudCamera();

	FPSText->draw();
	physicsData->draw();

	dxMgr->endRender();
}
game::~game()
{		
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
	// destroy map
	FPSText->~DXText();

	lvl1->~level();

}
#endif