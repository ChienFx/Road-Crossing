#include "Traffic.h"


CTraffic::CTraffic()
{
	m_lightOn = false;//default: run
	m_count = 0;
	m_timeOn = 20;//stop 20s
	m_timeOff = 60;//run 40s
}


CTraffic::~CTraffic()
{
}


int CTraffic::getTimeOff()
{
	return m_timeOff;
}
void CTraffic::setTimeOff(int t)
{
	m_timeOff = t;
}
int CTraffic::getTimeOn()
{
	return m_timeOn;
}
void CTraffic::setTimeOn(int t)
{
	m_timeOn = t;
}
void CTraffic::increaseCount()
{
	m_count++;
	if (m_count > m_timeOn && isLightOn())
	{
		this->switchState();
		m_count = 0;
	}
	if (m_count > m_timeOff && isLightOff())
	{
		this->switchState();
		m_count = 0;
	}

}
bool CTraffic::isLightOff()
{
	return m_lightOn == false;
}
bool CTraffic::isLightOn()
{
	return m_lightOn == true;
}
void CTraffic::switchState()
{
	m_lightOn = 1 - m_lightOn;
}