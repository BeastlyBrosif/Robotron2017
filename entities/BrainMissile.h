#ifndef BRAINMISSIIE_H
#define BRAINMISSIIE_H

#include "../entities/Enemy.h"


class BrainMissile: public Enemy {
public:
	BrainMissile(float playerX, float playerY, float x, float y, bool _isHead, unsigned int _moveStartTime, Shader * shader, Camera * camera): Enemy(){
        m_isHead = _isHead;
        m_shader = shader;
        m_camera = camera;
        m_moveSpeed = 3;
		dir = cfg.NO_DIR;
		scale =	cfg.MISSILE_SCALE;
		getTransform()->GetPos()->x = x;
		getTransform()->GetPos()->y = y;
		moveStartTime = getTimeWithOffSet();
		tailUpdateStartTime = getTimeWithOffSet();
		animationStartTime = getTimeWithOffSet();
		updateInterval = cfg.MISSILE_UPDATE;
		animationInterval = 200;
		//dirChangeStartTime = SDL_GetTicks();
		m_playerX = playerX;
		m_playerY = playerY;
		entityType = cfg.CRUISE_MISSILE;
		m_hitBoxHeight = cfg.MISSILE_HEIGHT;
		m_hitBoxWidth = cfg.MISSILE_WIDTH;
		scoreValue = cfg.CRUISE_MISSILE_SCORE;
		m_LifeTime = 4000;
		m_lifeTimeStart = getTimeWithOffSet();
		isZigZagging = false;
		zigZigChangeStartTime = getTimeWithOffSet();
		init();
		m_timeOffset = 0;


	}
    ~BrainMissile()
    {
        for(int i = 0; i < tailVec.size(); i++)
        {
            delete tailVec[i];
        }
        tailVec.clear();
    };
    void init();
    void draw(int dir);
    bool checkBoundaryCollides();
    void move(Player * player);
    void setUpTail(float x,float y);
    void setNewCoordsIfTime(float x, float y);
    void updateTail(Player* player);
    void zigZagMissile();
    void changeZigZig();

    void headMovement(Player * player);
    void tailMovement();



protected:
    bool m_isHead;
    std::vector <BrainMissile*> tailVec;
    float m_ratio;
    float m_playerX;
    float m_playerY;
    float m_moveDisX;
    float m_moveDisY;
    float m_xDisplacement;
    float m_yDisplacement;
    float prevX;
    float prevY;
    unsigned int tailUpdateStartTime;
    unsigned int zigZigChangeStartTime;
    Camera * m_camera;
    Shader * m_shader;
    bool isZigZagging;
    int num_directions = cfg.NUM_DIRECTIONS;
    std::vector<int> dirVec;

    int dirChoice;
};

#endif // BRAINMISSIIE_H
