#include "Landing.h"

Landing::Landing()
{
}

Landing::~Landing()
{
}

void Landing::idle(Animation* a)
{
	std::cout << "Landing -> Idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Landing::walking(Animation* a)
{
	std::cout << "Landing -> Walking" << std::endl;
	a->setCurrent(new Walking());
	delete this;
}
