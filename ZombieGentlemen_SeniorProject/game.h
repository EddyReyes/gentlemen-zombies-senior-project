#pragma once
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
#include "objectManager.h"
#include "objectVector.h"
#include "collisionMap.h"
#include "physics.h"

#include "cubeMap.h"
#include "planeMap.h"
#include "entity.h"
#include "collisionMap.h"

#include "Menu.h"
#include "defines.h"

#include "HUD.h"
#include "playerCharacter.h"
#include "EnemyCharacter.h"
#include "weapon.h"
#include "armor.h"
#include "level.h"

#include <stdio.h>

//#define testEnvironment

#ifdef testEnvironment

class game
{
private:
	dxManager * dxMgr;
	directInput * inputMgr;
	sound * soundMgr;
	BYTE * keystate;
	int * keyLag;
	DXText * dialog;
	HUD * hudStuff;
	HudImage * cursor;
	HudImage * background;
	PlayerCharacter * player;
	EnemyCharacter * enemy;
	level* lvl;
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
	D3DXVECTOR3 postion;
		
	// camera data
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
#endif 

#ifndef testEnvironment

class game
{
private:
	// main game components
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle
	dxManager * dxMgr;
	directInput * inputMgr;
	// input data
	sound * soundMgr;
	BYTE * keystate;
	int * keyLag;
	DIMOUSESTATE mouseState;
	Menu* mainMenu;
	int m_currentgamestate; //keeps track of which state the game is in
	
	// timer data
	int now, then, passed, soon; // low resolution timers for keylag
	LARGE_INTEGER timeStart, timeEnd, timerFreq; // high resolution timers for animation
	float UpdateSpeed, Elapsed;
	int FPS;

	// FPS display data
	DXText * FPSText;
	DXText * physicsData; 
	//DXText * objstate; 

	// camera data
	dxCamera * camera;
	float cameraX, cameraY, cameraZ;

	// Unit test parameters
	int m_charstate;	//keeps track of what state the player is in
	float objectX, objectY;
	level* lvl1;
			
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void setMusic();
	void update();
	void handleGamState();
	void updateDebugData();
	void handleInput();
	void draw();
	~game();
};

#endif