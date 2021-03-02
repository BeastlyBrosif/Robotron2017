/*
 * Grunt.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: callum
 */
#define GLM_ENABLE_EXPERIMENTAL
#include "Square.h"

#include "../graphics/Mesh.h"
#include "../Config.h"
#include <vector>
#include <string>

#include <SDL2/SDL_mixer.h>

namespace std {

void Square::init()
{
	ModelLoader modelLoader(1);
	modelLoader.readOBJfile("./res/Grunt1Model.obj");
	modelLoader.getVerticesSize();

    float aspect = 800/600;

    float left, right, bottom, top;

    right = (m_width / 2);
    left = 0 - right;

    top = (m_height / 2);
    bottom = 0 - top;



	vertexVec.push_back(glm::vec3(left,bottom,0));
	vertexVec.push_back(glm::vec3(right,bottom,0));
	vertexVec.push_back(glm::vec3(right,top,0));

	vertexVec.push_back(glm::vec3(left,bottom,0));
	vertexVec.push_back(glm::vec3(right,top,0));
	vertexVec.push_back(glm::vec3(left,top,0));



    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));

	addMesh(new Mesh(vertexVec, indexVec,colorVec, false, false, false), cfg.NO_DIR);

	clearVectors();


	clearVectors();
}


void Square :: setBlack()
{
    clearVectors();

      float aspect = 800/600;

    float left, right, bottom, top;

    right = (m_width / 2);
    left = 0 - right;

    top = (m_height / 2);
    bottom = 0 - top;

    vertexVec.push_back(glm::vec3(left,bottom,0));
	vertexVec.push_back(glm::vec3(right,bottom,0));
	vertexVec.push_back(glm::vec3(right,top,0));

	vertexVec.push_back(glm::vec3(left,bottom,0));
	vertexVec.push_back(glm::vec3(right,top,0));
	vertexVec.push_back(glm::vec3(left,top,0));



	float r = 0;
	float g = 0;
	float b = 0;

	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
	colorVec.push_back(glm::vec4(r,  g,  b, 1));
    meshVec.clear();

	addMesh(new Mesh(vertexVec, indexVec,colorVec, false, false, false),cfg.NO_DIR);


}

Square::~Square() {
	// TODO Auto-generated destructor stub
}


} /* namespace std */
