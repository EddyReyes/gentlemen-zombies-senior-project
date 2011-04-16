//#define physics
#include "game.h"

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
	OBLIST = new objectManager;

	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceFrequency(&timerFreq);
	Elapsed  = 0;
	FPS = 0;
	FPSText = new DXText(dxMgr, "images/BlackTextBox.bmp");
	FPSText->textInfo("Arial", 18,
					 D3DCOLOR_ARGB(255, 255, 255, 255),
					 "Loading...");
	FPSText->setTextBoxParameters(200, 50, 20, 500, 8);

	keyLag = new int [256];
	for(int i = 0; i < 256; i++){keyLag[i] = 0;}

	//camera = new dxCamera(dxMgr);
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -10.0f;

	//inits physics object
	physics = new phyVars;
	//testTile = new XYPlane(dxMgr, "images/Character.bmp");
	//testTile->setScale(1.1f);
	//testTile2->selectTextureSource(3, 2);
	//testTile->setPosition(0, 1, 0);


	m_map = new cubeMap("testMap.txt", "images/glassPanes2.bmp", dxMgr);

	testObject = new object(dxMgr, "images/Character.bmp", "testObject.txt");
	testCube = new dxCube(dxMgr, "images/glass tile.bmp");
	testCube->toggleTransparencyCulling();
	testObject2 = new object(testCube, "testObject2.txt");
	testObject2->setPosition(0.0f, -2.0f, 0.0f);
	objectX = 0; 
	objectY = 1;
	//OBLIST->insert(testObject);//////////////////////////////////////////////////////////TESTING LIST/////////////////////////////////
	//OBLIST->insert(testObject2);

	scale = 1.0f;
	player = new PlayerCharacter(dxMgr, "images/Character.bmp");
	enemy = new EnemyCharacter(dxMgr, "images/arrows2.bmp");
	player->initPlayerSpriteSheet(1,1);
	player->setPlayerSprite(0,0);
	player->setPosition(0, 4, 0);

	enemy->initEnemieSpriteSheet(1,4);
	enemy->setEnemieSprite(0, 3);
	enemy->setPosition(1, 4, 0);

	camera = new dxCamera(dxMgr);


	setMusic();

	SetSprites();
	// set the starting point for the cursor
	curX = WINDOW_WIDTH/2;
	curY = WINDOW_HEIGHT/2;
	cursor->setPosition((float)curX, (float)curY);
	position.x = 0;
	position.y = 0;
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
	hudStuff->setHudImage("images/new_hud.bmp");
	hudStuff->setHealthBarImage("images/healthBar.bmp");
	hudStuff->setArmorBarImage("images/armorBar.bmp");
	hudStuff->setWeaponImage("images/sword.bmp");
	hudStuff->setBagOfMoneyImage("images/moneyBag.bmp");
	hudStuff->setPlayerIDImage("images/WillConcept.bmp");
	hudStuff->initDefaultPositions(500.0, 0.0);
	//--------------------------------------------------------------------
	
	// set the starting point for the circle sprite
	position.x = 0;
	position.y = 0;
	background->setPosition(0,0);

}
//bool game::collides(PlayerCharacter* a,EnemyCharacter* b)//stub
//{	//nothing works =/	
	/*float ax = a->getPosition().x;	
	float ay = a->getPosition().y;	
	float bx = b->getPosition().x;	
	float by = b->getPosition().y;	
	//actually checks if its colliding	
	if(ax>=bx||		
	ay>=by||		
	ax+a->getWidth()==bx||		
	ax+a->getWidth()==bx+b->getWidth())	*/
	//if(a->getPosition().x>2.000||
	//	a->getPosition().x<-2.000)
		//return true;	
	//else
	//	return false;
//}
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
	// draw to the screen using Direct3D
	draw();

	// update high resolution timer
	QueryPerformanceCounter(&timeEnd);
	UpdateSpeed = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;

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


	// keyboard


	if(keystate[DIK_ESCAPE] & 0x80)
	{
		PostQuitMessage(0);
	}

	if ((keystate[DIK_G] & 0x80))
	{
		if(now - keyLag[DIK_G] > 150)
		{
			keyLag[DIK_G] = now;
		}
	}

	if ((keystate[DIK_SUBTRACT] & 0x80) || (keystate[DIK_MINUS] & 0x80))
	{
		if(now - keyLag[DIK_MINUS] > 150)
		{
			keyLag[DIK_MINUS] = now;
		}
	}

	if ((keystate[DIK_ADD] & 0x80) || (keystate[DIK_EQUALS] & 0x80))
	{
		if(now - keyLag[DIK_ADD] > 150)
		{
			keyLag[DIK_ADD] = now;
		}
	}

	if ((keystate[DIK_H] & 0x80))
	{
		if(now - keyLag[DIK_H] > 150)
		{
			if( scale > 0.2)
			{
				//OBLIST->get(0)->toggleCollision();
				testObject->toggleCollision();
				keyLag[DIK_H] = now;
			}
		}
	}
	if((keystate[DIK_X] & 0x80))//Mike's test key =P
	{
		//currently trying to delete things from a list on the fly
		if(now - keyLag[DIK_X] > 150)
		{
			OBLIST->remove(1);
		}
	}
	//if ((keystate[DIK_K] & 0x80))
	//{
	//	if(now - keyLag[DIK_K] > 150)
	//	{
	//		if( scale > 0.2)
	//		{
	//			scale += 0.1f;
	//			testTile->setScale(scale);
	//			keyLag[DIK_K] = now;
	//		}
	//	}
	//}

	// sprite movement
	float moveDistance = 0.005f;
	float prevX, prevY;
	
	prevX = objectX;	
	prevY = objectY;
	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		position.y += moveDistance;
		objectY += moveDistance;
		//physics->velY = 0.008;

	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		position.y -= moveDistance;
		objectY -= moveDistance;
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		position.x -= moveDistance;	
		objectX -= moveDistance;
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		position.x += moveDistance;
		objectX += moveDistance;
	}
	
	float x = testObject->getXYPlane()->getXPosition();
	float y = testObject->getXYPlane()->getYPosition();

#ifdef physics
	physics->velY -= physics->gravity;
	physics->velX *= physics->friction;

	x += physics->velX;
	y += physics->velY;
#endif
	testObject->setTargetCollision(testObject2->getCollisionRect());
	if(!testObject->handleCollision(objectX, objectY, 0.0f))
	{
		objectX = prevX;
		objectY = prevY;
	}
	else
	{
		objectX = x;
		objectY = y;
	}

	if ((keystate[DIK_B] & 0x80))
	{
		if(now - keyLag[DIK_B] > 200)
		{
			m_map->toggleMap();
			keyLag[DIK_B] = now;
		}
	}
	
	// camera movement
	float cameraMove = 0.05f;
	int cameraLag = 0;
	if ((keystate[DIK_NUMPAD4] & 0x80) || (keystate[DIK_J] & 0x80))
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
	}
		
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

	
	// mouse movement
	curX += mouseState.lX*1.5f;
	curY += mouseState.lY*1.5f;
	cursor->setPosition((float)curX, (float)curY);
}
void game::draw()
{
	dxMgr->beginRender();

	camera->SetupCamera2D(cameraX, cameraY, cameraZ);
	//camera->updateCamera3D(D3DXVECTOR3(cameraX, cameraY, cameraZ), D3DXVECTOR3(0, 0, 0)); 
	//testTile->setRenderStates();
	//testTile->draw();

	testObject->draw();
	testObject2->draw();
	//for(int c=0; c<OBLIST->getsize(); ++c)
	//{
		//OBLIST->get(c)->draw();
	//}
	m_map->draw();

	//player->Draw();
	
	//enemy->Draw();


	camera->SetHudCamera();

	//background->drawSprite();

	cursor->draw();

	FPSText->draw();

	//dialog->draw();
	hudStuff->draw();	

	dxMgr->endRender();
}
game::~game()
{		
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
	
	// destroy map
	m_map->~cubeMap();
	
	// release sprites
	cursor->~HudImage();
	//testTile->~XYPlane();
	player->~PlayerCharacter();
	enemy->~EnemyCharacter();
	dialog->~DXText();
	delete physics;
	hudStuff->~HUD();
	testObject->~object();
	testObject2->~object();
	//delete OBLIST;

}