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
#include "HUD.h"
#include "town.h"
#include "level.h"
#include "town.h"
#include "entity.h"
#include "ziggy.h"
#include <stdio.h>

//#define topdown
enum gameStates{menu, sideScroll, topDown, pause};

class game
{
private:
	// main game components
	HINSTANCE * m_hInstance; //pointer to global handle to hold the application instance
	HWND * m_wndHandle; //pointer to global variable to hold the window handle
	dxManager * dxMgr;
	directInput * inputMgr;
	sound * soundMgr;
	gameStates gameState;
	
	// input data
	inputData * input;

	// timer data
	int now, then, passed, soon; // low resolution timers for keylag
	LARGE_INTEGER timeStart, timeEnd, timerFreq; // high resolution timers for animation
	float UpdateSpeed;

	// camera data
	dxCamera * camera;

	// Unit test parameters	
	Menu* mainMenu;
	level* lvl1;
	town * the_town;
			
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void setMusic();
	void update();
	void handleGamState();
	void handleInput();
	void draw();
	~game();
};