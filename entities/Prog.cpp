#include "Prog.h"

void Prog::init()
{
    ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/son/STILL.mtl");
	modelLoader.readOBJfile("./res/son/STILL.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.0f,  0.1f,  0.8f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.NO_DIR);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/DOWN1.mtl");
	modelLoader.readOBJfile("./res/son/DOWN1.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.0f,  0.1f,  0.8f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/DOWN2.mtl");
	modelLoader.readOBJfile("./res/son/DOWN2.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(1.0f,  0.5f,  0.3f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/DOWN3.mtl");
	modelLoader.readOBJfile("./res/son/DOWN3.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.5f,  0.1f,  0.8f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.DOWN);
    modelLoader.clearMaterials();


    modelLoader.readMTLfile("./res/son/UP1.mtl");
	modelLoader.readOBJfile("./res/son/UP1.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.0f,  0.1f,  0.8f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.UP);
    modelLoader.clearMaterials();


    modelLoader.readMTLfile("./res/son/UP2.mtl");
	modelLoader.readOBJfile("./res/son/UP2.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(1.0f,  0.5f,  0.3f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.UP);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/UP3.mtl");
	modelLoader.readOBJfile("./res/son/UP3.obj");
	clearVectors();
	for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.5f,  0.1f,  0.8f, 1));
	}

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.UP);
    modelLoader.clearMaterials();
    modelLoader.readMTLfile("./res/son/LEFT1.mtl");
    modelLoader.readOBJfile("./res/son/LEFT1.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.0f,  0.1f,  0.8f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/LEFT2.mtl");
    modelLoader.readOBJfile("./res/son/LEFT2.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(1.0f,  0.5f,  0.3f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();
    modelLoader.readMTLfile("./res/son/LEFT3.mtl");
    modelLoader.readOBJfile("./res/son/LEFT3.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.5f,  0.1f,  0.8f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.LEFT);
    modelLoader.clearMaterials();


    modelLoader.readMTLfile("./res/son/RIGHT1.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT1.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.0f,  0.1f,  0.8f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();
    modelLoader.readMTLfile("./res/son/RIGHT2.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT2.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(1.0f,  0.5f,  0.3f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();

    modelLoader.readMTLfile("./res/son/RIGHT3.mtl");
    modelLoader.readOBJfile("./res/son/RIGHT3.obj");
    clearVectors();
    for(int i = 0; i < modelLoader.getVerticesSize();i++)
	{
        colorVec.push_back(glm::vec4(0.5f,  0.1f,  0.8f, 1));
	}

    addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),colorVec, true, false, false), cfg.RIGHT);
    modelLoader.clearMaterials();


	clearVectors();
	modelLoader.clearMaterials();
	//transform.GetRot()->z += cfg.DEFAULT_ROT * 2; //for the son textures this must be done for some reason, otherwise they display wierdly
    transform.GetPos()->z += 1.5f; //push backward
}
void Prog::move(Player * player)
{



    seekPlayer(player);



    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;

    int leeWay = 20;
    int dirSelect = 0;

    if((getTimeWithOffSet() - progStartTime) > progDelay) //the prog's movement is delayed while it is being "created"
    {
        updateAnimation();


        if (getTimeWithOffSet() - moveStartTime > updateInterval) //move towards player, needs to be improved
        {

           /* if ((m_currentTime - dirChangeStartTime) > dirUpdateInterval)
            {
                if(abs(x - m_seekedPlayerX) > abs(y - m_seekedPlayerY)) //select horizontal or vertical based on the distance from player
                {
                    dirSelect = 0;
                }
                else
                {
                    dirSelect = 1;
                }
                dirChangeStartTime = m_currentTime;
            }*/

            if(x < m_seekedPlayerX + leeWay && x > m_seekedPlayerX - leeWay)
            {
                dirSelect = 1;
            }

            if(y < m_seekedPlayerY + leeWay && y > m_seekedPlayerY - leeWay)
            {
                dirSelect = 0;
            }



            if(dirSelect == 0)
            {
                if(x > m_seekedPlayerX)
                {
                dir = cfg.LEFT;
                    getTransform()->GetPos()->x -= m_moveSpeed;
                }

                else if(x < m_seekedPlayerX)
                {
                    dir = cfg.RIGHT;
                    getTransform()->GetPos()->x += m_moveSpeed;
                }

            }


            if (dirSelect == 1)
            {
                if(y >= m_seekedPlayerY )
                {
                    dir = cfg.UP;
                    getTransform()->GetPos()->y -=  m_moveSpeed;
                }
                else if(y <= m_seekedPlayerY)
                {
                    dir = cfg.DOWN;
                    getTransform()->GetPos()->y += m_moveSpeed;
                }

            }


            moveStartTime = getTimeWithOffSet();
        }
    }

}

void Prog::seekPlayer(Player * player)
{
    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;

    if(((getTimeWithOffSet() - m_playerSeekStartTime) > m_playerSeekInterval))
    {
        m_seekedPlayerX = player->getTransform()->GetPos()->x;
        m_seekedPlayerY = player->getTransform()->GetPos()->y;


        m_playerSeekStartTime = getTimeWithOffSet();
    }
}
