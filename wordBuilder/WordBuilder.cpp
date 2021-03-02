/*
 * WordBuilder.cpp
 *
 *  Created on: 23 Feb 2018
 *      Author: callum
 */

#include "WordBuilder.h"
#include <vector>
#include <iostream>
#include "../entities/Entity.h"
#include "../entities/TextureSquare.h"
#include "../graphics/Mesh.h"
#include "../graphics/Shader.h"
#include "../Config.h"

void WordBuilder::replaceWord(string word, float wordX, float wordY)
{
	int prevSize = wordVec.size();

    for(unsigned int i = 0; i < wordVec.size(); i++) //loop to delete the memory associated with the old word
    {
        delete wordVec[i];
    }
	wordVec.clear();

	buildWord(word, wordX, wordY, m_timeOnScreen);
}

void WordBuilder::buildWord(string word, float wordX, float wordY, unsigned int timeOnScreen)
{

    m_timeOnScreen = timeOnScreen;
	int b = word.size() -1;
	int c = 0;
	int texX, texY;
    //16 and 8
	float x = wordX;

	float left, right, top, bottom;

    float horizontalVal = (float)1 / (float) 16; //scaling, to scale th x and y values between 0 and 1 for use with an openGL texture
    float verticalVal = (float)1 / (float) 8;

	for (unsigned int i = 0; i < word.size(); i++)
	{

		c = word[i];
        if (c >= 32 && c<= 47) //if statements to get the correct row + column of the image for the corresponding ascii value of the character
		{
			texY = 0;
			texX = c - 32;
		}
		else if (c >= 48 && c <= 63)
		{
			texY = 1;
			texX = c - 48;
		}
		else if(c >= 64 && c <= 79)
		{
			texY = 2;
			texX = c - 64;
		}
		else if (c >= 80 && c <= 95)
		{
			texY = 3;
			texX = c - 80;
		}

		left = horizontalVal * texX ; //calculate the left, and right x values, top and bottom y values for the character, passed into the mesh, used to draw a square over the correct letter in the texture
		right = left + horizontalVal;

		bottom = verticalVal * texY;
		top = (bottom + verticalVal);


		wordVec.push_back(new TextureSquare(x,wordY,m_scale,m_wordColor,left, right, top, bottom)); //add a new letter using a texture square

		x = x - m_letterSpacing; //move along by the letter spacing amount
	}


}
bool WordBuilder::update(Shader * shader, Camera * camera) //loop to draw all of the letters on the screen, draw backwards to solve overlapping, but shouldnt be a problem now transparency works
{

    unsigned int currentTime = SDL_GetTicks();
	int b = wordVec.size() -1;
	shader->Bind();

    if(m_timeOnScreen == 0 || currentTime - animationStartTime < m_timeOnScreen ) // 0 = infinite, so draw, otherwise check the word is in its time frame and draw
    {
        for(unsigned int i = 0; i < wordVec.size(); i++)
        {

                (*shader).Update(*(wordVec[b]->getTransform()), *camera);

                glDepthMask(GL_FALSE); //functions to enable the transparent backgroun to work
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                (*wordVec[b]).draw(cfg.NO_DIR); //draw with NO_DIR, only one mesh vec used
                glDisable(GL_BLEND);
                glDepthMask(GL_TRUE);

            b--;
        }
        return true;
    }
    else //if the word has used its time, delete the letters from the vector and clear the vector, return false
    {
        for(unsigned int i = 0; i < wordVec.size(); i++)
        {
           delete wordVec[i];
        }
        wordVec.clear();
        return false;
    }
}



WordBuilder::WordBuilder(string word,float wordScale,float letterSpacing, glm::vec4 wordColor, float wordX, float wordY, unsigned int timeOnScreen) {

    m_wordColor = wordColor;
    m_letterSpacing = letterSpacing;
    m_scale = wordScale;
    if(word != "") //if not empty build the word
    {
        m_timeOnScreen = timeOnScreen;
        buildWord(word, wordX, wordY, timeOnScreen);
    }

}

WordBuilder::~WordBuilder() {
	// TODO Auto-generated destructor stub
}


