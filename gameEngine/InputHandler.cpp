#include "InputHandler.h"

InputHandler::InputHandler() //costructor sets up controller if there is one connected
{
    if(SDL_NumJoysticks() < 1) //check if there is a controller connected
    {
        if(cfg.B_DEBUG_INPUT_HANDLER){std::cout << "InputHandler: No controllers (joysticks)" << std::endl;}
    }
    else //if there is, assign the first one to the controller handle, this will probably have to be changed when we start using joysticks
    {
        if(cfg.B_DEBUG_INPUT_HANDLER){std::cout << "InputHandler: Connecting controller..." << std::endl;}
        controllerHandle = SDL_GameControllerOpen(0);

        if(cfg.B_DEBUG_INPUT_HANDLER){std::cout << "InputHandler: Controller connected" << std::endl;}
    }

    escapeDelayStartTime = SDL_GetTicks();
    deleteDelayInterval = SDL_GetTicks();
    controllerStartStartTime = SDL_GetTicks();
    clearInputString();


}

InputHandler::~InputHandler()
{
    if(controllerHandle)
	{
        if(cfg.B_DEBUG_INPUT_HANDLER){std::cout << "InputHandler: Closing controller" << std::endl;}
        SDL_GameControllerClose(controllerHandle);
	}
}

bool InputHandler::checkIfBulletShot(bool * bulletDirArray) //returns whether a bullet was shot based on the state of the bullet dir array passed in
{
    for(int i = 0;i < cfg.NUM_DIRECTIONS;i++) //if there is a direction flag that is true, return true, otherwise return false
    {
        if(bulletDirArray[i])
        {
            return true;
        }

    }
    return false;
}

/*
getInput() will set both dir arrays to false, and then set the respective array values to true based on the direction of input recived from the controller or keyboard
Checks what buttons were pressed for that frame

*/

void InputHandler::getInput(bool * bulletDirArray, bool * playerDirArray) //passed the dir arrays for player and bullet
{

        unsigned int currentTime = SDL_GetTicks();

        keyboardESC = false;
        controllerStart = false;
        keyboardEnter = false;
        keyboardDelete = false;
        keyboardW = false;
        keyboardS = false;
        controllerMoveUp = false; //reset all controller direction bools to false
        controllerMoveDown = false;
        controllerMoveLeft = false;
        controllerMoveRight = false;

        controllerShootUp = false;
        controllerShootDown = false;
        controllerShootLeft = false;
        controllerShootRight = false;

        if(controllerHandle != 0 && SDL_GameControllerGetAttached(controllerHandle)) //if the controller is loaded and its attached
        {
            if((currentTime - controllerStartStartTime ) > 300)
            {
                controllerStart = SDL_GameControllerGetButton(controllerHandle,SDL_CONTROLLER_BUTTON_START);
                if(controllerStart)
                {
                    controllerStartStartTime = SDL_GetTicks();
                }
            }


            leftStickX = SDL_GameControllerGetAxis(controllerHandle, SDL_CONTROLLER_AXIS_LEFTX); //get the x and y value for the thumsticks of the controller
            leftStickY = SDL_GameControllerGetAxis(controllerHandle, SDL_CONTROLLER_AXIS_LEFTY);

            rightStickX = SDL_GameControllerGetAxis(controllerHandle, SDL_CONTROLLER_AXIS_RIGHTX);
            rightStickY = SDL_GameControllerGetAxis(controllerHandle, SDL_CONTROLLER_AXIS_RIGHTY);

            //right stick for bullet direction
            if(rightStickX > cfg.JOYSTICK_DEAD_ZONE) //check whether the thumstick has been pushed past the dead zoe in each direction, set the controller flag to true for that direction if so
            {
                controllerShootRight = true;
            }
            if(rightStickX < -cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerShootLeft = true;
            }
            if(rightStickY > cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerShootDown = true;
            }
            if(rightStickY < -cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerShootUp = true;
            }


            //left stick for movement direction
            if(leftStickX > cfg.JOYSTICK_DEAD_ZONE) //check whether the thumstick has been pushed past the dead zoe in each direction, set the controller flag to true for that direction if so
            {
                controllerMoveRight = true;
            }
            if(leftStickX < -cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerMoveLeft = true;
            }
            if(leftStickY > cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerMoveDown = true;
            }
            if(leftStickY < -cfg.JOYSTICK_DEAD_ZONE)
            {
                controllerMoveUp = true;
            }

        }


        if(currentKeyStates[SDL_SCANCODE_RETURN])
        {
            keyboardEnter = true;
        }


        if((currentTime - escapeDelayStartTime) > 300)
        {
            if(currentKeyStates[SDL_SCANCODE_ESCAPE])
            {
                keyboardESC = true;
                escapeDelayStartTime = SDL_GetTicks();
            }


        }

        if((currentTime - deleteDelayStartTime) > deleteDelayInterval)
        {
            if(currentKeyStates[SDL_SCANCODE_DELETE])
            {
                keyboardDelete = true;
                deleteDelayStartTime = currentTime;
            }

        }




        for (int i = 0; i <= cfg.NUM_DIRECTIONS; i++) //reset all of the directions for the players movement to false, so the correct current directions can be detected below (keyboard)
		{
			playerDirArray[i] = false;
		}


		if(currentKeyStates[SDL_SCANCODE_W] || controllerMoveUp) //set the player movement flags according to the current state of those keyboard keys
		{
			playerDirArray[cfg.UP] = true;
			keyboardW = true;

		}
		if(currentKeyStates[SDL_SCANCODE_S] || controllerMoveDown)
		{
           playerDirArray[cfg.DOWN] = true;
           keyboardS = true;

		}
		if(currentKeyStates[SDL_SCANCODE_A] || controllerMoveLeft)
		{
			playerDirArray[cfg.LEFT] = true;

		}
		if(currentKeyStates[SDL_SCANCODE_D] || controllerMoveRight)
		{
           playerDirArray[cfg.RIGHT] = true;

		}


        for (int i = 0; i <= cfg.NUM_DIRECTIONS; i++) //reset all of the directions for the bullets movement to false, so the correct current directions can be detected below (keyboard)
		{
			bulletDirArray[i] = false;
		}

		if(currentKeyStates[SDL_SCANCODE_LEFT] || controllerShootLeft) //set the player movement flags according to the current state of those keyboard keys
		{
            bulletDirArray[cfg.LEFT] = true;
		}
		if(currentKeyStates[SDL_SCANCODE_RIGHT] || controllerShootRight)
		{
            bulletDirArray[cfg.RIGHT] = true;
		}
		if(currentKeyStates[SDL_SCANCODE_UP] || controllerShootUp)
		{
            bulletDirArray[cfg.UP] = true;
		}
		if(currentKeyStates[SDL_SCANCODE_DOWN] || controllerShootDown)
		{
            bulletDirArray[cfg.DOWN] = true;
		}
}

std::string InputHandler::getInputAsString()
{
    SDL_StartTextInput();

    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if(e.key.keysym.sym == SDLK_BACKSPACE)
        {
            if(builtString != "")
            {
                builtString = builtString.substr(0,builtString.size()-1);
            }
        }
        else if(e.type = SDL_TEXTINPUT)
        {
            builtString += e.text.text;
        }
    }
    return builtString;


}

bool InputHandler::checkIfDPadUpPressed()
{
    if(controllerHandle != 0 && SDL_GameControllerGetAttached(controllerHandle)) //if the controller is loaded and its attached
    {
        controllerDPadUp = SDL_GameControllerGetButton(controllerHandle,SDL_CONTROLLER_BUTTON_DPAD_UP);
    }

    return controllerDPadUp;



}
bool InputHandler::checkIfDPadDownPressed()
{
    if(controllerHandle != 0 && SDL_GameControllerGetAttached(controllerHandle)) //if the controller is loaded and its attached
    {
        controllerDPadDown = SDL_GameControllerGetButton(controllerHandle,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    }

    return controllerDPadDown;
}

bool InputHandler::checkIfControllerAPressed()
{
    if(controllerHandle != 0 && SDL_GameControllerGetAttached(controllerHandle)) //if the controller is loaded and its attached
    {
        controllerA = SDL_GameControllerGetButton(controllerHandle,SDL_CONTROLLER_BUTTON_A);
    }

    return controllerA;
}




std::string InputHandler::clearInputString()
{
    builtString = "";
    return builtString;
}

bool InputHandler::checkIfStartPressed()
{
    return controllerStart;
}

bool InputHandler::checkIfEnterPressed()
{
    if(currentKeyStates[SDL_SCANCODE_RETURN])
    {
        keyboardEnter = true;
    }
    else
    {
        keyboardEnter = false;
    }
    return keyboardEnter;
}

bool InputHandler::checkIfEscapePressed()
{
    return keyboardESC;
}
bool InputHandler::checkIfDeletePressed()
{
    return keyboardDelete;
}
bool InputHandler::checkIfWPressed()
{
    if(currentKeyStates[SDL_SCANCODE_W] || controllerMoveUp) //set the player movement flags according to the current state of those keyboard keys
    {
        keyboardW = true;

    }
    else
    {
        keyboardW = false;
    }

    return keyboardW;
}
bool InputHandler::checkIfSPressed()
{
    if(currentKeyStates[SDL_SCANCODE_S] || controllerMoveDown) //set the player movement flags according to the current state of those keyboard keys
    {
        keyboardS = true;

    }
    else
    {
        keyboardS = false;
    }

    return keyboardS;
}
