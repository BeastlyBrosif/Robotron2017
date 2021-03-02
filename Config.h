/*
 * Config.h
 *
 *  Created on: 9 Feb 2018
 *      Author: callum
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Config {
public:
	Config()
	{
	};


	enum direction
	{
        NO_DIR,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_RIGHT,
		DOWN_RIGHT,
		UP_LEFT,
		DOWN_LEFT,
		NUM_DIRECTIONS

	};


	enum entityTypes
	{
		PLAYER,
		ELECTRODE,
		GRUNT,
		HULK,
		ENFORCER,
		ENFORCER_SPARK,
		SPHEROID,
		BRAIN,
		PROG,
		PROG_TRANSFORMER,
		TANK,
		TANK_SHELL,
		QUARK,
		CRUISE_MISSILE,
		FAMILY_1,
		FAMILY_2,
		FAMILY_3,
		FAMILY_4,
		FAMILY_5,
		SON,
		DAD,
		MUM

	};
	enum ParticleAmount
	{
		LOW,
		MEDIUM,
		HIGH,
	};

	const int PARTICLE_DENSITY = ParticleAmount::LOW;
	//controller / joystick stuff
	const int JOYSTICK_DEAD_ZONE = 8000; //set the joyStick deadzone for the controller

	enum TransitionShape
	{
		TRIANGLE,
		RECTANGLE,
		PENTAGON,
	};


    //score values
	int const GRUNT_SCORE = 100;
	int const BRAIN_SCORE = 500;
	int const PROG_SCORE = 100;
	int const SPHEROID_SCORE = 1000;
	int const ENFORCER_SCORE = 150;
	int const TANK_SCORE = 200;
	int const QUARK_SCORE = 1000;
	int const CRUISE_MISSILE_SCORE = 25;
	int const ENFORCER_SPARK_SCORE = 25;
	int const TANK_SHELL_SCORE = 50;
	int const FAMILY1_SCORE = 1000;
	int const FAMILY2_SCORE = 2000;
	int const FAMILY3_SCORE = 3000;
	int const FAMILY4_SCORE = 4000;
	int const FAMILY5_SCORE = 5000;

	int const SON_SCORE = 1000;
	int const DAD_SCORE = 1000;
    int const MUM_SCORE = 1000;

	//DEBUG booleans
	const bool B_DEBUG_ENEMYFACTORY = false;
	const bool B_DEBUG_DISPLAY = false;
	const bool B_DEBUG_MODELLOADER = false;
	const bool B_DEBUG_MAIN = false;
	const bool B_DEBUG_INPUT_HANDLER = false;


    const int PLAYER_LIVES = 6;

	//Display

    const bool FULLSCREEN = true;
    //4:3 aspect ratio resolutions: 640×480, 800×600, 960×720, 1024×768, 1280×960, 1400×1050, 1440×1080 , 1600×1200, 1856×1392, 1920×1440, and 2048×1536.
    //16:10 aspect ratio resolutions: - 1280×800, 1440×900, 1680×1050, 1920×1200 and 2560×1600. specifically for macbooks
    //16:9 aspect ratio resolutions: 1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080, 2560×1440 and 3840×2160.
    const int WIDTH = 1920; //set resolution, in the case of the fullscreen bool being true, the computers native resolution is fetched
    const int HEIGHT = 1080;
	const float FPS_LIMIT = 60.00f;

	const float positiveXedge = (float)(WIDTH/2) ; //calculate the openGL borders for the sprites and for the ortho perspective
	const float negativeXedge = (float)-(WIDTH/2);

	const float positiveYedge = (float)HEIGHT/2;
	const float negativeYedge = (float)-(HEIGHT/2);
    //border
    const float BORDER_WIDTH = 5; //border width
    const float GAP_FOR_TEXT = 25; //the gap to leave so the text appears above the border for the game

	const float positiveXBorder = positiveXedge - BORDER_WIDTH; //borders used for collisions, edit the openGL ones to remove the size of the border, so the entittes react to the border, not the edge of the screen
	const float negativeXBorder = negativeXedge + BORDER_WIDTH;
	const float positiveYBorder = positiveYedge - BORDER_WIDTH - GAP_FOR_TEXT;
	const float negativeYBorder = negativeYedge + BORDER_WIDTH;



    //speed values
	unsigned int PLAYER_SPEED = 4;
	unsigned int GRUNT_SPEED = 4;
    float HULK_SPEED = 2.5f;
	unsigned int BULLET_SPEED = 20;
	unsigned int SPARK_SPEED = 20;
	unsigned int TANK_SPEED = 3;
	unsigned int SON_SPEED = 2;
	unsigned int DAD_SPEED = 2;
	unsigned int MUM_SPEED = 2;
	unsigned int SPHEROID_SPEED = 2;

	float BRAIN_SPEED = 1;
	unsigned int PROG_SPEED = 4;
	unsigned int PROG_TRANSFORMER_SPEED = 1;

    float START_SCREEN_W_SPEED = 3;


	//when a hulk is shot and gets "shifted" in a direction, this determines how far it gets shifted
	unsigned int HULK_PUSH_VAL = 2;

    //movement intervals
	unsigned int GRUNT_UPDATE = 100;
	unsigned int ENFORCER_UPDATE = 100000;
	unsigned int HULK_UPDATE = 20;
	unsigned int BRAIN_UPDATE = 20;
	unsigned int PROG_UPDATE = 5;
	unsigned int TANK_UPDATE = 20;
	unsigned int SON_UPDATE = 20;
	unsigned int DAD_UPDATE = 20;
	unsigned int MUM_UPDATE = 20;
	unsigned int PROG_TRANSFORMER_UPDATE = 5;
	unsigned int MISSILE_UPDATE = 20;
	unsigned int SHELL_UPDATE = 10;
	unsigned int SPARK_UPDATE = 10;
	unsigned int START_SCREEN_W_UPDATE = 10;
    unsigned int SPHEROID_UPDATE = 10;

	unsigned int BRAIN_MISSILE_PART_DELAY = 50;


    //direction changer intervals

	unsigned int HULK_DIR_UPDATE = 1000;
	unsigned int TANK_DIR_UPDATE = 2000;
	unsigned int SON_DIR_UPDATE = 2000;
	unsigned int DAD_DIR_UPDATE = 2000;
	unsigned int MUM_DIR_UPDATE = 2000;
    unsigned int BRAIN_DIR_UPDATE = 2000;
    unsigned int PROG_TRANSFORMER_DIR_UPDATE = 50;
    unsigned int PROG_DIR_UPDATE = 100;
    unsigned int SPHEROID_DIR_UPDATE = 1000;




    float HULK_SLOWDOWN = 0.1f;

    unsigned int BULLET_INTERVAL = 100;
	unsigned int SPARK_INTERVAL = 3000; //spark and shells also have a random interval based on these values
    unsigned int SHELL_INTERVAL = 4000;
    unsigned int MISSILE_INTERVAL = 3000;
    unsigned int SPHEROID_SHOT_INTERVAL = 5000;


    unsigned int MISSILE_TAIL_DELAY = 30;

    unsigned int MISSILE_ZIG_ZAG_INTERVAL = 300;
    unsigned int MISSILE_ZIG_ZIG_CHANCE = 30; //% chance of zig zagging in the interval


	//ANIMATION DELAY

    unsigned int PLAYER_ANIMATION_INTERVAL = 100;
	unsigned int HULK_ANIMATION_INTERVAL = 100;
	unsigned int GRUNT_ANIMATION_INTERVAL = 100;
	unsigned int TANK_ANIMATION_INTERVAL = 100;
	unsigned int ELECTRODE_ANIMATION_INTERVAL = 100;
	unsigned int SON_ANIMATION_INTERVAL = 100;
	unsigned int DAD_ANIMATION_INTERVAL = 100;
	unsigned int MUM_ANIMATION_INTERVAL = 100;
	unsigned int ENFORCER_ANIMATION_INTERVAL = 100;
	unsigned int PROG_ANIMATION_INTERVAL = 100;
	unsigned int BRAIN_ANIMATION_INTERVAL = 100;
	unsigned int SPARK_ANIMATION_INTERVAL = 50;
	unsigned int SHELL_ANIMATION_INTERVAL = 200;
	unsigned int SPHEROID_ANIMATION_INTERVAL = 100;


	unsigned int SCORE_ON_SCREEN_INTERVAL = 200;
	unsigned int BRAIN_SEEK_INTERVAL = 3000;


    //make a rouge value for when you want a random spawn of an entity from a factory
	const int FACTORY_ROUGE_VALUE = (int)(positiveXBorder + positiveXBorder);


	const float PLAYER_SCALE = 2.0f;
	const float ENEMY_SCORE_WORD_SCALE = 3.5;
	const float GRUNT_SCALE = 4.0f;
	const float BULLET_SCALE = 2.0f;
	const float ELECTRODE_SCALE = 3.0f;
	const float HULK_SCALE = 5.0f;
    const float SON_SCALE = 1.8;
    const float DAD_SCALE = 3;
    const float MUM_SCALE = 2;
    const float ENFORCER_SCALE = 4.0f;
	const float TANK_SCALE = 2;
	const float BRAIN_SCALE = 5;
	const float SPARK_SCALE = 2;
	const float PROG_TRANSFORMER_SCALE = 8.0f;
	const float MISSILE_SCALE = 4;
    const float SPHEROID_SCALE = 4;

	const float DEFAULT_ROT = 1.5708f;

	//HITBOX
	const float PLAYER_WIDTH = 30;
	const float PLAYER_HEIGHT = 40;
	const float BULLET_WIDTH = 5;
	const float BULLET_HEIGHT = 5;
	const float GRUNT_WIDTH = 30;
	const float GRUNT_HEIGHT = 40;
	const float HULK_WIDTH = 40;
	const float HULK_HEIGHT = 40;
	const float ELECTRODE_WIDTH = 15;
	const float ELECTRODE_HEIGHT = 15;
	const float ENFORCER_WIDTH = 40;
	const float ENFORCER_HEIGHT = 40;
	const float TANK_WIDTH = 30;
	const float TANK_HEIGHT = 30;
    const float TANK_SHELL_HEIGHT = 30;
    const float TANK_SHELL_WIDTH = 30;
	const float SPARK_WIDTH = 30;
	const float SPARK_HEIGHT = 30;
	const float SON_WIDTH = 20;
	const float SON_HEIGHT = 20;
	const float DAD_WIDTH = 20;
	const float DAD_HEIGHT = 20;
	const float MUM_WIDTH = 20;
	const float MUM_HEIGHT = 20;
	const float BRAIN_WIDTH = 40;
	const float BRAIN_HEIGHT = 60;
	const float PROG_WIDTH = 20;
	const float PROG_HEIGHT = 30;
	const float MISSILE_WIDTH = 10;
	const float MISSILE_HEIGHT = 10;
	const float PROG_TRANSFORMER_WIDTH = 0;
	const float PROG_TRANSFORMER_HEIGHT = 0;
	const float SPHEROID_WIDTH = 25;
	const float SPHEROID_HEIGHT = 25;

	const float START_SCREEN_W_WIDTH = 140;
	const float START_SCREEN_W_HEIGHT = 140;




    unsigned int ENFORCER_OFFSET_INTERVAL = 1000;
    int ENFORCER_OFFSET = 300;
    unsigned int ENFORCER_FLYOFF_INTERVAL = 2000;
    unsigned int ENFORCER_FLYOFF_DURATION = 7000;
    unsigned int ENFORCER_FLYOFF_CHANCE = 10; //chance of actaully flying off in that interval is 10%

	const unsigned int SHELL_LIFETIME = 3000;
	const unsigned int SPARK_LIFETIME = 2000;
	const unsigned int MISSILE_LIFETIME = 3000;

    unsigned int TIME_TO_MAKE_PROG = 2000;

    unsigned int PROG_PLAYER_SEEK_INTERVAL = 500;

    unsigned int SPHEROID_ENFORCER_SPAWN_DELAY = 500;

	//virtual ~Config();
};

#endif /* CONFIG_H_ */
