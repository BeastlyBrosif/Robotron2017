#ifndef HIGHSCOREHANDLER_H
#define HIGHSCOREHANDLER_H
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include "InputHandler.h"
#include "../wordBuilder/WordBuilder.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../entities/TextureSquare.h"
#include "../Config.h"
#include "../entities/Border.h"
#include "../gameEngine/InputHandler.h"
class HighScoreHandler
{
    public:
        HighScoreHandler();
        virtual ~HighScoreHandler(){
        };
        void saveHighScoreToFile(std::string name, int score);
        void loadHighScoreFile();
        void saveHighScoreVecToFile();
        void rewriteFileOrdered();
        std::pair<int, std::string> getHighestScore();
        void update(Shader * textureShader,Shader * shader, Camera * camera, Texture * letterTexture);
        void setUpWordVec();
        void runGetNameScreen(Shader * textureShader,Shader * shader, Camera * camera, Texture * letterTexture, int score);
        void addNewHighScore(int score);
        void flashCurrentLetter();
        bool isValidHighScore(int score); //TO ADD, checks whether the score passed is actually a valid highscore (larger than one in the current range)
        void clearWordVectors();

        //add method, determineIfHighScore()
    protected:
    std::string fileName = "./res/highScore/highScores.txt";
    std::string newHighScoreStr = "___";
    std::string oldNewHighScoreStr = "___";
    std::string displayNewHighScoreStr = "___";

    std::vector<std::pair<int,std::string>> highScoreVec;
    std::vector<WordBuilder *> highScoreWordVec;
    std::vector<WordBuilder *> getNameWordVec;
    private:
    Config cfg;
    Border * border;
    bool gettingName = true;
    int flashingIndex = 0;
    int currentNewScoreLetter = 0;
    int letterChoice = 65;
    InputHandler inputHandler;
    unsigned int letterChangeStartTime;
    unsigned int letterChangeInterval = 70;
    unsigned int letterFlashStartTime;
    unsigned int letterFlashInterval = 150;
    bool isCurrentLetterVisible = false;
    int m_newScore = 0;
    bool m_replacingCurrentHighScore = false;

    int m_maxNumberOfHighScores = 37;

};

#endif // HIGHSCOREHANDLER_H
