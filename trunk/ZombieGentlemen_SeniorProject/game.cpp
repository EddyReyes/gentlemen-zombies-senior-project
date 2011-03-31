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
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -10.0f;

	testTile = new XYPlane(dxMgr, "images/letters.bmp");
	testTile->setImageRowsColumns(4, 7);
	testTile->selectTextureSource(2, 3);

	testTile2 = new XYPlane(dxMgr, testTile->getTexture(), testTile->getImageInfo());
	testTile2->setImageRowsColumns(4, 7);
	testTile2->selectTextureSource(3, 2);
	testTile2->setPosition(2, 0, -1.5);

	testTile3 = new XYPlane(dxMgr, testTile->getTexture(), testTile->getImageInfo());
	testTile3->setImageRowsColumns(4, 7);
	testTile3->selectTextureSource(0, 5);
	testTile3->setPosition(-2, 0, 1.5);

	//testTile->setPosition(D3DXVECTOR3(1.0f, 2.0f, 0.0f));
	//testTile->setScale(5.0f);
	//testTile->setScaleFromCenter(true);
	
	scale = 1.0f;
	player = new PlayerCharacter(dxMgr, "images/arrows2.bmp");
	player->initPlayerSpriteSheet(1,4);
	player->setPlayerSprite(0,0);
	player->setPosition(5, 5, 5);
	camera = new dxCamera(dxMgr);

	//Grid = new grid(100,WINDOW_WIDTH, WINDOW_HEIGHT,dxMgr);
	Grid = new grid(100,1000,1000,dxMgr);
	Grid->initGrid();

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
	dialog = new HudImage(dxMgr, "images/Game_Dialog1.bmp");
	dialog->scaleSize(0.8f);
	dialog->setPosition(600,540);

	// set the starting point for the circle sprite
	position.x = 0;
	position.y = 0;
	arrowSprite->setPosition(position.x,position.y);
	background->setPosition(0,0, 0);
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
			Grid->toggleGrid();
			keyLag[DIK_G] = now;
		}
	}

	if ((keystate[DIK_SUBTRACT] & 0x80) || (keystate[DIK_MINUS] & 0x80))
	{
		if(now - keyLag[DIK_MINUS] > 150)
		{
			Grid->changeGridScale(-10);
			keyLag[DIK_MINUS] = now;
		}
	}

	if ((keystate[DIK_ADD] & 0x80) || (keystate[DIK_EQUALS] & 0x80))
	{
		if(now - keyLag[DIK_ADD] > 150)
		{
			Grid->changeGridScale(10);
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

	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		position.y -= (int)moveDistance;
		arrowSprite->selectSpriteSource(1);
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		position.y += (int)moveDistance;
		arrowSprite->selectSpriteSource(2);
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		position.x -= (int)moveDistance;
		arrowSprite->selectSpriteSource(0);
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		position.x += (int)moveDistance;
		arrowSprite->selectSpriteSource(3);
	}
	arrowSprite->setPosition(position.x,position.y);

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
	testTile->draw();
	testTile2->draw();
	testTile3->draw();
	player->Draw();

	camera->SetHudCamera();

	//background->drawSprite();
	
	Grid->drawGrid();

	arrowSprite->draw();

	cursor->draw();

	dialog->draw();

	dxMgr->endRender();
}

game::~game()
{		
	Grid->~grid();
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
	
	// release sprites
	arrowSprite->~HudImage();
	cursor->~HudImage();
	testTile->~XYPlane();
}