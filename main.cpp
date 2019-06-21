#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Utility.h"
#include <iostream>
#include <list>

using namespace std;

sf::Vertex drawFieldLine(Field F, Point p, eField eF);

int main()
{
	const int step = 50;
	const int width = 800;
	const int height = 800;
	sf::RenderWindow window(sf::VideoMode(width, height), "Electric Field Lines");
	window.setFramerateLimit(10);

	float epsilon = 0.1;
	Field F = Field(epsilon);
	F.addCharge(500, 700, 0.1); // pixelposition and charge
	F.addCharge(30, 100, -.4);

	const int nPtsX = width / step;
	const int nPtsY = height / step;

	const int nPts = nPtsX * nPtsY;
	struct Point coords[nPts];
	
	float stepX = (float)width / (nPtsX - 1);
	float stepY = (float)height / (nPtsY - 1);

	Point p;
	for (unsigned i = 0; i < nPts; i++)
	{
		coords[i].x = stepX * (i % nPtsX);
		coords[i].y = stepY * (i / nPtsY);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();

		// Calculate electric field:
		for (unsigned i = 0; i < nPts; i++)
		{
			Point p = coords[i];
			eField eF = F.electricField(p.x, p.y);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(p.x, p.y)),
				sf::Vertex(sf::Vector2f(p.x + eF.eX, p.y + eF.eY))
			};
			window.draw(line, 2, sf::Lines);
		}

		window.display();
	}

	return 0;
}



sf::Vertex drawFieldLine(Field F, Point p, eField eF)
{
	// Etc, continue somewhere here
}