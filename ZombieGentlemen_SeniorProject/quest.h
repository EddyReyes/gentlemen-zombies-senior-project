#include "imageManager.h"
#include "interior.h"
#include "playerItem.h"
#include "playerCharacter.h"

#pragma once

class Quest
{
private:

DXText * playerMoney;
dxManager * dxMgr;
playerCharacter * player;
DXText *playerIDNumber;


public:
quest();
quest(dxManager * a_dxMgr, std::string filename);
~quest();
void loadQuest(std::string filename);

}