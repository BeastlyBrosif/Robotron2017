//============================================================================
// Name        : OpenGLFun.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <iostream>
#include "graphics/display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Transform.h"
#include "graphics/Camera.h"
#include <string>

#include "entities/Player.h"

#include "Config.h"
#include <ctime>
#include <cstdlib>
#include "factory/Factory.h"
#include "factory/BulletFactory.h"
#include "entities/Electrode.h"
#include "entities/Entity.h"
#include "factory/EnemyFactory.h"
#include "factory/FamilyFactory.h"
#include "factory/PlayerFactory.h"
#include "graphics/Texture.h"
#include "wordBuilder/WordBuilder.h"
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include "entities/TextureSquare.h"
#include "entities/Border.h"
#include "gameEngine/InputHandler.h"
#include "factory/StartScreenFactory.h"
#include "factory/PauseScreenFactory.h"
#include "gameEngine/HighScoreHandler.h"
#include "../graphics/Transition.h"


std::vector<Entity *> wordVec;


unsigned int GLOBAL_TIME_OFFSET;

void initTimeOffset()
{
    GLOBAL_TIME_OFFSET = SDL_GetTicks();

}

void addTimeOffSet(unsigned int offset)
{
    GLOBAL_TIME_OFFSET = offset;

    //could update entities here
}


bool GLOBAL_ISPAUSED;


bool initSDL()
{

	 if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	 if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	 {
		// return false;
	 }
    Mix_Volume(-1, 50);
	 return true;

}



int main(int argc, char * argv[]) {
    Config cfg;
    Transition t(glm::vec3(0, 0, 0), 25, glm::vec4(1.0, 0, 0, 1.0), 1500, cfg.PENTAGON);

   // cfg.GLOBAL_TIME_OFFSET = 0;
    initTimeOffset();

    srand(SDL_GetTicks());
    glm::vec4 wordColor = glm::vec4(0,0.5,1,1);
    bool paused = true; //not yet implemented
    bool runningHighScoreScreen = false;
	initSDL();
	WordBuilder wordBuilder("",cfg.ENEMY_SCORE_WORD_SCALE, 20,wordColor, (cfg.positiveXedge - 10), (cfg.positiveYedge - 10), 0);


	Display display(cfg.WIDTH,cfg.HEIGHT, "Robotron 2017", cfg.FULLSCREEN);

	BulletFactory bulletFactory;
	FamilyFactory familyFactory(bulletFactory.getBulletVec());

    EnemyFactory enemyFactory(bulletFactory.getBulletVec(), familyFactory.getFamilyVectorPointer());


	Shader shader("./res/basicShader");
	Shader textureShader("./res/texShader");
	Camera camera(glm::vec3(0,0,0.0f), 1.22173f, (float)cfg.WIDTH/(float)cfg.HEIGHT, 0.01f, 1000.0f);
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	bool bulletDirArray[cfg.NUM_DIRECTIONS + 1] = {false}; //direction arrays, the values will be true if that diretion has been pressed
	bool playerDirArray[cfg.NUM_DIRECTIONS + 1] = {false};

	SDL_Event event;

    //temporary, allow the offset to be added for when the game is paused and when the start screen is being displayed, in the actual game engine these will probably be separated
    unsigned int START_OF_PAUSE_TIME;

    unsigned int START_OF_START_SCREEN = SDL_GetTicks();

	enemyFactory.createEntity(cfg.TANK,cfg.FACTORY_ROUGE_VALUE ,cfg.FACTORY_ROUGE_VALUE, 5);
	enemyFactory.createEntity(cfg.GRUNT,cfg.FACTORY_ROUGE_VALUE ,cfg.FACTORY_ROUGE_VALUE, 3);
	enemyFactory.createEntity(cfg.ENFORCER, cfg.FACTORY_ROUGE_VALUE,cfg.FACTORY_ROUGE_VALUE, 3);
    //enemyFactory.createEntity(cfg.BRAIN, 0, 0, 1);
    //enemyFactory.createEntity(cfg.BRAIN, 250, 250, 1);
    enemyFactory.createEntity(cfg.BRAIN, cfg.FACTORY_ROUGE_VALUE,cfg.FACTORY_ROUGE_VALUE,5);
	//enemyFactory.createEntity(cfg.ELECTRODE, 50, 50, 1);
	//enemyFactory.createEntity(cfg.ELECTRODE, 0, 0, 1);
	enemyFactory.createEntity(cfg.HULK, cfg.FACTORY_ROUGE_VALUE,cfg.FACTORY_ROUGE_VALUE, 5);

    enemyFactory.createEntity(cfg.ELECTRODE, cfg.FACTORY_ROUGE_VALUE, cfg.FACTORY_ROUGE_VALUE, 5);
    enemyFactory.createEntity(cfg.SPHEROID, cfg.FACTORY_ROUGE_VALUE, cfg.FACTORY_ROUGE_VALUE, 5);

    familyFactory.createEntity(cfg.SON, cfg.FACTORY_ROUGE_VALUE, cfg.FACTORY_ROUGE_VALUE,2);
    familyFactory.createEntity(cfg.MUM, cfg.FACTORY_ROUGE_VALUE, cfg.FACTORY_ROUGE_VALUE,2);
    familyFactory.createEntity(cfg.DAD, cfg.FACTORY_ROUGE_VALUE, cfg.FACTORY_ROUGE_VALUE,5);




	//familyFactory.createEntity(cfg.SON,100,100,1);

	PlayerFactory playerFactory;
	Player * player = (playerFactory.getPlayerPointer());

	Texture textTex("./res/Robotron.png");


	float spacing = (float)-1/(float) 2;

	std::vector<Entity *> wordVec2;

    //ChangeAnimation animation;

	textTex.Bind();
	//specifiy time on screen as 0 as we want this permenantly on screen
	(wordBuilder).buildWord("SCORE:0", cfg.positiveXedge - 10, cfg.positiveYedge - 10, 0);

    InputHandler inputHandler;

    Border border(1,0,0,1, true); //create a border and pass it red as the color

    StartScreenFactory startScreenFac(&textTex);
    PauseScreenFactory pauseScreenFac(&textTex);

    bool runningStartScreen = true;


    enemyFactory.toggleIsPaused();
    familyFactory.toggleIsPaused();
    playerFactory.toggleIsPaused();
    bulletFactory.toggleIsPaused(); //pause the factories from moving the entities

    HighScoreHandler *highScoreHandler = new HighScoreHandler();

    bool playerKilledToggle = true;


	while(!display.isClosed()) //FOR NOW, ALL THIS IF STATEMENT SEPARATING UNTILL THE GAME ENGINE IS DONE AND THINGS CAN BE RUN SEPARATELY IN DIFFERENT METHODS
	{

        display.getStartTime(); //get the time in milliseconds from the begininng of frame




        if(runningStartScreen)
        {
            inputHandler.getInput(bulletDirArray,playerDirArray); //fill the direction arrays with the keys that were pressed
            if(inputHandler.checkIfStartPressed() || inputHandler.checkIfEnterPressed()) //check if enter or start has been pressed, to dismiss the start screen
            {
                if(runningStartScreen)
                {
                    paused = false;
                    runningStartScreen = false;
                    startScreenFac.clean();
                    addTimeOffSet(SDL_GetTicks() - START_OF_START_SCREEN);
                    enemyFactory.addOffsetToObjects(GLOBAL_TIME_OFFSET);
                    familyFactory.addOffsetToObjects(GLOBAL_TIME_OFFSET);
                    enemyFactory.toggleIsPaused();
                    familyFactory.toggleIsPaused();
                    playerFactory.toggleIsPaused();
                    bulletFactory.toggleIsPaused();

                }

        }

        }


        inputHandler.getInput(bulletDirArray,playerDirArray); //fill the direction arrays with the keys that were pressed
        if(inputHandler.checkIfEscapePressed() || inputHandler.checkIfStartPressed() || inputHandler.checkIfDeletePressed())
        {
            if(paused)
            {
                paused = false;
                enemyFactory.addOffsetToObjects(GLOBAL_TIME_OFFSET);
                familyFactory.addOffsetToObjects(GLOBAL_TIME_OFFSET);
                enemyFactory.toggleIsPaused();
                familyFactory.toggleIsPaused();
                playerFactory.toggleIsPaused();
                bulletFactory.toggleIsPaused();
            }
            else
            {
                paused = true;
                START_OF_PAUSE_TIME = SDL_GetTicks();
                enemyFactory.toggleIsPaused();
                familyFactory.toggleIsPaused();
                playerFactory.toggleIsPaused();
                bulletFactory.toggleIsPaused();
            }
        }




        if(inputHandler.checkIfDeletePressed() || !player->getPlayerAlive() && playerKilledToggle)
        {

            if(playerKilledToggle)
            {
                playerKilledToggle = false;
            }


            if(runningHighScoreScreen)
            {
                runningHighScoreScreen = false;
                paused = false;
            }
            else
            {
                highScoreHandler->addNewHighScore(player->getScore());
                runningHighScoreScreen = true;
                paused = true;

            }
        }

        if (inputHandler.checkIfBulletShot(bulletDirArray)) //call a method to check if a bullet was actually shot, if so, create a bullet for that direction
		{
            bulletFactory.createEntity(((*player).getTransform())->GetPos()->x, ((*player).getTransform())->GetPos()->y, bulletDirArray);
		}


		int prevScore = player->getScore(); //check if the player's score changes during this frame
		display.clear(0,0,0,0);


		textureShader.Bind();
		textTex.Bind();

        if(paused)
        {

            if(!runningStartScreen)
            {
                addTimeOffSet(SDL_GetTicks() - START_OF_PAUSE_TIME);
            }
        }


		if(!runningStartScreen && !runningHighScoreScreen)
		{
            if (t.getFinishedState() == true)
			{

                //std::cout << "UPDATING" << std::endl;

                bulletFactory.update(&camera, &shader);
                playerFactory.update(&camera, &shader, playerDirArray);
                enemyFactory.update(&camera, &shader,&textureShader, player);
                familyFactory.update(&camera, &shader, &textureShader, player);
            }
            wordBuilder.update(&textureShader, &camera);
            border.update(&camera, &shader);
            if (t.getFinishedState() == false)
			{
				bool t_f = t.getFinishedState();
				t.createElements();
				t.update(&shader, &camera);
				if (t.getFinishedState() != t_f)
				{
					t.cleanElements();
				}
			}



		}
		else
		{
            startScreenFac.update(&textureShader, &camera);

		}

		if(paused && !runningStartScreen && !runningHighScoreScreen)
		{
            pauseScreenFac.update(&camera, &shader, &textureShader);

		}

		if(runningHighScoreScreen)
		{

            highScoreHandler->update(&textureShader, &shader, &camera, &textTex);

		}


		if (prevScore != player->getScore()) //if the score has changed during the last frame
		{
			string score = "SCORE:" + to_string(player->getScore()); //build the string
			(wordBuilder).replaceWord(score, cfg.positiveXedge - 10, cfg.positiveYedge - 10); //draw a new word
		}

		display.checkFPS();

        display.swapBuffers();


	}


	return 0;

}
