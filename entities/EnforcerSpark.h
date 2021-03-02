/*
 * Bullet.h
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */

#ifndef ENFORCERSPARK_H_
#define ENFORCERSPARK_H_
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

class EnforcerSpark: public Enemy {
public:
	EnforcerSpark(float playerX, float playerY, float x, float y): Enemy(){

		dir = cfg.NO_DIR;
		scale =	cfg.SPARK_SCALE;
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		updateInterval = cfg.SPARK_UPDATE;
		animationInterval = cfg.SPARK_ANIMATION_INTERVAL;
		//dirChangeStartTime = SDL_GetTicks();
		m_playerX = playerX;
		m_playerY = playerY;
		entityType = cfg.ENFORCER_SPARK;
		m_hitBoxHeight = cfg.SPARK_HEIGHT;
		m_hitBoxWidth = cfg.SPARK_WIDTH;
		scoreValue = cfg.ENFORCER_SPARK_SCORE;
		m_LifeTime = cfg.SPARK_LIFETIME;
		m_lifeTimeStart = getTimeWithOffSet();
		init();
		xCurve = false;
		yCurve = false;

	}
    ~EnforcerSpark(){};
    bool checkBoundaryCollides();
    void init();
    void move(Player * player);

protected:
    float m_ratio;
    float m_playerX;
    float m_playerY;
    float m_moveDisX;
    float m_moveDisY;
    bool xCurve;
    bool yCurve;
    float randomCurve;
};


#endif /* ENFORCERSPARK_H_ */
