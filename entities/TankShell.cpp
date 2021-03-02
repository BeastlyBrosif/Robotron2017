#include "TankShell.h"
#include <cstdio>
#include <iostream>
void TankShell::init()
{


    ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/tankShell/p1.mtl");
	modelLoader.readOBJfile("./res/tankShell/p1.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/tankShell/p2.mtl");
	modelLoader.readOBJfile("./res/tankShell/p2.obj");
	//addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR); //this was on the wrong plane so doesnt draw the same as the others
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/tankShell/p3.mtl");
	modelLoader.readOBJfile("./res/tankShell/p3.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/tankShell/p4.mtl");
	modelLoader.readOBJfile("./res/tankShell/p4.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();



    getTransform()->GetRot()->x -= cfg.DEFAULT_ROT;

    getTransform()->GetScale()->x = scale; //set the scaling for the spark
    getTransform()->GetScale()->y = scale;
    getTransform()->GetScale()->z = scale;
    float sparkX = getTransform()->GetPos()->x;
    float sparkY = getTransform()->GetPos()->y;



    float xDisplacement = m_playerX - sparkX;
    float yDisplacement = m_playerY - sparkY;

    m_ratio = xDisplacement / yDisplacement;


    m_moveDisX = xDisplacement / 60; //set the speed to be proportional to the displacement from the player

    m_moveDisY = yDisplacement / 60;


}

void TankShell :: move(Player * player)
{



    updateAnimation();

    if((getTimeWithOffSet() - moveStartTime) > updateInterval)
    {
        getTransform()->GetPos()->x = getTransform()->GetPos()->x + m_moveDisX;
        getTransform()->GetPos()->y = getTransform()->GetPos()->y + m_moveDisY;

        moveStartTime = getTimeWithOffSet();
    }


    checkBoundaryCollides();


    checkIfLifeTimeOver();
}

bool TankShell::checkBoundaryCollides()
{
    if(getTransform()->GetPos()->y <= cfg.negativeYBorder || getTransform()->GetPos()->y >= cfg.positiveYBorder)
    {
        m_moveDisY = -m_moveDisY;
        return true;
    }
    else if (getTransform()->GetPos()->x <= cfg.negativeXBorder || getTransform()->GetPos()->x >= cfg.positiveXBorder)
    {
        m_moveDisX = -m_moveDisX;
        return true;
    }
    return false;
}


