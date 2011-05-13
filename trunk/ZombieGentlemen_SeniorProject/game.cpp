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
	
	// set game initial state
	gameState = menu;

	// initialize timer data
	now = clock();
	//then = now;
	//passed = now-then;

	QueryPerformanceFrequency(&timerFreq);
	UpdateSpeed = 0;

	// initialize input data
	input = new inputData;
	input->init();

	// initiailize camera
	camera = new dxCamera(dxMgr);
	
	//instantiate menu (TEST DATA)
	mainMenu = new Menu(dxMgr,"MenuArt.txt","options.txt");
	mainMenu->setParam(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH/4,WINDOW_HEIGHT/4);

	// initialize town (TEST DATA)
	the_town = new town();
	the_town->init(dxMgr,"anotherInit.txt","coords.txt");

	// initialize sound data (TEST DATA)
	a_soundMgr->initSoundFiles("soundManager.txt");
	lvl1 = new level();
	lvl1->initLevel(dxMgr, camera , "testfiles.txt");
	a_soundMgr->initSoundFiles("soundManager.txt");

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
	QueryPerformanceCounter(&timeStart);
	
	// Handle Input using Direct Input
	handleInput();
	// update according to game state
	switch(gameState)
	{
	case menu:
		// nothing here yet
		break;
	case sideScroll:
			lvl1->update(UpdateSpeed);
		break;
	case topDown:
		// nothing here yet
		break;
	case pause: 
		// nothing here yet
		break;
	}

	// draw to the screen using Direct3D
	draw();

	// update high resolution timer
	QueryPerformanceCounter(&timeEnd);
	UpdateSpeed = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart)/
		timerFreq.QuadPart;
}

void game::handleInput()
{
	inputMgr->reAcquireDevices();
	inputMgr->updateKeyboardState(); 
	input->keystate = inputMgr->getKeyboardState();
	inputMgr->updateMouseState();
	input->mouseState = *(inputMgr->getMouseState());

	// if esc is pressed Quit Game globally
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
			//gameState = topDown;
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
	case topDown:
		{
			if(the_town->update(input,now)== 0)
				gameState = sideScroll;
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
		break;
	}
	dxMgr->endRender();
}
game::~game()
{	
	lvl1->~level();	
	the_town->~town();
	dxMgr->shutdown();
	inputMgr->shutdownDirectInput();
	soundMgr->~sound();
}