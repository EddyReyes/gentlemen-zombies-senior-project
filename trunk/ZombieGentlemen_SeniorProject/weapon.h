#pragma once

class weapon
{
	private:
		int damage;
		int weaponSpeed;
		
	public:
		weapon();
		~weapon();

		// muutotors
		void setDamage();
		void setSpeed();

		// accessors
		void getDamage();
		void getSpeed();
};