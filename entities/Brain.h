/*
 * Brain.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef BRAIN_H_
#define BRAIN_H_
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
#include "../entities/Family.h"



class Brain: public Enemy {
public:
	Brain(float x, float y, std::vector<Family* > * _familyVec): Enemy(){
		entityType = cfg.BRAIN;
		scale =	cfg.BRAIN_SCALE;

		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.BRAIN_UPDATE;
		animationInterval = cfg.BRAIN_ANIMATION_INTERVAL;
		moveStartTime = SDL_GetTicks();
		animationStartTime = SDL_GetTicks();
		dirChangeStartTime = SDL_GetTicks() + cfg.BRAIN_DIR_UPDATE + rand() % cfg.BRAIN_DIR_UPDATE;
		dirUpdateInterval = cfg.BRAIN_DIR_UPDATE + rand() % cfg.BRAIN_DIR_UPDATE;

		m_moveSpeed = cfg.BRAIN_SPEED;;
		scoreValue = cfg.BRAIN_SCORE;
		m_hitBoxHeight = cfg.BRAIN_HEIGHT;
		m_hitBoxWidth = cfg.BRAIN_WIDTH;
		m_hasShot = false;

		m_shotStartTime = SDL_GetTicks();
		m_shotInterval = cfg.MISSILE_INTERVAL + rand() % (cfg.MISSILE_INTERVAL);


		familyVec = _familyVec;
		//dir = cfg.NO_DIR;

        m_brainSeekInterval = cfg.BRAIN_SEEK_INTERVAL;
        m_brainSeekStartTime = SDL_GetTicks();
        m_progMakeStartTime = SDL_GetTicks();
		init();
		m_timeOffset = 0;

	}
    ~Brain(){};
    void init();
    void move(Player * player);
    void moveRandomly();
    void moveToClosestHuman();
    void seekClosest();
    void makingProg(){m_makingProg = true;
    m_progMakeStartTime = getTimeWithOffSet();
    dir = cfg.NO_DIR;}


protected:
	unsigned int m_shellShotStartTime;
	unsigned int m_shellShotInterval;

	float m_closestFamilyMemX;
	float m_closestFamilyMemY;
    bool m_makingProg = false;
    unsigned int m_progDelay = cfg.TIME_TO_MAKE_PROG;
    unsigned int m_progMakeStartTime = SDL_GetTicks();

    Family * familyTarget;
    unsigned int m_brainSeekStartTime;
    unsigned int m_brainSeekInterval;


	std::vector<Family *> * familyVec;
};



#endif /* BRAIN_H_ */
