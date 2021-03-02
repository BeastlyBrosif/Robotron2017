#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "Mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool text, float texLeft, float texRight, float texTop, float texBottom)
{

	textureLeft = texLeft;
	textureRight = texRight;
	textureTop = texTop;
	textureBottom = texBottom;
	m_drawCount = vertices.size();

	setUpMesh(vertices, indices, colour_buffer_data, false, true,text);

}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool index, bool texture, bool text)
{
	setUpMesh(vertices, indices, colour_buffer_data, index, texture,text);

}

void Mesh::setUpMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool index, bool texture, bool text)
{
	vector<glm::vec2> texCoord;




		int verticesLength = vertices.size();
		int indicesLength = indices.size();
		if (index == true)
		{
			m_drawCount = indicesLength;
		}
		else if (index == false)
		{
			m_drawCount = verticesLength;
		}
		usesIndices = index;

		//generate the object and the buffers that will be sent to the GPU
		glGenVertexArrays(1, &m_vertexArrayObject);
		glBindVertexArray(m_vertexArrayObject);

		glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

		//send the vertices to the GPU
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        vertices.clear();

		if(texture)
		{
            if(text)
            {
                texCoord.push_back(glm::vec2(textureLeft,textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureTop));

                texCoord.push_back(glm::vec2(textureLeft, textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureTop));
                texCoord.push_back(glm::vec2(textureLeft,textureTop));
            }
            else
            {
                texCoord.push_back(glm::vec2(textureLeft,textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureTop));
                texCoord.push_back(glm::vec2(textureLeft, textureBottom));
                texCoord.push_back(glm::vec2(textureRight,textureTop));
                texCoord.push_back(glm::vec2(textureLeft,textureTop));
            }


			glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
			glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
			texCoord.clear();
		}


        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOR_VB]);
        glBufferData(GL_ARRAY_BUFFER, colour_buffer_data.size() * sizeof(colour_buffer_data[0]), &colour_buffer_data[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

        colour_buffer_data.clear();


		if (usesIndices == true)
		{
			//These indices are to be used in rendering if the flag 'index' is marked true
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
			indices.clear();
		}

		glBindVertexArray(0);
}

Mesh::~Mesh()
{

    //free the memory for the object and for the buffers
	glDeleteVertexArrays(1, &m_vertexArrayObject);


	for(int i = 0; i < NUM_BUFFERS; i++)
	{
        glDeleteBuffers(1,&m_vertexArrayBuffers[i]);
	}

}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	if (usesIndices == true)
	{
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT,(void *) 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	}
	glBindVertexArray(0);

}



