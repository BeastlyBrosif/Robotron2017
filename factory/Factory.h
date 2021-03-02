/*
 * Factory.h
 *
 *  Created on: 9 Feb 2018
 *      Author: callum
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "../Config.h"



class Factory {
public:
	Factory(){};
	void update();
	void createEntity();
	virtual void addOffsetToObjects(){};
	void toggleIsPaused(){
        if(m_isPaused)
        {
            m_isPaused = false;
        }
        else
        {
            m_isPaused = true;
        }
	}

    ~Factory(){};
	Config cfg;
    protected:

    bool m_isPaused;

};



#endif /* FACTORY_H_ */
