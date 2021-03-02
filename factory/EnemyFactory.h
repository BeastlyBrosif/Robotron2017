/*
 * Enemyfactory.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#include "Factory.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/Bullet.h"
#include "../entities/Enemy.h"
#include "../entities/Family.h"
#include "../wordBuilder/WordBuilder.h"
#include "../graphics/particlesystem/ParticleFactory.h"

#include <vector>


class EnemyFactory : public Factory {
public:
	EnemyFactory(vector<Bullet *> * _bulletVec, vector<Family *> * _familyVec) :Factory(){
		bulletVec = _bulletVec;
		familyVec = _familyVec;
		m_isPaused = false;
	}


	//~Enemyfactory();

	void createEntity(int Enemy, float x, float y, int amount);
	void update(Camera *camera, Shader *shader, Shader * texShader, Player * player);
	void setScaling();
	bool checkEnemyKilled(Enemy * enemy, Player * player);
	bool checkPlayerCollide(Player * player, Enemy * enemy);
	bool checkFamilyCollide(Enemy * enemy, Player * player);
	bool bulletHitBoundary(Enemy * enemy);
	void updateText(Shader * texShader, Camera * camera);
	void createProgs();
	void setScalingForLast();
	void createEnemyProjectiles(Enemy * enemy, Player * player, Shader * shader, Camera * camera);
	void addOffsetToObjects(unsigned int increment);


private:

	ParticleFactory m_particleFactory;
	glm::vec4 wordColor = glm::vec4(1,1,1,1);
	std::vector<Enemy *> enemyVec;

	std::vector<Bullet *> * bulletVec;
	std::vector<Family *> * familyVec;
	std::vector<WordBuilder * > wordScoreVec;
};


#endif /* ENEMYFACTORY_H_ */
