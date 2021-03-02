#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "../entities/Entity.h"
#include "../entities/Player.h"


class Enemy : public Entity
{
public:
  Enemy() : Entity()
  {
	  m_destroyed = false;

  };
    virtual void move(Player * player) {};

    bool checkIfTimeTOShoot();

    virtual bool hasShot(){return m_hasShot;}; //returns whether the enemy has shot, default is to return false, if the enemy has not shot

    virtual ~Enemy(){};


protected:
    bool m_hasShot = false;
    unsigned int m_shotStartTime = SDL_GetTicks();
    unsigned int m_shotInterval;

private:

};

#endif // ENEMY_H
