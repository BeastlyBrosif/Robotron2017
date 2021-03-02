#ifndef PROGTRANSFORMER_H
#define PROGTRANSFORMER_H

#include "Enemy.h"
class ProgTransformer : public Enemy
{
    public:
        ProgTransformer(float x, float y):Enemy(){
        entityType = cfg.PROG_TRANSFORMER;
		scale =	cfg.PROG_TRANSFORMER_SCALE;
		init();
		dir = cfg.UP; //initialise dir to UP for the shake animation
		transform.GetPos()->x = x;
		transform.GetPos()->y = y;
		animationInterval = cfg.PROG_ANIMATION_INTERVAL;
		updateInterval = cfg.PROG_TRANSFORMER_UPDATE;
		m_moveSpeed = cfg.PROG_TRANSFORMER_SPEED;
		dirUpdateInterval = cfg.PROG_TRANSFORMER_DIR_UPDATE;
		dirChangeStartTime = getTimeWithOffSet();
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();

		scoreValue = 0;
		m_hitBoxHeight = cfg.PROG_TRANSFORMER_HEIGHT;
		m_hitBoxWidth = cfg.PROG_TRANSFORMER_WIDTH;
		m_progTransformerStartTime = getTimeWithOffSet();
	}
    ~ProgTransformer(){};
    void init();
    void move(Player * player);
    void shake();

    protected:
        unsigned int m_progTransformerDuration = cfg.TIME_TO_MAKE_PROG;
        unsigned int m_progTransformerStartTime;
};

#endif // PROGTRANSFORMER_H
