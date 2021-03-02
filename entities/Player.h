/*
 * Player.h
 *
 *  Created on: 6 Feb 2018
 *      Author: callum
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../Config.h"

class Player: public Entity {
public:
	Player(): Entity()
	{
		init();
		lives = cfg.PLAYER_LIVES;
		animationInterval = cfg.PLAYER_ANIMATION_INTERVAL;
		moveStartTime = SDL_GetTicks();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();

		m_hitBoxWidth = cfg.PLAYER_WIDTH;
		m_hitBoxHeight = cfg.PLAYER_HEIGHT;
        transform.GetPos()->x = 0;
        transform.GetPos()->y = 0;
        m_playerAlive = true;
		score = 0;
		level = 0;
	}
    ~Player(){};
    void init();
	void increaseScore(int _score);
	void decreaseLives();
	int getScore();
	int getLives();
	void killPlayer(){m_playerAlive = false;};
	bool getPlayerAlive(){return m_playerAlive;}
private:
	int lives;
	int score;
	int level;
	bool m_playerAlive;


};



#endif /* PLAYER_H_ */
