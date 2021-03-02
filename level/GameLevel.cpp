#include "../level/GameLevel.h"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>

GameLevel::GameLevel(std::string levelfile)
{
	m_filename = levelfile; //the level file to be loaded (e.g. level0.txt)
	m_active = false; //is the level currently being played?
	m_completed = false; //has the level been completed?
	playerX = 0; //the position the player will spawn in (x axis)
	playerY = 0; //the position the player will spawn in (y axis)
	m_levelScore = 0; //the score achieved by the player in this level
}
GameLevel::~GameLevel()
{
	freeList(); //call the clear to the vector list
}
void GameLevel::freeList() //this function releases the memory that is used for the struct EnemyList
{
	int numberofenemies = m_enemyList.size();
	for (int i = 0; i < numberofenemies; i++)
	{
		delete m_enemyList.at(i);
	}
	m_enemyList.clear();
}
int GameLevel::getEnemyType(std::string stringType)
{
	if (stringType.compare("grunt"))
	{
		// TODO: return correct type
		return 1;
	}
	else if (stringType.compare("brain"))
	{
		return 2;
	}
	else if (stringType.compare("tank")) 
	{
		return 3;
	}
	return -1;
}
void GameLevel::addEnemyToList(int _type, int _xPos, int _yPos)
{
	struct enemyList *newEnemy = new enemyList;
	newEnemy->type = _type;
	newEnemy->x = _xPos;
	newEnemy->y = _yPos;
	m_enemyList.push_back(newEnemy);
}

void GameLevel::readFile() //this function should open the file specified in the constructor and read each line into the data structures of this class
{
	srand(time(0));
	std::ifstream infile(m_filename);
	if (!infile) 
	{
		cout << "could not find file '" << m_filename << "'" << endl;
		return;
	}

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		string buffer;
		if (!(iss >> buffer)) 
		{
			break;
		}

		if (buffer.empty() || buffer[0] == '#')
		{
			continue;
		}

		if (buffer.compare("l") == 0)
		{
			m_levelName = line.substr(2);
			cout << "level name: " << m_levelName << endl;
		}
		else if (buffer.compare("h") == 0)
		{
			size_t open = line.find('[');
			if (open == string::npos)
			{
				// error handle
				return;
			}
			size_t comma = line.find(',');
			if (comma == string::npos)
			{
				// error handle
				return;
			}
			size_t close = line.find(']');
			if (comma == string::npos)
			{
				// error handle
				return;
			}
			string heroType = line.substr(2, open - 2);
			string xpos = line.substr(open + 1, comma - open - 1);
			string ypos = line.substr(comma + 1, close - comma - 1);
			playerX = stoi(xpos);
			playerY = stoi(ypos);
 			cout << "hero: " << heroType << "[" << playerX << "," << playerY << "]" << endl;
		}
		else if (buffer.compare("e") == 0)
		{
			size_t open = line.find('[');
			if (open != string::npos)
			{
				size_t comma = line.find(',');
				if (comma == string::npos)
				{
					// error handle
					return;
				}
				size_t close = line.find(']');
				if (comma == string::npos)
				{
					// error handle
					return;
				}
				string enemyType = line.substr(2, open - 2);
				string xpos = line.substr(open + 1, comma - open - 1);
				string ypos = line.substr(comma + 1, close - comma - 1);
				int type = getEnemyType(enemyType);
				int x = stoi(xpos);
				int y = stoi(ypos);
				cout << "enemy: " << enemyType << "[" << x << "," << y << "]" << endl;
				addEnemyToList(type, x, y);
			}
			else if ((open = line.find("(")) != string::npos)
			{
				size_t close = line.find(')');
				if (close == string::npos)
				{
					// error handle
					return;
				}
				string enemyType = line.substr(2, open - 2);
				string enemyCount = line.substr(open + 1, close - open - 1);
				int type = getEnemyType(enemyType);
				int count = stoi(enemyCount);
				cout << "enemies: " << enemyType << "(" << enemyCount << ")" << endl;
				for (int i = 0; i < count; i++)
				{
					// TODO: screen dimensions
					addEnemyToList(type, rand() % 300, rand() % 300);
				}
			}
			else
			{
				// 
			}
		}

	}
}