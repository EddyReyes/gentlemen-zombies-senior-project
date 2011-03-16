/**
The game class will handle the bulk of the game logic
This class will contian the game states, the map, the players, the characters
etc.

status: unit test
*/
//#define debug
// DirectX files
#include "dxManager.h"
#include "directInput.h"
#include "sound.h"
#include <time.h>

#include "grid.h"
#include "object.h"
#include "physicsObject.h"

#include "map.h"
#include "entity.h"

#include "playerCharacter.h"
#include "playerItem.h"
#include "weapon.h"
#include "helmet.h"
#include "armor.h"

#pragma once

	#define KEYDOWN(name, key) (name[key] & 0x80) 
	#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80) 

	enum { K_LEFT_ARROW = 0,
		K_UP_ARROW,
		K_DOWN_ARROW,
		K_RIGHT_ARROW };
	enum { NONE=0,
	   M_LEFT_ARROW,
	   M_RIGHT_ARROW,
	   CIRCLE};

class game
{
private:
	dxManager * dxMgr;
	directInput * inputMgr;
	sound * soundMgr;
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle
	int now, then, passed, soon;

	
	grid * Grid;
	int gameScreenLength, gameScreenWidth;

	        // Unit test parameters
        IDirect3DSurface9* arrows;
        IDirect3DSurface9* mouseArrow;
        RECT src;
		RECT msrc;
        RECT spriteSrc;
        RECT spriteDest;
        LONG curX;
        LONG curY;
        RECT screen;
	
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance)
	{
		m_hInstance = a_hInstance;
		m_wndHandle = a_wndHandle;
	}
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr)
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
	void setMusic()
	{
		//Load sound (filename, bufferID) in this case the first buffer is 0
		soundMgr->LoadSound("Combat music.wav", 0);
		//SetVolume(bufferID, Volume)
		soundMgr->SetVolume(0, -2000);
		//play sound playSound(bufferID) in this case the first buffer is 0
		soundMgr->playSound(0);
	}
	void SetBMP()
	{
		arrows = dxMgr->getSurfaceFromBitmap("arrows.bmp",192, 48);
		mouseArrow = dxMgr->getSurfaceFromBitmap("mousearrows.bmp",192, 48);
	}
	void update()
	{

		//update time
		now = clock();
		then = now;
		passed = now-then;
		soon = now +100;


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
		if (KEYDOWN(keystate, DIK_LEFT) || KEYDOWN(keystate, DIK_A))
		{
			src.left = (48 * K_LEFT_ARROW);
			if(screen.left>0 && screen.right>48)
			{
				screen.left -=5;
				screen.right -=5;
			}
		}
		if (KEYDOWN(keystate, DIK_RIGHT) || KEYDOWN(keystate, DIK_D))
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

		if (BUTTONDOWN(mouseState, 0))
			msrc.left = (48 * M_LEFT_ARROW);
		if (BUTTONDOWN(mouseState, 1))
			msrc.left = (48 * M_RIGHT_ARROW);
		msrc.right = msrc.left + 48;
		if (BUTTONDOWN(mouseState, 2))
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

	~game()
	{		
		Grid->~grid();
		dxMgr->shutdown();
		inputMgr->shutdownDirectInput();
		soundMgr->shutdownDirectSound();
	};
};