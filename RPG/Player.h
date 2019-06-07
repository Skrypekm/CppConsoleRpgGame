#pragma once
#include <string>
#include <vector>

class Player
{
	private:
		int XPtoNextLevel = 100;
	public:
		std::string name = "null";
		std::string characterClass = "null";
		int Health = 10;
		int Armor = 1;
		int Attack = 1;
		int gold = 0;
		int XP = 0;
		std::vector<std::pair<int, std::string>> inventory;
		
		void setname(std::string newName);
		void setClass(std::string newClass);
		void levelUp();
};

inline void Player::setname(std::string newName)
{
	name = newName;
}

inline void Player::setClass(std::string newClass)
{
	characterClass = newClass;
}

inline void Player::levelUp()
{
	
}