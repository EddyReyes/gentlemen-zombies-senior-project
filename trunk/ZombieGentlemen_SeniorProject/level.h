#pragma once
#include "dxManager.h"
#include "objectManager.h"
#include "inputData.h"
#include "directInput.h"
#include "physics.h"
#include "stringArray.h"
#include "background.h"
#include "dxCamera.h"
#include "HUD.h"
#include "entityManager.h"

#include "math.h"

struct cameraUpdateData
{
	D3DXVECTOR3 point;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 displacement;
	D3DXVECTOR3 * playerData;
};

enum levelState{levelLoading, levelPaused, levelPlay, levelWin};

struct levelStats
{
	float timer;
	int numDeaths;

	levelStats()
	{
		timer = 0;
		numDeaths = 0;
	}
};

class level
{
private:
	objectManager * objMgr;
	stringArray * files;
	cubeMap * m_map;
	background * backGrnd;
	HUD * p1HUD;
	DXText* checkpointtxt;
	dxCamera * camera;
	int checkpoint;
	entityManager * entityMgr;
	player * m_player;
	float timer;
	cameraUpdateData camData;

	levelState state;

	HudImage * pauseScreen;
	HudImage * winScreen;

	levelStats stats;
	float Elapsed;
	int FPS;
	// debug data
	DXText * FPSText;
	DXText * controllerDebug; 
	DXText * statsDisplay;

public:
	level();
	void initLevel(dxManager* a_dxMgr, dxCamera * a_camera, std::string filename);
	void setMusic(char*);//sets the music for the level
	void draw();
	void handleInput(inputData * input, int now);
	bool update(float timePassed);
	void updateCamera(float updateTime);
	void updateDebugData(float updateTime);
	~level();//deconstructor
	void loadfromcheckpoint(std::string);
	objectManager* getManager(){return objMgr;}
	int getState();
};