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
	virtual void doSomething();
	StudentWorld* getWorld() const;
	void findRadius(int x, int y, int& r, int& angle);

private:
	StudentWorld* sw;
};



class Socrates:public Actor
{
public:
	Socrates(double startX, double startY, StudentWorld* swptr);
	virtual void doSomething();
	void moveSocrates(double d);
	int getHitPoints();
	int getSprays();
	int getFlames();

	//void move(int angle, int r, double& x, double& y);
	
private:
	int m_hitPoints;
	//int m_direction;
	//int m_angle;
	//int m_depth;
	int m_sprayCharges;
	int m_flameThrowerCharges;
};

class Dirt: public Actor
{
public:
	Dirt(double startX, double startY, StudentWorld* swptr);
};

class Pit:public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* swptr);
};

class Food :public Actor
{
public:
	Food(double startX, double startY, StudentWorld* swptr);
};

class Spray:public Actor
{
public:
	Spray(double startX, double startY, StudentWorld* swptr);
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



class Flames
{};

class RestoreHealthGoodies
{};

class ExtraLifeGoodies
{};

class Fungi
{};*/
#endif // ACTOR_H_



