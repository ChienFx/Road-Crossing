#ifndef _CANIMAL_H
#define _CANIMAL_H
#include <iostream>
#include "MyLib.h"
using namespace std;

class CAnimal
{
private:
	int m_X; int m_Y;
	int m_direct;
public:
	CAnimal();
	CAnimal(int x, int y,int d);
	CAnimal(const CAnimal &p);
	~CAnimal();
	int getX();
	int getY();
	void switchDirect();
	virtual bool isImpact(int x, int y) = 0;
	void Erase();
	int getDirect();
	bool writeData(fstream &f);
	void Move(int direction, int step);
	void Move();
};

#endif