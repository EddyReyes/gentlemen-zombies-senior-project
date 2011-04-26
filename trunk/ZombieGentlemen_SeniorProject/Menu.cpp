#include "Menu.h"

/*											*\
*											*
*This will house the Menu State code.	*
\*											*/


Menu::Menu()
{
	selected = 0;
	imgMan = NULL;
	background = NULL;
	option_txt = NULL;
	options = NULL;
}
Menu::Menu(dxManager * a_dxMgr)
{
	selected = 0;
	imgMan = new imageManager();
	imgMan->initImageManager("menuItems.txt",a_dxMgr);
	background = new HudImage(a_dxMgr,imgMan->getImage(0),imgMan->getImageInfo(0));

	option_txt = new stringArray;
	option_txt->loadFromTextFile("Scatta.txt");

	options = new DXText* [option_txt->getSize()];
	for(int c=0;c<num_of_options;++c)
	{
		options[c] = new DXText(a_dxMgr,imgMan->getImage(1),imgMan->getImageInfo(1));
		//options[c]->setDialog(option_txt->getStringAt(c));
	}
	setParam(300,300,150,150);
}

void Menu::Draw()
{
	background->draw();
	for(int a=0;a<num_of_options;++a)
		options[a]->draw();
}

void Menu::dialogueBox()
{

}
void Menu::setParam(float w, float h, float a_x, float a_y)
{
	background->setParameters(w,h,a_x,a_y);
	for(int q=0;q<num_of_options;++q)
	{
		options[q]->setTextBoxParameters(w,h,a_x,a_y+(q*100),0);
		options[q]->textInfo("Arial", 18,
					 D3DCOLOR_ARGB(255, 0, 0, 0),
					 option_txt->getStringAt(q));
	}
}
void Menu::questDialogue(std::string filename)
{

}
void Menu::storeMenu(std::string filename)
{

}
void Menu::update(BYTE* keystate,int now,int * keylag)
{
	if(keystate[DIK_T] & 0x80)
	{
		if(now - keylag[DIK_T] > 150)
		{
			if (selected == 0) 
			{
				options[0]->getimg()->shareImage(imgMan->getImage(2),imgMan->getImageInfo(2));
				selected = 1;
			}
			else if(selected == 1)
			{
				options[0]->getimg()->shareImage(imgMan->getImage(1),imgMan->getImageInfo(1));
				options[1]->getimg()->shareImage(imgMan->getImage(2),imgMan->getImageInfo(2));
				selected = 2;
			}
			else
			{
				options[1]->getimg()->shareImage(imgMan->getImage(1),imgMan->getImageInfo(1));
				selected =0;
			}
			keylag[DIK_T] = now;
		}
	}
}
Menu::~Menu()
{
	imgMan->~imageManager();

}