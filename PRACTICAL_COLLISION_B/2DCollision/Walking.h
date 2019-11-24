#pragma once
#include "State.h"
#include "Animation.h"

class Walking : public State
{
public:
	Walking();
	~Walking();
	void idle(Animation* a);
	void jumping(Animation* a);
	void falling(Animation* a);
	void climbing(Animation* a);
};

