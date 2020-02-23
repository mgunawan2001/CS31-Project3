#include "Actor.h"
#include "StudentWorld.h"
#include<math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////Actor///////////////////////////////////////
Actor::Actor(int imID, double startX, double startY, StudentWorld* studentWorldptr) :GraphObject(imID, startX, startY), sw(studentWorldptr)
{
    m_alive = true;
}

StudentWorld* Actor::getWorld() const
{
    return sw;
}

bool Actor::isAlive() { return m_alive; }
void Actor::setDead() { m_alive = false; }

void Actor::doSomething() {}

/////////////////////////////////////Damagable/////////////////////////
Damagable::Damagable(int hp, const int id, double startX, double startY, StudentWorld* swptr) : Actor(id, startX, startY, swptr)
{
    m_hitPoints = hp;
}

////////////////////////////////Living////////////////////////////////
//Living::Living(int hp, const int id, double startX, double startY, StudentWorld* swptr) : Actor(id, startX, startY, swptr)
//{
//    m_hitPoints = hp;
//}

///////////////////////////////////Bacteria///////////////////////////
Bacteria::Bacteria(int hp, const int id, double startX, double startY, StudentWorld* swptr) : Damagable(hp,id,startX,startY,swptr)
{
}

/////////////////////////////////////Socrates///////////////////////////////////////////
Socrates::Socrates(double startX, double startY, StudentWorld* swptr) : Damagable(100, IID_PLAYER, startX, startY, swptr)
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
void Socrates::decHitPoints(int m)
{
    m_hitPoints -= m;
    if (m_hitPoints <= 0)
    {
        setDead();
    }
}


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
    if (isAlive())
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
                        getWorld()->insert(new Spray(sprayX, sprayY, getWorld(), getDirection()));
                        m_sprayCharges--;
                        getWorld()->playSound(SOUND_PLAYER_SPRAY);
                    };
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
                            getWorld()->insert(new Flame(flameX, flameY, getWorld(), right));
                            //->getActors().push_back(new Flame(flameX, flameY, getWorld(), getDirection()));
                            getPositionInThisDirection(left, 2 * SPRITE_RADIUS, flameX, flameY);
                            getWorld()->insert(new Flame(flameX, flameY, getWorld(), left));
                            //getWorld()->getActors().push_back(new Flame(flameX, flameY, getWorld(), getDirection()));
                            right -= 22;
                            left += 22;
                        }
                            
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
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

void Socrates::overlap(Actor* a)
{
    a->harmSocrates();
}

////////////////////////////////////Dirt////////////////////////////////
Dirt::Dirt(double startX, double startY, StudentWorld* swptr) :Damagable(1, IID_DIRT, startX, startY, swptr)
{
    //setDirection(90);
}
//////////////////////////////////////Food//////////////////////////////////////////
Food::Food(double startX, double startY, StudentWorld* swptr) : Actor(IID_FOOD, startX, startY, swptr)
{
    //setDirection(90);
}
///////////////////////////////////////Pit/////////////////////////////////////////
Pit::Pit(double startX, double startY, StudentWorld* swptr) : Actor(IID_PIT, startX, startY, swptr)
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
void Flame::doSomething()
{
    if(isAlive())
    {
        for (int i = 0; i < (getWorld()->getActors()).size(); i++)
        {
            Actor* a = getWorld()->inPos(i);
            double x, y;
            a->getPos(x, y);
            if (getWorld()->findEuclidean(getX(), getY(), x,y) <= SPRITE_RADIUS * 2)
            {
                (getWorld()->inPos(i))->damagedByFlame();
                setDead();
                return;
            }
        }
        moveAngle(getDirection(), SPRITE_RADIUS * 2);
        //moveForward(SPRITE_RADIUS * 2);
    }
}
