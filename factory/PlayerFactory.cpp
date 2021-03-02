/*
 * PlayerFactory.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: callum
 */

#include "../factory/PlayerFactory.h"
#include "../entities/Player.h"
#include "../Config.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"

Player *  PlayerFactory::getPlayerPointer()
{
	return &player;
}


void PlayerFactory::setScaling() //get the player scale from the config file and use it to scale the players sprite to the appropiate size
{
	(*player.getTransform()).GetScale()->x = cfg.PLAYER_SCALE;
	(*player.getTransform()).GetScale()->y = cfg.PLAYER_SCALE;
	(*player.getTransform()).GetScale()->z = cfg.PLAYER_SCALE;
	(*player.getTransform()).GetRot()->x += cfg.DEFAULT_ROT;
}




void PlayerFactory::update(Camera * camera, Shader * shader, bool * dirArray) //update method for the player
{

	if (getPlayerPointer()->getPlayerAlive() == false && m_playerKilled == false)
	{
		m_playerKilled = true;
		glm::vec3 pos(getPlayerPointer()->getTransform()->GetPos()->x, getPlayerPointer()->getTransform()->GetPos()->y, getPlayerPointer()->getTransform()->GetPos()->z);
		p.addEmitter(pos, 50.00f, 100, 1500, glm::vec4(0.7, 0.3, 0.3, 1.0));

	}
    int dir; //what direction to draw for the animation, defaults to NO_DIR (still), then updates if a flag is true, left and right take presedance over up and down (as when moving diagonal the left and right animations are still used)
    dir = cfg.NO_DIR;

    float x,y;
    x = (*player.getTransform()).GetPos()->x;
    y = (*player.getTransform()).GetPos()->y;
    float width, height;
    width = player.getHitBoxWidth();
    height = player.getHitBoxHeight();

    if(!m_isPaused)
    {
        if(dirArray[cfg.UP] && (y + (height/2)) < cfg.positiveYBorder) //check the flags in the player movement array, corresponds to the keys pressed, move the player if that key was pressed
        {
            (*player.getTransform()).GetPos()->y += cfg.PLAYER_SPEED;
            dir = cfg.UP;
        }
        if(dirArray[cfg.DOWN] && (y - (height/2)) > cfg.negativeYBorder)
        {
            (*player.getTransform()).GetPos()->y -= cfg.PLAYER_SPEED;
            dir = cfg.DOWN;
        }
        if(dirArray[cfg.LEFT] && (x + (width/2)) < cfg.positiveXBorder)
        {
            (*player.getTransform()).GetPos()->x += cfg.PLAYER_SPEED;
            dir = cfg.LEFT;
        }
        if(dirArray[cfg.RIGHT] && (x - (width/2)) > cfg.negativeXBorder)
        {
            (*player.getTransform()).GetPos()->x -= cfg.PLAYER_SPEED;
            dir = cfg.RIGHT;
        }
    }



	player.setDir(dir);

	player.updateAnimation();

	(*shader).Update((*player.getTransform()), *camera); //update the players position in the shader and draw the player with thier current mesh for the correct direction
	player.draw(dir);
	p.update(camera, shader);
}
