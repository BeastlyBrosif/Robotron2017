#include "Dad.h"
void Dad::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/dad/DadDown1ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadDown1ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);



    modelLoader.readMTLfile("./res/dad/DadUp1ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadUp1ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);

    modelLoader.readMTLfile("./res/dad/DadUp2ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadUp2ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);


    modelLoader.readMTLfile("./res/dad/DadUp3ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadUp3ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.UP);



    modelLoader.readMTLfile("./res/dad/DadDown1ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadDown1ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);

    modelLoader.readMTLfile("./res/dad/DadDown2ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadDown2ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);


    modelLoader.readMTLfile("./res/dad/DadDown3ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadDown3ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.DOWN);



    modelLoader.readMTLfile("./res/dad/DadLeft1ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadLeft1ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);

    modelLoader.readMTLfile("./res/dad/DadLeft2ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadLeft2ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);


    modelLoader.readMTLfile("./res/dad/DadLeft3ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadLeft3ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.LEFT);


    modelLoader.readMTLfile("./res/dad/DadRight1ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadRight1ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);

    modelLoader.readMTLfile("./res/dad/DadRight2ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadRight2ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);


    modelLoader.readMTLfile("./res/dad/DadRight3ColourModel.mtl");
	modelLoader.readOBJfile("./res/dad/DadRight3ColourModel.obj");
	clearVectors();
	modelLoader.clearMaterials();
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.RIGHT);




    transform.GetRot()->z += cfg.DEFAULT_ROT * 2; //for the dad textures this must be done for some readad, otherwise they display wierdly
    transform.GetPos()->z += 5.0f; //bring forward
	clearVectors();
	modelLoader.clearMaterials();

}
void Dad:: move (Player * player)
{

    m_currentTime = SDL_GetTicks();
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
