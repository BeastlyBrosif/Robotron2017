#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <SDL2/SDL.h>
#include <iostream>
#include "../Config.h"


class InputHandler
{
    public:
        InputHandler();
        virtual ~InputHandler();
        void getInput(bool * _bulletDirArray, bool * _playerDirArray);
        bool checkIfBulletShot(bool * bulletDirArray);
        bool checkIfStartPressed();
        bool checkIfEnterPressed();
        bool checkIfEscapePressed();
        bool checkIfDeletePressed();
        bool checkIfWPressed();
        bool checkIfSPressed();
        bool checkIfDPadUpPressed();
        bool checkIfDPadDownPressed();
        bool checkIfControllerAPressed();

        std::string getInputAsString();
        std::string clearInputString();

    protected:
     Config cfg;

    bool * bulletDirArray;
	bool * playerDirArray;



    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); //get the currect states of the keys for the keyboard

    SDL_GameController * controllerHandle = NULL; //controller handle
     //set up controller values
    bool controllerMoveUp = false;
    bool controllerMoveDown = false;
    bool controllerMoveLeft = false;
    bool controllerMoveRight = false;

    bool controllerShootUp = false;
    bool controllerShootDown = false;
    bool controllerShootLeft = false;
    bool controllerShootRight = false;

    bool controllerDPadUp = false;
    bool controllerDPadDown = false;

    bool controllerA = false;

    SDL_Event event;
    int leftStickX;
    int leftStickY;
    int rightStickX;
    int rightStickY;

    bool controllerStart;
    bool keyboardEnter;
    bool keyboardESC;
    bool keyboardDelete;
    bool keyboardW;
    bool keyboardS;


    unsigned int escapeDelayStartTime;
    unsigned int controllerStartStartTime;

    unsigned int deleteDelayStartTime;
    unsigned int deleteDelayInterval = 100;

    std::string builtString = "";


    private:
};

#endif // INPUTHANDLER_H
