#include <iostream>
#include <math.h>
#include <time.h>

struct Point {
	int x;
	int y;

	void print() {
		std::cout << "x:" << x << " y:" << y << std::endl;
	}
};

struct Circle {
	Point p;
	int r;

	void print() {
		std::cout << "x:" << p.x << " y:" << p.y << " r:" << r << std::endl;
	}
};

struct Box {
	Point p;
	int width;
	int height;

	void print()
	{
		std::cout << "x:" << p.x << " y:" << p.y << " width:" << width << "height:" << height << std::endl;
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

void PointCollision(Point a, Point b);
void CircleCollision(Circle a, Circle b);
void CircleToPointCollision(Circle a, Point b);


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
	player_box.width = rand() % 4 + 1;
	player_box.height = rand() % 4 + 1;

	Box npc_box;
	npc_box.p.x = rand() % 10 + 1;
	npc_box.p.y = rand() % 10 + 1;
	npc_box.width = rand() % 4 + 1;
	npc_box.height = rand() % 4 + 1;


	while (true) {
		// Point Collision ---------------------------------------------------------
		player_point.x = rand() % 10 + 1;
		player_point.y = rand() % 10 + 1;

		npc_point.x = rand() % 10 + 1;
		npc_point.y = rand() % 10 + 1;

		PointCollision(player_point, npc_point);

		// Circle Collision --------------------------------------------------------
		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;

		npc_circle.p.x = rand() % 10 + 1;
		npc_circle.p.y = rand() % 10 + 1;

		CircleCollision(player_circle, npc_circle);

		// Circle -> Point Collision -----------------------------------------------
		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;

		npc_point.x = rand() % 10 + 1;
		npc_point.y = rand() % 10 + 1;

		CircleToPointCollision(player_circle, npc_point);

		// Box Collision -----------------------------------------------------------

		player_box.p.x = rand() % 10 + 1;
		player_box.p.y = rand() % 10 + 1;

		npc_box.p.x = rand() % 10 + 1;
		npc_box.p.y = rand() % 10 + 1;
	}

	return 0;
}

void PointCollision(Point a, Point b)
{
	// Point Collision check
	if (calculate_hypotenuse(a, b) == 0)
	{
		std::cout << "Point Collision" << std::endl;
		a.print();
		b.print();
		std::cin.get();
	}
	else
	{
		std::cout << "No Collision" << std::endl;
		a.print();
		b.print();
	}
}

void CircleCollision(Circle a, Circle b)
{
	// Circle Collision check
		if (calculate_hypotenuse(a.p, b.p) < (a.r + b.r))
		{
			std::cout << "Circle Collision" << std::endl;
			a.print();
			b.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			a.print();
			b.print();
		}
}

void CircleToPointCollision(Circle a, Point b)
{
	// Circle and Point collision
	if (calculate_hypotenuse(a.p, b) < a.r)
	{
		std::cout << "Circle to Point Collision" << std::endl;
		a.print();
		b.print();
		std::cin.get();
	}
	else
	{
		std::cout << "No Collision" << std::endl;
		a.print();
		b.print();
	}
}