#pragma once
#include <SFML/Graphics.hpp>

struct Capsule
{
	Capsule(sf::Vector2f t_pointA, sf::Vector2f t_pointB, int t_radius);

	sf::CircleShape m_capsuleTop;
	sf::RectangleShape m_body;
	int m_radius;

	sf::Vector2f m_posA;
	sf::Vector2f m_posB;

	void draw(sf::RenderWindow & t_window);

};

