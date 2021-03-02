/*
 * BulletFactory.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: callum
 */

#include "BulletFactory.h"

using namespace std;



vector<Bullet *> * BulletFactory::getBulletVec()
{
	return &bulletVec;
}

void BulletFactory::setScaling()
{
	for(unsigned int i = 0; i < bulletVec.size(); i++)
	{
		(*bulletVec[i]).getTransform()->GetScale()->x = cfg.BULLET_SCALE;
		(*bulletVec[i]).getTransform()->GetScale()->y = cfg.BULLET_SCALE;
		(*bulletVec[i]).getTransform()->GetScale()->z = cfg.BULLET_SCALE;
	}
}
void BulletFactory::setScalingForLast()
{
    (*bulletVec[bulletVec.size() - 1]).getTransform()->GetScale()->x = (*bulletVec[bulletVec.size() - 1]).getScale();
    (*bulletVec[bulletVec.size() - 1]).getTransform()->GetScale()->y = (*bulletVec[bulletVec.size() - 1]).getScale();
    (*bulletVec[bulletVec.size() - 1]).getTransform()->GetScale()->z = (*bulletVec[bulletVec.size() - 1]).getScale();
}

void BulletFactory::createEntity(float x, float y, bool * bulletDirArray)
{
    int dir;
    unsigned int currentTime = SDL_GetTicks();

            if(bulletDirArray[cfg.UP]) //find the correct dir to fire the bullet from the array passed in
			{
				if(bulletDirArray[cfg.RIGHT])
				{
					dir = cfg.UP_RIGHT;

				}
				else if (bulletDirArray[cfg.LEFT])
				{
					dir = cfg.UP_LEFT;

				}
				else
				{
					dir = cfg.UP;

				}

			}
			else if (bulletDirArray[cfg.DOWN])
			{
				if(bulletDirArray[cfg.RIGHT])
				{
					dir = cfg.DOWN_RIGHT;

				}
				else if (bulletDirArray[cfg.LEFT])
				{
					dir = cfg.DOWN_LEFT;
				}
				else
				{
					dir = cfg.DOWN;
				}
			}
			else if (bulletDirArray[cfg.LEFT])
			{
				dir = cfg.LEFT;

			}
			else if(bulletDirArray[cfg.RIGHT])
			{
				dir = cfg.RIGHT;

			}


    if(((currentTime - m_bulletsStartTime) > m_bulletInterval) && !m_isPaused)
    {
        bulletVec.push_back(new Bullet(dir, x, y));
        setScalingForLast();

        m_bulletsStartTime = currentTime;
        Mix_PlayChannel(-1, bulletShot, 0 );
    }

}

void BulletFactory::update(Camera *camera, Shader *shader)
{
	if (bulletVec.empty() == false)
	{
		for (unsigned int i = 0; i < bulletVec.size(); i++)
		{

            if(!m_isPaused)
            {
                if ((*bulletVec[i]).getDir() == cfg.UP)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->y += cfg.BULLET_SPEED;

                }
                else if ((*bulletVec[i]).getDir() == cfg.DOWN)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->y -= cfg.BULLET_SPEED;

                }
                else if ((*bulletVec[i]).getDir() == cfg.LEFT)
                {

                    ((*bulletVec[i]).getTransform())->GetPos()->x += cfg.BULLET_SPEED;
                }
                else if ((*bulletVec[i]).getDir() == cfg.RIGHT)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->x -= cfg.BULLET_SPEED;
                }

                else if ((*bulletVec[i]).getDir() == cfg.UP_RIGHT)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->x -= cfg.BULLET_SPEED;
                    ((*bulletVec[i]).getTransform())->GetPos()->y += cfg.BULLET_SPEED;
                }
                else if ((*bulletVec[i]).getDir() == cfg.UP_LEFT)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->x += cfg.BULLET_SPEED;
                    ((*bulletVec[i]).getTransform())->GetPos()->y += cfg.BULLET_SPEED;
                }
                else if ((*bulletVec[i]).getDir() == cfg.DOWN_RIGHT)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->x -= cfg.BULLET_SPEED;
                    ((*bulletVec[i]).getTransform())->GetPos()->y -= cfg.BULLET_SPEED;
                }
                else if ((*bulletVec[i]).getDir() == cfg.DOWN_LEFT)
                {
                    ((*bulletVec[i]).getTransform())->GetPos()->x += cfg.BULLET_SPEED;
                    ((*bulletVec[i]).getTransform())->GetPos()->y -= cfg.BULLET_SPEED;
                }

            }




			if ((*bulletVec[i]).getTransform()->GetPos()->y > cfg.positiveYBorder || (*bulletVec[i]).getTransform()->GetPos()->y < cfg.negativeYBorder || (*bulletVec[i]).getTransform()->GetPos()->x > cfg.positiveXBorder || (*bulletVec[i]).getTransform()->GetPos()->x < cfg.negativeXBorder)
			{
				(*bulletVec[i]).setBulletToDeleted();
			}
			(*shader).Update((*(*bulletVec[i]).getTransform()), *camera);
			(*bulletVec[i]).draw(cfg.NO_DIR); //solved previous bug, new bug arisen

			if ((*bulletVec[i]).getDeletedState() == true) //the bullet has been deleted, we will move the pointer to a seperate vector
			{
                if(bulletVec[i]->getHitState())
                {
                     Mix_PlayChannel(-1, bulletHit, 0 );
                }

				delete bulletVec[i];
				bulletVec.erase(bulletVec.begin() + i);
			}

		}
	}
}
