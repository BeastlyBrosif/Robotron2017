#include "Son.h"
void Son::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/son/STILL.mtl");
	modelLoader.readOBJfile("./res/son/STILL.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);


    modelLoader.readMTLfile("./res/son/DOWN1.mtl");
	modelLoader.readOBJfile("./res/son/DOWN1.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);


    modelLoader.readMTLfile("./res/son/DOWN2.mtl");
	modelLoader.readOBJfile("./res/son/DOWN2.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);


    modelLoader.readMTLfile("./res/son/DOWN3.mtl");
	modelLoader.readOBJfile("./res/son/DOWN3.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);



    modelLoader.readMTLfile("./res/son/UP1.mtl");
	modelLoader.readOBJfile("./res/son/UP1.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);



    modelLoader.readMTLfile("./res/son/UP2.mtl");
	modelLoader.readOBJfile("./res/son/UP2.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);


    modelLoader.readMTLfile("./res/son/UP3.mtl");
	modelLoader.readOBJfile("./res/son/UP3.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);

    modelLoader.readMTLfile("./res/son/LEFT1.mtl");
    modelLoader.readOBJfile("./res/son/LEFT1.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);


    modelLoader.readMTLfile("./res/son/LEFT2.mtl");
    modelLoader.readOBJfile("./res/son/LEFT2.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);

    modelLoader.readMTLfile("./res/son/LEFT3.mtl");
    modelLoader.readOBJfile("./res/son/LEFT3.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);



    modelLoader.readMTLfile("./res/son/RIGHT1.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT1.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);

    modelLoader.readMTLfile("./res/son/RIGHT2.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT2.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);


    modelLoader.readMTLfile("./res/son/RIGHT3.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT3.obj");
    clearVectors();
    modelLoader.clearMaterials();
    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);



    transform.GetRot()->z += cfg.DEFAULT_ROT * 2; //for the son textures this must be done for some reason, otherwise they display wierdly
    transform.GetPos()->z += 5.0f; //bring forward
	clearVectors();
	modelLoader.clearMaterials();

}
void Son:: move (Player * player)
{
    float playerX = (*player).getTransform()->GetPos()->x;
    float playerY = (*player).getTransform()->GetPos()->y;

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;
    //int dir = getDir();
    if(!isProg())
    {
        updateAnimation();

        updateRandomDir();

        checkBoundaryCollides(); //check if the entity has hot any of the boundaries and reverse thier motion if they have

        defaultMovementForDir();
    }

}
