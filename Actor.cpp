#include "Actor.h"
#include "StudentWorld.h"
#include<math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////Actor///////////////////////////////////////
Actor::Actor(int imID, double startX, double startY, StudentWorld* studentWorldptr) :GraphObject(imID, startX, startY)
{
    sw = studentWorldptr;
}

StudentWorld* Actor::getWorld() const
{
    return sw;
}

void Actor::findRadius(int x, int y, int& r, int& angle)
{
    angle = tan(y / x);
    r = sqrt((y * y) + (x * x));
}


/////////////////////////////////////Socrates///////////////////////////////////////////
Socrates::Socrates(StudentWorld* swptr) : Actor(IID_PLAYER, 0, 128, swptr)
{
    int m_hitPoints = 100;
    //bool m_alive = true;
    //int m_direction = 0;
    //int m_startAngle = 180;
    //int m_depth = 0;
    //int m_sprayCharges = 20;
    //int m_flameThrowerCharges = 5;
    
}



void Socrates::doSomething() 
{
    //if (m_hitPoints>0)
    //{
    //    int ch;
    //    if (getWorld()->getKey(ch)) {
    //        // user hit a key during this tick!
    //     switch (ch)
    //     {
    //        case KEY_PRESS_LEFT:
    //        ... move Socrates counterclockwise ...;
    //        break;
    //        case KEY_PRESS_RIGHT:
    //        ... move Socrates clockwise...;             
    //        break;
    //        case KEY_PRESS_SPACE:
    //            if (m_sprayCharges > 0)
    //            {
    //                m_sprayCharges--;
    //            }
    //            ... add spray in front of Socrates...;    
    //            break; 
    //        case KEY_PRESS_ENTER:
    //            if (m_flameThrowerCharges > 0)
    //            {
    //                m_flameThrowerCharges--;
    //            }
    //     }
    //    }
    //}
    //else
    //{
    //    return;
    //}
} 

////////////////////////////////////Dirt////////////////////////////////
Dirt::Dirt(int startX, int startY, StudentWorld* swptr) :Actor(IID_DIRT, startX, startY, swptr)
{
}