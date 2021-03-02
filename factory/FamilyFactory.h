/*
 * Enemyfactory.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef FAMILYFACTORY_H_
#define FAMILYFACTORY_H_
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Bullet.h"
#include "../entities/Enemy.h"
#include "../entities/Family.h"



class FamilyFactory : public Factory {
public:
	FamilyFactory(vector<Bullet *> * _bulletVec) :Factory(){
		bulletVec = _bulletVec;
		m_isPaused = false;
	}


	~FamilyFactory(){

    Mix_FreeChunk(saveFamilySound);
	};

	void createEntity(int Enemy, float x, float y, int amount);
	void update(Camera *camera, Shader *shader, Shader * texShader, Player * player);
	void setScaling();
	void setScalingForLast();
	//bool checkEnemyKilled(Enemy * enemy);
	bool checkPlayerCollide(Player * player, Family * entity);
    void updateText(Shader * texShader, Camera * camera);

    vector<Family *> * getFamilyVectorPointer(){return &entityVec;}
    void addOffsetToObjects(unsigned int increment);


private:
    glm::vec4 wordColor = glm::vec4(1,1,1,1);
	std::vector<Family *> entityVec;

	vector<Bullet *> * bulletVec;
	Mix_Chunk * saveFamilySound = Mix_LoadWAV("./res/save_human.wav");
};


#endif /* FAMILYFACTORY_H_ */
