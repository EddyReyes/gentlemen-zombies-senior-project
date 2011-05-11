#include "level.h"


level::level()
{
	objMgr = NULL;
	files = NULL;
	m_map = NULL;
	checkpointtxt = NULL;
	camera = NULL;

}
/******************************************************************
* initLevel
* takes in a  text file, and loads all level assets from it
******************************************************************/
void level::initLevel(dxManager* a_dxMgr, dxCamera * a_camera, std::string initFiles)
{
	//puts the files into a string array
	files = new stringArray();
	files->loadFromTextFile(initFiles);

	//initialize the data with it
	m_map = new cubeMap(files->getStringAt(0),files->getStringAt(1),a_dxMgr);

	objMgr = new objectManager();
	objMgr->initObjectMgr(a_dxMgr);
	objMgr->initColMap(files->getStringAt(2), m_map);
	objMgr->initImages(files->getStringAt(3));
	objMgr->loadObjectsFromTxtFile(files->getStringAt(4));
	backGrnd = new background();
	backGrnd->initBackground(a_dxMgr, files->getStringAt(5));
	p1HUD = new HUD();
	p1HUD->loadFromFile(files->getStringAt(6), files->getStringAt(7), a_dxMgr);
	p1HUD->initPositions(files->getStringAt(8));

	camera = a_camera;

	checkpointtxt = new DXText(a_dxMgr,"images/blackTextBox.bmp");
	checkpointtxt->setTextBoxParameters(200,50,600,500,10);
	checkpointtxt->setDialog("CHECKPOINT");
	checkpoint = 20;

	tempPlayer = new player;
	tempPlayer->setObject(objMgr->getObject());

	// initialize FPS display data
	FPSText = new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	FPSText->loadFromTxtFile("textParameters.txt");
	FPSText->setDialog("Loading...");

	physicsData = new DXText(a_dxMgr, "images/BlackTextBox.bmp");
	physicsData->loadFromTxtFile("textParameters2.txt");
	physicsData->setDialog("Loading...");

	Elapsed = 0;
	FPS = 0;
}
/******************************************************************
* update
* takes in the time that has ellapsed since the last update
* and updates the physics with it, as well as checks for collision
* between all objects
******************************************************************/
void level::update(float updateTime)
{
	objMgr->updatePhysics(updateTime);
	objMgr->handleCollision();
	tempPlayer->update(updateTime);
	updateDebugData(updateTime);
	updateCamera();
	//will check if youur at a checkpoint
}

void level::updateCamera()
{
	float cameraY = tempPlayer->getObject()->getPosition()->y;
	float cameraX = tempPlayer->getObject()->getPosition()->x;
	//camera->SetupCamera2D(cameraX, cameraY, -10);
	camera->SetupCamera2D(cameraX, 0, -10);
}
void level::updateDebugData(float updateTime)
{
	// display FPS
	FPS++;
	Elapsed += updateTime;

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
		if(tempPlayer->getObject()->getPhysics())
		{
			sprintf_s(PhysicsBuffer, "Physics x: %f\nPhysics y: %f", 
				tempPlayer->getObject()->getPhysics()->getXVelocity(), 
				tempPlayer->getObject()->getPhysics()->getYVelocity());
		}
		else
		{
			sprintf_s(PhysicsBuffer, "Physics Disabled");
		}
		physicsData->setDialog(PhysicsBuffer);
	}
}
void level::setMusic(char* sound)
{

}
void level::draw()
{
	m_map->draw();
	backGrnd->draw();
	objMgr->draw();
	p1HUD->draw();
	FPSText->draw();
	physicsData->draw();
	//checks if checkpoint was hit draws indication 
	//also checks if the player is way past it to stop drawing indication
	if(hitcheckpoint())
	{
		checkpointtxt->draw();
		//checkpointtxt->~DXText();
	}
}
void level::handleInput(inputData * input, int now)
{
	// down key
	if ((input->keystate[DIK_UP] & 0x80) || (input->keystate[DIK_W] & 0x80))
	{
		if(objMgr->getObject()->getPhysics())
		{
			objMgr->getObject()->getPhysics()->setYVelocity(12.0f);
		}
		else
			objMgr->moveObject(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	}

	// down key
	if ((input->keystate[DIK_DOWN] & 0x80)|| (input->keystate[DIK_S] & 0x80))
	{
		if(!objMgr->getObject()->getPhysics())
			objMgr->moveObject(D3DXVECTOR3(0.0f, -0.05f, 0.0f));
	}
	
	// left key
	if ((input->keystate[DIK_LEFT] & 0x80) || (input->keystate[DIK_A] & 0x80))
	{
		if(objMgr->getObject()->getPhysics())
		{
			if(objMgr->getObject()->getPhysics()->canMoveLeft())
			{
				objMgr->getObject()->getPhysics()->walkingOn();
				objMgr->getObject()->getPhysics()->setXVelocity(-6.0f);
			}
		}
		else
			objMgr->moveObject(D3DXVECTOR3(-0.05f, 0.0f, 0.0f));
	}

	// right key
	if ((input->keystate[DIK_RIGHT] & 0x80) || (input->keystate[DIK_D] & 0x80))
	{
		if(objMgr->getObject()->getPhysics())
		{
			if(objMgr->getObject()->getPhysics()->canMoveRight())
			{
				objMgr->getObject()->getPhysics()->walkingOn();
				objMgr->getObject()->getPhysics()->setXVelocity(6.0f);
			}
		}
		else
			objMgr->moveObject(D3DXVECTOR3(0.05f, 0.0f, 0.0f));
	}

	// if neither left or right key are active
	if (!((input->keystate[DIK_LEFT] & 0x80) || (input->keystate[DIK_A] & 0x80))
		&& !((input->keystate[DIK_RIGHT] & 0x80) || (input->keystate[DIK_D] & 0x80)))
	{
		if(objMgr->getObject()->getPhysics())
		{
			objMgr->getObject()->getPhysics()->walkingOff();
		}
	}

	if ((input->keystate[DIK_B] & 0x80))
	{
		if(now - input->keyLag[DIK_B] > 200)
		{
			objMgr->getObject()->togglePhysics();
			input->keyLag[DIK_B] = now;
		}
	}

	if ((input->keystate[DIK_G] & 0x80))
	{
		if(now - input->keyLag[DIK_G] > 200)
		{
			objMgr->indexPrev();
			input->keyLag[DIK_G] = now;
		}
	}
	if ((input->keystate[DIK_H] & 0x80))
	{
		if(now - input->keyLag[DIK_H] > 200)
		{
			objMgr->indexNext();
			input->keyLag[DIK_H] = now;
		}
	}

	if ((input->keystate[DIK_P] & 0x80))
	{
		if(now - input->keyLag[DIK_P] > 200)
		{
			input->keyLag[DIK_P] = now;
		}
	}


			//if ((input->keystate[DIK_P] & 0x80))
		//{
		//	if(now - input->keyLag[DIK_P] > 200)
		//	{
		//		lvl1->getManager()->pop();
		//		input->keyLag[DIK_P] = now;
		//	}
		//}
		////test key
		//if((input->keystate[DIK_E] & 0x80))
		//{
		//	if(now - input->keyLag[DIK_E] >200)
		//	{
		//		lvl1->~level();
		//		lvl1->initLevel(dxMgr, "testfiles2.txt");
		//	}
		//}




			//// camera movement
		///*if ((keystate[DIK_NUMPAD4] & 0x80) || (keystate[DIK_J] & 0x80))
		//{
		//	if(now - keyLag[DIK_NUMPAD4] > cameraLag)
		//	{
		//		cameraX-= cameraMove;
		//		keyLag[DIK_NUMPAD4] = now;
		//	}
		//}
		//if ((keystate[DIK_NUMPAD6] & 0x80) || (keystate[DIK_L] & 0x80))
		//{
		//	if(now - keyLag[DIK_NUMPAD6] > cameraLag)
		//	{
		//		cameraX += cameraMove;
		//		keyLag[DIK_NUMPAD6] = now;
		//	}
		//}
		//if ((keystate[DIK_NUMPAD2] & 0x80) || (keystate[DIK_K] & 0x80))
		//{
		//	if(now - keyLag[DIK_NUMPAD2] > cameraLag)
		//	{
		//		cameraY -= cameraMove;
		//		keyLag[DIK_NUMPAD2] = now;
		//	}
		//}
		//if ((keystate[DIK_NUMPAD8] & 0x80) || (keystate[DIK_I] & 0x80))
		//{
		//	if(now - keyLag[DIK_NUMPAD8] > cameraLag)
		//	{
		//		cameraY+= cameraMove;
		//		keyLag[DIK_NUMPAD8] = now;
		//	}
		//}*/
		//
		//if ((input->keystate[DIK_NUMPAD7] & 0x80) || (input->keystate[DIK_U] & 0x80))
		//{
		//	if(now - input->keyLag[DIK_NUMPAD7] > cameraLag)
		//	{
		//		if(cameraZ < -1.1)
		//		{
		//			cameraZ += cameraMove;
		//			input->keyLag[DIK_NUMPAD7] = now;
		//		}
		//	}
		//}
		//if ((input->keystate[DIK_NUMPAD9] & 0x80) || (input->keystate[DIK_O] & 0x80))
		//{
		//	if(now - input->keyLag[DIK_NUMPAD9] > cameraLag)
		//	{
		//		cameraZ -= cameraMove;
		//		input->keyLag[DIK_NUMPAD9] = now;
		//	}
		//}
}

void level::moveObject(D3DXVECTOR3 go)
{
	objMgr->moveObject(go);
}
bool level::hitcheckpoint()
{
	if(objMgr->getObject()->getPosition()->x >= checkpoint && 
		objMgr->getObject()->getPosition()->x < checkpoint + 2)
	{
		std::ofstream file("checkpoint.txt");
		file<<objMgr->getObject()->getPosition()->x<<'\n';
		file<<objMgr->getObject()->getPosition()->y<<'\n';
		return true;
	}
	else
		return false;
}
void level::loadfromcheckpoint(std::string a_file)
{
	std::fstream temp;

	temp.open(a_file.c_str(),std::fstream::out||std::fstream::app);
	float x,y;
	temp>>x;
	temp>>y;
	objMgr->getObject()->setPosition(x,y,0.0f);
}
level::~level()
{
	FPSText->~DXText();
	physicsData->~DXText();
	m_map->~cubeMap();
	objMgr->~objectManager();
	files->~stringArray();
	checkpointtxt->~DXText();
}