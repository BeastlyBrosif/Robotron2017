/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef ENFORCER_H_
#define ENFORCER_H_
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


class Enforcer: public Enemy {
public:
	Enforcer(float x, float y): Enemy(){
		entityType = cfg.ENFORCER;
		scale =	cfg.ENFORCER_SCALE;
		init();
		dir = cfg.NO_DIR; //Enforcer doesnt have different meshes for the different directions, so when it draws use NO_DIR
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.ENFORCER_UPDATE;
		animationInterval = cfg.ENFORCER_ANIMATION_INTERVAL;
		moveStartTime = SDL_GetTicks();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();


		m_shotInterval = getTimeWithOffSet();
		m_shotInterval = cfg.SPARK_INTERVAL + rand() % (cfg.SPARK_INTERVAL / 2);


		m_moveSpeed = 0;
		scoreValue = cfg.ENFORCER_SCORE;
		m_hitBoxHeight = cfg.ENFORCER_HEIGHT;
		m_hitBoxWidth = cfg.ENFORCER_WIDTH;
		moveStartTime = getTimeWithOffSet();
		m_offsetChangeInterval = cfg.ENFORCER_OFFSET_INTERVAL + rand() %(cfg.ENFORCER_OFFSET_INTERVAL / 2);
		m_offsetChangeStartTime = getTimeWithOffSet();
		flyOffStartTime = getTimeWithOffSet();
		flyOffDurationStarted = false;

	}
    ~Enforcer();
    void init();
	virtual void move(Player * player);
	void flyOffToEdge();
	void chooseEdge();
	void startFlyoffInterval();

protected:
	unsigned int m_offsetChangeInterval;
	unsigned int m_offsetChangeStartTime;
	float randomOffsetX;
	float randomOffsetY;
	int edgeChosen;
	unsigned int flyOffStartTime;
	unsigned int flyDurationStartTime;
	unsigned int flyOffDurationInterval = cfg.ENFORCER_FLYOFF_DURATION;
	unsigned int flyOffInterval = cfg.ENFORCER_FLYOFF_INTERVAL + rand() % cfg.ENFORCER_FLYOFF_INTERVAL;
	bool flyOffDurationStarted;

	float edgeSlideSpeed = 1;
};


#endif /* ENFORCER_H_ */
