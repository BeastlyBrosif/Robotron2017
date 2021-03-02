#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include "../factory/EnemyFactory.h"
#include "../factory/PlayerFactory.h"
#include "../Config.h"

struct enemyList
{
	int type;
	int x, y;
};

class GameLevel
{
public:
	GameLevel(std::string levelfile);
	~GameLevel();

	std::string getLevelName() { return m_levelName; };

	void readFile();
	void addEnemyToList(int _type, int _xPos, int _yPos);
	void setPlayerPos(int _xPos, int _yPos) { playerX = _xPos; playerY = _yPos; }
	void freeList();

	bool isLevelComplete() { return m_completed; }
	bool isLevelActive() { return m_active; }

	bool setActiveState(bool _active) { m_active = _active; }
	bool setCompletedState(bool _compl) { m_completed = _compl; }
private:
	int playerX;
	int playerY;

	bool m_active; //this flag marks whether this level is active
	bool m_completed; //this marks whether the level is completed
	unsigned int m_levelScore; //the score for this level

	std::string m_levelName;
	std::string m_filename;
	std::vector<enemyList*> m_enemyList;

	int getEnemyType(std::string);
	
};

#endif