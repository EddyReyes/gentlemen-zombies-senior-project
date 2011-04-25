#include "Menu.h"

/*											*\
*											*
*This will house the Menu State code.	*
\*											*/


Menu::Menu()
{
	selected = 0;
}
Menu::Menu(dxManager * a_dxMgr)
{
	selected = 0;
	imgMan = new imageManager();
	imgMan->initImageManager("menuItems.txt",a_dxMgr);
	background = new HudImage(a_dxMgr,imgMan->getImage(0),imgMan->getImageInfo(0));
	//background->setRowsColumns(1,1);
	background->setParameters(300,300,150,150);
	//options = new DXText(a_dxMgr,imgMan->getImage(1),imgMan->getImageInfo(1));
	
	/*
	dxMgr = a_dxMgr;
	playerIDNumber = NULL;
	playerMoney = NULL;
	armor = new Armor();
	weapon = new Weapon();
	item = new PlayerItem();
	player = new PlayerCharacter();
	//dxManager * dxMgr;*/
}

void Menu::Draw()
{
	background->draw();
//	options->draw();
}

void Menu::dialogueBox(std::string filename)
{

}

void Menu::questDialogue(std::string filename)
{

}

void Menu::setPlayer(PlayerCharacter *a_player)
{
	//player = a_player;
}

void Menu::storeMenu(std::string filename)
{

}
Menu::~Menu()
{
	imgMan->~imageManager();

}