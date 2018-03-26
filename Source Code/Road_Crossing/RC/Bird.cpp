#include "Bird.h"

int CBird::m_Amount = 0;

int CBird::getAmount()
{
	return CBird::m_Amount;
}
CBird::CBird() :CAnimal()
{
	CBird::m_Amount++;
}
CBird::CBird(int x, int y,int d) : CAnimal(x, y,d)
{
	CBird::m_Amount++;
}
CBird::CBird(const CBird &p) : CAnimal(p)
{
	CBird::m_Amount++;
}

CBird::~CBird()
{
	CBird::m_Amount--;
}

void CBird::Draw()
{
	int x = getX();
	int y = getY();
	GotoXY(x, y + 1);
	cout << CH_BIRD;
	if (x - 1 > 0)
	{
		GotoXY(x - 1, y);
		cout << CH_BIRD;
	}
	if (x + 1 < NUM_COLS)
	{
		GotoXY(x + 1, y);
		cout << CH_BIRD;
	}
}
bool CBird::isImpact(int x, int y)
{
	int m_X = getX(), m_Y = getY();
	if (y == m_Y)
	{
		if (x == m_X - 1 || x == m_X + 1)
			return true;
	}
	else if (y == m_Y + 1)
	{
		if (x == m_X)
			return true;
	}
	return false;
}
void CBird::Tell()
{
	MyPlaySound(PTH_SOUND_BIRD_CRASH);
}