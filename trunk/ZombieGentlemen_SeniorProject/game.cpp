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
	keyLag = new int [256];
	for(int i = 0; i < 256; i++){keyLag[i] = 0;}

	gameScreenLength = 600;
	gameScreenWidth = 800;


	Grid = new grid(100,(float)gameScreenWidth,(float)gameScreenLength,dxMgr);
	Grid->initGrid();

	setMusic();

	SetBMP();
	// set the starting point for the circle sprite
	curX = 320;
	curY = 240;

	screen.left = 0;
	screen.right = 48;
	screen.top = 0;
	screen.bottom = 48;

	src.left = 0;
	src.right = 48;
	src.top = 0;
	src.bottom = 48;
	msrc = src;
	return true;
}
void game::setMusic()
{
	//Load sound (filename, bufferID) in this case the first buffer is 0
	soundMgr->LoadSound("Combat music.wav", 0);
	//SetVolume(bufferID, Volume)
	soundMgr->SetVolume(0, -2000);
	//play sound playSound(bufferID) in this case the first buffer is 0
	soundMgr->playSound(0);
}
void game::SetBMP()
{
	arrows = dxMgr->getSurfaceFromBitmap("arrows.bmp",192, 48);
	mouseArrow = dxMgr->getSurfaceFromBitmap("mousearrows.bmp",192, 48);
}
void game::update()
{

	//update time
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;
	
	// Handle Input using Direct Input
	handleInput();
	
	// draw to the screen using Direct3D
	draw();
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

	if ((keystate[DIK_SUBTRACT] & 0x80))
	{
		if(now - keyLag[DIK_MINUS] > 150)
		{
			Grid->changeGridScale(-10);
			keyLag[DIK_MINUS] = now;
		}
	}

	if ((keystate[DIK_ADD] & 0x80))
	{
		if(now - keyLag[DIK_ADD] > 150)
		{
			Grid->changeGridScale(10);
			keyLag[DIK_ADD] = now;
		}
	}

	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		src.left = (48 * K_UP_ARROW);
		if(screen.top>0 && screen.bottom>48)
		{
			screen.top-=5;
			screen.bottom-=5;
		}
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		src.left = (48 * K_DOWN_ARROW);
		if(screen.bottom < 480 && screen.top < (480-50))
		{
			screen.bottom +=5;
			screen.top+=5;
		}
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		src.left = (48 * K_LEFT_ARROW);
		if(screen.left>0 && screen.right>48)
		{
			screen.left -=5;
			screen.right -=5;
		}
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		src.left = (48 * K_RIGHT_ARROW);
		if(screen.right < 650 && screen.left < (670-60))
		{
			screen.right +=5;
			screen.left +=5;
		}
	}

	src.right = src.left + 48;


	// mouse

	if (mouseState.rgbButtons[0] & 0x80)
		msrc.left = (48 * M_LEFT_ARROW);
	if (mouseState.rgbButtons[1] & 0x80)
		msrc.left = (48 * M_RIGHT_ARROW);
	msrc.right = msrc.left + 48;
	if (mouseState.rgbButtons[2] & 0x80)
		msrc.left = (48 * NONE);
	msrc.right = msrc.left + 48;

	// CIRCLE SPRITE
	// set the source rectangle
	spriteSrc.top = 0;
	spriteSrc.bottom = spriteSrc.top + 48;
	spriteSrc.left = (48 * CIRCLE);
	spriteSrc.right = spriteSrc.left + 48;
	// set the destination rectangle
	spriteDest.top = curY;
	spriteDest.left = curX;
	spriteDest.right = spriteDest.left + 48;
	spriteDest.bottom = spriteDest.top + 48;

	curX += mouseState.lX;
	curY += mouseState.lY;
}
void game::draw()
{
	dxMgr->beginRender();


	dxMgr->blitToSurface(mouseArrow, &msrc, NULL);

	// blit the sprite to the back buffer
	dxMgr->blitToSurface(mouseArrow, &spriteSrc, &spriteDest);

	// blit this letter to the back buffer
	dxMgr->blitToSurface(arrows, &src, &screen);


	// Draw grid
	Grid->drawGrid();

	dxMgr->endRender();
}

game::~game()
{		
	Grid->~grid();
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->shutdownDirectSound();
}