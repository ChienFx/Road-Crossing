#include "People.h"

int CPeople::m_Amount = 0;

CPeople::CPeople()
{
	m_State = true;
	m_X = 0; 
	m_Y = 0;
	m_Amount++;
}

CPeople::CPeople(int x, int y)
{
	m_X = x; m_Y = y;
	m_State = true;
	m_Amount++;
}
CPeople::CPeople(const CPeople &p)
{
	m_X = p.m_X;
	m_Y = p.m_Y;
	m_State = p.m_State;
	m_Amount++;
}

CPeople::~CPeople()
{
	m_Amount--;
}
int CPeople::getAmount()
{
	return m_Amount;
}
void CPeople::move_Up(int n)
{
	if (m_Y - n > 0 && m_Y - n < NUM_ROWS)
	{
		MoveCursor();
		cout << ' ';
		m_Y -= n;
	}
}
void CPeople::move_Down(int n)
{
	if (m_Y + n > 0 && m_Y + n < NUM_ROWS)
	{
		MoveCursor();
		cout << ' ';
		m_Y += n;
	}
}
void CPeople::move_Left(int n)
{
	if (m_X - n > 0 && m_X - n < NUM_COLS)
	{
		MoveCursor();
		cout << ' ';
		m_X -= n;
	}
}
void CPeople::move_Right(int n)
{
	if (m_X + n > 0 && m_X + n < NUM_COLS)
	{
		MoveCursor();
		cout << ' ';
		m_X += n;
	}
}
bool CPeople::isImpact(CVehicle **p)
{
	int x, y;
	int n = CTruck::getAmount() + CCar::getAmount();
	for (int i = 0; i < n; i++)
	{
		if (p[i]->isImpact(m_X,m_Y))
		{
			return true;
		}
	}

	return false;
}

bool CPeople::isImpact(CAnimal **p)
{
	int n = CBird::getAmount() + CDinosaur::getAmount();
	for (int i = 0; i < n; i++)
	{
		if (p[i]->isImpact(m_X, m_Y))
		{
			return true;
		}
	}
	return false;
}
bool CPeople::isFinish()
{
	if (m_Y == 1)
		return true;
	return false;
}
bool CPeople::isDead()
{
	return m_State == false;
}

