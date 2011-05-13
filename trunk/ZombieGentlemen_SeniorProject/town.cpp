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
	if(map)
	map->~XYPlane();
	if(m_object)
	m_object->~XYPlane();
	if(camera)
	camera->~dxCamera();
	//if(initfiles)
		//initfiles->~stringArray();
	buildings->~XYPlane();
}
void town::init(dxManager * a_dxMgr,char * file, char* file2)
{
	stringArray temp;
	temp.loadFromTextFile(file);

	std::fstream initfiles;
	initfiles.open(file2,std::fstream::app|std::fstream::in|std::fstream::out);

	camera = new dxCamera(a_dxMgr);

	map = new XYPlane();
	map->init(a_dxMgr,"images/top_down1.bmp");
	map->setParam(D3DXVECTOR3(-10.0f,10.0f,0.0f),20,20);

	m_object = new XYPlane();
	m_object->init(a_dxMgr,temp.getStringAt(0));
	if(initfiles.good())
	{
		buildings = new XYPlane[5];
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
	//D3DXVECTOR3 temp(m_object->getPosition()->x,m_object->getPosition()->y,0.0f);
	if(input->keystate[DIK_A] & 0x80||input->keystate[DIK_LEFT])
	{
		if(now - input->keyLag[DIK_A] > 200||now - input->keyLag[DIK_LEFT] > 200)
		{
			for(int r=0;r<max_positions;++r)
				if(*m_object->getPosition() == *buildings[r].getPosition())
				{
					if(r!=0)
						m_object->setPosition(*buildings[r-1].getPosition());
				}
		}
	}
	if(input->keystate[DIK_D] & 0x80||input->keystate[DIK_RIGHT])
	{
		if(now - input->keyLag[DIK_D] > 200||now - input->keyLag[DIK_RIGHT] > 200)
		{
			for(int r=0;r<max_positions;++r)
			{
				if(*m_object->getPosition() == *buildings[r].getPosition())
				{
					if(r!=max_positions-1)
						m_object->setPosition(*buildings[r+1].getPosition());
				}
			}
		}
	}
	//if(input->keystate[DIK_RETURN])
	//{
	//	if(now - input->keyLag[DIK_RETURN] > 200)
	//	{
	//		if(temp == m_points[0])
	//			return 0;
	//		if(temp == m_points[1])
	//			return 1;
	//		if(temp == m_points[2])
	//			return 2;
	//		if(temp == m_points[3])
	//			return 3;
	//	}
	//}
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