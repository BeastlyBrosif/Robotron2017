/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef GRUNT_H_
#define GRUNT_H_
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "../Config.h"
#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"

namespace std {

class Grunt: public Enemy {
public:
	Grunt(float x, float y): Enemy(){
		entityType = cfg.GRUNT;
		scale =	cfg.GRUNT_SCALE;
		init();
		dir = cfg.NO_DIR; //Grunt doesnt have different meshes for the different directions, so when it draws use NO_DIR
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		updateInterval = cfg.GRUNT_UPDATE;
		animationInterval = cfg.GRUNT_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		m_moveSpeed = cfg.GRUNT_SPEED;
		scoreValue = cfg.GRUNT_SCORE;
		m_hitBoxHeight = cfg.GRUNT_HEIGHT;
		m_hitBoxWidth = cfg.GRUNT_WIDTH;
	}
    ~Grunt();
    void init();
    void move(Player * player);

protected:
};

} /* namespace std */

#endif /* GRUNT_H_ */
