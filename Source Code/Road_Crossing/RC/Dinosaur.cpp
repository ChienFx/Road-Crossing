#include "Dinosaur.h"

int CDinosaur::m_Amount = 0;

int CDinosaur::getAmount()
{
	return CDinosaur::m_Amount;
}
CDinosaur::CDinosaur() :CAnimal()
{
	CDinosaur::m_Amount++;
}
CDinosaur::CDinosaur(int x, int y,int d) : CAnimal(x, y,d)
{
	CDinosaur::m_Amount++;
}
CDinosaur::CDinosaur(const CDinosaur &p) : CAnimal(p)
{
	CDinosaur::m_Amount++;
}

CDinosaur::~CDinosaur()
{
	CDinosaur::m_Amount--;
}

void CDinosaur::Draw(){
	int x = getX();
	int y = getY();
	int d = getDirect();
	GotoXY(x, y);
	cout << (char)CH_DINO;
	GotoXY(x, y + 1);
	cout << (char)CH_DINO;
	if (x - 1 > 0)
	{
		if (d == E_LEFT)
		{
			GotoXY(x - 1, y);
			cout << (char)CH_DINO;
		}
		else
		{
			GotoXY(x - 1, y + 1);
			cout << (char)CH_DINO;
		}
	}
	if (x + 1 < NUM_COLS)
	{
		if (d == E_RIGHT)
		{
			GotoXY(x + 1, y);
			cout << (char)CH_DINO;
		}
		else
		{
			GotoXY(x + 1, y + 1);
			cout << (char)CH_DINO;
		}
	}
}
bool CDinosaur::isImpact(int x, int y)
{
	int m_X = getX(), m_Y = getY(), d = getDirect();
	if (y == m_Y)
	{
		if (d == E_LEFT)
		{
			if (x == m_X - 1 || x == m_X)
				return true;
		}
		else if (d == E_RIGHT)
		{
			if (x == m_X || x == m_X + 1)
				return true;
		}
	}
	else if (y == m_Y + 1)
	{
		if (d == E_LEFT)
		{
			if (x == m_X + 1 || x == m_X)
				return true;
		}
		else if (d == E_RIGHT)
		{
			if (x == m_X || x == m_X - 1)
				return true;
		}
	}
	return false;
}

void CDinosaur::Tell()
{
	MyPlaySound(PTH_SOUND_DINO_CRASH);
}