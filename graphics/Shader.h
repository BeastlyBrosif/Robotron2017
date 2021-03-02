/*
 * Shader.h
 *
 *  Created on: 16 Dec 2017
 *      Author: callum
 */

#ifndef SHADER_H_
#define SHADER_H_
#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

using namespace std;

class Shader {
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);


	GLuint m_program;

	GLuint m_shaders[NUM_SHADERS];

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};


	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif /* SHADER_H_ */

