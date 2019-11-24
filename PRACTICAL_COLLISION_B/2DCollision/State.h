#pragma once
#include <iostream>

class Animation; // forward reference to animation class
class Jumping; // forward reference to jumping class
class Climbing; // forward reference to climbing class
class Idle; // forward reference to idle class
class Falling; // foward reference to falling class
class Walking; // forward reference to walking class
class Landing; // forward reference to landing class

class State
{
public:
	virtual void idle(Animation* a) {};
	virtual void jumping(Animation* a) {};
	virtual void climbing(Animation* a) {};
	virtual void falling(Animation* a) {};
	virtual void walking(Animation* a) {};
	virtual void landing(Animation* a) {};
};

