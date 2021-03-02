/*
 * Enemyfactory.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */

#include <vector>
#include "../factory/EnemyFactory.h"

#include "../Config.h"
#include "../entities/Grunt.h"
#include "../entities/Hulk.h"
#include "../entities/Electrode.h"
#include "../entities/Enforcer.h"
#include "../entities/Bullet.h"
#include "../entities/Tank.h"
#include "../entities/Brain.h"
#include "../entities/Prog.h"
#include "../wordBuilder/WordBuilder.h"
#include "../entities/EnforcerSpark.h"
#include "../entities/TankShell.h"
#include "../entities/ProgTransformer.h"
#include "../entities/BrainMissile.h"
#include "../entities/Spheroid.h"

void EnemyFactory::addOffsetToObjects(unsigned int increment)
{

    for(int i = 0; i < enemyVec.size();i++)
    {
        enemyVec[i]->addOffsetToEntities(increment);
    }
}

void EnemyFactory::createProgs() //if the fmaily member has been set to a prog, destroy it and create a prog
{

float familyX;
float familyY;

    for(int i = 0; i < familyVec->size();i++)
    {
        familyX = familyVec->at(i)->getTransform()->GetPos()->x;
        familyY = familyVec->at(i)->getTransform()->GetPos()->y;

        if(familyVec->at(i)->isProg())
        {
            familyVec->at(i)->SetEntityToDestroyed();
            createEntity(cfg.PROG,familyX, familyY, 1);
            createEntity(cfg.PROG_TRANSFORMER, familyX, familyY,1);
        }
    }
}


bool EnemyFactory::checkEnemyKilled(Enemy * enemy, Player * player)
{

    float enemyWidth = enemy->getHitBoxWidth();
    float enemyHeight = enemy->getHitBoxHeight();
    float enemyX = enemy->getTransform()->GetPos()->x;
    float enemyY = enemy->getTransform()->GetPos()->y;

    float enemyLeft = enemyX + (enemyWidth / 2);
    float enemyRight = enemyX - (enemyWidth / 2);
    float enemyTop = enemyY + (enemyHeight / 2);
    float enemyBottom = enemyY - (enemyHeight / 2);


    float bulletX;
    float bulletY;
    float bulletWidth;
    float bulletHeight;
    float bulletLeft;
    float bulletRight;
    float bulletBottom;
    float bulletTop;

    for (unsigned int i = 0; i < bulletVec->size(); i++)
	{

        bulletX = bulletVec->at(i)->getTransform()->GetPos()->x;
        bulletY = bulletVec->at(i)->getTransform()->GetPos()->y;
        bulletWidth = bulletVec->at(i)->getHitBoxWidth();
        bulletHeight = bulletVec->at(i)->getHitBoxHeight();
        bulletLeft = bulletX + (bulletWidth / 2);
        bulletRight = bulletX - (bulletWidth / 2);
        bulletTop = bulletY + (bulletHeight / 2);
        bulletBottom = bulletY - (bulletHeight / 2);


        //check the hitboxes both ways around

        if(((bulletLeft <= enemyLeft) && (bulletLeft >= enemyRight)) || ((bulletRight <= enemyLeft) && (bulletRight >= enemyRight)) )
        {
            if(((bulletBottom >= enemyBottom) && (bulletBottom <= enemyTop)) || ((bulletTop >= enemyBottom) && (bulletTop <= enemyTop)) )
            {
                    player->increaseScore(enemy->getScoreValue());
                    bulletVec->at(i)->bulletHasHit();
                    bulletVec->at(i)->setBulletToDeleted();
                    enemy->setHasBeenShotDir(bulletVec->at(i)->getDir());
                    if(enemy->getEntityType() != cfg.HULK)
                    {
                        wordScoreVec.push_back(new WordBuilder(to_string((enemy)->getScoreValue()),cfg.ENEMY_SCORE_WORD_SCALE,20,wordColor,enemyX, enemyY, cfg.SCORE_ON_SCREEN_INTERVAL)); //add a new score to be displayed to the screen
                        (enemy)->SetEntityToDestroyed(); //set the enemy's flag to indicate that it is destroyed
                    }
                    return true;
            }
        }


		if(((enemyLeft <= bulletLeft) && (enemyLeft >= bulletRight)) || ((enemyRight <= bulletLeft) && (enemyRight >= bulletRight)) )
        {
            if(((enemyBottom >= bulletBottom) && (enemyBottom <= bulletTop)) || ((enemyTop >= bulletBottom) && (enemyTop <= bulletTop)) )
            {
                player->increaseScore(enemy->getScoreValue());
                bulletVec->at(i)->bulletHasHit();
                bulletVec->at(i)->setBulletToDeleted();
                enemy->setHasBeenShotDir(bulletVec->at(i)->getDir());

                if(enemy->getEntityType() != cfg.HULK)
                {
                    wordScoreVec.push_back(new WordBuilder(to_string((enemy)->getScoreValue()),cfg.ENEMY_SCORE_WORD_SCALE,20,wordColor,enemyX, enemyY, cfg.SCORE_ON_SCREEN_INTERVAL)); //add a new score to be displayed to the screen
                    (enemy)->SetEntityToDestroyed(); //set the enemy's flag to indicate that it is destroyed
                }



                return true;
            }

        }
	}

	return false;
}



bool EnemyFactory::checkFamilyCollide(Enemy * enemy, Player * player)
{

    float enemyWidth = enemy->getHitBoxWidth();
    float enemyHeight = enemy->getHitBoxHeight();
    float enemyX = enemy->getTransform()->GetPos()->x;
    float enemyY = enemy->getTransform()->GetPos()->y;

    float enemyLeft = enemyX + (enemyWidth / 2);
    float enemyRight = enemyX - (enemyWidth / 2);
    float enemyTop = enemyY + (enemyHeight / 2);
    float enemyBottom = enemyY - (enemyHeight / 2);

    float familyX;
    float familyY;
    float familyWidth;
    float familyHeight;
    float familyLeft;
    float familyRight;
    float familyBottom;
    float familyTop;

    for (unsigned int i = 0; i < familyVec->size(); i++)
	{

        familyX = familyVec->at(i)->getTransform()->GetPos()->x;
        familyY = familyVec->at(i)->getTransform()->GetPos()->y;
        familyWidth = familyVec->at(i)->getHitBoxWidth();
        familyHeight = familyVec->at(i)->getHitBoxHeight();
        familyLeft = familyX + (familyWidth / 2);
        familyRight = familyX - (familyWidth / 2);
        familyTop = familyY + (familyHeight / 2);
        familyBottom = familyY - (familyHeight / 2);

        //check the hitboxes both ways around


        if(((familyLeft <= enemyLeft) && (familyLeft >= enemyRight)) || ((familyRight <= enemyLeft) && (familyRight >= enemyRight)) )
        {
            if(((familyBottom >= enemyBottom) && (familyBottom <= enemyTop)) || ((familyTop >= enemyBottom) && (familyTop <= enemyTop)) )
            {


                    if(enemy->getEntityType() == cfg.HULK)
                    {
                        familyVec->at(i)->SetEntityToDestroyed();
                    }
                    else if(enemy->getEntityType() == cfg.BRAIN)
                    {
                        familyVec->at(i)->setToProg();
                        (dynamic_cast<Brain*> (enemy))->makingProg(); //cast to the Brain type to get the makingProg method

                    }

                    return true;
            }
        }


		if(((enemyLeft <= familyLeft) && (enemyLeft >= familyRight)) || ((enemyRight <= familyLeft) && (enemyRight >= familyRight)) )
        {
            if(((enemyBottom >= familyBottom) && (enemyBottom <= familyTop)) || ((enemyTop >= familyBottom) && (enemyTop <= familyTop)) )
            {

                    if(enemy->getEntityType() == cfg.HULK)
                    {
                        familyVec->at(i)->SetEntityToDestroyed();
                    }
                    else if(enemy->getEntityType() == cfg.BRAIN)
                    {
                        familyVec->at(i)->setToProg();
                        (dynamic_cast<Brain*> (enemy))->makingProg(); //cast to the Brain type to get the makingProg method


                    }

                    return true;
        }
	}
}
return false;
}

bool EnemyFactory::checkPlayerCollide(Player * player, Enemy * enemy) //check if the player and enemy hitboxes overlap
{

    float enemyWidth = enemy->getHitBoxWidth();
    float enemyHeight = enemy->getHitBoxHeight();
    float enemyX = enemy->getTransform()->GetPos()->x;
    float enemyY = enemy->getTransform()->GetPos()->y;

    float playerX = player->getTransform()->GetPos()->x;
    float playerY = player->getTransform()->GetPos()->y;

    float playerWidth = player->getHitBoxWidth();

    float playerHeight = player->getHitBoxHeight();

    float playerLeft = playerX + (playerWidth / 2);
    float playerRight = playerX - (playerWidth / 2);;
    float playerTop = playerY + (playerHeight / 2);
    float playerBottom = playerY - (playerHeight / 2);

    float enemyLeft = enemyX + (enemyWidth / 2);
    float enemyRight = enemyX - (enemyWidth / 2);
    float enemyTop = enemyY + (enemyHeight / 2);
    float enemyBottom = enemyY - (enemyHeight / 2);




   if(((playerLeft <= enemyLeft) && (playerLeft >= enemyRight)) || ((playerRight <= enemyLeft) && (playerRight >= enemyRight)) )
    {
        if(((playerBottom >= enemyBottom) && (playerBottom <= enemyTop)) || ((playerTop >= enemyBottom) && (playerTop <= enemyTop)) )
        {
                player->decreaseLives();
                player->killPlayer();
                 if (enemy->getEntityType() == cfg.ENFORCER_SPARK || enemy->getEntityType() == cfg.TANK_SHELL || enemy->getEntityType() == cfg.PROG || enemy->getEntityType() == cfg.CRUISE_MISSILE) //if the spark has collided with the player it will be set to delete
                {
                (enemy)->SetEntityToDestroyed(); //set the enemy's flag to indicate that it is destroyed

                if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Spark deleted, hit player\n"); }
                }
                return true;
        }
    }

    if(((enemyLeft <= playerLeft) && (enemyLeft >= playerRight)) || ((enemyRight <= playerLeft) && (enemyRight >= playerRight)) )
    {
        if(((enemyBottom >= playerBottom) && (enemyBottom <= playerTop)) || ((enemyTop >= playerBottom) && (enemyTop <= playerTop)) )
        {
            player->decreaseLives();
            player->killPlayer();
             if (enemy->getEntityType() == cfg.ENFORCER_SPARK || enemy->getEntityType() == cfg.TANK_SHELL || enemy->getEntityType() == cfg.PROG || enemy->getEntityType() == cfg.CRUISE_MISSILE) //if the spark has collided with the player it will be set to delete
                {
                    (enemy)->SetEntityToDestroyed(); //set the enemy's flag to indicate that it is destroyed

                    if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Spark deleted, hit player\n"); }
                }
            return true;
        }

    }

		return false;

}


void EnemyFactory::setScaling()
{
	for(unsigned int i = 0; i < enemyVec.size(); i++)
	{
		(*enemyVec[i]).getTransform()->GetScale()->x = (*enemyVec[i]).getScale();
		(*enemyVec[i]).getTransform()->GetScale()->y = (*enemyVec[i]).getScale();
		(*enemyVec[i]).getTransform()->GetScale()->z = (*enemyVec[i]).getScale();
	}
}

void EnemyFactory::setScalingForLast()
{
    (*enemyVec[enemyVec.size() - 1]).getTransform()->GetScale()->x = (*enemyVec[enemyVec.size() - 1]).getScale();
    (*enemyVec[enemyVec.size() - 1]).getTransform()->GetScale()->y = (*enemyVec[enemyVec.size() - 1]).getScale();
    (*enemyVec[enemyVec.size() - 1]).getTransform()->GetScale()->z = (*enemyVec[enemyVec.size() - 1]).getScale();

}

void EnemyFactory::createEntity(int Enemy, float x, float y, int amount)
{


	if(x != cfg.FACTORY_ROUGE_VALUE || y != cfg.FACTORY_ROUGE_VALUE) //Not NULL, make one enemy in this x and y loaction
	{

		if(Enemy == cfg.GRUNT)
		{
			enemyVec.push_back(new Grunt(x, y));
		}
		if(Enemy == cfg.HULK)
		{
			enemyVec.push_back(new Hulk(x, y));
			//(*enemyVec[enemyVec.size() - 1]).setDir(rand() % cfg.NUM_DIRECTIONS);
		}
		if(Enemy == cfg.ELECTRODE)
		{
			enemyVec.push_back(new Electrode(x, y));
		}
		if(Enemy == cfg.ENFORCER)
		{
			enemyVec.push_back(new Enforcer(x, y));
		}
		if(Enemy == cfg.TANK)
		{
            enemyVec.push_back(new Tank(x, y));
		}
		if(Enemy == cfg.BRAIN)
		{
            enemyVec.push_back(new Brain(x,y,familyVec));
		}
		if(Enemy == cfg.PROG)
		{
            enemyVec.push_back(new Prog(x,y));
		}
		if(Enemy == cfg.PROG_TRANSFORMER)
		{
            enemyVec.push_back(new ProgTransformer(x,y));
		}
		if(Enemy == cfg.SPHEROID)
		{
            enemyVec.push_back(new Spheroid(x,y));
		}

		(*enemyVec[enemyVec.size() - 1]).getTransform()->GetRot()->x += cfg.DEFAULT_ROT;
		setScalingForLast();
	}
	else //if is the rougue value, generate a random x and y and create the enemyies there
	{

		for (unsigned int i = 0; i < amount; i++)
		{
			float randX = (float)(rand() % (int)(cfg.positiveXBorder * 2) + (cfg.negativeXBorder));
			float randY = (float)(rand() % (int)(cfg.positiveYBorder * 2) + (cfg.negativeYBorder));

			if (Enemy == cfg.GRUNT)
			{
				if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Creating Grunt\n"); }
				enemyVec.push_back(new Grunt(randX, randY));
			}
			if (Enemy == cfg.HULK)
			{
				if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Creating Hulk\n"); }
				enemyVec.push_back(new Hulk(randX, randY));
			}
			if(Enemy == cfg.ELECTRODE)
			{
				if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Creating Electrode\n"); }
				enemyVec.push_back(new Electrode(randX, randY));
			}
			if(Enemy == cfg.ENFORCER)
			{
				if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Creating Enforcer\n"); }
				enemyVec.push_back(new Enforcer(randX, randY));
			}
			if(Enemy == cfg.TANK)
            {
                if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Creating Tank\n"); }
                enemyVec.push_back(new Tank (randX, randY));
            }
            if(Enemy == cfg.BRAIN)
            {
                enemyVec.push_back(new Brain(randX,randY,familyVec));
            }
            if(Enemy == cfg.PROG)
            {
                enemyVec.push_back(new Prog(randX,randY));
            }
            if(Enemy == cfg.PROG_TRANSFORMER)
            {
                enemyVec.push_back(new ProgTransformer(randX,randY));
            }
            if(Enemy == cfg.SPHEROID)
		{
            enemyVec.push_back(new Spheroid(randX,randY));
		}

			(*enemyVec[enemyVec.size() - 1]).getTransform()->GetRot()->x += cfg.DEFAULT_ROT;
			setScalingForLast();
		}

	}



}
void EnemyFactory::updateText(Shader * texShader, Camera * camera)
{

    texShader->Bind();
    for(unsigned int i = 0; i < wordScoreVec.size();i++)
    {
        if(!wordScoreVec[i]->update(texShader, camera)) //update returns false if the word has used all of its time
        {
            delete wordScoreVec[i];
            wordScoreVec.erase(wordScoreVec.begin() + i);
        }
    }
}



void EnemyFactory::update(Camera * camera, Shader * shader,Shader * texShader, Player * player)
{

	float x;
	float y;
	float playerX;
	float playerY;
	int dir;
	unsigned int currentTime;

	for(unsigned int i = 0; i < enemyVec.size(); i++)
	{
		currentTime = SDL_GetTicks();
		x = enemyVec[i]->getTransform()->GetPos()->x;
		y = enemyVec[i]->getTransform()->GetPos()->y;
		playerX = player->getTransform()->GetPos()->x;
		playerY = player->getTransform()->GetPos()->y;
		dir = (*enemyVec[i]).getDir();

        (*shader).Bind(); //bind the correct shader for drawing the enemies & particles
        //check collides ith bullets, player and family

		checkPlayerCollide(player, enemyVec[i]);

		//check if the enemy was killed
        checkEnemyKilled(enemyVec[i], player);




        if(enemyVec[i]->getEntityType() == cfg.HULK || enemyVec[i]->getEntityType() == cfg.BRAIN)
        {
            checkFamilyCollide(enemyVec[i], player);
        }



		if (enemyVec.empty() == true)
		{
			if (cfg.B_DEBUG_ENEMYFACTORY)
			{
				printf("EnemyFactory Class: Issue update() function. Enemy Vector is empty yet the functions are still being run! RISK OF CRASH!\n"); //the vector is empty but commands will still be operated on them below!
			}
		}


        if(!m_isPaused)
        {
            (*enemyVec[i]).move(player); //move the entity to thier new position
        }


        createEnemyProjectiles(enemyVec[i], player, shader, camera);


		(*shader).Update((*(*enemyVec[i]).getTransform()), *camera); //update the enemy in the shader and then draw the mesh


        enemyVec[i]->draw(dir);


		if ((*enemyVec[i]).getDestoryedState() == true) //the enemy has been destroyed, remove it from the vector
		{
			if (enemyVec[i]->getEntityType() != cfg.entityTypes::TANK_SHELL && enemyVec[i]->getEntityType() != cfg.entityTypes::CRUISE_MISSILE
				&& enemyVec[i]->getEntityType() != cfg.entityTypes::ENFORCER_SPARK)
			{
				glm::vec3 pos(enemyVec[i]->getTransform()->GetPos()->x, enemyVec[i]->getTransform()->GetPos()->y, enemyVec[i]->getTransform()->GetPos()->z);
				m_particleFactory.addEmitter(pos, 5.00f, 20, 1500, glm::vec4(0.7, 0.3, 0.3, 1.0));
			}
            delete enemyVec[i];
			enemyVec.erase(enemyVec.begin() + i);

		}

	}
	updateText(texShader, camera);
    createProgs(); //check the family vector for any family members that have become a prog, set them to deleted and create a prog replacing them

	m_particleFactory.update(camera, shader);
	m_particleFactory.combFinishedEmitters();
}

void EnemyFactory::createEnemyProjectiles(Enemy * enemy,Player * player, Shader * shader, Camera * camera)
{
	float playerX = player->getTransform()->GetPos()->x;
    float playerY = player->getTransform()->GetPos()->y;
    float x = enemy->getTransform()->GetPos()->x;
    float y = enemy->getTransform()->GetPos()->y;

    if(enemy->hasShot()) //if the enemy shot on that interation, if it was an enforcer, create a new spark, if it were a tank, create a new shell
    {
        if(enemy->getEntityType() == cfg.ENFORCER)
        {
            enemyVec.push_back(new EnforcerSpark(playerX, playerY, x,y));
            setScalingForLast();

            if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Spark shot\n"); }
        }
        if(enemy->getEntityType() == cfg.TANK)
        {
            enemyVec.push_back(new TankShell(playerX, playerY, x,y));
            setScalingForLast();

            if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Tank Shell shot\n"); }
        }
        if(enemy->getEntityType() == cfg.BRAIN)
        {
            enemyVec.push_back(new BrainMissile(playerX, playerY, x,y,true, SDL_GetTicks(), shader, camera));
            setScalingForLast();

            if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Brain Missile shot\n"); }
        }
        if(enemy->getEntityType() == cfg.SPHEROID)
        {
            enemyVec.push_back(new Enforcer(x,y));
            setScalingForLast();
            (*enemyVec[enemyVec.size() - 1]).getTransform()->GetRot()->x += cfg.DEFAULT_ROT;

            if (cfg.B_DEBUG_ENEMYFACTORY) { printf("EnemyFactor Class: Brain Missile shot\n"); }
        }

    }
}


