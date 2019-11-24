#pragma once
#include "State.h"
#include "Animation.h"

class Landing : public State
{
public:
	Landing();
	~Landing();
	void idle(Animation* a);
	void walking(Animation* a);
};
