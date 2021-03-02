#include "../graphics/particlesystem/Particle.h"
#include "../graphics/modelLoader.h"


Particle::Particle(glm::vec3 _pos, glm::vec3 _path, glm::vec3 _weights,
	bool _changeCol, unsigned int _lifeTime, unsigned int _creationTime, float _speed, Mesh *_mesh)
{
	transform.GetPos()->x = _pos.x;
	transform.GetPos()->y = _pos.y;
	transform.GetPos()->z = _pos.z;

	m_path = _path;
	m_weights = _weights;

	m_changeColour = _changeCol;

	m_creationTime = _creationTime;
	m_lifetime = _lifeTime;

	m_speed = _speed;

	addMesh(_mesh, cfg.NO_DIR);
}
Particle::~Particle()
{

}
void Particle::moveParticle(unsigned int deltaTime)
{
	if (deltaTime == 0)
	{
		deltaTime = 1;
	}
	float xVel = (m_speed * m_path.x * m_weights.x) / deltaTime;
	float yVel = (m_speed * m_path.y * m_weights.y) / deltaTime;

//	float zVel = m_speed * (m_path.z) * m_weights.z; //this should just be 0 and be ignored
	transform.GetPos()->x += xVel;
	transform.GetPos()->y += yVel;
	//update the m_pos
	m_pos.x = transform.GetPos()->x;
	m_pos.y = transform.GetPos()->y;
}
bool Particle::isParticleDead(unsigned int curTime)
{
	if (curTime >= (m_creationTime + m_lifetime))
	{
		return true;
	}
	else
	{
		return false;
	}
}
