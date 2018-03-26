#include "Truck.h"

int CTruck::m_Amount = 0;

int CTruck::getAmount()
{
	return CTruck::m_Amount;
}
CTruck::CTruck() :CVehicle()
{
	CTruck::m_Amount++;
}
CTruck::CTruck(int x, int y,int d) :CVehicle(x, y,d)
{
	CTruck::m_Amount++;
}
CTruck::CTruck(const CTruck &p) : CVehicle(p)
{
	CTruck::m_Amount++;
}

CTruck::~CTruck()
{
	CTruck::m_Amount--;
}

void CTruck::Tell()
{
	MyPlaySound(PTH_SOUND_TRUCK_CRASH);
}


void CTruck::Draw(){
	int x = getX();
	int y = getY();
	int d = getDirect();
	GotoXY(x, y);
	cout << CH_TRUCK;
	GotoXY(x, y + 1);
	cout << CH_TRUCK;
	if (x - 1 > 0)
	{
		if (d == E_RIGHT)
		{
			GotoXY(x - 1, y);
			cout << CH_TRUCK;
		}

		GotoXY(x - 1, y + 1);
		cout << CH_TRUCK;
	}
	if (x + 1 < NUM_COLS)
	{
		if (d == E_LEFT)
		{
			GotoXY(x + 1, y);
			cout << CH_TRUCK;
		}
		GotoXY(x + 1, y + 1);
		cout << CH_TRUCK;
	}
}

bool CTruck::isImpact(int x, int y)
{
	if (CVehicle::isImpact(x, y))
		return true;
	int m_X = getX(), m_Y = getY(), d = getDirect();
	if ((d == E_LEFT && x == m_X + 1 && y == m_Y) || (d == E_RIGHT&&x == m_X - 1 && y == m_Y))
		return true;
	return false;
}

