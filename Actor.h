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
	Actor(const int imID, double startX, double startY, StudentWorld* studentWorldptr);
	virtual void doSomething();

	StudentWorld* getWorld() const;

	bool isAlive();
	void setDead();

	void getPos(double& x, double& y) { x = -100; y = -100; }
	void damagedByFlame() {}
	void harmSocrates(){}
	
	virtual ~Actor() { delete sw; }

private:
	StudentWorld* sw;
	bool m_alive;
};

class Damagable : public Actor
{
public:
	Damagable(int hp, const int id, double startX, double startY, StudentWorld* swptr);
	
	void getPos(double& x, double& y) { x = getX(); y = getY(); }
	void damagedByFlame() { m_hitPoints -= 5; }
	
	int getHitPoints();
	bool isAlive()
	{
		if (m_hitPoints <= 0)
		{
			setDead();
		}
		return Actor::isAlive();
	}
	virtual ~Damagable() {}
private:
	int m_hitPoints;
};

//class Living : public Actor
//{
//public:
//	Living(int hp, const int id, double startX, double startY, StudentWorld* swptr);
//	int getHitPoints();
//	bool isAlive() 
//	{
//		if (m_hitPoints <= 0)
//		{
//			setDead();
//		}
//		Actor::isAlive();
//	}
//	virtual ~Living() {}
//private:
//	int m_hitPoints;
//};

class Bacteria : public Damagable
{
public:
	Bacteria(int hp, const int id, double startX, double startY, StudentWorld* swptr);
};

















class Socrates:public Damagable
{
public:
	Socrates(double startX, double startY, StudentWorld* swptr);
	void doSomething();

	void moveSocrates(double d);

	int getHitPoints() const;
	void decHitPoints(int m);

	int getSprays() const;
	int getFlames() const;

	void overlap(Actor* a);


private:
	int m_hitPoints;
	//int m_direction;
	//int m_angle;
	//int m_depth;
	int m_sprayCharges;
	int m_flameThrowerCharges;
	bool alive;
	int tickNotPressed;
};

class Dirt: public Damagable
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

class Spray : public Actor
{
public:
	Spray(double startX, double startY, StudentWorld* swptr, Direction d);
};
class Flame: public Actor
{
public:
	Flame(double startX, double startY, StudentWorld* swptr, Direction d);
	void doSomething();
};

//class Spray:public Actor
//{
//public:
//	Spray(double startX, double startY, StudentWorld* swptr);
//};

/*class Bacterium: public Actor
{
	
};

class Salmonella: public Actor
{};

class AggressiveSalmonella : public Salmonella
{
public:
};

class EColi
{};

class RestoreHealthGoodies
{};

class ExtraLifeGoodies
{};

class Fungi
{
	void harmSocrates()
	{
		increaseScore(-50);
		getWorld()->decHitPoints(20);
	}
};*/
#endif // ACTOR_H_



