/*
 * WordBuilder.h
 *
 *  Created on: 23 Feb 2018
 *      Author: callum
 */

#ifndef WORDBUILDER_H_
#define WORDBUILDER_H_
#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "../entities/Entity.h"
#include "../graphics/Mesh.h"
#include "../graphics/Shader.h"
#include "../graphics/Camera.h"
#include "../entities/TextureSquare.h"


class WordBuilder {
public:
	void buildWord(string word, float wordX, float wordY, unsigned int timeOnScreen);
	bool update(Shader * shader, Camera * camera);
	void replaceWord(string word, float wordX, float wordY);
	WordBuilder(string word,float wordScale,float letterSpacing, glm::vec4 wordColor, float wordX, float wordY, unsigned int timeOnScreen);
    ;

	virtual ~WordBuilder();

protected:
    unsigned int animationStartTime = SDL_GetTicks();
    unsigned int m_timeOnScreen;
	std::vector<TextureSquare *> wordVec;
	Config cfg;
    glm::vec4 m_wordColor;
	float m_scale;
	float m_letterSpacing;


};




#endif /* WORDBUILDER_H_ */
