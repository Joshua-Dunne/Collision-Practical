#pragma once
#include "State.h"
#include "Animation.h"

class Falling : public State
{
public:
	Falling();
	~Falling();
	void landing(Animation* a);
	void climbing(Animation* a);
	void walking(Animation* a);
};
