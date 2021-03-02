/*
 * Grunt.h
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#ifndef TEXTURESQUARE_H_
#define TEXTURESQUARE_H_
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



class TextureSquare: public Entity {
public:
	TextureSquare(float x, float y,float _scale, glm::vec4 textureColor, float texLeft, float texRight, float texTop, float texBottom): Entity(){
		textureLeft = texLeft;
        textureRight = texRight;
        textureTop = texTop;
        textureBottom = texBottom;


        scale = _scale;
        m_textureColor = textureColor;

		entityType = -1;
		//scale = cfg.WORD_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
	}
    ~TextureSquare(){};
    void init();

private:

	float textureLeft;
	float textureRight;
	float textureTop;
	float textureBottom;
	float m_scale;
	glm::vec4 m_textureColor;


};



#endif /* TEXTURESQUARE_H_ */
