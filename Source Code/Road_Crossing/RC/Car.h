#ifndef _CAR_H
#define _CAR_H

#include "Vehicle.h"

class CCar :	public CVehicle
{
	static int m_Amount;
public:
	static int getAmount();
	static void Tell();
	void Draw();
	CCar();
	CCar(int x, int y, int d);
	CCar(const CCar &p);
	~CCar();
};


#endif