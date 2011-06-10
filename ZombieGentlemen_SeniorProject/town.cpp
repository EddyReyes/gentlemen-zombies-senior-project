#include "town.h"

town::town()
{
	map = NULL;
	m_object = NULL;
	camera = NULL;
	buildings = NULL;
}
town::~town()
{
	// destroy map
	if(map)
	{
	delete map;
	map = NULL;
	}

	// destroy cursor
	if(m_object)
	{
		delete m_object;
		m_object = NULL;
	}

	// destroy buildings
	if(buildings)
	{
		buildings->~XYPlane();
		buildings = NULL;
	}
}
void town::init(dxManager * a_dxMgr, dxCamera * a_camera,char * file, char* file2)
{
	stringArray temp;
	temp.loadFromTextFile(file);

	std::fstream initfiles;
	initfiles.open(file2,std::fstream::app|std::fstream::in|std::fstream::out);

	camera  = a_camera; // camera is borrowed from game class

	map = new XYPlane();
	map->init(a_dxMgr,"images/top_down2.bmp");
	map->setParam(D3DXVECTOR3(-10.38f,10.4f,0.0f),20.72,21.2);

	m_object = new XYPlane();
	m_object->init(a_dxMgr,temp.getStringAt(0));
	if(initfiles.good())
	{
		buildings = new XYPlane[9];
		float x,y,z;
		for(int b=0;b<max_positions;++b)
		{
			initfiles>>x>>y>>z;
			buildings[b].init(a_dxMgr,temp.getStringAt(0));
			buildings[b].setPosition(x,y,z);
		}
		m_object->setPosition(*buildings[0].getPosition());
		initfiles.close();
	}
}
int town::update(inputData * input,int now)
{
	static int r=0;
	if((input->keystate[DIK_A] & 0x80)||(input->keystate[DIK_LEFT] & 0x80))
	{
		if(now - input->keyLag[DIK_LEFT] > 150)
		{
			input->keyLag[DIK_LEFT] = now;
			if(r!=0)
			{
				r--;
				m_object->setPosition(*buildings[r].getPosition());
			}
		}
	}
	if(input->keystate[DIK_D] & 0x80||input->keystate[DIK_RIGHT] & 0x80)
	{
		if(now - input->keyLag[DIK_D] > 150)
		{
			input->keyLag[DIK_D] = now;
			if(r!= max_positions-1)
			{
				r++;
				m_object->setPosition(*buildings[r].getPosition());
			}
		}

	}
	
	if(input->keystate[DIK_RETURN] & 0x80)
	{
		if(now - input->keyLag[DIK_RETURN] > 150)
		{
			input->keyLag[DIK_RETURN] = now;
			return r;
		}
	}
	return -1;
}
void town::draw()
{
	camera->SetupCamera2D(0.0f,0.0f,-25.0f);
	map->draw();
	m_object->draw();
	//for(int p=0;p<5;++p)
	//{
		//buildings[p].draw();
	//}
}