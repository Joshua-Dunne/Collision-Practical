#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Input.h>
#include <Animation.h>
#include <AnimatedSprite.h>
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	Animation fsm;
	AnimatedSprite m_animated_sprite;
	GameObject();
	GameObject(const AnimatedSprite&);

public:
	virtual ~GameObject() = 0;
	virtual void init() = 0;
	virtual AnimatedSprite& getAnimatedSprite() = 0;
	virtual AnimatedSprite* getAnimationSprite() = 0;
	virtual void handleInput(sf::Event t_event) = 0;
	virtual void update() = 0;
	virtual void drawAnim(sf::RenderWindow & t_window) = 0;
	virtual sf::CircleShape& getCircleShape() = 0;
	virtual sf::VertexArray& getVertexArray() = 0;
	virtual sf::Vector2f getVertexPos(int t_pointNum) = 0;
};

#endif // !GAME_OBJECT_H
