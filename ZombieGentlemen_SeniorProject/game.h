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
#include "collisionRect.h"
#include "HudImage.h"
#include "XYPlane.h"
#include "dxCube.h"
#include "DXText.h"

#include "object.h"
#include "physicsObject.h"

#include "cubeMap.h"
#include "planeMap.h"
#include "entity.h"

#include "playerCharacter.h"
#include "playerItem.h"
#include "EnemyCharacter.h"
#include "weapon.h"
#include "helmet.h"
#include "armor.h"

#include <stdio.h>


#pragma once

class game
{
private:
	dxManager * dxMgr;
	directInput * inputMgr;
	sound * soundMgr;
	BYTE * keystate;
	int * keyLag;
	PlayerCharacter * player;
	EnemyCharacter * enemy;
	DIMOUSESTATE mouseState;
	float curX; // mouse X position
	float curY; // moust Y position
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle
	int now, then, passed, soon; // low resolution timers for keylag
	LARGE_INTEGER timeStart, timeEnd, timerFreq; // high resolution timers for animation
	float UpdateSpeed, Elapsed;
	int FPS;
	DXText  * FPSText;

	// Unit test parameters

	cubeMap * m_map;
	planeMap * XYMap;
	
	XY position;
	DXText * dialog;
	HudImage * cursor;
	HudImage * background;
	XYPlane * testTile;
	float scale;
	dxCamera * camera;
	float cameraX, cameraY, cameraZ;
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void setMusic();
	void SetSprites();
	void update();
	void UpdateFPS();
	void handleInput();
	void draw();

	~game();
};