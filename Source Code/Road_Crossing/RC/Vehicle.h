#ifndef _CVEHICLE_H
#define _CVEHICLE_H
#include <iostream>
#include "MyLib.h"
using namespace std;

class CVehicle
{
private:
	int m_X; int m_Y;
	int m_direct;
public:
	CVehicle();
	CVehicle(int x, int y, int direct);
	CVehicle(const CVehicle &p);
	~CVehicle();
	virtual bool isImpact(int x, int y);
	int getX();
	int getY();
	int getDirect();
	void Move();
	void MoveCursor();
	void switchDirect();
	bool writeData(fstream &f);
	void Erase();
	void Move(int direction, int step);
};

#endif