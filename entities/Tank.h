/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef TANK_H_
#define TANK_H_
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "../Config.h"
#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Camera.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../entities/EnforcerSpark.h"



class Tank: public Enemy {
public:
	Tank(float x, float y): Enemy(){
		entityType = cfg.TANK;
		scale =	cfg.TANK_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.TANK_UPDATE;
		animationInterval = cfg.TANK_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet() - cfg.TANK_DIR_UPDATE;
		dirUpdateInterval = cfg.TANK_DIR_UPDATE + rand() % cfg.TANK_DIR_UPDATE;

		m_shotStartTime = getTimeWithOffSet();
		m_shotInterval = cfg.SHELL_INTERVAL + rand() % (cfg.SHELL_INTERVAL);

		m_moveSpeed = cfg.TANK_SPEED;;
		scoreValue = cfg.TANK_SCORE;
		m_hitBoxHeight = cfg.TANK_HEIGHT;
		m_hitBoxWidth = cfg.TANK_WIDTH;
		m_hasShot = false;
	}
    ~Tank();
    void init();
    void move(Player * player);
    void draw(int dir); //OVERRIDE the entity version so we can make sure the tanks only draw from there one set of meshs, the default version automatically chooses the meshvec for the dir
    void updateAnimation(); //OVERRIDE to allow th tanks to move diagnonally
    void updateRandomDir();

protected:

};



#endif /* TANK_H_ */
