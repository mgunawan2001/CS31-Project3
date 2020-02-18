#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

/*const int IID_PLAYER                =  0;
const int IID_SALMONELLA            =  1;
const int IID_FOOD                  =  2;
const int IID_ECOLI                 =  3;
const int IID_SPRAY                 =  4;
const int IID_FLAME                 =  5;
const int IID_PIT                   =  6;
const int IID_DIRT                  =  7;
const int IID_FLAME_THROWER_GOODIE  =  8;
const int IID_RESTORE_HEALTH_GOODIE =  9;
const int IID_EXTRA_LIFE_GOODIE     = 10;
const int IID_FUNGUS                = 11;*/
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject 
{ 
public: 
	Actor(int imID, double startX, double startY, StudentWorld* studentWorldptr);
	void doSomething();
	StudentWorld* getWorld() const;
	void findRadius(int x, int y, int& r, int& angle);

private:
	StudentWorld* sw;
};



class Socrates:public Actor
{
public:
	Socrates(StudentWorld* swptr);
	virtual void doSomething();
	
private:
	int m_hitPoints;
	//int m_direction;
	//int m_startAngle;
	//int m_depth;
	//int m_sprayCharges;
	//int m_flameThrowerCharges;	
};

class Dirt: public Actor
{
public:
	Dirt(int startX, int startY, StudentWorld* swptr);
};

/*class Bacterium: public Actor
{};

class Salmonella: public Actor
{};

class AggressiveSalmonella : public Salmonella
{
public:
};

class EColi
{};

class Spray
{};

class Flames
{};

class RestoreHealthGoodies
{};

class ExtraLifeGoodies
{};

class Pits
{};

class Fungi
{};

class Food
{};*/
#endif // ACTOR_H_



