#ifndef SPHEROID_H_
#define SPHEROID_H_
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



class Spheroid: public Enemy {
public:
	Spheroid(float x, float y): Enemy(){
		entityType = cfg.SPHEROID;
		scale =	cfg.SPHEROID_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.SPHEROID_UPDATE;
		animationInterval = cfg.SPHEROID_ANIMATION_INTERVAL + rand() % (cfg.SPHEROID_ANIMATION_INTERVAL);
		moveStartTime = getTimeWithOffSet() - cfg.SPHEROID_UPDATE;
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet() - cfg.SPHEROID_DIR_UPDATE;
		dirUpdateInterval = cfg.SPHEROID_DIR_UPDATE + rand() % (cfg.SPHEROID_DIR_UPDATE);
		numEnforcersToShoot = (rand() % 7) + 1;

		m_shotStartTime = getTimeWithOffSet();
		m_shotInterval = cfg.SPHEROID_SHOT_INTERVAL + rand() % (cfg.SPHEROID_SHOT_INTERVAL);

		m_moveSpeed = cfg.SPHEROID_SPEED;;
		scoreValue = cfg.SPHEROID_SCORE;
		m_hitBoxHeight = cfg.SPHEROID_HEIGHT;
		m_hitBoxWidth = cfg.SPHEROID_WIDTH;
        enforcerSpawnDelay = cfg.SPHEROID_ENFORCER_SPAWN_DELAY;
        enforcerDelayStartTime = getTimeWithOffSet();
		m_hasShot = false;
	}
    virtual ~Spheroid(){};
    void init();
    void move(Player * player);
    void draw(int dir); //OVERRIDE as Spheroids only have the one set of meshs, they arent dependent on the direction
    void updateRandomDir();
    void updateAnimation();
    void setUpEnforcerStartTime();

protected:
    int numEnforcersToShoot;
    unsigned int enforcerSpawnDelay;
    unsigned int enforcerDelayStartTime;
    bool used = false;
};



#endif /* SPHEROID_H_ */
