/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef ELECTRODE_H_
#define ELECTRODE_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../entities/Enemy.h"
#include "../Config.h"


class Electrode: public Enemy {
public:
	Electrode(float x, float y): Enemy(){
		entityType = cfg.ELECTRODE;
		scale = cfg.ELECTRODE_SCALE;
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		init();

		animationInterval = cfg.GRUNT_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dir = cfg.NO_DIR;
		scoreValue = 0; //the amount of points to give the player when killed
		m_hitBoxHeight = cfg.ELECTRODE_HEIGHT;
		m_hitBoxWidth = cfg.ELECTRODE_WIDTH;

	}
    ~Electrode(){};
    void init();
	 void move(Player * player);

protected:


};

#endif /* ELECTRODE_H_ */
