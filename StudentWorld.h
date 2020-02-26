#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include<vector>
#include<list>
using namespace std;

#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    int findEuclidean(int startX, int startY, int endX, int endY);
    bool checkAllowed(int startX, int startY);

    
    void insert(Actor* a) { actors.push_back(a); }
    Actor* inPos(int i) 
    { //return actors[i]; 
        list<Actor*>::iterator it = actors.begin();
        for (int k=0; k<i;k++)
        {
            it++;
        }
        return *it;
    }

    void harmSocrates(int h)
    {
        m_player->decHitPoints(h);
    }
    
    bool overlapsSocrates(double X, double Y)
    {
        double socX = m_player->getX();
        double socY = m_player->getY();

        if (findEuclidean(socX, socY, X, Y) <= SPRITE_RADIUS * 2)
        {
            return true;
        }
        return false;
    }

    bool overlapsSalmonella(double salmonellaX, double salmonellaY)
    {
        list<Actor*>::iterator it = actors.begin();
        for (; it != actors.end(); it++)
        {
            if ((*it)->affectedBySalmonella())
            {
                int x = (*it)->getX(), y = (*it)->getY();
                if (findEuclidean(x, y, salmonellaX, salmonellaY) <= (2 * SPRITE_RADIUS))
                {
                    (*it)->setDead();
                    return true;
                }
            }
        }
        return false;
    }

    
    bool overlapsFlame(double flameX, double flameY) 
    {
        /*for (int i = 0; i < actors.size(); i++)
        {
            int x = actors[i]->getX(), y = actors[i]->getY();
            if (actors[i]->isDamagable())
            {
                if (findEuclidean(x, y, flameX, flameY) <= (2 * SPRITE_RADIUS))
                {
                    return  true;
                }
            }
        }*/

        list<Actor*>::iterator it = actors.begin();
        for (; it != actors.end();it++)
        {
            int x = (*it)->getX(), y = (*it)->getY();
            if ((*it)->isDamagable())
            {
                if (findEuclidean(x, y, flameX, flameY) <= (2 * SPRITE_RADIUS))
                {
                    (*it)->setDead();
                    return true;
                }
            }
        }
        return false;
    }

    bool salmonellaCanMove(double salmonellaX, double salmonellaY)
    {
        list<Actor*>::iterator it = actors.begin();
        for (; it != actors.end(); it++)
        {
            if ((*it)->blocksSalmonella()) 
            {
                int x = (*it)->getX(), y = (*it)->getY();
                if (findEuclidean(x, y, salmonellaX, salmonellaY) < SPRITE_RADIUS)
                {
                    return false;
                }
            }
        }
        return true;
    }
private:
    Socrates* m_player;
    //vector<Actor*> actors;
    list<Actor*> actors;

    struct Coordinate
    {
        double x, y;

        Coordinate(double X, double Y) :x(X), y(Y) {}
    };

    vector<Coordinate> coords;
    
};



#endif // STUDENTWORLD_H_
