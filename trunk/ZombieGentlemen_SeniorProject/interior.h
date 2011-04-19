#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "playerCharacter.h"
#include "armor.h"
#include "weapon.h"
#include "playerItem.h"


class interior
{

private:
DXText * playerMoney;
dxManager * dxMgr;
PlayerCharacter * player;
DXText * playerIDNumber;
Armor * armor;
Weapon * weapon;
PlayerItem * item;

public:
interior();
interior(dxManager * a_dxMgr);
~interior();
void interiorDraw();
void setInteriorBackground(std::string filename);
void setInteriorForeground(std::string filename);
void dialogueBox(std::string filename);
void updateMenu(std::string filename);
void questDialogue(std::string filename);
void setPlayer(PlayerCharacter * a_player);
};