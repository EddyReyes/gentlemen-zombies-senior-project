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

#include "object.h"
#include "grid.h"
#include "physicsObject.h"

#include "map.h"
#include "entity.h"

#include "playerCharacter.h"
#include "playerItem.h"
#include "weapon.h"
#include "helmet.h"
#include "armor.h"

#pragma once

// for unit testing
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

	// grid and parameters
	grid * Grid;
	int gameScreenLength, gameScreenWidth;

	// Unit test parameters
	IDirect3DSurface9* arrows;
	IDirect3DSurface9* mouseArrow;
	IDirect3DSurface9* line;
	RECT lineRect;
	RECT lineRectScreen;
	RECT src;
	RECT msrc;
	RECT spriteSrc;
	RECT spriteDest;
	LONG curX;
	LONG curY;
	RECT screen;
	
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void setMusic();
	void SetBMP();
	void update();
	void handleInput();
	void draw();
	~game();
};