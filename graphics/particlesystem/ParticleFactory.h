#pragma once
//Author: Nimrod Wynne
//This class will be used in the enemy factory class. 
//Every time an enemy is killed, this class will create a particle emitter at the dead enemy's position

#include "../graphics/particlesystem/ParticleEmitter.h"

class ParticleFactory
{
public:
	ParticleFactory();
	~ParticleFactory();

	void addEmitter(glm::vec3 _centre, float _maxSpeed, unsigned int _amount, unsigned int _avgLifetime, glm::vec4 _avgCol);
	void combFinishedEmitters();
	void removeEmitter(int index);

	void clearList();

	void update(Camera *c, Shader *s);

	int getNumberofEmitters() { return m_emitterList.size(); }
private:
	std::vector<ParticleEmitter*> m_emitterList;
	std::vector<unsigned int> m_particleEmitterstobedeletedList;
};
