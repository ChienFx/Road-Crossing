#include "Car.h"

int CCar::m_Amount = 0;

int CCar::getAmount()
{
	return CCar::m_Amount;
}
CCar::CCar() :CVehicle()
{
	CCar::m_Amount++;
}
CCar::CCar(int x, int y,int d) :CVehicle(x, y, d)
{
	CCar::m_Amount++;
}
CCar::CCar(const CCar &p) : CVehicle(p)
{
	CCar::m_Amount++;
}

CCar::~CCar()
{
	CCar::m_Amount--;
}

void CCar::Tell()
{
	MyPlaySound(PTH_SOUND_CAR_CRASH);
}

void CCar::Draw(){
	int x = getX();
	int y = getY();

	GotoXY(x, y);

	cout << CH_CAR;
	GotoXY(x, y + 1);
	cout << CH_CAR;
	if (x - 1 > 0)
	{
		GotoXY(x - 1, y + 1);
		cout << CH_CAR;
	}
	if (x + 1 < NUM_COLS)
	{
		GotoXY(x + 1, y + 1);
		cout << CH_CAR;
	}
}