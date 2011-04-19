#include "interior.h"

/*											*\
*											*
*This will house the Interior State code.	*
\*											*/


interior::interior(){}
interior::interior(dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	playerIDNumber = NULL;
	playerMoney = NULL;
	armor = new Armor();
	weapon = new Weapon();
	item = new PlayerItem();
	player = new PlayerCharacter();
	//dxManager * dxMgr;
}

void interior::interiorDraw()
{

}

void interior::dialogueBox(std::string filename)
{

}

void interior::setInteriorBackground(std::string filename)
{

}

void interior::setInteriorForeground(std::string filename)
{

}

void interior::questDialogue(std::string filename)
{

}
void interior::setPlayer(PlayerCharacter *a_player)
{
	player = a_player;
}