#pragma once

#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../graphics/particlesystem/Particle.h"
#include "../factory/Factory.h"

class ParticleEmitter : public Factory
{
public:
	ParticleEmitter(glm::vec3 _centre, float _maxSpeed, unsigned int _amount, unsigned int _avgLifetime, glm::vec4 _avgCol);
	~ParticleEmitter();

	void createParticles();
	void update(Camera *camera, Shader *shader);
	void removeParticlesFromList();
	bool isEmiterFinished();
	
	Config cfg;
private:
	
	glm::vec3 m_emissionCentre; //choose the point that the particle will emit from
	glm::vec4 m_averageColour;
	unsigned int m_emissionAmount; //number of particles to be created
	unsigned int m_particleAmount; //how many particles should this emitter produce
	unsigned int m_averageLifetime; //the average lifetime of each particle
	bool m_completed; //has the particle emmitter finished?

	std::vector<Particle *> m_particleList; //contains a list of current living particles
	float MAX_SPEED;
	unsigned int prevTime;
};