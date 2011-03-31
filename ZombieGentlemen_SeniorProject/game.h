/**
The game class will handle the bulk of the game logic
This class will contian the game states, the map, the players, the characters
etc.


status: unit test
*/

// DirectX files
#include "dxManager.h"
#include "directInput.h"
#include "sound.h"
#include <time.h>
#include "dxCamera.h"
#include "rectangle.h"
#include "HudImage.h"
#include "XYPlane.h"


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
#include "dialogue.h"

#pragma once

class game
{
private:
	dxManager * dxMgr;
	directInput * inputMgr;
	sound * soundMgr;
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;
	float curX; // mouse X position
	float curY; // moust Y position
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle
	int now, then, passed, soon; // low resolution timers for keylag
	LARGE_INTEGER timeStart, timeEnd, timerFreq; // high resolution timers for animation
	float animationRate;

	// grid
	grid * Grid;

	// Unit test parameters
	
	XY position;
	HudImage * dialog;
	HudImage * arrowSprite;
	HudImage * cursor;
	HudImage * background;
	XYPlane * testTile;
	XYPlane * testTile2;
	XYPlane * testTile3;
	float scale;
	dxCamera * camera;
	float cameraX, cameraY, cameraZ;

	
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void setMusic();
	void SetSprites();
	void update();
	void handleInput();
	void draw();
	~game();
};