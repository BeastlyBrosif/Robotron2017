#pragma once
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

//Author: Nimrod W
/* Particle class:
* Main functions: to be used in an explosion or transition of a character/model (i.e. the player spawns in a level or an enemy is killed)
* Workings: a particle is a light, simple class. A simple move function that moves the particle along a vector with a set, irregular deviation from that path
*/

#include <cstdlib>
#include <glm/glm.hpp>

#include "../entities/Entity.h"
#include "../graphics/Transform.h"

class Particle : public Entity
{
public:
	Particle(glm::vec3 _pos, glm::vec3 _path, glm::vec3 _weights,
		     bool _changeCol, unsigned int _lifeTime, unsigned int _creationTime, float _speed, Mesh *_mesh);
	~Particle();

	void moveParticle(unsigned int delataTime); //moves the particle in a pseudo random motion
	bool isParticleDead(unsigned int curTime); //returns true if particle has reached the end of its lifetime

	Transform *getTransform() { return &transform; };
private:
	Transform transform; //the transform class of the particle
	glm::vec3 m_pos;
	glm::vec3 m_path; //a unit vector in x,y,z describing the path the particle will take
	glm::vec3 m_weights; //the weights used to create irregularities in the path the particle takes
	bool m_changeColour; //controls whether the particle changes its colour during its lifetime

	unsigned int m_lifetime; //how many milliseconds the particle will exist for
	unsigned int m_creationTime;

	float m_speed; //the speed the particle will move along its path (measured in units/s)
};
