/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "Hulk.h"
#include "../graphics/Mesh.h"
#include "../Config.h"
#include <vector>
#include <string>

#include <SDL2/SDL_mixer.h>



void Hulk::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/hulk/HulkFront1ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkFront1ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/hulk/HulkFront2ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkFront2ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/hulk/HulkFront3ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkFront3ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();


    modelLoader.readMTLfile("./res/hulk/HulkLeft1ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkLeft1ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkLeft2ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkLeft2ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkLeft3ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkLeft3ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkRight1ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkRight1ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkRight2ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkRight2ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkRight3ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkRight3ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/hulk/HulkRight1ColourModel.mtl");
	modelLoader.readOBJfile("./res/hulk/HulkRight1ColourModel.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();

    getTransform()->GetPos()->z += 0.1;
}

void Hulk:: move (Player * player)
{

    float playerX = (*player).getTransform()->GetPos()->x;
    float playerY = (*player).getTransform()->GetPos()->y;

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;


    if(getHasBeenShotDir() != cfg.NO_DIR) //detect if the hulk was shot, and from what direction, push them in that direction
    {
        setSpeed(getSpeed() - cfg.HULK_SLOWDOWN);
        int push_dir = getHasBeenShotDir();

        if(push_dir == cfg.UP)
        {
            getTransform()->GetPos()->y += cfg.HULK_PUSH_VAL;
        }
        else if(push_dir == cfg.DOWN)
        {
            getTransform()->GetPos()->y -= cfg.HULK_PUSH_VAL;
        }
        else if(push_dir == cfg.LEFT)
        {
            getTransform()->GetPos()->x += cfg.HULK_PUSH_VAL;
        }
        else if(push_dir == cfg.RIGHT)
        {
            getTransform()->GetPos()->x -= cfg.HULK_PUSH_VAL;
        }
        if(push_dir == cfg.UP_RIGHT)
        {
            getTransform()->GetPos()->x -= cfg.HULK_PUSH_VAL;
            getTransform()->GetPos()->y += cfg.HULK_PUSH_VAL;
        }
        if(push_dir == cfg.UP_LEFT)
        {
            getTransform()->GetPos()->x += cfg.HULK_PUSH_VAL;
            getTransform()->GetPos()->y += cfg.HULK_PUSH_VAL;
        }
        if(push_dir == cfg.DOWN_RIGHT)
        {
            getTransform()->GetPos()->x -= cfg.HULK_PUSH_VAL;
            getTransform()->GetPos()->y -=cfg.HULK_PUSH_VAL;
        }
        if(push_dir == cfg.DOWN_LEFT)
        {
            getTransform()->GetPos()->x += cfg.HULK_PUSH_VAL;
            getTransform()->GetPos()->y -= cfg.HULK_PUSH_VAL;
        }


        setHasBeenShotDir(cfg.NO_DIR);

    }

    updateRandomDir();

    updateAnimation();

    checkBoundaryCollides(); //check if the entity has hot any of the boundaries and reverse thier motion if they have

    defaultMovementForDir();
}
Hulk::~Hulk() {
	// TODO Auto-generated destructor stub
}



