/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#include "../entities/Electrode.h"
#include "../graphics/Mesh.h"
#include "../Config.h"


void Electrode::init()
{
	ModelLoader mLoader(1);

	//get rand number -> convert to letter load in

	mLoader.readMTLfile("./res/electrode/A2.mtl");
	mLoader.readOBJfile("./res/electrode/A2.obj");

	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.NO_DIR);
	mLoader.clearMaterials();
	clearVectors();


	mLoader.readMTLfile("./res/electrode/A3.mtl");
	mLoader.readOBJfile("./res/electrode/A3.obj");
	addMesh(new Mesh(mLoader.getVertices(), mLoader.getIndices(), mLoader.getColourList(), true, false, false), cfg.NO_DIR);
	mLoader.clearMaterials();

	clearVectors();
}

void Electrode::move(Player * player)
{
    updateAnimation();
}



