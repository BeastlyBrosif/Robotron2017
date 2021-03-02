#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif


#include <fstream>
#include <glm/glm.hpp>
#include <cstring>

#include "modelLoader.h"

/* Author: Nimrod Wynne
* Last Changed: 07/02/2018
* Description: This class reads in an .OBJ (wavefront) file and acquires the position, uvs, and normal vertices from the file
* as well as the indices that make up the faces. 
*/
ModelLoader::ModelLoader(int loaderType) 
{
	type = loaderType; //this tells the loader what kind of file to load.
					   //currently, only OBJ capabilities are implemented but I have introduced the flexibility for other types in the future
					   // 1 is the key for OBJ
	//initialise the size variables as -1 so if there is an error in acquiring them, we know
	numVertices = -1;
	numIndices  = -1;
	numNormals  = -1;
	numUVs      = -1;

	maxVertices = 2000; //This must be set as the colour vertices are placed inside the limits of the max number of vertices 
					   //without knowing how many total vertices there are
}
ModelLoader::~ModelLoader() 
{
	clearMaterials();
}
//COMMON PROBLEMS for model not appearing properly:
//-not enough difference between the vertices (some faces engulf others and stop them being rendered)
//-model is facing wrong side and needs to be rotated (180deg for example)

void ModelLoader::readMTLfile(std::string path) //This will read an OBJ file with the materials for the OBJ file in the 
{
	std::ifstream file;
	file.open(path);
	std::string line;
	if (!file.is_open())
	{
		std::cerr << "Error occurred when opening .mtl file! ['" << path << "']" << std::endl;
	}	
	else
	{
		if (cfg.B_DEBUG_MODELLOADER) { std::cout << "Reading file: " << path << std::endl; }
		int counter = 0;
		int lineLength = 0;
		struct Material *tempMaterial = NULL;
		while (!file.eof())
		{
			getline(file, line);
			lineLength = line.length();
			if (line.find("newmtl") != std::string::npos)
			{
				counter++;
				std::size_t found = line.find("newmtl");
				std::string materialName = line.substr(7, std::string::npos); //material name starts at index 7
				//save material and details
				tempMaterial = new struct Material;
				tempMaterial->materialName = materialName;
		//		if(cfg.B_DEBUG_MODELLOADER) { std::cout << "Reading Material: " << materialName << std::endl; }
				getline(file, line); //advance the line to read Ns
				std::string::size_type sz;
				float tmpNs = std::stof(line.substr(3, std::string::npos), &sz);
				tempMaterial->Ns = tmpNs;
				getline(file, line); //advance the line to read Ka
				float tmpKa[3];
				tmpKa[0] = std::stof(line.substr(3, 10), &sz);
				tmpKa[1] = std::stof(line.substr(12, 19), &sz);
				tmpKa[2] = std::stof(line.substr(21, std::string::npos), &sz);
				tempMaterial->Ka[0] = tmpKa[0];
				tempMaterial->Ka[1] = tmpKa[1];
				tempMaterial->Ka[2] = tmpKa[2];

				getline(file, line); //advance the line to read Kd
				float tmpKd[3];
				tmpKd[0] = std::stof(line.substr(3, 10), &sz);
				tmpKd[1] = std::stof(line.substr(12, 19), &sz);
				tmpKd[2] = std::stof(line.substr(21, std::string::npos), &sz);
				tempMaterial->Kd[0] = tmpKd[0];
				tempMaterial->Kd[1] = tmpKd[1];
				tempMaterial->Kd[2] = tmpKd[2];

				getline(file, line); //advance the line to read Ks
				float tmpKs[3];
				tmpKs[0] = std::stof(line.substr(3, 10), &sz);
				tmpKs[1] = std::stof(line.substr(12, 19), &sz);
				tmpKs[2] = std::stof(line.substr(21, std::string::npos), &sz);
				tempMaterial->Ks[0] = tmpKs[0];
				tempMaterial->Ks[1] = tmpKs[1];
				tempMaterial->Ks[2] = tmpKs[2];

				getline(file, line); //advance the line to read Ke
				float tmpKe[3];
				tmpKe[0] = std::stof(line.substr(3, 10), &sz);
				tmpKe[1] = std::stof(line.substr(12, 19), &sz);
				tmpKe[2] = std::stof(line.substr(21, std::string::npos), &sz);
				tempMaterial->Ke[0] = tmpKe[0];
				tempMaterial->Ke[1] = tmpKe[1];
				tempMaterial->Ke[2] = tmpKe[2];

				getline(file, line); //advance the line to read Ne
				float tmpNi = std::stof(line.substr(3, std::string::npos), &sz);
				tempMaterial->Ni = tmpNi;

				getline(file, line); //advance the line to read d
				float tmpd = std::stof(line.substr(3, std::string::npos), &sz);
				tempMaterial->d = tmpd;
				
				materialList.push_back(tempMaterial);
				
			}
		}
	}
}
//NOTE!!! When exporting and .OBJ file select 'triangualate faces' on the application
void ModelLoader::readOBJfile(std::string path) 
{
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;

	std::vector<unsigned int> vIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;

	struct Material *tempMaterial = NULL;

	FILE *file = fopen(path.c_str(), "r"); //open the file in read mode
	if (file == NULL)
	{
		printf("ERROR: Failed to open file: %s in OBJ LOADER\n", path.c_str());
	}
	colourList.resize(maxVertices); //set the size of the colourlist to something big, that way we won't run out of room while allocating colours	
							//its size will be shrunk down afterwards
	int coloursAdded = 0;
	while (1)
	{
		char line[128];
		int result = fscanf(file, "%s\n", line);
		if (result == EOF)
		{
			break;
		}
		if (strcmp(line, "v") == 0) //line read begins with v -> vertex
		{
			glm::vec3 temp_v;
			fscanf(file, "%f %f %f\n", &temp_v.x, &temp_v.y, &temp_v.z);
			tempVertices.push_back(temp_v);
		}
		else if (strcmp(line, "vt") == 0) //line read begins with a vt -> vertex texture/uv
		{
			glm::vec2 temp_uv(0.0f, 0.0f);
			fscanf(file, "%f %f\n", &temp_uv.x, temp_uv.y);
			uvs.push_back(temp_uv);
		}
		else if (strcmp(line, "vn") == 0) //line read vn -> vertex normal
		{
			glm::vec3 temp_vn;
			fscanf(file, "%f %f %f\n", &temp_vn.x, &temp_vn.y, &temp_vn.z);
			tempNormals.push_back(temp_vn);
		}
		else if (strcmp(line, "usemtl") == 0) //line read "usemtl". we want to read in the material's name
		{
			char buffer[18];
			fgets(buffer, 18, file);
			std::string materialName = buffer; //get the name of the material
			materialName = materialName.substr(0, materialName.size() - 1);
			for (unsigned int i = 0; i < materialList.size(); i++)
			{
				if (materialList.at(i)->materialName == materialName)
				{
					//found the material to be used
					tempMaterial = materialList.at(i);
					break;
				}
			}
		}
		else if (strcmp(line, "f") == 0) //line read is f -> these are the faces and will be used to construct the indices
		{
			unsigned int vertexIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0],
																 &vertexIndex[1], &normalIndex[1],
																 &vertexIndex[2], &normalIndex[2]); //we are ignoring the uv indices as we won't use them in this project
			
			if (vertexIndex[0] == NULL || vertexIndex[1] == NULL || vertexIndex[2] == NULL)
			{
				printf("Parser requires the OBJ file to be in the triangular format!\n");
			}
			vIndices.push_back(vertexIndex[0] - 1);
			vIndices.push_back(vertexIndex[1] - 1);
			vIndices.push_back(vertexIndex[2] - 1);

			if (tempMaterial != NULL)
			{
				if ((vertexIndex[0] - 1) == maxVertices - 3) //the number of vertices is close to the limit
				{
					colourList.resize(colourList.size() * 2);
				}
				colourList.at(vertexIndex[0] - 1) = glm::vec4(tempMaterial->Kd[0], tempMaterial->Kd[1], tempMaterial->Kd[2], 1.0);
				colourList.at(vertexIndex[1] - 1) = glm::vec4(tempMaterial->Kd[0], tempMaterial->Kd[1], tempMaterial->Kd[2], 1.0);
				colourList.at(vertexIndex[2] - 1) = glm::vec4(tempMaterial->Kd[0], tempMaterial->Kd[1], tempMaterial->Kd[2], 1.0);
				coloursAdded += 1;
			}
			
			//uv indices not required but can be implemented as above and below
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	fclose(file); //close the file
	indices = vIndices;
	vertices = tempVertices;
	//get the sizes of the lists
	numVertices = vertices.size();
	numIndices = indices.size();
	colourList.resize(numVertices);
}
void ModelLoader::clearMaterials()
{
	int numberofMaterials = materialList.size();
	for (int i = 0; i < numberofMaterials; i++)
	{
		delete materialList.at(i);
	}
	materialList.clear();
}


std::vector<glm::vec3> ModelLoader::getVertices() { return vertices; }
std::vector<glm::vec2> ModelLoader::getUVs() { return uvs; }
std::vector<glm::vec3> ModelLoader::getNormals() { return vnormals; }
std::vector<unsigned int> ModelLoader::getIndices() { return indices; }
std::vector<glm::vec4> ModelLoader::getColourList() { return colourList; }
