/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef HULK_H_
#define HULK_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "../Config.h"

namespace std {

class Hulk: public Enemy {
public:
	Hulk(float x, float y): Enemy(){
		entityType = cfg.HULK;
		m_moveSpeed = cfg.HULK_SPEED;
		scale = cfg.HULK_SCALE;
		init();
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		updateInterval = cfg.HULK_UPDATE;
		dirUpdateInterval = cfg.HULK_DIR_UPDATE + rand() % cfg.HULK_DIR_UPDATE;
		animationInterval = cfg.HULK_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		scoreValue = 0;
		m_hitBoxHeight = cfg.HULK_HEIGHT;
		m_hitBoxWidth = cfg.HULK_WIDTH;
		setHasBeenShotDir(cfg.NO_DIR);
		dir = cfg.NO_DIR;
	}
    ~Hulk();
    void init();
    void move(Player * player);



protected:


};

} /* namespace std */

#endif /* HULK_H_ */
