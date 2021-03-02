/*
 * Bullet.cpp
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#include "../entities/Bullet.h"
#include "../graphics/Mesh.h"
#include "../Config.h"


void Bullet::rotateForDir()
{
    if(dir == cfg.UP || dir == cfg.DOWN) //rotate 90 degrees for up and DOWN
    {
        getTransform()->GetRot()->z += 1.5708;
    }
    if(dir == cfg.UP_LEFT || dir == cfg.DOWN_RIGHT) //rotate 45 degrees for the correct diagonal
    {
        getTransform()->GetRot()->z += 0.785398;
    }
    if(dir == cfg.UP_RIGHT || dir == cfg.DOWN_LEFT) //rotate 45 degress for the correct diagonal
    {
        getTransform()->GetRot()->z += 5.49779;
    }

}
void Bullet::init()
{

    ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/bullet/p6.mtl");
	modelLoader.readOBJfile("./res/bullet/p6.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR); //just used one of the bullet textures and rotated it, rather than loading them all in because of meshVec limitations
    modelLoader.clearMaterials();
    rotateForDir();
}




