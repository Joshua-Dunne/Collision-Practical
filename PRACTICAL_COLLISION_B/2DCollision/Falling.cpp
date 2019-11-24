#include "Falling.h"
Falling::Falling()
{
}

Falling::~Falling()
{
}

void Falling::landing(Animation* a)
{
	std::cout << "Falling -> Landing" << std::endl;
	a->setCurrent(new Landing());
	delete this;
}

void Falling::climbing(Animation* a)
{
	std::cout << "Falling -> Climbing" << std::endl;
	a->setCurrent(new Climbing());
	delete this;
}

void Falling::walking(Animation* a)
{
	std::cout << "Falling -> Walking" << std::endl;
	a->setCurrent(new Walking());
	delete this;
}