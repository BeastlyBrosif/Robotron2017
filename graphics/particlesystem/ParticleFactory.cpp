#include "../graphics/particlesystem/ParticleFactory.h"

ParticleFactory::ParticleFactory()
{

}
ParticleFactory::~ParticleFactory()
{
	//clearList();
}
void ParticleFactory::update(Camera *c, Shader *s)
{
	int numOfEmitters = getNumberofEmitters();
	for (int i = 0; i < numOfEmitters; i++)
	{
		m_emitterList.at(i)->update(c, s);
	}
}
void ParticleFactory::combFinishedEmitters()
{
	int numOfEmitters = getNumberofEmitters();
	for (int i = 0; i < numOfEmitters; i++)
	{
		if (m_emitterList.at(i)->isEmiterFinished())
		{
			m_particleEmitterstobedeletedList.push_back(i);
		}
	}
	int emittersToBeRemoved = m_particleEmitterstobedeletedList.size();
	/*for (int i = 0; i < emittersToBeRemoved; i++)
	{
		removeEmitter(m_particleEmitterstobedeletedList.at(i));
		std::cout << "removing: " << i << " Size: " << m_particleEmitterstobedeletedList.size() << std::endl;
	}*/

    //MIGHT solve the crashing problem for me, Need to talk for workings of this function, i havnt crashed since changing this
	for(int i = (m_particleEmitterstobedeletedList.size() - 1); i > -1; i--) //loop backwards, to avoid trying to delete an index which could be outside of the array
	{
        //std::cout << i << std::endl;
        removeEmitter(m_particleEmitterstobedeletedList.at(i));
	}
	m_particleEmitterstobedeletedList.clear();
}
void ParticleFactory::addEmitter(glm::vec3 _centre, float _maxSpeed, unsigned int _amount, unsigned int _avgLifetime, glm::vec4 _avgCol)
{
	m_emitterList.push_back(new ParticleEmitter(_centre, _maxSpeed, _amount, _avgLifetime, _avgCol));
}
void ParticleFactory::removeEmitter(int index)
{
	delete m_emitterList.at(index);
	m_emitterList.erase(m_emitterList.begin() + index);
}
void ParticleFactory::clearList()
{
	int numOfEmitters = getNumberofEmitters();
	for (int i = 0; i < numOfEmitters; i++)
	{
		removeEmitter(i);
	}
}
