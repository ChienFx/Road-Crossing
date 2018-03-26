#include "Animal.h"

CAnimal::CAnimal()
{
	m_X = m_Y = 0;
	m_direct = E_RIGHT;
}

CAnimal::CAnimal(int x, int y, int d)
{  
	m_X = x; 
	m_Y = y; 
	m_direct = d;
}

CAnimal::CAnimal(const CAnimal &p)
{
	m_X = p.m_X;
	m_Y = p.m_Y;
	m_direct = p.m_direct;
	//CVehicle::m_Amount++;
}

CAnimal::~CAnimal()
{
}

int CAnimal::getX()
{ 
	return m_X; 
}

int CAnimal::getY()
{ 
	return m_Y; 
}

int CAnimal::getDirect(){
	return this->m_direct;
}

void CAnimal::switchDirect()
{
	if (m_direct == E_LEFT)
		m_direct = E_RIGHT;
	else
	{
		m_direct = E_LEFT;
	}
}

void CAnimal::Erase()
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

void CAnimal::Move(int direction, int step)
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

		if (m_Y + step >= NUM_ROWS - 1)
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

void CAnimal::Move()
{
	Move(m_direct, MOVE_STEP);
}

bool CAnimal::writeData(fstream &f)
{
	if (f.is_open())
	{
		f << setw(2) << setfill('0') << m_X << ";";
		f << setw(2) << setfill('0') << m_Y << ";";
		f << setw(2) << setfill('0') << m_direct << endl;// "; " << (int)m_State << endl;
		return true;
	}
	return false;
}

