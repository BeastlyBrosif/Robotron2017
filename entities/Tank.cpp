/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <ctime>

#include "../entities/Grunt.h"
#include "../graphics/Mesh.h"
#include "../Config.h"
#include "Tank.h"

void Tank::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/tank/tank1.mtl");
	modelLoader.readOBJfile("./res/tank/tank1_1.obj");
	clearVectors();
	modelLoader.clearMaterials();


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);

	modelLoader.readMTLfile("./res/tank/tank2.mtl");
	modelLoader.readOBJfile("./res/tank/tank1_1.obj");
	clearVectors();
	modelLoader.clearMaterials();


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	modelLoader.readMTLfile("./res/tank/tank3.mtl");
	modelLoader.readOBJfile("./res/tank/tank1_1.obj");
	clearVectors();
	modelLoader.clearMaterials();


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	modelLoader.readMTLfile("./res/tank/tank4.mtl");
	modelLoader.readOBJfile("./res/tank/tank1_1.obj");
	clearVectors();
	modelLoader.clearMaterials();


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);


	clearVectors();
	modelLoader.clearMaterials();

}
void Tank:: move (Player * player)
{

    float playerX = (*player).getTransform()->GetPos()->x;
    float playerY = (*player).getTransform()->GetPos()->y;

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;

    updateAnimation();

    checkIfTimeTOShoot();

    updateRandomDir();


    checkBoundaryCollides(); //check if the entity has hit any of the boundaries and reverse thier motion if they have
    defaultMovementForDir();


}

void Tank::draw(int dir)
{
    Entity::draw(cfg.NO_DIR); //override to only draw from the NO_DIR vector

}

void Tank::updateRandomDir() //override to allow diagonals, as the base class version does not
{

    if ((getTimeWithOffSet() - dirChangeStartTime) > dirUpdateInterval)
    {
        setDir(rand() % (cfg.NUM_DIRECTIONS));
        dirChangeStartTime = getTimeWithOffSet();
    }
}

void Tank::updateAnimation() //override to ensure we only draw from the NO_DIR meshs
{

    if ((getTimeWithOffSet() - animationStartTime) > animationInterval)
    {
        nextMesh(cfg.NO_DIR);
        animationStartTime = getTimeWithOffSet();
    }
}

Tank::~Tank() {
	// TODO Auto-generated destructor stub
}



