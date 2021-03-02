#pragma once

#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../entities/Entity.h"

class TransitionElement : public Entity
{
public:
	TransitionElement(glm::vec3 _startPos, int _shape, glm::vec4 _shapeColour, int _w, int _h, int _widthLimit, int _heightLimit) : Entity()
	{
		m_startPos = _startPos;
		transform.GetPos()->x = m_startPos.x;
		transform.GetPos()->y = m_startPos.y;
		transform.GetPos()->z = 0; //setting z-position to 0 as everything should be so
		m_shapeType = _shape;
		m_width = _w;
		m_height = _h;
		m_colour = _shapeColour;

		m_widthLimit = _widthLimit;
		m_heightLimit = _heightLimit;
		setDirection(1); //Default is outwards/positive
		setUpShape();
	}
	
	~TransitionElement();
	void setDirection(int dir);
	void update(Camera *c, Shader *s);
	void setUpShape(); //set up the shape, i.e. the vertices, indices, and the colour data
	void changeSize(); //beacause the transitions in robotron involve rectangles appearing in the centre and expanding outwards, they will change size, not position
private:
	int m_width; //the starting width of the rectangle
	int m_height;	//the starting height of the rectangle
	float m_scaleIncrement;

	int m_widthLimit;
	int m_heightLimit;

	int m_shapeType;
	int m_direction; //+1 if it is expanding, -1 if it is shrinking
	glm::vec4 m_colour;
	std::vector<glm::vec3> m_vertexCoords;
	std::vector<unsigned int> m_indexList;
	std::vector<glm::vec4> m_vertexColour;
	glm::vec3 m_startPos;
};