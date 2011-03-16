#pragma once

/* Implementing a single class for now that would take care of most of everything
   for items.  Might update a new class. */

class PlayerItem
{
	private:
		int playerItem;
		int itemType;
		int itemUpdate;
		int itemPickup;
		int itemRandomSpawn;
	public:
		int itemToBeUsed();
		int itemRespawn();
		int generateRandomItemType();
		int usedItem();
		PlayerItem();
		~PlayerItem();
};