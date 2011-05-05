#pragma once
#include "dxManager.h"
#include "directInput.h"
#include "inputData.h"
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
#include "Player.h"
#include "EnemyCharacter.h"
#include "weapon.h"
#include "armor.h"
#include "level.h"

#include <stdio.h>

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
	inputData * input;
	Menu* mainMenu;
	int m_currentgamestate; //keeps track of which state the game is in
	Player * player;
	
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
	int m_charstate;	//keeps track of what state the Player is in
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