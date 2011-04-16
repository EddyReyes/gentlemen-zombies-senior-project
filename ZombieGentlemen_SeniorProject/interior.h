#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "playerCharacter.h"


class interior
{

private:
DXText * playerMoney;
dxManager * dxMgr;



public:
interior();
interior(dxManager * a_dxMgr);
~interior();
void interiorDraw();
void interiorBackground();
void interiorForeground();
void dialogueBox();
void updateMenu();
};