#include "Actor.h"
#include "StudentWorld.h"
#include<math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////Actor///////////////////////////////////////
Actor::Actor(int imID, double startX, double startY, StudentWorld* studentWorldptr) :GraphObject(imID, startX, startY), sw(studentWorldptr)
{
}

StudentWorld* Actor::getWorld() const
{
    return sw;
}

void Actor::doSomething() {}

void Actor::findRadius(int x, int y, int& r, int& angle)
{
    angle = tan(y / x);
    r = sqrt((y * y) + (x * x));
}

//bool Actor::harmSocrates()
//{
//    return false;
//}
////////////////////////////////Living////////////////////////////////
Living::Living(int hp, const int id, double startX, double startY, StudentWorld* swptr) : Actor(id, startX, startY, swptr)
{
    m_hitPoints = hp;
}
///////////////////////////////////Bacteria///////////////////////////
Bacteria::Bacteria(int hp, const int id, double startX, double startY, StudentWorld* swptr) : Living(hp,id,startX,startY,swptr)
{
}

/////////////////////////////////////Socrates///////////////////////////////////////////
Socrates::Socrates(double startX, double startY, StudentWorld* swptr) : Actor(IID_PLAYER, startX, startY, swptr)
{
    m_hitPoints = 100;
    m_sprayCharges = 20;
    m_flameThrowerCharges = 5;
    alive = true;
    //bool m_alive = true;
    //int m_direction = 0;
    //m_angle = 180;
    //int m_depth = 0;
    tickNotPressed = 0;
    setDirection(0);
}

int Socrates::getHitPoints() const { return m_hitPoints; }
int Socrates::getSprays() const { return m_sprayCharges; }
int Socrates::getFlames() const { return m_flameThrowerCharges; }
void Socrates::hit() { m_hitPoints--; }


void Socrates::moveSocrates(double d)
{
    double x, y;
    Direction a = getDirection() + d;
    getPositionInThisDirection(a, VIEW_RADIUS, x, y);
    moveTo(VIEW_WIDTH / 2 - x + getX(), VIEW_HEIGHT / 2 - y + getY());
    setDirection(a);
}

void Socrates::doSomething() 
{
    if (m_hitPoints>0)
    {
        int ch;
        if (Actor::getWorld()->getKey(ch)) {
            tickNotPressed = 0;
            // user hit a key during this tick!
            switch (ch)
            {
                case KEY_PRESS_LEFT:
                    //move Socrates counterclockwise
                {
                    moveSocrates(-5.0);
                    break;
                }
                case KEY_PRESS_RIGHT:
                    //... move Socrates clockwise...;  
                {
                    moveSocrates(+5.0);
                    break;

                }
                case KEY_PRESS_SPACE:
                    //... add spray in front of Socrates...; 
                {
                    if (m_sprayCharges >= 1)
                    {
                        double sprayX, sprayY;
                        getPositionInThisDirection(getDirection(), 2 * SPRITE_RADIUS, sprayX, sprayY);
                        getWorld()->getActors().push_back(new Spray(sprayX, sprayY, getWorld(), getDirection()));
                        m_sprayCharges--;
                        getWorld()->playSound(SOUND_PLAYER_SPRAY);
                    }
                    break;
                }
                case KEY_PRESS_ENTER:
                {
                    if (m_flameThrowerCharges > 0)
                    {
                        Direction right = getDirection()-22;
                        Direction left = getDirection();
                        for (int i = 0; i < 8; i++)
                        {
                            double flameX, flameY;
                            getPositionInThisDirection(right, 2 * SPRITE_RADIUS, flameX, flameY);
                            getWorld()->getActors().push_back(new Flame(flameX, flameY, getWorld(), getDirection()));
                            getPositionInThisDirection(left, 2 * SPRITE_RADIUS, flameX, flameY);
                            getWorld()->getActors().push_back(new Flame(flameX, flameY, getWorld(), getDirection()));
                            right -= 22;
                            left += 22;
                        }
                             m_flameThrowerCharges--;
                    }
                    break;
                }
            }
        }
        else 
        {
            if (tickNotPressed > 1)
            {
                m_sprayCharges = 20;
            }
            else if (m_sprayCharges < 20)
            {
                m_sprayCharges++;
            }
            tickNotPressed++;
        }
    }
    else
    {
    //    return;
    }
} 

////////////////////////////////////Dirt////////////////////////////////
Dirt::Dirt(double startX, double startY, StudentWorld* swptr) :Actor(IID_DIRT, startX, startY, swptr)
{}
///////////////////////////////////////Pit/////////////////////////////////////////
Pit::Pit(double startX, double startY, StudentWorld* swptr) : Actor(IID_PIT, startX, startY, swptr)
{}
//////////////////////////////////////Food//////////////////////////////////////////
Food::Food(double startX, double startY, StudentWorld* swptr) : Actor(IID_FOOD, startX, startY, swptr)
{}
/////////////////////////////////////Spray///////////////////////////////
Spray::Spray(double startX, double startY, StudentWorld* swptr, Direction d) : Actor(IID_SPRAY, startX, startY, swptr)
{
    setDirection(d);
}
///////////////////////////////////////Flame//////////////////////////////
Flame::Flame(double startX, double startY, StudentWorld* swptr, Direction d) : Actor(IID_FLAME, startX, startY, swptr)
{
    setDirection(d);
}
