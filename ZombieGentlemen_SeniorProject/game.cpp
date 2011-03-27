#include "game.h"

#define debug

#ifdef debug

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

	testTile = new tile(dxMgr, "images/Character.bmp");
	camera = new dxCamera(dxMgr);

	// set the starting point for the cursor
	curX = WINDOW_WIDTH/2;
	curY = WINDOW_HEIGHT/2;
	return true;
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

	// camera movement
	if ((keystate[DIK_NUMPAD4] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD4] > 300)
		{
			cameraX--;
			keyLag[DIK_NUMPAD4] = now;
		}
	}
	if ((keystate[DIK_NUMPAD6] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD6] > 300)
		{
			cameraX++;
			keyLag[DIK_NUMPAD6] = now;
		}
	}
	if ((keystate[DIK_NUMPAD2] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD2] > 300)
		{
			cameraY--;
			keyLag[DIK_NUMPAD2] = now;
		}
	}
	if ((keystate[DIK_NUMPAD8] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD8] > 300)
		{
			cameraY++;
			keyLag[DIK_NUMPAD8] = now;
		}
	}
	
	// mouse movement
	curX += mouseState.lX*1.5f;
	curY += mouseState.lY*1.5f;
}
void game::draw()
{
	dxMgr->beginRender();
	
	camera->updateCamera(D3DXVECTOR3(0.0f, 0.0f, 3.0f), 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	testTile->setRenderStates();
	testTile->draw();

	camera->SetHudCamera();

	dxMgr->endRender();
}

game::~game()
{
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();

	// release test tile
	testTile->~tile();
}

#endif

#ifndef debug 

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

	testTile = new tile(dxMgr, "images/Character.bmp");
	camera = new dxCamera(dxMgr);

	//Grid = new grid(100,WINDOW_WIDTH, WINDOW_HEIGHT,dxMgr);
	Grid = new grid(100,1000,1000,dxMgr);
	Grid->initGrid();

	setMusic();

	SetSprites();
	// set the starting point for the cursor
	curX = WINDOW_WIDTH/2;
	curY = WINDOW_HEIGHT/2;
	cursor->setPosition(curX, curY);
	position.x = 0;
	position.y = 0;
	arrowSprite->setPosition(position.x,position.y);
	background->setPosition(0,0);
	return true;
}
void game::setMusic()
{
	//Load sound (filename, bufferID) in this case the first buffer is 0
	soundMgr->LoadSound("sound/Peaceful.wav", 0);
	//SetVolume(bufferID, Volume)
	soundMgr->SetVolume(0, -2000);
	//play sound playSound(bufferID) in this case the first buffer is 0
	soundMgr->playSound(0);
}
void game::SetSprites()
{
	arrowSprite = new dxSprite(dxMgr,"images/lambo.bmp");
	arrowSprite->scaleSize(100.0f/256.0f);
	cursor = new dxSprite(dxMgr,"images/cursor.dds");
	cursor->scaleSize(0.5f);
	background = new dxSprite(dxMgr, "images/Lake level.dds");
	background->scaleSize(1.0f);

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

	// sprite movement
	float moveDistance = 5.0f;

	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		position.y -= moveDistance;
		arrowSprite->selectSpriteSource(1);
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		position.y += moveDistance;
		arrowSprite->selectSpriteSource(2);
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		position.x -= moveDistance;
		arrowSprite->selectSpriteSource(0);
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		position.x += moveDistance;
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

	if ((keystate[DIK_NUMPAD4] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD4] > 300)
		{
			cameraX--;
			keyLag[DIK_NUMPAD4] = now;
		}
	}
	if ((keystate[DIK_NUMPAD6] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD6] > 300)
		{
			cameraX++;
			keyLag[DIK_NUMPAD6] = now;
		}
	}
	if ((keystate[DIK_NUMPAD2] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD2] > 300)
		{
			cameraY--;
			keyLag[DIK_NUMPAD2] = now;
		}
	}
	if ((keystate[DIK_NUMPAD8] & 0x80))
	{
		if(now - keyLag[DIK_NUMPAD8] > 300)
		{
			cameraY++;
			keyLag[DIK_NUMPAD8] = now;
		}
	}
	
	// mouse movement
	curX += mouseState.lX*1.5f;
	curY += mouseState.lY*1.5f;
	cursor->setPosition(curX, curY);
}
void game::draw()
{
	dxMgr->beginRender();
	
	camera->updateCamera(D3DXVECTOR3(0.0f, 0.0f, 3.0f), 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	testTile->setRenderStates();
	testTile->draw();

	camera->SetHudCamera();

	background->drawSprite();
	
	Grid->drawGrid();

	arrowSprite->drawSprite();

	cursor->drawSprite();

	dxMgr->endRender();
}

game::~game()
{		
	Grid->~grid();
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
	
	// release sprites
	arrowSprite->releaseImage();
	arrowSprite->~dxSprite();
	cursor->releaseImage();
	cursor->~dxSprite();
}
#endif