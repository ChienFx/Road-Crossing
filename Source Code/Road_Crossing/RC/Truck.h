#ifndef _TRUCK_H
#define _TRUCK_H

#include "Vehicle.h"

class CTruck :	public CVehicle
{
	static int m_Amount;
public:
	static int getAmount();
	static void Tell();
	void Draw();
	bool isImpact(int x, int y);
	CTruck();
	CTruck(int x, int y, int direct);
	CTruck(const CTruck &p);
	~CTruck();
	
};


#endif