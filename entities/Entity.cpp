/*
 * Entity.cpp
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */

#include "Entity.h"
#include <cstdio>

void Entity::checkIfLifeTimeOver()
{
    if((getTimeWithOffSet() - m_lifeTimeStart) > m_LifeTime) //if the missile has used its lifetime set it to deleted
    {
        SetEntityToDestroyed();
    }
}


void Entity::addOffsetToEntities(unsigned int increment)
{
    m_timeOffset += increment;
}

void Entity::updateAnimation()
{

    if ((getTimeWithOffSet() - animationStartTime) > animationInterval)
    {
        nextMesh(dir);
        animationStartTime = getTimeWithOffSet();
    }
}

void Entity::updateRandomDir()
{

    if ((getTimeWithOffSet() - dirChangeStartTime) > dirUpdateInterval)
    {
        setDir(rand() % (cfg.NUM_DIRECTIONS - 4));
        dirChangeStartTime = getTimeWithOffSet();
    }
}

bool Entity::checkBoundaryCollides()
{
    float halfHitBoxWidth = m_hitBoxWidth / 2;
    float halfHitBoxHeight = m_hitBoxHeight / 2;

    float x = transform.GetPos()->x;
    float y = transform.GetPos()->y;

    if((x + halfHitBoxWidth) >= cfg.positiveXBorder)
    {
        setDir(cfg.RIGHT);
        return true;
    }
    if((x - halfHitBoxWidth) <= cfg.negativeXBorder)
    {
       setDir(cfg.LEFT);
       return true;
    }
    if((y + halfHitBoxHeight) >= cfg.positiveYBorder)
    {
       setDir(cfg.DOWN);
       return true;
    }
    if((y - halfHitBoxHeight) <= cfg.negativeYBorder)
    {
        setDir(cfg.UP);
        return true;
    }

    return false;
}

void Entity::defaultMovementForDir()
{

    if ((getTimeWithOffSet() - moveStartTime) > updateInterval)
    {
        if(dir == cfg.RIGHT)
        {
            getTransform()->GetPos()->x -= m_moveSpeed;
        }

        if(dir == cfg.LEFT)
        {
            getTransform()->GetPos()->x +=m_moveSpeed;
        }
        if(dir == cfg.DOWN)
        {
            getTransform()->GetPos()->y -=m_moveSpeed;
        }
        if(dir == cfg.UP)
        {
            getTransform()->GetPos()->y +=m_moveSpeed;
        }
        if(dir == cfg.UP_RIGHT)
        {
            getTransform()->GetPos()->x -= m_moveSpeed;
            getTransform()->GetPos()->y += m_moveSpeed;
        }
        if(dir == cfg.UP_LEFT)
        {
            getTransform()->GetPos()->x += m_moveSpeed;
            getTransform()->GetPos()->y += m_moveSpeed;
        }
        if(dir == cfg.DOWN_RIGHT)
        {
            getTransform()->GetPos()->x -= m_moveSpeed;
            getTransform()->GetPos()->y -=m_moveSpeed;
        }
        if(dir == cfg.DOWN_LEFT)
        {
            getTransform()->GetPos()->x += m_moveSpeed;
            getTransform()->GetPos()->y -= m_moveSpeed;
        }
        moveStartTime = getTimeWithOffSet();

        }

}


int Entity::getScoreValue()
{
    return scoreValue;
}


float Entity::getScale()
{
	return scale;
}


float Entity::getAnimationInterval()
{
	return animationInterval;
}

void Entity::setAnimationInterval(float _interval)
{
	animationInterval = _interval;

}
void Entity::setSpeed(float _speed)
{
	m_moveSpeed = _speed;
}

float Entity::getSpeed()
{
	return m_moveSpeed;
}

float Entity::getDirUpdateInterval()
{
	return dirUpdateInterval;
}
unsigned int * Entity::getDirChangeStartTime()
{
	return &dirChangeStartTime;
}

int Entity::getEntityType()
{
	return entityType;
}
unsigned int * Entity::getMoveStartTime()
{

	return &moveStartTime;

}
unsigned int * Entity::getAnimationStartTime()
{

	return &animationStartTime;

}

float Entity::getUpdateInterval()
{
	return updateInterval;
}
int Entity::getDir()
{
	return dir;


}

void Entity::setDir(int _dir)
{
	dir = _dir;
}

void Entity::clearVectors()
{
	vertexVec.clear();
	colorVec.clear();
	indexVec.clear();

}

vector<glm::vec3> Entity:: getVertices()
{
 return vertexVec;
}
vector<glm::vec4> Entity::getColors()
{
	return colorVec;
}

Transform* Entity::getTransform()
{
	return &transform;
}


void Entity::draw(int dir) //draws the current mesh for the direction specified
{


    if(dir == cfg.NO_DIR)
    {
         (*meshVec[currentMesh]).Draw();
    }
    if(dir == cfg.UP)
    {
        (*meshVecUp[currentUpMesh]).Draw();
    }
    else if (dir == cfg.DOWN)
    {

        (*meshVecDown[currentDownMesh]).Draw();
    }
    else if (dir == cfg.LEFT || dir == cfg.UP_LEFT || dir == cfg.DOWN_LEFT)
    {

        (*meshVecLeft[currentLeftMesh]).Draw();
    }
    else if (dir == cfg.RIGHT|| dir == cfg.UP_RIGHT || dir == cfg.DOWN_RIGHT)
    {

        (*meshVecRight[currentRightMesh]).Draw();
    }

}
void Entity::init()
{

}
Entity::Entity() {

	usesIndices = false;
	//init();
	currentMesh = 0;
	currentUpMesh = 0;
	currentDownMesh = 0;
	currentLeftMesh = 0;
	currentRightMesh = 0;


}

void Entity::addMesh(Mesh * mesh, int dir) //adds a mesh for the direction specified
{

    if(dir == cfg.NO_DIR)
    {
        meshVec.push_back(mesh);
    }


    if(dir == cfg.UP)
    {
        meshVecUp.push_back(mesh);
    }
    else if (dir == cfg.DOWN)
    {

        meshVecDown.push_back(mesh);
    }
    else if (dir == cfg.LEFT)
    {
        meshVecLeft.push_back(mesh);

    }
    else if (dir == cfg.RIGHT)
    {
        meshVecRight.push_back(mesh);

    }
}


void Entity::nextMesh(int dir) //changes to the next mesh for the specified direction
{

if (dir == cfg.NO_DIR)
{
    if(currentMesh < meshVec.size()-1)
    {
        currentMesh++;
    }
    else
    {
        currentMesh = 0;
    }

}
if (dir == cfg.UP)
{
    if(currentUpMesh < meshVecUp.size()-1)
    {
        currentUpMesh++;
    }
    else
    {
        currentUpMesh = 0;
    }

}
else if (dir == cfg.DOWN)
{
    if(currentDownMesh < meshVecDown.size()-1)
    {
        currentDownMesh++;
    }
    else
    {
        currentDownMesh = 0;
    }


}
else if (dir == cfg.LEFT || dir == cfg.UP_LEFT || dir == cfg.DOWN_LEFT)
{
    if(currentLeftMesh < meshVecLeft.size()-1)
    {
        currentLeftMesh++;
    }
    else
    {
        currentLeftMesh = 0;
    }

}
else if (dir == cfg.RIGHT|| dir == cfg.UP_RIGHT || dir == cfg.DOWN_RIGHT)
{
    if(currentRightMesh < meshVecRight.size()-1)
    {
        currentRightMesh++;
    }
    else
    {
        currentRightMesh = 0;
    }

}

}
Entity::~Entity()
{

	for (auto p : meshVec)
	{
		delete p;
	}
	for (auto p : meshVecLeft)
	{
		delete p;
	}
	for (auto p : meshVecRight)
	{
		delete p;
	}
	for (auto p : meshVecUp)
	{
		delete p;
	}
	for (auto p : meshVecDown)
	{
		delete p;
	}
}

