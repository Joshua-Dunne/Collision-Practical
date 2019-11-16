#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>
#include "Capsule.h"

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	sf::CircleShape m_capsuleCircle;
	m_capsuleCircle.setFillColor(sf::Color::White);
	m_capsuleCircle.setRadius(20.0f);

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup the NPC
	GameObject& npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject& player = Player(player_animated_sprite);
	player.init();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width,
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	enum ShapeState{AABB, Circle, Ray};
	ShapeState m_currentShape{ AABB };

	// Initialize Input
	Input input;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);

	// vertex array of lines
	sf::VertexArray hitboxArray{ sf::LineStrip, 5 };

	Capsule capsule{ sf::Vector2f{600.0f, 50.0f}, sf::Vector2f{600.0f, 100.0f}, 25 };

	c2Capsule c2_capsule;
	c2_capsule.a = c2v{ capsule.m_posA.x, capsule.m_posA.y };
	c2_capsule.b = c2v{ capsule.m_posB.x, capsule.m_posB.y };
	c2_capsule.r = static_cast<float>(capsule.m_radius);

	VertexArray npc_triangle{ sf::Triangles, 3 };

	c2Poly c2_polygon;
	c2_polygon.count = 3;
	c2_polygon.verts[0].x = 200;
	c2_polygon.verts[0].y = 100;

	c2_polygon.verts[1].x = 150;
	c2_polygon.verts[1].y = 200;

	c2_polygon.verts[2].x = 250;
	c2_polygon.verts[2].y = 200;

	npc_triangle[0].position = sf::Vector2f{ c2_polygon.verts[0].x, c2_polygon.verts[0].y };
	npc_triangle[1].position = sf::Vector2f{ c2_polygon.verts[1].x, c2_polygon.verts[1].y };
	npc_triangle[2].position = sf::Vector2f{ c2_polygon.verts[2].x, c2_polygon.verts[2].y };


	c2Ray c2_ray;
	c2_ray.p = c2v{ 450, 550 };
	c2_ray.d = c2v{ 1, 0 };
	c2_ray.t = 100.0f;

	VertexArray npc_ray{ sf::Lines, 2 };
	npc_ray[0].position = { sf::Vector2f{c2_ray.p.x, c2_ray.p.y} };
	npc_ray[1].position = { sf::Vector2f{c2_ray.p.x + (c2_ray.t * c2_ray.d.x), c2_ray.p.y +(c2_ray.t * c2_ray.d.y)} };

	c2Circle c2_circle;
	c2_circle.p = c2v{ 100, 400 };
	c2_circle.r = 30.0f;


	sf::CircleShape npc_circle;
	npc_circle.setRadius(c2_circle.r);
	npc_circle.setOrigin(npc_circle.getRadius(), npc_circle.getRadius());
	npc_circle.setPosition(sf::Vector2f{ c2_circle.p.x, c2_circle.p.y });

	c2Circle circle_player;
	circle_player.p = c2v{ player.getCircleShape().getPosition().x, player.getCircleShape().getPosition().y };
	circle_player.r = player.getCircleShape().getRadius();

	sf::VertexArray* arr_ptr = &player.getVertexArray();

	c2Ray ray_player;
	ray_player.p = c2v{ 0,0 };
	ray_player.t = sqrt((pow(player.getVertexPos(1).x, 2) + pow(player.getVertexPos(1).y, 2)));
	ray_player.d = c2v{ player.getVertexPos(1).x / ray_player.t, player.getVertexPos(1).y / ray_player.t };
	
	//ray_player.d = 
	
	// Start the game loop
	while (window.isOpen())
	{
		if (m_currentShape == AABB) // Move Sprite Follow Mouse if current shape is AABB
			player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		else if (m_currentShape == Circle)
			player.getCircleShape().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		else if (m_currentShape == Ray)
		{
			arr_ptr->clear();
			arr_ptr->append(sf::Vertex{ sf::Vector2f{ray_player.p.x, ray_player.p.y} });
			arr_ptr->append(sf::Vertex{ window.mapPixelToCoords(sf::Mouse::getPosition(window)) });

			ray_player.t = sqrt((pow(player.getVertexPos(1).x, 2)) + pow(player.getVertexPos(1).y, 2));

			ray_player.d = c2v{ player.getVertexPos(1).x / ray_player.t, player.getVertexPos(1).y / ray_player.t };
		}
			
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}

		
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player
		if (m_currentShape == AABB)
		{
			aabb_player.min = c2V(
				player.getAnimatedSprite().getPosition().x,
				player.getAnimatedSprite().getPosition().y
			);
			aabb_player.max = c2V(
				player.getAnimatedSprite().getPosition().x +
				player.getAnimatedSprite().getGlobalBounds().width,
				player.getAnimatedSprite().getPosition().y +
				player.getAnimatedSprite().getGlobalBounds().height
			);
		}
		else if (m_currentShape == Circle)
		{
			circle_player.p = c2v{ player.getCircleShape().getPosition().x, player.getCircleShape().getPosition().y };
		}
		else if (m_currentShape == Ray)
		{
			circle_player.p = c2v{ player.getCircleShape().getPosition().x, player.getCircleShape().getPosition().y };
		}
		

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					m_currentShape = AABB;
					player.getCircleShape().setPosition(sf::Vector2f{ -1000.0f, -1000.0f });
					player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					m_currentShape = Circle;

					player.getAnimatedSprite().setPosition(sf::Vector2f{ -1000.0f, -1000.0f });
					player.getCircleShape().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					m_currentShape = Ray;

					player.getAnimatedSprite().setPosition(sf::Vector2f{ -1000.0f, -1000.0f });
					player.getAnimatedSprite().setPosition(sf::Vector2f{ -1000.0f, -1000.0f });
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

#ifdef _DEBUG
		hitboxArray[0].position = player.getAnimatedSprite().getPosition();

		hitboxArray[1].position = sf::Vector2f{
			player.getAnimatedSprite().getPosition().x + player.getAnimatedSprite().getGlobalBounds().width,
			player.getAnimatedSprite().getPosition().y };

		hitboxArray[2].position = sf::Vector2f{
			player.getAnimatedSprite().getPosition().x + player.getAnimatedSprite().getGlobalBounds().width,
			player.getAnimatedSprite().getPosition().y + player.getAnimatedSprite().getGlobalBounds().height };

		hitboxArray[3].position = sf::Vector2f{
			player.getAnimatedSprite().getPosition().x,
			player.getAnimatedSprite().getPosition().y + player.getAnimatedSprite().getGlobalBounds().height };

		hitboxArray[4].position = player.getAnimatedSprite().getPosition();
#endif

		

		
		if (m_currentShape == AABB)
		{
			// Handle input to Player
			player.handleInput(input);

			// Update the Player
			player.update();
		}

		// Update the Player
		npc.update();

		// Check for collisions

		if (m_currentShape == AABB)
		{
			if (c2AABBtoAABB(aabb_player, aabb_npc)
				|| c2AABBtoCapsule(aabb_player, c2_capsule)
				|| c2AABBtoPoly(aabb_player, &c2_polygon, NULL)
				|| c2RaytoAABB(c2_ray, aabb_player, &c2Raycast())
				|| c2CircletoAABB(c2_circle, aabb_player))
				result = 1;
			else
				result = 0;
		}
		else if (m_currentShape == Circle)
		{
			if (c2CircletoCircle(circle_player, c2_circle)
				|| c2RaytoCircle(c2_ray, circle_player, &c2Raycast())
				|| c2CircletoCapsule(circle_player, c2_capsule)
				|| c2CircletoPoly(circle_player, &c2_polygon, NULL))
				result = 1;
			else
				result = 0;
		}
		else if (m_currentShape == Ray)
		{
			if (c2RaytoAABB(ray_player, aabb_npc, &c2Raycast())
				|| c2RaytoCapsule(ray_player, c2_capsule, &c2Raycast())
				|| c2RaytoCircle(ray_player, c2_circle, &c2Raycast())
				|| c2RaytoPoly(ray_player, &c2_polygon, NULL, &c2Raycast()))
				result = 1;
			else
				result = 0;
		}

#ifdef _DEBUG

		cout << ((result != 0) ? ("Collision") : "") << endl;

		if (result){


			for (int i = 0; i < 4; ++i)
				hitboxArray[i].color = sf::Color::Red;
		}
		else {

			for (int i = 0; i < 4; ++i)
				hitboxArray[i].color = sf::Color::Green;

		}
#endif

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		if (m_currentShape == AABB)
			window.draw(player.getAnimatedSprite());
		else if (m_currentShape == Circle)
			window.draw(player.getCircleShape());
		else if (m_currentShape == Ray)
			window.draw(player.getVertexArray());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

#ifdef _DEBUG
		// Draw vertex array
		window.draw(hitboxArray);
#endif

		capsule.draw(window);

		window.draw(npc_triangle);

		window.draw(npc_ray);

		window.draw(npc_circle);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};