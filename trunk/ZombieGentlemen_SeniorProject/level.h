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

struct cameraUpdateData
{
	D3DXVECTOR3 point;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 displacement;
	D3DXVECTOR3 * playerData;
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


	float Elapsed;
	int FPS;
	// debug data
	DXText * FPSText;
	DXText * physicsData; 

public:
	level();
	void initLevel(dxManager* a_dxMgr, dxCamera * a_camera, std::string filename);
	void setMusic(char*);//sets the music for the level
	void draw();
	void handleInput(inputData * input, int now);
	void update(float timePassed);
	void updateCamera(float updateTime);
	void updateDebugData(float updateTime);
	~level();//deconstructor
	void loadfromcheckpoint(std::string);
	objectManager* getManager(){return objMgr;}
};