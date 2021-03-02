/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#include "../entities/Grunt.h"
#include "../graphics/Mesh.h"
#include "../Config.h"

namespace std {

void Grunt::init()
{
	ModelLoader modelLoader(1);

    modelLoader.readMTLfile("./res/grunt/Grunt1ColourModel.mtl");
	modelLoader.readOBJfile("./res/grunt/Grunt1ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/grunt/Grunt2ColourModel.mtl");
	modelLoader.readOBJfile("./res/grunt/Grunt2ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/grunt/Grunt3ColourModel.mtl");
	modelLoader.readOBJfile("./res/grunt/Grunt3ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();


}

void Grunt::move(Player * player)
{
    float playerX = (*player).getTransform()->GetPos()->x;
    float playerY = (*player).getTransform()->GetPos()->y;

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;


    updateAnimation();


    if (getTimeWithOffSet() - moveStartTime > updateInterval) //move directly towards the player
    {
        if(x > playerX)
        {
            getTransform()->GetPos()->x -= m_moveSpeed;
        }

        if(x < playerX)
        {
            getTransform()->GetPos()->x += m_moveSpeed;
        }
        if(y > playerY)
        {
            getTransform()->GetPos()->y -=  m_moveSpeed;
        }
        if(y < playerY)
        {
            getTransform()->GetPos()->y += m_moveSpeed;
        }
        moveStartTime = getTimeWithOffSet();

    }

}


Grunt::~Grunt() {
	// TODO Auto-generated destructor stub
}


} /* namespace std */
