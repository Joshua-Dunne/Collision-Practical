#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>

class Player : public GameObject
{

public:
	Player();
	~Player();
	void init();
	Player(const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();
	sf::CircleShape& getCircleShape();
	sf::VertexArray& getVertexArray();
	sf::Vector2f getVertexPos(int t_pointNum);

private:
	sf::CircleShape m_circle;
	sf::VertexArray m_line;
};

#endif // !PLAYER_H
