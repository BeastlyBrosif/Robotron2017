#include "FamilyFactory.h"



/*
 * Enemyfactory.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#include <vector>

#include "../Config.h"
#include "../entities/Son.h"
#include "../entities/Dad.h"
#include "../entities/Mum.h"

#include "../wordBuilder/WordBuilder.h"


vector<WordBuilder * > familyWordScoreVec;

void FamilyFactory::addOffsetToObjects(unsigned int increment)
{

    for(int i = 0; i < entityVec.size();i++)
    {
        entityVec[i]->addOffsetToEntities(increment);
    }
}


bool FamilyFactory::checkPlayerCollide(Player * player, Family * entity) //check if the player and enemy hitboxes overlap
{


    float entityWidth = entity->getHitBoxWidth();
    float entityHeight = entity->getHitBoxHeight();
    float entityX = entity->getTransform()->GetPos()->x;
    float entityY = entity->getTransform()->GetPos()->y;

    float playerX = player->getTransform()->GetPos()->x;
    float playerY = player->getTransform()->GetPos()->y;

    float playerWidth = player->getHitBoxWidth();

    float playerHeight = player->getHitBoxHeight();

    float playerLeft = playerX + (playerWidth / 2);
    float playerRight = playerX - (playerWidth / 2);;
    float playerTop = playerY + (playerHeight / 2);
    float playerBottom = playerY - (playerHeight / 2);

    float entityLeft = entityX + (entityWidth / 2);
    float entityRight = entityX - (entityWidth / 2);
    float entityTop = entityY + (entityHeight / 2);
    float entityBottom = entityY - (entityHeight / 2);




   if(((playerLeft <= entityLeft) && (playerLeft >= entityRight)) || ((playerRight <= entityLeft) && (playerRight >= entityRight)) )
    {
        if(((playerBottom >= entityBottom) && (playerBottom <= entityTop)) || ((playerTop >= entityBottom) && (playerTop <= entityTop)) )
        {


            player->increaseScore(entity->getScoreValue());
            Mix_PlayChannel(-1,saveFamilySound, 0);
            familyWordScoreVec.push_back(new WordBuilder(std::to_string(entity->getScoreValue()),cfg.ENEMY_SCORE_WORD_SCALE,20,wordColor,entityX,entityY,1000));

            entity->SetEntityToDestroyed();
            return true;
        }
    }

    if(((entityLeft <= playerLeft) && (entityLeft >= playerRight)) || ((entityRight <= playerLeft) && (entityRight >= playerRight)) )
    {
        if(((entityBottom >= playerBottom) && (entityBottom <= playerTop)) || ((entityTop >= playerBottom) && (entityTop <= playerTop)) )
        {

            player->increaseScore(entity->getScoreValue());
            Mix_PlayChannel(-1,saveFamilySound, 0);
            familyWordScoreVec.push_back(new WordBuilder(std::to_string(entity->getScoreValue()),cfg.ENEMY_SCORE_WORD_SCALE,20,wordColor,entityX,entityY,1000));

            entity->SetEntityToDestroyed();
            return true;
        }

    }
		return false;
}


void FamilyFactory::setScaling()
{
	for(unsigned int i = 0; i < entityVec.size(); i++)
	{
		(*entityVec[i]).getTransform()->GetScale()->x = (*entityVec[i]).getScale();
		(*entityVec[i]).getTransform()->GetScale()->y = (*entityVec[i]).getScale();
		(*entityVec[i]).getTransform()->GetScale()->z = (*entityVec[i]).getScale();
	}
}
void FamilyFactory::setScalingForLast()
{
    (*entityVec[entityVec.size() - 1]).getTransform()->GetScale()->x = (*entityVec[entityVec.size() - 1]).getScale();
    (*entityVec[entityVec.size() - 1]).getTransform()->GetScale()->y = (*entityVec[entityVec.size() - 1]).getScale();
    (*entityVec[entityVec.size() - 1]).getTransform()->GetScale()->z = (*entityVec[entityVec.size() - 1]).getScale();

}

void FamilyFactory::createEntity(int Enemy, float x, float y, int amount)
{


	if(x != cfg.FACTORY_ROUGE_VALUE || y != cfg.FACTORY_ROUGE_VALUE) //Not NULL, make one enemy in this x and y loaction
	{

		if(Enemy == cfg.SON)
		{
			entityVec.push_back(new Son(x, y));
        }
        if (Enemy == cfg.DAD)
        {
            entityVec.push_back(new Dad(x, y));
        }
        if (Enemy == cfg.MUM)
        {
            entityVec.push_back(new Mum(x, y));
        }

		(*entityVec[entityVec.size() - 1]).getTransform()->GetRot()->x += cfg.DEFAULT_ROT;
		setScalingForLast();
	}
	else //if is NULL, generate a random x and y and create the enemyies there
	{
		for (unsigned int i = 0; i < amount; i++)
		{
			float randX = (float)(rand() % (int)(cfg.positiveXBorder * 2) + (cfg.negativeXBorder));
			float randY = (float)(rand() % (int)(cfg.positiveYBorder * 2) + (cfg.negativeYBorder));

			if (Enemy == cfg.SON)
			{
				entityVec.push_back(new Son(randX, randY));
			}
			if (Enemy == cfg.DAD)
			{
				entityVec.push_back(new Dad(randX, randY));
			}
            if (Enemy == cfg.MUM)
            {
                entityVec.push_back(new Mum(randX, randY));
            }

			(*entityVec[entityVec.size() - 1]).getTransform()->GetRot()->x += cfg.DEFAULT_ROT;
            setScalingForLast();
		}
	}
}

void FamilyFactory::updateText(Shader * texShader, Camera * camera)
{

    texShader->Bind();
    for(unsigned int i = 0; i < familyWordScoreVec.size();i++)
    {
        if(!familyWordScoreVec[i]->update(texShader, camera)) //update returns false if the word has used all of its time
        {
            delete familyWordScoreVec[i];
            familyWordScoreVec.erase(familyWordScoreVec.begin() + i);
        }
    }
}


void FamilyFactory::update(Camera * camera, Shader * shader,Shader * texShader, Player * player)
{

	float x;
	float y;
	float playerX;
	float playerY;
	int dir;
	unsigned int currentTime;

	for(unsigned int i = 0; i < entityVec.size(); i++)
	{

		currentTime = SDL_GetTicks();
		x = entityVec[i]->getTransform()->GetPos()->x;
		y = entityVec[i]->getTransform()->GetPos()->y;
		playerX = player->getTransform()->GetPos()->x;
		playerY = player->getTransform()->GetPos()->y;
        dir = (*entityVec[i]).getDir();



		checkPlayerCollide(player, entityVec[i]);


		(*shader).Bind();
		//check if the enemy was killed

        if(!m_isPaused)
        {
            (*entityVec[i]).move(player); //move the entity to thier new position
        }


		(*shader).Update((*(*entityVec[i]).getTransform()), *camera); //update the enemy in the shader and then draw the mesh



            entityVec[i]->draw(dir); //draw, make sure you have loaded a mesh for every dir you intend to draw!



		if ((*entityVec[i]).getDestoryedState() == true) //the enemy has been destroyed, remove it from the vector
		{
            delete entityVec[i];
			entityVec.erase(entityVec.begin() + i);
		}

	}
	texShader->Bind();
	updateText(texShader, camera);
}


