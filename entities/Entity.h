/*
 * Entity.h
 *
 *  Created on: 5 Feb 2018
 *      Author: callum
 */

#ifndef ENTITY_H_
#define ENTITY_H_
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "../Config.h"
#include "../graphics/Mesh.h"
#include "../graphics/modelLoader.h"
#include "../graphics/Transform.h"


class Entity {
public:
	Entity();
    ~Entity();
    vector<glm::vec3> getVertices();
    vector<glm::vec4> getColors();
    Transform* getTransform();
    virtual void draw(int dir);
    void init();
    int getDir();
    void setDir(int _dir);
	void addMesh(Mesh * mesh, int dir);
	void nextMesh(int dir);


	void clearVectors();
	unsigned int * getMoveStartTime();
	float getUpdateInterval();
	float getDirUpdateInterval();
	unsigned int * getAnimationStartTime();
	unsigned int * getDirChangeStartTime();
	int getEntityType();
	void setSpeed(float _speed);
	float getSpeed();
	float getAnimationInterval();
	void setAnimationInterval(float _interval);
	float getScale();
	virtual void setBlack(){};
	int getScoreValue();
	float getHitBoxWidth() { return m_hitBoxWidth; }
    float getHitBoxHeight() { return m_hitBoxHeight; }
    void SetEntityToDestroyed() { m_destroyed = true; }
    bool getDestoryedState() { return m_destroyed; }
    void setHasBeenShotDir(int _dir){hasBeenShotDir = _dir;}
    int getHasBeenShotDir(){return hasBeenShotDir;}
    virtual bool checkBoundaryCollides();
    void defaultMovementForDir();
    void updateAnimation();//call to call nextMesh if the correct time has been reached
    void updateRandomDir();

    void addOffsetToEntities(unsigned int increment);


    unsigned int getTimeWithOffSet(){return (SDL_GetTicks() - m_timeOffset);}


    void checkIfLifeTimeOver();
    //mostly for playerFactory to update the m_currentTime var

    void updateCurrentTime(unsigned int newCurrentTime)
    {
        m_currentTime = newCurrentTime;
    }

	Config cfg;




protected:
	std::vector<glm::vec3> vertexVec; //vectors for vertices, indices, colors, normals and uvs
	std::vector<glm::vec4> colorVec;
	std::vector<glm::vec2> normalVec;
	std::vector<glm::vec2> uvVec;
	std::vector<unsigned int> indexVec;
	bool usesIndices;


	Transform transform; //transform (for moving scaling etc)

	std::vector<Mesh *> meshVec; //vectors for storing the meshes for directions
	std::vector<Mesh *> meshVecLeft;
	std::vector<Mesh *> meshVecRight;
	std::vector<Mesh *> meshVecUp;
	std::vector<Mesh *> meshVecDown;
    int hasBeenShotDir;
	int dir; //current direction
	int currentMesh; //default mesh index
	int currentLeftMesh; //left mesh index
	int currentRightMesh;
	int currentUpMesh;
	int currentDownMesh;
	unsigned int moveStartTime; //starttime of interval of moving
	unsigned int animationStartTime; //starttime of interval of animation
	unsigned int dirChangeStartTime; //starttime of interval of direction change
	int entityType; //type of enemy, specified in Config.h
	float dirUpdateInterval; //intervals for updating
	unsigned int updateInterval;
	unsigned int animationInterval;
	float m_moveSpeed; //movement velocity

	float scale; //scale of entity
	int scoreValue; //score value for when killed (mostly for enemies)
	float m_hitBoxHeight;
    float m_hitBoxWidth;
    unsigned int m_LifeTime;
    unsigned int m_lifeTimeStart;
    bool m_destroyed; //Check if the enemy has been destroyed or killed

    bool hasCollided;

    unsigned int m_currentTime;

    unsigned int m_timeOffset = 0;
};

#endif /* ENTITY_H_ */
