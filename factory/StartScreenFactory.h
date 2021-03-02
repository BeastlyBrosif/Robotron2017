#ifndef STARTSCREENFACTORY_H
#define STARTSCREENFACTORY_H

#include "Factory.h"
#include "../wordBuilder/WordBuilder.h"
#include "../entities/TextureSquare.h"
#include "../graphics/Texture.h"


class StartScreenFactory : public Factory
{
    public:
        StartScreenFactory(Texture * _textTex);
        ~StartScreenFactory(){
            //delete wTex;
        };
        void update(Shader * shader, Camera * camera);
        //void createEntity();
        void createWs();
        void moveW();
        void clean(); //cleans all vectors clearning the memory, make sure you dont call any of this classes methods after calling this!
        void togglePressStart();
        glm::vec4 genRandColor();
    protected:
        glm::vec4 wordColor = glm::vec4(0.8,0,0,1); //color for the words
        Texture * textTex;
        Texture * wTex;
        std::vector<WordBuilder *> wordVec;
        std::vector<TextureSquare *> wVec;
        float separation = 130;
        float startFlashInterval = 500;
        bool isPressStartShown = true;
        unsigned int pressStartStartTime;
        unsigned int moveStartTime;
        float updateInterval;
    private:
};

#endif // STARTSCREENFACTORY_H
