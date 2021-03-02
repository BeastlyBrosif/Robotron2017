#include "../level/LevelFactory.h"

LevelFactory::~LevelFactory()
{

}
//Load levels should read a directory (e.g. "./res/levels/...") and load m_numberoflevels from that directory
void LevelFactory::loadLevels()
{

}
//this function is run every loop, it should check if the current level has been completed and if it has, it should move to the next one
//examine GameLevel.h and GameLevel.cpp to see how to do this
void LevelFactory::update() 
{

}
void LevelFactory::addLevel(std::string _levelfile)
{
	m_levelList.push_back(new GameLevel(_levelfile));
}
void LevelFactory::clearLevels() //this function is to be called after the game is over to free all the levels remaining in the vector list
{
	int numberoflevels = m_levelList.size();
	for (int i = 0; i < numberoflevels; i++)
	{
		delete m_levelList.at(i);
	}
	m_levelList.clear();
}