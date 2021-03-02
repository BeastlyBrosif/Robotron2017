#include "../graphics/particlesystem/ParticleEmitter.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

//Constructor:
/*
	_centre: the point the particles will originate from
	_amount: total number of particles
	_avgLifetime: misleading, the lifetime of the particles can be from 0.5 of this value to 1.5 of this value
	_avgCol: the average colour the particles will be
*/
ParticleEmitter::ParticleEmitter(glm::vec3 _centre, float _maxSpeed, unsigned int _amount, unsigned int _avgLifetime, glm::vec4 _avgCol)
{
	m_emissionCentre = _centre;
	MAX_SPEED = _maxSpeed;
	if (cfg.PARTICLE_DENSITY == cfg.ParticleAmount::LOW)
	{
		m_emissionAmount = _amount / 4;
	}
	else if (cfg.PARTICLE_DENSITY == cfg.ParticleAmount::MEDIUM)
	{
		m_emissionAmount = _amount / 2;
	}
	else if (cfg.PARTICLE_DENSITY == cfg.ParticleAmount::HIGH)
	{
		m_emissionAmount = _amount;
	}

	m_averageLifetime = _avgLifetime;
	m_averageColour = _avgCol;
	m_completed = false;
	prevTime = 0;
	createParticles();
}

void ParticleEmitter::createParticles()
{
	srand(time(NULL));
	
	//simple triangle
	ModelLoader mloader(1);
	std::vector<glm::vec4> colourData;
	mloader.readOBJfile("./res/particle.obj");
	

	for (int i = 0; i < m_emissionAmount; i++)
	{
		float angle = rand() % 360;
		float Hx = cosf(angle); //heading x
		float Hy = sinf(angle); //heading y
		
		glm::vec3 dir(Hx, Hy, 0.0f);
		float r = (((float)rand() / RAND_MAX) * 0.6f) - 0.3f;
		float g = (((float)rand() / RAND_MAX) * 0.6f) - 0.3f;
		float b = (((float)rand() / RAND_MAX) * 0.6f) - 0.3f;
		glm::vec3 pos = m_emissionCentre;
		glm::vec4 col = m_averageColour + glm::vec4(r, g, b, 1.0);
		int ra = rand() % (m_averageLifetime)+( - (int)(m_averageLifetime / 2) - 1);
		unsigned int liTime = m_averageLifetime + ra;

		for (int i = 0; i < mloader.getVerticesSize(); i++)
		{
			colourData.push_back(col);
		}
		float randSpeed = rand() % (int)MAX_SPEED;
		m_particleList.push_back(new Particle(pos, dir, glm::vec3(1.0f, 1.0f, 1.0f), false, liTime, SDL_GetTicks(), randSpeed, 
			new Mesh(mloader.getVertices(), mloader.getIndices(), colourData, true, false, false)));
		colourData.clear();
		m_particleList[i]->getTransform()->GetRot()->x = cfg.DEFAULT_ROT;
		m_particleList[i]->getTransform()->GetScale()->x = 2.0f;
		m_particleList[i]->getTransform()->GetScale()->y = 2.0f;
		m_particleList[i]->getTransform()->GetScale()->z = 2.0f;

	}
}
bool ParticleEmitter::isEmiterFinished()
{
	if(m_completed == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ParticleEmitter::removeParticlesFromList()
{
	for (int i = 0; i < m_particleList.size(); i++)
	{
		if (m_particleList[i]->isParticleDead(SDL_GetTicks())) //has this particle's lifetime been exceeded?
		{
			delete m_particleList[i];
			m_particleList.erase(m_particleList.begin() + i);
		}
	}
}
void ParticleEmitter::update(Camera *camera, Shader *shader)
{
	
	if (m_particleList.size() == 0)
	{
		m_completed = true;
	}
	unsigned int curTime;
	for (int i = 0; i < m_particleList.size(); i++)
	{
		curTime = SDL_GetTicks();
		m_particleList[i]->moveParticle(curTime - prevTime);
		(*shader).Update(*(m_particleList[i])->getTransform(), *camera);
		m_particleList[i]->draw(cfg.NO_DIR);
		prevTime = SDL_GetTicks();
	}
	
	removeParticlesFromList();
}
ParticleEmitter::~ParticleEmitter()
{

}