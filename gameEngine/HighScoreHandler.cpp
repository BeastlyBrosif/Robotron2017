#include "HighScoreHandler.h"
#include<bits/stdc++.h>

HighScoreHandler::HighScoreHandler()
{

    letterChangeStartTime = SDL_GetTicks(); //initialise the change and flash start times
    letterFlashStartTime = SDL_GetTicks();

}
/*
This function is called from other classes to add a new highscore to the file, it'll set the state to getting name so the user can enter thier name to save with thier highscore
*/
void HighScoreHandler::addNewHighScore(int score)
{
    clearWordVectors();
    setUpWordVec();
    if(isValidHighScore(score))
    {

        m_newScore = score;
        gettingName = true;

        std::string scoreWordBuild = "SCORE: " + std::to_string(m_newScore);
        getNameWordVec[1]->replaceWord(scoreWordBuild,250,-100);


    }
    else
    {
        gettingName = false;
    }



}

bool HighScoreHandler::isValidHighScore(int score)
{
    loadHighScoreFile();

    if(!highScoreVec.empty())
    {
        if(highScoreVec.size() < m_maxNumberOfHighScores + 1)
        {
            return true;
        }
        else
        {
            if(score > highScoreVec[0].first)
            {
                m_replacingCurrentHighScore = true;
                return true;
            }
            else
            {
                return false;
            }
        }

    }
    else
    {
        return true;
    }

}

void HighScoreHandler::clearWordVectors()
{
    for(int i = 0; i < highScoreWordVec.size(); i++)
    {
        delete highScoreWordVec[i];
    }
    highScoreWordVec.clear();

    for(int i = 0; i < getNameWordVec.size(); i++)
    {
        delete getNameWordVec[i];
    }
    getNameWordVec.clear();
}


void HighScoreHandler::saveHighScoreToFile(std::string name, int score)
{

    std::pair<int, std::string> PAIR;


    loadHighScoreFile();

    if(m_replacingCurrentHighScore)
    {
        highScoreVec.erase(highScoreVec.begin());
        m_replacingCurrentHighScore = false;
    }


    PAIR.first = score;
    PAIR.second = name;

    highScoreVec.push_back(PAIR);

    sort(highScoreVec.begin(), highScoreVec.end());
    saveHighScoreVecToFile();
    highScoreVec.clear();

    gettingName = false;

}

std::pair<int, std::string> HighScoreHandler::getHighestScore()
{
    loadHighScoreFile();

    std::pair<int, std::string> HIGHSCORE;

    HIGHSCORE = highScoreVec[highScoreVec.size()-1];
    highScoreVec.clear();
    return HIGHSCORE;

}

void HighScoreHandler::loadHighScoreFile()
{

    highScoreVec.clear();
    std::ifstream file;

    file.open(fileName,std::ios::in);

    std::string line;
    std::string token;
    std::string delim = ",";

    std::string name;
    std::string score;

    std::pair<int, std::string> PAIR;

    while(file >> line)
    {
        score = token = line.substr(0,line.find(delim));

        line.erase(0,line.find(delim) + 1);

        name = token = line.substr(0,line.length());
        PAIR.first = std::stoi(score);
        PAIR.second = name;
        highScoreVec.push_back(PAIR);
    }

    file.close();


}

void HighScoreHandler::saveHighScoreVecToFile()
{
    std::ofstream file;


    file.open(fileName, std::ios::out);

    for(int i = 0; i < highScoreVec.size();i++)
    {
        std::string sb = std::to_string(highScoreVec[i].first) + "," + highScoreVec[i].second + "\n";
        file << sb;
    }

    file.close();
    newHighScoreStr = "___";
    oldNewHighScoreStr = "___";
    currentNewScoreLetter = 0;
}


void HighScoreHandler::rewriteFileOrdered()
{
    loadHighScoreFile();
    sort(highScoreVec.begin(), highScoreVec.end());
    saveHighScoreVecToFile();
    highScoreVec.clear();
}

void HighScoreHandler::setUpWordVec()
{
    clearWordVectors();
    loadHighScoreFile();

    highScoreWordVec.clear();
    glm::vec4 wordColor = glm::vec4(0.8,0,0,1); //color for the words
    highScoreWordVec.push_back(new WordBuilder("HIGHSCORES:",6,70,wordColor,300,200,0));


    getNameWordVec.push_back(new WordBuilder(displayNewHighScoreStr,6,70,wordColor,100,0,0));
    std::string scoreWordBuild = "SCORE: " + std::to_string(m_newScore);
    getNameWordVec.push_back(new WordBuilder(scoreWordBuild,6,70,wordColor,250,-100,0));
    getNameWordVec.push_back(new WordBuilder("NEW HIGHSCORE!",6,70,wordColor,400,100,0));



    int offsetBeforeBottom = 50;

    int x,y;
    x = 600;
    y = 25;

    std::string sb = "";
    for(int i = 0; i < highScoreVec.size(); i++)
    {
        if(y - offsetBeforeBottom <= cfg.negativeYBorder)
        {

            x -= 400;
            y = 25;
        }

        sb = std::to_string(i) + ") " +  highScoreVec[highScoreVec.size() - 1 - i].second + " " +  std::to_string(highScoreVec[highScoreVec.size() - 1 - i].first);
        highScoreWordVec.push_back(new WordBuilder(sb,4,25,wordColor,x,y,0));
        y -= 50;

    }



}

void HighScoreHandler::update(Shader * textureShader,Shader * shader, Camera * camera, Texture * letterTexture)
{
    Border border(1,0,0,1, false);
    textureShader->Bind();
    letterTexture->Bind();
    //gettingName = true;
    if(gettingName)
    {
        runGetNameScreen(textureShader, shader, camera, letterTexture, 5);

    }
    else
    {
        for(int i = 0; i < highScoreWordVec.size(); i++)
        {
            highScoreWordVec[i]->update(textureShader, camera);
        }
    }



    border.update(camera, shader);

}

void HighScoreHandler::runGetNameScreen(Shader * textureShader,Shader * shader, Camera * camera, Texture * letterTexture, int score)
{

    //65 and 90


    if((SDL_GetTicks() - letterChangeStartTime) > letterChangeInterval)
    {
        if(inputHandler.checkIfWPressed() || inputHandler.checkIfDPadUpPressed())
        {
            letterChoice++;

        }
        else if(inputHandler.checkIfSPressed() || inputHandler.checkIfDPadDownPressed())
        {
            letterChoice--;

        }
        if(letterChoice == 91)
        {
            letterChoice = 65;
        }
        else if(letterChoice == 64)
        {
            letterChoice = 90;
        }

        if(inputHandler.checkIfEnterPressed() || inputHandler.checkIfControllerAPressed())
        {
            letterChoice = 65;
            currentNewScoreLetter++;
            displayNewHighScoreStr = newHighScoreStr;
            getNameWordVec[0]->replaceWord(newHighScoreStr,100,0); //draw a new word
            if(currentNewScoreLetter == getNameWordVec.size())
            {
                gettingName = false;
                saveHighScoreToFile(newHighScoreStr,m_newScore);
                loadHighScoreFile();
                setUpWordVec();

            }

        }


        letterChangeStartTime = SDL_GetTicks();
    }


    char c = letterChoice;
    if(currentNewScoreLetter < 4)
    {
        newHighScoreStr[currentNewScoreLetter] = c;

    }


    flashCurrentLetter();

    if(oldNewHighScoreStr.compare(displayNewHighScoreStr) != 0)
    {
        getNameWordVec[0]->replaceWord(displayNewHighScoreStr,100,0); //draw a new word
    }


    oldNewHighScoreStr = displayNewHighScoreStr;



    for(int i = 0; i < getNameWordVec.size(); i++)
    {
        getNameWordVec[i]->update(textureShader, camera);
    }



}

void HighScoreHandler::flashCurrentLetter()
{

    if((SDL_GetTicks() - letterFlashStartTime) > letterFlashInterval)
    {

        if(isCurrentLetterVisible)
        {
            isCurrentLetterVisible = false;
            displayNewHighScoreStr[currentNewScoreLetter] = ' ';
        }
        else
        {
            isCurrentLetterVisible = true;
            displayNewHighScoreStr[currentNewScoreLetter] = newHighScoreStr[currentNewScoreLetter];
        }
        letterFlashStartTime = SDL_GetTicks();
    }

}
