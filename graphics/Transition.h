#pragma once

/*
	Author: Nimrod W
	Description: Robotron is characterised by the transitions in between levels.
				 To create something similar, the transition entity will sit on top of the level and when a transition is played, it will display a 
				 sequence of images
*/

#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"
#include "../Config.h"
#include "../graphics/TransitionElement.h"

class Transition
{
public:
	Transition(glm::vec3 _startPos, int _numElements, glm::vec4 _startCol, unsigned int _lengthOfTransition, int _shapeType)
	{
		m_numberOfElements = _numElements;
		m_startPos = _startPos;
		m_startColour = _startCol;
		m_lengthOfTransition = _lengthOfTransition;
		m_startTime = SDL_GetTicks();
		m_finished = false;
		m_ElementShapeType = _shapeType;
	}
	~Transition();
	void createElements();
	bool getFinishedState() { return m_finished; } //returns true if the animation has finished
	void update(Shader *s, Camera *c);
	void cleanElements();
private:
	Config cfg;
	glm::vec3 m_startPos;
	glm::vec4 m_startColour;
	unsigned int m_duration; //how long the transition will take (in milliseconds)
	unsigned int m_numberOfElements;
	unsigned int m_lengthOfTransition;

	unsigned int m_startTime;
	int m_ElementShapeType;
	bool m_finished;

	std::vector<TransitionElement *> m_ElementList;
};