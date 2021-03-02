//Class - Level Factory
//This class is responsible for creating levels

#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include <iostream>

#include "Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Bullet.h"
#include "../entities/Enemy.h"

class LevelFactory : public Factory
{
	LevelFactory() : Factory()
	{
	
	}

};



#endif