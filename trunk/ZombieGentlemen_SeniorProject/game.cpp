#include "game.h"

game::game(HWND * a_wndHandle, HINSTANCE * a_hInstance)
{
	m_hInstance = a_hInstance;
	m_wndHandle = a_wndHandle;
}
bool game::initGame(dxManager * a_dxMgr, directInput * a_inputMgr, sound * a_soundMgr)
{
	// initiallize game data
	dxMgr = a_dxMgr;
	inputMgr = a_inputMgr;
	soundMgr = a_soundMgr;
	
	// game states
	gameState = menu;

	//instantiate menu
	mainMenu = new Menu(dxMgr,"MenuArt.txt","options.txt");
	mainMenu->setParam(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH/4,WINDOW_HEIGHT/4);

	// initialize timer data
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceFrequency(&timerFreq);
	Elapsed  = 0;
	FPS = 0;

	// initialize FPS display data
	FPSText = new DXText(dxMgr, "images/BlackTextBox.bmp");
	FPSText->loadFromTxtFile("textParameters.txt");
	FPSText->setDialog("Loading...");

	physicsData = new DXText(dxMgr, "images/BlackTextBox.bmp");
	physicsData->loadFromTxtFile("textParameters2.txt");
	physicsData->setDialog("Loading...");

	input = new inputData;
	input->init();

	camera = new dxCamera(dxMgr);
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = -10.0f;

	a_soundMgr->initSoundFiles("soundManager.txt");
	lvl1 = new level();
	lvl1->initLevel(dxMgr, camera , "testfiles.txt");
	a_soundMgr->initSoundFiles("soundManager.txt");

	the_town = new town();
	the_town->init(dxMgr);
	setMusic();
	return true;
}
void game::setMusic()
{
	soundMgr->SetVolume(0, -2000);
}
void game::update()
{
	//update time
	now = clock();
	then = now;
	passed = now-then;
	soon = now +100;

	QueryPerformanceCounter(&timeStart);
	
	// Handle Input using Direct Input
	handleInput();
	// handle collision & update physics
	lvl1->update(UpdateSpeed);
	if(lvl1->getobject())
	{
		//float ycoord = lvl1->getobject()->getPosition()->y;
		float xcoord = lvl1->getobject()->getPosition()->x;
		cameraX = xcoord;
		//cameraY = ycoord;
	}

	// draw to the screen using Direct3D
	draw();

	// update high resolution timer
	QueryPerformanceCounter(&timeEnd);
	UpdateSpeed = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;

	updateDebugData();
}
void game::updateDebugData()
{
	// display FPS
	FPS++;
	Elapsed += UpdateSpeed;

	if(Elapsed >= 1)
	{
		char UpdateBuffer[256];
		sprintf_s(UpdateBuffer, "FPS: %i", FPS);
		FPSText->setDialog(UpdateBuffer);
		Elapsed = 0;
		FPS = 0;
	}

	// display phsics
	if(Elapsed >= 0.0)
	{
		char PhysicsBuffer[256];
		if(lvl1->getobject()->getPhysics())
		{
			sprintf_s(PhysicsBuffer, "Physics x: %f\nPhysics y: %f", 
				lvl1->getobject()->getPhysics()->getXVelocity(), 
				lvl1->getobject()->getPhysics()->getYVelocity());
		}
		else
		{
			sprintf_s(PhysicsBuffer, "Physics Disabled");
		}
		physicsData->setDialog(PhysicsBuffer);
	}
}
void game::handleInput()
{
	inputMgr->reAcquireDevices();
	inputMgr->updateKeyboardState(); 
	input->keystate = inputMgr->getKeyboardState();
	inputMgr->updateMouseState();
	input->mouseState = *(inputMgr->getMouseState());

	// keyboard
	//mainMenu->update(keystate,now,keyLag);

	if(input->keystate[DIK_ESCAPE] & 0x80)
	{
		PostQuitMessage(0);
	}

	int check = 0;

	switch(gameState)
	{
	case menu:
		soundMgr->SetVolume(1, -2000);
		soundMgr->playSound(1);

		check = mainMenu->update(input->keystate,now,input->keyLag);
		if(check == 1)
		{
			mainMenu->~Menu();
			gameState = sideScroll;

			soundMgr->stopSound(1);
			soundMgr->playSound(0);
		}
		if(check == 2)
		{
			fstream file("checkpoint.txt",fstream::in||fstream::app);
			if(file.good())
			{
				mainMenu->~Menu();
				gameState = sideScroll;
				lvl1->loadfromcheckpoint("checkpoint.txt");

				soundMgr->stopSound(1);
				soundMgr->playSound(0);
			}
		}
		if(check == 3)
		{
			PostQuitMessage(0);
		}
		
		break;

	case sideScroll:
		// when game is in level state, input is handled inside level
		lvl1->handleInput(input, now);
		break;
	}
}

void game::draw()
{
	dxMgr->beginRender();

	camera->SetupCamera2D(cameraX, cameraY, cameraZ);
	//camera->updateCamera3D(D3DXVECTOR3(cameraX, cameraY, cameraZ), D3DXVECTOR3(0, 0, 0)); 

	switch(gameState)
	{
	case menu:
		mainMenu->Draw();
		break;
	case topDown:
		the_town->draw();
		break;
	case sideScroll:
		lvl1->draw();
		FPSText->draw();
		physicsData->draw();
		break;
	}
	//camera->SetHudCamera();
	dxMgr->endRender();
}
game::~game()
{	
	physicsData->~DXText();
	FPSText->~DXText();
	lvl1->~level();	
	the_town->~town();

	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->~sound();
}