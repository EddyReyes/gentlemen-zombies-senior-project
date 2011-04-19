#pragma once
#include "imageManager.h"
//#include "interior.h"
#include "playerItem.h"
#include "playerCharacter.h"



class Quest
{
	private:
		DXText * playerMoney;
		dxManager * dxMgr;
		PlayerCharacter * player;
		DXText *playerIDNumber;

	public:
		Quest();
		Quest(dxManager * a_dxMgr, std::string filename);
		~Quest();
		void loadQuest(std::string filename);
};