#include "Actor.h"
#include "StudentWorld.h"
#include<math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////Actor///////////////////////////////////////
Actor::Actor(int imID, double startX, double startY, StudentWorld* studentWorldptr, Direction dir, int depth, double size) :GraphObject(imID, startX, startY, dir, depth, size), sw(studentWorldptr)
{
    m_alive = true;
}

StudentWorld* Actor::getWorld() const
{
    return sw;
}
int Actor::getLevel() { return sw->getLevel(); }

bool Actor::isAlive() { return m_alive; }
void Actor::setDead() { m_alive = false; }

void Actor::doSomething() {}

/////////////////////////////////////Damagable/////////////////////////
Damagable::Damagable(int hp, const int id, double startX, double startY, StudentWorld* swptr, Direction dir, int depth, double size) : Actor(id, startX, startY, swptr, dir, depth, size)
{
    m_hitPoints = hp;
}

////////////////////////////////Living////////////////////////////////
Goodie::Goodie(const int id, double startX, double startY, StudentWorld* swptr):Actor(id, startX, startY, swptr, 0, 1)
{
}

///////////////////////////////////Bacteria///////////////////////////
Bacteria::Bacteria(const int id, double startX, double startY, StudentWorld* swptr, int hp) : Damagable(hp,id,startX,startY,swptr,90)
{
}
/////////////////////////////////////Projectile/////////////////////////////
Projectile::Projectile(const int id, double startX, double startY, StudentWorld* swptr, Direction d, int maxTravel) : Actor(id, startX, startY, swptr, d, 1), m_maxTravel(maxTravel)
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
                            getPositionInThisDirection(left, 2 * SPRITE_RADIUS, flameX, flameY);
                            getWorld()->insert(new Flame(flameX, flameY, getWorld(), left));
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
} 

void Socrates::overlap(Actor* a)
{
    a->harmSocrates();
}

////////////////////////////////////Dirt////////////////////////////////
Dirt::Dirt(double startX, double startY, StudentWorld* swptr) :Damagable(1, IID_DIRT, startX, startY, swptr,0,1)
{
    //setDirection(90);
}
//////////////////////////////////////Food//////////////////////////////////////////
Food::Food(double startX, double startY, StudentWorld* swptr) : Actor(IID_FOOD, startX, startY, swptr,0,1)
{
    //setDirection(90);
}
///////////////////////////////////////Pit/////////////////////////////////////////
Pit::Pit(double startX, double startY, StudentWorld* swptr) : Actor(IID_PIT, startX, startY, swptr,0,1)
{
    
}
void Pit::doSomething()
{
    if (randInt(1, 50) == 1)
    {
        int b = randInt(1, 3); 
        switch (b) 
        {
        case 1:
            if (m_regSalmonella > 0)
            {
                m_regSalmonella--;
                getWorld()->insert(new RegularSalmonella(getX(), getY(), getWorld()));
            }
            break;
        case2:
            if (m_aggSalmonella > 0)
            {
                m_aggSalmonella--;
                getWorld()->insert(new AggressiveSalmonella(getX(), getY(), getWorld()));
            }
            break;
        case 3:
            if (m_eColi > 0)
            {
                m_eColi--;
                getWorld()->insert(new eColi(getX(), getY(), getWorld()));
            }
            break;
        };
    }
}
/////////////////////////////////////Spray///////////////////////////////
Spray::Spray(double startX, double startY, StudentWorld* swptr, Direction d) : Projectile(IID_SPRAY, startX, startY, swptr, d, 112)
{
    //setDirection(d);
}

void Spray::doSomething()
{
    if (isAlive())
    {
        //if overlaps
        Projectile::doSomething();
        move += (SPRITE_RADIUS * 2);
        if (move >= getMax())
        {
            setDead();
            return;
        }
    }
    return;
}
///////////////////////////////////////Flame//////////////////////////////
Flame::Flame(double startX, double startY, StudentWorld* swptr, Direction d) : Projectile(IID_FLAME, startX, startY, swptr, d, 32)
{
    //setDirection(d);
    move = 0;
}
void Flame::doSomething()
{ 
    if(isAlive())
    {
       /*if (getWorld()->overlapsFlame(this->getX(), this->getY()))
        {
            this->setDead();
            return;
        }*/

        Projectile::doSomething();
        if (getWorld()->overlapsFlame(getX(), getY()))
        {
            setDead();
            return;
        }

        move += (SPRITE_RADIUS * 2);
        if (move >= getMax())
        {
            setDead();
            return;
        }
    }
    return;
}
/////////////////////////////////////////RestoreHealthGoody/////////////////////////
RestoreHealthGoody::RestoreHealthGoody(double startX, double startY, StudentWorld* swptr): Goodie(IID_RESTORE_HEALTH_GOODIE, startX, startY, swptr)
{
}
bool RestoreHealthGoody::maxTime(int ticks)
{
        if (ticks > max(randInt(0, (300 - 10 * getWorld()->getLevel())),50))
        {
            setDead();
            return true;
        }
        return false;
}
void RestoreHealthGoody::doSomething()
{
    if (isAlive())
    {
    }
}
/////////////////////////////////FlameThrowerGoodie/////////////////////////////////
FlameThrowerGoody::FlameThrowerGoody(double startX, double startY, StudentWorld* swptr) : Goodie(IID_FLAME_THROWER_GOODIE, startX, startY, swptr)
{
}

ExtraLifeGoody::ExtraLifeGoody(double startX, double startY, StudentWorld* swptr) : Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, swptr)
{
}

Fungi::Fungi(double startX, double startY, StudentWorld* swptr) : Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, swptr)
{
}
void Fungi::doSomething() {}

////////////////////////////////////////////Salmonella/////////////////////////////////
Salmonella::Salmonella(const int id, double startX, double startY, StudentWorld* swptr, int hp):Bacteria(id, startX, startY, swptr, hp)
{
    mpd = 0;
    m_food = 0;
}


RegularSalmonella::RegularSalmonella(double startX, double startY, StudentWorld* swptr) :Salmonella(IID_SALMONELLA, startX, startY, swptr, 4)
{}

void RegularSalmonella::doSomething()
{
    if (!isAlive())
    { 
        return;
    }
    else if (isAlive())
    {
        if (getWorld()->overlapsSocrates(getX(), getY()))
        {
            getWorld()->harmSocrates(1);
        }
        else if (getFood() == 3)
        {
            double newX, newY;
            if (getX() <= VIEW_WIDTH / 2)
            {
                newX = getX() + SPRITE_RADIUS;
            }
            else if (getX() > VIEW_WIDTH / 2)
            {
                newX = getX() - SPRITE_RADIUS;
            }

            if (getY() <= VIEW_WIDTH / 2)
            {
                newY = getY() + SPRITE_RADIUS;
            }
            else if (getY() > VIEW_WIDTH / 2)
            {
                newY = getY() - SPRITE_RADIUS;
            }

            getWorld()->insert(new RegularSalmonella(newX, newY, getWorld()));
            resetFood();
        }

        else if (getWorld()->overlapsSalmonella(getX(), getY()))
        {
            changeFood(1);
        }

        if (getMPD() > 0)
        {
            changeMPD(-1);
            double threeX, threeY;
            getPositionInThisDirection(getDirection(), 3, threeX, threeY);
            int r = getWorld()->findEuclidean(threeX, threeY, VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
            if (r < VIEW_RADIUS && getWorld()->salmonellaCanMove(threeX, threeY)) 
            {
                moveTo(threeX, threeY);
            }
        }
        else
        {
            Direction rand = randInt(0, 359);
            setDirection(rand);
            resetMPD();
        }
        
    }
        
}

//////////////////////////////////////////////RegularSalmonella/////////////////////////////////

AggressiveSalmonella::AggressiveSalmonella(double startX, double startY, StudentWorld* swptr) : Salmonella(IID_SALMONELLA, startX, startY, swptr, 10)
{}

eColi::eColi(double startX, double startY, StudentWorld* swptr) : Bacteria(IID_ECOLI, startX, startY, swptr, 5)
{}