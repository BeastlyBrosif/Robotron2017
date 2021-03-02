/*
 * PlayerFactory.h
 *
 *  Created on: 14 Feb 2018
 *      Author: callum
 */

#ifndef PLAYERFACTORY_H_
#define PLAYERFACTORY_H_

#include "Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../graphics/particlesystem/ParticleFactory.h"

#include <vector>


class PlayerFactory : public Factory {
public:
	PlayerFactory(): Factory()
	{
		m_playerKilled = false;
		setScaling();
		m_isPaused = false;
	}


	virtual ~PlayerFactory(){};

	void update(Camera *camera, Shader *shader, bool * dirArray);
	void setScaling();
	Player * getPlayerPointer();
private:
	bool m_playerKilled;
	Player player; //creating the player factory creates the player
	ParticleFactory p;
};


#endif /* PLAYERFACTORY_H_ */
