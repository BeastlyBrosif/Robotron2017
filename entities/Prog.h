#ifndef PROG_H
#define PROG_H

#include "Enemy.h"


class Prog : public Enemy
{
    public:
        Prog(float x, float y):Enemy(){
        entityType = cfg.PROG;
		scale =	cfg.SON_SCALE;
		init();
		dir = cfg.NO_DIR; //Prog doesnt have different meshes for the different directions, so when it draws use NO_DIR
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		updateInterval = cfg.PROG_UPDATE;
		dirChangeStartTime = getTimeWithOffSet();
		dirUpdateInterval = cfg.PROG_DIR_UPDATE;
		animationInterval = cfg.PROG_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		m_moveSpeed = cfg.PROG_SPEED;
		scoreValue = cfg.PROG_SCORE;
		m_hitBoxHeight = cfg.PROG_HEIGHT;
		m_hitBoxWidth = cfg.PROG_WIDTH;

		m_playerSeekStartTime = getTimeWithOffSet();
		m_playerSeekInterval = cfg.PROG_PLAYER_SEEK_INTERVAL + rand() & cfg.PROG_PLAYER_SEEK_INTERVAL;
	}
    ~Prog(){};
    void init();
    void move(Player * player);
    void seekPlayer(Player * player);

    protected:
    unsigned int progDelay = cfg.TIME_TO_MAKE_PROG; //delay the movement for this amount of time (creation time)
    unsigned int progStartTime = getTimeWithOffSet();
    float m_seekedPlayerX = 0;
    float m_seekedPlayerY = 0;
    unsigned int m_playerSeekStartTime;
    unsigned int m_playerSeekInterval;
    private:
};

#endif // PROG_H
