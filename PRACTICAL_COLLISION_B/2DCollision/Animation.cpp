#include "Animation.h"

Animation::Animation() : m_current{ new Idle() }, m_previous{ new Idle() }
{
	if (!m_playerTex.loadFromFile("animations.png"))
	{
		std::cerr << "error loading animation png" << std::endl;
	}

	initAnimations();

}

/// <summary>
/// Initialize Animation frames
/// </summary>
void Animation::initAnimations()
{
	sf::IntRect m_idleRect{ 0,0,100,200 };
	sf::IntRect m_idleRectTwo{ 0,200,100,200 };

	sf::IntRect m_walkRect{ 100,0,100,200 };
	sf::IntRect m_walkRectTwo{ 100,200,100,200 };

	sf::IntRect m_jumpRect{ 200,0,100,200 };
	sf::IntRect m_jumpRectTwo{ 200,200,100,200 };

	sf::IntRect m_fallRect{ 300,0,100,200 };
	sf::IntRect m_fallRectTwo{ 300,200,100,200 };

	sf::IntRect m_landRect{ 400,0,100,200 };
	sf::IntRect m_landRectTwo{ 400,200,100,200 };

	sf::IntRect m_climbRect{ 500,0,100,200 };
	sf::IntRect m_climbRectTwo{ 500,200,100,200 };


	m_idleAnim.setTexture(m_playerTex);
	m_idleAnim.addFrame(m_idleRect);
	m_idleAnim.addFrame(m_idleRectTwo);
	m_idleAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_walkAnim.setTexture(m_playerTex);
	m_walkAnim.addFrame(m_walkRect);
	m_walkAnim.addFrame(m_walkRectTwo);
	m_walkAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_jumpAnim.setTexture(m_playerTex);
	m_jumpAnim.addFrame(m_jumpRect);
	m_jumpAnim.addFrame(m_jumpRectTwo);
	m_jumpAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_fallAnim.setTexture(m_playerTex);
	m_fallAnim.addFrame(m_fallRect);
	m_fallAnim.addFrame(m_fallRectTwo);
	m_fallAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_landAnim.setTexture(m_playerTex);
	m_landAnim.addFrame(m_landRect);
	m_landAnim.addFrame(m_landRectTwo);
	m_landAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_climbAnim.setTexture(m_playerTex);
	m_climbAnim.addFrame(m_climbRect);
	m_climbAnim.addFrame(m_climbRectTwo);
	m_climbAnim.setPosition(sf::Vector2f{ 400.0f, 300.0f });

	m_currentAnim = &m_idleAnim;
}

/// <summary>
/// Move to Idle state
/// </summary>
void Animation::idle()
{
	if (!startedJump) // as long as a jump hasn't started, we can go to idle
	{
		m_current->idle(this);
		m_currentAnim = &m_idleAnim;
	}
	
}

/// <summary>
/// Move to jumping state
/// </summary>
void Animation::jumping()
{
	if (!startedJump) // as long as a jump hasn't already started, we can jump
	{
		m_previous = m_current;
		m_current->jumping(this);
		startedJump = true;
		m_currentAnim = &m_jumpAnim;
	}
}

/// <summary>
/// Move to climbing state
/// </summary>
void Animation::climbing()
{
	m_current->climbing(this);
	m_currentAnim = &m_climbAnim;
}

/// <summary>
/// Move to falling state
/// </summary>
void Animation::falling()
{
	m_current->falling(this);
	m_currentAnim = &m_fallAnim;
}

/// <summary>
/// Move to walking state
/// </summary>
void Animation::walking()
{
	m_current->walking(this);
	m_currentAnim = &m_walkAnim;
}

/// <summary>
/// Move to landing state
/// </summary>
void Animation::landing()
{
	m_current->landing(this);
	m_currentAnim = &m_landAnim;
}

/// <summary>
/// Control timers for falling, landing and waiting to go to idle
/// </summary>
void Animation::update()
{
	if (m_fallingClock.getElapsedTime().asSeconds() < 3.0f && startedJump)
	{
		m_landingClock.restart();
		m_idleClock.restart();
	}
	else if (m_fallingClock.getElapsedTime().asSeconds() >= 3.0f
			&& m_landingClock.getElapsedTime().asSeconds() < 3.0f
			&& startedJump)
	{
		landing();
		m_idleClock.restart();
	}
	else if (m_fallingClock.getElapsedTime().asSeconds() >= 3.0f
			&& m_landingClock.getElapsedTime().asSeconds() >= 3.0f
			&& m_idleClock.getElapsedTime().asSeconds() < 1.0f && startedJump)
	{
		idle();
	}
	else
	{
		startedJump = false;
	}

	m_currentAnim->update(); // update frames
	
}

/// <summary>
/// Draws the animation
/// </summary>
/// <param name="t_window">Window to draw</param>
void Animation::drawAnim(sf::RenderWindow& t_window)
{
	t_window.draw(*m_currentAnim);
}
