/*
 * display.cpp
 *
 *  Created on: 16 Dec 2017
 *      Author: Callum and Nimrod
 */


#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>




Display::Display(int width, int height, const std::string &title, bool fullScreen)
{
	FPSlimit = cfg.FPS_LIMIT;

	DEBUG_loops_run = 0; //DEBUG

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if(fullScreen)
	{
		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);

		width = dm.w;
		height = dm.h;

		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL |SDL_WINDOW_FULLSCREEN);

	}
	else
	{
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL);

	}

	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if(status != GLEW_OK)
	{
		std::cerr << "GLew failed to initialise!" <<std::endl;

	}
	m_isClosed = false;
	glewExperimental = true; //not sure if this works
}


void Display::setIsClosed(bool isClosed)
{
	m_isClosed = isClosed;
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_window);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::setFullscreen()
{
	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_DestroyWindow(m_window);


	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);

	int w, h;
	w = dm.w;
	h = dm.h;
	//m_window = SDL_CreateWindow("HEY", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1920, 1080,SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	//SDL_GL_MakeCurrent(m_window, m_glContext);
	//SDL_SetWindowDisplayMode(m_window,&dm );
	//SDL_MaximizeWindow(m_window);
	//SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);


}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

bool Display::isClosed()
{
	return m_isClosed;
}


void Display::swapBuffers()
{
	
	SDL_GL_SwapWindow(m_window);
	DEBUG_loops_run++;
	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}
void Display::getStartTime()
{
	startTime = SDL_GetTicks();
}
void Display::checkFPS()
{
	endTime = SDL_GetTicks();
	double framePeriod = 1000.00f / FPSlimit;
	double timeSpan = endTime - startTime; //duration of the frame in ms;
	if (timeSpan < framePeriod)
	{
		double timeToWait = framePeriod - timeSpan;
	//	if (cfg.B_DEBUG_DISPLAY) {std::cout << "framePeriod + time to wait is: " << timeToWait + }
		SDL_Delay((Uint32)timeToWait);
	}
}
void Display:: clean() //function empty
{
}
void Display:: loadPicture() //function empty
{
}




