#include "../graphics/TransitionElement.h"


TransitionElement::~TransitionElement()
{

}
void TransitionElement::setDirection(int dir)
{
	m_direction = dir;
}
void TransitionElement::setUpShape()
{
	if (m_shapeType == cfg.RECTANGLE)
	{
		//to draw a rectangle we need 4 vertices
		//since the amination starts at zero, we can do this fairly easily
		
		m_vertexCoords.push_back(glm::vec3(0 + m_width / 2, 0 + m_height / 2, m_startPos.z));
		m_vertexCoords.push_back(glm::vec3(0 + m_width / 2, 0 - m_height / 2, m_startPos.z));
		m_vertexCoords.push_back(glm::vec3(0 - m_width / 2, 0 + m_height / 2, m_startPos.z));
		m_vertexCoords.push_back(glm::vec3(0 - m_width / 2, 0 - m_height / 2, m_startPos.z));

		m_indexList.push_back(0);
		m_indexList.push_back(1);
		m_indexList.push_back(2);
		m_indexList.push_back(1);
		m_indexList.push_back(2);
		m_indexList.push_back(3);

		m_scaleIncrement = 1.2f;
	}
	else if (m_shapeType == cfg.TRIANGLE)
	{
		m_vertexCoords.push_back(glm::vec3(0, 0 + m_height/2, 0));
		m_vertexCoords.push_back(glm::vec3(0 + m_width/2, 0 - m_height/2, 0));
		m_vertexCoords.push_back(glm::vec3(0 - m_width/2, 0 - m_height/2, 0));
		m_indexList.push_back(0);
		m_indexList.push_back(1);
		m_indexList.push_back(2);

		m_scaleIncrement = 1.2f;
	}
	else if (m_shapeType == cfg.PENTAGON)
	{
		m_vertexCoords.push_back(glm::vec3(0, 1, 0));
		m_vertexCoords.push_back(glm::vec3(sinf((2*3.14)/5), cosf((2*3.14)/5), 0));
		m_vertexCoords.push_back(glm::vec3(sinf((4*3.14)/5), -sinf((3.14)/5), 0));
		m_vertexCoords.push_back(glm::vec3(-sinf((4 * 3.14) / 5), -sinf((3.14) / 5), 0));
		m_vertexCoords.push_back(glm::vec3(-sinf((2 * 3.14) / 5), cosf((2 * 3.14) / 5), 0));
		m_indexList.push_back(0);
		m_indexList.push_back(1);
		m_indexList.push_back(2);
		m_indexList.push_back(0);
		m_indexList.push_back(2);
		m_indexList.push_back(3);
		m_indexList.push_back(0);
		m_indexList.push_back(4);
		m_indexList.push_back(3);

		m_scaleIncrement = 20.0f;
	}
	for (int i = 0; i < m_vertexCoords.size(); i++)
	{
		m_vertexColour.push_back(m_colour);
	}
	addMesh(new Mesh(m_vertexCoords, m_indexList, m_vertexColour, true, false, false), cfg.NO_DIR);
}
void TransitionElement::update(Camera *c, Shader *s)
{
	s->Update(*getTransform(), *c);
	changeSize();
	draw(cfg.NO_DIR);
}
void TransitionElement::changeSize()
{
	float x, y;
	x = getTransform()->GetPos()->x;
	y = getTransform()->GetPos()->y;
	float xScale = getTransform()->GetScale()->x;
	float yScale = getTransform()->GetScale()->y;
	//expand the box until it reaches the edge of the screen
	if (m_direction > 0)
	{
		if (m_shapeType == cfg.RECTANGLE)
		{
			if (x + (xScale * (m_width / 2)) < cfg.positiveXBorder)
			{
				getTransform()->GetScale()->x += m_scaleIncrement;
			}
			if (y + (yScale * (m_height / 2)) < cfg.positiveYBorder)
			{
				getTransform()->GetScale()->y += m_scaleIncrement;
			}
		}
		else if (m_shapeType == cfg.TRIANGLE)
		{
			if (x + (xScale * (m_width / 2)) < cfg.positiveXBorder*4)
			{
				getTransform()->GetScale()->x += m_scaleIncrement;
			}
			if (y + (yScale * (m_height / 2)) < cfg.positiveYBorder*4)
			{
				getTransform()->GetScale()->y += m_scaleIncrement;
			}
		}
		else if (m_shapeType == cfg.PENTAGON)
		{
			if (x < cfg.positiveXBorder)
			{
				getTransform()->GetScale()->x += m_scaleIncrement;
			}
			if (y < cfg.positiveYBorder)
			{
				getTransform()->GetScale()->y += m_scaleIncrement;
			}
		}
		
	}
	if (m_direction < 0)
	{

	}
	
	
}