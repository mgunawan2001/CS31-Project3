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
    m_player = new Socrates(this);
   /* Add max(180 – 20 * L, 20) dirt objects to the Petri dish at random locations, 
      in a manner such that no dirt objects overlap with previously - placed food
      objects or pits(their centers are at least 2 * SPRITE_RADIUS pixels apart from
      each other).It is OK for dirt objects to overlap with each other, however.Each
      dirt object must be no more 120 pixels from the center of the Petri dish which
      is at(VIEW_WIDTH / 2, VIEW_HEIGHT / 2).*/
    int numDirt = max((180-2*getLevel()), 20);
    for (int i = 0; i < numDirt; i++)
    {
        int startX = rand() % 256;
        int startY = rand() % 256;
        int r = sqrt((startX - VIEW_WIDTH / 2) * (startX - VIEW_WIDTH / 2) + (startY - VIEW_HEIGHT / 2) * (startY - VIEW_HEIGHT / 2));
        if (r<=120)
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
    return 1;
}

void StudentWorld::cleanUp()
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}