/*
 * display.h
 *
 *  Created on: 16 Dec 2017
 *      Author: callum
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>

#include "../Config.h"

class Display {
public:
	Display(int width, int height, const std::string &title, bool fullScreen);
	void swapBuffers();
	void clean();
	void clear(float r, float g, float b, float a);


	void loadPicture();
	bool isClosed();
	virtual ~Display();


	void getStartTime();
	void checkFPS();

	void setFullscreen();
	void setIsClosed(bool isClosed);

	Config cfg;
private:
	unsigned int startTime; //ticks at start of frame (ms)
	unsigned int endTime; //ticks at end of frame (ms)

	float FPSlimit;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

	int DEBUG_loops_run; //debug varaible for checking the number of loops run
};



#endif /* DISPLAY_H_ */
