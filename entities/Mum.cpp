#include "Mum.h"
void Mum::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/mum/MumDown1ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumDown1ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumDown1ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumDown1ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.DOWN);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumDown2ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumDown2ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.DOWN);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumDown3ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumDown3ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.DOWN);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumUp1ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumUp1ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.UP);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumUp2ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumUp2ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.UP);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumUp3ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumUp3ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.UP);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumLeft1ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumLeft1ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.LEFT);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumLeft2ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumLeft2ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.LEFT);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumLeft3ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumLeft3ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.LEFT);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumRight1ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumRight1ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    clearVectors();
	modelLoader.clearMaterials();


	modelLoader.readMTLfile("./res/mum/MumRight2ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumRight2ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    clearVectors();
	modelLoader.clearMaterials();

	modelLoader.readMTLfile("./res/mum/MumRight3ColourModel.mtl");
	modelLoader.readOBJfile("./res/mum/MumRight3ColourModel.obj");

	addMesh(new Mesh(modelLoader.getVertices(), modelLoader.getIndices(), modelLoader.getColourList(), true, false, false), cfg.RIGHT);
    clearVectors();
	modelLoader.clearMaterials();
	transform.GetRot()->z += cfg.DEFAULT_ROT * 2;
	transform.GetPos()->z += 5.0f;
	clearVectors();
	modelLoader.clearMaterials();

}
void Mum::move(Player * player)
{
	float playerX = (*player).getTransform()->GetPos()->x;
	float playerY = (*player).getTransform()->GetPos()->y;

	float x = getTransform()->GetPos()->x;
	float y = getTransform()->GetPos()->y;


	if (!isProg())
	{
		updateAnimation();

		updateRandomDir();

		checkBoundaryCollides();

		defaultMovementForDir();
	}

}
