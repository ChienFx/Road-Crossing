#ifndef _PEOPLE_H
#define _PEOPLE_H

#include "Vehicle.h"
#include "Truck.h"
#include "Car.h"

#include "Animal.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "MyLib.h"
class CPeople
{
private:
	int m_X;	int m_Y;
	bool m_State;
	static int m_Amount;
public:
	static int getAmount();
	CPeople();
	CPeople(int x, int y);
	CPeople(const CPeople &p);
	~CPeople();

	void move_Up(int);
	void move_Down(int);
	void move_Left(int);
	void move_Right(int);

	bool isImpact(CVehicle **p);
	bool isImpact(CAnimal **p);

	void Die(){ this->m_State = false; }

	bool isFinish();
	bool isDead();

	void MoveCursor(){ GotoXY(m_X, m_Y); }

	void Draw(){ MoveCursor();  cout << CH_PEOPLE; }
	void Erase(){ MoveCursor(); TextColor(CO_DEFAULT);cout << ' '; }
	void Tell(bool sound_on)
	{
		MyPlaySound(sound_on,PTH_SOUND_PEOPLE_CRASH,E_SOUND_SINGLE);
	}
	bool operator == (const CPeople &p)
	{return(m_X == p.m_X && m_Y == p.m_Y);}

	bool writeData(fstream &f)
	{
		if (f.is_open())
		{
			f << m_X << ";" << m_Y << endl;// ";" << (int)m_State << endl;
			return true;
		}
		return false;
	}
};



#endif