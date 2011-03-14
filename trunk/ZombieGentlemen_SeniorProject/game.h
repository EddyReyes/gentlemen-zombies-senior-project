/**
The game class will handle the bulk of the game logic
This class will contian the game states, the map, the players, the characters
etc.

status: unit test
*/
//#define debug

#pragma once
#include "includeFiles.h"

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
	DIMOUSESTATE mouseState;
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle

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
		soundMgr->SetVolume(0, 0);
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

		
		if (KEYDOWN(keystate, DIK_UP) || KEYDOWN(keystate, DIK_W))
		{
			src.left = (48 * K_UP_ARROW);
			if(screen.top>0 && screen.bottom>48)
			{
				screen.top-=5;
				screen.bottom-=5;
			}
		}
		if (KEYDOWN(keystate, DIK_DOWN)|| KEYDOWN(keystate, DIK_S))
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


		// call our render function
		dxMgr->beginRender();



		dxMgr->blitToSurface(mouseArrow, &msrc, NULL);

		//// blit the sprite to the back buffer
		dxMgr->blitToSurface(mouseArrow, &spriteSrc, &spriteDest);

		// blit this letter to the back buffer
		dxMgr->blitToSurface(arrows, &src, &screen);

		dxMgr->endRender();
		
	}

	~game()
	{
		dxMgr->shutdown();
		inputMgr->shutdownDirectInput();
		soundMgr->shutdownDirectSound();
	};
};