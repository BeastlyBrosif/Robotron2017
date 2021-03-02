/*
 * Bullet.h
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */

#ifndef BULLET_H_
#define BULLET_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL_mixer.h>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "./Entity.h"

class Bullet: public Entity {
public:
	Bullet(int _dir, float x, float y): Entity(){
		dir = _dir;
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		scale = cfg.BULLET_SCALE;
		init();

		moveStartTime = SDL_GetTicks();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		m_deleted = false;
		m_hitBoxWidth = cfg.BULLET_WIDTH;
		m_hitBoxHeight = cfg.BULLET_HEIGHT;

        hit = false;
	}
	void rotateForDir();

    ~Bullet(){ ;

    if(hit)
    {
       // Mix_PlayChannel(-1, cfg.bulletHit, 0 );
    }


    }
    void init();
    void bulletHasHit(){hit = true;};
    bool getHitState(){return hit;}

	void setBulletToDeleted() { m_deleted = true; }
	bool getDeletedState() { return m_deleted; }
protected:

	bool m_deleted; //adding a boolean so that the factor knows that this bullet is to be deleted
	bool hit;
};


#endif /* BULLET_H_ */
