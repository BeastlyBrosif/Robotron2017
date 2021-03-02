/*
 * Square.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef LETTERSQUARE_H_
#define LETTERSQUARE_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL_mixer.h>

#include "../graphics/display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../entities/Entity.h"
#include "../Config.h"

namespace std {

class Square: public Entity {
public:
	Square(float x, float y, float width, float height): Entity(){
		m_width = width;
		m_height = height;


		entityType = -1;
		scale = 2;
		init();
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;


	}
	virtual ~Square();
    void init();
    virtual void setBlack();

private:

	float m_width;
	float m_height;


};

} /* namespace std */

#endif /* SQUARE_H_ */
