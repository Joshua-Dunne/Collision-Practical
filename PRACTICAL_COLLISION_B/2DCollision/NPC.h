#ifndef NPC_H
#define NPC_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>

class NPC : public GameObject
{

public:
	NPC();
	~NPC();
	void init();
	NPC(const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();
	sf::CircleShape& getCircleShape();
	sf::VertexArray& getVertexArray();
	sf::Vector2f getVertexPos(int t_pointNum);

private:
	sf::CircleShape m_circle;
	sf::VertexArray m_line{ sf::Lines, 2 };
};

#endif // !NPC_H
