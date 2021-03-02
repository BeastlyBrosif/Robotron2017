#ifndef MUM_H
#define MUM_H
#include "../entities/Family.h"

class Mum : public Family {
public:
	Mum(float x, float y) : Family() {
		entityType = cfg.MUM;
		scale = cfg.MUM_SCALE;
		init();
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		updateInterval = cfg.MUM_UPDATE;
		animationInterval = cfg.MUM_ANIMATION_INTERVAL;
		moveStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		dirChangeStartTime = getTimeWithOffSet();
		dirUpdateInterval = cfg.MUM_DIR_UPDATE + rand() % cfg.MUM_DIR_UPDATE;
		m_moveSpeed = cfg.MUM_SPEED;;
		scoreValue = cfg.MUM_SCORE;
		m_hitBoxHeight = cfg.MUM_HEIGHT;
		m_hitBoxWidth = cfg.MUM_WIDTH;
		isNowProg = false;
	}
	~Mum() {};
	void init();
	virtual void move(Player * player);

protected:

};

#endif // Mum_H#pragma once
