#include <iostream>
#include <Player.h>
#include <Idle.h>
#include <Debug.h>

Player::Player() : GameObject()
{
	fsm.setCurrent(new Idle());
	fsm.setPrevious(new Idle());
}

Player::Player(const AnimatedSprite& s) : GameObject(s)
{
	fsm.setCurrent(new Idle());
	fsm.setPrevious(new Idle());
}

Player::~Player()
{
}

void Player::init()
{
	m_circle.setRadius(20.0f);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setPosition(-1000.0f, -1000.0f);
	m_circle.setFillColor(sf::Color::White);

	m_line.setPrimitiveType(sf::Lines);
	m_line.append(sf::Vertex{ sf::Vector2f{0,0} });
	m_line.append(sf::Vertex{ sf::Vector2f{10,10} });

	fsm.initAnimations();
}

AnimatedSprite& Player::getAnimatedSprite()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

AnimatedSprite* Player::getAnimationSprite()
{
	return fsm.m_currentAnim;
}

sf::CircleShape& Player::getCircleShape()
{
	return m_circle;
}

sf::VertexArray& Player::getVertexArray()
{
	return m_line;
}

sf::Vector2f Player::getVertexPos(int t_pointNum)
{
	return m_line[t_pointNum].position;
}

void Player::handleInput(sf::Event t_event)
{

	switch (t_event.type)
	{
	case sf::Event::KeyPressed:
		//std::cout << "Player Idling" << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			fsm.walking();
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			fsm.climbing();
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			fsm.walking();
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			fsm.jumping();
			break;
		}
		default:
			fsm.idle();
		break;
	}
}

void Player::update()
{
	//std::cout << "Handle Update" << std::endl;
	m_animated_sprite.update();

	if (m_clock.getElapsedTime().asSeconds() > 1.0f)
	{
		fsm.update();
		m_clock.restart();
	}
	
}

void Player::drawAnim(sf::RenderWindow & t_window)
{
	fsm.drawAnim(t_window);
}
