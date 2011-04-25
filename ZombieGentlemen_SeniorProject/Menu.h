#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "playerCharacter.h"
#include "armor.h"
#include "weapon.h"
#include "playerItem.h"
#include "quest.h"

#define num_of_options 2

/*the menu class will be responsible for the title screen
as well as the in game stores*/
class Menu
{
	private:
		int selected;
		imageManager* imgMan;
		//DXText * options;		
		HudImage * background;
		/*
		DXText * playerMoney;
		PlayerCharacter * player;
		DXText * playerIDNumber;
		Armor * armor;
		Weapon * weapon;
		PlayerItem * item;
		Quest * quest;
		*/
	public:
		Menu();
		Menu(dxManager * a_dxMgr);
		~Menu();
		void Draw();
		void dialogueBox(std::string filename);
		void updateMenu(std::string filename);
		void questDialogue(std::string filename);
		void setPlayer(PlayerCharacter * a_player);
		void storeMenu(std::string filename);
};