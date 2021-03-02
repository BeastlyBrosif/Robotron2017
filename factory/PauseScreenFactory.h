#ifndef PAUSESCREENFACTORY_H
#define PAUSESCREENFACTORY_H

#include "Factory.h"
#include "../wordBuilder/WordBuilder.h"
#include "../entities/TextureSquare.h"
#include "../graphics/Texture.h"


class PauseScreenFactory : public Factory
{
    public:
        PauseScreenFactory(Texture * _textTex);
        ~PauseScreenFactory(){
            delete m_transparentSquare;
        };
        void update(Camera * camera, Shader * shader, Shader * texShader);


    protected:
        glm::vec4 m_color = glm::vec4(0,0,0,0.5); //color for the background tint
        glm::vec4 wordColor = glm::vec4(0.8,0,0,1); //color for the words
        Texture * textTex;
        std::vector<WordBuilder *> wordVec;
        Mesh * m_transparentSquare; //mesh for the background tint rectangle
        Transform transform; //transform for the tint rectangle
    private:
};

#endif // PAUSESCREENFACTORY_H
