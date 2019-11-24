#pragma once

#include "State.h"
#include "Idle.h"
#include "Climbing.h"
#include "Jumping.h"
#include "Falling.h"
#include "Walking.h"
#include "Landing.h"
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>


class Animation
{
	class State* m_current;
	class State* m_previous;
public:
	Animation();

	void initAnimations();

	void setCurrent(State* s) { m_current = s; };
	void setPrevious(State* s) { m_previous = s; };
	State* getCurrent(){ return m_current; };
	State* getPrevious() { return m_previous; };
	void idle();
	void jumping();
	void climbing();
	void falling();
	void walking();
	void landing();

	void update();
	void drawAnim(sf::RenderWindow & t_window);


	sf::Clock m_fallingClock;
	sf::Clock m_landingClock;
	sf::Clock m_idleClock;

	bool startedJump{ false };

	sf::Texture m_playerTex;
	AnimatedSprite m_idleAnim;
	AnimatedSprite m_walkAnim;
	AnimatedSprite m_jumpAnim;
	AnimatedSprite m_fallAnim;
	AnimatedSprite m_landAnim;
	AnimatedSprite m_climbAnim;

	AnimatedSprite* m_currentAnim;

	
};

