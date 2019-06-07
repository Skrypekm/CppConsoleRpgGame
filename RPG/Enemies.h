#pragma once
#include <string>

class EnemyTemplate
{
public:
	std::string name;
	int health;
	int armor;
	int attack;
	int xpOnDeath;
	int goldOnDeath;
};

class BasicEnemy : public EnemyTemplate
{
public:
	BasicEnemy();
};

inline BasicEnemy::BasicEnemy()
{
	name = "Sample Enemy";
	health = 3;
	armor = 0;
	attack = 1;
	xpOnDeath = 10;
	goldOnDeath = 10;
}