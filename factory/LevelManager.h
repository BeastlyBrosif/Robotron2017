//Class - Level Factory
//This class is responsible for creating levels classes from data files

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>

#include "Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Bullet.h"
#include "../entities/Enemy.h"

class LevelManager : public Factory
{
	LevelManager() : Factory()
	{
	
	}

};



#endif