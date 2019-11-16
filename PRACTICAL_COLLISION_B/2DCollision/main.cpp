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


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);

	// vertex array of lines
	sf::VertexArray hitboxArray{ sf::LineStrip, 5 };

	Capsule capsule{ sf::Vector2f{100.0f, 50.0f}, sf::Vector2f{100.0f, 100.0f}, 25 };

	c2Capsule c2_capsule;
	c2_capsule.a = c2v{ capsule.m_posA.x, capsule.m_posA.y };
	c2_capsule.b = c2v{ capsule.m_posB.x, capsule.m_posB.y };
	c2_capsule.r = capsule.m_radius;

	VertexArray npc_triangle{ sf::Triangles, 3 };

	c2Poly c2_polygon;
	c2_polygon.count = 3;
	c2_polygon.verts[0].x = 400;
	c2_polygon.verts[0].y = 100;

	c2_polygon.verts[1].x = 350;
	c2_polygon.verts[1].y = 200;

	c2_polygon.verts[2].x = 450;
	c2_polygon.verts[2].y = 200;

	npc_triangle[0].position = sf::Vector2f{ c2_polygon.verts[0].x, c2_polygon.verts[0].y };
	npc_triangle[1].position = sf::Vector2f{ c2_polygon.verts[1].x, c2_polygon.verts[1].y };
	npc_triangle[2].position = sf::Vector2f{ c2_polygon.verts[2].x, c2_polygon.verts[2].y };


	c2Ray c2_ray;
	c2_ray.p = c2v{ 450, 550 };
	c2_ray.d = c2v{ 1, 0 };
	c2_ray.t = 50.0f;

	VertexArray npc_ray{ sf::Lines, 2 };
	npc_ray[0].position = { sf::Vector2f{c2_ray.p.x, c2_ray.p.y} };
	npc_ray[1].position = { sf::Vector2f{c2_ray.p.x + (c2_ray.t * c2_ray.d.x), c2_ray.p.y +(c2_ray.t * c2_ray.d.y)} };
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
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

		// Update Player AABB
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

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions

		if (c2AABBtoAABB(aabb_player, aabb_npc) 
			|| c2AABBtoCapsule(aabb_player, c2_capsule)
			|| c2AABBtoPoly(aabb_player, &c2_polygon, NULL) 
			|| c2RaytoAABB(c2_ray, aabb_player, &c2Raycast()))
			result = 1;
		else
			result = 0;

		cout << ((result != 0) ? ("Collision") : "") << endl;

		if (result){

#ifdef _DEBUG
			for (int i = 0; i < 4; ++i)
				hitboxArray[i].color = sf::Color::Red;
#endif

			player.getAnimatedSprite().setColor(sf::Color(255,0,0));
		}
		else {
#ifdef _DEBUG
			for (int i = 0; i < 4; ++i)
				hitboxArray[i].color = sf::Color::Green;
#endif

			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

#ifdef _DEBUG
		// Draw vertex array
		window.draw(hitboxArray);
#endif

		capsule.draw(window);

		window.draw(npc_triangle);

		window.draw(npc_ray);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};