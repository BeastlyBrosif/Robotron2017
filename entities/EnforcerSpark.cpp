#include "EnforcerSpark.h"
#include <cstdio>
void EnforcerSpark::init()
{

    ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/enforcerSpark/p9.mtl");
	modelLoader.readOBJfile("./res/enforcerSpark/p9.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/enforcerSpark/p10.mtl");
	modelLoader.readOBJfile("./res/enforcerSpark/p10.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/enforcerSpark/p11.mtl");
	modelLoader.readOBJfile("./res/enforcerSpark/p11.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/enforcerSpark/p12.mtl");
	modelLoader.readOBJfile("./res/enforcerSpark/p12.obj");
	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();


    getTransform()->GetRot()->x -= cfg.DEFAULT_ROT;


    float sparkX = getTransform()->GetPos()->x;
    float sparkY = getTransform()->GetPos()->y;


    float randomOffsetX = (rand() % 101) - 50;
    float randomOffsetY = (rand() % 101) - 50;


    float xDisplacement = (m_playerX - sparkX) + randomOffsetX;
    float yDisplacement = (m_playerY - sparkY) + randomOffsetY;

    m_ratio = xDisplacement / yDisplacement;

    m_moveDisX = xDisplacement / 30; //set the speed to be proportional to the displacement from the player

    m_moveDisY = yDisplacement / 30;

    //some of this isnt currently used, needs improvements
    int chance = rand() % 100;
    if(chance < 20)
    {
        xCurve = true;
        randomCurve = (rand() % 10) / 10;

    }


}

void EnforcerSpark :: move(Player * player)
{



    checkBoundaryCollides();


    checkIfLifeTimeOver();

    updateAnimation();
    float sparkX = getTransform()->GetPos()->x;
    float sparkY = getTransform()->GetPos()->y;


    float width = getHitBoxWidth();
    float height = getHitBoxHeight();
    if((getTimeWithOffSet() - moveStartTime) > updateInterval)
    {
        getTransform()->GetPos()->x = getTransform()->GetPos()->x + m_moveDisX;
        getTransform()->GetPos()->y = getTransform()->GetPos()->y + m_moveDisY;

        moveStartTime = getTimeWithOffSet();
    }




}

bool EnforcerSpark::checkBoundaryCollides()
{
    float width = getHitBoxWidth();
    float height = getHitBoxHeight();
    if(getTransform()->GetPos()->y - (height / 2) <= cfg.negativeYBorder) //if its hits any of the edges, make it slide across the edge
    {
       m_moveDisY = 0;

    }
    if (getTransform()->GetPos()->y + (height / 2)>= cfg.positiveYBorder)
    {
        m_moveDisY = 0;

    }
    if (getTransform()->GetPos()->x - (width / 2)<= cfg.negativeXBorder)
    {
        m_moveDisX = 0;

    }
    if (getTransform()->GetPos()->x + (width / 2)>= cfg.positiveXBorder)
    {
        m_moveDisX = 0;

    }
    return false;
}
