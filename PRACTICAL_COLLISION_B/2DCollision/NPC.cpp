#include <iostream>
#include <NPC.h>
#include <Idle.h>
#include <Debug.h>

NPC::NPC() : GameObject()
{
	fsm.setCurrent(new Idle());
	fsm.setPrevious(new Idle());
}

NPC::NPC(const AnimatedSprite& s) : GameObject(s)
{
	fsm.setCurrent(new Idle());
	fsm.setPrevious(new Idle());
}

NPC::~NPC()
{
}

void NPC::init()
{
}

AnimatedSprite& NPC::getAnimatedSprite()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

AnimatedSprite* NPC::getAnimationSprite()
{
	return nullptr;
}

void NPC::handleInput(sf::Event t_event)
{
	switch (t_event.type)
	{
	case sf::Event::KeyPressed:
		//std::cout << "NPC Idling" << std::endl;
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

void NPC::update()
{
	//std::cout << "Handle Update" << std::endl;
	m_animated_sprite.update();
}

void NPC::drawAnim(sf::RenderWindow& t_window)
{
}

sf::CircleShape& NPC::getCircleShape()
{
	return m_circle;
}

sf::VertexArray& NPC::getVertexArray()
{
	return m_line;
}

sf::Vector2f NPC::getVertexPos(int t_pointNum)
{
	return m_line[1].position;
}
