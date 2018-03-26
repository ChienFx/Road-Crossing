#ifndef _TRAFFIC_H
#define _TRAFFIC_H
#include "MyLib.h"
class CTraffic
{
private:
	//true: stop, false: run
	bool m_lightOn;
	int  m_count;
	int  m_timeOn;
	int  m_timeOff;
public:
	CTraffic();
	~CTraffic();
	int getCount(){ return m_count; }
	int getTimeOn();
	void setTimeOn(int t);
	int getTimeOff();
	void setTimeOff(int t);
	void increaseCount();
	bool isLightOn();
	bool isLightOff();
	void switchState();
};

#endif