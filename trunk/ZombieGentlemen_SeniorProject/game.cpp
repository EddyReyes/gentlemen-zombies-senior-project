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

	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceFrequency(&timerFreq);

	keyLag = new int [256];
	for(int i = 0; i < 256; i++){keyLag[i] = 0;}

	//camera = new dxCamera(dxMgr);
	cameraX = -5.0f;
	cameraY = 8.0f;
	cameraZ = -10.0f;

	testTile = new dxCube(dxMgr, "images/glassPanes2.bmp");
	testTile->setImageRowsColumns(1, 4);
	testTile->selectTextureSource(0, 1);

	testTile2 = new XYPlane(dxMgr, "images/Character.bmp");
	testTile2->setScale(1.1f);
	//testTile2->selectTextureSource(3, 2);
	testTile2->setPosition(0, 1, 0);

	testTile3 = new XYPlane(dxMgr, testTile->getTexture(), testTile->getImageInfo());
	testTile3->setImageRowsColumns(1, 4);
	testTile3->selectTextureSource(0, 2);
	testTile3->setPosition(-2, 0, 1.5);

	//testTile->setPosition(D3DXVECTOR3(1.0f, 2.0f, 0.0f));
	//testTile->setScale(0.5f);

	m_map = new Map("testMap.txt", dxMgr, true);
	
	
	scale = 1.0f;
	player = new PlayerCharacter(dxMgr, "images/arrows2.bmp");
	enemy = new EnemyCharacter(dxMgr, "images/arrows2.bmp");
	player->initPlayerSpriteSheet(1,4);
	player->setPlayerSprite(0,0);
	player->setPosition(4, 1, 0);

	enemy->initEnemieSpriteSheet(1,4);
	enemy->setEnemieSprite(0, 3);
	enemy->setPosition(4, 4, 0);
	

	camera = new dxCamera(dxMgr);


	setMusic();

	SetSprites();
	// set the starting point for the cursor
	curX = WINDOW_WIDTH/2;
	curY = WINDOW_HEIGHT/2;
	cursor->setPosition((float)curX, (float)curY);
	position.x = 0;
	position.y = 0;
	arrowSprite->setPosition(position.x,position.y);
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
	
	arrowSprite = new HudImage(dxMgr,"images/lambo.bmp");
	arrowSprite->scaleSize(100.0f/256.0f);
	cursor = new HudImage(dxMgr,"images/cursor.dds");
	cursor->scaleSize(0.5f);
	background = new HudImage(dxMgr,"images/Lake level.dds");
	background->scaleSize(1.0f);
	dialog = new DXText(dxMgr, "images/Game_Dialog1.bmp");
	dialog->textInfo("Charlemagne std", 22,
					 D3DCOLOR_ARGB(255, 255, 255, 0),
					 "The text finally works!!");
	dialog->setRect(50, 200, 20, 400);
	
		

	// set the starting point for the circle sprite
	position.x = 0;
	position.y = 0;

	arrowSprite->setPosition(position.x,position.y);
	background->setPosition(0,0);

}
bool game::collides(PlayerCharacter* a,EnemyCharacter* b)//stub
{	//nothing works =/	
	/*float ax = a->getPosition().x;	
	float ay = a->getPosition().y;	
	float bx = b->getPosition().x;	
	float by = b->getPosition().y;	
	//actually checks if its colliding	
	if(ax>=bx||		
	ay>=by||		
	ax+a->getWidth()==bx||		
	ax+a->getWidth()==bx+b->getWidth())		
	return true;*/	
	return false;}
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
	animationRate = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;
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

	//if ((keystate[DIK_J] & 0x80))
	//{
	//	if(now - keyLag[DIK_J] > 150)
	//	{
	//		if( scale > 0.2)
	//		{
	//			scale -= 0.1f;
	//			testTile->setScale(scale);
	//			keyLag[DIK_J] = now;
	//		}
	//	}
	//}
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
	float moveDistance = 5.0f;
	int prevX, prevY;
	prevX = position.x;	prevY = position.y;	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		position.y += (int)moveDistance;
		//arrowSprite->selectSpriteSource(1);
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		position.y -= (int)moveDistance;
		//arrowSprite->selectSpriteSource(2);
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		position.x -= (int)moveDistance;
		//arrowSprite->selectSpriteSource(0);	
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		position.x += (int)moveDistance;
		//arrowSprite->selectSpriteSource(3);
	}
	//arrowSprite->setPosition(position.x,position.y);
	if(collides(player,enemy))	{		player->setPosition(prevX*0.005,prevY*0.005,0);	}	else	{		player->setPosition(position.x*0.005,position.y*0.005,0);	}
	if ((keystate[DIK_B] & 0x80))
	{
		if(now - keyLag[DIK_B] > 150)
		{
			background->toggleSprite();
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

	//camera->SetupCamera2D(cameraX, cameraY, cameraZ);
	camera->updateCamera3D(D3DXVECTOR3(cameraX, cameraY, cameraZ), D3DXVECTOR3(0, 0, 0)); 
	//testTile->setRenderStates();
	m_map->draw();
	testTile->draw();
	testTile2->draw();
	testTile3->draw();
	player->Draw();
	enemy->Draw();


	camera->SetHudCamera();

	//background->drawSprite();
	

	arrowSprite->draw();

	cursor->draw();

	dialog->draw();

	dxMgr->endRender();
}
game::~game()
{		
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
	
	// release sprites
	arrowSprite->~HudImage();
	cursor->~HudImage();
	testTile->~dxCube();
	testTile2->~XYPlane();
	testTile3->~XYPlane();
	player->~PlayerCharacter();
	enemy->~EnemyCharacter();
	dialog->~DXText();
}