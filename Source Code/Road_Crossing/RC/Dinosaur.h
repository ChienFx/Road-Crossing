#ifndef _DINOSAUR_H
#define _DINOSAUR_H
#include "Animal.h"

class CDinosaur :public CAnimal
{
private:
	static int m_Amount;
public:
	static int getAmount();
	static void Tell();
	void Draw();
	bool isImpact(int x, int y);

	CDinosaur();
	CDinosaur(int x, int y,int d);
	CDinosaur(const CDinosaur &p);
	~CDinosaur();
};

#endif

