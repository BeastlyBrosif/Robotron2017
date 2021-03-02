#include "../graphics/Transition.h"
Transition::~Transition()
{
	//cleanElements();
}
void Transition::createElements()
{
	static int createdElements = 0;
	static glm::vec4 currentColour = m_startColour;

	int currentTime = SDL_GetTicks();
	//std::cout << "R: " << currentColour.r << " G: " << currentColour.g << " B: " << currentColour.b << std::endl;
	if (currentColour.r == 1.0f && currentColour.b < 1.0f)
	{
	//	std::cout << "Increasing Blue" << std::endl;
		currentColour.b = currentColour.b + (1.0f / 10.0f);
	}
	if (currentColour.b >= 0.99f && currentColour.r > 0)
	{
	//	std::cout << "Decreasing Red" << std::endl;
		currentColour.r = currentColour.r - (1.0f / 10.0f);
	}
	if (currentColour.b >= 0.99f && currentColour.g < 1.0f)
	{
	//	std::cout << "Increasing Green" << std::endl;
		currentColour.g = currentColour.g + (1.0f / 10.0f);
	}
	if (currentColour.g >= 0.99f && currentColour.b > 0)
	{
	//	std::cout << "Decreasing Blue" << std::endl;
		currentColour.b = currentColour.b - (1.0f / 10.0f);
	}
	if (currentColour.g >= 0.99f && currentColour.r < 1.0f)
	{
	//	std::cout << "Increasing Red" << std::endl;
		currentColour.r = currentColour.r + (1.0f / 10.0f);
	}
	if (currentColour.r >= 0.99f && currentColour.g > 0)
	{
	//	std::cout << "Decreasing Green" << std::endl;
		currentColour.g = currentColour.g - (1.0f / 10.0f);
	}
	
	if (currentTime - m_startTime > m_lengthOfTransition / m_numberOfElements && createdElements < m_numberOfElements)
	{
		if (createdElements == m_numberOfElements - 1)
		{
			m_ElementList.push_back(new TransitionElement(m_startPos, m_ElementShapeType, glm::vec4(0,0,0,0), 50, 20, cfg.positiveXedge, cfg.positiveYedge));
		}
		else
		{
			m_ElementList.push_back(new TransitionElement(m_startPos, m_ElementShapeType, currentColour, 50, 20, cfg.positiveXedge, cfg.positiveYedge));
		}
		m_startTime = currentTime;
		createdElements++;
	}
	if (createdElements == m_numberOfElements && currentTime - m_startTime > m_lengthOfTransition && m_finished != true)
	{
		m_finished = true;
	}

}
void Transition::update(Shader *s, Camera *c)
{
	for(int i = 0; i < m_ElementList.size(); i++)
	{
		int currTime = SDL_GetTicks();
		if (currTime - m_startTime > 30)
		{
			m_ElementList.at(i)->getTransform()->GetPos()->z += 0.2f;
		}
		m_ElementList.at(i)->update(c, s);
	}
}
void Transition::cleanElements()
{
	int numElements = m_ElementList.size();

	for (int i = 0; i < numElements; i++)
	{
		delete m_ElementList[i];
	}
	m_ElementList.clear();
}