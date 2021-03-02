#ifndef MESH_H_
#define MESH_H_

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;


class Mesh {
public:

	void Draw();
	//Mesh(Vertex* vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices, Vertex * g_color_buffer_data, bool index);
	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool index, bool texture, bool text);
	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool text, float texLeft, float texRight, float texTop, float texBottom);
	void setUpMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec4> colour_buffer_data, bool index, bool texture, bool text);
	virtual ~Mesh();
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		COLOR_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

private:
	bool usesIndices;
	float textureLeft;
	float textureRight;
	float textureTop;
	float textureBottom;
};
#endif /* MESH_H_ */
