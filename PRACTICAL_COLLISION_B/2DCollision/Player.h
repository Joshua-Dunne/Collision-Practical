#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Input.h>
#include <Animation.h>
#include <AnimatedSprite.h>

class Player : public GameObject
{

public:
	Player();
	~Player();
	void init();
	Player(const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite* getAnimationSprite();
	void handleInput(sf::Event t_event);
	void update();
	void drawAnim(sf::RenderWindow& t_window);
	sf::CircleShape& getCircleShape();
	sf::VertexArray& getVertexArray();
	sf::Vector2f getVertexPos(int t_pointNum);

private:
	sf::CircleShape m_circle;
	sf::VertexArray m_line;

	sf::Clock m_clock;
};

#endif // !PLAYER_H
