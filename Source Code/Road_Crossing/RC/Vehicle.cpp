#include "Vehicle.h"

CVehicle::CVehicle()
{
	m_X = m_Y = 0;
	m_direct = 0;
}

CVehicle::CVehicle(int x, int y, int direct) 
{ 
	m_X = x; m_Y = y; 
	m_direct = direct;
	//CVehicle::m_Amount++;
}

CVehicle::CVehicle(const CVehicle &p)
{
	m_X = p.m_X;
	m_Y = p.m_Y;
}

CVehicle::~CVehicle()
{
}

void CVehicle::Erase()
{
	TextColor(CO_DEFAULT);
	GotoXY(m_X, m_Y);
	cout << ' ';
	GotoXY(m_X, m_Y + 1);
	cout << ' ';
	if (m_X - 1 > 0)
	{
		GotoXY(m_X - 1, m_Y);
		cout << ' ';
		GotoXY(m_X - 1, m_Y + 1);
		cout << ' ';
	}
	if (m_X + 1 < NUM_COLS)
	{
		GotoXY(m_X + 1, m_Y);
		cout << ' ';
		GotoXY(m_X + 1, m_Y + 1);
		cout << ' ';
	}
}

void CVehicle::Move(int direction, int step)
{
	switch (direction)
	{
	case E_UP:

		if (m_Y - step <= 1)
			m_Y = NUM_ROWS - 2;
		else
			m_Y -= step;
		break;

	case E_DOWN:

		if (m_Y + step >= NUM_ROWS-1)
			m_Y = 2;
		else
			m_Y += step;
		break;

	case E_LEFT:

		if (m_X - step <= 0)
			m_X = NUM_COLS - abs(m_X - step) - 1;
		else
			m_X -= step;
		break;

	case E_RIGHT:

		if (m_X + step >= NUM_COLS)
			m_X = abs(NUM_COLS - (m_X + step)) + 1;
		else
			m_X += step;
		break;
	}
}

void CVehicle::Move()
{
	Move(m_direct, MOVE_STEP);
}

bool CVehicle::isImpact (int x, int y)
{
	if (y == m_Y)
	{
		if (x == m_X)
			return true;
	}
	else if (y == m_Y + 1)
	{
		if (x >= m_X - 1 && x <= m_X + 1)
			return true;
	}
	return false;
}

int CVehicle::getX()
{
	return this->m_X;
}

int CVehicle::getY()
{
	return this->m_Y;
}

int CVehicle::getDirect(){
	return this->m_direct;
}

void CVehicle::switchDirect()
{
	if (m_direct == E_LEFT)
		m_direct = E_RIGHT;
	else
	{
		m_direct = E_LEFT;
	}
}
bool CVehicle::writeData(fstream &f)
{
	if (f.is_open())
	{
		f << setw(2) << setfill('0') << m_X << ";";
		f << setw(2) << setfill('0') << m_Y << ";";
		f << setw(2) << setfill('0') << m_direct << endl;
		return true;
	}
	return false;
}