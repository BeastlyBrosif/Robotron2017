#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "TextureSquare.h"

#include "../graphics/Mesh.h"
#include "../Config.h"
#include <vector>
#include <string>

#include <SDL2/SDL_mixer.h>

void TextureSquare::init()
{
	vertexVec.push_back(glm::vec3(-1 *scale,-1*scale,0));
	vertexVec.push_back(glm::vec3(1*scale,-1*scale,0));
	vertexVec.push_back(glm::vec3(1*scale,1*scale,0));

	vertexVec.push_back(glm::vec3(-1*scale,-1*scale,0));
	vertexVec.push_back(glm::vec3(1*scale,1*scale,0));
	vertexVec.push_back(glm::vec3(-1*scale,1*scale,0));



    for(int i = 0; i < vertexVec.size(); i++)
    {
        colorVec.push_back(m_textureColor);
    }


	addMesh(new Mesh(vertexVec, indexVec,colorVec, true, textureLeft, textureRight, textureTop, textureBottom), cfg.NO_DIR);

	clearVectors();

	getTransform()->GetScale()->x -= scale;
	getTransform()->GetScale()->y -= scale;
	getTransform()->GetScale()->z -= scale;

	clearVectors();
}


