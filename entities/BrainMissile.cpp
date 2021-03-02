#include "BrainMissile.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
void BrainMissile::init()
{


    vertexVec.push_back(glm::vec3(-1,1,0.1)); //add a square as the missile
	vertexVec.push_back(glm::vec3(-1,-1,0.1));
	vertexVec.push_back(glm::vec3(1,-1,0.1));
	vertexVec.push_back(glm::vec3(-1,1,0.1));
	vertexVec.push_back(glm::vec3(1,-1,0.1));
	vertexVec.push_back(glm::vec3(1,1,0.1));


    if(m_isHead) //if this is the head
    {
        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(1.0f,  1.0f,  1.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();


        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(1.0f,  0.0f,  0.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();

        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(0.0f,  1.0f,  0.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();


    }
    else //if its the tail
    {
        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(0.0f,  1.0f,  1.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();

        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(1.0f,  1.0f,  0.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();

        for(int i = 0; i < vertexVec.size(); i++)
        {
            colorVec.push_back(glm::vec4(1.0f,  0.0f,  1.0f, 1));
        }

        addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
        colorVec.clear();

    }


    if(m_isHead) //set up the tail segments if its the head
    {
        setUpTail(getTransform()->GetPos()->x, getTransform()->GetPos()->y);
    }



    clearVectors();
    getTransform()->GetScale()->x = scale; //set the scaling for the spark
    getTransform()->GetScale()->y = scale;
    getTransform()->GetScale()->z = scale;

}

void BrainMissile::setUpTail(float x, float y) //method to create the tail segments
{
	int tailLength = 5;
    unsigned int tailStartTime = moveStartTime;

    for(int i = 0; i < tailLength; i++)
    {
        tailStartTime += cfg.MISSILE_TAIL_DELAY; //make each tail segment start later than the previous one
        tailVec.push_back(new BrainMissile(m_playerX, m_playerY, x, y, false, (tailStartTime), m_shader, m_camera)); //add a new missile to the tail vec (cannot be shot as isnt in the enemy factory vec)

    }

}

void BrainMissile::draw(int _dir)
{
    //std::cout << "HEY" << std::endl;

    if(m_isHead) //if this is the head node, call the draw function for all of the tail nodes
    {
        for(int i = tailVec.size() - 1; i > - 1; i--)
        {
            //std::cout << "HEY" << std::endl;
            tailVec[i]->draw(cfg.NO_DIR);

        }
    }
        //update the shader, and call the Entity implementation of draw
        m_shader->Update(*getTransform(), *m_camera);
        Entity::draw(cfg.NO_DIR); //scoping to draw using the entity method for draw, to stop recursion





}

void BrainMissile::setNewCoordsIfTime(float x, float y) //will update the tail with the prevoius nodes coords, so the tail will always move towards the head
{

    if((getTimeWithOffSet() - tailUpdateStartTime) > cfg.MISSILE_TAIL_DELAY)
    {
        prevX = x;
        prevY = y;
        tailUpdateStartTime = getTimeWithOffSet();
    }
}



void BrainMissile::updateTail(Player * player) //call setNewCoordsifTime on all of the tails segments to update the target they are travelling to
{

    float tempX = getTransform()->GetPos()->x;
    float tempY = getTransform()->GetPos()->y;

    for(int i = 0; i < tailVec.size(); i++)
    {

        tailVec[i]->setNewCoordsIfTime(tempX, tempY);

        tempX = tailVec[i]->getTransform()->GetPos()->x;
        tempY = tailVec[i]->getTransform()->GetPos()->y;


        tailVec[i]->move(player); //call the move function on the tail segments
    }

}

void BrainMissile :: move(Player * player)
{


        updateAnimation();

        float x = getTransform()->GetPos()->x;
        float y = getTransform()->GetPos()->y;


        float playerX = player->getTransform()->GetPos()->x;
        float playerY = player->getTransform()->GetPos()->y;

        if(((getTimeWithOffSet() - moveStartTime) > 2))
        {

            if(m_isHead) // if the
            {
                headMovement(player);
            }
            else // movement for the tail
            {
                tailMovement();
            }

            moveStartTime = getTimeWithOffSet();
        }


        if(m_isHead) // if this is the head, update the tail
        {
            updateTail(player);
        }

    checkBoundaryCollides();

    checkIfLifeTimeOver();
}

void BrainMissile::headMovement(Player * player)
{

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;


    float playerX = player->getTransform()->GetPos()->x;
    float playerY = player->getTransform()->GetPos()->y;

    changeZigZig(); //run method to check whether the missile should be zig zagging
    if(!isZigZagging) //if not zig zagging, just move directly towards the player
    {

        dirVec.clear(); //clear the vec that keeps track of directions the missile is travelling


        if(x > playerX + 5) //+5 to provide a "deadzone" to prevent an "always diagonal"
        {
            getTransform()->GetPos()->x -= m_moveSpeed;
            dir = cfg.LEFT;
            dirVec.push_back(cfg.LEFT);
        }

        if(x < playerX - 5)
        {
            getTransform()->GetPos()->x += m_moveSpeed;
            dir = cfg.RIGHT;
            dirVec.push_back(cfg.RIGHT);
        }
        if(y > playerY + 5)
        {
            getTransform()->GetPos()->y -=  m_moveSpeed;


           if(std::find(dirVec.begin(), dirVec.end(), cfg.LEFT) != dirVec.end()) //if the missile has already moved left or right, set the diagonal movement
           {
                dir = cfg.UP_LEFT;
           }
           else if (std::find(dirVec.begin(), dirVec.end(), cfg.RIGHT) != dirVec.end())
           {
                dir = cfg.UP_RIGHT;
           }
           else
           {
                dir = cfg.UP;
           }

        }
        if(y < playerY - 5)
        {
            getTransform()->GetPos()->y += m_moveSpeed;
            if(std::find(dirVec.begin(), dirVec.end(), cfg.LEFT) != dirVec.end()) //if the missile has already moved left or right, set the diagonal movement
           {
                dir = cfg.DOWN_LEFT;
           }
           else if (std::find(dirVec.begin(), dirVec.end(), cfg.RIGHT) != dirVec.end())
           {
                dir = cfg.DOWN_RIGHT;
           }
           else
           {
                dir = cfg.DOWN;
           }
        }

    }
    else{
        zigZagMissile(); // if it is time to zig zag run the zig zag function
    }

}

void BrainMissile::tailMovement()
{

    float x = getTransform()->GetPos()->x;
    float y = getTransform()->GetPos()->y;


    if(x > prevX) //so tail follows head
    {
        getTransform()->GetPos()->x -= m_moveSpeed;
    }

    if(x < prevX)
    {
        getTransform()->GetPos()->x += m_moveSpeed;
    }
    if(y > prevY)
    {
        getTransform()->GetPos()->y -=  m_moveSpeed;
    }
    if(y < prevY)
    {
        getTransform()->GetPos()->y += m_moveSpeed;
    }

}

void BrainMissile::changeZigZig() //if isZigZagging, make it false if the interval has finished, otherwise, make it true if the chance is over the required amount
{
    int chance = rand() % 100;



    if((getTimeWithOffSet() - zigZigChangeStartTime) > cfg.MISSILE_ZIG_ZAG_INTERVAL)
    {
        dirChoice = rand() % 2; //set the  dir choise (as the zig zag has a choise of the two perpendicular directions)
        if(isZigZagging) //toggle it off if the interval has finished
        {
            isZigZagging = false;
            return;
        }

        if(chance > (100 - cfg.MISSILE_ZIG_ZIG_CHANCE)) //if the chance is over the required amount, set it to zig zag
        {
            isZigZagging = true;
        }
        else
        {
            isZigZagging = false;
        }
        zigZigChangeStartTime = getTimeWithOffSet();
    }



}

void BrainMissile::zigZagMissile() //zig zag movement accoding to the direction set
{
    if(dir == cfg.LEFT || dir == cfg.RIGHT)
    {

         if(dirChoice == 0)
         {
            getTransform()->GetPos()->y -=  m_moveSpeed;
         }
         else if(dirChoice == 1)
         {
            getTransform()->GetPos()->y += m_moveSpeed;
         }
    }
    if(dir == cfg.UP || dir == cfg.DOWN)
    {


         if(dirChoice == 0)
         {
            getTransform()->GetPos()->x -=  m_moveSpeed;
         }
         else if(dirChoice == 1)
         {
            getTransform()->GetPos()->x += m_moveSpeed;
         }
    }


    if(dir == cfg.UP_LEFT || dir == cfg.DOWN_RIGHT)
    {

         if(dirChoice == 0)
         {
            getTransform()->GetPos()->y +=  m_moveSpeed;
            getTransform()->GetPos()->x -=  m_moveSpeed;
         }
         else if(dirChoice == 1)
         {
            getTransform()->GetPos()->y -= m_moveSpeed;
            getTransform()->GetPos()->x +=  m_moveSpeed;
         }
    }

    if(dir == cfg.UP_RIGHT || dir == cfg.DOWN_LEFT)
    {

         if(dirChoice == 0)
         {
            getTransform()->GetPos()->y -=  m_moveSpeed;
            getTransform()->GetPos()->x -=  m_moveSpeed;
         }
         else if(dirChoice == 1)
         {
            getTransform()->GetPos()->y += m_moveSpeed;
            getTransform()->GetPos()->x +=  m_moveSpeed;
         }
    }


}
bool BrainMissile::checkBoundaryCollides() //check if the missile hits the boubdaries, if so, delete it
{
    if(getTransform()->GetPos()->y <= cfg.negativeYBorder || getTransform()->GetPos()->y >= cfg.positiveYBorder)
    {
        SetEntityToDestroyed();
        return true;
    }
    else if (getTransform()->GetPos()->x <= cfg.negativeXBorder || getTransform()->GetPos()->x >= cfg.positiveXBorder)
    {
        SetEntityToDestroyed();
        return true;
    }
    return false;
}


