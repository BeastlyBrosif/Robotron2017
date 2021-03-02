/*
	Class: modelLoader
	Short Description: loads a 3d model and its materials from its .obj and .mtl files
	Author: Nimrod Wynne
*/
#pragma once
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <string>


#include "../Config.h"


struct Material 
{	
	std::string materialName; //the name of the material in the .mtl file
	float Ns; //Phong specular component (1-1000) 
	float Ka[3]; //Ambient colour weighted by the ambiet coeeficient
	float Kd[3]; //Diffuse colour weighted by the diffuse coefficient
	float Ks[3]; //Specular colour weighted by the specular coefficient
	float Ke[3]; //emmisive coefficent (how much light is emmitted by the material)
	float Ni; //Refraction Index -> values range from 1 upwards where 1 is no refraction (NORMALLY 1)
	float d;  //Dissolve factor (pseudo-transparency) Values from 0-1, 0 is completely transparent, 1 is opaque (NORMALLY 1)
};

//Helpful tips for using the .mtl loader and therefore using materials:
/*  The class still works for loading .obj files into 3d models without any materials
	The .mtl file reader feature is for reading models that have been created with materials on blender software. The most important attribute to be read
	is the Kd (diffuse colour) everything else (currently) is not used.
	The .mtl file should be used before reading the .obj file as the materials that are loaded in have their use specified in the .obj file
	The .obj file states a material to be used and then the vertice indexes that these materials apply to, that way this class can assign colours to each vertex 
	like in the blender model.
	Common issues (that I have come across):
	If the a similar but not quite right model is being displayed, consider flipping the model 180 degrees on the x/y axes
	If some parts of the model are not showing, they may be too far away from the origin of the scene in blender. The model must be as close as possible to the z origin
	Leave a nice gap between faces in the z (up) direction so colours do not clip and disturb each other
	NOTE: to use
*/
class ModelLoader
{
public:
	ModelLoader(int loaderType);
	virtual ~ModelLoader();

	void readMTLfile(std::string path); //reads the materials into a vector of struct Material from an .mtl file
	void readOBJfile(std::string path); //reads vertices and indices (derived from faces) from an .obj file specified in 'path'
	

	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getNormals();
	std::vector<unsigned int> getIndices();
	std::vector<glm::vec4> getColourList();

	inline int getVerticesSize() { return numVertices; }
	inline int getUVSize() { return numUVs; }
	inline int getNormalSize() { return numNormals; }
	inline int getIndicesSize() { return numIndices; }

	void clearMaterials(); //delete the materials in the materialList vector
private:
	int type;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> vnormals;

	std::vector<unsigned int> indices;

	std::vector<struct Material*> materialList; //hold a list of all the materials read into from the .mtl file
	std::vector<glm::vec4> colourList; //holds the values of the diffuse colour for each vertex

	int numVertices;
	int numUVs;
	int numNormals;
	int numIndices;

	unsigned int maxVertices; //this limits how many colours can be stored in this class
	Config cfg;
};