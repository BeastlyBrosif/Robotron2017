//Class - Level Factory
//This class is responsible for creating levels

#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include <iostream>

#include "../factory/Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Bullet.h"
#include "../entities/Enemy.h"

#include "../level/GameLevel.h"

class LevelFactory : public Factory
{
public:
	LevelFactory() : Factory() //the constructor, it uses the factory constructor plus whatever is stated below
	{
		m_currentlevel = 0;
		m_numberoflevels = 42; //not necessary to have the exact value at the moment
		loadLevels();
	}
	~LevelFactory();
	void loadLevels(); //This will load the levels from the files in the 'res' folder into the vector variable 'levelList' ./res/levels/level1.txt etc...
	void addLevel(std::string _levelfile);
	void update(); //this will check if the current level is finished and if it is, it will load the next level

	void clearLevels();
private:
	int m_currentlevel;
	int m_numberoflevels;
	std::vector<GameLevel*> m_levelList;
};



#endif