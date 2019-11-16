#include "Capsule.h"


Capsule::Capsule(sf::Vector2f t_pointA, sf::Vector2f t_pointB, int t_radius)
	: m_capsuleTop{ t_radius }
	, m_body{}
	, m_radius{ t_radius }
	, m_posA{t_pointA}
	, m_posB{t_pointB}
{
	m_capsuleTop.setRadius(m_radius);
	m_capsuleTop.setOrigin(m_radius, m_radius);
	m_capsuleTop.setPosition(m_posA);

	m_body.setSize(sf::Vector2f{ static_cast<float>(m_radius) * 2, m_posA.y - m_posB.y });
	m_body.setOrigin(m_body.getSize().x / 2, m_body.getSize().y);
	m_body.setPosition(m_capsuleTop.getPosition());
}

void Capsule::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);

	m_capsuleTop.setPosition(m_posA);
	t_window.draw(m_capsuleTop);

	m_capsuleTop.setPosition(m_posB);
	t_window.draw(m_capsuleTop);

}
