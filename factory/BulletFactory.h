/*
 * BulletFactory.h
 *
 *  Created on: 9 Feb 2018
 *      Author: callum & nimrod
 */

#ifndef BULLETFACTORY_H_
#define BULLETFACTORY_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "./Factory.h"
#include "../entities/Entity.h"
#include "../entities/Bullet.h"
#include "../Config.h"


class BulletFactory: public Factory {
public:
	BulletFactory():Factory(){

    m_bulletsStartTime = SDL_GetTicks();
	m_bulletInterval = cfg.BULLET_INTERVAL;
	m_isPaused = false;
	}
	void createEntity(float x, float y, bool * bulletDirArray);
	void update(Camera *camera, Shader *shader);
    ~BulletFactory(){
    Mix_FreeChunk(bulletShot);
    Mix_FreeChunk(bulletHit);
    };
	vector<Bullet *> * getBulletVec();
	void setScaling();
	void setScalingForLast();
	void rotateForDir();


protected:
	vector<Bullet *> bulletVec;
	vector<Bullet *> deletedBulletsVec;
	unsigned int m_bulletInterval;
	unsigned int m_bulletsStartTime;
	Mix_Chunk * bulletShot = Mix_LoadWAV("./res/Fire.wav");
	Mix_Chunk * bulletHit = Mix_LoadWAV("./res/FireHit.wav");

};


#endif /* BULLETFACTORY_H_ */
