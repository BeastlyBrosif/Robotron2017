/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <ctime>

#include "../entities/Grunt.h"
#include "../graphics/Mesh.h"
#include "../Config.h"
#include "Enforcer.h"


void Enforcer::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readMTLfile("./res/enforcer/enforcer.mtl");
	modelLoader.readOBJfile("./res/enforcer/enforcer.obj");
	modelLoader.getVerticesSize();

	addMesh(new Mesh(modelLoader.getVertices(),  modelLoader.getIndices(),modelLoader.getColourList(), true, false, false), cfg.NO_DIR);

	clearVectors();

    randomOffsetX = (rand() % (cfg.ENFORCER_OFFSET * 2)) - cfg.ENFORCER_OFFSET;
    randomOffsetY = (rand() % (cfg.ENFORCER_OFFSET * 2)) - cfg.ENFORCER_OFFSET;



}
void Enforcer:: move (Player * player)
{


    float playerX = (*player).getTransform()->GetPos()->x;
    float playerY = (*player).getTransform()->GetPos()->y;

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;
    int dir = getDir();

    int offSetLimit = 30;

    float temp = pow( (x - (randomOffsetX + playerX)) ,2 )+ pow((y - (randomOffsetY + playerY)), 2);
    float distanceFromPlayer = sqrt(temp);

    //movespeed is proportional from the distance from the player
    m_moveSpeed = distanceFromPlayer/ 200;

    //change the update interval aswell to keep the animation smooth
    updateInterval = (unsigned int)(distanceFromPlayer / (200));




    if ((getTimeWithOffSet() - m_offsetChangeStartTime) > m_offsetChangeInterval)
    {
        randomOffsetX = (rand() % (cfg.ENFORCER_OFFSET * 2)) - cfg.ENFORCER_OFFSET;
        randomOffsetY = (rand() % (cfg.ENFORCER_OFFSET * 2)) - cfg.ENFORCER_OFFSET;

        m_offsetChangeStartTime = getTimeWithOffSet();
    }



    updateAnimation();



    checkIfTimeTOShoot();

    if((getTimeWithOffSet() - flyOffStartTime) > flyOffInterval) //if in the interval to check for flyoff
    {
        if((rand()%100) > (100 - cfg.ENFORCER_FLYOFF_CHANCE) || flyOffDurationStarted) // % chance to actually flyoff, or if the flyoff has already started
        {
            flyOffToEdge();//run the movement command to fly to the edge
            startFlyoffInterval(); //set up flyDuration start time and the flyOffDurationStarted bool

            if((getTimeWithOffSet() - flyDurationStartTime) > flyOffDurationInterval) //if the enforcer has used all of its duration for flyoff
            {
                flyOffStartTime = getTimeWithOffSet(); //reset the the entire interval to the start time, so the interval starts again
                flyOffDurationStarted = false; // reset the bool to false, to show the flyoff isnt happening
            }
        }
        else
        {
            flyOffStartTime = getTimeWithOffSet(); //if the rand chance failed, reset the interval for checking this
        }

    }
    else //otherwise move normalley for enforcer
    {
        if ((getTimeWithOffSet() - moveStartTime) > updateInterval) //if in the interval to move
        {
            if(x > (playerX +randomOffsetX) && (x - m_hitBoxWidth/2) > cfg.negativeXBorder) //move proportional to the distance from the player with a random offset
            {
                getTransform()->GetPos()->x -= m_moveSpeed;
            }

            if(x < (playerX +randomOffsetX) && (x + m_hitBoxWidth/2) < cfg.positiveXBorder)
            {
                getTransform()->GetPos()->x += m_moveSpeed;
            }
            if(y > (playerY +randomOffsetY) && (y - m_hitBoxHeight/2) > cfg.negativeYBorder)
            {
                getTransform()->GetPos()->y -=  m_moveSpeed;
            }
            if(y < (playerY +randomOffsetY) && (y + m_hitBoxHeight/2) < cfg.positiveYBorder)
            {
                getTransform()->GetPos()->y += m_moveSpeed;
            }
            moveStartTime = getTimeWithOffSet();

        }
    }



}
void Enforcer::flyOffToEdge()
{

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;

    if(edgeChosen == 0) //edge 0
    {
        if((y - getHitBoxHeight() / 2) > cfg.negativeYBorder) //if not hit the border, move toward the border
        {
            getTransform()->GetPos()->y -=  m_moveSpeed;



        }
            if(((x + getHitBoxWidth() / 2) < cfg.positiveXBorder) &&((x - getHitBoxWidth() / 2) > cfg.negativeXBorder)) //if not hit the opposite border, move toward the corner
            {
                if(abs(x - cfg.positiveXBorder) < abs(x - cfg.negativeXBorder)) //choose a direction to go based on which is the closest
                {
                    getTransform()->GetPos()->x +=  edgeSlideSpeed;
                }
                else
                {
                    getTransform()->GetPos()->x -=  edgeSlideSpeed;
                }
            }

    }
    if(edgeChosen == 1)
    {
        if((x - getHitBoxWidth() / 2) > cfg.negativeXBorder)
        {
            getTransform()->GetPos()->x -=  m_moveSpeed;

        }
            if(((y + getHitBoxHeight() / 2) < cfg.positiveYBorder) &&((y - getHitBoxHeight() / 2) > cfg.negativeYBorder) )
            {
                if(abs(y - cfg.positiveYBorder) < abs(y - cfg.negativeYBorder))
                {
                    getTransform()->GetPos()->y +=  edgeSlideSpeed;
                }
                else
                {
                    getTransform()->GetPos()->y -=  edgeSlideSpeed;
                }
            }

    }
    if(edgeChosen == 2)
    {
        if((y + getHitBoxHeight() / 2) < cfg.positiveYBorder)
        {
            getTransform()->GetPos()->y +=  m_moveSpeed;

        }
            if(((x + getHitBoxWidth() / 2) < cfg.positiveXBorder) &&((x - getHitBoxWidth() / 2) > cfg.negativeXBorder) )
            {
                if(abs(x - cfg.positiveXBorder) < abs(x - cfg.negativeXBorder))
                {
                    getTransform()->GetPos()->x +=  edgeSlideSpeed;
                }
                else
                {
                    getTransform()->GetPos()->x -=  edgeSlideSpeed;
                }
            }
    }
    if(edgeChosen == 3)
    {
        if((x + getHitBoxWidth() / 2) < cfg.positiveXBorder)
        {
            getTransform()->GetPos()->x +=  m_moveSpeed;

        }

            if(((y + getHitBoxHeight() / 2) < cfg.positiveYBorder) &&((y - getHitBoxHeight() / 2) > cfg.negativeYBorder) )
            {
                if(abs(y - cfg.positiveYBorder) < abs(y - cfg.negativeYBorder))
                {
                    getTransform()->GetPos()->y +=  edgeSlideSpeed;
                }
                else
                {
                    getTransform()->GetPos()->y -=  edgeSlideSpeed;
                }
            }

    }
}

void Enforcer::chooseEdge()
{
    edgeChosen = rand() % 4; //choose a random of the four edges

}
void Enforcer::startFlyoffInterval()
{
    if(flyOffDurationStarted) //if the flyoff duration is already happening, just return
    {
        return;
    }
    else //otherwise, set up the bool to show the interval is happening, set the start time for the duration to the current time, and choose and edge
    {
        flyDurationStartTime = getTimeWithOffSet();
        flyOffDurationStarted = true;
        chooseEdge();
    }
}


Enforcer::~Enforcer() {
	// TODO Auto-generated destructor stub
}



