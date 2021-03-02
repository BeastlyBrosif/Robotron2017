#include "ProgTransformer.h"

void ProgTransformer::init()
{
    vertexVec.push_back(glm::vec3(-2,3,0.1));
	vertexVec.push_back(glm::vec3(-2,-3,0.1));
	vertexVec.push_back(glm::vec3(2,-3,0.1));
	vertexVec.push_back(glm::vec3(-2,3,0.1));
	vertexVec.push_back(glm::vec3(2,-3,0.1));
	vertexVec.push_back(glm::vec3(2,3,0.1));


	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.0f,  1.0f, 1));

	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.UP);
	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.DOWN);
    clearVectors();


    vertexVec.push_back(glm::vec3(-2,3,0.1));
	vertexVec.push_back(glm::vec3(-2,-3,0.1));
	vertexVec.push_back(glm::vec3(2,-3,0.1));
	vertexVec.push_back(glm::vec3(-2,3,0.1));
	vertexVec.push_back(glm::vec3(2,-3,0.1));
	vertexVec.push_back(glm::vec3(2,3,0.1));


	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));
	colorVec.push_back(glm::vec4(0.5f,  0.5f,  1.0f, 1));

	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.UP);
	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.DOWN);
    clearVectors();

    getTransform()->GetRot()->x -= cfg.DEFAULT_ROT; //the enemy factory class will rotate the other way, as this is already in the right plane, need to counteract its rotation

}

void ProgTransformer::move(Player * player)
{

    updateAnimation();

    if((getTimeWithOffSet() - m_progTransformerStartTime) > m_progTransformerDuration) //if the prog transformer has been on the screen for the amount of time it takes to make a prog, delete it
    {
        SetEntityToDestroyed();
    }


    shake();


}

void ProgTransformer::shake()
{


    if((getTimeWithOffSet() - moveStartTime) > updateInterval)
    {
        if(dir == cfg.UP)
        {
            getTransform()->GetPos()->y += m_moveSpeed;
        }
        else if(dir == cfg.DOWN)
        {
            getTransform()->GetPos()->y -= m_moveSpeed;
        }

        moveStartTime = getTimeWithOffSet();
    }






    if((getTimeWithOffSet() - dirChangeStartTime) > dirUpdateInterval)
    {
        if(dir == cfg.UP)
        {
            setDir(cfg.DOWN);
        }
        else if (dir == cfg.DOWN)
        {
            setDir(cfg.UP);
        }
        dirChangeStartTime = getTimeWithOffSet();

    }



}
