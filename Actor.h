#ifndef ACTOR_H_
#define ACTOR_H_

#include <stdlib.h>
#include "GraphObject.h"
#include<math.h>
#include <algorithm>  
class StudentWorld;
using namespace std;

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

/*GraphObject
    Actor
        Dirt
        Food
        Pit
        Projectile
            Flame
            Spray
        Goodie
            RestoreHealthGoodie
            FlamethrowerGoodie
            ExtraLifeGoodie
            Fungus
        Agent
            Socrates
            Bacterium
                EColi
                Salmonella
                    RegularSalmonella
                    AggressiveSalmonella*/

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
public:
	Actor(const int imID, double startX, double startY, StudentWorld* studentWorldptr, Direction dir = 0, int depth = 0, double size = 1.0);
	virtual void doSomething();

	StudentWorld* getWorld() const;
	int getLevel();

	virtual bool isAlive();
	void setDead();

	virtual bool affectedBySalmonella() { return false; }
	virtual bool blocksSalmonella() { return false; }

	virtual void damagedByFlame() { return; }
	virtual void harmSocrates() {}
	virtual bool isDamagable()
	{
		return false;
	}
	
	virtual ~Actor() { delete sw; }

private:
	StudentWorld* sw;
	bool m_alive;
};

class Damagable : public Actor
{
public:
	Damagable(int hp, const int id, double startX, double startY, StudentWorld* swptr, Direction dir = 0, int depth = 0, double size = 1.0);
	
	bool isDamagable() 
	{
		return true;
	}

	int getHitPoints();
	bool isAlive()
	{
		if (m_hitPoints <= 0)
		{
			setDead();
		}
		return Actor::isAlive();
	}


	virtual void damagedByFlame() 
	{ 
		m_hitPoints -= 5; 
		if (m_hitPoints <= 0)
		{
			setDead();
		}
	}
	
	virtual ~Damagable() {}
private:
	int m_hitPoints;
};

class Goodie : public Actor
{
public:
	Goodie(const int id, double startX, double startY, StudentWorld* swptr);
	bool isLimited() { return true; }
	int getMaxLife() { return maxLife; }
private:
	int maxLife = max(randInt(0, (300 - 10 * getLevel())), 50);

};

class Projectile: public Actor
{
public:
	Projectile(const int id, double startX, double startY, StudentWorld* swptr, Direction d, int maxTravel);
	int getMax() { return m_maxTravel; }
	void doSomething(){ moveForward(SPRITE_RADIUS * 2); }
private:
	int m_maxTravel;
};


class Bacteria : public Damagable
{
public:
	Bacteria(const int id, double startX, double startY, StudentWorld* swptr, int hp);
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
	bool blocksSalmonella() { return true; }
};

class Pit:public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* swptr);
	void doSomething();
private:
	int m_regSalmonella = 5;
	int m_aggSalmonella = 3;
	int m_eColi = 2;
};

class Food :public Actor
{
public:
	Food(double startX, double startY, StudentWorld* swptr);
	bool affectedBySalmonella() { return true; }
};




class Spray : public Projectile
{
public:
	Spray(double startX, double startY, StudentWorld* swptr, Direction d);
	void doSomething();
private:
	int move;

};
class Flame: public Projectile
{
public:
	Flame(double startX, double startY, StudentWorld* swptr, Direction d);
	void doSomething();
private:
	int move;
};




class RestoreHealthGoody:public Goodie
{
public: 
	RestoreHealthGoody(double startX, double startY, StudentWorld* swptr);
	bool maxTime(int ticks);
	void doSomething();
	
private:
};
class FlameThrowerGoody: public Goodie
{
public:
	FlameThrowerGoody(double startX, double startY, StudentWorld* swptr);
	//bool maxTime(int ticks);
	//void doSomething();

private:
};

class ExtraLifeGoody:public Goodie
{
public:
	ExtraLifeGoody(double startX, double startY, StudentWorld* swptr);
	//bool maxTime(int ticks);
	//void doSomething();

private:
};

class Fungi :public Goodie
{
public:
	Fungi(double startX, double startY, StudentWorld* swptr);
	//bool maxTime(int ticks);
	void doSomething();

private:
};

class Salmonella: public Bacteria
{
public:
	Salmonella(const int id, double startX, double startY, StudentWorld* swptr, int hp);
	int getMPD() { return mpd; }
	void changeMPD(int c) { mpd += c; }
	void resetMPD() { mpd = 10; }
	int getFood() { return m_food; }
	void changeFood(int c) { m_food += c; }
	void resetFood() { m_food = 0; }
	//virtual void doSomething();
private:
	int mpd;
	int m_food;
};

class RegularSalmonella : public Salmonella
{
public:
	RegularSalmonella(double startX, double startY, StudentWorld* swptr);
	void doSomething();
};

class AggressiveSalmonella : public Salmonella
{
public:
	AggressiveSalmonella(double startX, double startY, StudentWorld* swptr);
};

class eColi:public Bacteria
{
public:
	eColi(double startX, double startY, StudentWorld* swptr);
};



/*class Bacterium: public Actor
{
	
};






class Fungi
{
	void harmSocrates()
	{
		increaseScore(-50);
		getWorld()->decHitPoints(20);
	}
};*/
#endif // ACTOR_H_



