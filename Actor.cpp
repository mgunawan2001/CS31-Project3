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
Socrates::Socrates(StudentWorld* swptr) : Actor(IID_PLAYER, 0, (VIEW_HEIGHT / 2), swptr)
{
    m_hitPoints = 100;
    m_sprayCharges = 20;
    m_flameThrowerCharges = 5;
    //bool m_alive = true;
    //int m_direction = 0;
    m_angle = 180;
    //int m_depth = 0;
    
    
}
int Socrates::getHitPoints() { return m_hitPoints; }
int Socrates::getSprays() { return m_sprayCharges; }
int Socrates::getFlames() { return m_flameThrowerCharges; }



void Socrates::doSomething() 
{
    if (m_hitPoints>0)
    {
        int ch;
        if (getWorld()->getKey(ch)) {
            // user hit a key during this tick!
            switch (ch)
            {
            case KEY_PRESS_LEFT:
               //move Socrates counterclockwise
            {
                double x, y;
                Direction a = getDirection() + 5;
                getPositionInThisDirection(a, VIEW_RADIUS, x, y);
                moveTo(x, y);
                break;
            }
    //        case KEY_PRESS_RIGHT:
    //        ... move Socrates clockwise...;             
    //        break;
    //       case KEY_PRESS_SPACE:
    //           if (m_sprayCharges > 0)
    //           {
    //               m_sprayCharges--;
    //           }
    //           //(*getWorld().getActors().push_back(Spray()));
    ////            ... add spray in front of Socrates...;    
    //           break; 
    //        case KEY_PRESS_ENTER:
    //            if (m_flameThrowerCharges > 0)
    //            {
    //                m_flameThrowerCharges--;
    //            }
    //            break;
            }
        }
    }
    else
    {
    //    return;
    }
} 

////////////////////////////////////Dirt////////////////////////////////
Dirt::Dirt(int startX, int startY, StudentWorld* swptr) :Actor(IID_DIRT, startX, startY, swptr)
{
}
///////////////////////////////////////Pit/////////////////////////////////////////
Pit::Pit(int startX, int startY, StudentWorld* swptr) : Actor(IID_PIT, startX, startY, swptr)
{}
//////////////////////////////////////Food//////////////////////////////////////////
Food::Food(int startX, int startY, StudentWorld* swptr) : Actor(IID_FOOD, startX, startY, swptr)
{}