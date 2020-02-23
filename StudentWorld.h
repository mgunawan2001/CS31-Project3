#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include<vector>
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

    
    vector<Actor*> getActors() { return actors; }

    void insert(Actor* a) { actors.push_back(a); }
    Actor* inPos(int i) { return actors[i]; }

private:
    Socrates* m_player;
    vector<Actor*> actors;

    struct Coordinate
    {
        double x, y;

        Coordinate(double X, double Y) :x(X), y(Y) {}
    };

    vector<Coordinate> coords;
    
};



#endif // STUDENTWORLD_H_
