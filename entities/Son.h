#ifndef SON_H
#define SON_H
#include "../entities/Family.h"

class Son: public Family {
public:
	Son(float x, float y): Family(){
		entityType = cfg.SON;
		scale =	cfg.SON_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.SON_UPDATE;
		animationInterval = cfg.SON_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		dirUpdateInterval = cfg.SON_DIR_UPDATE + rand() % cfg.SON_DIR_UPDATE;
		m_shellShotStartTime = SDL_GetTicks();
		m_shellShotInterval = cfg.SHELL_INTERVAL;
		m_moveSpeed = cfg.SON_SPEED;;
		scoreValue = cfg.SON_SCORE;
		m_hitBoxHeight = cfg.SON_HEIGHT;
		m_hitBoxWidth = cfg.SON_WIDTH;
		isNowProg = false;

	}
	~Son(){};
    void init();
	virtual void move(Player * player);

protected:
	unsigned int m_shellShotStartTime;
	unsigned int m_shellShotInterval;

};

#endif // SON_H
