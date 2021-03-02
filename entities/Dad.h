#ifndef DAD_H
#define DAD_H
#include "../entities/Family.h"

class Dad: public Family {
public:
	Dad(float x, float y): Family(){
		entityType = cfg.DAD;
		scale =	cfg.DAD_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.DAD_UPDATE;
		animationInterval = cfg.SON_ANIMATION_INTERVAL;
		moveStartTime = SDL_GetTicks();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		dirUpdateInterval = cfg.DAD_DIR_UPDATE + rand() % cfg.DAD_DIR_UPDATE;
		m_shellShotStartTime = getTimeWithOffSet();
		m_shellShotInterval = cfg.SHELL_INTERVAL;
		m_moveSpeed = cfg.DAD_SPEED;;
		scoreValue = cfg.DAD_SCORE;
		m_hitBoxHeight = cfg.DAD_HEIGHT;
		m_hitBoxWidth = cfg.DAD_WIDTH;
		isNowProg = false;

	}
	~Dad(){};
    void init();
	virtual void move(Player * player);

protected:
	unsigned int m_shellShotStartTime;
	unsigned int m_shellShotInterval;

};

#endif // DAD_H
