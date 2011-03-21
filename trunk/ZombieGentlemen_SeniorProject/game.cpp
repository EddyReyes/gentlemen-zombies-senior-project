#include "game.h"

#define debug

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

	SetSprites();
	// set the starting point for the circle sprite
	curX = 320;
	curY = 240;
	msrc.left = 0;
	msrc.right = 48;
	msrc.top = 0;
	msrc.bottom = 48;
	
	position.x = 0;
	position.y = 0;
	arrowSprite->setPosition(position.x,position.y);
	arrow->setLocation(position.x,position.y);
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
void game::SetSprites()
{
	arrowSprite = new dxSprite(dxMgr,"arrows2.bmp");
	arrowSprite->scaleSize(0.2f);
	arrow = new rectangle(dxMgr,"arrows.bmp");
	//arrowSprite->initializeDXSprite("arrows.bmp");
	//arrowSprite->initSprite(4, gameScreenWidth, gameScreenLength);
	
	/*arrowSprite->setScreenLocation(100,0);*/
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
	int moveDistance = 20;

	if (((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80))
		&& !((keystate[DIK_DOWN] & 0x80) || (keystate[DIK_S] & 0x80)))
	{
		position.y -= moveDistance;
		arrowSprite->selectSpriteSource(1);
		arrow->selectSpriteSource(1);
	}
	if (((keystate[DIK_DOWN] & 0x80)|| (keystate[DIK_S] & 0x80))
		&& !((keystate[DIK_UP] & 0x80) || (keystate[DIK_W] & 0x80)))
	{
		position.y += moveDistance;
		arrowSprite->selectSpriteSource(2);
		arrow->selectSpriteSource(2);
	}
	if ((keystate[DIK_LEFT] & 0x80) || (keystate[DIK_A] & 0x80))
	{
		position.x -= moveDistance;
		arrowSprite->selectSpriteSource(0);
		arrow->selectSpriteSource(0);
	}
	if ((keystate[DIK_RIGHT] & 0x80) || (keystate[DIK_D] & 0x80))
	{
		position.x += moveDistance;
		arrowSprite->selectSpriteSource(3);
		arrow->selectSpriteSource(3);
	}
	//arrowSprite->setLocation(position.x,position.y);
	arrowSprite->setPosition(position.x,position.y);
	//arrowSprite->setScreenLocation(position.x,position.y);
	//arrowSprite->updateRect();
	
	// mouse movement

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
	//dxMgr->blitToSurface(arrows, arrowSprite->getSpriteSource(), arrowSprite->getSpriteScreen());
	arrow->draw();

	arrowSprite->drawSprite();
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