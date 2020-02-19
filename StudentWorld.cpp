#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <algorithm>
#include<math.h>
using namespace std;

#include "Actor.h"

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{

} 

int StudentWorld::init()
{
    m_player = new Socrates(0, VIEW_HEIGHT/2,this);

///////Pit////////
    for (int p = 0; p < getLevel(); p++)
    {
        bool allowed = true;
        int startX = randInt(0, 256);
        int startY = randInt(0, 256);
        for (int k = 0; k < coords.size(); k++)
        {
            if (coords[k].x == startX && coords[k].y == startY)
            {
                allowed = false;
            }
            else
            {
                int d = sqrt((startX - coords[k].x) * (startX - coords[k].x) + (startY - coords[k].y) * (startY - coords[k].y));
                if (d < (2 * SPRITE_RADIUS))
                {
                    allowed = false;
                }
            }
        }

        int r = sqrt((startX - VIEW_WIDTH / 2) * (startX - VIEW_WIDTH / 2) + (startY - VIEW_HEIGHT / 2) * (startY - VIEW_HEIGHT / 2));
        if (r <= 120 && allowed)
        {
            actors.push_back(new Pit(startX, startY, this));
            coords.push_back(Coordinate(startX, startY));
        }
        else
        {
            p--;
        }

    }
  
/////Food/////
    for (int f = 0; f < max(5 * getLevel(), 25); f++)
    {
        bool allowed = true;
        int startX = randInt(0, 256);
        int startY = randInt(0, 256);
        for (int k = 0; k < coords.size(); k++)
        {
            if (coords[k].x == startX && coords[k].y == startY)
            {
                allowed = false;
            }
            else
            {
                int d = sqrt((startX - coords[k].x) * (startX - coords[k].x) + (startY - coords[k].y) * (startY - coords[k].y));
                if (d < (2 * SPRITE_RADIUS))
                {
                    allowed = false;
                }
            }
        }

        int r = sqrt((startX - VIEW_WIDTH / 2) * (startX - VIEW_WIDTH / 2) + (startY - VIEW_HEIGHT / 2) * (startY - VIEW_HEIGHT / 2));
        if (r <= 120 && allowed)
        {
            actors.push_back(new Food(startX, startY, this));
            coords.push_back(Coordinate(startX, startY));

        }
        else
        {
            f--;
        }

    }

/////Dirt////////
    int numDirt = max((180-2*getLevel()), 20);
    for (int i = 0; i < numDirt; i++)
    {
        bool allowed = true;
        int startX = randInt(0, 256);
        int startY = randInt(0, 256);
        for (int k = 0; k < coords.size(); k++)
        {
            if (coords[k].x == startX && coords[k].y == startY)
            {
                allowed = false;
            }
            else
            {
                int d = sqrt((startX - coords[k].x) * (startX - coords[k].x) + (startY - coords[k].y) * (startY - coords[k].y));
                if (d < (2 * SPRITE_RADIUS))
                {
                    allowed = false;
                }
            }
        }

        int r = sqrt((startX - VIEW_WIDTH / 2) * (startX - VIEW_WIDTH / 2) + (startY - VIEW_HEIGHT / 2) * (startY - VIEW_HEIGHT / 2));
        if (r <= 120 && allowed)
        {
            actors.push_back(new Dirt(startX, startY, this));
        }
        else 
        {
            i--;
        }
    }

    

    return GWSTATUS_CONTINUE_GAME;
}     

int StudentWorld::move()
{
   // // This code is here merely to allow the game to build, run, and terminate after you hit enter.
   // // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
   //// The term "actors" refers to all bacteria, Socrates, goodies,   
   //// pits, flames, spray, foods, etc.       
   //// Give each actor a chance to do something, incl. Socrates 
   // for each of the actors in the game world  {      
   //     if (actor[i] is still active/alive)
   //     {
   //         // tell each actor to do something (e.g. move)
   //         actor[i]->doSomething();  
   //     if (SocratesDiedDuringThisTick())  return GWSTATUS_PLAYER_DIED;
   //     if (SocratesCompletedTheCurrentLevel()) 
   //     { return GWSTATUS_FINISHED_LEVEL; }
   //     } 
   // }
   // // Remove newly-dead actors after each tick  
   // removeDeadGameObjects(); // delete dead game objects 
   // // Potentially add new actors to the game (e.g., goodies or fungi)    
   // addNewActors();  
   // // Update the Game Status Line 
   // updateDisplayText();   // update the score/lives/level text at screen top 
   // // the player hasn’t completed the current level and hasn’t died, so  
   // // continue playing the current level  
   // return GWSTATUS_CONTINUE_GAME;    } 
    m_player->doSomething();
    string stats = "Score: " + to_string(getScore()) + " Level: " + to_string(getLevel()) + " Lives: " + to_string(getLives()) + " health: " + to_string((*m_player).getHitPoints()) + " Sprays: " + to_string(m_player->getSprays()) + " Flames: " + to_string(m_player->getFlames());
    setGameStatText(stats);
    return 1;
}

void StudentWorld::cleanUp()
{
    delete m_player;
    for (int i = 0; i < actors.size(); i++)
    {
        delete actors[i];
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}