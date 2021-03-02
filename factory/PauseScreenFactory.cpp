#include "PauseScreenFactory.h"


PauseScreenFactory::PauseScreenFactory(Texture * _textTex)
{

    textTex = _textTex;
    std::vector<glm::vec3> vertexVec;
    std::vector<glm::vec4> colorVec;
    std::vector<unsigned int> indexVec;

    vertexVec.push_back(glm::vec3(cfg.negativeXedge,cfg.negativeYedge,0)); //set up the rectangle to fill the screen
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,cfg.negativeYedge,0));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,cfg.positiveYedge,0));

	vertexVec.push_back(glm::vec3(cfg.negativeXedge,cfg.negativeYedge,0));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,cfg.positiveYedge,0));
	vertexVec.push_back(glm::vec3(cfg.negativeXedge,cfg.positiveYedge,0));

    transform.GetPos()->x = 0;
    transform.GetPos()->y = 0;


    for(int i = 0; i < vertexVec.size(); i++)
    {
        colorVec.push_back(m_color);
    }


    m_transparentSquare = new Mesh(vertexVec,indexVec,colorVec,false, false, false); //set up the mesh for the tinted background


    wordVec.push_back(new WordBuilder("PAUSED",7,80,wordColor,200,0,0)); //add the word paused to the wordVec

}

void PauseScreenFactory::update(Camera * camera, Shader * shader, Shader * texShader)
{

    shader->Bind(); //bind the shader for non-textures

    glDepthMask(GL_FALSE); //allows the textures transparent background to work
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    shader->Update(transform, *camera);
    m_transparentSquare->Draw();

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);



    texShader->Bind(); //bind the texture shader
    textTex->Bind(); //bind the texture for the text
    for(int i = 0; i < wordVec.size(); i++)
    {
        wordVec[i]->update(texShader, camera); //call the update method of the wordbuilder to draw the word to the screen
    }

}

