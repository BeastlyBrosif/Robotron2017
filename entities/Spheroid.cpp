#include <string>
#include <SDL2/SDL_mixer.h>

#include "Spheroid.h"

void Spheroid::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/spheroid/1.mtl");
	modelLoader.readOBJfile("./res/spheroid/1.obj");



	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/2.mtl");
	modelLoader.readOBJfile("./res/spheroid/2.obj");



	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/3.mtl");
	modelLoader.readOBJfile("./res/spheroid/3.obj");



	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/4.mtl");
	modelLoader.readOBJfile("./res/spheroid/4.obj");


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/5.mtl");
	modelLoader.readOBJfile("./res/spheroid/5.obj");


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/6.mtl");
	modelLoader.readOBJfile("./res/spheroid/6.obj");


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/7.mtl");
	modelLoader.readOBJfile("./res/spheroid/7.obj");


	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/spheroid/8.mtl");
	modelLoader.readOBJfile("./res/spheroid/8.obj");

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    clearVectors();
	modelLoader.clearMaterials();


	clearVectors();
	modelLoader.clearMaterials();

	getTransform()->GetPos()->z += 5;

}
void Spheroid:: move (Player * player)
{

    updateAnimation();

    if((getTimeWithOffSet() - enforcerDelayStartTime) > enforcerSpawnDelay) //just added so we can add a delay of the enforcers spawning if we need
    {
        if(!used) //just ensures we only initialise the shotStartTime abnormally one time
        {
            m_shotStartTime = getTimeWithOffSet();
        }
        used = true;

        if(numEnforcersToShoot == 0) //destroy spheroid if shot all enforcers
        {
            SetEntityToDestroyed();
        }

        if (checkIfTimeTOShoot()) //if time to shoot, decrease the amount of enforcers to shoot
        {
            numEnforcersToShoot--;
        }
    }


    updateRandomDir();

    checkBoundaryCollides(); //check if the entity has hit any of the boundaries and reverse thier motion if they have
    defaultMovementForDir();

}

void Spheroid::draw(int dir)
{
    Entity::draw(cfg.NO_DIR);
}


void Spheroid::updateRandomDir() //override to allow diagonals, as the base class version does not
{

    if ((getTimeWithOffSet() - dirChangeStartTime) > dirUpdateInterval)
    {
        setDir(rand() % (cfg.NUM_DIRECTIONS));
        dirChangeStartTime = getTimeWithOffSet();
    }
}

void Spheroid::updateAnimation() //override to ensure we only draw from the NO_DIR meshs
{

    if ((getTimeWithOffSet() - animationStartTime) > animationInterval)
    {
        nextMesh(cfg.NO_DIR);
        animationStartTime = getTimeWithOffSet();
    }
}


