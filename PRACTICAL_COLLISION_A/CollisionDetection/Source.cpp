/// <summary>
/// Joshua Dunne - C00241588
/// Start Date: 11/11/19
/// 
/// Estimated Time: ~1 Hour
/// Time Taken: ~1 Hour
/// 
/// Simple collisions for Points, Circles and Boxes.
/// </summary>

#include <iostream>
#include <math.h>
#include <time.h>

struct Point {
	int x;
	int y;

	void print() {
		std::cout << "x: " << x << ", y: " << y << std::endl;
	}
};

struct Circle {
	Point p;
	int r;

	void print() {
		std::cout << "x: " << p.x << ", y: " << p.y << ", r: " << r << std::endl;
	}
};

struct Box {
	Point p;
	int width;
	int height;

	void print()
	{
		std::cout << "x: " << p.x << ", y: " << p.y << ", width: " << width << ", height: " << height << std::endl;
	}
};

int calculate_hypotenuse(Point a, Point b) {

	// Find the distance (Length) of X and Y  

	int x_Distance = b.x - a.x;
	int y_Distance = b.y - a.y;

	// Now that we have the distance (Length)
	// of x and y, use Pythagoras theorem 
	// to get the distance (length of hypotenuse) 
	// between Point a and Point b 

	return static_cast<int>(sqrt(pow(x_Distance, 2) + pow(y_Distance, 2)));
}

bool PointCollision(Point a, Point b);
bool CircleCollision(Circle a, Circle b);
bool CircleToPointCollision(Circle a, Point b);
bool BoxCollision(Box a, Box b);


int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	// Point Collision
	Point player_point;
	player_point.x = rand() % 10 + 1;
	player_point.y = rand() % 10 + 1;

	Point npc_point;
	npc_point.x = rand() % 10 + 1;
	npc_point.y = rand() % 10 + 1;

	// Circle Collision
	Circle player_circle;
	player_circle.p.x = rand() % 10 + 1;
	player_circle.p.y = rand() % 10 + 1;
	player_circle.r = rand() % 2 + 1;
	
	Circle npc_circle;
	npc_circle.p.x = rand() % 10 + 1;
	npc_circle.p.y = rand() % 10 + 1;
	npc_circle.r = rand() % 2 + 1;

	Box player_box;
	player_box.p.x = rand() % 10 + 1;
	player_box.p.y = rand() % 10 + 1;
	player_box.width = rand() % 10 + 1;
	player_box.height = rand() % 10 + 1;

	Box npc_box;
	npc_box.p.x = rand() % 10 + 1;
	npc_box.p.y = rand() % 10 + 1;
	npc_box.width = rand() % 4 + 1;
	npc_box.height = rand() % 4 + 1;

	while (true) 
	{
		// Point Collision ---------------------------------------------------------
		player_point.x = rand() % 10 + 1;
		player_point.y = rand() % 10 + 1;

		npc_point.x = rand() % 10 + 1;
		npc_point.y = rand() % 10 + 1;

		if (PointCollision(player_point, npc_point))
			break;
	}

	while (true)
	{
		// Circle Collision --------------------------------------------------------
		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;

		npc_circle.p.x = rand() % 10 + 1;
		npc_circle.p.y = rand() % 10 + 1;

		if (CircleCollision(player_circle, npc_circle))
			break;
	}

	while (true)
	{
		// Circle -> Point Collision -----------------------------------------------
		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;

		npc_point.x = rand() % 10 + 1;
		npc_point.y = rand() % 10 + 1;

		if (CircleToPointCollision(player_circle, npc_point))
			break;
	}

		
	while (true)
	{
		// Box Collision -----------------------------------------------------------

		player_box.p.x = rand() % 10 + 1;
		player_box.p.y = rand() % 10 + 1;

		npc_box.p.x = rand() % 10 + 1;
		npc_box.p.y = rand() % 10 + 1;

		if (BoxCollision(player_box, npc_box))
			break;
	}

	std::cin.get();
	return 0;
}

/// <summary>
/// Check for collision between two points.
/// Finds the distance between the two points,
/// if the distance is equal to zero, they are overlapping.
/// </summary>
/// <param name="a">Point A</param>
/// <param name="b">Point B</param>
/// <returns> If a collision has happened</returns>
bool PointCollision(Point a, Point b)
{
	// Point Collision check
	if (calculate_hypotenuse(a, b) == 0)
	{
		std::cout << "Point Collision" << std::endl;
		a.print();
		b.print();
		std::cin.get();
		return true;
	}
	else
	{
		std::cout << "No Collision" << std::endl;
		a.print();
		b.print();
		return false;
	}
}

/// <summary>
/// Check for Collision between two Circles
/// Finds the distance between the two points of the circles,
/// then uses their radii to see if they are overlapping.
/// </summary>
/// <param name="a">Circle A</param>
/// <param name="b">Circle B</param>
/// <returns> If a collision has happened</returns>
bool CircleCollision(Circle a, Circle b)
{
	// Circle Collision check
		if (calculate_hypotenuse(a.p, b.p) < (a.r + b.r))
		{
			std::cout << "Circle Collision" << std::endl;
			a.print();
			b.print();
			std::cin.get();
			return true;
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			a.print();
			b.print();
			return false;
		}
}

/// <summary>
/// Check if a Circle and a Point have collided.
/// Gets the distance between the two points,
/// then uses the Radius of the Circle to see if they are overlapping.
/// </summary>
/// <param name="a">Circle A</param>
/// <param name="b">Point B</param>
/// <returns> If a collision has happened</returns>
bool CircleToPointCollision(Circle a, Point b)
{
	// Circle and Point collision
	if (calculate_hypotenuse(a.p, b) < a.r)
	{
		std::cout << "Circle to Point Collision" << std::endl;
		a.print();
		b.print();
		std::cin.get();
		return true;
	}
	else
	{
		std::cout << "No Collision" << std::endl;
		a.print();
		b.print();
		return false;
	}
}

/// <summary>
/// Using Axis-Aligned Bounding Box to determine collisions between two Boxes.
/// This is done by checking all sides of each box for a Gap.
/// If there is any gap, then collision does not exist.
/// By using AABB, we assume there are no rotations in play.
/// </summary>
/// <param name="a">Box A</param>
/// <param name="b">Box B</param>
/// <returns> If a collision has happened</returns>
bool BoxCollision(Box a, Box b)
{
	if (a.p.x < b.p.x + b.width &&
		a.p.x + a.width > b.p.x &&
		a.p.y < b.p.y + b.height &&
		a.p.y + a.height > b.p.y) // Check for gaps on all sides of the Box, no gap means collision.
	{
		std::cout << "Box Collision" << std::endl;
		a.print();
		b.print();
		std::cin.get();
		return true;
	}
	else
	{
		std::cout << "No Collision" << std::endl;
		a.print();
		b.print();
		return false;
	}
}
