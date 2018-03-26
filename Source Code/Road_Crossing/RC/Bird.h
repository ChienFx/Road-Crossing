#ifndef _BIRD_H
#define _BIRD_H
#include "Animal.h"

class CBird:public CAnimal
{
private:
	static int m_Amount;
public:
	static int getAmount();
	static void Tell();
	void Draw();
	bool isImpact(int x, int y);
	CBird();
	CBird(int x, int y,int d);
	CBird(const CBird &p);
	~CBird();
};

#endif

