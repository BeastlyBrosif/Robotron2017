/*
 * Player.cpp
 *
 *  Created on: 6 Feb 2018
 *      Author: callum
 */


#include <vector>
#include "../entities/Player.h"
#include "../graphics/Mesh.h"




void Player::init()
{
	lives = cfg.PLAYER_LIVES;

	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/player/PLAYER_STILL.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_STILL.obj");

//	modelLoader.readOBJfile("./res/player/PLAYER_STILL.obj");

	for(int i = 0; i < modelLoader.getVerticesSize(); i++)
	{
		colorVec.push_back(glm::vec4(0.0f,  0.0f,  1.0f, 1));
	}
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(), modelLoader.getColourList() , true, false, false), cfg.NO_DIR);
	modelLoader.clearMaterials();


	//PLAYER GOING UP
	modelLoader.readMTLfile("./res/player/PLAYER_UP1.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_UP1.obj");
//	modelLoader.getVerticesSize(); WHY???!?!

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.UP);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_UP2.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_UP2.obj");
//	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.UP);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_UP3.mtl");
    modelLoader.readOBJfile("./res/player/PLAYER_UP3.obj");
//	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);
	modelLoader.clearMaterials();

//PLAYER GOING DOWN
	modelLoader.readMTLfile("./res/player/PLAYER_DOWN1.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_DOWN1.obj");
//	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_DOWN2.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_DOWN2.obj");

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_DOWN3.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_DOWN3.obj");
//	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
	modelLoader.clearMaterials();

//TO THE LEFT

	modelLoader.readMTLfile("./res/player/PLAYER_RIGHT1.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_RIGHT1.obj");
	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_RIGHT2.mtl");
    modelLoader.readOBJfile("./res/player/PLAYER_RIGHT2.obj");
	modelLoader.getVerticesSize();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_RIGHT3.mtl");
    modelLoader.readOBJfile("./res/player/PLAYER_RIGHT3.obj");
	modelLoader.getVerticesSize();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
	modelLoader.clearMaterials();

//TO THE RIGHT
	modelLoader.readMTLfile("./res/player/PLAYER_LEFT1.mtl");
    modelLoader.readOBJfile("./res/player/PLAYER_LEFT1.obj");

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/player/PLAYER_LEFT2.mtl");
	modelLoader.readOBJfile("./res/player/PLAYER_LEFT2.obj");
	modelLoader.getVerticesSize();

//	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.RIGHT);

	modelLoader.readMTLfile("./res/player/PLAYER_LEFT3.mtl");
    modelLoader.readOBJfile("./res/player/PLAYER_LEFT3.obj");
	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);
	modelLoader.clearMaterials();


	clearVectors();
	getTransform()->GetScale()->x = cfg.PLAYER_SCALE;
	getTransform()->GetScale()->y = cfg.PLAYER_SCALE;
	getTransform()->GetScale()->z = cfg.PLAYER_SCALE;



}
void Player::decreaseLives()
{
	lives--;
}


void Player::increaseScore(int _score)
{
    score += _score;
}
int Player::getScore()
{
	return score;
}
int Player::getLives()
{
	return lives;
}


