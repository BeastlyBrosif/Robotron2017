/*
 * Bullet.h
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */

#ifndef TANKSHELL_H_
#define TANKSHELL_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL_mixer.h>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "./Entity.h"
#include "../entities/Enemy.h"

class TankShell: public Enemy {
public:
	TankShell(float playerX, float playerY, float x, float y): Enemy(){

		dir = cfg.NO_DIR;
		scale =	cfg.SPARK_SCALE;
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		animationInterval = cfg.SHELL_ANIMATION_INTERVAL;
		updateInterval = cfg.SHELL_UPDATE;
		//dirChangeStartTime = SDL_GetTicks();
		m_playerX = playerX;
		m_playerY = playerY;
		entityType = cfg.TANK_SHELL;
		m_hitBoxHeight = cfg.TANK_SHELL_HEIGHT;
		m_hitBoxWidth = cfg.TANK_SHELL_WIDTH;
		scoreValue = cfg.TANK_SHELL_SCORE;
		m_LifeTime = cfg.SHELL_LIFETIME;
		m_lifeTimeStart = getTimeWithOffSet();
		init();

	}
    ~TankShell(){};
    bool checkBoundaryCollides();
    void init();
    void move(Player * player);

protected:
    float m_ratio;
    float m_playerX;
    float m_playerY;
    float m_moveDisX;
    float m_moveDisY;


};


#endif /* ENFORCERSPARK_H_ */
