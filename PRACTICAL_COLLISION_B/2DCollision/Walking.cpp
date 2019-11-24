#include "Walking.h"

Walking::Walking()
{
}

Walking::~Walking()
{
}

void Walking::idle(Animation* a)
{
	std::cout << "Walking -> Idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Walking::jumping(Animation* a)
{
	std::cout << "Walking -> Jumping" << std::endl;
	a->setCurrent(new Jumping());
	delete this;
}

void Walking::falling(Animation* a)
{
	std::cout << "Walking -> Falling" << std::endl;
	a->setCurrent(new Falling());
	delete this;
}

void Walking::climbing(Animation* a)
{
	std::cout << "Walking -> Climbing" << std::endl;
	a->setCurrent(new Climbing());
	delete this;
}
