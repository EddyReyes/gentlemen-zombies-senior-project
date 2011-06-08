#pragma once
#include "defines.h"

//#define topdown
enum gameStates{menu, sideScroll, topDown, loading};

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
	int now; // low resolution timer for keylag
	LARGE_INTEGER timeStart, timeEnd, timerFreq; // high resolution timers for animation
	float UpdateSpeed;

	// camera data
	dxCamera * camera;

	// Unit test parameters	
	Menu * mainMenu;

	DXText * loadingScreen;
	DXText * controllerDebug;
	levelManager * lvlMgr;
	level * lvl;
	town * the_town;
			
public: 
	game(HWND * a_wndHandle, HINSTANCE * a_hInstance);
	bool initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr);
	void update();
	void handleGamState();
	void handleInput();
	void draw();
	~game();
};